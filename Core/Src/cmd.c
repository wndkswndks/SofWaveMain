//cmd.c

#include "cmd.h"
UART_T m_uart1;
UART_T m_uart2;
UART_T m_uart3;
UART_T m_uart4;
UART_T m_uart5;



uint8_t Rx_data1[1];
uint8_t Rx_data2[1];
uint8_t Rx_data3[1];
uint8_t Rx_data4[1];
uint8_t Rx_data5[1];

void Uart_Init()
{
	HAL_UART_Receive_IT(&huart1, Rx_data1, 1);
	HAL_UART_Receive_IT(&huart2, Rx_data2, 1);
	HAL_UART_Receive_IT(&huart3, Rx_data3, 1);
	HAL_UART_Receive_IT(&huart4, Rx_data4, 1);
	HAL_UART_Receive_IT(&huart5, Rx_data5, 1);
}


#if 0
int putchar(int ch)
{
	while(HAL_OK != HAL_UART_Transmit_IT(&huart1, (uint8_t *)&ch, 1))
	{}
	return ch;

}

#else
int __io_putchar(int ch)
{
    while(HAL_OK != HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1,100))
	{}
	return ch;
}

#endif
uint8_t Uart_RxBuff_Get(UART_T* uart, uint8_t data,char startChar, char endChar)
{
	if(data ==startChar)
	{
		uart->rxCnt = 0;
		uart->startFlag = 1;
		memset(uart->rxBuff, 0, RX_BUFF_SIZE);
	}
	else if(uart->startFlag &&data ==endChar)
	{
		uart->endFlag = 1;
	}
	if(uart->startFlag)
	{
		uart->rxBuff[uart->rxCnt] = data;
		uart->rxCnt++;
		uart->rxCnt %= RX_BUFF_SIZE;
	}

	if(uart->startFlag&&uart->endFlag)
	{
		uart->startFlag = 0;
		uart->endFlag = 0;
		return 1;
	}
	else
	{
		return 0;
	}

}


void Rx_BuffClear(UART_T *uart)
{
	memset(uart->rxBuff,0,RX_BUFF_SIZE);
	uart->rxCnt = 0;
}

void Debug_Printf(char* str, uint8_t cr)
{
#ifdef DEBUG_PRINT

	printf("%s",str);
	if(cr)printf("\r\n");
#endif

}

void Debug_HAND_Printf(uint8_t rxtx, uint8_t cmd, uint16_t data)
{
#ifdef DEBUG_PRINT

	if(rxtx != DEBUG_RX && rxtx != DEBUG_TX) return;
	char rxtxStr[2][3] = {"Rx","Tx"};
	printf("[%s_HAND] [%u,%u]\r\n",rxtxStr[rxtx], cmd, data);

#endif

}

void Debug_LCD_Printf(uint8_t rxtx, uint8_t cmd, uint16_t data)
{
#ifdef DEBUG_PRINT
	if(rxtx != DEBUG_RX && rxtx != DEBUG_TX) return;
	char rxtxStr[2][3] = {"Rx","Tx"};
	printf("[%s_LCD] [%u,%u]\r\n",rxtxStr[rxtx], cmd, data);

#endif

}


void Debug_Rx_RF_Printf(uint8_t* buff, uint8_t cnt)
{
#if 1
	printf("[RX_RF] ");
	for(int i =0 ;i < cnt;i++)
	{
		printf("%02X ", buff[i]);
	}
	printf("\r\n");

	//printf("%02X %02X %02X %02X %02X %02X %02X\r\n",buff[0], buff[1], buff[2], buff[3], buff[4], buff[5], buff[6] );
#endif

}
void Debug_Tx_RF_Printf(uint8_t* buff,uint8_t len)
{
#if 1

	printf("Rf Tx :");
	for(int i =0 ;i < len;i++)
	{
		printf("%02X ",buff[i]);

	}
	printf("\r\n");
#endif

}

void Debug_Tx_RF_Watt_Printf(uint8_t ch, uint16_t watt)
{
#if 1
	printf("[TX_RF] ");
	printf("Ch[%u] Watt[%u] \r\n",ch, watt);

#endif

}
void Debug_Tx_RF_Frq_Printf(uint8_t ch, uint16_t frq)
{
#if 1
	printf("[TX_RF] ");
	printf("Ch[%u] Frq[%u] \r\n",ch, frq);
#endif

}


void Debug_Tx_RF_All_Watt_Printf()
{
#if 1
	float wattF = (float)m_rf.watt/10;
	printf("[TX_RF] ");
	printf("> %.1f Watt \r\n", wattF);
	for(int i =0 ;i < 7;i++)
	{
		printf("[%d] %u\r\n", i, (unsigned int)m_rf.rfwattBuff[i]);

	}
	printf("\r\n");
#endif

}
void Debug_Tx_RF_All_Zero_Watt_Printf()
{
#if 1
	printf("[TX_RF] ");
	printf(">Watt Zero Da\r\n");
	for(int i =0 ;i < 7;i++)
	{
		printf("[%d] 0\r\n", i);
	}
	printf("\r\n");
#endif

}

void Debug_Tx_RF_All_Frq_Printf()
{
#if 1
	printf("[TX_RF] ");
	printf(">Frq\r\n");
	for(int i =0 ;i < 7;i++)
	{
		printf("[%d] %u \r\n", i, (unsigned int)m_rf.rfFrqBuff[i]);

	}
	printf("\r\n");
#endif

}
void Debug_Tx_RF_MaxOntime_Printf()
{
#if 1
	printf("[TX_RF] ");
	printf(">MaxOntime = %u\r\n", MAX_ONTIME);
#endif
}
void Debug_Tx_GenStatus_Check_Printf()
{
#if 1
	printf("[TX_RF] ");
	printf("GenStatus_Check\r\n");
#endif
}
void Debug_Tx_FeedBack_Check_Printf()
{
#if 1
	printf("[TX_RF] ");
	printf("FeedBack_Check\r\n");
#endif
}

