/*
 * eeprom.h
 *
 *  Created on: Sep 11, 2025
 *      Author: Cellah_SW
 */
#ifndef EEPROM_H
#define EEPROM_H

/*  			include start  			*/
#include "common.h"
/*  			include end  			*/



/*  			define start  			*/
#define CAT24C16_BASE_7BIT   0x50U  // 0x50~0x57 (7-bit form)
#define CAT24C16_PAGE_BYTES  16U    // 페이지 크기(참고용)
#define CAT24C16_TOTAL_BYTES 2048U
#define CAT24C16_ADDRESS_ID   0x50U<<1
#define FLASHA_FIRST_FLAG   33

/*  			define end  			*/


/*  			enum start  			*/
typedef enum
{
	IDX_HP1_IS_FLASH_FIRST = 0,

	IDX_HP1_CART_ID1_START = 1,
	IDX_HP1_CART_ID1_END = 1,

	IDX_HP1_CART_ID2_START = 2,
	IDX_HP1_CART_ID2_END = 2,

	IDX_HP1_CART_ID3_START = 3,
	IDX_HP1_CART_ID3_END = 3,

	IDX_HP1_CART_ID4_START = 4,
	IDX_HP1_CART_ID4_END = 4,

	IDX_HP1_CART_ID5_START = 5,
	IDX_HP1_CART_ID5_END = 5,

	IDX_HP1_CART_ID6_START = 6,
	IDX_HP1_CART_ID6_END = 6,

	IDX_HP1_CART_ID7_START = 7,
	IDX_HP1_CART_ID7_END = 7,

	IDX_HP1_CART_ID8_START = 8,
	IDX_HP1_CART_ID8_END = 8,

	MAX_EEPROM_SIZE = 200,
} EEPROM_E;

/*  			enum end  				*/



/*  			stuct start  			*/
typedef struct
{
	uint8_t flashFirst;
	uint8_t saveFlag;
	uint8_t buff[MAX_EEPROM_SIZE];
	uint8_t cartIdBuff[10];
} EEPROM_MAIN_T;

/*  			stuct end  				*/



/*  			function start  		*/

void eeprom_test(void);
void Eeprom_All_Read(void);

void RTC_Init(void);
void RTC_Test(void);
void DS1308_GetTime(uint8_t *hour, uint8_t *min, uint8_t *sec);
void DS1308_GetDay(uint8_t *dayOfWeek, uint8_t *DD, uint8_t *MM,  uint8_t *YY);
void DS1308_SetParts(uint8_t add, uint8_t data);
void Eeprom_Byte_Write(uint8_t Idx, uint8_t data);


/*  			function end  			*/


/*  			extern start  			*/

extern EEPROM_MAIN_T m_eepMain;


/*  			extern end  			*/

#endif

