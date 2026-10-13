#define TRUE  1
#define FALSE 0
#define bool BYTE
#include <stdio.h>
#include <stdlib.h>

#include "stm32f1xx_hal.h"
#include "main.h"

#include "diskio.h"
#include "fatfs_sd.h"
#include "fatfs.h"
//
extern SPI_HandleTypeDef hspi1;
extern volatile uint8_t Timer1, Timer2;                    /* 10ms ë§ˆë‹¤ ê°ì†Œ?ï¿½ëŠ” ?ï¿?ï¿½ë¨¸ */

static volatile DSTATUS Stat = STA_NOINIT;              /* ?ï¿½ìŠ¤???ï¿½íƒœ Flag*/
static uint8_t CardType;                                /* SD ?ï¿??0:MMC, 1:SDC, 2:Block addressing */
static uint8_t PowerFlag = 0;                           /* Power ?ï¿½íƒœ Flag */

/* SPI Chip Select */
static void SELECT(void)
{
  HAL_GPIO_WritePin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin, GPIO_PIN_RESET);
}

/* SPI Chip Deselect */
static void DESELECT(void)
{
  HAL_GPIO_WritePin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin, GPIO_PIN_SET);
}

/* SPI ?ï¿½ì´???ï¿½ì†¡ */
static void SPI_TxByte(BYTE data)
{
  while (HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY);
  HAL_SPI_Transmit(&hspi1, &data, 1, SPI_TIMEOUT);
}

/* SPI ?ï¿½ì´???ï¿½ìˆ˜??ë¦¬í„´???ï¿½ìˆ˜ */
static uint8_t SPI_RxByte(void)
{
  uint8_t dummy, data;
  dummy = 0xFF;
  data = 0;

  while ((HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY));
  HAL_SPI_TransmitReceive(&hspi1, &dummy, &data, 1, SPI_TIMEOUT);

  return data;
}

/* SPI ?ï¿½ì´???ï¿½ìˆ˜???ï¿½ì¸?ï¿½í˜• ?ï¿½ìˆ˜ */
static void SPI_RxBytePtr(uint8_t *buff)
{
  *buff = SPI_RxByte();
}

/* SDì¹´ë“œ Ready ?ï¿½ï¿½?*/
static uint8_t SD_ReadyWait(void)
{
  uint8_t res;

  /* 500ms ì¹´ìš´??ì¤€ï¿?*/
  Timer2 = 50;
  SPI_RxByte();

  do
  {
    /* 0xFF ê°’ì´ ?ï¿½ì‹ ????ê¹Œï¿½? SPI ?ï¿½ì‹  */
    res = SPI_RxByte();
  } while ((res != 0xFF) && Timer2);

  return res;
}

/* ?ï¿½ì› ì¼œê¸° */
static void SD_PowerOn(void)
{
  uint8_t cmd_arg[6];
  uint32_t Count = 0x1FFF;

  /* Deselect ?ï¿½íƒœ?ï¿½ì„œ SPI ë©”ì‹œì§€ï¿??ï¿½ì†¡?ï¿½ì—¬ ?ï¿½ê¸°??ï¿½ë¡œ ë§Œë“ ?? */
  DESELECT();

  for(int i = 0; i < 10; i++)
  {
    SPI_TxByte(0xFF);
  }

  /* SPI Chips Select */
  SELECT();

  /* ì´ˆê¸° GO_IDLE_STATE ?ï¿½íƒœ ?ï¿½í™˜ */
  cmd_arg[0] = (CMD0 | 0x40);
  cmd_arg[1] = 0;
  cmd_arg[2] = 0;
  cmd_arg[3] = 0;
  cmd_arg[4] = 0;
  cmd_arg[5] = 0x95;

  /* ëª…ë ¹ ?ï¿½ì†¡ */
  for (int i = 0; i < 6; i++)
  {
    SPI_TxByte(cmd_arg[i]);
  }

  /* ?ï¿½ë‹µ ?ï¿½ï¿½?*/
  while ((SPI_RxByte() != 0x01) && Count)
  {
    Count--;
  }

  DESELECT();
  SPI_TxByte(0XFF);

  PowerFlag = 1;
}

/* ?ï¿½ì› ?ï¿½ê¸° */
static void SD_PowerOff(void)
{
  PowerFlag = 0;
}

/* ?ï¿½ì› ?ï¿½íƒœ ?ï¿½ì¸ */
static uint8_t SD_CheckPower(void)
{
  /*  0=off, 1=on */
  return PowerFlag;
}

/* ?ï¿½ì´???ï¿½í‚· ?ï¿½ì‹  */
static bool SD_RxDataBlock(BYTE *buff, UINT btr)
{
  uint8_t token;

  /* 100ms ?ï¿?ï¿½ë¨¸ */
  Timer1 = 10;

  /* ?ï¿½ë‹µ ?ï¿½ï¿½?*/
  do
  {
    token = SPI_RxByte();
  } while((token == 0xFF) && Timer1);

  /* 0xFE ?ï¿½ì™¸ Token ?ï¿½ì‹  ???ï¿½ëŸ¬ ì²˜ë¦¬ */
  if(token != 0xFE)
    return FALSE;

  /* ë²„í¼???ï¿½ì´???ï¿½ì‹  */
  while(btr--)
  {
    SPI_RxBytePtr(buff++);
  }

  SPI_RxByte(); /* CRC ë¬´ì‹œ */
  SPI_RxByte();

  return TRUE;
}

/* ?ï¿½ì´???ï¿½ì†¡ ?ï¿½í‚· */
#if _READONLY == 0
static bool SD_TxDataBlock(const BYTE *buff, BYTE token)
{
  uint8_t resp = 0xFF, i = 0;  /* resp ì´ˆê¸°??*/
  uint16_t wc;

  /* SDì¹´ë“œ ì¤€ï¿??ï¿½ï¿½?*/
  if (SD_ReadyWait() != 0xFF)
    return FALSE;

  /* ?ï¿½í° ?ï¿½ì†¡ */
  SPI_TxByte(token);

  /* ?ï¿½ì´???ï¿½í°??ê²½ìš° */
  if (token != 0xFD)
  {
    wc = 512;

    /* 512 ë°”ì´???ï¿½ì´???ï¿½ì†¡ */
    while(wc--)
    {
      SPI_TxByte(*buff++);
    }

    SPI_RxByte();       /* CRC ë¬´ì‹œ */
    SPI_RxByte();

    /* ?ï¿½ì´???ï¿½ë‹µ ?ï¿½ì‹  */
    while (i <= 64)
    {
      resp = SPI_RxByte();

      /* ?ï¿½ëŸ¬ ?ï¿½ë‹µ ì²˜ë¦¬ */
      if ((resp & 0x1F) == 0x05)
        break;

      i++;
    }

    /* SPI ?ï¿½ì‹  ë²„í¼ Clear - ?ï¿?ï¿½ì•„??ì¶”ï¿½? */
    Timer1 = 20; /* 200ms ?ï¿?ï¿½ì•„??*/
    while (SPI_RxByte() == 0 && Timer1);
  }

  if ((resp & 0x1F) == 0x05)
    return TRUE;
  else
    return FALSE;
}
#endif /* _READONLY */

