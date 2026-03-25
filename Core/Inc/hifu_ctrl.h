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


#define BHB0003_1W_1	174
#define BHB0003_1W_2	140
#define BHB0003_1W_3	170
#define BHB0003_1W_4	166
#define BHB0003_1W_5	152
#define BHB0003_1W_6	162
#define BHB0003_1W_7	160



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

	CART_EVENT_UNDETECT = 0,
	CART_EVENT_DETECT = 1,
	CART_EVENT_DETECT_NEW = 2,
	CART_EVENT_EXPRATION = 3,

	CATRIGE_CHK_OK = 0,
	CATRIGE_CHK_NEW = 1,
	CATRIGE_CHK_I2C_READ_ERR = 2,
	CATRIGE_CHK_I2C_WRITE_ERR = 3,
	CATRIGE_CHK_REMIND_ZERO_ERR = 4,
	CATRIGE_CHK_UN_DETECT = 5,



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
	TIME_1000MS = 1000,

	MAX_ENERGY = 50,
	MAX_PULSE_DURATION = 50,
	MAX_POST_COOLING = 30,
	MAX_INTERVAL = 3,
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

	SWITCH_HAND = 0,
	SWITCH_FOOT = 1,

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
	int FeedBackWBuff[70];
	uint8_t autoCalFlag;
	uint8_t autoCalStep;
	uint8_t autoCalWattLevel;
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
	uint8_t agingCnt;
	uint8_t agingUpDn;
	uint32_t trigTemeStamp[30];
	uint8_t trigCnt;
	uint8_t getWattBuff[10];
	uint8_t getWattCnt;
	uint8_t feedBackTest;
	uint16_t remainingShotNegative;
	uint8_t vibeLevel;
	uint8_t switchHandFoot;
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
	uint8_t catridgeRxErrCnt;
	uint8_t cartAllow;
} EEPROM_T;



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
	uint8_t tempDutyEn;
	uint8_t cartAllOk;
} HAND_T;


/*  			stuct end  				*/



/*  			function start  		*/
void Rf_Config();
void Rx_RF_Get(uint8_t getData);
void Rf_Init();
void RF_Eg_Exp_Conter();


void RF_Rx_Parssing(uint8_t rxID);

void HP1_Tx_Msg(uint8_t add, uint16_t data);
void Hand_Init();
void TX_RF_Max_Ontime_Set();
void Tx_RF_GenStatus_Check();
void Tx_RF_FeedBack_Check();

void Error_Check_Config();
void LCD_Init();
int AutoCal_Avg();
void PulseData_Sand(uint8_t num, uint16_t data);
void PulseEn_Sand(uint8_t num, uint16_t enDis);
void CurrentEnergy_Cal();
void Tx_RF_FRQ_ALL_Module();
void Test_Init();
void Tx_RF_Watt_Zero_ALL_Module();
void Tx_RF_Watt_Module(uint8_t ch, uint16_t watt);
void RF_eg_Exp_On(uint32_t expTime);
void Tx_RF_FRQ_Module(uint8_t ch, uint16_t frequency);
void CARTRIGE_REQ_DATA(uint8_t idx);
void Err_Init();
void Get_Err_StatusBitFlag();


/*  			function end  			*/


/*  			extern start  			*/
extern RF_T m_rf;
extern EEPROM_T m_eep;
extern HAND_T m_hand1;
extern uint8_t testExpFlag;

/*  			extern end  			*/

#endif
