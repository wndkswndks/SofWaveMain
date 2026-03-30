/*
 * error_handler.c
 *
 *  Created on: Mar 25, 2026
 *      Author: Cellah_SW
 */

#include "error_handler.h"
ERROR_T m_err;

void Error_Test_Init()
{
//	m_err.txEn = 1;

	m_hand1.temprature = 200;
	m_io.level1Status = 0;
	m_io.flowSensorFrq = 3;
	m_io.battery = 3.3;
	m_err.autoCalStatus = 0;
	m_io.hour = 1;
	m_io.min = 15;
	m_io.sec = 45;

}


void Err_Init()
{
//	Get_Err_StatusBitFlag();
	for(int i =0 ;i < 50;i++)
	{
		switch (i)
		{
		  case IDX_TEMP_OUT:
		  case IDX_TEMP_LIMIT_UNDER:
		  case IDX_TEMP_LOW:
		  case IDX_FLOW_LIMIT_UNDER:
		  case IDX_BATTRY_LIMIT_OVER:
		  case IDX_BATTRY_LIMIT_UNDER:
		  case IDX_BATTRY_LIMIT_LOW:
			   m_err.errStandBuff[i] = 5;
		  break;

		  default:
			  m_err.errStandBuff[i] = 1;
		  break;
		}
	}
//	 Error_Test_Init();
}




void Set_Err_StatusBitFlag(uint8_t cmd, uint8_t status)
{
	if(status)
	{
		if(cmd<=15) m_err.errStatus[0] |= 1<<cmd;
		else if(cmd<=31) m_err.errStatus[1] |= 1<<(cmd-16);
		else if(cmd<=47) m_err.errStatus[2] |= 1<<(cmd-32);
		else m_err.errStatus[3] |= 1<<(cmd-48);
	}
	else
	{
		if(cmd<=15) m_err.errStatus[0] &= ~(1<<cmd);
		else if(cmd<=31) m_err.errStatus[1] &= ~(1<<(cmd-16));
		else if(cmd<=47) m_err.errStatus[2] &= ~(1<<(cmd-32));
		else m_err.errStatus[3] |= ~(1<<(cmd-48));
	}


	Eeprom_Word_Write(IDX_EEP_ERROR_STATUS_1, m_err.errStatus[0]);
	Eeprom_Word_Write(IDX_EEP_ERROR_STATUS_2, m_err.errStatus[1]);
	Eeprom_Word_Write(IDX_EEP_ERROR_STATUS_3, m_err.errStatus[2]);
	Eeprom_Word_Write(IDX_EEP_ERROR_STATUS_4, m_err.errStatus[3]);

}




void Get_Err_StatusBitFlag()
{

	for(int i =0 ;i <= 15;i++)
	{
		if((m_err.errStatus[0]>>i)&0x01) m_err.errDataBuff[i] = i;
		else m_err.errDataBuff[i] = 0;

	}
	for(int i =0 ;i <= 15;i++)
	{
		if((m_err.errStatus[1]>>i)&0x01) m_err.errDataBuff[i+16] = i+16;
		else m_err.errDataBuff[i+16] = 0;
	}
	for(int i =0 ;i <= 15;i++)
	{
		if((m_err.errStatus[2]>>i)&0x01) m_err.errDataBuff[i+32] = i+32;
		else m_err.errDataBuff[i+32] = 0;
	}
	for(int i =0 ;i <= 1;i++)
	{
		if((m_err.errStatus[3]>>i)&0x01) m_err.errDataBuff[i+48] = i+48;
		else m_err.errDataBuff[i+48] = 0;
	}
}

uint8_t Check_Common(uint8_t status, uint8_t cmd)
{

	if(status)//Nomal
	{
		if(m_err.errDataBuff[cmd])
		{
			m_err.errDataBuff[cmd] = 0;
			Set_Err_StatusBitFlag(cmd, 0);
			m_err.errCheckBuff[cmd] = 0;
			printf("[ERR %u] Clear \r\n",cmd);

		}
		m_err.errCntBuff[cmd] = 0;
	}
	else//errs
	{
		if(!m_err.errDataBuff[cmd])
		{
			m_err.errCntBuff[cmd]++;
			if(m_err.errStandBuff[cmd] <= m_err.errCntBuff[cmd])
			{
				m_err.errCntBuff[cmd] = 0;
				m_err.errDataBuff[cmd] = cmd;
				Body_Led_Ctrl(BODY_LED_ERROR);
				Set_Err_StatusBitFlag(cmd, 1);
				if(m_eepMain.errCntBuff[cmd]<999)
				{
					m_eepMain.errCntBuff[cmd]++;
					Eeprom_Word_Write(IDX_EEP_ERROR+cmd*2, m_eepMain.errCntBuff[cmd]);
				}
				printf("[ERR %u] Event\r\n",cmd);
			}
		}
	}
	return m_err.errDataBuff[cmd];

}