/* CMD ?ï¿½í‚· ?ï¿½ì†¡ */
static BYTE SD_SendCmd(BYTE cmd, DWORD arg)
{
  uint8_t crc, res;

  /* SDì¹´ë“œ ?ï¿½ï¿½?*/
  if (SD_ReadyWait() != 0xFF)
    return 0xFF;

  /* ëª…ë ¹ ?ï¿½í‚· ?ï¿½ì†¡ */
  SPI_TxByte(cmd); 			/* Command */
  SPI_TxByte((BYTE) (arg >> 24)); 	/* Argument[31..24] */
  SPI_TxByte((BYTE) (arg >> 16)); 	/* Argument[23..16] */
  SPI_TxByte((BYTE) (arg >> 8)); 	/* Argument[15..8] */
  SPI_TxByte((BYTE) arg); 		/* Argument[7..0] */

  /* ëª…ë ¹ï¿?CRC ì¤€ï¿?*/
  crc = 0;
  if (cmd == CMD0)
    crc = 0x95; /* CRC for CMD0(0) */

  if (cmd == CMD8)
    crc = 0x87; /* CRC for CMD8(0x1AA) */

  /* CRC ?ï¿½ì†¡ */
  SPI_TxByte(crc);

  /* CMD12 Stop Reading ëª…ë ¹??ê²½ìš°?ï¿½ëŠ” ?ï¿½ë‹µ ë°”ì´???ï¿½ë‚˜ï¿?ë²„ë¦°??*/
  if (cmd == CMD12)
    SPI_RxByte();

  /* 10???ï¿½ì— ?ï¿½ìƒ ?ï¿½ì´?ï¿½ï¿½? ?ï¿½ì‹ ?ï¿½ë‹¤. */
  uint8_t n = 10;
  do
  {
    res = SPI_RxByte();
  } while ((res & 0x80) && --n);

  return res;
}
/* SDÄ«µå ÃÊ±âÈ­ */
DSTATUS SD_disk_initialize(BYTE drv)
{
  uint8_t n, type, ocr[4];

  /* ´ÜÀÏ µå¶óÀÌºê¸¸ Áö¿ø */
  if (drv)
    return STA_NOINIT;

  /* SDÄ«µå°¡ ¾ø´Ù°í Ç¥½ÃµÈ °æ¿ì */
  if (Stat & STA_NODISK)
    return Stat;

  printf("SD_disk_initialize start\r\n");

  /* ÃÊ±âÈ­ Àü ´À¸° ¼Óµµ·Î º¯°æ (400kHz ÀÌÇÏ) */
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
  HAL_SPI_Init(&hspi1);

  /* SDÄ«µå Power On */
  SD_PowerOn();

  /* SPI Åë½ÅÀ» À§ÇØ Chip Select */
  SELECT();

  /* SDÄ«µå Å¸ÀÔ ÃÊ±âÈ­ */
  type = 0;

  /* Idle »óÅÂ·Î ÁøÀÔ (CMD0) */
  uint8_t res0 = SD_SendCmd(CMD0, 0);
  printf("CMD0 response = 0x%02X\r\n", res0);

  if (res0 == 1)
  {
    /* Å¸ÀÓ¾Æ¿ô 1ÃÊ ¼³Á¤ */
    Timer1 = 100;

    /* SD ¹öÀü È®ÀÎ */
    uint8_t res8 = SD_SendCmd(CMD8, 0x1AA);
    printf("CMD8 response = 0x%02X\r\n", res8);

    if (res8 == 1)
    {
      /* SDC Ver2+ */
      for (n = 0; n < 4; n++)
      {
        ocr[n] = SPI_RxByte();
      }
      printf("CMD8 OCR = %02X %02X %02X %02X\r\n", ocr[0], ocr[1], ocr[2], ocr[3]);

      if (ocr[2] == 0x01 && ocr[3] == 0xAA)
      {
        /* 2.7-3.6V µ¿ÀÛ¹üÀ§ È®ÀÎ */
        do {
          if (SD_SendCmd(CMD55, 0) <= 1 && SD_SendCmd(CMD41, 1UL << 30) == 0)
            break; /* ACMD41 with HCS bit */
        } while (Timer1);

        if (Timer1 && SD_SendCmd(CMD58, 0) == 0)
        {
          /* Check CCS bit */
          for (n = 0; n < 4; n++)
          {
            ocr[n] = SPI_RxByte();
          }
          printf("CMD58 OCR = %02X %02X %02X %02X\r\n", ocr[0], ocr[1], ocr[2], ocr[3]);

          type = (ocr[0] & 0x40) ? 6 : 2;   // SDHC/SDXC or SDSC
        }
      }
    }
    else
    {
      /* SDC Ver1 or MMC */
      type = (SD_SendCmd(CMD55, 0) <= 1 && SD_SendCmd(CMD41, 0) <= 1) ? 2 : 1; /* SDC : MMC */

      do {
        if (type == 2)
        {
          if (SD_SendCmd(CMD55, 0) <= 1 && SD_SendCmd(CMD41, 0) == 0)
            break; /* ACMD41 */
        }
        else
        {
          if (SD_SendCmd(CMD1, 0) == 0)
            break; /* CMD1 */
        }
      } while (Timer1);

      if (!Timer1 || SD_SendCmd(CMD16, 512) != 0)
      {
        /* ºí·Ï ±æÀÌ ¼³Á¤ ½ÇÆĞ */
        type = 0;
      }
    }
  }
  else
  {
    printf("CMD0 failed! (card not responding)\r\n");
  }

  CardType = type;
  printf("CardType = %d\r\n", CardType);

  DESELECT();
  SPI_RxByte(); /* Idle »óÅÂ À¯Áö (Release DO) */

  if (type)
  {
    /* Clear STA_NOINIT */
    Stat &= ~STA_NOINIT;

    /* ÃÊ±âÈ­ ¼º°ø ÈÄ °í¼ÓÀ¸·Î º¯°æ */
    hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
    HAL_SPI_Init(&hspi1);

    printf("SD_disk_initialize SUCCESS\r\n");
  }
  else
  {
    /* Initialization failed */
    SD_PowerOff();
    printf("SD_disk_initialize FAILED\r\n");
  }

  return Stat;
}

/* ?ï¿½ìŠ¤???ï¿½íƒœ ?ï¿½ì¸ */
DSTATUS SD_disk_status(BYTE drv)
{
  if (drv)
    return STA_NOINIT;

  return Stat;
}

/* ?ï¿½í„° ?ï¿½ê¸° */
DRESULT SD_disk_read(BYTE pdrv, BYTE* buff, DWORD sector, UINT count)
{
  if (pdrv || !count)
    return RES_PARERR;

  if (Stat & STA_NOINIT)
    return RES_NOTRDY;

  if (!(CardType & 4))
    sector *= 512;      /* ì§€??sectorï¿?Byte addressing ?ï¿½ìœ„ï¿?ë³€ï¿?*/

  SELECT();

  if (count == 1)
  {
    /* ?ï¿½ï¿½? ë¸”ë¡ ?ï¿½ê¸° */
    if ((SD_SendCmd(CMD17, sector) == 0) && SD_RxDataBlock(buff, 512))
      count = 0;
  }
  else
  {
    /* ?ï¿½ì¤‘ ë¸”ë¡ ?ï¿½ê¸° */
    if (SD_SendCmd(CMD18, sector) == 0)
    {
      do {
        if (!SD_RxDataBlock(buff, 512))
          break;

        buff += 512;
      } while (--count);

      /* STOP_TRANSMISSION, ëª¨ë“  ë¸”ëŸ­?????ï¿½ï¿½? ?? ?ï¿½ì†¡ ì¤‘ï¿½? ?ï¿½ì²­ */
      SD_SendCmd(CMD12, 0);
    }
  }

  DESELECT();
  SPI_RxByte(); /* Idle ?ï¿½íƒœ(Release DO) */

  return count ? RES_ERROR : RES_OK;
}

/* ?ï¿½í„° ?ï¿½ê¸° */
#if _READONLY == 0
DRESULT SD_disk_write(BYTE pdrv, const BYTE* buff, DWORD sector, UINT count)
{
  if (pdrv || !count)
    return RES_PARERR;

  if (Stat & STA_NOINIT)
    return RES_NOTRDY;

  if (Stat & STA_PROTECT)
    return RES_WRPRT;

  if (!(CardType & 4))
    sector *= 512; /* ì§€??sectorï¿?Byte addressing ?ï¿½ìœ„ï¿?ë³€ï¿?*/

  SELECT();

  if (count == 1)
  {
    /* ?ï¿½ï¿½? ë¸”ë¡ ?ï¿½ê¸° */
    if ((SD_SendCmd(CMD24, sector) == 0) && SD_TxDataBlock(buff, 0xFE))
      count = 0;
  }
  else
  {
    /* ?ï¿½ì¤‘ ë¸”ë¡ ?ï¿½ê¸° */
    if (CardType & 2)
    {
      SD_SendCmd(CMD55, 0);
      SD_SendCmd(CMD23, count); /* ACMD23 */
    }

    if (SD_SendCmd(CMD25, sector) == 0)
    {
      do {
        if(!SD_TxDataBlock(buff, 0xFC))
          break;

        buff += 512;
      } while (--count);

      if(!SD_TxDataBlock(0, 0xFD))
      {
        count = 1;
      }
    }
  }

  DESELECT();
  SPI_RxByte();

  return count ? RES_ERROR : RES_OK;
}
#endif /* _READONLY */

