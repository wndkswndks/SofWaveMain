#ifndef HIFU_CTRL_H
#define HIFU_CTRL_H

/*  			include start  			*/
#include "common.h"
/*  			include end  			*/



/*  			define start  			*/
#define GEN_STATUS_CHECK          'A' //1  // 제너레이터 상태 체크
#define GEN_GET_VERSION            'B' //1  // 제너레이터 버전
#define GEN_FREQ_SET                   'C' //3  // 제너레이터 주파수 설정
#define GEN_OUTPUT_SET              'D' //3  // 제너레이터 출력 설정
#define GEN_MAX_ON_TIME_SET     'E' //2  // 최대 On time 설정
#define GEN_RF_VOLTAGE_REQ        'F' //1  // RF 출력 전압 요청
#define ALL_CH_FREQ_SET               'G' //16  // 전 채널 주파수 설정
#define ALL_CH_OUTPUT_SET          'H' //16  // 전 채널 출력 설정
#define ALL_CH_FREQ_REQ              'I' //1  // 전 채널 주파수 요청
#define ALL_CH_OUTPUT_REQ         'J' //1  // 전 채널 출력 요청
#define OUTPUT_VOLTAGE_ERR_CHK   'K' //1  // 출력 전압 에러 확인
#define OUTPUT_VOLTAGE_LIMIT_SET  'L' //4  // 출력 전압 한도 설정
#define OUTPUT_MODE_SET                'M' //1  // 출력 모드 설정

#define GEN_STATUS_CHECK_R          'a' //2  // 제너레이터 상태 체크
#define GEN_GET_VERSION_R            'b' //3  // 제너레이터 버전
#define GEN_FREQ_SET_R                   'c' //1  // 제너레이터 주파수 설정
#define GEN_OUTPUT_SET_R              'd' //1  // 제너레이터 출력 설정
#define GEN_MAX_ON_TIME_SET_R     'e' //1 // 최대 On time 설정
#define GEN_RF_VOLTAGE_REQ_R        'f' //16  // RF 출력 전압 요청
#define ALL_CH_FREQ_SET_R               'g' //1  // 전 채널 주파수 설정
#define ALL_CH_OUTPUT_SET_R          'h' //1  // 전 채널 출력 설정
#define ALL_CH_FREQ_REQ_R              'i' //16  // 전 채널 주파수 요청
#define ALL_CH_OUTPUT_REQ_R         'j' //16  // 전 채널 출력 요청
#define OUTPUT_VOLTAGE_ERR_CHK_R   'k' //2  // 출력 전압 에러 확인
#define OUTPUT_VOLTAGE_LIMIT_SET_R  'l' //4  // 출력 전압 한도 설정
#define OUTPUT_MODE_SET_R                'm' //1  // 출력 모드 설정


#define STX	0x02
#define ETX	0x03





/*  			define end  			*/


