/*
 * io_ctrl.h
 *
 *  Created on: Aug 25, 2025
 *      Author: Cellah_SW
 */

#ifndef IO_CTRL_H
#define IO_CTRL_H

/*  			include start  			*/
#include "common.h"
/*  			include end  			*/



/*  			define start  			*/
#define IS_LEVEL_SENSOR1_ON()      (HAL_GPIO_ReadPin(LEVEL_SENSOR1_GPIO_Port, LEVEL_SENSOR1_Pin) == 0) //low active
#define IS_LEVEL_SENSOR2_ON()      (HAL_GPIO_ReadPin(LEVEL_SENSOR2_GPIO_Port, LEVEL_SENSOR2_Pin) == 0) //low active
#define IS_FLOWSENSOR_OUT()        (HAL_GPIO_ReadPin(FLOWSENSOR_OUT_GPIO_Port, FLOWSENSOR_OUT_Pin) != 0) // GPIO_EXIT0
#define IS_AC_INPUT_STATE()        (HAL_GPIO_ReadPin(AC_INPUT_STATE_GPIO_Port, AC_INPUT_STATE_Pin) != 0)
#define IS_HP1_SHOT_PUSH()         (HAL_GPIO_ReadPin(HP1_SHOT_PUSH_GPIO_Port, HP1_SHOT_PUSH_Pin) == 0)
#define IS_HP1_INSERT()            (HAL_GPIO_ReadPin(HP1_INSERT_GPIO_Port, HP1_INSERT_Pin) == 0)
#define IS_HP2_SHOT_PUSH()         (HAL_GPIO_ReadPin(HP2_SHOT_PUSH_GPIO_Port, HP2_SHOT_PUSH_Pin) != 0)
#define IS_HP2_INSERT()            (HAL_GPIO_ReadPin(HP2_INSERT_GPIO_Port, HP2_INSERT_Pin) != 0)
#define IS_STATE_A_ON()            (HAL_GPIO_ReadPin(STATE_A_GPIO_Port, STATE_A_Pin) == 0)
#define IS_STATE_B_ON()            (HAL_GPIO_ReadPin(STATE_B_GPIO_Port, STATE_B_Pin) == 0)


#define HP1_RST_CONTROL_H()      HAL_GPIO_WritePin(HP1_RST_CONTROL_GPIO_Port, HP1_RST_CONTROL_Pin, GPIO_PIN_SET)
#define HP1_RST_CONTROL_L()       HAL_GPIO_WritePin(HP1_RST_CONTROL_GPIO_Port, HP1_RST_CONTROL_Pin, GPIO_PIN_RESET)

#define HP1_Boot_CONTROL_H()     HAL_GPIO_WritePin(HP1_Boot_CONTROL_GPIO_Port, HP1_Boot_CONTROL_Pin, GPIO_PIN_SET)
#define HP1_Boot_CONTROL_L()      HAL_GPIO_WritePin(HP1_Boot_CONTROL_GPIO_Port, HP1_Boot_CONTROL_Pin, GPIO_PIN_RESET)

#define HP2_Boot_CONTROL_H()     HAL_GPIO_WritePin(HP2_Boot_CONTROL_GPIO_Port, HP2_Boot_CONTROL_Pin, GPIO_PIN_SET)
#define HP2_Boot_CONTROL_L()      HAL_GPIO_WritePin(HP2_Boot_CONTROL_GPIO_Port, HP2_Boot_CONTROL_Pin, GPIO_PIN_RESET)

#define HP2_RST_CONTROL_H()      HAL_GPIO_WritePin(HP2_RST_CONTROL_GPIO_Port, HP2_RST_CONTROL_Pin, GPIO_PIN_SET)
#define HP2_RST_CONTROL_L()       HAL_GPIO_WritePin(HP2_RST_CONTROL_GPIO_Port, HP2_RST_CONTROL_Pin, GPIO_PIN_RESET)

