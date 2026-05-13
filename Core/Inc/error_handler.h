#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

/*  			include start  			*/
#include "common.h"
/*  			include end  			*/



/*  			define start  			*/

/*  			define end  			*/


/*  			enum start  			*/
typedef enum
{
	TEMP_MAX   = 40,
	TEMP_MIN = -10,
	TEMP_LOW_VALUE = -5,

	TEMP_OUT_MAX   = 290,
	TEMP_OUT_MIN = -100,


	COMU_MAX_CNT = 10,
	FLOW_ZERO = 0,
	FLOW_LOW_MAX = 40,
	FLOW_LOW_MIN = 2,

	BATTRY_LIMIT_MAX = 42,
	BATTRY_LIMIT_MIN = 10,
	BATTRY_NOMAL_MAX = 38,
	BATTRY_NOMAL_MIN = 13,

	CATRIDGE_REMAIN_LOW_30 = 3000,
	CATRIDGE_REMAIN_LOW_20 = 2000,
	CATRIDGE_REMAIN_LOW_5 = 500,
	CATRIDGE_REMAIN_LOW_3 = 300,

	CATRIDGE_REMAIN_MIN = 1,
	CATRIDGE_REMAIN_MAX = 10001,


	CATRIDGE_WATT_MAX = 400,
	CATRIDGE_WATT_MIN = 0,
	CATRIDGE_FRQ_MAX = 13000,
	CATRIDGE_FRQ_MIN = 9000,

	CATRIDGE_ID_MAX = 100,

	YY_MAX = 70,
	YY_MIN = 25,
	MM_MAX = 12,
	MM_MIN = 1,
	DD_MAX = 31,
	DD_MIN = 1,

	HOUR_MAX = 24,
	HOUR_MIN = 1,
	MIN_MAX = 60,
	MIN_MIN = 0,
	SEC_MAX = 60,
	SEC_MIN = 0,

	DAY_MAX = 30,

	WATER_LEVEL_HIGH = 0,
	WATER_LEVEL_LOW = 1,

	PRECOOL_TIMEOUT = 2000,

	LEVEL_UNIT = 1000,
	ERR_ENDIS_UNIT = 100,
	ERR_ENABLE = 100,
	ERR_DISABLE = 0,
	ERR_DATA_UNIT = 0,


	ERR_NOT_EXIST = 0,
	ERR_EXIST = 1,

	OK_MAIN = 1,
	OK_HP = 2,
	OK_RF = 3,

	NONE_OK_ADDR = 20,
	NONE_OK_MAIN = 21,
	NONE_OK_HP = 22,
	NONE_OK_RF = 23,

	ERR_CHK_MAIN = 11,
	ERR_CHK_HP = 12,
	ERR_CHK_RF = 13,
} ERROR_DATA_E;


typedef enum
{
	IDX_MAIN_EVENT_START = 1,
	IDX_TEMP_OUT = IDX_MAIN_EVENT_START,
	IDX_TEMP_LIMIT_UNDER =2,//
	IDX_TEMP_LOW =3,//
	IDX_FLOW_LIMIT_UNDER =4,//
	IDX_LEVEL_LOW =5,//
	IDX_AUTO_CAL_COMU_ERR =6,//
	IDX_BATTRY_LIMIT_OVER =7,//
	IDX_BATTRY_LIMIT_UNDER =8,//
	IDX_BATTRY_LIMIT_LOW =9,//
	IDX_RTC_ERR =10,
	IDX_MAIN_EVENT_END =11,//~~~~~
  //------------------------------
	IDX_HP_EVENT_START =12,//
	IDX_PRE_COOL_ERR = IDX_HP_EVENT_START,//
	IDX_HAND_COMU_ERR =13,//
	IDX_CATRIGE_I2C_ERR  =14,//
	IDX_CATRIGE_NEW_DETECT= 15,//
	IDX_CATRIGE_ID_ERR =16,//
	IDX_CATRIGE_MANU_ERR =17,//
	IDX_CATRIGE_MANU_OVER_ERR =18,//
	IDX_CATRIGE_ISUE_ERR =19,//
	IDX_CATRIGE_ISUE_OVER_ERR =20,//
	IDX_CATRIGE_WATT_ERR =21,//
	IDX_CATRIGE_FRQ_ERR =22,//
	IDX_CATRIGE_RESHOT_ERR =23,//
	IDX_CATRIGE_RESHOT_LOW =24,//
	IDX_CATRIGE_RESHOT_ZERO =25,//
	IDX_CATRIGE_DETECT =26,
	IDX_CATRIGE_UN_DETECT =27,//
	IDX_HP_EVENT_END =28,//~~~~~
  //------------------------------
	IDX_RF_EVENT_START =29,
	IDX_RF_COMU_ERR = IDX_RF_EVENT_START,
	IDX_RF_STATUS_ERR =30,//
	IDX_RF_EVENT_END =31,//~~~~~

//------------------------------

  IDX_LCD_COMU_ERR,
  IDX_LCD_TIMEOUT,
  IDX_IS_CURRNTSHOT_RESET,
  IDX_IS_TOTALJULE_RESET,
  IDX_CATRIGE_NEW,
  IDX_ERROR_MAX,


} ERROR_IDX_E;

/*  			enum end  				*/



/*  			stuct start  			*/
typedef struct
{
	uint8_t rfComuErr;
	uint8_t rfTimeout;
	uint8_t rfStatus;
	uint8_t rfStatusErr;

	uint8_t handComuErr;
	uint8_t handTimeout;

	uint8_t flowLimitUnder;
	uint8_t flowZero;

	uint8_t autoCalComuErr;
	uint8_t autoCalStatus;
	uint8_t preCoolStatus;

	uint8_t errCntBuff[50];
	uint8_t errStandBuff[50];
	uint8_t errDataBuff[50];
	uint8_t errCheckBuff[50];
	uint16_t errStatus[4];
	uint8_t statusTx;
	uint8_t txEn;

} ERROR_T;

/*  			stuct end  				*/



/*  			function start  		*/
void Error_Check_Main();
void Error_Check_HP();
void Error_Check_RF();


/*  			function end  			*/


/*  			extern start  			*/

extern ERROR_T m_err;


/*  			extern end  			*/

#endif
