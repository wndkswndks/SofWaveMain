//debug.c

#include "debug.h"


// ���氡��====================

#define OTHER_CPYBUFF_LEN		5
#define CLEAR_SCR               "\033[2J"
#define CLEAR_X0Y0               "\033[0;0H"




DEBUG_T dd;
// �����Ϸ����� ���� ����
uint32_t DeGetTime()
{
	return HAL_GetTick();
}


void ddInit()
{

}
void ddFunc1(char* buff)
{

}
void ddFunc2()
{

}

void ddFunc3()
{

}


void ddClearIntBuff(int* buff, int*cnt, int size)
{
	memset(buff, 0, size*sizeof(int));
	*cnt = 0;
}

void ddClearCharBuff(char* buff, int*cnt, int size)
{
	memset(buff, 0, size);
	*cnt = 0;
}

void ddStep(char data)
{

	if(data >= DEBUG_STEP_SIZE)
	{
		ERR_FUC_LINE();
		return;
	}

	dd.step[data] = 1;
}


void ddCnt(char data)
{
	if(data >= DEBUG_CNT_SIZE)
	{
		ERR_FUC_LINE();
		return;
	}
	dd.cnt[data]++;
}





void ddIBuff1(int data)
{
	static int buffPre = 0xaaa;
	#if 0
	if(data == buffPre)return; // �ߺ�üũ
	#endif

	dd.ibuff1[dd.icnt1] = data;
	#if 0
	if(dd.icnt1<DEBUG_IBUFF1_SIZE-1)dd.icnt1++;
	#else
	dd.icnt1++;
	dd.icnt1 %= DEBUG_IBUFF1_SIZE;
	#endif
	buffPre = data;
}
#if 1

void ddIBuff2(int data)
{
	static int buffPre = 0xaaa;
	#if 1
	if(data == buffPre)return; // �ߺ�üũ
	#endif
	dd.ibuff2[dd.icnt2] = data;
	#if 0
	if(dd.icnt2<DEBUG_IBUFF2_SIZE-1)dd.icnt2++;
	#else
	dd.icnt2++;
	dd.icnt2 %= DEBUG_IBUFF2_SIZE;
	#endif
	buffPre = data;
}

#endif
#if 1

void ddIBuff3(int data)
{
	static int buffPre = 0xaaa;
	#if 1
	if(data == buffPre)return; // �ߺ�üũ
	#endif
	dd.ibuff3[dd.icnt3] = data;
	#if 0
	if(dd.icnt3<DEBUG_IBUFF3_SIZE-1)dd.icnt3++;
	#else
	dd.icnt3++;
	dd.icnt3 %= DEBUG_IBUFF3_SIZE;
	#endif
	buffPre = data;
}
#endif







void ddCBuff1(char data)
{

	dd.cbuff1[dd.ccnt1] = data;
	#if 0
	if(dd.ccnt1<DEBUG_CBUFF1_SIZE-1) dd.ccnt1++;
	#else
	dd.ccnt1++;
	dd.ccnt1 %= DEBUG_CBUFF1_SIZE;
	#endif
}


#if 1

void ddCBuff2(char data)
{
	dd.cbuff2[dd.ccnt2++] = data;
	#if 1
	if(dd.ccnt2<DEBUG_CBUFF2_SIZE-1) dd.ccnt2++;
	#else
	dd.ccnt2++;
	dd.ccnt2 %= DEBUG_CBUFF2_SIZE;
	#endif
}
#endif



#if 1

void ddCBuff3(char data)
{
	dd.cbuff3[dd.ccnt3++] = data;
	#if 1
	if(dd.ccnt3<DEBUG_CBUFF3_SIZE-1) dd.ccnt3++;
	#else
	dd.ccnt3++;
	dd.ccnt3 %= DEBUG_CBUFF3_SIZE;
	#endif
}
#endif




void ddICpy1(int* cpyBff, int len)
{
	if(len>DEBUG_ICPY1_SIZE)
	{
		ERR_FUC_LINE();
		return;
	}
	memcpy(dd.Icpy1,cpyBff, sizeof(int)*len );
}
#if 1
void ddICpy2(int* cpyBff, int len)
{
	if(len>DEBUG_ICPY2_SIZE)
	{
		ERR_FUC_LINE();
		return;
	}

	memcpy(dd.Icpy2,cpyBff, sizeof(int)*len );
}

#endif

#if 1
void ddICpy3(int* cpyBff, int len)
{
	if(len>DEBUG_ICPY3_SIZE)
	{
		ERR_FUC_LINE();
		return;
	}

	memcpy(dd.Icpy3,cpyBff, sizeof(int)*len );
}

#endif





void ddCCpy1(char* cpyBff, int len)
{
	if(len>DEBUG_CCPY1_SIZE)
	{
		ERR_FUC_LINE();
		return;
	}

	memcpy(dd.ccpy1,cpyBff, sizeof(char)*len );
}
#if 1
void ddCCpy2(char* cpyBff, int len)
{
	if(len>DEBUG_CCPY2_SIZE)
	{
		ERR_FUC_LINE();
		return;
	}

	memcpy(dd.ccpy2,cpyBff, sizeof(char)*len );
}