/* ê¸°ï¿½? ?ï¿½ìˆ˜ */
DRESULT SD_disk_ioctl(BYTE drv, BYTE ctrl, void *buff)
{
  DRESULT res;
  BYTE n, csd[16], *ptr = buff;
  WORD csize;

  if (drv)
    return RES_PARERR;

  res = RES_ERROR;

  if (ctrl == CTRL_POWER)
  {
    switch (*ptr)
    {
    case 0:
      if (SD_CheckPower())
        SD_PowerOff();          /* Power Off */
      res = RES_OK;
      break;
    case 1:
      SD_PowerOn();             /* Power On */
      res = RES_OK;
      break;
    case 2:
      *(ptr + 1) = (BYTE) SD_CheckPower();
      res = RES_OK;             /* Power Check */
      break;
    default:
      res = RES_PARERR;
    }
  }
  else
  {
    if (Stat & STA_NOINIT)
      return RES_NOTRDY;

    SELECT();

    switch (ctrl)
    {
    case GET_SECTOR_COUNT:
      /* SDì¹´ë“œ ??Sector??ê°œìˆ˜ (DWORD) */
      if ((SD_SendCmd(CMD9, 0) == 0) && SD_RxDataBlock(csd, 16))
      {
        if ((csd[0] >> 6) == 1)
        {
          /* SDC ver 2.00 - ?ï¿½í™•??C_SIZE ?ï¿½ë“œ ?ï¿½ì‹± */
          csize = ((DWORD)(csd[7] & 0x3F) << 16) | ((DWORD)csd[8] << 8) | csd[9];
          *(DWORD*) buff = (csize + 1) << 10;
        }
        else
        {
          /* MMC or SDC ver 1.XX */
          n = (csd[5] & 15) + ((csd[10] & 128) >> 7) + ((csd[9] & 3) << 1) + 2;
          csize = (csd[8] >> 6) + ((WORD) csd[7] << 2) + ((WORD) (csd[6] & 3) << 10) + 1;
          *(DWORD*) buff = (DWORD) csize << (n - 9);
        }

        res = RES_OK;
      }
      break;

    case GET_SECTOR_SIZE:
      /* ?ï¿½í„°???ï¿½ìœ„ ?ï¿½ê¸° (WORD) */
      *(WORD*) buff = 512;
      res = RES_OK;
      break;

    case CTRL_SYNC:
      /* ?ï¿½ê¸° ?ï¿½ê¸°??*/
      if (SD_ReadyWait() == 0xFF)
        res = RES_OK;
      break;

    case MMC_GET_CSD:
      /* CSD ?ï¿½ë³´ ?ï¿½ì‹  (16 bytes) */
      if (SD_SendCmd(CMD9, 0) == 0 && SD_RxDataBlock(ptr, 16))
        res = RES_OK;
      break;

    case MMC_GET_CID:
      /* CID ?ï¿½ë³´ ?ï¿½ì‹  (16 bytes) */
      if (SD_SendCmd(CMD10, 0) == 0 && SD_RxDataBlock(ptr, 16))
        res = RES_OK;
      break;

    case MMC_GET_OCR:
      /* OCR ?ï¿½ë³´ ?ï¿½ì‹  (4 bytes) */
      if (SD_SendCmd(CMD58, 0) == 0)
      {
        for (n = 0; n < 4; n++)
        {
          *ptr++ = SPI_RxByte();
        }

        res = RES_OK;
      }
      break;

    default:
      res = RES_PARERR;
    }

    DESELECT();
    SPI_RxByte();
  }

  return res;
}

/* main()ï¿½Ì³ï¿½ ï¿½Ê±ï¿½È­ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ ï¿½ï¿½ ï¿½ï¿½ */





//================================================
//================================================
//================================================
FATFS fs;
FATFS *pfs;
FIL fil;//
FRESULT fres;
DWORD fre_clust;
uint32_t total, sd_free;
char buffer[100];//

uint8_t SD_Error_Chk(FRESULT errCode, const char* msg)
{
	if(errCode != FR_OK)
	{
		printf("%s Error = %d\r\n", msg, errCode);   // ï¿½ï¿½ï¿½ï¿½ ï¿½Úµåµµ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿?
		return 1;        // ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ 1(ï¿½ï¿½) ï¿½ï¿½ È£ï¿½ï¿½Î¿ï¿½ï¿½ï¿?return Ã³ï¿½ï¿½
	}
	else
	{
		//printf("%s OK\r\n", msg);
		return 0;        // ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ 0(ï¿½ï¿½ï¿½ï¿½) ï¿½ï¿½ È£ï¿½ï¿½Î¿ï¿½ï¿½ï¿?ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½
	}
}

//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½Úµï¿½

/**
  * @brief  SDÄ«ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½Ã¼/ï¿½ï¿½ï¿½ï¿½ ï¿½ë·®ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Ï°ï¿?Ä«ï¿½ï¿½ ï¿½ï¿½ï¿½Â¸ï¿½ Ã¼Å©
  * @retval 1: ï¿½ï¿½ï¿½ï¿½(Ä«ï¿½ï¿½ ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½), 0: ï¿½ï¿½ï¿½ï¿½
  */
uint8_t SD_CheckFreeSpace(void)
{
  if(SD_Error_Chk(f_getfree("", &fre_clust, &pfs), "f_getfree"))
  {
    return 1;
  }

  total = (uint32_t)((pfs->n_fatent - 2) * pfs->csize * 0.5);
  sd_free  = (uint32_t)(fre_clust * pfs->csize * 0.5);

  printf("Total: %lu KB, Free: %lu KB\r\n", total, sd_free);

  return 0;
}

void SD_Init(void)
{
  if(SD_Error_Chk(f_mount(&fs, "", 0), "f_mount"))return;
  if(SD_CheckFreeSpace())return;

    /* 5ï¿½ï¿½ ï¿½ï¿½É¾ï¿?ï¿½ï¿½ï¿½Í¸ï¿½, ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ (ï¿½Ì¹ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ FR_EXIST, ï¿½ï¿½ï¿½ï¿½) */

    f_mkdir("ERROR_LOG");

  printf("SD_Init Done\r\n");
}

void SD_Read_All(const char* filename)
{

	if(SD_Error_Chk(f_open(&fil, filename, FA_READ), "f_open"))return;

	while(f_gets(buffer, sizeof(buffer), &fil))
	{
	  printf("%s", buffer);
	}

	SD_Error_Chk(f_close(&fil), "f_close");
	printf("SD_Read_All Done\r\n");

}

void SD_Read_Addr(const char* filename, uint16_t add, uint16_t len)
{
  UINT br;
  uint8_t buf[100] = {0,};

  if(len > 100)
  {
    printf("len Over\r\n");
    return;
  }


  if(SD_Error_Chk(f_open(&fil, filename, FA_READ), "f_open"))return;


  if(SD_Error_Chk(f_lseek(&fil, add), "f_lseek"))
  {
  	f_close(&fil);
	return;
  }

  if(SD_Error_Chk(f_read(&fil, buf, len, &br), "f_read"))
  {
	f_close(&fil);
	return;
  }

  if(br == 0) printf("No data (offset %u is beyond EOF)\r\n", add); // ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½Í°ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ (offsetï¿½ï¿½ EOF ï¿½ï¿½ï¿½ï¿½)
  else
  {
    printf("read %u bytes: %.*s\r\n", br, br, buf);
    if(br < len) printf("Partial read: requested %u, got %u bytes\r\n", len, br);   // ï¿½ï¿½Ã»ï¿½ï¿½ ï¿½ï¿½ï¿½Ìºï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ (ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½É¸ï¿½)
  }

  SD_Error_Chk(f_close(&fil), "f_close");
  printf("SD_Read_Addr Done\r\n");
}



