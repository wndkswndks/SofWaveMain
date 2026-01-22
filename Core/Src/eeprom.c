/*
 * eeprom.c
 *
 *  Created on: Sep 11, 2025
 *      Author: Cellah_SW
 */
#include "eeprom.h"
EEPROM_MAIN_T m_eepMain;

static inline uint8_t CAT24C16_MemAddr8(uint16_t abs_addr)
{
    return (uint8_t)(abs_addr & 0xFF);          // ï¿½ï¿½ï¿?ï¿½ï¿½ 8ï¿½ï¿½Æ® ï¿½Ö¼ï¿½
}

static HAL_StatusTypeDef CAT24C16_WaitReady(I2C_HandleTypeDef *hi2c, uint16_t abs_addr, uint32_t timeout_ms)
{
    uint32_t tick_start = HAL_GetTick();
    uint16_t dev =CAT24C16_ADDRESS_ID;
    while ((HAL_GetTick() - tick_start) < timeout_ms)
    {
        if (HAL_I2C_IsDeviceReady(hi2c, dev, 1, 5) == HAL_OK)
            return HAL_OK;
    }
    return HAL_TIMEOUT;
}

HAL_StatusTypeDef CAT24C16_WriteByte(I2C_HandleTypeDef *hi2c, uint16_t abs_addr, uint8_t data)
{
    if (abs_addr >= CAT24C16_TOTAL_BYTES) return HAL_ERROR;

    uint16_t dev  = CAT24C16_ADDRESS_ID;
    uint8_t  maddr= CAT24C16_MemAddr8(abs_addr);

    HAL_StatusTypeDef st = HAL_I2C_Mem_Write(hi2c, dev, maddr, I2C_MEMADD_SIZE_8BIT, &data, 1, 100);
    if (st != HAL_OK) return st;

    // ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½Ï·ï¿½ ï¿½ï¿½ï¿?ACK ï¿½ï¿½ï¿½ï¿½)
    return CAT24C16_WaitReady(hi2c, abs_addr, 10 /*ms*/);
}

HAL_StatusTypeDef CAT24C16_ReadByte(I2C_HandleTypeDef *hi2c, uint16_t abs_addr, uint8_t *p_data)
{
    if (abs_addr >= CAT24C16_TOTAL_BYTES || p_data == NULL) return HAL_ERROR;

    uint16_t dev  = CAT24C16_ADDRESS_ID;
    uint8_t  maddr= CAT24C16_MemAddr8(abs_addr);

    return HAL_I2C_Mem_Read(hi2c, dev, maddr, I2C_MEMADD_SIZE_8BIT, p_data, 1, 100);
}



uint8_t bufQQ[255] = {0};
void Eeprom_All_Read(void)
{

    for (uint16_t i = 0; i < 200; ++i)
    {
        if (CAT24C16_ReadByte(&hi2c1, i, &m_eepMain.buff[i]) != HAL_OK)
        {
            //¿¡·¯Ã³¸®
            return;
        }
    }
	if(m_eepMain.buff[IDX_HP1_IS_FLASH_FIRST] != FLASHA_FIRST_FLAG)
	{
		m_eepMain.flashFirst = FLASHA_FIRST_FLAG;

		m_eepMain.buff[IDX_HP1_IS_FLASH_FIRST] = m_eepMain.flashFirst;
		for(int i =0 ;i < 10;i++)
		{
			m_eepMain.cartIdBuff[i] = 0;
			m_eepMain.buff[i+1] = 0;
		}

		for(int i =0 ;i < 50;i++)
		{
			m_eepMain.errCntBuff[i] = 0;
			m_eepMain.buff[IDX_EEP_ERROR+i*2] = 0;
			m_eepMain.buff[IDX_EEP_ERROR+i*2+1] = 0;
		}

		for (uint16_t i = 0; i < 200; ++i)
	    {
	        if (CAT24C16_WriteByte(&hi2c1, i, m_eepMain.buff[i]) != HAL_OK)
	        {
	            // ¿¡·¯ Ã³¸®
	            return;
	        }
	    }
	}
	else
	{
		for(int i =0 ;i < 10;i++)
		{
			m_eepMain.cartIdBuff[i] = m_eepMain.buff[i+IDX_HP1_CART_ID1_START];
		}

		for(int i =0 ;i < 50;i++)
		{
			m_eepMain.errCntBuff[i] = (m_eepMain.buff[IDX_EEP_ERROR+i*2]<<8)|(m_eepMain.buff[IDX_EEP_ERROR+i*2+1]);
		}
	}


}



void Eeprom_Byte_Write(uint8_t Idx, uint8_t data)
{
	if(Idx >= MAX_EEPROM_SIZE) return;
	m_eepMain.buff[Idx] = (uint8_t)data;
	CAT24C16_WriteByte(&hi2c1, Idx, data);
}