#define HP1_PWR_EN_H()            HAL_GPIO_WritePin(HP1_PWR_EN_GPIO_Port, HP1_PWR_EN_Pin, GPIO_PIN_SET)
#define HP1_PWR_EN_L()             HAL_GPIO_WritePin(HP1_PWR_EN_GPIO_Port, HP1_PWR_EN_Pin, GPIO_PIN_RESET)

#define HP2_PWR_EN_H()            HAL_GPIO_WritePin(HP2_PWR_EN_GPIO_Port, HP2_PWR_EN_Pin, GPIO_PIN_SET)
#define HP2_PWR_EN_L()             HAL_GPIO_WritePin(HP2_PWR_EN_GPIO_Port, HP2_PWR_EN_Pin, GPIO_PIN_RESET)


#define CILLER_PWR_ON_GPIO_Port_H()        HAL_GPIO_WritePin(CILLER_PWR_ON_GPIO_Port, CILLER_PWR_ON_Pin, GPIO_PIN_SET)
#define CILLER_PWR_ON_GPIO_Port_L()         HAL_GPIO_WritePin(CILLER_PWR_ON_GPIO_Port, CILLER_PWR_ON_Pin, GPIO_PIN_RESET)

#define WATER_PUMP_PWR_EN_H()    HAL_GPIO_WritePin(WATER_PUMP_PWR_EN_GPIO_Port, WATER_PUMP_PWR_EN_Pin, GPIO_PIN_SET)
#define WATER_PUMP_PWR_EN_L()     HAL_GPIO_WritePin(WATER_PUMP_PWR_EN_GPIO_Port, WATER_PUMP_PWR_EN_Pin, GPIO_PIN_RESET)

#define BUFFER_ON_H()    				  HAL_GPIO_WritePin(BUFFER_ON_GPIO_Port, BUFFER_ON_Pin, GPIO_PIN_SET)
#define BUFFER_ON_L()     				  HAL_GPIO_WritePin(BUFFER_ON_GPIO_Port, BUFFER_ON_Pin, GPIO_PIN_RESET)

#define RF_Pulse_Signal_GPIO_Port_H()      HAL_GPIO_WritePin(RF_Pulse_Signal_GPIO_Port, RF_Pulse_Signal_Pin,GPIO_PIN_SET)
#define RF_Pulse_Signal_GPIO_Port_L()      HAL_GPIO_WritePin(RF_Pulse_Signal_GPIO_Port, RF_Pulse_Signal_Pin,GPIO_PIN_RESET)

#define CON_SOL2_ON_GPIO_Port_H()          HAL_GPIO_WritePin(CON_SOL2_ON_GPIO_Port, CON_SOL2_ON_Pin, GPIO_PIN_SET)
#define CON_SOL2_ON_GPIO_Port_L()           HAL_GPIO_WritePin(CON_SOL2_ON_GPIO_Port, CON_SOL2_ON_Pin, GPIO_PIN_RESET)

#define CON_SOL1_ON_GPIO_Port_H()          HAL_GPIO_WritePin(CON_SOL1_ON_GPIO_Port, CON_SOL1_ON_Pin, GPIO_PIN_SET)
#define CON_SOL1_ON_GPIO_Port_L()           HAL_GPIO_WritePin(CON_SOL1_ON_GPIO_Port, CON_SOL1_ON_Pin, GPIO_PIN_RESET)




#define COOLING_LV1_H()          HAL_GPIO_WritePin(COOLING_LV1_GPIO_Port, COOLING_LV1_Pin, GPIO_PIN_SET)
#define COOLING_LV1_L()           HAL_GPIO_WritePin(COOLING_LV1_GPIO_Port, COOLING_LV1_Pin, GPIO_PIN_RESET)

#define COOLING_LV2_H()          HAL_GPIO_WritePin(COOLING_LV2_GPIO_Port, COOLING_LV2_Pin, GPIO_PIN_SET)
#define COOLING_LV2_L()            HAL_GPIO_WritePin(COOLING_LV2_GPIO_Port, COOLING_LV2_Pin, GPIO_PIN_RESET)