void Tx_LCD_Msg(uint8_t add, uint16_t data)
{
	while(HAL_GetTick() -m_rf.lastLcdTxTime<20);

	Debug_LCD_Printf(DEBUG_TX, add, data);

	char str[20]={0,};
	sprintf(str,"[%d,%d]\r\n",add, data);
	HAL_UART_Transmit(&huart5, (uint8_t *)str, strlen(str), 100);

	m_rf.lastLcdTxTime = HAL_GetTick();

}

void Tx_LCD_Msg_NoDebug(uint8_t add, uint16_t data)
{
	while(HAL_GetTick() -m_rf.lastLcdTxTime<20);

	char str[20]={0,};
	sprintf(str,"[%d,%d]\r\n",add, data);
	HAL_UART_Transmit(&huart5, (uint8_t *)str, strlen(str), 100);

	m_rf.lastLcdTxTime = HAL_GetTick();

}

void Tx_Hand1_Msg(uint8_t add, uint16_t data)
{
	char str[20];
	while(HAL_GetTick() -m_hand1.lastHPTxTime<20);

	sprintf(str,"[%d,%d]\r\n",add, data);

	Debug_HAND_Printf(DEBUG_TX, add, data);
	HAL_UART_Transmit(&huart2,(uint8_t *)str, strlen(str),100);
	m_hand1.lastHPTxTime = HAL_GetTick();
}


void Tx_RF_Msg(uint8_t* buff, uint8_t len)
{
	while(HAL_GetTick() -m_rf.lastRfGenTxTime<50);
	HAL_UART_Transmit(&huart4,buff, len,100);
#ifdef DEBUG_PRINT
	//Debug_Tx_RF_Printf(buff, len);
#endif
	m_rf.lastRfGenTxTime = HAL_GetTick();
	RF_Rx_Parssing(RF_RX_CALLBACK);

}


void AutoCal_Tx_IP_Msg()
{
	char buff[5] = "IP\r\n";
	HAL_UART_Transmit(&huart3,(uint8_t *)buff, 4,100);
#ifdef DEBUG_PRINT

#endif

}

void AutoCal_Tx_Z_Msg()
{
	char buff[5] = "Z\r\n";
	HAL_UART_Transmit(&huart3,(uint8_t *)buff, 3,100);
	Debug_Printf("Z",1);
#ifdef DEBUG_PRINT

#endif

}

void CMD_Is_All_Live()
{
	uint8_t rxLiveStatus = 0;


	m_hand1.liveChkCnt = 0;
	m_hand1.liveOk = 0;
	for(int i =0 ;i < 3;i++)
	{
		Tx_Hand1_Msg(CMD_DO_ALL_LIVE, 0);
		HAL_Delay(100);
		UartRx2DataProcess();
	}
	if(m_hand1.liveChkCnt >= 2)
	{
		m_hand1.liveOk = 1;
	}

	m_rf.liveChkCnt = 0;
	m_rf.liveOk = 0;
	for(int i =0 ;i < 3;i++)
	{
		Tx_RF_GenStatus_Check();
	}
	if(m_rf.liveChkCnt >= 2)
	{
		m_rf.liveOk = 1;
	}
	if(m_hand1.liveOk == 0 && m_rf.liveOk==0)
	{
		Tx_LCD_Msg(CMD_DO_ALL_LIVE, LIVE_ALL_DETH);
	}
	else
	{
		rxLiveStatus = m_hand1.liveOk*10 + m_rf.liveOk;
		Tx_LCD_Msg(CMD_DO_ALL_LIVE, rxLiveStatus);
	}



}

void HP_Cartrige_Check()
{
	uint8_t family = 0;

		for(int i =0 ;i < 10;i++)
		{
			if(m_eepMain.cartIdBuff[i] == m_eep.catridgeId)
			{
				family = 1;
				break;
			}
		}

		if(m_eep.remainingShotNum == 0)
		{
			Tx_LCD_Msg(CMD_CATRIDGE_EVENT, CART_EVENT_EXPRATION);
		}
		else
		{
			if(family) Tx_LCD_Msg(CMD_CATRIDGE_EVENT, CART_EVENT_DETECT);
			else Tx_LCD_Msg(CMD_CATRIDGE_EVENT, CART_EVENT_DETECT_NEW);
		}
		m_eep.catridgeId = 0;
		m_eep.remainingShotNum = 10000;
}