/*  			enum start  			*/
typedef enum
{
	RF_INDEX_STX = 0,
	RF_INDEX_LEN  = 1,
	RF_INDEX_ADDR = 2,
	RF_INDEX_CMD = 3,
	RF_INDEX_DATA = 4,

	RF_INDEX_HEAD_FIX = 4,
	RF_NUM_FIX = 6,

	PWM_H1_LEVEL = 0,
	PWM_L1_LEVEL = 1,
	PWM_H2_LEVEL = 2,
	PWM_L2_LEVEL = 3,
	PWM_H3_LEVEL = 4,
	PWM_L3_LEVEL = 5,
	PWM_H4_LEVEL = 6,
	PWM_COOL_LEVEL = 7,


	PWM_H_LEVEL = 0,
	PWM_L_LEVEL = 1,
	PWM_POST_LEVEL = 2,


	RF_FRQ_CH0 = 0,
	RF_FRQ_CH1 = 1,
	RF_FRQ_CH2 = 2,
	RF_FRQ_CH3 = 3,
	RF_FRQ_CH4 = 4,
	RF_FRQ_CH5 = 5,
	RF_FRQ_CH6 = 6,

	RF_WATT_CH0 = 0,
	RF_WATT_CH1 = 1,
	RF_WATT_CH2 = 2,
	RF_WATT_CH3 = 3,
	RF_WATT_CH4 = 4,
	RF_WATT_CH5 = 5,
	RF_WATT_CH6 = 6,

	CART_IDX_DUMY = 0,
	CART_IDX_CART_ID,
	CART_IDX_MANUFAC_YY,
	CART_IDX_MANUFAC_MM,
	CART_IDX_MANUFAC_DD,
	CART_IDX_ISSUED_YY,
	CART_IDX_ISSUED_MM,
	CART_IDX_ISSUED_DD,
	CART_IDX_TRANDU1_FRQ,
	CART_IDX_TRANDU2_FRQ,
	CART_IDX_TRANDU3_FRQ,
	CART_IDX_TRANDU4_FRQ,
	CART_IDX_TRANDU5_FRQ,
	CART_IDX_TRANDU6_FRQ,
	CART_IDX_TRANDU7_FRQ,
	CART_IDX_REMIND_SHOT,
	CART_IDX_STATUS,
	CART_IDX_RTC,


	MAX_ONTIME = 10000,
	MAX_ONTIME__22 = 10000,

	RF_RX_COMMON = 0,
	RF_RX_CALLBACK = 1,

	LIVE_ALL_DETH = 0,
	LIVE_HP = 10,
	LIVE_RF = 1,

	RTC_REG_YY = 0x06,
	RTC_REG_MM = 0x05,
	RTC_REG_DD = 0x04,
	RTC_REG_DoW = 0x03,

	RTC_REG_HOUR = 0x02,
	RTC_REG_MIN = 0x01,
	RTC_REG_SEC = 0x00,

	IDX_MAIN_P1_WATT = 1,
	IDX_MAIN_P1_DURATION_TIME ,
	IDX_MAIN_P1_INTERVAL_TIME ,
	IDX_MAIN_P2_WATT = 4,
	IDX_MAIN_P2_DURATION_TIME ,
	IDX_MAIN_P2_INTERVAL_TIME ,
	IDX_MAIN_P3_WATT = 7,
	IDX_MAIN_P3_DURATION_TIME ,
	IDX_MAIN_P3_INTERVAL_TIME ,
	IDX_MAIN_P4_WATT = 10,
	IDX_MAIN_P4_DURATION_TIME ,
	IDX_MAIN_POSTCO0L_TIME,

} RF_E;


//req : c51이 요구
//write : main이 송신
//LCD_TX : c51이 값송신








typedef enum
{
	CMD_HP1_COOL_MODE_CTRL = 1,
	CMD_HP1_COOL_MODE_OFF = 2,

	LCD_EXP_START = 1,
	LCD_EXP_END = 2,

	STATUS_STNBY = 0,
	STATUS_PRECOOLING = 1,
	STATUS_TRET = 2,


	SOF_HIGH = 1,
	SOF_LOW = 0,

	BUTTON_UP = 1,
	BUTTON_DN = 2,

	REQ_DATA = 0xffff,

	TIME_100MS = 100,

	MAX_ENERGY = 50,
	MAX_PULSE_DURATION = 50,
	MAX_POST_COOLING = 30,
	MAX_INTERVAL = 30,
	MAX_WATT_IDX = 11,

	READY_ON = 1,
	READY_OFF = 0,


	KEY_AUTO_CAL_1_2 = 1,
	KEY_AUTO_CAL_3_4_5 = 2,
	KEY_AUTO_CAL_6_7 = 3,
	KEY_AUTO_CAL_STOP = 4,
	KEY_AUTO_CAL_BACK = 5,

	AUTOCAL_START = 150,
	AUTOCAL_STOP = 160,
	AUTOCAL_DA_FAIL = 1,
	AUTOCAL_DA_PASS_CNT = 15,

	PULSE_DISABLE = 0,
	PULSE_ENABLE = 1,

} LCD_NUM_E;
/*  			enum end  				*/



