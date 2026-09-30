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


void PELTIER_PWR_ON()
{
	PELTIER_PWR_H();
	Debug_Printf("PELTIER_PWR_ON",1);
	m_io.ptrPwrOn = 1;
}
void PELTIER_PWR_OFF()
{
	PELTIER_PWR_L();
	Debug_Printf("PELTIER_PWR_OFF",1);
	m_io.ptrPwrOn = 0;
}

void SOL1_ON()
{
	CON_SOL1_ON_GPIO_Port_L();  //////�ݴ�
	Debug_Printf("SOL1_ON",1);
	m_io.sol1On= 1;
}
void SOL1_OFF()
{
	CON_SOL1_ON_GPIO_Port_H();	//////�ݴ�
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
	if(!m_io.waterPumpPwrEn)
	{
		WATER_PUMP_PWR_EN_H();
		Debug_Printf("PUMP ON",1);
		m_io.waterPumpPwrEn = 1;
	}
}

void WaterPump_Pwr_OFF()
{
	WATER_PUMP_PWR_EN_L();
	Debug_Printf("PUMP OFF",1);
	m_io.waterPumpPwrEn = 0;
}


void Ciller_Pwr_ON()
{
	if(!m_io.ChillerPwrEn)
	{
		CILLER_PWR_ON_GPIO_Port_H();
		Debug_Printf("Ciller ON",1);
		m_io.ChillerPwrEn = 1;
	}
}

