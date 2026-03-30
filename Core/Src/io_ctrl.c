/*
 * io_ctrl.c
 *
 *  Created on: Aug 25, 2025
 *      Author: Cellah_SW
 */

#include "io_ctrl.h"

IO_T m_io;

uint32_t timeTerm;

float Get_X_From_Y(float y)
{
    float x;
    x = (y + 1.0f) / 14.0f;
    return x;
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	static uint32_t timeStamp;


	if(GPIO_Pin == FLOWSENSOR_OUT_Pin)
	{
		m_io.flowTimeTerm = HAL_GetTick()-timeStamp;
		m_io.flowSensorFrq = (1000.0f) / (float)m_io.flowTimeTerm;
		m_io.flowSensorFrqChk = m_io.flowSensorFrq;
		m_io.LperSec = Get_X_From_Y(m_io.flowSensorFrq);

		timeStamp = HAL_GetTick();
		m_io.flowPulseCnt++;

	}
}


void SOL1_ON_ORG()
{
	CON_SOL2_ON_GPIO_Port_H();
	Debug_Printf("SOL1_ON",1);
	m_io.sol1On= 1;
}
void SOL1_OFF_ORG()
{
	CON_SOL2_ON_GPIO_Port_L();
	Debug_Printf("SOL1_OFF",1);
	m_io.sol1On= 0;
}


void SOL1_ON()
{
	CON_SOL1_ON_GPIO_Port_L();  //////반대
	CON_SOL2_ON_GPIO_Port_H();
	Debug_Printf("SOL1_ON",1);
	m_io.sol1On= 1;
}
void SOL1_OFF()
{
	CON_SOL1_ON_GPIO_Port_H();	//////반대
	CON_SOL2_ON_GPIO_Port_L();
	Debug_Printf("SOL1_OFF",1);
	m_io.sol1On= 0;
}


void RF_Pwr_ON()
{
	RF_PWR_EN_H();
	Debug_Printf("RF_Pwr_ON",1);
	m_io.rfPwrEn = 1;
}
void RF_Pwr_OFF()
{
	RF_PWR_EN_L();
	Debug_Printf("RF_Pwr_OFF",1);
	m_io.rfPwrEn = 0;
}

void HP1_Pwr_ON()
{
	HP1_PWR_EN_H();
	Debug_Printf("HP1_Pwr_ON",1);
	m_io.HP1PwrEn = 1;
}

void HP1_Pwr_OFF()
{
	HP1_PWR_EN_L();
	Debug_Printf("HP1_Pwr_OFF",1);
	m_io.HP1PwrEn = 0;
}


int HP1_InsertOOn, HP1_InsertOOff;
int HP1_InsertOOnI, HP1_InsertOOffI;



void HP2_Pwr_ON()
{
	HP2_PWR_EN_H();
	Debug_Printf("HP2_Pwr_ON",1);
	m_io.HP2PwrEn = 1;
}
void HP2_Pwr_OFF()
{
	HP2_PWR_EN_L();
	Debug_Printf("HP2_Pwr_OFF",1);
	m_io.HP2PwrEn = 1;
}

void WaterPump_Pwr_ON()
{
	WATER_PUMP_PWR_EN_H();
	Debug_Printf("PUMP ON",1);
	m_io.waterPumpPwrEn = 1;
}

void WaterPump_Pwr_OFF()
{
	WATER_PUMP_PWR_EN_L();
	Debug_Printf("PUMP OFF",1);
	m_io.waterPumpPwrEn = 0;
}


void Ciller_Pwr_ON()
{
	CILLER_PWR_ON_GPIO_Port_H();
	Debug_Printf("Ciller ON",1);
	m_io.ChillerPwrEn = 1;
}

void Ciller_Pwr_OFF()
{
	CILLER_PWR_ON_GPIO_Port_L();
	Debug_Printf("Ciller OFF",1);
	m_io.ChillerPwrEn = 0;
}