void SD_Write_Addr(const char* filename, const uint8_t* data, uint16_t len)
{
  UINT bw;
  uint32_t pos;


  if(SD_Error_Chk(f_open(&fil, filename, FA_OPEN_ALWAYS | FA_WRITE), "f_open"))
    return;

  pos = f_size(&fil);		   // ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ Å©ï¿½ï¿½ = ï¿½ï¿½ ï¿½ï¿½Ä¡
  if(SD_Error_Chk(f_lseek(&fil, pos), "f_lseek"))
  {
    f_close(&fil);
    return;
  }



  if(SD_Error_Chk(f_write(&fil, data, len, &bw), "f_write"))
  {
    f_close(&fil);
    return;
  }

  if(bw < len)
    printf("Partial write: requested %u, written %u bytes\r\n", len, bw);
  else
    printf("write %u bytes at offset %u\r\n", bw, pos);

  SD_Error_Chk(f_close(&fil), "f_close");
  printf("SD_Write_Addr Done\r\n");
}



typedef struct {
  uint16_t hhmm;     // 0~2359 ï¿½ï¿½ï¿½Â·ï¿½ ï¿½ï¿½:ï¿½ï¿½ (ï¿½ï¿½Â¥ï¿½ï¿½ ï¿½ï¿½ï¿½Ï¸ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½Ğ¸ï¿½, ï¿½Æ·ï¿½ ï¿½ï¿½ï¿½ï¿½)
  uint16_t len;      // ï¿½ï¿½ ï¿½ï¿½ï¿½Úµï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
  // ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½(lenï¿½ï¿½ï¿½ï¿½Æ®)ï¿½ï¿½ ï¿½Ì¾ï¿½ï¿½ï¿½
} RecordHeader;

void SD_Write_Record(char* dirName, uint32_t yymmdd, uint16_t hhmm, const uint8_t* data, uint16_t len)
{
  char filename[24];
  char header[20];
  uint32_t pos;
  UINT bw;
  UINT header_len;
  uint32_t YYMMDDhhmm = yymmdd*10000UL + hhmm;


  sprintf(filename, "%s/error_log.txt", dirName);  // "TNOH/260621.txt"

  // ½Ã°£À» ÅØ½ºÆ®·Î º¯È¯ (¿¹: "0900,0008,")
  sprintf(header, "%010lu,%04u,", YYMMDDhhmm, len);
  header_len = strlen(header);

  if(SD_Error_Chk(f_open(&fil, filename, FA_OPEN_ALWAYS | FA_WRITE), "f_open"))
    return;

  pos = f_size(&fil);
  if(SD_Error_Chk(f_lseek(&fil, pos), "f_lseek"))
  {
    f_close(&fil);
    return;
  }

  // Çì´õ ¾²±â (ÅØ½ºÆ® Çü½Ä)
  if(SD_Error_Chk(f_write(&fil, header, header_len, &bw), "f_write(hdr)"))
  {
    f_close(&fil);
    return;
  }

  if(bw < header_len)
  {
    printf("Header write incomplete! requested %u, written %u\r\n", header_len, bw);
    f_close(&fil);
    return;
  }

  // µ¥ÀÌÅÍ ¾²±â
  if(SD_Error_Chk(f_write(&fil, data, len, &bw), "f_write(data)"))
  {
    f_close(&fil);
    return;
  }

  if(bw < len)
  {
    printf("Data write incomplete! requested %u, written %u\r\n", len, bw);
    // return ÇÏÁö ¾Ê°í f_close()±îÁö ÁøÇà
  }

  SD_Error_Chk(f_close(&fil), "f_close");
}


void SD_Read_Range(const char* dirName, uint32_t yymmdd,  uint16_t startHHMM, uint16_t endHHMM)
{
  RecordHeader hdr;
  UINT br;
  uint8_t buf[300];   // ï¿½Ö´ï¿½ ï¿½ï¿½ï¿½Ì¸ï¿½Å­ ï¿½ï¿½ï¿½ï¿½ (ï¿½î¿µ ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½)
  char filename[24];
  sprintf(filename, "%s/%lu.txt", dirName, yymmdd);   // "TNOH/260621.txt"

  if(SD_Error_Chk(f_open(&fil, filename, FA_READ), "f_open"))
    return;

  while(1)
  {
    FRESULT res = f_read(&fil, &hdr, sizeof(hdr), &br);
    if(res != FR_OK || br < sizeof(hdr))
      break;   // ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½ (ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½)

    if(hdr.hhmm >= startHHMM && hdr.hhmm <= endHHMM)
    {
      // ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ ? ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
      if(SD_Error_Chk(f_read(&fil, buf, hdr.len, &br), "f_read"))
	  {
		f_close(&fil);
		return;
	  }
	  if(br < hdr.len) printf("Warning: header says %u bytes but only %u read (corrupted?)\r\n", hdr.len, br);

	  printf("%s [%04u] %u bytes: %.*s\r\n",dirName, hdr.hhmm, br, br, buf);
      // ï¿½ï¿½ï¿½â¼­ ï¿½ï¿½ï¿½ï¿½ ï¿½Û½Å¿ï¿½ ï¿½ï¿½ï¿½Û¿ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½Ï°Å³ï¿½ ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½
    }
    else
    {
      // ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ ? ï¿½ï¿½ï¿½ï¿½ï¿½Í´ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½Ê°ï¿½ ï¿½×³ï¿½ ï¿½Ç³Ê¶Ù±ï¿½ (ï¿½ï¿½ï¿½ï¿½ï¿½Í¸ï¿½ ï¿½Ìµï¿½)
      if(SD_Error_Chk(f_lseek(&fil, f_tell(&fil) + hdr.len), "f_lseek"))
      {
	    f_close(&fil);
	    return;
	  }
    }
  }

  SD_Error_Chk(f_close(&fil), "f_close");
}

/**
 * @brief  ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½Í¸ï¿½ ï¿½È¿ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ maxFilesï¿½ï¿½ ï¿½Ê°ï¿½ï¿½Ï¸ï¿½,
 *         ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½(=ï¿½ï¿½Â¥ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½Ì¸ï¿½) ï¿½ï¿½ï¿½ï¿½ 1ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½Ñ´ï¿½.
 *
 * @param  dirPath  ï¿½Ë»ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½Í¸ï¿½ ï¿½ï¿½ï¿?(ï¿½ï¿½: "TDAH")
 * @param  maxFiles ï¿½ï¿½ï¿½ï¿½ï¿?ï¿½Ö´ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ (ï¿½ï¿½: 62 ï¿½ï¿½ ï¿½ï¿½ ï¿½ï¿½Ä¡ ï¿½ï¿½ï¿½ï¿½)
 *
 * @note   ï¿½ï¿½ï¿½Ï¸ï¿½ï¿½ï¿½ "YYMMDD.txt" ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½×»ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½Ú¸ï¿½ï¿½ï¿½ï¿½ï¿½,
 *         ï¿½ï¿½ï¿½Ú¿ï¿½ ï¿½ï¿½(strcmp)ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½Â¥ ï¿½ï¿½ï¿½ï¿½ ï¿½ñ±³°ï¿½ ï¿½ï¿½È®ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½Ñ´ï¿½.
 */
void SD_CleanupOldFiles_Simple(const char* dirPath, uint16_t maxFiles)
{
  DIR dir;
  FILINFO fno;
  FRESULT res;                 // ï¿½ï¿½ ï¿½ß°ï¿½
  char oldestName[32] = "";
  uint16_t count = 0;

  if(SD_Error_Chk(f_opendir(&dir, dirPath), "f_opendir")) return;

  while((res = f_readdir(&dir, &fno)) == FR_OK && fno.fname[0] != 0)   // ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
  {
    if(fno.fattrib & AM_DIR) continue;

    count++;

    if(oldestName[0] == 0 || strcmp(fno.fname, oldestName) < 0)
      strcpy(oldestName, fno.fname);
  }
  if(res != FR_OK)
  {
    printf("f_readdir Error = %d (dir scan incomplete)\r\n", res);
  }

  SD_Error_Chk(f_closedir(&dir), "f_closedir");

  if(count > maxFiles && oldestName[0] != 0)
  {
    char fullPath[40];
    sprintf(fullPath, "%s/%s", dirPath, oldestName);

    if(SD_Error_Chk(f_unlink(fullPath), "f_unlink"))
    {
      return;
    }
    printf("Deleted: %s (count was %u)\r\n", fullPath, count);
  }
}

void SD_CleanupAll(void)
{
  SD_CleanupOldFiles_Simple("TDAH", 31);
}