void Eeprom_Word_Write(uint8_t startIdx, uint16_t data)
{
	uint8_t lsb,msb;
	if(startIdx >= MAX_EEPROM_SIZE-1) return;

	msb = (data>>8)&0xff;
	lsb = (data)&0xff;
	m_eepMain.buff[startIdx] = msb;
	m_eepMain.buff[startIdx+1] = lsb;
	CAT24C16_WriteByte(&hi2c1, startIdx, msb);
	CAT24C16_WriteByte(&hi2c1, startIdx+1, lsb);
}



#define DS1308_ADDR    (0x68 << 1)

extern I2C_HandleTypeDef hi2c1;  // I2C1 ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½

uint8_t DS1308_Read(uint8_t reg) {
    uint8_t data;
    HAL_I2C_Mem_Read(&hi2c1, DS1308_ADDR, reg, I2C_MEMADD_SIZE_8BIT, &data, 1, 100);
    return data;
}

void DS1308_Write(uint8_t reg, uint8_t data) {
    HAL_I2C_Mem_Write(&hi2c1, DS1308_ADDR, reg, I2C_MEMADD_SIZE_8BIT, &data, 1, 100);
}

// BCD <-> DEC ï¿½ï¿½È¯ ï¿½Ô¼ï¿½ (DS1308ï¿½ï¿½ BCD ï¿½ï¿½ï¿½ï¿½)
uint8_t BCD2DEC(uint8_t bcd) {
    return ((bcd >> 4) * 10) + (bcd & 0x0F);
}

uint8_t DEC2BCD(uint8_t dec) {
    return ((dec / 10) << 4) | (dec % 10);
}

// ï¿½Ã°ï¿½ ï¿½Ð±ï¿½ ï¿½ï¿½ï¿½ï¿½ (0x00: ï¿½ï¿½, 0x01: ï¿½ï¿½, 0x02: ï¿½ï¿½)
void DS1308_GetTime(uint8_t *hour, uint8_t *min, uint8_t *sec)
{
    *sec = BCD2DEC(DS1308_Read(0x00));
    *min = BCD2DEC(DS1308_Read(0x01));
    *hour = BCD2DEC(DS1308_Read(0x02));
}


void DS1308_GetDay(uint8_t *dayOfWeek, uint8_t *DD, uint8_t *MM,  uint8_t *YY)
{
    *dayOfWeek = BCD2DEC(DS1308_Read(0x03));
    *DD = BCD2DEC(DS1308_Read(0x04));
    *MM = BCD2DEC(DS1308_Read(0x05));
    *YY = BCD2DEC(DS1308_Read(0x06));
}

// ï¿½Ã°ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
void DS1308_SetParts(uint8_t add, uint8_t data)
{
    DS1308_Write(add, DEC2BCD(data));
}


void DS1308_SetTime(uint8_t hour, uint8_t min, uint8_t sec) {
    DS1308_Write(0x00, DEC2BCD(sec));
    DS1308_Write(0x01, DEC2BCD(min));
    DS1308_Write(0x02, DEC2BCD(hour));
}
void DS1308_SetDay(uint8_t dayOfWeek, uint8_t DD, uint8_t MM , uint8_t YY)
{
    DS1308_Write(0x03, DEC2BCD(dayOfWeek));
    DS1308_Write(0x04, DEC2BCD(DD));
    DS1308_Write(0x05, DEC2BCD(MM));
    DS1308_Write(0x06, DEC2BCD(YY));
}

void RTC_Init(void)
{

	//2601220918 start
	//m_io.battery  : 2.06V
	// no charge

#if 0
		DS1308_SetTime(9, 18, 0);
		DS1308_SetDay(4,22,1,26);
		HAL_Delay(500); //
#endif
	BAT_CHG_ON_L();
}

uint8_t hour, min, sec;
void RTC_Test(void)///
{
	static uint32_t timeStamp;

	if(HAL_GetTick()-timeStamp >= 500)
	{

		timeStamp = HAL_GetTick();
		// RTCï¿½Îºï¿½ï¿½ï¿½ ï¿½Ã°ï¿½ ï¿½Ð±ï¿½
		DS1308_GetTime(&hour, &min, &sec);

		// ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ È®ï¿½Î¿ï¿½ (ï¿½ï¿½: UART ï¿½ï¿½ï¿?- ï¿½ï¿½ï¿½ï¿½ È¯ï¿½æ¿¡ ï¿½Â°ï¿½ ï¿½ï¿½Ã¼)
//		printf("RTC Time: %02d:%02d:%02d\r\n", hour, min, sec);
	}
}