void MP3_PLAY_ON(uint8_t num)
{
	m_io.mp3On = num;
	switch(num)
	{
		case MP3_PREVIOUS_VOLMI:
			MP3_PREVIOUS_VOLMI_H();
		break;
		case MP3_NEXT_VOLUP:
			MP3_NEXT_VOLUP_H();
		break;
		case MP3_PLAY_PAUSE:
			MP3_PLAY_PAUSE_H();
		break;
		case MP3_WORK_MODE:
			MP3_WORK_MODE_H();
		break;
		case MP3_DEVICE_SWITCH:
			MP3_DEVICE_SWITCH_H();
		break;
		case MP3_PLAY_MODE:
			MP3_PLAY_MODE_H();
		break;
		case MP3_Segment1:
			MP3_Segment1_H();
		break;
		case MP3_Segment2:
			MP3_Segment2_H();
		break;
		case MP3_Segment3:
			MP3_Segment3_H();
		break;
		case MP3_Segment4:
			MP3_Segment4_H();
		break;
	}
}


void MP3_PLAY_OFF_Config(uint8_t num)
{
	static uint16_t mp3Cnt;
	if(m_io.mp3On)
	{
		mp3Cnt++;
		if(mp3Cnt == MP3_ON_TIME)
		{
			mp3Cnt = 0;
			switch(m_io.mp3On)
			{
				case MP3_PREVIOUS_VOLMI:
					MP3_PREVIOUS_VOLMI_L();
				break;
				case MP3_NEXT_VOLUP:
					MP3_NEXT_VOLUP_L();
				break;
				case MP3_PLAY_PAUSE:
					MP3_PLAY_PAUSE_L();
				break;
				case MP3_WORK_MODE:
					MP3_WORK_MODE_L();
				break;
				case MP3_DEVICE_SWITCH:
					MP3_DEVICE_SWITCH_L();
				break;
				case MP3_PLAY_MODE:
					MP3_PLAY_MODE_L();
				break;
				case MP3_Segment1:
					MP3_Segment1_L();
				break;
				case MP3_Segment2:
					MP3_Segment2_L();
				break;
				case MP3_Segment3:
					MP3_Segment3_L();
				break;
				case MP3_Segment4:
					MP3_Segment4_L();
				break;
			}
			m_io.mp3On = 0;
		}
	}

}

void Buzzer_ON()
{
	BUZZER_H();
	m_io.buzzerOn = 1;
}

void Buzzer_OFF_Config()
{
	static uint16_t buzzCnt;
	if(m_io.buzzerOn)
	{
		buzzCnt++;
		if(buzzCnt == BUZZER_ON_TIME)
		{
			buzzCnt = 0;
			BUZZER_L();
			m_io.buzzerOn = 0;
		}
	}
}

void DIP_SW_Config()
{
	if(!IS_STATE_A_ON() && !IS_STATE_B_ON())
	{
		m_io.dipState = DIP_STATE_0;
	}
	else if(IS_STATE_A_ON() && !IS_STATE_B_ON())
	{
		m_io.dipState = DIP_STATE_1;
	}
	else if(!IS_STATE_A_ON() && IS_STATE_B_ON())
	{
		m_io.dipState = DIP_STATE_2;
	}
	else if(IS_STATE_A_ON() && IS_STATE_B_ON())
	{
		m_io.dipState = DIP_STATE_3;
	}


}

void Cooling_ON(uint8_t num)
{
	switch (num)
	{
		case COOL_LV1:
			COOLING_LV1_H();
		break;
		case COOL_LV2:
			COOLING_LV2_H();
		break;
		case COOL_LV3:
			COOLING_LV3_H();
		break;
		case COOL_LV4:
			COOLING_LV4_H();
		break;
		case COOL_LV5:
			COOLING_LV5_H();
		break;
	}
}

 uint16_t adcQQ;

 void Battery_Read(void)
{
    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
    uint16_t adc = (uint16_t)HAL_ADC_GetValue(&hadc1);
    HAL_ADC_Stop(&hadc1);
	adcQQ = adc;

	m_io.battery = 3.3* ((float)adc/4095);
}