void SD_Error_Save(uint8_t YY, uint8_t MM, uint8_t DD, uint8_t hh, uint8_t mm)
{
	uint32_t YYMMDD = YY*10000 + MM*100 + DD;
	uint16_t hhmm = hh*100 + mm;
	uint8_t timeStr[11] ={0,};

	sprintf(timeStr,"%08lu\r\n",HAL_GetTick());
	SD_Write_Record("ERROR_LOG",YYMMDD, hhmm, timeStr, 10);

}

uint32_t tt1,tt2;
uint8_t clrFlag;
void SD_Test()
{
	static uint32_t timeStamp;

	if(HAL_GetTick()-timeStamp >= 1000)
	{

		timeStamp = HAL_GetTick();
		tt1 = timeStamp;
		SD_Error_Save(26, 7, 31, 12, 19);
		printf("%08lu\r\n",timeStamp);
		tt2= HAL_GetTick() -tt1;
	}

}


// ==============================================================================
//  ï¿½ï¿½ï¿½â¼­ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½Úµå¸¦ ï¿½ï¿½ï¿½ï¿½ï¿?ï¿½Æ·ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½Ã¼ï¿½Ï¼ï¿½ï¿½ï¿½.
// ==============================================================================

//#define FLASH_APP_START_ADDRESS  0x08008000  // ï¿½ï¿½ï¿½ï¿½ Appï¿½ï¿½ ï¿½ï¿½ï¿½Ûµï¿½ ï¿½Ã·ï¿½ï¿½ï¿½ ï¿½Ö¼ï¿½
#define FLASH_APP_START_ADDRESS	 0x08010000

/* 1. ï¿½Ô¼ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½Ô¼ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Å¸ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ (ï¿½ï¿½ï¿½ï¿½ï¿½Ï·ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½Ä¡) */
typedef void (*pFunction)(void);
uint8_t Flash_Erase_AppArea(uint32_t StartAddr, uint32_t Length);
void JumpToApplication(uint32_t address);
void Bootloader_Process(void);

/**
  * @brief  STM32 ï¿½ï¿½ï¿½ï¿½ ï¿½Ã·ï¿½ï¿½ï¿½ï¿½ï¿½ Æ¯ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Ï´ï¿?(Erase)
  * @param  StartAddr: ï¿½ï¿½ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½Ö¼ï¿½
  * @param  Length: ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Æ® Å©ï¿½ï¿½
  * @retval 0: ï¿½ï¿½ï¿½ï¿½, 1: ï¿½ï¿½ï¿½ï¿½
  */
uint8_t Flash_Erase_AppArea(uint32_t StartAddr, uint32_t Length)
{
    uint32_t PageError = 0xFFFFFFFFU;
    FLASH_EraseInitTypeDef EraseInitStruct = {0};

    // STM32F103VET(High-density) ÆäÀÌÁö Å©±â = 2KB(2048 Byte)
    uint32_t PageSize = 2048;

    if (Length == 0U)                          return 1;
    if ((StartAddr - 0x08000000U) % PageSize)  return 1;   // ÆäÀÌÁö Á¤·Ä ÇÊ¼ö

    // fileSize ±âÁØ ÆäÀÌÁö ¼ö (¿Ã¸²). EndPage ¹æ½ÄÀº °æ°è¿¡¼­ 1ÆäÀÌÁö ´õ Áö¿öÁü
    uint32_t NbOfPages = (Length + PageSize - 1U) / PageSize;

    EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGES;
    EraseInitStruct.Banks       = FLASH_BANK_1;   // ¡Ú ´©¶ôµÅ ÀÖ´ø ÇÊµå
    EraseInitStruct.PageAddress = StartAddr;
    EraseInitStruct.NbPages     = NbOfPages;

    printf("Erase %lu pages from 0x%08lX\r\n", NbOfPages, StartAddr);

    // __disable_irq() ¾øÀ½ ? ³ÖÀ¸¸é SysTick°¡ ¸ØÃç HAL Å¸ÀÓ¾Æ¿ôÀÌ ¹«·ÂÈ­µÊ
    if (HAL_FLASHEx_Erase(&EraseInitStruct, &PageError) != HAL_OK)
    {
        printf("Erase FAIL: PageError=0x%08lX err=0x%08lX\r\n",
               PageError, HAL_FLASH_GetError());
        return 1;
    }

    printf("Erase OK\r\n");
    return 0;
}








/**
  * @brief  ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½Ö¼ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ Appï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½Ï°ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½Õ´Ï´ï¿½.
  */
void JumpToApplication(uint32_t address)
{
    // 1. App ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ Stack Pointerï¿½ï¿½ SRAM ï¿½ï¿½ï¿½ï¿½(0x20000000 ~) ï¿½ï¿½ï¿½ï¿½ ï¿½Ö´ï¿½ï¿½ï¿½ ï¿½ï¿½È¿ï¿½ï¿½ ï¿½Ë»ï¿½
    if (((*(__IO uint32_t*)address) & 0x2FFE0000) == 0x20000000)
    {
        // 2. ï¿½ï¿½ï¿½ï¿½ ï¿½Ö¼ï¿½ È¹ï¿½ï¿½ (Reset Handler)
        uint32_t JumpAddress = *(__IO uint32_t*)(address + 4);
        pFunction Jump = (pFunction)JumpAddress;

        // 3. ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½Ì´ï¿½ ï¿½ï¿½ï¿?ï¿½Öºï¿½ï¿½ï¿½Ä¡ ï¿½ï¿½ ï¿½ï¿½ï¿½Í·ï¿½Æ® ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½È°ï¿½ï¿½È­ (ï¿½Å¿ï¿½ ï¿½ß¿ï¿½)
        HAL_RCC_DeInit();
        HAL_DeInit();
        SysTick->CTRL = 0;
        SysTick->LOAD = 0;
        SysTick->VAL  = 0;

        // 4. MSP(Main Stack Pointer) ï¿½ç¼³ï¿½ï¿½ ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
        __set_MSP(*(__IO uint32_t*)address);
        Jump();
    }
    else
    {
        printf("No valid Application found at 0x%08lX\r\n", address);
    }
}

/**
  * @brief  ï¿½ï¿½Æ®ï¿½Î´ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½Î¼ï¿½ï¿½ï¿½ (mainï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ È£ï¿½ï¿½ ï¿½ï¿½ï¿?
  */
uint8_t writeBuffer[2408]; // 2KB ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
#define FLASH_APP_SIZE  (448U * 1024U)