uint8_t Check_CartrigeCommon(uint8_t status, uint8_t cmd)
{
	uint16_t errData;

	if(status)
	{
		errData = ERR_DISABLE +cmd;
		m_err.errDataBuff[cmd] = errData;
	}

	return 0;

}

uint8_t Check_Max_Min(int data, int max, int min, uint8_t cmd)
{
	uint8_t status = (min <= data && data <max);
	uint8_t returnValue = 0;
	returnValue = Check_Common(status, cmd);

	return returnValue;
}

uint8_t Check_Max(int data, int max, uint8_t cmd)
{

	uint8_t status = (data <max);
	uint8_t returnValue = 0;
	returnValue = Check_Common(status, cmd);

	return returnValue;

}

uint8_t Check_Min(int data, int min, uint8_t cmd)
{
	uint8_t status = (min <= data);
	uint8_t returnValue = 0;
	returnValue = Check_Common(status,cmd);

	return returnValue;

}


uint8_t Check_Status(int data, int nomalData, uint8_t cmd)
{
	uint8_t status = (data == nomalData);
	uint8_t returnValue = 0;
	returnValue = Check_Common(status, cmd);

	return returnValue;

}

uint8_t Check_Status_Rvrs(int data, int errorData, uint8_t cmd)
{
	uint8_t status = (data == errorData);
	uint8_t returnValue = 0;
	returnValue = Check_Common(!status, cmd);

	return returnValue;

}

uint8_t Check_Day(uint16_t YY, uint16_t MM, uint16_t DD, uint8_t cmd)
{
	uint8_t yyOk = (YY_MIN <= YY && YY <=YY_MAX);
	uint8_t mmOk = (MM_MIN <= MM && MM <=MM_MAX);
	uint8_t ddOk = (DD_MIN <= DD && DD <=DD_MAX);
	uint8_t status = (yyOk && mmOk && ddOk);
	uint8_t returnValue = 0;
	returnValue = Check_Common(status, cmd);

	return returnValue;
}

uint8_t Check_Time(uint8_t hour, uint8_t min, uint8_t sec, uint8_t cmd)
{
	uint8_t hourOk = (HOUR_MIN <= hour && hour <=HOUR_MAX);
	uint8_t minOk = (MIN_MIN <= min && min <=MIN_MAX);
	uint8_t secOk = (SEC_MIN <= sec && sec <=SEC_MAX);
	uint8_t status = (hourOk && minOk && secOk);
	uint8_t returnValue = 0;

	returnValue = Check_Common(status, cmd);

	return returnValue;


}
void Error_Buff_Clear()
{
	memset(m_err.errDataBuff, 0, sizeof(m_err.errDataBuff));
}


void Error_Buff_Main_Tx()
{
	uint8_t errCnt = 0;
	for(int i =IDX_MAIN_EVENT_START ;i < IDX_MAIN_EVENT_END; i++)
	{
		if(m_err.errDataBuff[i])
		{
			errCnt++;
			if(!m_err.errCheckBuff[i])
			{
				Tx_LCD_Msg(CMD_ERR, m_err.errDataBuff[i]);
				HAL_Delay(1500);
				m_err.errCheckBuff[i] = m_err.errDataBuff[i];
			}

		}
	}
	if(errCnt==0 && !m_err.txEn)
	{
		Tx_LCD_Msg(CMD_OK, OK_MAIN);
	}
}

void Error_Buff_HP_Tx()
{
	uint8_t errCnt = 0;
	for(int i =IDX_HP_EVENT_START ;i < IDX_HP_EVENT_END; i++)
	{
		if(m_err.errDataBuff[i])
		{
			errCnt++;
			if(!m_err.errCheckBuff[i])
			{
				Tx_LCD_Msg(CMD_ERR, m_err.errDataBuff[i]);
				HAL_Delay(1500);
				m_err.errCheckBuff[i] = m_err.errDataBuff[i];
			}
		}
	}
	if(errCnt==0 && !m_err.txEn)
	{
		Tx_LCD_Msg(CMD_OK, OK_HP);
	}
}