void HP_Connect_Config()
{
	static uint32_t timeStamp;
	static uint8_t isCartDetectCnt = 0;

	int flowINt;

	flowINt = m_io.flowSensorFrq*10.0;


	if(HAL_GetTick()-timeStamp >= 1000)
	{
		timeStamp = HAL_GetTick();

		if(IS_HP1_INSERT())
		{
			if(m_io.HP1_Insert != HP_INSERT)Debug_Printf("HP_INSERT",1);
			m_io.HP1_Insert = HP_INSERT;
		}
		else
		{
			if(m_io.HP1_Insert != HP_UN_INSERT)Debug_Printf("HP_UN_INSERT",1);
			m_io.HP1_Insert = HP_UN_INSERT;
			m_eep.catridgeDetect = CATRIGE_CHK_UN_DETECT;
		}

		if(!m_hand1.cartDetectFlag && isCartDetectCnt<3)
		{
			Tx_Hand1_Msg(CMD_CATRIDGE_EVENT, 1);
			isCartDetectCnt++;
		}
	}
	if(m_io.HP1_Insert == HP_INSERT)
	{
		if(!m_io.HP1PwrEn)HP1_Pwr_ON();
	}
	else
	{
		if(m_io.HP1PwrEn)HP1_Pwr_OFF();
	}


	if((m_io.HP1_Insert == HP_INSERT) && (m_eep.catridgeDetect != CATRIGE_CHK_UN_DETECT))
	{
		m_io.sol1OnStatus = 1;//SOL1_ON();
		isCartDetectCnt = 0;
	}
	else
	{
		if(m_io.sol1OnStatus)Ready_OFF();
		m_io.sol1OnStatus = 0;
	}


}







void Level_Check()
{
	m_io.level1Status = IS_LEVEL_SENSOR1_ON() ;
	m_io.level2Status = IS_LEVEL_SENSOR2_ON() ;

	if(m_io.level1Status && m_io.level2Status)
	{
		// ok
		m_io.levelStatusErr = 0;
	}
	else if(!m_io.level1Status && m_io.level2Status)
	{
		// warning
		m_io.levelStatusErr = 0;
	}
	else
	{
		//error
		if(!m_io.levelStatusErr)
		{
			Ciller_Pwr_OFF();//나중에 플로우 값 정상들어와야지 켜지게 하기
			WaterPump_Pwr_OFF();
			m_io.levelStatusErr = 1;
		}
	}


}

uint8_t IO_ErrCnt_Chk(uint8_t BooL, uint8_t idx )
{
	static uint8_t cntBuff[10];
	uint8_t eventOn = 0;

	if(idx >= 10) return 0;

	if(BooL)
	{
		 if(cntBuff[idx] < 10) cntBuff[idx]++;
	}
	else cntBuff[idx] = 0;

	if(cntBuff[idx] >= 10)
	{
		cntBuff[idx] = 0;
		eventOn = 1;
	}

	return eventOn;
}
void Flow_Stop_Check_ORG()
{

	uint8_t is_flowOk = (2<m_io.flowSensorFrq&&m_io.flowSensorFrq<40);
//	uint8_t is_flowOk = 1;//(3<m_io.flowSensorFrq);
	int flowINt;
	static uint32_t timeStamp;
	uint8_t flowErr = 0;
	static uint8_t flowErrAccu;

	flowINt = m_io.flowSensorFrq*10.0;
	if(HAL_GetTick()-timeStamp >= 1000)
	{

		timeStamp = HAL_GetTick();

		if(!m_io.flowSensorFrqChk)
		{
			flowErr++;
			Debug_Printf("m_io.flowPulseCnt",1);
		}
		if(is_flowOk)
		{
			flowErr++;
			Debug_Printf("is_flowOk Fail",1);
			printf("flowINt = %d \r\n",flowINt);
		}
		m_io.flowPulseCnt = 0;

		if(!flowErrAccu &&flowErr)
		{
			if(m_io.sol1On)
			{
				Debug_Printf("1111",1);
				SOL1_OFF();
			}
			else
			{
				Debug_Printf("2222",1);
				flowErrAccu = 1;
				Ciller_Pwr_OFF();//나중에 플로우 값 정상들어와야지 켜지게 하기
				WaterPump_Pwr_OFF();
				Debug_Printf("CILLER PUMP_FLOW END",1);
			}
		}
		m_io.flowSensorFrqChk = 0;
	}

}

void Flow_Stop_Check()
{

	uint8_t is_flowOkSolOn = (2<m_io.flowSensorFrq&&m_io.flowSensorFrq<20);
	uint8_t is_flowOkSolOff = (10<m_io.flowSensorFrq&&m_io.flowSensorFrq<40);
	static uint32_t timeStamp;


	if(HAL_GetTick()-timeStamp >= 1000)
	{

		timeStamp = HAL_GetTick();

		if(m_io.sol1On)
		{
			if(!is_flowOkSolOn || !m_io.flowSensorFrqChk) SOL1_OFF();
		}
		else
		{
			if(!is_flowOkSolOff || !m_io.flowSensorFrqChk)
			{
				WaterPump_Pwr_OFF();
				Ciller_Pwr_OFF();
			}
		}
		m_io.flowSensorFrqChk = 0;
	}

}