void Bootloader_Process(void)
{
	// ¡é¡é¡é ÀÌ ºÎºĞ Ãß°¡ ¡é¡é¡é
//	printf(">>> Direct test start\r\n");
//	DSTATUS st = SD_disk_initialize(0);
//	printf(">>> Direct SD_disk_initialize result = 0x%02X\r\n", st);
	// ¡è¡è¡è ¿©±â±îÁö Ãß°¡ ¡è¡è¡è

    UINT bytesRead = 0;
    uint32_t currentFlashAddr = FLASH_APP_START_ADDRESS;

    printf("\r\n--- Bootloader StartQQQ ---\r\n");

    // 1. SD Ä«ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Æ® ï¿½ï¿½ï¿½ï¿½
	int failSd = f_mount(&fs, "", 1);
	printf("failSd = %d \r\n",failSd);
    if (failSd != FR_OK)
    {
        printf("SD Card not found. Jumping to App...\r\n");
        JumpToApplication(FLASH_APP_START_ADDRESS);
        return;
    }

    // 2. SD Ä«ï¿½ï¿½ ï¿½Ö»ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ "update.bin" ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½Ï´ï¿½ï¿½ï¿½ ï¿½Ë»ï¿½
    if (f_open(&fil, "update.bin", FA_READ) == FR_OK)
    {
        uint32_t fileSize = f_size(&fil);
        printf("Found 'update.bin' (%lu bytes)!\r\n", fileSize);
        printf("Flashing starting... DO NOT power off!\r\n");

        // Flash ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
        HAL_FLASH_Unlock();

        // 3. ï¿½ï¿½ï¿½ï¿½ Appï¿½ï¿½ ï¿½ï¿½î°?ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ Flash ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ (Erase)
        printf("Erasing Flash Memory...\r\n");
//        if (Flash_Erase_AppArea(FLASH_APP_START_ADDRESS, fileSize) != 0)
        if (Flash_Erase_AppArea(FLASH_APP_START_ADDRESS, FLASH_APP_SIZE) != 0)
        {
            printf("Flash Erase Failed!\r\n");
            HAL_FLASH_Lock();
            f_close(&fil);
            return;
        }
//		testFuc();

        // 4. ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½Ğ¾ï¿½ ï¿½ï¿½ï¿½ï¿½ Flashï¿½ï¿½ ï¿½ï¿½ï¿?(Write)
        printf("Writing new firmware...qqqq\r\n");
        while (1)
        {
            memset(writeBuffer, 0xFF, sizeof(writeBuffer)); // ï¿½ï¿½ï¿½ï¿½ ï¿½Ê±ï¿½È­
			printf("Reading from SD...\r\n");
            f_read(&fil, writeBuffer, sizeof(writeBuffer), &bytesRead);
            if (bytesRead == 0) break; // ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½Ï¸ï¿½ ï¿½ï¿½ï¿½ï¿½ Å»ï¿½ï¿½
			printf("Read done: %u bytes\r\n", bytesRead);

            // 16ï¿½ï¿½Æ®(Half-Word) ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½É°ï¿½ï¿½ï¿½ Flashï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿?
			uint32_t alignedLen = (bytesRead + 1U) & ~1U;	// È¦¼ö¸é Â¦¼ö·Î ¿Ã¸²

			for (uint32_t i = 0; i < alignedLen; i += 2)
			{
				uint16_t data = writeBuffer[i] | (writeBuffer[i+1] << 8);
				if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, currentFlashAddr + i, data) != HAL_OK)
				{
					printf("Flash Write Error at 0x%08lX!\r\n", currentFlashAddr + i);
					HAL_FLASH_Lock();
					f_close(&fil);
					return;
				}
			}
			currentFlashAddr += alignedLen;   // bytesRead ¡æ alignedLen

            printf("#"); // ï¿½ï¿½ï¿½ï¿½ Ç¥ï¿½Ã¿ï¿½ ï¿½Ø½Ã¸ï¿½Å© ï¿½ï¿½ï¿?
        }

        printf("\r\nWriting Success!\r\n");
        HAL_FLASH_Lock();
        f_close(&fil);

        // 5. ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Æ® ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
        printf("Removing 'update.bin' from SD card...\r\n");
        f_unlink("update.bin");

        printf("Update Complete!\r\n");
    }
    else
    {
        printf("No update file ('update.bin') found.\r\n");
    }

    // 6. SD Ä«ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Æ® ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ Appï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
    f_mount(NULL, "", 0);
    printf("Jumping to Application...\r\n\r\n");

    // ï¿½ï¿½Æ®ï¿½Î´ï¿½ ï¿½Î±ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿?ï¿½Í¹Ì³Î¿ï¿½ ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ ï¿½Öµï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿?ï¿½ï¿½ï¿?
    HAL_Delay(100);

    JumpToApplication(FLASH_APP_START_ADDRESS);
}

extern UART_HandleTypeDef huart3;

void B_Boot_Get_Test(void)
{
    uint8_t txData[2] = {0x00, 0xFF};
    uint8_t ack;
    uint8_t finalAck;
    uint8_t N;
    uint8_t rxData[32] = {0,};
    HAL_StatusTypeDef status;

    // GET Command
    HAL_UART_Transmit(&huart3, txData, 2, 1000);

    // ACK
    status = HAL_UART_Receive(&huart3, &ack, 1, 1000);

    if (status != HAL_OK)
    {
        printf("GET : ACK Timeout\r\n");
        return;
    }

    if (ack != 0x79)
    {
        printf("GET : ACK Fail 0x%02X\r\n", ack);
        return;
    }

    // ï¿½ß¿ï¿½: ï¿½ï¿½ï¿½â¼­ printf ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½

    // N
    status = HAL_UART_Receive(&huart3, &N, 1, 1000);

    if (status != HAL_OK)
    {
        printf("GET : N Timeout\r\n");
        return;
    }

    // ï¿½ß¿ï¿½: ï¿½ï¿½ï¿½â¼­ï¿½ï¿½ printf ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½

    if ((N + 1) > sizeof(rxData))
    {
        printf("GET : Response Too Long\r\n");
        return;
    }

    // Version + Supported Commands
    status = HAL_UART_Receive(&huart3, rxData, N + 1, 1000);

    if (status != HAL_OK)
    {
        printf("GET : Data Timeout\r\n");
        return;
    }

    // Final ACK
    status = HAL_UART_Receive(&huart3, &finalAck, 1, 1000);

    if (status != HAL_OK)
    {
        printf("GET : Final ACK Timeout\r\n");
        return;
    }


    // ============================================
    // ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿?
    // ============================================

    printf("GET ACK : 0x%02X\r\n", ack);
    printf("GET N : %d\r\n", N);
    printf("Bootloader Version : 0x%02X\r\n", rxData[0]);

    printf("Supported Commands : ");

    for (int i = 1; i < (N + 1); i++)
    {
        printf("0x%02X ", rxData[i]);
    }

    printf("\r\n");

    printf("GET Final ACK : 0x%02X\r\n", finalAck);

    if (finalAck == 0x79)
    {
        printf("GET TEST SUCCESS\r\n");
    }
    else
    {
        printf("GET TEST FAIL\r\n");
    }
}
void B_Boot_Get_ID_Test(void)
{
    uint8_t txData[2] = {0x02, 0xFD};
    uint8_t ack = 0;
    uint8_t finalAck = 0;
    uint8_t N = 0;
    uint8_t idData[8] = {0,};
    HAL_StatusTypeDef status;

    // 1. GET ID Command ï¿½ï¿½ï¿½ï¿½
    HAL_UART_Transmit(&huart3, txData, 2, 1000);

    // 2. ACK ï¿½ï¿½ï¿½ï¿½
    status = HAL_UART_Receive(&huart3, &ack, 1, 1000);

    if (status != HAL_OK)
    {
        printf("GET ID : ACK Timeout\r\n");
        return;
    }

    if (ack != 0x79)
    {
        printf("GET ID : ACK Fail 0x%02X\r\n", ack);
        return;
    }

    // ï¿½ï¿½ï¿½ï¿½:
    // ï¿½ï¿½ï¿½â¼­ printf ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
    // Bï¿½ï¿½ï¿½å°¡ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½Í¸ï¿½ ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½ï¿½Ï°ï¿½ ï¿½ï¿½ï¿½ï¿½


    // 3. N ï¿½ï¿½ï¿½ï¿½
    status = HAL_UART_Receive(&huart3, &N, 1, 1000);

    if (status != HAL_OK)
    {
        printf("GET ID : N Timeout\r\n");
        return;
    }

    if ((N + 1) > sizeof(idData))
    {
        printf("GET ID : Response Too Long\r\n");
        return;
    }


    // 4. Product ID ï¿½ï¿½ï¿½ï¿½
    // N = ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Æ® ï¿½ï¿½ - 1
    // ï¿½ï¿½ï¿½ï¿½ N + 1 ï¿½ï¿½ï¿½ï¿½Æ® ï¿½ï¿½ï¿½ï¿½
    status = HAL_UART_Receive(&huart3, idData, N + 1, 1000);

    if (status != HAL_OK)
    {
        printf("GET ID : Data Timeout\r\n");
        return;
    }


    // 5. ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ACK ï¿½ï¿½ï¿½ï¿½
    status = HAL_UART_Receive(&huart3, &finalAck, 1, 1000);

    if (status != HAL_OK)
    {
        printf("GET ID : Final ACK Timeout\r\n");
        return;
    }


    // =====================================
    // ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿?ï¿½ï¿½ï¿?
    // ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½Ï·ï¿½ ï¿½ï¿½ printf
    // =====================================

    printf("GET ID ACK : 0x%02X\r\n", ack);
    printf("GET ID N : %d\r\n", N);

    printf("Product ID : ");

    for (int i = 0; i < (N + 1); i++)
    {
        printf("0x%02X ", idData[i]);
    }

    printf("\r\n");

    // ï¿½Ï¹ï¿½ STM32 Product ID = 2 Byte
    if (N == 1)
    {
        uint16_t productID;

        productID = ((uint16_t)idData[0] << 8) | idData[1];

        printf("Product ID = 0x%04X\r\n", productID);
    }

    printf("GET ID Final ACK : 0x%02X\r\n", finalAck);

    if (finalAck == 0x79)
    {
        printf("GET ID TEST SUCCESS\r\n");
    }
    else
    {
        printf("GET ID TEST FAIL\r\n");
    }
}
uint8_t B_Boot_Mass_Erase(void)
{
    uint8_t cmd[2] = {0x43, 0xBC};
    uint8_t eraseData[2] = {0xFF, 0x00};
    uint8_t rx = 0;

    // =====================================
    // 1. Erase Command
    // 0x43 XOR 0xBC = 0xFF
    // =====================================

    if (HAL_UART_Transmit(&huart3, cmd, 2, 1000) != HAL_OK)
    {
        printf("ERASE : Command TX Fail\r\n");
        return 0;
    }

    if (HAL_UART_Receive(&huart3, &rx, 1, 1000) != HAL_OK)
    {
        printf("ERASE : Command ACK Timeout\r\n");
        return 0;
    }

    if (rx != 0x79)
    {
        printf("ERASE : Command NACK 0x%02X\r\n", rx);
        return 0;
    }


    // =====================================
    // 2. Global Mass Erase
    //
    // 0xFF : Global Erase
    // 0x00 : Checksum
    // =====================================

    if (HAL_UART_Transmit(&huart3, eraseData, 2, 1000) != HAL_OK)
    {
        printf("ERASE : Data TX Fail\r\n");
        return 0;
    }


    // =====================================
    // 3. Erase ï¿½Ï·ï¿½ ACK ï¿½ï¿½ï¿?
    //
    // ï¿½ï¿½ï¿½ï¿½ Flash Erase ï¿½Ã°ï¿½ï¿½ï¿½ ï¿½Ê¿ï¿½ï¿½Ï±ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
    // Timeoutï¿½ï¿½ ï¿½Ë³ï¿½ï¿½Ï°ï¿½ ï¿½ï¿½ï¿½ï¿½
    // =====================================

    if (HAL_UART_Receive(&huart3, &rx, 1, 10000) != HAL_OK)
    {
        printf("ERASE : Final ACK Timeout\r\n");
        return 0;
    }

    if (rx != 0x79)
    {
        printf("ERASE : Final NACK 0x%02X\r\n", rx);
        return 0;
    }


    printf("MASS ERASE SUCCESS\r\n");

    return 1;
}

