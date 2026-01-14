/*
 * io_ctrl.c
 *
 *  Created on: Aug 25, 2025
 *      Author: Cellah_SW
 */

#include "io_ctrl.h"

IO_T m_io;

uint32_t timeTerm;
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	static uint32_t timeStamp;


	if(GPIO_Pin == FLOWSENSOR_OUT_Pin)
	{
		timeTerm = HAL_GetTick()-timeStamp;
		m_io.flowSensorFrq = (1000.0f) / (float)timeTerm;

		timeStamp = HAL_GetTick();

	}
}


void RF_Pwr_ON()
{
	RF_PWR_EN_H();
	m_io.rfPwrEn = 1;
}
void RF_Pwr_OFF()
{
	RF_PWR_EN_L();
	m_io.rfPwrEn = 0;
}

void HP1_Pwr_ON()
{
	HP1_PWR_EN_H();
	m_io.HP1PwrEn = 1;
}

void HP1_Pwr_OFF()
{
	HP1_PWR_EN_L();
	m_io.HP1PwrEn = 0;
}

void HP2_Pwr_ON()
{
	HP2_PWR_EN_H();
	m_io.HP2PwrEn = 1;
}
void HP2_Pwr_OFF()
{
	HP2_PWR_EN_L();
	m_io.HP2PwrEn = 1;
}

void WaterPump_Pwr_ON()
{
	WATER_PUMP_PWR_EN_H();
	m_io.waterPumpPwrEn = 1;
}

void WaterPump_Pwr_OFF()
{
	WATER_PUMP_PWR_EN_L();
	m_io.waterPumpPwrEn = 0;
}


void Ciller_Pwr_ON()
{
	CILLER_PWR_ON_GPIO_Port_H();
	m_io.ChillerPwrEn = 1;
}

void Ciller_Pwr_OFF()
{
	CILLER_PWR_ON_GPIO_Port_L();
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

void IO_Init()
{
	BUFFER_ON_L();
	HP1_Pwr_ON();
	WaterPump_Pwr_ON();

    BUZZER_H();
    HAL_Delay(1000);//
    BUZZER_L();
	Ciller_Pwr_ON();
	m_io.rtcEn = 1;
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

void IO_Config()
{
	uint8_t is_flowOk = (5<m_io.flowSensorFrq&&m_io.flowSensorFrq<10);
	uint8_t is_pumpOn = (m_io.waterPumpPwrEn == 1);
	uint8_t is_cillerOn = (m_io.ChillerPwrEn == 1);

	if(m_rf.pluseOn) return;

	m_io.level1Status = IS_LEVEL_SENSOR1_ON() ;
	m_io.level2Status = IS_LEVEL_SENSOR2_ON() ;


	if(is_flowOk && is_pumpOn &&  !is_cillerOn && m_io.level1Status && m_io.level2Status )
	{

		Ciller_Pwr_ON();
	}
	else
	{
		if(is_cillerOn) Ciller_Pwr_OFF();
		if(is_pumpOn) WaterPump_Pwr_OFF();
	}

	Battery_Read();
	RTC_Config();
 	IO_Test();

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