void Ciller_Pwr_OFF()
{
	CILLER_PWR_ON_GPIO_Port_L();
	Debug_Printf("Ciller OFF",1);
	m_io.ChillerPwrEn = 0;
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


 void ADC1_Channel_Selection(uint8_t ch)
 {
   ADC_ChannelConfTypeDef sConfig = {0};
   if(ch == 0) sConfig.Channel = ADC_CHANNEL_10;
   else if(ch == 1)  sConfig.Channel = ADC_CHANNEL_13;
   else if(ch == 2)  sConfig.Channel = ADC_CHANNEL_1;

   else return;

   sConfig.Rank = ADC_REGULAR_RANK_1;
   sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
   if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
   {
	 Error_Handler();
   }

 }

 uint16_t adcQQ,adcQQ2;


void Battery_Read(void)
{
	static uint32_t timeStamp;

	if(HAL_GetTick()-timeStamp >= 1000)
	{

		ADC1_Channel_Selection(ADC_CH_RTC_BATTERY);
		HAL_ADC_Start(&hadc1);
		if(HAL_ADC_PollForConversion(&hadc1, 10) == HAL_OK) {
			uint16_t adc = (uint16_t)HAL_ADC_GetValue(&hadc1);
			adcQQ = adc;
			m_io.battery = 3.3f * ((float)adc / 4095.0f);
		}
		HAL_ADC_Stop(&hadc1);
		timeStamp = HAL_GetTick();
	}


}

//==========================================================================================================
//���̳���
// �����ͽ�Ʈ �� ȸ�� ���?���?����
#define R25          10000.0f   // 25���� �� ���� (10k)
#define B_VALUE      3984.0f    // B25/85 ��
#define T25          298.15f    // 25���� �̺� �µ��� ��ȯ (273.15 + 25)
//#define R_PULLUP     24000.0f   // �����?���� Ǯ�� ���� (24k)

#define ADC_MAX      4095.0f    // STM32F103 12��Ʈ ADC �ִ밪
uint32_t R_PULLUP    = 10000;   // �����?���� Ǯ�� ���� (24k)

/**
 * @brief ADC ���� �Է¹޾� ���� �µ��� ��ȯ�ϴ� �Լ�
 * @param adc_value ADC_IN���� �о����?RAW ��
 * @return float ���� ���� �µ� (��C)
 */
float Get_NTC_Temperature_j(uint32_t adc_value) {
    if (adc_value == 0) return -99.0f; // Open circuit or GND short error ó��

    // 1. ADC ���� �̿��Ͽ� ���� NTC ���װ� ���?
    // Ǯ�ٿ� ����: R_ntc = R_pullup * (V_out / (V_cc - V_out))
    // ���� ��ʽĿ�?���� V_cc ���� ����: R_ntc = R_pullup * (adc / (4095 - adc))
    float r_ntc = R_PULLUP * ((float)adc_value / (ADC_MAX - (float)adc_value));

    // 2. B-parameter ���� �̿��� �µ�(Kelvin) ���?
    float temperature;
    temperature = r_ntc / R25;              // R/R0
    temperature = log(temperature);         // ln(R/R0)
    temperature /= B_VALUE;                 // 1/B * ln(R/R0)
    temperature += (1.0f / T25);            // + (1/T0)
    temperature = 1.0f / temperature;       // �̺� �µ� �ϼ�

    // 3. �̺� �µ��� ���� �µ��� ��ȯ
    float temperature_c = temperature - 273.15f;
	temperature_c +=19;

    return temperature_c;
}

/* ���� ���� ���?���� */
// uint32_t adc_raw = HAL_ADC_GetValue(&hadc1);
// float current_temp = Get_NTC_Temperature(adc_raw);

//==========================================================================================================


//==========================================================================================================

uint8_t chilFlag = 0;
uint32_t chilTerm = 0;

void Chiller_Temperature_Read()
{
	static uint32_t timeStamp;
	uint32_t adc;

	ADC1_Channel_Selection(ADC_CH_WATER_TEMP);
	HAL_ADC_Start(&hadc1);
	if(HAL_ADC_PollForConversion(&hadc1, 10) == HAL_OK)
	{
		adc = (uint16_t)HAL_ADC_GetValue(&hadc1);
	}
	HAL_ADC_Stop(&hadc1);
	adcQQ2 = adc;
	m_io.chillerTemp = Get_NTC_Temperature_j(adc);



	if(HAL_GetTick()-timeStamp >= 5000)
	{
		timeStamp = HAL_GetTick();
		if(m_io.chillerTemp<-10.0)
		{
			Ciller_Pwr_OFF();
			HAL_Delay(500);
			Ciller_Pwr_ON();
		}
//		printf("[244,%d]\r\n",Data);
	}



}


void HP_Connect_Config()
{
	static uint32_t timeStamp;
	static uint8_t isCartDetectCnt = 0;

	int flowINt;

	flowINt = m_io.flowSensorFrq*10.0;


	if(HAL_GetTick()-timeStamp >= 500)
	{
		timeStamp = HAL_GetTick();

		if(IS_HP1_INSERT())
		{
			if(m_io.HP1_Insert != HP_INSERT)
			{
				Debug_Printf("HP_INSERT",1);
				Debug_Event(EVENT_7);
			}
			m_io.HP1_Insert = HP_INSERT;
		}
		else
		{
			if(m_io.HP1_Insert != HP_UN_INSERT)
			{
				Debug_Printf("HP_UN_INSERT",1);
				Debug_Event(EVENT_8);
				m_eep.catridgeDetect = CATRIGE_CHK_UN_DETECT;
//				Tx_LCD_Msg(CMD_CATRIDGE_EVENT, m_eep.catridgeDetect);
			}
			m_io.HP1_Insert = HP_UN_INSERT;
		}

		if(!m_hand1.cartDetectFlag && isCartDetectCnt<3)
		{
			Tx_Hand1_Msg(CMD_CATRIDGE_EVENT, 0XFF);
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
		m_io.sol1OnStatus = 1;
		isCartDetectCnt = 0;
		Flow_Stop_Check();
	}
	else
	{
		if(m_io.sol1OnStatus)
		{
			Ready_OFF(EVENT_3);
			SOL1_OFF();
			PELTIER_PWR_OFF();
		}
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
			Ciller_Pwr_OFF();//���߿� �÷ο� �� ������;���?������ �ϱ�
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


uint8_t Flow_Nomal_Check()
{
	static uint8_t flowErrCnt1;

}

void Flow_Stop_Check()
{

	uint8_t is_flowOkSolOn = (1<m_io.flowSensorFrq&&m_io.flowSensorFrq<10);
	uint8_t is_flowOkSolOff = (10<m_io.flowSensorFrq&&m_io.flowSensorFrq<40);

	static uint32_t timeStamp;
	static uint8_t flowErrCnt1,flowErrCnt2;

	if(!m_rf.sysChkFlag) return;
	if(HAL_GetTick()-timeStamp >= 1000)
	{
		timeStamp = HAL_GetTick();

		switch (m_io.sol1On)
		{
			case 1:
				if((!is_flowOkSolOn)||(!m_io.flowSensorFrqChk))
				{
					flowErrCnt1++;
					if(flowErrCnt1>=3)
					{
						flowErrCnt1 = 0;
						if(m_err.flowLimitUnder !=1)
						{
							Ready_OFF(EVENT_4);
							PELTIER_PWR_OFF();
							SOL1_OFF();
						}
						m_err.flowLimitUnder = 1;
					}
				}
				else
				{
					m_err.flowLimitUnder = 0;
					flowErrCnt1 = 0;
				}
			break;

			case 0:
				if((!is_flowOkSolOff)||(!m_io.flowSensorFrqChk))
				{
					flowErrCnt2++;
					if(flowErrCnt2>=3)
					{
						flowErrCnt2 = 0;
						if(m_err.flowLimitUnder !=2)
						{
							Ready_OFF(EVENT_10);
							PELTIER_PWR_OFF();
							WaterPump_Pwr_OFF();
							Ciller_Pwr_OFF();
							SOL1_OFF();
						}
						m_err.flowLimitUnder = 2;
					}
				}
				else
				{
					m_err.flowLimitUnder = 0;
					flowErrCnt2 = 0;
				}
			break;


		}

		m_io.flowSensorFrqChk = 0;
	}

}


void IO_Init()
{

	AC_RLY_H();
	for(int i =0 ;i < 2;i++)
	{
	    BUZZER_H();
	    HAL_Delay(50);//
	    BUZZER_L();
	    HAL_Delay(50);
	}

	if(IS_AC_INPUT_STATE()) m_io.powerSpecs = POWER_AC_KOREA;
	else m_io.powerSpecs = POWER_AC_OTHER;

	HP1_PELT_ON();
	PELTIER_PWR_OFF();

	BAT_CHG_ON_H();
//	BAT_ADC_EN_H();

	SOL1_OFF();
	m_io.sol1OnStatus = 0;


	m_io.HP1_Insert = HP_YET_INSERT;
	m_eep.catridgeDetect = CATRIGE_CHK_UN_DETECT;

	m_io.rtcEn = 1;
	if(IS_HP1_INSERT())HP1_Pwr_ON();
	Body_Led_Ctrl(BODY_LED_BOOT);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);

	if(IS_HP1_FOOT_INSERT())
	{
		m_io.footInsert = 1;
		m_rf.switchHandFoot = SWITCH_FOOT;
	}
	else
	{
		m_io.footInsert = 0;
		m_rf.switchHandFoot = SWITCH_HAND_FOOT_NO;
	}

	RTC_Init();
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
		// RTC�κ��� �ð� �б�
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
		// ���� �� Ȯ�ο� (��: UART ���?- ���� ȯ�濡 �°� ��ü)
//		printf("RTC Time: %02d:%02d:%02d\r\n", hour, min, sec);
	}
}
void Body_Led_Ctrl(uint8_t mode)
{
	switch (mode)
	{
		case BODY_LED_STANDBY:
			BODY_LED_1_OFF();
			BODY_LED_2_OFF();
			BODY_LED_3_OFF();
			Debug_Printf("LED_NOMAL", 1);
		break;

		case BODY_LED_BOOT:
			BODY_LED_1_ON();
			BODY_LED_2_OFF();
			BODY_LED_3_OFF();
			Debug_Printf("LED_BOOT", 1);
		break;

		case BODY_LED_ERROR:
			BODY_LED_1_OFF();
			BODY_LED_2_ON();
			BODY_LED_3_OFF();
			m_err.errLedViewTime = 5;
			Debug_Printf("LED_ERROR", 1);
		break;


		case BODY_LED_READY:
			BODY_LED_1_ON();
			BODY_LED_2_ON();
			BODY_LED_3_OFF();
			Debug_Printf("LED_NOMAL", 1);
		break;

		case BODY_LED_SHOT:
			BODY_LED_1_OFF();
			BODY_LED_2_OFF();
			BODY_LED_3_ON();
			Debug_Printf("LED_SHOT", 1);
		break;

	}

}

void Foot_Insert_Chk()
{
	static uint32_t timeStamp;

	if(HAL_GetTick()-timeStamp >= 100)
	{

		if(IS_HP1_FOOT_INSERT())
		{
			if(!m_io.footInsert)
			{
				Tx_LCD_Msg(CMD_ALRAM, IDX_FOOT_CONNECT);
				m_rf.switchHandFoot = SWITCH_FOOT;
				Tx_LCD_Msg(CMD_HAND_FOOT, m_rf.switchHandFoot);
			}
			m_io.footInsert = 1;
		}
		else
		{
			if(m_io.footInsert)
			{
				Tx_LCD_Msg(CMD_ALRAM, IDX_FOOT_DISCONNECT);
				m_rf.switchHandFoot = SWITCH_HAND_FOOT_NO;
				Tx_LCD_Msg(CMD_HAND_FOOT, m_rf.switchHandFoot);
			}
			m_io.footInsert = 0;
		}
		timeStamp = HAL_GetTick();
	}

}

void PowerSpecs_Chk()
{
	if(m_io.powerSpecs != m_eep.powerSpecs) m_err.powerSpecs = 1;
	else m_err.powerSpecs = 0;
}
void WDT_LED_Config()
{
	static uint32_t timeStamp;

	if(HAL_GetTick()-timeStamp >= 500)
	{
		LED_DR2_TOGGLE();
		timeStamp = HAL_GetTick();
	}
}
void IO_Config()
{
	if(m_rf.pluseOn) return;

//	Level_Check();
	HP_Connect_Config();
	Battery_Read();
	RTC_Config();
	Chiller_Temperature_Read();
 	WDT_LED_Config();
 	Foot_Insert_Chk();
 	PowerSpecs_Chk();


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