void Error_Buff_Rf_Tx()
{
	uint8_t errCnt = 0;
	for(int i =IDX_RF_EVENT_START ;i < IDX_RF_EVENT_END; i++)
	{
		if(m_err.errDataBuff[i])
		{
			errCnt++;
			if(!m_err.errCheckBuff[i])
			{
				Tx_LCD_Msg(CMD_ERR, m_err.errDataBuff[i]);
				HAL_Delay(1500);
				m_err.errCheckBuff[i] = m_err.errDataBuff[i];
			}
		}
	}
	errCnt=0;
	if(errCnt==0 && !m_err.txEn)
	{
		Tx_LCD_Msg(CMD_OK, OK_RF);
	}
}




/*
m_err.errDataBuff[IDX_TEMP_OUT]
m_err.errDataBuff[IDX_TEMP_LIMIT_UNDER]
m_err.errDataBuff[IDX_TEMP_LOW]
m_err.errDataBuff[IDX_FLOW_LIMIT_UNDER]
m_err.errDataBuff[IDX_FLOW_ZERO_IDX]
m_err.errDataBuff[IDX_LEVEL_LOW]
m_err.errDataBuff[IDX_AUTO_CAL_COMU_ERR]
m_err.errDataBuff[IDX_BATTRY_LIMIT_OVER]
m_err.errDataBuff[IDX_BATTRY_LIMIT_UNDER]
m_err.errDataBuff[IDX_BATTRY_LIMIT_LOW]
m_err.errDataBuff[IDX_RTC_ERR]
m_err.errDataBuff[IDX_PRE_COOL_ERR]
m_err.errDataBuff[IDX_HAND_COMU_ERR]
m_err.errDataBuff[IDX_CATRIGE_ID_ERR]
m_err.errDataBuff[IDX_CATRIGE_MANU_ERR]
m_err.errDataBuff[IDX_CATRIGE_MANU_OVER_ERR]
m_err.errDataBuff[IDX_CATRIGE_ISUE_ERR]
m_err.errDataBuff[IDX_CATRIGE_ISUE_OVER_ERR]
m_err.errDataBuff[IDX_CATRIGE_WATT_ERR]
m_err.errDataBuff[IDX_CATRIGE_FRQ_ERR]
m_err.errDataBuff[IDX_CATRIGE_RESHOT_ERR]
m_err.errDataBuff[IDX_CATRIGE_RESHOT_LOW]
m_err.errDataBuff[IDX_CATRIGE_RESHOT_ZERO]
m_err.errDataBuff[IDX_CATRIGE_DETECT]
m_err.errDataBuff[IDX_CATRIGE_UN_DETEC]
m_err.errDataBuff[IDX_HAND_TIMEOUT]
m_err.errDataBuff[IDX_RF_COMU_ERR]
m_err.errDataBuff[IDX_RF_STATUS_ERR]
m_err.errDataBuff[IDX_RF_EVENT_END]
m_err.errDataBuff[IDX_LCD_COMU_ERR]
m_err.errDataBuff[IDX_LCD_TIMEOUT]
m_err.errDataBuff[IDX_IS_CURRNTSHOT_RESET]
m_err.errDataBuff[IDX_IS_TOTALJULE_RESET]
m_err.errDataBuff[IDX_CATRIGE_NEW]
*/


void Error_Check_Main()
{
#if 0
	Check_Status(m_io.level1Status, 0, IDX_LEVEL_LOW);
	Check_Max_Min(m_io.flowSensorFrq, FLOW_LOW_MAX, FLOW_LOW_MIN, IDX_FLOW_LIMIT_UNDER);

	if(Check_Max(m_io.battery*10.0, BATTRY_LIMIT_MAX, IDX_BATTRY_LIMIT_OVER)){}
	else if(Check_Min(m_io.battery*10.0, BATTRY_LIMIT_MIN, IDX_BATTRY_LIMIT_UNDER)){}
	else if(Check_Min(m_io.battery*10.0, BATTRY_NOMAL_MIN, IDX_BATTRY_LIMIT_LOW)){}

	Check_Status(m_err.autoCalStatus, 0, IDX_AUTO_CAL_COMU_ERR);
	Check_Time(m_io.hour, m_io.min, m_io.sec, IDX_RTC_ERR);


#endif

	if(m_err.txEn)Error_Buff_Main_Tx();





}