//static
uint8_t agingCnt, updn;
void Debug_Rx_Parssing(uint8_t add, uint32_t data)
{

	if(add==0)return;
	switch (add)
	{

		case CMD_TEST_PULSE:
			m_rf.testPulseOption++;
			if(m_rf.testPulseOption == 5) m_rf.testPulseOption = 1;
			Tx_LCD_Msg(CMD_TEST_PULSE, m_rf.testPulseOption);
		break;

		case CMD_TEST_FORCE_PAGE_CHANGE:
			LCD_Init();
			Tx_LCD_Msg(CMD_TEST_FORCE_PAGE_CHANGE, data);
		break;

		case CMD_RF_ALL_SETTING:
			Tx_RF_FRQ_ALL_Module();
			Tx_RF_Watt_Zero_ALL_Module();
			TX_RF_Max_Ontime_Set();
		break;

		case CMD_RF_WATT_MEATER_Z:
			AutoCal_Tx_Z_Msg();
		break;

		case CMD_RF_SINGLE_EXP:
			uint8_t tdu = data/1000;
			uint16_t da = data%1000;
			Tx_RF_Watt_Zero_ALL_Module();
			Tx_RF_Watt_Module(tdu, da);
			RF_eg_Exp_On(3000);
		break;
		case CMD_TEMP_DUTY_ON:
			Tx_Hand1_Msg(CMD_TEMP_DUTY_ON, data);
			m_hand1.tempDutyEn = data;
		break;

		case CMD_RF_WATT_MEATER_IP:
			AutoCal_Tx_IP_Msg();
		break;

		case CMD_AUTO_CAL_START:
			m_rf.autoCalFlag = data;
			if(data==1)
			{
				TX_RF_Max_Ontime_Set();
				Tx_RF_FRQ_ALL_Module();
				Tx_RF_Watt_Zero_ALL_Module();
				Debug_Printf("Autocal Start",1);
			}
			else Debug_Printf("Autocal End",1);

		break;


		case CMD_DEBUG_PUMP:
			if(data) WaterPump_Pwr_ON();
			else WaterPump_Pwr_OFF();
		break;

		case CMD_DEBUG_CHILLER:
			if(data) Ciller_Pwr_ON();
			else Ciller_Pwr_OFF();
		break;

		case CMD_DEBUG_PELTIER:
			Tx_Hand1_Msg(CMD_HP1_ADD, data);
		break;

		case CMD_WATT_FEEDBACK:
//			Tx_RF_FeedBack_Check();
			m_rf.feedBackTest = data;
			Debug_Printf("CMD_WATT_FEEDBACK START",1);
		break;


		case CMD_FRQ_CH0:
			m_rf.rfFrqBuff[RF_FRQ_CH0] = data;
			Tx_RF_FRQ_Module(RF_FRQ_CH0, data);
		break;

		case CMD_FRQ_CH1:
			m_rf.rfFrqBuff[RF_FRQ_CH1] = data;
			Tx_RF_FRQ_Module(RF_FRQ_CH1, data);
		break;

		case CMD_FRQ_CH2:
			m_rf.rfFrqBuff[RF_FRQ_CH2] = data;
			Tx_RF_FRQ_Module(RF_FRQ_CH2, data);
		break;

		case CMD_FRQ_CH3:
			m_rf.rfFrqBuff[RF_FRQ_CH3] = data;
			Tx_RF_FRQ_Module(RF_FRQ_CH3, data);
		break;

		case CMD_FRQ_CH4:
			m_rf.rfFrqBuff[RF_FRQ_CH4] = data;
			Tx_RF_FRQ_Module(RF_FRQ_CH4, data);
		break;

		case CMD_FRQ_CH5:
			m_rf.rfFrqBuff[RF_FRQ_CH5] = data;
			Tx_RF_FRQ_Module(RF_FRQ_CH5, data);
		break;

		case CMD_FRQ_CH6:
			m_rf.rfFrqBuff[RF_FRQ_CH6] = data;
			Tx_RF_FRQ_Module(RF_FRQ_CH6, data);
		break;

		case CMD_AGING_BUTTON:
			if(data<=30)
			{
				Tx_LCD_Msg(CMD_AGING_BUTTON, data);
				printf("Aging Button %d\r\n",data);
			}
			else
			{
				m_rf.agingUpDn = data%100;
				m_rf.agingCnt = data/100;
			}

		break;

		case CMD_AUTO_EXP:
			testExpFlag  = 1;
			printf("Auto Exp\r\n");
		break;


	}


}