/*  			stuct start  			*/
typedef struct
{
	char cmd;
	uint8_t txBuff[30];
	uint8_t fBuff[16];
	uint8_t rxBuff[30];
	uint8_t rxCnt;
	uint8_t rxBuffPassing[30];
	uint32_t lastTimeStamp;
	uint8_t rxCallBackCmd;
	uint8_t rxCallBackData[20];

	uint8_t expEndFlag;

	uint8_t pluseOn;
	uint8_t pluseLevel;
	uint32_t pluseTimeStamp;
	uint32_t pluseEgTimeStamp;

	uint8_t energy;
	uint32_t pulseDuration;
	uint32_t postCooling;
	uint32_t interval;
	uint32_t currentShot;
	uint16_t currentEnergy;
	uint16_t totaEnergy;
	uint8_t EnginerFlag;
	uint8_t egExpOn;
	uint8_t watt;
	uint32_t pluseEnginerHigh;
	uint8_t treatStatus;
	uint32_t preCooltime;
	uint8_t sysChkFlag;


	uint32_t rfFrqBuff[8];
	uint32_t rfwattBuff[8];
	uint8_t rfFrqFlag;
	uint8_t rfWattFlag;
	uint8_t rfFrqCh;
	uint8_t rfWattCh;
	uint8_t maxOntimeFlag;
	uint8_t readyFlag;
	uint8_t rfTxFlag;
	int FeedBackW;
	int FeedBackWBuff[30];
	uint8_t autoCalFlag;
	uint8_t autoCalStep;
	uint8_t autoCalNowDa;
	uint8_t autoCalReTryCnt;
	uint8_t autoCalAddr;
	uint8_t autoCalAddrEnd;
	uint8_t FeedBackCnt;
	uint32_t lastLcdTxTime;
	uint32_t lastRfGenTxTime;
	uint8_t liveChkCnt;
	uint8_t liveOk;
	uint8_t testPulseOption;
	uint8_t pulseNum;
	uint8_t pulseBuff[13];
	uint8_t pulseMaxBuff[13];
	uint8_t pulseMinBuff[13];
	uint8_t pulseNowWattNum;
	uint8_t pulseEndisBuff[5];
	uint8_t pulseEndisChkBuff[5];
	uint8_t pulsePreHigh;
} RF_T;
typedef struct
{
	uint16_t catridgeId;
	uint16_t manufacYY;
	uint16_t manufacMM;
	uint16_t manufacDD;
	uint32_t manufacDay;
	uint16_t issuedYY;
	uint16_t issuedMM;
	uint16_t issuedDD;
	uint32_t issuedDay;
	uint16_t rfFrqBuff[8];
	uint16_t rfWattBuff[78];
	uint16_t remainingShotNum;
	uint16_t catridgeStatus;
	uint16_t catridgeDetect;
	uint16_t catridgeDetectPre;
	uint8_t catridgeRxErrCnt;

} EEPROM_T;
typedef enum
{
	TEMP_MAX   = 40,
	TEMP_MIN = -10,
	TEMP_LOW_VALUE = -5,

	TEMP_OUT_MAX   = 200,
	TEMP_OUT_MIN = -100,


	COMU_MAX_CNT = 5,
	FLOW_ZERO = 0,
	FLOW_LOW_MAX = 5,
	FLOW_LOW_MIN = 1,

	BATTRY_LIMIT_MAX = 20,
	BATTRY_LIMIT_MIN = 1,
	BATTRY_NOMAL_MAX = 15,
	BATTRY_NOMAL_MIN = 5,

	CATRIDGE_REMAIN_LOW_30 = 3000,
	CATRIDGE_REMAIN_LOW_20 = 2000,
	CATRIDGE_REMAIN_LOW_5 = 500,
	CATRIDGE_REMAIN_LOW_3 = 300,

	CATRIDGE_REMAIN_MIN = 1,
	CATRIDGE_REMAIN_MAX = 10000,


	CATRIDGE_WATT_MAX = 300,
	CATRIDGE_WATT_MIN = 0,
	CATRIDGE_FRQ_MAX = 11000,
	CATRIDGE_FRQ_MIN = 13000,

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
	//MAIN
	EVENT_START_NUM = 1,
	ERR_FLOW_LIMIT_ZERO = 1,
	ERR_FLOW_LIMIT_UNDER,
	ERR_WATER_LEVEL_LIMIT_UNDER,
	ERR_RTC_BATTERY_LIMIT_OVER,
	ERR_RTC_BATTERY_LIMIT_UNDER,
	ERR_RTC_TIME,
	ERR_MAIN_COMMU,

	//RF
	ERR_RF_GENERATOR_COMMU,
	ERR_RF_GENERATOR_STATUS,

	//HP
	ERR_HP_COMMU,
	ERR_TRANSDUCER_TEMP,
	ERR_TRANSDUCER_TEMP_LIMIT_UNDER,
	ERR_COOLING_TIMEOUT,
	ERR_CARTRIDGE_MANUFAC,
	ERR_CARTRIDGE_ISSUED,
	ERR_CARTRIDGE_FRQ,
	ERR_CARTRIDGE_WATT_DA,
	ERR_CARTRIDGE_MAX_SHOT,
	ERR_CARTRIDGE_REMAINING_SHOT,
	ERR_CARTRIDGE_ID,
	ERR_CARTRIDGE_MANUFAC_OVER,
	ERR_CARTRIDGE_ISSUED_OVER,



	ALRAM_01,
	ALRAM_02,
	ALRAM_03,
	ALRAM_04,
	ALRAM_05,
	ALRAM_06,

	INFO_01,
	INFO_02,
	INFO_03,
	INFO_04,
	INFO_05,
	INFO_06,

	EVENT_MAX_NUM = INFO_06,

	EVENT_ICON_BASE = 50,// 임의의수

	LEVEL_ERROR = 1,
	LEVEL_ALRAM = 2,
	LEVEL_INFO = 3,

	CATRIGE_DETECT = 0,
	CATRIGE_UN_DETECT = 1,
} ERR_CMD_E;