void IO_Init()
{

    BUZZER_H();
    HAL_Delay(500);//
    BUZZER_L();



	SOL1_OFF();
	m_io.sol1OnStatus = 0;


	m_io.HP1_Insert = HP_YET_INSERT;
	m_eep.catridgeDetect = CATRIGE_CHK_UN_DETECT;

	m_io.rtcEn = 1;
	if(IS_HP1_INSERT())HP1_Pwr_ON();
	Body_Led_Ctrl(BODY_LED_BOOT);

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

void RTC_Config(void)
{
	static uint32_t timeStamp;

	if(!m_io.rtcEn)return;

	if(HAL_GetTick()-timeStamp >= 1000)
	{

		timeStamp = HAL_GetTick();
		// RTC로부터 시간 읽기
		DS1308_GetTime(&m_io.hour, &m_io.min, &m_io.sec);
		DS1308_GetDay(&m_io.dayOfWeek, &m_io.DD, &m_io.MM, &m_io.YY);

		m_io.day = m_io.YY*10000 + m_io.MM*100 + m_io.DD;
		m_io.time = m_io.hour*10000 + m_io.min*100 + m_io.sec;



#if 0
		if(m_io.min != m_io.minPre)
		{
			Tx_LCD_Msg(CMD_RTC_YY, m_io.YY);
			Tx_LCD_Msg(CMD_RTC_MM, m_io.MM);
			Tx_LCD_Msg(CMD_RTC_DD, m_io.DD);
			Tx_LCD_Msg(CMD_RTC_HOUR, m_io.hour);
			Tx_LCD_Msg(CMD_RTC_MIN, m_io.min);
			Tx_LCD_Msg(CMD_RTC_SEC, m_io.sec);
			m_io.minPre = m_io.min;
		}
#endif
		// 읽은 값 확인용 (예: UART 출력 - 실제 환경에 맞게 대체)
//		printf("RTC Time: %02d:%02d:%02d\r\n", hour, min, sec);
	}
}
void Body_Led_Ctrl(uint8_t mode)
{
	switch (mode)
	{
		case BODY_LED_NOMAL:
			HANDLE_LED_RED_OFF();//1 boot
			HANDLE_LED_GREED_OFF();//2 err
			HANDLE_LED_BLUE_OFF();//3 shot
			Debug_Printf("LED_NOMAL", 1);
		break;

		case BODY_LED_BOOT:
			HANDLE_LED_RED_ON();//1 boot
			HANDLE_LED_GREED_OFF();//2 err
			HANDLE_LED_BLUE_OFF();//3 shot
			Debug_Printf("LED_BOOT", 1);
		break;

		case BODY_LED_ERROR:
			HANDLE_LED_RED_OFF();//1 boot
			HANDLE_LED_GREED_ON();//2 err
			HANDLE_LED_BLUE_OFF();//3 shot
			Debug_Printf("LED_ERROR", 1);
		break;

		case BODY_LED_SHOT:
			HANDLE_LED_RED_OFF();//1 boot
			HANDLE_LED_GREED_OFF();//2 err
			HANDLE_LED_BLUE_ON();//3 shot
			Debug_Printf("LED_SHOT", 1);
		break;
	}

}
void IO_Config()
{
	uint8_t is_pumpOn = (m_io.waterPumpPwrEn == 1);
	uint8_t is_cillerOn = (m_io.ChillerPwrEn == 1);

	if(m_rf.pluseOn) return;

//	Level_Check();
	HP_Connect_Config();
//	Flow_Stop_Check();

	Battery_Read();
	RTC_Config();

 }



void IO_Test()
{

	if(m_io.test1 == 1)
	{
		m_io.test1 = 0;
//		BAT_CHG_ON_H();
	WaterPump_Pwr_ON();


	}
	if(m_io.test1 == 2)
	{
		m_io.test1 = 0;
//		BAT_CHG_ON_L();
	WaterPump_Pwr_OFF();

	}
	if(m_io.test2 == 1)
	{
		m_io.test2 = 0;
		Ciller_Pwr_ON();

	}
	if(m_io.test2 == 2)
	{
		m_io.test2 = 0;
		Ciller_Pwr_OFF();

	}




}