#define COOLING_LV3_H()          HAL_GPIO_WritePin(COOLING_LV3_GPIO_Port, COOLING_LV3_Pin, GPIO_PIN_SET)
#define COOLING_LV3_L()           HAL_GPIO_WritePin(COOLING_LV3_GPIO_Port, COOLING_LV3_Pin, GPIO_PIN_RESET)

#define COOLING_LV4_H()          HAL_GPIO_WritePin(COOLING_LV4_GPIO_Port, COOLING_LV4_Pin, GPIO_PIN_SET)
#define COOLING_LV4_L()           HAL_GPIO_WritePin(COOLING_LV4_GPIO_Port, COOLING_LV4_Pin, GPIO_PIN_RESET)

#define COOLING_LV5_H()          HAL_GPIO_WritePin(COOLING_LV5_GPIO_Port, COOLING_LV5_Pin, GPIO_PIN_SET)
#define COOLING_LV5_L()           HAL_GPIO_WritePin(COOLING_LV5_GPIO_Port, COOLING_LV5_Pin, GPIO_PIN_RESET)

#define HP2_SHOT_PUSH_H()        		HAL_GPIO_WritePin(HP2_SHOT_PUSH_GPIO_Port, HP2_SHOT_PUSH_Pin, GPIO_PIN_SET)
#define HP2_SHOT_PUSH_L()         		HAL_GPIO_WritePin(HP2_SHOT_PUSH_GPIO_Port, HP2_SHOT_PUSH_Pin, GPIO_PIN_RESET)

#define HP2_INSERT_H()           		HAL_GPIO_WritePin(HP2_INSERT_GPIO_Port, HP2_INSERT_Pin, GPIO_PIN_SET)
#define HP2_INSERT_L()            		HAL_GPIO_WritePin(HP2_INSERT_GPIO_Port, HP2_INSERT_Pin, GPIO_PIN_RESET)

#define MP3_PREVIOUS_VOLMI_H()   		HAL_GPIO_WritePin(MP3_PREVIOUS_VOLMI_GPIO_Port, MP3_PREVIOUS_VOLMI_Pin, GPIO_PIN_SET)
#define MP3_PREVIOUS_VOLMI_L()    		HAL_GPIO_WritePin(MP3_PREVIOUS_VOLMI_GPIO_Port, MP3_PREVIOUS_VOLMI_Pin, GPIO_PIN_RESET)

#define MP3_NEXT_VOLUP_H()       		HAL_GPIO_WritePin(MP3_NEXT_VOLUP_GPIO_Port, MP3_NEXT_VOLUP_Pin, GPIO_PIN_SET)
#define MP3_NEXT_VOLUP_L()        		HAL_GPIO_WritePin(MP3_NEXT_VOLUP_GPIO_Port, MP3_NEXT_VOLUP_Pin, GPIO_PIN_RESET)

#define MP3_PLAY_PAUSE_H()       		HAL_GPIO_WritePin(MP3_PLAY_PAUSE_GPIO_Port, MP3_PLAY_PAUSE_Pin, GPIO_PIN_SET)
#define MP3_PLAY_PAUSE_L()        		HAL_GPIO_WritePin(MP3_PLAY_PAUSE_GPIO_Port, MP3_PLAY_PAUSE_Pin, GPIO_PIN_RESET)

#define MP3_WORK_MODE_H()        		HAL_GPIO_WritePin(MP3_WORK_MODE_GPIO_Port, MP3_WORK_MODE_Pin, GPIO_PIN_SET)
#define MP3_WORK_MODE_L()         		HAL_GPIO_WritePin(MP3_WORK_MODE_GPIO_Port, MP3_WORK_MODE_Pin, GPIO_PIN_RESET)

#define MP3_DEVICE_SWITCH_H()    		HAL_GPIO_WritePin(MP3_DEVICE_SWITCH_GPIO_Port, MP3_DEVICE_SWITCH_Pin, GPIO_PIN_SET)
#define MP3_DEVICE_SWITCH_L()     		HAL_GPIO_WritePin(MP3_DEVICE_SWITCH_GPIO_Port, MP3_DEVICE_SWITCH_Pin, GPIO_PIN_RESET)