void LCD_Rx_Parssing(uint8_t add, uint32_t data)
{



	if(add==0)return;
	Debug_LCD_Printf(DEBUG_RX, add, data);

	if(m_rf.treatStatus == STATUS_TRET)
	{
		if(add != CMD_LCD_STATUS)
		{
			m_rf.treatStatus = STATUS_STNBY;
			m_rf.readyFlag = READY_OFF;
			Tx_LCD_Msg(CMD_LCD_STATUS, STATUS_STNBY);
		}
	}
	switch (add)
	{
		case CMD_ENERGY:
			if(data == BUTTON_UP)
			{
				if(m_rf.energy<MAX_ENERGY)
				{
					float wattF = ((float)(m_rf.energy+1) /(float)m_rf.pulseDuration);
					uint8_t wattRange = (0.1 <= wattF && wattF <= 1.0);
					if(wattRange)
					{
						m_rf.energy++;
					}
				}
			}
			else if(data == BUTTON_DN)
			{
				if(m_rf.energy>0)
				{
					float wattF = ((float)(m_rf.energy-1) /(float)m_rf.pulseDuration);
					uint8_t wattRange = (0.1 <= wattF && wattF <= 1.0);
					if(wattRange)
					{
						m_rf.energy--;
					}
				}
			}
			Tx_LCD_Msg(CMD_ENERGY, m_rf.energy);
		break;

		case CMD_PULSE_DURATION:
			if(data == BUTTON_UP)
			{
				if(m_rf.pulseDuration<MAX_PULSE_DURATION)
				{
					float wattF = ((float)(m_rf.energy) /(float)(m_rf.pulseDuration+1));
					uint8_t wattRange = (0.1 <= wattF && wattF <= 1.0);
					if(wattRange)
					{
						m_rf.pulseDuration++;
					}
				}
			}
			else if(data == BUTTON_DN)
			{
				if(m_rf.pulseDuration>0)
				{
					float wattF = ((float)(m_rf.energy) /(float)(m_rf.pulseDuration-1));
					uint8_t wattRange = (0.1 <= wattF && wattF <= 1.0);
					if(wattRange)
					{
						m_rf.pulseDuration--;
					}
				}
			}
			Tx_LCD_Msg(CMD_PULSE_DURATION, m_rf.pulseDuration);

		break;

		case CMD_POST_COOLING:

			if(data == BUTTON_UP&& m_rf.postCooling<MAX_POST_COOLING)
				m_rf.postCooling++;
			else if(data == BUTTON_DN&& m_rf.postCooling>0)
				m_rf.postCooling--;
			Tx_LCD_Msg(CMD_POST_COOLING, m_rf.postCooling);
		break;

		case CMD_INTERVAL:

			if(data == BUTTON_UP&& m_rf.interval<MAX_INTERVAL)
				m_rf.interval++;
			else if(data == BUTTON_DN&& m_rf.interval>0)
				m_rf.interval--;

			if(m_rf.interval==0)
			{
				m_rf.testPulseOption = 1;
				Tx_LCD_Msg(CMD_TEST_PULSE, m_rf.testPulseOption);
			}

			Tx_LCD_Msg(CMD_INTERVAL, m_rf.interval);
		break;

		case CMD_CURRENT_SHOT:
			if(data==0)
			{
				m_rf.currentShot = 0;
				Tx_LCD_Msg(CMD_CURRENT_SHOT, m_rf.currentShot);
			}
		break;

		case CMD_TOTAL_JOULE:
			if(data==0)
			{
				m_rf.totaEnergy = 0;
				Tx_LCD_Msg(CMD_TOTAL_JOULE, m_rf.totaEnergy);
			}
		break;

		case CMD_REMIND_SHOT:
			m_eep.remainingShotNum = data;
			Tx_LCD_Msg(CMD_REMIND_SHOT, data);
			Tx_Hand1_Msg(CMD_REMIND_SHOT, data);
		break;

		case CMD_WATT_CH0:
			m_rf.rfwattBuff[RF_WATT_CH0] = data;
			Tx_RF_Watt_Module(RF_WATT_CH0, data);
		break;

		case CMD_WATT_CH1:
			m_rf.rfwattBuff[RF_WATT_CH1] = data;
			Tx_RF_Watt_Module(RF_WATT_CH1, data);
		break;

		case CMD_WATT_CH2:
			m_rf.rfwattBuff[RF_WATT_CH2] = data;
			Tx_RF_Watt_Module(RF_WATT_CH2, data);
		break;

		case CMD_WATT_CH3:
			m_rf.rfwattBuff[RF_WATT_CH3] = data;
			Tx_RF_Watt_Module(RF_WATT_CH3, data);
		break;

		case CMD_WATT_CH4:
			m_rf.rfwattBuff[RF_WATT_CH4] = data;
			Tx_RF_Watt_Module(RF_WATT_CH4, data);
		break;

		case CMD_WATT_CH5:
			m_rf.rfwattBuff[RF_WATT_CH5] = data;
			Tx_RF_Watt_Module(RF_WATT_CH5, data);
		break;

		case CMD_WATT_CH6:
			m_rf.rfwattBuff[RF_WATT_CH6] = data;
			Tx_RF_Watt_Module(RF_WATT_CH6, data);
		break;

		case CMD_PLUSE_NUM:
			if(data == 0 ||data > 12 ) break;
			m_rf.pulseNum = data;
		break;

		case CMD_PLUSE_EN:
			if(data == 0 || data > 4) break;
			uint8_t endisValue;
			if(m_rf.pulseEndisBuff[data])
			{
				m_rf.pulseEndisBuff[data] = 0;
			}
			else
			{
				m_rf.pulseEndisBuff[data] = 1;
			}

			endisValue = data*10 + m_rf.pulseEndisBuff[data];
			Tx_LCD_Msg(CMD_PLUSE_EN, endisValue);
			CurrentEnergy_Cal();
		break;


		case CMD_PLUSE_BTN_UP_DN:
			uint16_t pulseData = 0;
			if(m_rf.pulseNum == 0 ||m_rf.pulseNum > 12 ) break;
			if(data == BUTTON_UP)
			{
				if(m_rf.pulseBuff[m_rf.pulseNum]< m_rf.pulseMaxBuff[m_rf.pulseNum])
				{
					m_rf.pulseBuff[m_rf.pulseNum]++;
				}
			}
			else if(data == BUTTON_DN)
			{
				if(m_rf.pulseBuff[m_rf.pulseNum]>m_rf.pulseMinBuff[m_rf.pulseNum])
				{
					m_rf.pulseBuff[m_rf.pulseNum]--;
				}
			}
			pulseData = m_rf.pulseNum*100 + m_rf.pulseBuff[m_rf.pulseNum];
			Tx_LCD_Msg(CMD_PLUSE_VALUE, pulseData);
			CurrentEnergy_Cal();
		break;

		case CMD_TEST_FORCE_PAGE_CHANGE:
			LCD_Init();
			Tx_LCD_Msg(CMD_TEST_FORCE_PAGE_CHANGE, data);
		break;

		case CMD_CALIV_SHOT:

			TX_RF_Max_Ontime_Set();
			Tx_RF_FRQ_ALL_Module();
			RF_eg_Exp_On(data*100);
		break;

		case CMD_OK:
			switch (data)
			{
				case ERR_CHK_MAIN:
					Error_Buff_Main_Tx();
				break;
				case ERR_CHK_HP:
					Error_Buff_HP_Tx();
				break;
				case ERR_CHK_RF:
					Error_Buff_Rf_Tx();
				break;
			}
		break;

		case CMD_CART_ID:
			m_eep.catridgeId = data;
			Tx_LCD_Msg(CMD_CART_ID, data);
			Tx_Hand1_Msg(CMD_CART_ID, data);
		break;
		case CMD_MANUFAC_YY:
			m_eep.manufacYY = data;
			Tx_LCD_Msg(CMD_MANUFAC_YY, data);
			Tx_Hand1_Msg(CMD_MANUFAC_YY, data);
		break;

		case CMD_MANUFAC_MM:
			m_eep.manufacMM = data;
			Tx_LCD_Msg(CMD_MANUFAC_MM, data);
			Tx_Hand1_Msg(CMD_MANUFAC_MM, data);
		break;

		case CMD_MANUFAC_DD:
			m_eep.manufacDD = data;
			Tx_LCD_Msg(CMD_MANUFAC_DD, data);
			Tx_Hand1_Msg(CMD_MANUFAC_DD, data);
		break;

		case CMD_ISSUED_YY:
			m_eep.issuedYY = data;
			Tx_LCD_Msg(CMD_ISSUED_YY, data);
			Tx_Hand1_Msg(CMD_ISSUED_YY, data);
		break;

		case CMD_ISSUED_MM:
			m_eep.issuedMM= data;
			Tx_LCD_Msg(CMD_ISSUED_MM, data);
			Tx_Hand1_Msg(CMD_ISSUED_MM, data);
		break;

		case CMD_ISSUED_DD:
			m_eep.issuedDD= data;
			Tx_LCD_Msg(CMD_ISSUED_DD, data);
			Tx_Hand1_Msg(CMD_ISSUED_DD, data);
		break;

		case CMD_DAY_REQ:
			Tx_LCD_Msg(CMD_DAY_REQ, data);
			Tx_Hand1_Msg(CMD_DAY_REQ, data);
		break;

		case CMD_RTC:
			Tx_LCD_Msg(CMD_RTC, data);
			Tx_Hand1_Msg(CMD_RTC, data);
		break;

		case CMD_INFO_UI_DESING:
			m_io.infoUiDesing = data;
		break;

		case CMD_INFO_UI_FW:
			m_io.infoUiFw = data;
		break;

		case CMD_INFO_MAIN_FW:
			m_io.infoMainFw = data;
		break;

		case CMD_INFO_HP_FW:
			m_io.infoHPFw = data;
		break;

		case CMD_INFO_RF_FW:
			m_io.infoRfFw = data;
		break;

		case CMD_RTC_YY:
			m_io.YY = data;
			Tx_LCD_Msg(CMD_RTC_YY, m_io.YY);
			DS1308_SetParts(RTC_REG_YY, m_io.YY);
		break;

		case CMD_RTC_MM:
			m_io.MM = data;
			Tx_LCD_Msg(CMD_RTC_MM, m_io.MM);
			DS1308_SetParts(RTC_REG_MM, m_io.MM);
		break;

		case CMD_RTC_DD:
			m_io.DD = data;
			Tx_LCD_Msg(CMD_RTC_DD, m_io.DD);
			DS1308_SetParts(RTC_REG_DD, m_io.DD);
		break;

		case CMD_RTC_HOUR:
			m_io.hour = data;
			Tx_LCD_Msg(CMD_RTC_HOUR, m_io.hour);
			DS1308_SetParts(RTC_REG_HOUR, m_io.hour);
		break;

		case CMD_RTC_MIN:
			m_io.min = data;
			Tx_LCD_Msg(CMD_RTC_MIN, m_io.min);
			DS1308_SetParts(RTC_REG_MIN, m_io.min);
		break;

		case CMD_RTC_SEC:
			m_io.sec = data;
			Tx_LCD_Msg(CMD_RTC_SEC, m_io.sec);
			DS1308_SetParts(RTC_REG_SEC, m_io.sec);
		break;

		case CMD_RTC_EN:
			m_io.rtcEn = data;
		break;

		case CMD_CART_ALLOW:
			if(data==1)
			{
				m_eep.issuedYY = m_io.YY;
				m_eep.issuedMM = m_io.MM;
				m_eep.issuedDD = m_io.DD;
				Tx_Hand1_Msg(CMD_ISSUED_YY, m_eep.issuedYY);
				Tx_Hand1_Msg(CMD_ISSUED_MM, m_eep.issuedMM);
				Tx_Hand1_Msg(CMD_ISSUED_DD, m_eep.issuedDD);
				Tx_LCD_Msg(CMD_ISSUED_YY, m_eep.issuedYY);
				Tx_LCD_Msg(CMD_ISSUED_MM, m_eep.issuedMM);
				Tx_LCD_Msg(CMD_ISSUED_DD, m_eep.issuedDD);

				m_eep.cartAllow = 1;
				Tx_Hand1_Msg(CMD_CART_ALLOW, 1);
			}
		break;

		case CMD_SYS_CHK:
			Tx_LCD_Msg(CMD_SYS_CHK, data);
			CARTRIGE_REQ_DATA(data);
			m_rf.sysChkFlag = 1;
		break;

		case CMD_LCD_STATUS:
			if(data == STATUS_PRECOOLING)
			{
				m_rf.preCooltime = HAL_GetTick();
				m_rf.treatStatus = data;
				Tx_LCD_Msg(CMD_LCD_STATUS, data);
			}
			else if(data == STATUS_STNBY)
			{
				m_rf.readyFlag = READY_OFF;
				m_rf.treatStatus = data;
				Tx_LCD_Msg(CMD_LCD_STATUS, data);
			}



		break;

		case CMD_INFOMATION:
			Tx_LCD_Msg(CMD_INFO_UI_DESING, m_io.infoUiDesing);
			Tx_LCD_Msg(CMD_INFO_UI_FW, m_io.infoUiFw);
			Tx_LCD_Msg(CMD_INFO_MAIN_FW, m_io.infoMainFw);
			Tx_LCD_Msg(CMD_INFO_HP_FW, m_io.infoHPFw);
			Tx_LCD_Msg(CMD_INFO_RF_FW, m_io.infoRfFw);
			Tx_LCD_Msg(CMD_RTC_YY, m_io.YY);
			Tx_LCD_Msg(CMD_RTC_MM, m_io.MM);
			Tx_LCD_Msg(CMD_RTC_DD, m_io.DD);
			Tx_LCD_Msg(CMD_RTC_HOUR, m_io.hour);
			Tx_LCD_Msg(CMD_RTC_MIN, m_io.min);
			Tx_LCD_Msg(CMD_RTC_SEC, m_io.sec);
		break;

		case CMD_DEVICE_STATUS:
			m_err.statusTx = data;
		break;

		case CMD_ERR_EVENT:
			uint16_t txErrData;//1000~50999 ÃæºÐ
			if (data)
			{
				for(int i =1 ;i < 42;i++)
				{
					txErrData = i*1000 + m_eepMain.errCntBuff[i];
					Tx_LCD_Msg(CMD_ERR_EVENT, txErrData);
				}
			}
		break;

		case CMD_DO_ALL_LIVE:
			CMD_Is_All_Live();
		break;

		case CMD_GET_ALL_CART:
			Tx_Hand1_Msg(CMD_GET_ALL_CART, 0);
		break;

		case CMD_GET_ALL_CART_END:
			Debug_Printf("lcd all cart Recive",1);
			Tx_Hand1_Msg(CMD_GET_ALL_CART_END, 0);

		break;

		case CMD_AUTO_CAL_START:
			m_rf.autoCalFlag = data;
			if(data==1)
			{
				TX_RF_Max_Ontime_Set();
				Tx_RF_FRQ_ALL_Module();
				Debug_Printf("Autocal Start",1);
				HAL_Delay(1000);
			}
			else Debug_Printf("Autocal End",1);

		break;

		case CMD_GET_WATT_CART:
			Tx_Hand1_Msg(CMD_GET_WATT_CART, 1);
		break;


		case CMD_TEMP_DUTY_ON:
			Tx_Hand1_Msg(CMD_TEMP_DUTY_ON, data);
			m_hand1.tempDutyEn = data;
		break;

		case CMD_TEST_PULSE:
			m_rf.testPulseOption++;
			if(m_rf.testPulseOption == 5) m_rf.testPulseOption = 1;

			Tx_LCD_Msg(CMD_TEST_PULSE, m_rf.testPulseOption);

			if(m_rf.testPulseOption == 1)
			{
				m_rf.interval = 0;
				Tx_LCD_Msg(CMD_INTERVAL, m_rf.interval);
			}


		break;

		case CMD_VIBE_LEVEL:
			m_rf.vibeLevel++;
			m_rf.vibeLevel %= 5;
			Tx_LCD_Msg(CMD_VIBE_LEVEL, m_rf.vibeLevel);
		break;


		default:
			uint16_t reqAdd, reqData;
			if(data == REQ_DATA)
			{
				if(CMD_TRANDU1_FRQ <= add && add <= CMD_TRANDU7_FRQ)
				{
					reqAdd = add - CMD_TRANDU_FRQ_BASE;
					reqData = m_eep.rfFrqBuff[reqAdd];
					Tx_LCD_Msg(add, reqData);
				}
				else if(CMD_TRANDU1_WATT10 <= add && add <=CMD_TRANDU7_WATT005)
				{
					reqAdd = add-CMD_TRANDU_WATT_BASE;
					reqData = m_eep.rfWattBuff[reqAdd];
					Tx_LCD_Msg(add, reqData);
				}

			}
			else
			{
				if(CMD_TRANDU1_FRQ <= add && add <=CMD_TRANDU7_FRQ)
				{
					m_eep.rfFrqBuff[add-CMD_TRANDU_FRQ_BASE] = data;
					Tx_Hand1_Msg(add, data);
				}
				else if(CMD_TRANDU1_WATT10 <= add && add <=CMD_TRANDU7_WATT005)
				{
					reqAdd = add-CMD_TRANDU_WATT_BASE;
					m_eep.rfWattBuff[reqAdd] = data;
					Tx_Hand1_Msg(add, data);
				}
			}

		break;



	}
}