void Error_Check_HP()
{
	uint8_t errStatus;



#if 0
	m_err.handTimeout++;
	if(Check_Max(m_err.handTimeout, COMU_MAX_CNT, IDX_HAND_COMU_ERR)){}
	if(Check_Status(m_err.preCoolStatus, 0, IDX_PRE_COOL_ERR)){}

	if(Check_Max_Min(m_hand1.temprature, TEMP_OUT_MAX, TEMP_OUT_MIN,IDX_TEMP_OUT)){}
	else if(Check_Min(m_hand1.temprature, TEMP_MIN, IDX_TEMP_LIMIT_UNDER)){}
	else if(Check_Min(m_hand1.temprature, TEMP_LOW_VALUE, IDX_TEMP_LOW)){}


//==================================




	if(Check_Status_Rvrs(m_eep.catridgeDetect, CATRIGE_CHK_NEW, IDX_CATRIGE_NEW_DETECT)){}

	if(Check_Status_Rvrs(m_eep.catridgeDetect, CATRIGE_CHK_I2C_READ_ERR, IDX_CATRIGE_I2C_ERR)){}
	else if(Check_Status_Rvrs(m_eep.catridgeDetect, CATRIGE_CHK_I2C_WRITE_ERR, IDX_CATRIGE_I2C_ERR)){}
	else if(Check_Status_Rvrs(m_eep.catridgeDetect, CATRIGE_CHK_UN_DETECT, IDX_CATRIGE_UN_DETECT)){}
	else
	{
		for(int i = 1; i <= 7; i++)
		{
			if(Check_Max_Min(m_eep.rfFrqBuff[i], CATRIDGE_FRQ_MAX, CATRIDGE_FRQ_MIN, IDX_CATRIGE_FRQ_ERR))break;

		}
		for(int i = 1; i <= 77; i++)
		{
			if(Check_Max_Min(m_eep.rfWattBuff[i], CATRIDGE_WATT_MAX, CATRIDGE_WATT_MIN, IDX_CATRIGE_WATT_ERR))break;

		}

		Check_Max(m_eep.remainingShotNum, CATRIDGE_REMAIN_MAX, IDX_CATRIGE_RESHOT_ERR);
		Check_Max(m_eep.catridgeId, CATRIDGE_ID_MAX, IDX_CATRIGE_ID_ERR);
		Check_Day(m_eep.manufacYY, m_eep.manufacMM, m_eep.manufacDD, IDX_CATRIGE_MANU_ERR);
		Check_Day(m_eep.issuedYY, m_eep.issuedMM, m_eep.issuedDD, IDX_CATRIGE_ISUE_ERR);

		m_eep.manufacDay = m_eep.manufacYY*10000 + m_eep.manufacMM*100 + m_eep.manufacDD;
		m_eep.issuedDay = m_eep.issuedYY*10000 + m_eep.issuedMM*100 + m_eep.issuedDD;
		Check_Max(m_io.day, m_eep.manufacDay + DAY_MAX, IDX_CATRIGE_MANU_OVER_ERR);
		Check_Max(m_io.day, m_eep.issuedDay + DAY_MAX, IDX_CATRIGE_ISUE_OVER_ERR);

		if(!m_rf.remainingShotNegative)
		{
			Check_Min(m_eep.remainingShotNum, CATRIDGE_REMAIN_LOW_3, IDX_CATRIGE_RESHOT_LOW);
		}
		else
		{
			Check_Max(m_rf.remainingShotNegative, m_eepMain.remainingShotRandom, IDX_CATRIGE_RESHOT_ZERO);
		}
	}

//==================================





#endif

	if(m_err.txEn)Error_Buff_HP_Tx();

}

void Error_Check_RF()
{
#if 0
	m_err.rfTimeout++;
	Tx_RF_GenStatus_Check();
	Check_Max(m_err.rfTimeout, COMU_MAX_CNT, IDX_RF_COMU_ERR);//E02
	Check_Status(m_err.rfStatus, 0, IDX_RF_STATUS_ERR);//E14
#if 0
#endif

#endif

	if(m_err.txEn)Error_Buff_Rf_Tx();

}

void Error_Check_Config()
{
	static uint32_t timeStamp;

	if(m_rf.pluseOn) return;
	if(HAL_GetTick()-timeStamp >= 1000)
	{
		Error_Check_Main();
		Error_Check_HP();
		Error_Check_RF();

		timeStamp = HAL_GetTick();
	}
}

