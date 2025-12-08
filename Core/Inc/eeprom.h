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

/*  			define end  			*/


/*  			enum start  			*/

/*  			enum end  				*/



/*  			stuct start  			*/

/*  			stuct end  				*/



/*  			function start  		*/

void eeprom_test(void);
void RTC_Init(void);
void RTC_Test(void);
void DS1308_GetTime(uint8_t *hour, uint8_t *min, uint8_t *sec);
//void DS1308_GetDay(uint8_t *dayOfWeek, uint8_t *DD, uint8_t *MM, , uint8_t *YY);


/*  			function end  			*/


/*  			extern start  			*/



/*  			extern end  			*/

#endif