void Hand_Rx_Parssing(uint8_t add, uint32_t data, uint32_t data2, uint32_t data3, uint32_t data4 )
{
	if(add !=0)
	{
		if(add != CMD_HP1_ADD)
		{
			Debug_HAND_Printf(DEBUG_RX, add, data);
		}
		switch (add)
		{
			case CMD_HP1_ADD:
				m_err.handTimeout = 0;
				m_err.handComuErr = 0;
				Hand1_Poling_Ctrl(CMD_HP1_ADD,data, data2, data3, data4);
			break;

			case CMD_CART_ID:
				m_eep.catridgeId = data;
				if(m_eep.cartAllow)
				{
					for(int i =0 ;i < 10;i++)
					{
						if(m_eepMain.cartIdBuff[i] == 0)
						{
							m_eepMain.cartIdBuff[i] = data;
							Eeprom_Byte_Write(i+1, data);
							break;
						}
					}
					Tx_LCD_Msg(CMD_CART_ID, data);
				}

			break;

			case CMD_MANUFAC_YY:
				m_eep.manufacYY = data;
				Tx_LCD_Msg(CMD_MANUFAC_YY, data);
			break;

			case CMD_MANUFAC_MM:
				m_eep.manufacMM = data;
				Tx_LCD_Msg(CMD_MANUFAC_MM, data);
			break;

			case CMD_MANUFAC_DD:
				m_eep.manufacDD = data;
				Tx_LCD_Msg(CMD_MANUFAC_DD, data);
			break;

			case CMD_ISSUED_YY:
				m_eep.issuedYY = data;
				Tx_LCD_Msg(CMD_ISSUED_YY, data);
			break;

			case CMD_ISSUED_MM:
				m_eep.issuedMM = data;
				Tx_LCD_Msg(CMD_ISSUED_MM, data);
			break;

			case CMD_ISSUED_DD:
				m_eep.issuedDD = data;
				Tx_LCD_Msg(CMD_ISSUED_DD, data);
			break;

			case CMD_REMIND_SHOT:
				m_eep.remainingShotNum = data;
				if(m_eep.cartAllow) Tx_LCD_Msg(CMD_REMIND_SHOT, data);

			break;

			case CMD_CATRIDGE_STATUS:
				m_eep.catridgeStatus = data;
				//ï¿½Ö¾ï¿½ï¿½ï¿½ï¿?
			break;

			case CMD_CATRIDGE_EVENT:
				if(data == CATRIGE_DETECT)
				{
					 HP_Cartrige_Check();
				}
				else
				{
					Tx_LCD_Msg(CMD_CATRIDGE_EVENT, CART_EVENT_UNDETECT);
				}

				m_eep.catridgeDetect = data;
				//ï¿½Ö¾ï¿½ï¿½ï¿½ï¿?
			break;

			case CMD_CART_ALLOW:
				if(data==0) m_eep.cartAllow = 0;
			break;


			case CMD_DO_ALL_LIVE:
				m_hand1.liveChkCnt++;
				//ï¿½Ö¾ï¿½ï¿½ï¿½ï¿?
			break;

			case CMD_GET_ALL_CART_END:
				uint8_t eepErr = 0;
				if(!m_eep.catridgeId)eepErr++;
				if(!m_eep.manufacYY)eepErr++;
				if(!m_eep.manufacMM)eepErr++;
				if(!m_eep.manufacDD)eepErr++;
				if(!m_eep.issuedYY)eepErr++;
				if(!m_eep.issuedMM)eepErr++;
				if(!m_eep.issuedDD)eepErr++;
				if(!m_eep.remainingShotNum)eepErr++;
//				for(int i =1 ;i <= 7;i++)
//				{
//					if(!m_eep.rfFrqBuff[i])eepErr++;
//				}
//				for(int i =1 ;i <= 77;i++)
//				{
//					if(!m_eep.rfWattBuff[i])eepErr++;
//				}
				if(eepErr==0)
				{
					LCD_Init();
					Tx_LCD_Msg(CMD_GET_ALL_CART_END, 1);
					Debug_Printf("CartAllOk",1);
//					m_err.txEn = 1;
					m_hand1.cartAllOk = 1;
				}
				else
				{
					m_eep.catridgeRxErrCnt++;
					if(m_eep.catridgeRxErrCnt<3)
					{
						HAL_Delay(1000);
						Debug_Printf("CartErrReCall",1);
						Tx_Hand1_Msg(CMD_GET_ALL_CART, 0);
						m_hand1.cartAllOk = 2;
					}
					else
					{
						Debug_Printf("Cart Fail",1);
						m_hand1.cartAllOk = 3;
						m_err.handComuErr = 1;
//						m_err.txEn = 1;
					}

				}


			break;

			default:
				if(CMD_TRANDU1_FRQ <= add && add <=CMD_TRANDU7_FRQ)
				{
					m_eep.rfFrqBuff[add-CMD_TRANDU_FRQ_BASE] = data;
					Tx_LCD_Msg(add, data);
				}
				else if(CMD_TRANDU1_WATT10 <= add && add <=CMD_TRANDU7_WATT005)
				{
					m_eep.rfWattBuff[add -CMD_TRANDU_WATT_BASE] = data;
					Tx_LCD_Msg(add, data);
				}

			break;

		}

	}


}