#define MP3_PLAY_MODE_H()        		HAL_GPIO_WritePin(MP3_PLAY_MODE_GPIO_Port, MP3_PLAY_MODE_Pin, GPIO_PIN_SET)
#define MP3_PLAY_MODE_L()         		HAL_GPIO_WritePin(MP3_PLAY_MODE_GPIO_Port, MP3_PLAY_MODE_Pin, GPIO_PIN_RESET)

#define MP3_Segment1_H()         		HAL_GPIO_WritePin(MP3_Segment1_GPIO_Port, MP3_Segment1_Pin, GPIO_PIN_SET)
#define MP3_Segment1_L()          		HAL_GPIO_WritePin(MP3_Segment1_GPIO_Port, MP3_Segment1_Pin, GPIO_PIN_RESET)

#define MP3_Segment2_H()         		HAL_GPIO_WritePin(MP3_Segment2_GPIO_Port, MP3_Segment2_Pin, GPIO_PIN_SET)
#define MP3_Segment2_L()          		HAL_GPIO_WritePin(MP3_Segment2_GPIO_Port, MP3_Segment2_Pin, GPIO_PIN_RESET)

#define MP3_Segment3_H()         		HAL_GPIO_WritePin(MP3_Segment3_GPIO_Port, MP3_Segment3_Pin, GPIO_PIN_SET)
#define MP3_Segment3_L()          		HAL_GPIO_WritePin(MP3_Segment3_GPIO_Port, MP3_Segment3_Pin, GPIO_PIN_RESET)

#define MP3_Segment4_H()         		HAL_GPIO_WritePin(MP3_Segment4_GPIO_Port, MP3_Segment4_Pin, GPIO_PIN_SET)
#define MP3_Segment4_L()          		HAL_GPIO_WritePin(MP3_Segment4_GPIO_Port, MP3_Segment4_Pin, GPIO_PIN_RESET)

#define RF_PWR_EN_H()            		HAL_GPIO_WritePin(RF_PWR_EN_GPIO_Port, RF_PWR_EN_Pin, GPIO_PIN_SET)
#define RF_PWR_EN_L()             		HAL_GPIO_WritePin(RF_PWR_EN_GPIO_Port, RF_PWR_EN_Pin, GPIO_PIN_RESET)

#define BUZZER_H()               		HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, GPIO_PIN_SET)
#define BUZZER_L()                		HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, GPIO_PIN_RESET)

#define BAT_CHG_ON_H()           		HAL_GPIO_WritePin(BAT_CHG_ON_GPIO_Port, BAT_CHG_ON_Pin, GPIO_PIN_SET)
#define BAT_CHG_ON_L()            		HAL_GPIO_WritePin(BAT_CHG_ON_GPIO_Port, BAT_CHG_ON_Pin, GPIO_PIN_RESET)


#define SD__INSERT_SIGNAL2_H()   		HAL_GPIO_WritePin(SD__INSERT_SIGNAL2_GPIO_Port, SD__INSERT_SIGNAL2_Pin, GPIO_PIN_SET)
#define SD__INSERT_SIGNAL2_L()    		HAL_GPIO_WritePin(SD__INSERT_SIGNAL2_GPIO_Port, SD__INSERT_SIGNAL2_Pin, GPIO_PIN_RESET)





//LED
#define HANDLE_LED_BLUE_ON()			      HAL_GPIO_WritePin(HANDLE_LED_BLUE_GPIO_Port, HANDLE_LED_BLUE_Pin, GPIO_PIN_SET)
#define HANDLE_LED_BLUE_OFF()       		  HAL_GPIO_WritePin(HANDLE_LED_BLUE_GPIO_Port, HANDLE_LED_BLUE_Pin, GPIO_PIN_RESET)