#endif

#if 1

void ddCCpy3(char* cpyBff, int len)
{
	if(len>DEBUG_CCPY3_SIZE)
	{
		ERR_FUC_LINE();
		return;
	}

	memcpy(dd.ccpy3,cpyBff, sizeof(char)*len );
}
#endif


#if 1



void ddMCpyc(char* cpyBff, int len)
{
	memcpy(dd.mcpyC[dd.cpyCnt],cpyBff, sizeof(char)*len );
	if(dd.cpyCnt<DEBUG_CPY_D_MAIN_SIZE-1)dd.cpyCnt++;
}
#endif

void ddGpio(GPIO_TypeDef *gpio,uint16_t pin, uint8_t ch)
{
	if (HAL_GPIO_ReadPin(gpio, pin))
	{
		dd.gpioRead[ch] = 2;
	}
	else
	{
		dd.gpioRead[ch] = 1;
	}

}


void ddTimeStart1()
{
	dd.timeStart1 = DeGetTime();
}

int ddTimeEnd1()
{
	dd.timeTerm1 = DeGetTime() - dd.timeStart1;
	return dd.timeTerm1;
}

void ddTimeStart2()
{
	dd.timeStart2 = DeGetTime();
}

int ddTimeEnd2()
{
	dd.timeTerm2 = DeGetTime() - dd.timeStart2;
	return dd.timeTerm2;
}
void ddTimeStart3()
{
	dd.timeStart3 = DeGetTime();
}

int ddTimeEnd3()
{
	dd.timeTerm3 = DeGetTime() - dd.timeStart3;
	return dd.timeTerm3;
}

int ddTimeRatio1()
{
	dd.timeRatio1 = DeGetTime() - dd.timePre1;
	dd.timePre1 = DeGetTime();
}

int ddTimeRatio2()
{
	dd.timeRatio2 = DeGetTime() - dd.timePre2;
	dd.timePre2 = DeGetTime();
}
int ddTimeRatio3()
{
	dd.timeRatio3 = DeGetTime() - dd.timePre3;
	dd.timePre3 = DeGetTime();
}

int ddButton1()
{
	if(dd.button1!= 0)
	{
	#if 1
		dd.button1 = 0;// dbutton1�� ������ �������ٲ��� �����? �����Ŀ��� 0���� �ʱ�ȭ�ؾ���
	#endif
		return 1;
	}
	return 0;
}
int ddButton2()
{
	if(dd.button2!= 0)
	{
	#if 1
		dd.button2 = 0;// dbutton2�� ������ �������ٲ��� �����? �����Ŀ��� 0���� �ʱ�ȭ�ؾ���
	#endif
		return 1;
	}
	return 0;
}
int ddButton3()
{
	if(dd.button3!= 0)
	{
	#if 1
		dd.button3 = 0;// dbutton3�� ������ �������ٲ��� �����? �����Ŀ��� 0���� �ʱ�ȭ�ؾ���
	#endif
		return 1;
	}
	return 0;
}


int ddAgingBuff() // �̸������� ���� �μ��� �ֱ�(�μ� �ƴϿ��� �ٸ����� ������)
{
	int data;
	data = dd.agingBuff[dd.agingCnt];
	#if 1
	if(dd.agingCnt<DEBUG_AGING_SIZE-1) dd.agingCnt++;
	#else
	ddagingCnt++;
	ddagingCnt %= DEBUG_BUFF_C1_SIZE;
	#endif

	return data;
}
void ddStepDe(char step, char limt, int data0, int data1, int data2, int data3, int data4 )// �̰� �Լ� �� ���ٿ� �־�д�?
{
	static char stepCheck = 0xff;
	if(stepCheck != step)
	{
		dd.mcpyS[dd.mcpySCnt][0] = data0;
		dd.mcpyS[dd.mcpySCnt][1] = data1;
		dd.mcpyS[dd.mcpySCnt][2] = data2;
		dd.mcpyS[dd.mcpySCnt][3] = data3;
		dd.mcpyS[dd.mcpySCnt][4] = data4;
		if( dd.mcpySCnt<limt)dd.mcpySCnt++;
		stepCheck = step;
	}

}

//if(Diff1(xxxx)) // ���� �ٸ����� �����ϴ�?�Լ�
//{
//
//}
int ddDiff1(int data)//if���� �־��ֱ�
{
static uint8_t once = 1;

	if(once)
	{
		once = 0;
		dd.diff1 = 0xffff;
	}
	if(dd.diff1 != data)
	{
		dd.diff1 = data;
		return 1;
	}
	else
	{
		dd.diff1 = data;
		return 0;
	}
}
int ddDiff2(int data)//if���� �־��ֱ�
{
	static uint8_t once = 1;

	if(once)
	{
		once = 0;
		dd.diff2 = 0xffff;
	}

	if(dd.diff2 != data)
	{
		dd.diff2 = data;
		return 1;
	}
	else
	{
		dd.diff2 = data;
		return 0;
	}
}
int ddDiff3(int data)//if���� �־��ֱ�
{
	static uint8_t once = 1;

	if(once)
	{
		once = 0;
		dd.diff3 = 0xffff;
	}

	if(dd.diff3 != data)
	{
		dd.diff3 = data;
		return 1;
	}
	else
	{
		dd.diff3 = data;
		return 0;
	}
}