void UartRx1DataProcess()
{
	if(m_uart1.rxCmdChk == 0x0000)return;

	for(int i =0 ;i < 10;i++)
	{
		if(m_uart1.rxCmdAdd[i] !=0)
		{
			Debug_Rx_Parssing(m_uart1.rxCmdAdd[i],m_uart1.rxCmdData[i]);
			m_uart1.rxCmdAdd[i] = 0;
			m_uart1.rxCmdData[i] = 0;
			m_uart1.rxCmdChk &= ~(1<<i);
		}

	}
}

void UartRx2DataProcess()
{
	if(m_uart2.rxCmdChk == 0x0000)return;
	for(int i =0 ;i < 10;i++)
	{
		if(m_uart2.rxCmdAdd[i] !=0)
		{
			Hand_Rx_Parssing(m_uart2.rxCmdAdd[i], m_uart2.rxCmdData[i], m_uart2.rxCmdData2[i], m_uart2.rxCmdData3[i], m_uart2.rxCmdData4[i]);

			m_uart2.rxCmdAdd[i] = 0;
			m_uart2.rxCmdData[i] = 0;
			m_uart2.rxCmdData2[i] = 0;
			m_uart2.rxCmdData3[i] = 0;
			m_uart2.rxCmdData4[i] = 0;
			m_uart2.rxCmdChk &= ~(1<<i);
		}
	}
}