#define HANDLE_LED_GREED_ON()     			  HAL_GPIO_WritePin(HANDLE_LED_GREED_GPIO_Port, HANDLE_LED_GREED_Pin, GPIO_PIN_SET)
#define HANDLE_LED_GREED_OFF()      		  HAL_GPIO_WritePin(HANDLE_LED_GREED_GPIO_Port, HANDLE_LED_GREED_Pin, GPIO_PIN_RESET)

#define HANDLE_LED_RED_ON()  			      HAL_GPIO_WritePin(HANDLE_LED_RED_GPIO_Port, HANDLE_LED_RED_Pin, GPIO_PIN_SET)
#define HANDLE_LED_RED_OFF()        		  HAL_GPIO_WritePin(HANDLE_LED_RED_GPIO_Port, HANDLE_LED_RED_Pin, GPIO_PIN_RESET)

#define LED_DR2_ON()              			  HAL_GPIO_WritePin(LED_DR2_GPIO_Port, LED_DR2_Pin, GPIO_PIN_SET)
#define LED_DR2_OFF()               		  HAL_GPIO_WritePin(LED_DR2_GPIO_Port, LED_DR2_Pin, GPIO_PIN_RESET)

#define LED_DR1_ON()              			  HAL_GPIO_WritePin(LED_DR1_GPIO_Port, LED_DR1_Pin, GPIO_PIN_SET)
#define LED_DR1_OFF()               		  HAL_GPIO_WritePin(LED_DR1_GPIO_Port, LED_DR1_Pin, GPIO_PIN_RESET)


#define HP1_RST_CONTROL_TOGGLE()         HAL_GPIO_TogglePin(HP1_RST_CONTROL_GPIO_Port, HP1_RST_CONTROL_Pin)
#define HP1_Boot_CONTROL_TOGGLE()        HAL_GPIO_TogglePin(HP1_Boot_CONTROL_GPIO_Port, HP1_Boot_CONTROL_Pin)
#define HP2_Boot_CONTROL_TOGGLE()        HAL_GPIO_TogglePin(HP2_Boot_CONTROL_GPIO_Port, HP2_Boot_CONTROL_Pin)
#define HP2_RST_CONTROL_TOGGLE()         HAL_GPIO_TogglePin(HP2_RST_CONTROL_GPIO_Port, HP2_RST_CONTROL_Pin)
#define HP1_PWR_EN_TOGGLE()               HAL_GPIO_TogglePin(HP1_PWR_EN_GPIO_Port, HP1_PWR_EN_Pin)
#define HP2_PWR_EN_TOGGLE()               HAL_GPIO_TogglePin(HP2_PWR_EN_GPIO_Port, HP2_PWR_EN_Pin)
#define CILLER_PWR_ON_TOGGLE()           HAL_GPIO_TogglePin(CILLER_PWR_ON_GPIO_Port, CILLER_PWR_ON_Pin)
#define WATER_PUMP_PWR_EN_TOGGLE()       HAL_GPIO_TogglePin(WATER_PUMP_PWR_EN_GPIO_Port, WATER_PUMP_PWR_EN_Pin)
#define CON_SOL2_ON_TOGGLE()             HAL_GPIO_TogglePin(CON_SOL2_ON_GPIO_Port, CON_SOL2_ON_Pin)
#define CON_SOL1_ON_TOGGLE()             HAL_GPIO_TogglePin(CON_SOL1_ON_GPIO_Port, CON_SOL1_ON_Pin)
#define HANDLE_LED_BLUE_TOGGLE()         HAL_GPIO_TogglePin(HANDLE_LED_BLUE_GPIO_Port, HANDLE_LED_BLUE_Pin)
#define HANDLE_LED_GREED_TOGGLE()        HAL_GPIO_TogglePin(HANDLE_LED_GREED_GPIO_Port, HANDLE_LED_GREED_Pin)
#define HANDLE_LED_RED_TOGGLE()          HAL_GPIO_TogglePin(HANDLE_LED_RED_GPIO_Port, HANDLE_LED_RED_Pin)
#define LED_DR2_TOGGLE()                 HAL_GPIO_TogglePin(LED_DR2_GPIO_Port, LED_DR2_Pin)
#define LED_DR1_TOGGLE()                 HAL_GPIO_TogglePin(LED_DR1_GPIO_Port, LED_DR1_Pin)
#define COOLING_LV1_TOGGLE()             HAL_GPIO_TogglePin(COOLING_LV1_GPIO_Port, COOLING_LV1_Pin)
#define COOLING_LV2_TOGGLE()             HAL_GPIO_TogglePin(COOLING_LV2_GPIO_Port, COOLING_LV2_Pin)
#define COOLING_LV3_TOGGLE()             HAL_GPIO_TogglePin(COOLING_LV3_GPIO_Port, COOLING_LV3_Pin)
#define COOLING_LV4_TOGGLE()             HAL_GPIO_TogglePin(COOLING_LV4_GPIO_Port, COOLING_LV4_Pin)
#define COOLING_LV5_TOGGLE()             HAL_GPIO_TogglePin(COOLING_LV5_GPIO_Port, COOLING_LV5_Pin)