typedef enum
{
  IDX_ERR_DUMY = 0,
  IDX_TEMP_OUT = 1,
  IDX_TEMP_LIMIT_UNDER = 2,
  IDX_TEMP_LOW = 3,
  IDX_FLOW_LIMIT_UNDER = 4,
  IDX_FLOW_ZERO_IDX = 5,
  IDX_LEVEL_LOW = 6,
  IDX_AUTO_CAL_COMU_ERR = 7,
  IDX_BATTRY_LIMIT_OVER = 8,
  IDX_BATTRY_LIMIT_UNDER = 9,
  IDX_BATTRY_LIMIT_LOW = 10,
  IDX_RTC_ERR = 11,//11
//------------------------------

  IDX_PRE_COOL_ERR = 12,//12
  IDX_HAND_COMU_ERR = 13,//13
  IDX_CATRIGE_ID_ERR = 14,
  IDX_CATRIGE_MANU_ERR = 15,
  IDX_CATRIGE_MANU_OVER_ERR = 16,
  IDX_CATRIGE_ISUE_ERR = 17,
  IDX_CATRIGE_ISUE_OVER_ERR = 18,
  IDX_CATRIGE_WATT_ERR = 19,
  IDX_CATRIGE_FRQ_ERR = 20,
  IDX_CATRIGE_RESHOT_ERR = 21,
  IDX_CATRIGE_RESHOT_LOW = 22,
  IDX_CATRIGE_RESHOT_ZERO = 23,
  IDX_CATRIGE_DETECT = 24,
  IDX_CATRIGE_UN_DETECT = 25,
//------------------------------

  IDX_RF_COMU_ERR = 26,
  IDX_RF_STATUS_ERR = 27,
//------------------------------

  IDX_HAND_TIMEOUT,
  IDX_LCD_COMU_ERR,
  IDX_LCD_TIMEOUT,
  IDX_ERROR_MAX,

} ERROR_IDX_E;

