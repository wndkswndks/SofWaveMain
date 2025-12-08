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
		uart->rxCnt%=RX_BUFF_SIZE;
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

void Debug_Printf(uint8_t* str, uint8_t cr)
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
	printf("[%s] HAND [%u,%u]\r\n",rxtxStr[rxtx], cmd, data);

#endif

}

void Debug_LCD_Printf(uint8_t rxtx, uint8_t cmd, uint16_t data)
{
#ifdef DEBUG_PRINT
	if(rxtx != DEBUG_RX && rxtx != DEBUG_TX) return;
	char rxtxStr[2][3] = {"Rx","Tx"};
	printf("[%s] LCD [%u,%u]\r\n",rxtxStr[rxtx], cmd, data);

#endif

}


void Debug_Rx_RF_Printf(uint8_t* buff)
{
#if 1
	printf("Rf rx :");
	printf("%02X %02X %02X %02X %02X %02X %02X\r\n",buff[0], buff[1], buff[2], buff[3], buff[4], buff[5], buff[6] );
#endif

}
void Debug_Tx_RF_Printf(uint8_t* buff,uint8_t len)
{
#if 0

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
	printf("Ch[%u] Watt[%u] \r\n",ch, watt);

#endif

}
void Debug_Tx_RF_Frq_Printf(uint8_t ch, uint16_t frq)
{
#if 1
	printf("Ch[%u] Frq[%u] \r\n",ch, frq);
#endif

}


void Debug_Tx_RF_All_Watt_Printf()
{
#if 1
	float wattF = (float)m_rf.watt/10;
	printf("> %.1f Watt \r\n", wattF);
	for(int i =0 ;i < 7;i++)
	{
		printf("[%d] %u\r\n", i, m_rf.rfwattBuff[i]);

	}
	printf("\r\n");
#endif

}
void Debug_Tx_RF_All_Zero_Watt_Printf()
{
#if 1
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
	printf(">Frq\r\n");
	for(int i =0 ;i < 7;i++)
	{
		printf("[%d] %u \r\n", i, m_rf.rfFrqBuff[i]);

	}
	printf("\r\n");
#endif

}
void Debug_Tx_RF_MaxOntime_Printf()
{
#if 1
	printf(">MaxOntime = %u\r\n", MAX_ONTIME);
#endif
}
void Debug_Tx_GenStatus_Check_Printf()
{
#if 1
	printf("GenStatus_Check\r\n");
#endif
}

uint8_t lcdTxMsg[7] = {0x5B, 0x00, 0x2C, 0x00, 0x2C, 0x00, 0x5D};
void Tx_LCD_Msg(uint8_t add, uint16_t data)
{
	while(HAL_GetTick() -m_rf.lastLcdTxTime<20);
	lcdTxMsg[1] = add;
	lcdTxMsg[3] = (data>>8)&0xff;
	lcdTxMsg[5] = (data)&0xff;

	Debug_LCD_Printf(DEBUG_TX, add, data);

#if 1//To PC
	char str[20]={0,};
	sprintf(str,"[%d,%d]\r\n",add, data);
	HAL_UART_Transmit(&huart5, str, strlen(str), 100);

#else
	HAL_UART_Transmit(&huart5, lcdTxMsg, 7,100);
#endif

	m_rf.lastLcdTxTime = HAL_GetTick();

}
void Tx_Hand1_Msg(uint8_t add, uint16_t data)
{
	uint8_t str[20];
	while(HAL_GetTick() -m_hand1.lastHPTxTime<20);

	sprintf(str,"[%d,%d]\r\n",add, data);

	Debug_HAND_Printf(DEBUG_TX, add, data);
	HAL_UART_Transmit(&huart2,str, strlen(str),100);
	m_hand1.lastHPTxTime = HAL_GetTick();
}


void Tx_RF_Msg(uint8_t* buff, uint8_t len)
{
	while(HAL_GetTick() -m_rf.lastRfGenTxTime<50);
	HAL_UART_Transmit(&huart4,buff, len,100);
#ifdef DEBUG_PRINT
	Debug_Tx_RF_Printf(buff, len);
#endif
	m_rf.lastRfGenTxTime = HAL_GetTick();
	RF_Rx_Parssing(RF_RX_CALLBACK);

}


void AutoCal_Tx_IP_Msg()
{
	char buff[5] = "IP\r\n";
	HAL_UART_Transmit(&huart3,buff, 4,100);
#ifdef DEBUG_PRINT

#endif

}

void AutoCal_Tx_Z_Msg()
{
	char buff[5] = "Z\r\n";
	HAL_UART_Transmit(&huart3,buff, 3,100);
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

void Uart_HP_Temp_LCD_Veiw()
{
	static uint32_t timeStamp;

	if(m_hand1.cartEndFlag == 1)
	{
		if(HAL_GetTick()-timeStamp >= 1000)
		{
			Tx_LCD_Msg(CMD_TEMPERATURE_SHOT, m_hand1.temprature);
			Tx_LCD_Msg(CMD_PELTIER_DUTY, m_hand1.pwmDuty);
			timeStamp = HAL_GetTick();
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
	Uart_HP_Temp_LCD_Veiw();
}



#if 0
void Uart_Passing_org(UART_T* uart, uint8_t* ptr)//stm32��
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

void Uart_Passing(UART_T* uart, uint8_t* ptr)//stm32��
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



	}
	else
	{
//		ERR_FUC_LINE();
		printf("%s \r\n",uart->rxBuff);
	}

	Rx_BuffClear(uart);
}


void Uart3_Passing(uint8_t data)//stm32��
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
			m_rf.FeedBackCnt %= 30;
		}

		Rx_BuffClear(&m_uart3);
	}
	else
	{
		m_uart3.rxBuff[m_uart3.rxCnt] = data;
		m_uart3.rxCnt++;
		m_uart3.rxCnt%=RX_BUFF_SIZE;
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
	static uint32_t timeStamp;

	if(HAL_GetTick()-timeStamp >= 500 )
	{
		timeStamp = HAL_GetTick();
//	    HAL_UART_Transmit(&huart1,"11111111\r\n",10,100);
//	    HAL_UART_Transmit(&huart2,"22222222\r\n",10,100);
//	    HAL_UART_Transmit(&huart3,"33333333\r\n",10,100);
//	    HAL_UART_Transmit(&huart4,"44444444\r\n",10,100);
//		HAL_UART_Transmit(&huart5,"55555555\r\n",10,100);
	}


	if(ddQ[0])
	{
		ddQ[0] = 0;
		Tx_LCD_Msg(ddQ[1],(uint16_t)ddQ[2]);

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
	uint8_t cmd = 0;
	static uint8_t startFlag = 0;
	static uint8_t endFlag = 0;

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



