/*
 * error_handler.c
 *
 *  Created on: Mar 25, 2026
 *      Author: Cellah_SW
 */

#include "error_handler.h"
ERROR_T m_err;



uint8_t Check_ERROR(uint8_t nomal, uint8_t cmd, uint8_t delay)
{
	static uint8_t errCntBuff[50];
	static uint8_t clrCntBuff[50];
	uint8_t str[20] ={0,};
	if(nomal)//Nomal
	{
		if(m_err.errDataBuff[cmd])
		{
			clrCntBuff[cmd]++;
			if(delay <= clrCntBuff[cmd])
			{
				clrCntBuff[cmd] = 0;
				m_err.errDataBuff[cmd] = 0;
				Debug_Printf_Value("[ERR Clear] ",cmd,1);
				Body_Led_Ctrl(BODY_LED_STANDBY);
			}

		}
		errCntBuff[cmd] = 0;
	}
	else//err
	{
		if(!m_err.errDataBuff[cmd])
		{
			errCntBuff[cmd]++;
			if(delay <= errCntBuff[cmd])
			{
				errCntBuff[cmd] = 0;
				m_err.errDataBuff[cmd] = cmd;
				Body_Led_Ctrl(BODY_LED_ERROR);
				if(m_err.txEn)Tx_LCD_Msg(CMD_ERR, cmd);
				Debug_Printf_Value("[ERR Event] ",cmd,1);

				sprintf(str,"[ERR_EVENT_%u]\r\n",cmd);
				SD_Error_Save(m_io.day,m_io.hhmm, str);
			}
		}
		clrCntBuff[cmd] = 0;
	}
	return m_err.errDataBuff[cmd];

}




uint8_t Check_Day_ERROR(uint16_t YY, uint16_t MM, uint16_t DD, uint8_t cmd)
{
	uint8_t yyOk = (YY_MIN <= YY && YY <=YY_MAX);
	uint8_t mmOk = (MM_MIN <= MM && MM <=MM_MAX);
	uint8_t ddOk = (DD_MIN <= DD && DD <=DD_MAX);
	uint8_t status = (yyOk && mmOk && ddOk);
	uint8_t returnValue = 0;
	returnValue = Check_ERROR(status, cmd, ERR_DEL_1);

	return returnValue;
}


uint8_t Check_Time_ERROR(uint8_t hour, uint8_t min, uint8_t sec, uint8_t cmd)
{
	uint8_t hourOk = (HOUR_MIN <= hour && hour <=HOUR_MAX);
	uint8_t minOk = (MIN_MIN <= min && min <=MIN_MAX);
	uint8_t secOk = (SEC_MIN <= sec && sec <=SEC_MAX);
	uint8_t status = (hourOk && minOk && secOk);
	uint8_t returnValue = 0;

	returnValue = Check_ERROR(status, cmd, ERR_DEL_1);

	return returnValue;


}
void Error_Led_View()
{
	if(m_err.errLedViewTime )
	{
		m_err.errLedViewTime--;
		if(!m_err.errLedViewTime)
		{
			Body_Led_Ctrl(BODY_LED_STANDBY);
		}

	}

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
			Tx_LCD_Msg(CMD_ERR, m_err.errDataBuff[i]);
			HAL_Delay(1000);
		}
	}
	if(errCnt==0)
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
			Tx_LCD_Msg(CMD_ERR, m_err.errDataBuff[i]);
			HAL_Delay(1000);
		}
	}
	if(errCnt==0)
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
			Tx_LCD_Msg(CMD_ERR, m_err.errDataBuff[i]);
			HAL_Delay(1000);
		}
	}
	if(errCnt==0)
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
m_err.errDataBuff[IDX_CATRIGE_RESHOT_LOW_1000]
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
//=============================================
	Check_ERROR((m_io.level1Status==0), IDX_LEVEL_LOW, ERR_DEL_3);
	if(Check_ERROR((m_err.flowLimitUnder1==0), IDX_FLOW_LIMIT_UNDER, ERR_DEL_3))
	{
		Ready_OFF(EVENT_4);
		PELTIER_PWR_OFF();
		SOL1_OFF();
		if(m_io.flowSensorFrqChk==0) m_io.flowSensorFrq = 0;
	}
	if(Check_ERROR((m_err.flowLimitUnder2==0), IDX_FLOW_LIMIT_STOP, ERR_DEL_3))
	{
		Ready_OFF(EVENT_10);
		PELTIER_PWR_OFF();
		Pump_Ciller_Pwr_OFF();
		SOL1_OFF();
		if(m_io.flowSensorFrqChk==0) m_io.flowSensorFrq = 0;
	}


	Check_ERROR((m_err.powerSpecs==0), IDX_POWER_SPECS, ERR_DEL_1);
	Check_ERROR((m_io.chillerTemp<CHILLER_TEMP_MAX), IDX_CHILER_TEMP_OVER, ERR_DEL_3);
	Check_ERROR((m_err.autoCalStatus==0), IDX_AUTO_CAL_COMU_ERR, ERR_DEL_1);
#if 0
	Check_ERROR((m_err.flowZero==0), IDX_FLOW_LIMIT_UNDER, ERR_DEL_1);
	if(Check_ERROR((m_io.battery*10.0< BATTRY_LIMIT_MAX), IDX_BATTRY_LIMIT_OVER, ERR_DEL_1)){}
	else if(Check_ERROR((m_io.battery*10.0 > BATTRY_LIMIT_MIN), IDX_BATTRY_LIMIT_UNDER, ERR_DEL_1)){}
	else if(Check_ERROR((m_io.battery*10.0 > BATTRY_NOMAL_MIN), IDX_BATTRY_LIMIT_LOW, ERR_DEL_1)){}
	Check_Time_ERROR(m_io.hour, m_io.min, m_io.sec, IDX_RTC_ERR);