void ddCmd_Tx()
{
	if(!dd.txDflag)return;
	dd.txDflag = 0;

	/*
	data0 = dddataView[0];
	data1 = dddataView[1];
	data2 = dddataView[2];
	data3 = dddataView[3];
	*/

	printf(CLEAR_X0Y0);
	printf(CLEAR_SCR);
	printf("(0) data0 = %d\r\n",dd.dataView[0]);
	printf("(1) data1 = %d\r\n",dd.dataView[1]);
	printf("(2) data2 = %d\r\n",dd.dataView[2]);
	printf("(3) data3 = %d\r\n",dd.dataView[3]);
	printf("(4) data4 = %d\r\n",dd.dataView[4]);
	printf("time(ms) = %u\r\n",HAL_GetTick());



}



void TerminalAction1()
{

}
void TerminalAction2()
{

}
void TerminalAction3()
{

}
void TerminalAction4()
{

}



/*
�̷��� �ֱ�
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart == &huart2)
	{
		HAL_UART_Receive_IT(&huart2, m_cmd2.rxData, 1);

		if(D_CMD_RX_Parssing(m_cmd2.rxData[0])) // �׶��� Ŀ���?�̿��?�ֱ�
		{
			HAL_UART_Transmit_IT(&huart2, m_cmd2.rxData, 1); // ���ͷ�Ʈ�� ��������
		}
	}
}


*/
uint8_t ddCMD_RX_Parssing(uint8_t data)
{
	static char step = 0;
	static char addQ;
	static char buffP[10];
	static char cntP;
	int changData = 0;

	switch (data)
	{
		case CMD_ESC:
			dd.txDflag = 1;
			memset(buffP, 0, 10);
			cntP = 0;
			step = 0;
			addQ = 0;
		break;

		case 'q':
			//Aatting1
			dd.txDflag = 1;
			TerminalAction1();
		break;

		case 'w':
			//Aatting2
			dd.txDflag = 1;
			TerminalAction2();
		break;

		case 'e':
			//Aatting3
			dd.txDflag = 1;
			TerminalAction3();
		break;

		case 'r':
			//Aatting4
			dd.txDflag = 1;
			TerminalAction4();
		break;

		default:
			switch (step)
			{

				case 0:
					if('0' <= data && data <='4')
					{
						cntP = 0;
						addQ = data - '0';
						step = 1;
					}
				break;

				case 1:
					if(data ==CMD_SPACE) step = 2;
					else step = 0;
				break;

				case 2:
					if('0' <= data && data <='9' ||data =='-')
					{
						buffP[cntP++] = data;
						cntP %=10;
					}
					else if(data == CMD_ENTER && cntP>0)
					{
						changData = atoi(buffP);

						dd.dataView[addQ] = changData;
						memset(buffP, 0, 10);
						dd.txDflag = 1;
						step = 0;
					}

			}
		break;
	}

	if(('0' <= data && data<='9') ||data== '-' ||data == CMD_SPACE)
	{
		dd.txCallback = data;
		HAL_UART_Transmit_IT(&huart2, &dd.txCallback, 1);
		return 1;
	}
	else
	{
		return 0;
	}


}

// ������ �ڸ��� �Լ����?���� ǥ�� : �������Ͱ����ڸ��� DEBUG_UART(); �����־��ָ� ������ ����Ʈ �۽�
void uart_send_string(const char *str)
{
    HAL_UART_Transmit(&huart2, (uint8_t *)str, strlen(str), HAL_MAX_DELAY);
}

void send_debug_info_uart(const char *function, int line)
{
    char message[128];
    snprintf(message, sizeof(message), "Function: %s, Line: %d\r\n", function, line);
    uart_send_string(message);
}
void BL_LedDiming()//1ms ���� ȣ��
{
  static uint8_t rActive10ms = 0;
  static uint8_t rActive_LED = 0;
  static uint8_t bActive_LED = 0;
  static uint8_t b10ms = 0;


  if (rActive10ms >= rActive_LED)
  {
//    LED_BL(0);//ON
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);
  }
  else
  {
//    LED_BL(1);//OFF
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET);
  }
  if (++rActive10ms > 9) rActive10ms = 0;


  if (++b10ms >= 150)
  {
    b10ms = 0;

    if (!bActive_LED)
    {
      if (++rActive_LED >= 9)
        bActive_LED = 1;
    }
    else
    {
      if (--rActive_LED == 0)
        bActive_LED = 0;
    }
  }

}

void ddbugConfig()
{
#if 1
	ddCmd_Tx();
#endif

#if 1
	Uart_Gulobal();
#endif






}