typedef struct
{
	uint8_t rfComuErr;
	uint8_t rfTimeout;
	uint8_t rfStatus;
	uint8_t rfStatusErr;

	uint8_t handComuErr;
	uint8_t handTimeout;

	uint8_t lcdComuErr;
	uint8_t lcdTimeout;

	uint8_t tempOut;
	uint8_t tempLimitUnder;
	uint8_t tempLow;

	uint8_t flowLimitUnder;
	uint8_t flowZero;

	uint8_t levelLow;

	uint8_t autoCalComuErr;
	uint8_t autoCalStatus;

	uint8_t preCoolErr;
	uint8_t preCoolStatus;

	uint8_t battryLimitOver;
	uint8_t battryLimitUnder;
	uint8_t battryLimitLow;

	uint8_t RtcErr;
	uint8_t catrigeIDErr;
	uint8_t catrigeManuErr;
	uint8_t catrigeManuOverErr;
	uint8_t catrigeIsueErr;
	uint8_t catrigeIsueOverErr;
	uint8_t catrigeWattErr;
	uint8_t catrigeFrqErr;
	uint8_t catrigeReShotErr;
	uint8_t catrigeReShotLow;
	uint8_t catrigeReShotZero;

	uint8_t errBuff[50];
	uint16_t errDataBuff[50];
	uint16_t errMemoryBuff[50];
	uint16_t errTraceBuff[50];
	uint8_t errBuffMsg[50][40];
	uint8_t errTraceCnt;
	uint16_t errChkCnt;
	uint16_t okChkCnt;
	uint16_t errStatus;

} ERROR_T;
typedef struct
{
	uint8_t mode;
	uint8_t pwmDuty;
	int temprature;
	int ioStatus;
	uint32_t lastRxTime;
	uint32_t dieFlag;
	uint32_t lastHPTxTime;
	uint8_t liveOk;
	uint8_t liveChkCnt;
	uint8_t cartEndFlag;
} HAND_T;


/*  			stuct end  				*/



/*  			function start  		*/
void Rf_Config();
void Rx_RF_Get(uint8_t getData);
void Rf_Init();
void RF_Pwm_Conter();
void RF_Eg_Exp_Conter();

void LCD_Rx_Parssing(uint8_t add, uint32_t data);
void Hand_Rx_Parssing(uint8_t add, uint32_t data, uint32_t data2, uint32_t data3, uint32_t data4);
void Debug_Rx_Parssing(uint8_t add, uint32_t data);
void RF_Rx_Parssing(uint8_t rxID);

void HP1_Tx_Msg(uint8_t add, uint16_t data);
void Hand_Init();
void Hand1_Poling_Ctrl(int add, int data1, int data2, int data3, int data4);
void TX_RF_Max_Ontime_Set();
void Tx_RF_GenStatus_Check();
void Error_Check_Config();
void LCD_Init();
void AutoCal_Avg();
void PulseData_Sand(uint8_t num, uint16_t data);
void PulseEn_Sand(uint8_t num, uint16_t enDis);
void CurrentEnergy_Cal();


/*  			function end  			*/


/*  			extern start  			*/
extern RF_T m_rf;
extern EEPROM_T m_eep;
extern ERROR_T m_err;
extern HAND_T m_hand1;

/*  			extern end  			*/

#endif