#endif
}

void Error_Check_HP()
{



	m_err.handTimeout++;
	if(Check_ERROR((m_err.handTimeout < COMU_MAX_CNT), IDX_HAND_COMU_ERR ,ERR_DEL_1)){m_hand1.temprature = 0;}
	if(Check_ERROR((m_err.preCoolStatus == 0), IDX_PRE_COOL_ERR ,ERR_DEL_1)){}

	if(Check_ERROR((TEMP_OUT_MIN <= m_hand1.temprature && m_hand1.temprature <TEMP_OUT_MAX),IDX_TEMP_OUT ,ERR_DEL_1))
	{
		Ready_OFF(EVENT_5);
		PELTIER_PWR_OFF();
	}
	else if(Check_ERROR((m_hand1.temprature > TEMP_MIN), IDX_TEMP_LIMIT_UNDER ,ERR_DEL_1)){}
	else if(Check_ERROR((m_hand1.temprature > TEMP_LOW_VALUE), IDX_TEMP_LOW ,ERR_DEL_1)){}

	if(m_eep.catridgeDetect == CATRIGE_CHK_OK && m_eep.catridgeStatus == SING_UP_CODE)
	{
		for(int i = 1; i <= 7; i++)
		{
			uint16_t Frq = m_eep.rfFrqBuff[i];
			if(Check_ERROR((CATRIDGE_FRQ_MIN <= Frq && Frq <CATRIDGE_FRQ_MAX), IDX_CATRIGE_FRQ_ERR ,ERR_DEL_1))break;

		}

		for(int i = 1; i <= 77; i++)
		{
			uint16_t watt = m_eep.rfWattBuff[i];
			if(Check_ERROR((CATRIDGE_WATT_MIN <= watt && watt <CATRIDGE_WATT_MAX), IDX_CATRIGE_WATT_ERR ,ERR_DEL_1))break;

		}

		Check_ERROR((m_eep.catridgeId < CATRIDGE_ID_MAX), IDX_CATRIGE_ID_ERR ,ERR_DEL_1);
		Check_Day_ERROR(m_eep.manufacYY, m_eep.manufacMM, m_eep.manufacDD, IDX_CATRIGE_MANU_ERR);
		Check_Day_ERROR(m_eep.issuedYY, m_eep.issuedMM, m_eep.issuedDD, IDX_CATRIGE_ISUE_ERR);

		m_eep.manufacDay = m_eep.manufacYY*10000 + m_eep.manufacMM*100 + m_eep.manufacDD;
		m_eep.issuedDay = m_eep.issuedYY*10000 + m_eep.issuedMM*100 + m_eep.issuedDD;
		Check_ERROR((m_io.day < m_eep.manufacDay + DAY_MAX), IDX_CATRIGE_MANU_OVER_ERR ,ERR_DEL_1);
		Check_ERROR((m_io.day < m_eep.issuedDay + DAY_MAX), IDX_CATRIGE_ISUE_OVER_ERR ,ERR_DEL_1);


		Check_ERROR((m_eep.remainingShotNum < CATRIDGE_REMAIN_MAX), IDX_CATRIGE_RESHOT_ERR ,ERR_DEL_1);

		if(Check_ERROR((m_eep.remainingShotNum > CATRIDGE_REMAIN_LOW_500), IDX_CATRIGE_RESHOT_LOW_500 ,ERR_DEL_1)){}
		else if(Check_ERROR((m_eep.remainingShotNum > CATRIDGE_REMAIN_LOW_1000), IDX_CATRIGE_RESHOT_LOW_1000 ,ERR_DEL_1)){}

	}

}

void Error_Check_RF()
{
#if 1

	m_err.rfTimeout++;
	Tx_RF_GenStatus_Check();
	Check_ERROR((m_err.rfTimeout< COMU_MAX_CNT), IDX_RF_COMU_ERR, 1);//E02
	Check_ERROR((m_err.rfStatus == 1), IDX_RF_STATUS_ERR, 1);//E14
#if 0
#endif

#endif

}
extern uint8_t sdExist;
void SD_Error_Save(uint32_t YYMMDD, uint32_t hhmm, uint8_t* logData)
{
	uint8_t timeStr[11] ={0,};
	if(!sdExist)return;

	if (logData == NULL) return;
	int len = strlen((char*)logData);
	SD_Write_Record("ERROR_LOG",YYMMDD, hhmm, logData, len);
}

uint32_t tt1,tt2;
void SD_Test()
{
	if(!sdExist)return;
	static uint32_t timeStamp;

	if(HAL_GetTick()-timeStamp >= 1000)
	{

		timeStamp = HAL_GetTick();
		tt1 = timeStamp;
		SD_Error_Save(m_io.day,m_io.hhmm,"test");
		printf("%08lu\r\n",timeStamp);
		tt2= HAL_GetTick() -tt1;
	}

}

void Error_Check_Config()
{
	static uint32_t timeStamp;
	if(!m_rf.sysChkFlag) return;
//	if(m_eep.cartDataMoving) return;

	Check_Cart_Req_Config();
	if(HAL_GetTick()-timeStamp >= 1000)
	{
		Error_Check_Main();
		Error_Check_HP();
		Error_Check_RF();
		Error_Led_View();

		timeStamp = HAL_GetTick();
	}
}