uint8_t testData[16] =
{
    0x11, 0x22, 0x33, 0x44,
    0x55, 0x66, 0x77, 0x88,
    0xAA, 0xBB, 0xCC, 0xDD,
    0x12, 0x34, 0x56, 0x78
};
uint8_t readData[16] = {0,};

uint8_t B_Boot_Write_Memory(uint32_t address, uint8_t *data, uint16_t length)
{
    uint8_t cmd[2] = {0x31, 0xCE};
    uint8_t addrData[5];
    uint8_t txData[258];
    uint8_t rx = 0;
    uint8_t checksum;
    uint16_t i;


    // ==========================================
    // ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½Ë»ï¿½
    // 1 ~ 256 Byte
    // STM32 Bootloader Writeï¿½ï¿½ 4Byte ï¿½ï¿½ï¿?ï¿½ï¿½ï¿?
    // ==========================================

    if ((length == 0) || (length > 256))
    {
        printf("WRITE : Invalid Length %d\r\n", length);
        return 0;
    }

    if ((length % 4) != 0)
    {
        printf("WRITE : Length must be multiple of 4\r\n");
        return 0;
    }


    // ==========================================
    // 1. Write Memory Command
    //
    // 0x31 XOR 0xCE = 0xFF
    // ==========================================

    if (HAL_UART_Transmit(&huart3, cmd, 2, 1000) != HAL_OK)
    {
        printf("WRITE : Command TX Fail\r\n");
        return 0;
    }

    if (HAL_UART_Receive(&huart3, &rx, 1, 1000) != HAL_OK)
    {
        printf("WRITE : Command ACK Timeout\r\n");
        return 0;
    }

    if (rx != 0x79)
    {
        printf("WRITE : Command NACK 0x%02X\r\n", rx);
        return 0;
    }


    // ==========================================
    // 2. Flash Address ï¿½ï¿½ï¿½ï¿½
    //
    // ï¿½ï¿½:
    // 0x08000000
    //
    // 08 00 00 00 08
    //             ï¿½ï¿½
    //          Checksum
    // ==========================================

    addrData[0] = (address >> 24) & 0xFF;
    addrData[1] = (address >> 16) & 0xFF;
    addrData[2] = (address >> 8)  & 0xFF;
    addrData[3] = address & 0xFF;

    addrData[4] = addrData[0]
                ^ addrData[1]
                ^ addrData[2]
                ^ addrData[3];


    if (HAL_UART_Transmit(&huart3, addrData, 5, 1000) != HAL_OK)
    {
        printf("WRITE : Address TX Fail\r\n");
        return 0;
    }

    if (HAL_UART_Receive(&huart3, &rx, 1, 1000) != HAL_OK)
    {
        printf("WRITE : Address ACK Timeout\r\n");
        return 0;
    }

    if (rx != 0x79)
    {
        printf("WRITE : Address NACK 0x%02X\r\n", rx);
        return 0;
    }


    // ==========================================
    // 3. ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
    //
    // txData[0] = ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ - 1
    // txData[1...] = ï¿½ï¿½ï¿½ï¿½ Data
    // ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ = Checksum
    // ==========================================

    txData[0] = (uint8_t)(length - 1);

    checksum = txData[0];

    for (i = 0; i < length; i++)
    {
        txData[i + 1] = data[i];
        checksum ^= data[i];
    }

    txData[length + 1] = checksum;


    // ==========================================
    // 4. ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
    // ==========================================

    if (HAL_UART_Transmit(&huart3,
                          txData,
                          length + 2,
                          1000) != HAL_OK)
    {
        printf("WRITE : Data TX Fail\r\n");
        return 0;
    }


    // ==========================================
    // 5. Flash Write ï¿½Ï·ï¿½ ACK
    // ==========================================

    if (HAL_UART_Receive(&huart3, &rx, 1, 2000) != HAL_OK)
    {
        printf("WRITE : Final ACK Timeout\r\n");
        return 0;
    }

    if (rx != 0x79)
    {
        printf("WRITE : Final NACK 0x%02X\r\n", rx);
        return 0;
    }


    printf("WRITE SUCCESS : Addr=0x%08lX Len=%d\r\n",
           (unsigned long)address,
           length);

    return 1;
}