#define AC_RLY_ON_TOGGLE()             HAL_GPIO_TogglePin(AC_RLY_ON_GPIO_Port, AC_RLY_ON_Pin)
#define RF_Pulse_Signal_TOGGLE()       HAL_GPIO_TogglePin(RF_Pulse_Signal_GPIO_Port, RF_Pulse_Signal_Pin)


/*  			define end  			*/


/*  			enum start  			*/
typedef enum
{
	MP3_PREVIOUS_VOLMI,
	MP3_NEXT_VOLUP,
	MP3_PLAY_PAUSE,
	MP3_WORK_MODE,
	MP3_DEVICE_SWITCH,
	MP3_PLAY_MODE,
	MP3_Segment1,
	MP3_Segment2,
	MP3_Segment3,
	MP3_Segment4,

} MP3_E;

typedef enum
{
	DIP_STATE_0,
	DIP_STATE_1,
	DIP_STATE_2,
	DIP_STATE_3,
} DIP_STATE_E;
typedef enum
{
	BUZZER_ON_TIME = 50,
	MP3_ON_TIME = 50,

	COOL_LV1 = 1,
	COOL_LV2 = 2,
	COOL_LV3 = 3,
	COOL_LV4 = 4,
	COOL_LV5 = 5,
} IO_E;


typedef struct
{
	float flowSensorFrq;
	uint8_t ChillerPwrEn;
	uint8_t waterPumpPwrEn;
	uint8_t HP1PwrEn;
	uint8_t HP2PwrEn;
	uint8_t dipState;
	uint8_t buzzerOn;
	uint8_t mp3On;
	float battery;
	uint8_t rfPwrEn;
	uint8_t sol1On;
	uint8_t test1;
	uint8_t test2;
	uint8_t level1Status;
	uint8_t level2Status;
	uint8_t levelStatusErr;
	uint32_t day;
	uint16_t infoUiDesing;
	uint16_t infoUiFw;
	uint16_t infoMainFw;
	uint16_t infoHPFw;
	uint16_t infoRfFw;
	uint8_t YY;
	uint8_t MM;
	uint8_t DD;
	uint8_t dayOfWeek;
	uint32_t time;
	uint8_t hour;
	uint8_t min;
	uint8_t sec;
	uint8_t minPre;
	uint8_t rtcEn;
	uint8_t hp1CoolOk;
}IO_T;

/*  			enum end  				*/



/*  			stuct start  			*/

/*  			stuct end  				*/



/*  			function start  		*/
void WaterPump_Pwr_ON();
void WaterPump_Pwr_OFF();
void Ciller_Pwr_ON();
void Ciller_Pwr_OFF();
void IO_Init();
void IO_Test();
void RF_Pwr_ON();
void IO_Config();
void RTC_Init(void);


/*  			function end  			*/


/*  			extern start  			*/

extern IO_T m_io;

/*  			extern end  			*/

#endif