void UartRx4DataProcess()
{
	RF_Rx_Parssing(RF_RX_COMMON);
}
void UartRx5DataProcess()
{
	if(m_uart5.rxCmdChk == 0x0000)return;

	for(int i =0 ;i < 10;i++)
	{
		if(m_uart5.rxCmdAdd[i] !=0)
		{
			LCD_Rx_Parssing(m_uart5.rxCmdAdd[i], m_uart5.rxCmdData[i]);
			m_uart5.rxCmdAdd[i] = 0;
			m_uart5.rxCmdData[i] = 0;
			m_uart5.rxCmdChk &= ~(1<<i);
		}

	}


}

void Uart_Tx_Polling_Status()
{
	static uint32_t timeStamp, timeStamp2;

	if(m_hand1.tempDutyEn == 1)
	{
		if(HAL_GetTick()-timeStamp >= 1000)
		{
			Tx_LCD_Msg_NoDebug(CMD_TEMPERATURE_SHOT, m_hand1.temprature);
			Tx_LCD_Msg_NoDebug(CMD_PELTIER_DUTY, m_hand1.pwmDuty);
			timeStamp = HAL_GetTick();
		}
	}
	if(m_err.statusTx)
	{

		if(HAL_GetTick()-timeStamp2 >= 1000)
		{
			uint16_t txData;
			txData = 1000 + m_hand1.temprature;
			Tx_LCD_Msg(CMD_DEVICE_STATUS, txData);
			txData = 3000 + m_err.handTimeout;
			Tx_LCD_Msg(CMD_DEVICE_STATUS, txData);
			txData = 4000 + m_err.rfTimeout;
			Tx_LCD_Msg(CMD_DEVICE_STATUS, txData);
			txData = 5000 + m_err.rfStatus;
			Tx_LCD_Msg(CMD_DEVICE_STATUS, txData);
			txData = 6000 + m_io.battery*10;
			Tx_LCD_Msg(CMD_DEVICE_STATUS, txData);
			txData = 7000 + m_io.flowSensorFrq;
			Tx_LCD_Msg(CMD_DEVICE_STATUS, txData);
			txData = 8000 + m_io.level1Status;
			Tx_LCD_Msg(CMD_DEVICE_STATUS, txData);
			timeStamp2 = HAL_GetTick();
		}

	}
	if(m_rf.agingCnt)
	{
		static uint32_t timeStamp;

		if(HAL_GetTick()-timeStamp >= 200)
		{
			timeStamp = HAL_GetTick();
			Tx_LCD_Msg(CMD_AGING_BUTTON, m_rf.agingUpDn);
			printf("Aging Button %d\r\n",m_rf.agingUpDn);
			m_rf.agingCnt--;
		}
	}
}

void UartRxDataProcess()
{
	if(m_rf.pluseOn) return;
	UartRx1DataProcess();
	UartRx2DataProcess();//hp
	UartRx4DataProcess();//gen
	UartRx5DataProcess();//lcd
	Uart_Tx_Polling_Status();
}



#if 0
void Uart_Passing_org(UART_T* uart, uint8_t* ptr)//stm32ï¿½ï¿½
{
	int i = 0;
	uint16_t commaCnt = 0;
	for(i =0 ;i < RX_BUFF_SIZE;i++)
	{
		if(uart->rxBuff[i] == ',')commaCnt++;
	}

	char* ptrStart = strchr((char*)(uart->rxBuff),'[');
	char* ptrEnd = strrchr ((char*)(uart->rxBuff),']');

	if(ptrStart !=NULL && ptrEnd !=NULL)
	{
		if(commaCnt ==4)
			sscanf(ptr,"[%d,%d,%d,%d,%d]",&(uart->rxCmdAdd),&(uart->rxCmdData),&(uart->rxCmdData2),&(uart->rxCmdData3),&(uart->rxCmdData4));
		else if(commaCnt ==1)
			sscanf(ptr,"[%d,%d]",&(uart->rxCmdAdd),&(uart->rxCmdData));

	}
	else
	{
//		ERR_FUC_LINE();
		printf("%s \r\n",uart->rxBuff);
	}

	Rx_BuffClear(uart);
}