uint8_t B_Boot_Read_Memory(uint32_t address, uint8_t *data, uint16_t length)
{
    uint8_t cmd[2] = {0x11, 0xEE};
    uint8_t addrData[5];
    uint8_t lengthData[2];
    uint8_t rx = 0;


    // ==========================================
    // Length ï¿½Ë»ï¿½
    // ï¿½Ö´ï¿½ 256 Byte
    // ==========================================

    if ((length == 0) || (length > 256))
    {
        printf("READ : Invalid Length %d\r\n", length);
        return 0;
    }


    // ==========================================
    // 1. Read Memory Command
    //
    // 0x11 XOR 0xEE = 0xFF
    // ==========================================

    if (HAL_UART_Transmit(&huart3, cmd, 2, 1000) != HAL_OK)
    {
        printf("READ : Command TX Fail\r\n");
        return 0;
    }

    if (HAL_UART_Receive(&huart3, &rx, 1, 1000) != HAL_OK)
    {
        printf("READ : Command ACK Timeout\r\n");
        return 0;
    }

    if (rx != 0x79)
    {
        printf("READ : Command NACK 0x%02X\r\n", rx);
        return 0;
    }


    // ==========================================
    // 2. ï¿½ï¿½ï¿½ï¿½ Address ï¿½ï¿½ï¿½ï¿½
    //
    // ï¿½ï¿½: 0x08000000
    //
    // 08 00 00 00 08
    //             ï¿½ï¿½
    //           XOR
    // ==========================================

    addrData[0] = (address >> 24) & 0xFF;
    addrData[1] = (address >> 16) & 0xFF;
    addrData[2] = (address >> 8)  & 0xFF;
    addrData[3] = address & 0xFF;

    addrData[4] = addrData[0]
                ^ addrData[1]
                ^ addrData[2]
                ^ addrData[3];


    if (HAL_UART_Transmit(&huart3, addrData, 5, 1000) != HAL_OK)
    {
        printf("READ : Address TX Fail\r\n");
        return 0;
    }

    if (HAL_UART_Receive(&huart3, &rx, 1, 1000) != HAL_OK)
    {
        printf("READ : Address ACK Timeout\r\n");
        return 0;
    }

    if (rx != 0x79)
    {
        printf("READ : Address NACK 0x%02X\r\n", rx);
        return 0;
    }


    // ==========================================
    // 3. ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
    //
    // 16 Byteï¿½ï¿½ï¿?
    //
    // N = 16 - 1 = 0x0F
    //
    // 0x0F
    // 0xF0
    //
    // 0x0F XOR 0xF0 = 0xFF
    // ==========================================

    lengthData[0] = (uint8_t)(length - 1);
    lengthData[1] = lengthData[0] ^ 0xFF;


    if (HAL_UART_Transmit(&huart3, lengthData, 2, 1000) != HAL_OK)
    {
        printf("READ : Length TX Fail\r\n");
        return 0;
    }


    // ==========================================
    // 4. ACK ï¿½ï¿½ï¿½ï¿½
    // ==========================================

    if (HAL_UART_Receive(&huart3, &rx, 1, 1000) != HAL_OK)
    {
        printf("READ : Length ACK Timeout\r\n");
        return 0;
    }

    if (rx != 0x79)
    {
        printf("READ : Length NACK 0x%02X\r\n", rx);
        return 0;
    }


    // ==========================================
    // 5. ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
    //
    // ï¿½ï¿½ï¿½â¼­ printf ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
    // ==========================================

    if (HAL_UART_Receive(&huart3, data, length, 1000) != HAL_OK)
    {
        printf("READ : Data Timeout\r\n");
        return 0;
    }


    printf("READ SUCCESS : Addr=0x%08lX Len=%d\r\n",
           (unsigned long)address,
           length);

    return 1;
}

#define BOARD_B_FLASH_START     0x08000000U
#define BOARD_B_FLASH_SIZE      (256U * 1024U)
//#define BOARD_B_FW_FILE         "board_b.bin"
#define BOARD_B_FW_FILE         "TEST_F103RCT.bin"

//TEST_F103RCT

uint8_t BoardB_Update_From_SD(void)
{
    FRESULT res;
    UINT bytesRead;
    uint32_t fileSize;
    uint32_t address;
    uint32_t totalWritten = 0;
	DSTATUS sdStatus;

    uint8_t writeBuf[256];
    uint8_t readBuf[256];


    printf("\r\n");
    printf("==============================\r\n");
    printf("Board B Firmware Update Start\r\n");
    printf("==============================\r\n");


    // ==========================================
    // 1. SD Mount
    // ==========================================

    sdStatus = SD_disk_initialize(0);

    if (sdStatus & STA_NOINIT)
    {
        printf("SD Initialize FAIL : 0x%02X\r\n", sdStatus);
        return 0;
    }

    res = f_mount(&fs, "", 1);

    if (res != FR_OK)
    {
        printf("SD Mount FAIL : %d\r\n", res);
        return 0;
    }


    // ==========================================
    // 2. Bº¸µå BIN ÆÄÀÏ Open
    // ==========================================

    res = f_open(&fil, BOARD_B_FW_FILE, FA_READ);

    if (res != FR_OK)
    {
        printf("'%s' Open FAIL : %d\r\n",
               BOARD_B_FW_FILE,
               res);

        f_mount(NULL, "", 0);
        return 0;
    }


    // ==========================================
    // 3. BIN ÆÄÀÏ Å©±â È®ÀÎ
    // ==========================================

    fileSize = f_size(&fil);

    printf("Found '%s'\r\n", BOARD_B_FW_FILE);
    printf("File Size : %lu bytes\r\n", fileSize);


    if (fileSize == 0)
    {
        printf("Firmware File Empty\r\n");

        f_close(&fil);
        f_mount(NULL, "", 0);

        return 0;
    }


    if (fileSize > BOARD_B_FLASH_SIZE)
    {
        printf("Firmware Too Large\r\n");

        f_close(&fil);
        f_mount(NULL, "", 0);

        return 0;
    }


    // ==========================================
    // 4. Bº¸µå Flash ÀüÃ¼ Erase
    // ==========================================

    printf("Board B Flash Erase...\r\n");

    if (B_Boot_Mass_Erase() == 0)
    {
        printf("Board B Flash Erase FAIL\r\n");

        f_close(&fil);
        f_mount(NULL, "", 0);

        return 0;
    }


    // ==========================================
    // 5. BIN ¡æ Bº¸µå Flash
    //
    // 256Byte ´ÜÀ§·Î ¹İº¹
    // ==========================================

    address = BOARD_B_FLASH_START;

    while (1)
    {
        uint16_t writeLength;


        // ¸¶Áö¸· ºí·Ï PaddingÀ» À§ÇØ ¸ÕÀú FF·Î ÃÊ±âÈ­
        memset(writeBuf, 0xFF, sizeof(writeBuf));


        // --------------------------------------
        // SD¿¡¼­ ÃÖ´ë 256 Byte ÀĞ±â
        // --------------------------------------

        res = f_read(&fil,
                     writeBuf,
                     sizeof(writeBuf),
                     &bytesRead);

        if (res != FR_OK)
        {
            printf("SD Read FAIL : %d\r\n", res);

            f_close(&fil);
            f_mount(NULL, "", 0);

            return 0;
        }


        // EOF
        if (bytesRead == 0)
        {
            break;
        }


        // --------------------------------------
        // Write Memory´Â 4Byte ¹è¼ö
        //
        // ex)
        // 253 ¡æ 256
        // 254 ¡æ 256
        // 255 ¡æ 256
        // 256 ¡æ 256
        // --------------------------------------

        writeLength = (bytesRead + 3U) & ~3U;


        // --------------------------------------
        // Bº¸µå Flash Write
        // --------------------------------------

        if (B_Boot_Write_Memory(address,
                                writeBuf,
                                writeLength) == 0)
        {
            printf("Firmware Write FAIL\r\n");
            printf("Address : 0x%08lX\r\n",
                   (unsigned long)address);

            f_close(&fil);
            f_mount(NULL, "", 0);

            return 0;
        }


        // ======================================
        // 6. ¹æ±İ ¾´ µ¥ÀÌÅÍ¸¦ ´Ù½Ã Read
        // ======================================

        if (B_Boot_Read_Memory(address,
                               readBuf,
                               writeLength) == 0)
        {
            printf("Firmware Verify Read FAIL\r\n");

            f_close(&fil);
            f_mount(NULL, "", 0);

            return 0;
        }


        // ======================================
        // 7. Write Data == Read Data ºñ±³
        // ======================================

        if (memcmp(writeBuf,
                   readBuf,
                   writeLength) != 0)
        {
            printf("Firmware VERIFY FAIL\r\n");
            printf("Address : 0x%08lX\r\n",
                   (unsigned long)address);

            f_close(&fil);
            f_mount(NULL, "", 0);

            return 0;
        }


        // --------------------------------------
        // ´ÙÀ½ Flash ÁÖ¼Ò
        // --------------------------------------

        address += writeLength;

        // ½ÇÁ¦ BIN Å©±â¸¸ °è»ê
        totalWritten += bytesRead;


        printf("Progress : %lu / %lu bytes\r\n",
               totalWritten,
               fileSize);
    }


    // ==========================================
    // 8. ÆÄÀÏ Close
    // ==========================================

    f_close(&fil);

    f_mount(NULL, "", 0);


    // ==========================================
    // 9. ÃÖÁ¾ Å©±â °Ë»ç
    // ==========================================

    if (totalWritten != fileSize)
    {
        printf("Firmware Size Mismatch\r\n");
        printf("File    : %lu\r\n", fileSize);
        printf("Written : %lu\r\n", totalWritten);

        return 0;
    }


    printf("==============================\r\n");
    printf("Board B Firmware Update SUCCESS\r\n");
    printf("Written : %lu bytes\r\n", totalWritten);
    printf("Verify  : SUCCESS\r\n");
    printf("==============================\r\n");


    return 1;
}

/* USER CODE END 4 */