#endif

void Uart_Passing(UART_T* uart, uint8_t* ptr)//stm32ï¿½ï¿½
{
	int i = 0;
	uint8_t rxRingCnt = 0;
	uint16_t commaCnt = 0;
	for(i =0 ;i < RX_BUFF_SIZE;i++)
	{
		if(uart->rxBuff[i] == ',')commaCnt++;
	}

	char* ptrStart = strchr((char*)(uart->rxBuff),'[');
	char* ptrEnd = strrchr ((char*)(uart->rxBuff),']');

	rxRingCnt = uart->rxCmdRingCnt;

	if(ptrStart !=NULL && ptrEnd !=NULL)
	{
		uart->rxCmdChk |= 1<< (uart->rxCmdRingCnt);

		if(commaCnt ==4)
			sscanf(ptr,"[%d,%d,%d,%d,%d]",&(uart->rxCmdAdd[rxRingCnt]),&(uart->rxCmdData[rxRingCnt]),&(uart->rxCmdData2[rxRingCnt]),&(uart->rxCmdData3[rxRingCnt]),&(uart->rxCmdData4[rxRingCnt]));
		else if(commaCnt ==1)
			sscanf(ptr,"[%d,%d]",&(uart->rxCmdAdd[rxRingCnt]),&(uart->rxCmdData[rxRingCnt]));

		if(uart->rxCmdRingCnt< 9)uart->rxCmdRingCnt++;
		else uart->rxCmdRingCnt = 0;


	}
	else
	{
//		ERR_FUC_LINE();
		printf("%s \r\n",uart->rxBuff);
	}

	Rx_BuffClear(uart);
}


void Uart3_Passing(uint8_t data)//stm32ï¿½ï¿½
{
	float FeedBackWtemp;
	if(data == '\n')
	{
		FeedBackWtemp = atof(m_uart3.rxBuff);
		FeedBackWtemp = FeedBackWtemp*100.0;
//		if(0< FeedBackWtemp&&FeedBackWtemp<=4000000)//4w max
		{
			m_rf.FeedBackW = FeedBackWtemp;
			m_rf.FeedBackWBuff[m_rf.FeedBackCnt] = m_rf.FeedBackW;
			m_rf.FeedBackCnt++;
			m_rf.FeedBackCnt %= 70;
		}

		Rx_BuffClear(&m_uart3);
	}
	else
	{
		m_uart3.rxBuff[m_uart3.rxCnt] = data;
		m_uart3.rxCnt++;
		m_uart3.rxCnt %= RX_BUFF_SIZE;
	}

}


void Uart_Passing_STX_ETX_Config(UART_T* uart, uint8_t data, char startChar, char endChar)
{
	if(Uart_RxBuff_Get(uart, data, startChar, endChar))
	{
		Uart_Passing(uart, uart->rxBuff);
	}
}

uint8_t ddQ[5];
void TxTest()
{
	if(dd.d1)
	{
		dd.d1 = 0;
		MX_UART5_Init();
	}
}
void Uart_RxBuff_View(UART_T* uart, uint8_t data)
{
	uart->rxViewBuff[uart->rxViewCnt++] = data;
	uart->rxViewCnt %= RX_BUFF_SIZE;
}


void Uart_ClearCharBuff(uint8_t* buff, uint16_t*cnt, int size)
{
	memset(buff, 0, size);
	*cnt = 0;
}




void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

	 if (huart == &huart1)//debug
	 {
		HAL_UART_Receive_IT(&huart1, Rx_data1, 1);
		Uart_RxBuff_View(&m_uart1, Rx_data1[0]);
		Uart_Passing_STX_ETX_Config(&m_uart1, Rx_data1[0],'[', ']');//lcdtemp test

	 }
	 else if (huart == &huart2)
	 {
		HAL_UART_Receive_IT(&huart2, Rx_data2, 1);
		Uart_RxBuff_View(&m_uart2, Rx_data2[0]);
		 Uart_Passing_STX_ETX_Config(&m_uart2, Rx_data2[0],'[', ']');
	 }
	 else if (huart == &huart3)
	 {
		HAL_UART_Receive_IT(&huart3, Rx_data3, 1);
		Uart_RxBuff_View(&m_uart3, Rx_data3[0]);
		Uart3_Passing(Rx_data3[0]);
	 }
	 else if (huart == &huart4)
	 {
		HAL_UART_Receive_IT(&huart4, Rx_data4, 1);
		Uart_RxBuff_View(&m_uart4, Rx_data4[0]);
		Rx_RF_Get(Rx_data4[0]);//

	 }
	 else if (huart == &huart5)
	 {
		HAL_UART_Receive_IT(&huart5, Rx_data5, 1);
		Uart_RxBuff_View(&m_uart5, Rx_data5[0]);
	 	Uart_Passing_STX_ETX_Config(&m_uart5, Rx_data5[0],'[', ']');
	 }

}



void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)//485
{
	if(huart == &huart2)
	{
//		HAL_GPIO_WritePin(RS485_EN_GPIO_Port, RS485_EN_Pin, GPIO_PIN_RESET);//485
	}

}

extern uint32_t readRfidID;
void Uart_Gulobal()
{
	if(m_uart2.clearFlag1)
	{
		m_uart2.clearFlag1 = 0;
		Uart_ClearCharBuff(m_uart2.rxBuff,&m_uart2.rxCnt ,RX_BUFF_SIZE);
	}

	if(m_uart2.clearFlag2)
	{
		m_uart2.clearFlag2 = 0;
		Uart_ClearCharBuff(m_uart2.rxViewBuff,&m_uart2.rxViewCnt ,RX_BUFF_SIZE);
	}


}



