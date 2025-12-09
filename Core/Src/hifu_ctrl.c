

#include "hifu_ctrl.h"
uint8_t testExpFlag;
ERROR_T m_err = {
    .errBuffMsg = {
        "DUMY",
        "TEMP_OUT",
        "TEMP_LIMIT_UNDER",
        "TEMP_LOW",
        "FLOW_LIMIT_UNDER",
        "FLOW_ZERO_IDX",
        "LEVEL_LOW",
        "AUTO_CAL_COMU_ERR",
        "BATTRY_LIMIT_OVER",
        "BATTRY_LIMIT_UNDER",
        "BATTRY_LIMIT_LOW",
        "RTC_ERR",
        "PRE_COOL_ERR",
        "HAND_COMU_ERR",
        "CATRIGE_ID_ERR",
        "CATRIGE_MANU_ERR",
        "CATRIGE_MANU_OVER_ERR",
        "CATRIGE_ISUE_ERR",
        "CATRIGE_ISUE_OVER_ERR",
        "CATRIGE_WATT_ERR",
        "CATRIGE_FRQ_ERR",
        "CATRIGE_RESHOT_ERR",
        "CATRIGE_RESHOT_LOW",
        "CATRIGE_RESHOT_ZERO",
        "CATRIGE_DETECT",
        "CATRIGE_UN_DETECT",
        "RF_COMU_ERR",
        "RF_STATUS_ERR"
    }
};


RF_T m_rf;
EEPROM_T m_eep =
{
//	.rfFrqBuff = {0, 11000, 11000, 11000, 11000, 11000, 11000, 11000},
//	.rfFrqBuff = {0, 11035, 11027, 10962, 10992, 11062, 11045, 11060},//td no 1
	.rfFrqBuff = {0, 11090, 11037, 11030, 11025, 11102, 10972, 11115},//td no 2

};

HAND_T m_hand1;

int AutoWattDefulteTable[78] =
{
255,
11,10,9,8,7,6,5,4,3,2,1,
11,10,9,8,7,6,5,4,3,2,1,
11,10,9,8,7,6,5,4,3,2,1,
11,10,9,8,7,6,5,4,3,2,1,
11,10,9,8,7,6,5,4,3,2,1,
11,10,9,8,7,6,5,4,3,2,1,
11,10,9,8,7,6,5,4,3,2,1
};
uint8_t AutoDaDefulteTable[78];


uint32_t watt[5] ={10,100,5,20,30};
void Test_Init()
{
//	AutoCal_Avg();
}

void Rf_TD1_Table()
{
	//frq
	m_eep.rfFrqBuff[0] = 0;
	m_eep.rfFrqBuff[1] = 11035;
	m_eep.rfFrqBuff[2] = 11027;
	m_eep.rfFrqBuff[3] = 10962;
	m_eep.rfFrqBuff[4] = 10992;
	m_eep.rfFrqBuff[5] = 11062;
	m_eep.rfFrqBuff[6] = 11045;
	m_eep.rfFrqBuff[7] = 11060;
}

void Rf_TD2_Table()
{
	//frq
	m_eep.rfFrqBuff[0] = 0;
	m_eep.rfFrqBuff[1] = 11090;
	m_eep.rfFrqBuff[2] = 11037;
	m_eep.rfFrqBuff[3] = 11030;
	m_eep.rfFrqBuff[4] = 11025;
	m_eep.rfFrqBuff[5] = 11102;
	m_eep.rfFrqBuff[6] = 10972;
	m_eep.rfFrqBuff[7] = 11115;

	//no1
	m_eep.rfWattBuff[0]		= 0;
	m_eep.rfWattBuff[1]		= 1;		//0.1
	m_eep.rfWattBuff[2]		= 17;		//0.2
	m_eep.rfWattBuff[3]		= 34;		//0.3
	m_eep.rfWattBuff[4]		= 51;		//0.4
	m_eep.rfWattBuff[5]		= 68;		//0.5
	m_eep.rfWattBuff[6]		= 80;		//0.6
	m_eep.rfWattBuff[7]		= 97;		//0.7
	m_eep.rfWattBuff[8]		= 110;		//0.8
	m_eep.rfWattBuff[9]		= 126;		//0.9
	m_eep.rfWattBuff[10]	= 143;		//1.0
	m_eep.rfWattBuff[11]	= 160;		//
	//no2
	m_eep.rfWattBuff[12]	= 1	;		//0.1
	m_eep.rfWattBuff[13]	= 17;		//0.2
	m_eep.rfWattBuff[14]	= 35;		//0.3
	m_eep.rfWattBuff[15]	= 50;		//0.4
	m_eep.rfWattBuff[16]	= 64;		//0.5
	m_eep.rfWattBuff[17]	= 79;		//0.6
	m_eep.rfWattBuff[18]	= 94;		//0.7
	m_eep.rfWattBuff[19]	= 107;		//0.8
	m_eep.rfWattBuff[20]	= 120;		//0.9
	m_eep.rfWattBuff[21]	= 135;		//1.0
	m_eep.rfWattBuff[22]	= 160;		//
	//no3
	m_eep.rfWattBuff[23]	= 1	;		//0.1
	m_eep.rfWattBuff[24]	= 18;		//0.2
	m_eep.rfWattBuff[25]	= 33;		//0.3
	m_eep.rfWattBuff[26]	= 50;		//0.4
	m_eep.rfWattBuff[27]	= 66;		//0.5
	m_eep.rfWattBuff[28]	= 82;		//0.6
	m_eep.rfWattBuff[29]	= 95;		//0.7
	m_eep.rfWattBuff[30]	= 110;		//0.8
	m_eep.rfWattBuff[31]	= 122;		//0.9
	m_eep.rfWattBuff[32]	= 139;		//1.0
	m_eep.rfWattBuff[33]	= 160;		//
	//no4
	m_eep.rfWattBuff[34]	= 1	;		//0.1
	m_eep.rfWattBuff[35]	= 19;		//0.2
	m_eep.rfWattBuff[36]	= 37;		//0.3
	m_eep.rfWattBuff[37]	= 53;		//0.4
	m_eep.rfWattBuff[38]	= 72;		//0.5
	m_eep.rfWattBuff[39]	= 86;		//0.6
	m_eep.rfWattBuff[40]	= 100;		//0.7
	m_eep.rfWattBuff[41]	= 115;		//0.8
	m_eep.rfWattBuff[42]	= 130;		//0.9
	m_eep.rfWattBuff[43]	= 145;		//1.0
	m_eep.rfWattBuff[44]	= 160;		//
	//no5
	m_eep.rfWattBuff[45]	= 1	;		//0.1
	m_eep.rfWattBuff[46]	= 25;		//0.2
	m_eep.rfWattBuff[47]	= 42;		//0.3
	m_eep.rfWattBuff[48]	= 61;		//0.4
	m_eep.rfWattBuff[49]	= 76;		//0.5
	m_eep.rfWattBuff[50]	= 88;		//0.6
	m_eep.rfWattBuff[51]	= 103;		//0.7
	m_eep.rfWattBuff[52]	= 115;		//0.8
	m_eep.rfWattBuff[53]	= 129;		//0.9
	m_eep.rfWattBuff[54]	= 146;		//1.0
	m_eep.rfWattBuff[55]	= 160;		//
	//no6
	m_eep.rfWattBuff[56]	= 1	;		//0.1
	m_eep.rfWattBuff[57]	= 18;		//0.2
	m_eep.rfWattBuff[58]	= 34;		//0.3
	m_eep.rfWattBuff[59]	= 48;		//0.4
	m_eep.rfWattBuff[60]	= 63;		//0.5
	m_eep.rfWattBuff[61]	= 78;		//0.6
	m_eep.rfWattBuff[62]	= 88;		//0.7
	m_eep.rfWattBuff[63]	= 104;		//0.8
	m_eep.rfWattBuff[64]	= 119;		//0.9
	m_eep.rfWattBuff[65]	= 133;		//1.0
	m_eep.rfWattBuff[66]	= 160;		//
	//no7
	m_eep.rfWattBuff[67]	= 1	;		//0.1
	m_eep.rfWattBuff[68]	= 25;		//0.2
	m_eep.rfWattBuff[69]	= 41;		//0.3
	m_eep.rfWattBuff[70]	= 60;		//0.4
	m_eep.rfWattBuff[71]	= 75;		//0.5
	m_eep.rfWattBuff[72]	= 90;		//0.6
	m_eep.rfWattBuff[73]	= 103;		//0.7
	m_eep.rfWattBuff[74]	= 116;		//0.8
	m_eep.rfWattBuff[75]	= 132;		//0.9
	m_eep.rfWattBuff[76]	= 145;		//1.0
	m_eep.rfWattBuff[77]	= 160;		//

}

void Rf_Init()
{
	m_rf.pluseOn = 0;
	m_rf.pluseLevel = 0;
	m_rf.pluseTimeStamp = HAL_GetTick();
	m_eep.remainingShotNum = 10000;
	HAL_GPIO_WritePin(RF_Pulse_Signal_GPIO_Port, RF_Pulse_Signal_Pin ,SOF_LOW);
	HAL_Delay(1500);
	RF_Pwr_ON();


	#if 0
	Rf_TD1_Table();
	#else
	Rf_TD2_Table();
	#endif
	m_rf.testPulseOption = 2;

	m_rf.pulseMaxBuff[IDX_MAIN_P1_WATT]			= 10;
	m_rf.pulseMaxBuff[IDX_MAIN_P1_DURATION_TIME]= 50;
	m_rf.pulseMaxBuff[IDX_MAIN_P1_INTERVAL_TIME]= 50;
	m_rf.pulseMaxBuff[IDX_MAIN_P2_WATT]         = 10;
	m_rf.pulseMaxBuff[IDX_MAIN_P2_DURATION_TIME]= 50;
	m_rf.pulseMaxBuff[IDX_MAIN_P2_INTERVAL_TIME]= 50;
	m_rf.pulseMaxBuff[IDX_MAIN_P3_WATT]         = 10;
	m_rf.pulseMaxBuff[IDX_MAIN_P3_DURATION_TIME]= 50;
	m_rf.pulseMaxBuff[IDX_MAIN_P3_INTERVAL_TIME]= 50;
	m_rf.pulseMaxBuff[IDX_MAIN_P4_WATT]         = 10;
	m_rf.pulseMaxBuff[IDX_MAIN_P4_DURATION_TIME]= 50;
	m_rf.pulseMaxBuff[IDX_MAIN_POSTCO0L_TIME]   = 30;

	m_rf.pulseMinBuff[IDX_MAIN_P1_WATT]			= 1;
	m_rf.pulseMinBuff[IDX_MAIN_P1_DURATION_TIME]= 10;
	m_rf.pulseMinBuff[IDX_MAIN_P1_INTERVAL_TIME]= 0;
	m_rf.pulseMinBuff[IDX_MAIN_P2_WATT]         = 1;
	m_rf.pulseMinBuff[IDX_MAIN_P2_DURATION_TIME]= 10;
	m_rf.pulseMinBuff[IDX_MAIN_P2_INTERVAL_TIME]= 0;
	m_rf.pulseMinBuff[IDX_MAIN_P3_WATT]         = 1;
	m_rf.pulseMinBuff[IDX_MAIN_P3_DURATION_TIME]= 10;
	m_rf.pulseMinBuff[IDX_MAIN_P3_INTERVAL_TIME]= 0;
	m_rf.pulseMinBuff[IDX_MAIN_P4_WATT]         = 1;
	m_rf.pulseMinBuff[IDX_MAIN_P4_DURATION_TIME]= 10;
	m_rf.pulseMinBuff[IDX_MAIN_POSTCO0L_TIME]   = 0;



}
void Hand_Init()
{
	m_eep.catridgeDetectPre = CATRIGE_DETECT;
	m_eep.catridgeDetect = CATRIGE_DETECT;
}
void LCD_Init()
{
	HAL_Delay(500);



	PulseData_Sand(IDX_MAIN_P1_WATT, 2);
	PulseData_Sand(IDX_MAIN_P1_DURATION_TIME, 10);
	PulseData_Sand(IDX_MAIN_P1_INTERVAL_TIME, 5);
	PulseData_Sand(IDX_MAIN_P2_WATT, 4);
	PulseData_Sand(IDX_MAIN_P2_DURATION_TIME, 15);
	PulseData_Sand(IDX_MAIN_P2_INTERVAL_TIME, 5);
	PulseData_Sand(IDX_MAIN_P3_WATT, 6);
	PulseData_Sand(IDX_MAIN_P3_DURATION_TIME, 20);
	PulseData_Sand(IDX_MAIN_P3_INTERVAL_TIME, 5);
	PulseData_Sand(IDX_MAIN_P4_WATT, 8);
	PulseData_Sand(IDX_MAIN_P4_DURATION_TIME, 25);
	PulseData_Sand(IDX_MAIN_POSTCO0L_TIME, 10);

	PulseEn_Sand(1, PULSE_ENABLE);
	PulseEn_Sand(2, PULSE_ENABLE);
	PulseEn_Sand(3, PULSE_ENABLE);
	PulseEn_Sand(4, PULSE_ENABLE);

	m_rf.currentShot = 0;
	m_rf.totaEnergy = 0;
	Tx_LCD_Msg(CMD_TOTAL_JOULE, m_rf.totaEnergy);
	Tx_LCD_Msg(CMD_CURRENT_SHOT, m_rf.currentShot);

	Tx_LCD_Msg(CMD_LCD_STATUS, STATUS_STNBY);

}

void PulseData_Sand(uint8_t num, uint16_t data)
{
	uint16_t pulseData;
	if(num>12)return;

	m_rf.pulseBuff[num] = data;
	pulseData = num*100 + data;
	Tx_LCD_Msg(CMD_PLUSE_VALUE, pulseData);

}
void PulseEn_Sand(uint8_t num, uint16_t enDis)
{
	uint16_t pulseData;
	if(num>12)return;

	pulseData = num*10 + enDis;
	m_rf.pulseEndisBuff[num] = enDis;
	Tx_LCD_Msg(CMD_PLUSE_EN, pulseData);

}


#if 0

uint8_t Check_Common(uint8_t status, uint8_t idx, uint8_t level, uint8_t cmd)
{
	uint16_t errData;

	if(status)
	{
		if(m_err.errBuff[idx]==1)
		{
			errData = level*LEVEL_UNIT + ERR_DISABLE +cmd;
			m_err.errDataBuff[idx] = errData;

		}
		m_err.errBuff[idx] = 0;
	}
	else
	{
		if(m_err.errBuff[idx] == 0)
		{
			errData = level*LEVEL_UNIT + ERR_ENABLE +cmd;
			m_err.errDataBuff[idx] = errData;
		}
		m_err.errBuff[idx] = 1;
	}
	return m_err.errBuff[idx];

}
#else
uint8_t Check_Common(uint8_t status, uint8_t idx, uint8_t level, uint8_t cmd)
{
	uint16_t errData;

	if(status)//Nomal
	{
		if(m_err.errBuff[idx]==1)
		{
			m_err.errDataBuff[idx] = 0;
			m_err.errMemoryBuff[idx] = 0;
		}
		m_err.errBuff[idx] = 0;
	}
	else//errs
	{
		if(m_err.errBuff[idx] == 0)
		{
			errData = level*LEVEL_UNIT +cmd;
			m_err.errDataBuff[idx] = errData;
			m_err.errMemoryBuff[idx] = errData;
		}
		m_err.errBuff[idx] = 1;
	}
	return m_err.errBuff[idx];

}

#endif

uint8_t Check_CartrigeCommon(uint8_t status, uint8_t idx, uint8_t cmd, uint8_t level)
{
	uint16_t errData;

	if(status)
	{
		errData = level*LEVEL_UNIT + ERR_DISABLE +cmd;
		m_err.errDataBuff[idx] = errData;
	}

	return 0;

}

uint8_t Check_Max_Min(int data, int max, int min, uint8_t idx, uint8_t cmd, uint8_t level)
{
	uint16_t errData;
	uint8_t status = (min <= data && data <max);
	uint8_t returnValue = 0;
	returnValue = Check_Common(status, idx, level, cmd);

	return returnValue;
}

uint8_t Check_Max(int data, int max, uint8_t idx, uint8_t cmd, uint8_t level)
{

	uint16_t errData;
	uint8_t status = (data <max);
	uint8_t returnValue = 0;
	returnValue = Check_Common(status, idx, level, cmd);

	return returnValue;

}

uint8_t Check_Min(int data, int min, uint8_t idx, uint8_t cmd, uint8_t level)
{
	uint16_t errData;
	uint8_t status = (min <= data);
	uint8_t returnValue = 0;
	returnValue = Check_Common(status, idx, level, cmd);

	return returnValue;

}


uint8_t Check_Status(int data, int nomalData, uint8_t idx, uint8_t cmd, uint8_t level)
{
	uint16_t errData;
	uint8_t status = (data == nomalData);
	uint8_t returnValue = 0;
	returnValue = Check_Common(status, idx, level, cmd);

	return returnValue;

}
uint8_t Check_CartrigeDetect(int data, int nomalData, uint8_t idx, uint8_t cmd, uint8_t level)
{
	uint16_t errData;
	uint8_t status = (data == nomalData);
	uint8_t returnValue = 0;
	returnValue = Check_CartrigeCommon(status, idx, level, cmd);

	return returnValue;

}


uint8_t Check_Day(uint16_t YY, uint16_t MM, uint16_t DD, uint8_t idx, uint8_t cmd, uint8_t level)
{
	uint16_t errData;
	uint8_t yyOk = (YY_MIN <= YY && YY <=YY_MAX);
	uint8_t mmOk = (MM_MIN <= MM && MM <=MM_MAX);
	uint8_t ddOk = (DD_MIN <= DD && DD <=DD_MAX);
	uint8_t status = (yyOk && mmOk && ddOk);
	uint8_t returnValue = 0;
	returnValue = Check_Common(status, idx, level, cmd);

	return returnValue;
}

uint8_t Check_Time(uint8_t hour, uint8_t min, uint8_t sec, uint8_t idx, uint8_t cmd, uint8_t level)
{

	uint16_t errData;
	uint8_t hourOk = (HOUR_MIN <= hour && hour <=HOUR_MAX);
	uint8_t minOk = (MIN_MIN <= min && min <=MIN_MAX);
	uint8_t secOk = (SEC_MIN <= sec && sec <=SEC_MAX);
	uint8_t status = (hourOk && minOk && secOk);
	uint8_t returnValue = 0;

	returnValue = Check_Common(status, idx, level, cmd);

	return returnValue;


}
void Error_Buff_Clear()
{
	memset(m_err.errDataBuff, 0, sizeof(m_err.errDataBuff));
	memset(m_err.errTraceBuff, 0, sizeof(m_err.errTraceBuff));
	m_err.errTraceCnt = 0;
}



void Error_Check_Check(uint8_t bordID)
{
	uint16_t errCnt = 0,errData;


	for(int i =0 ;i < IDX_ERROR_MAX;i++)
	{
		if(m_err.errDataBuff[i])
		{
//			errData = m_err.errDataBuff[i];
//			m_err.errTraceBuff[m_err.errTraceCnt++] = errData;
//			m_err.errTraceCnt %= 50;
			errCnt++;
		}
	}

	if(errCnt)
	{
		m_err.okChkCnt++;
		m_err.errStatus = 0;
		Tx_LCD_Msg(CMD_OK, bordID/* +NONE_OK_ADDR*/);
		HAL_Delay(1000);
		Error_Buff_Tx();
	}
	else
	{
		m_err.errChkCnt++;
		m_err.errStatus = 1;
		Tx_LCD_Msg(CMD_OK, bordID);
	}

}

void Error_Buff_Tx()
{
	uint16_t errData;
	for(int i =0 ;i < 50; i++)
	{
		errData = m_err.errDataBuff[i];
		errData %= 100;
		if(errData)
		{
//			Debug_Printf("Err ",0);
//			Debug_Printf(m_err.errBuffMsg[errData], 1);
			Tx_LCD_Msg(CMD_ERR, errData);
			HAL_Delay(1500);
		}
	}
}


void Error_Check_Main()
{
	Error_Buff_Clear();
#if 0
	Check_Max_Min(m_hand1.temprature, TEMP_OUT_MAX, TEMP_OUT_MIN, IDX_TEMP_OUT, IDX_TEMP_OUT, LEVEL_ERROR);//E05
	Check_Min(m_hand1.temprature, TEMP_MIN, IDX_TEMP_LIMIT_UNDER, IDX_TEMP_LIMIT_UNDER, LEVEL_ERROR);//E06

	Check_Status(m_io.level1Status, 0, IDX_LEVEL_LOW, IDX_LEVEL_LOW, LEVEL_ERROR);//E07
	Check_Min(m_io.flowSensorFrq, FLOW_LOW_MIN, IDX_FLOW_ZERO_IDX, IDX_FLOW_ZERO_IDX, LEVEL_ERROR);//E08
	Check_Max_Min(m_io.flowSensorFrq, FLOW_LOW_MAX, FLOW_LOW_MIN, IDX_FLOW_LIMIT_UNDER, IDX_FLOW_LIMIT_UNDER, LEVEL_ERROR);//E09

	Check_Max(m_io.battery, BATTRY_LIMIT_MAX, IDX_BATTRY_LIMIT_OVER, IDX_BATTRY_LIMIT_OVER, LEVEL_ERROR);//E10
	Check_Min(m_io.battery, BATTRY_LIMIT_MIN, IDX_BATTRY_LIMIT_UNDER, IDX_BATTRY_LIMIT_UNDER, LEVEL_ERROR);//E11

	Check_Status(m_err.autoCalStatus, 0, IDX_AUTO_CAL_COMU_ERR, IDX_AUTO_CAL_COMU_ERR, LEVEL_ERROR);//E12
	Check_Time(m_io.hour, m_io.min, m_io.sec, IDX_RTC_ERR, IDX_RTC_ERR, LEVEL_ERROR);//E22

	Check_Min(m_hand1.temprature, TEMP_LOW_VALUE, IDX_TEMP_LOW, IDX_TEMP_LOW, LEVEL_ALRAM);//A01
	Check_Min(m_io.battery, BATTRY_NOMAL_MIN, IDX_BATTRY_LIMIT_LOW, IDX_BATTRY_LIMIT_LOW, LEVEL_ALRAM);//A04

#endif

	uint8_t errEvent = 0;
	Error_Check_Check(OK_MAIN);

	Error_Buff_Clear();



}

void Error_Check_HP()
{
	uint8_t errStatus;
	Error_Buff_Clear();
#if 0
	if(m_eep.catridgeDetectPre != m_eep.catridgeDetect)
	{
		if(m_eep.catridgeDetect == CATRIGE_DETECT)
		{
			Check_CartrigeDetect(m_eep.catridgeDetect, CATRIGE_DETECT, IDX_CATRIGE_DETECT, IDX_CATRIGE_DETECT, LEVEL_ERROR);//E14
		}
		else
		{
			Check_CartrigeDetect(m_eep.catridgeDetect, CATRIGE_UN_DETECT, IDX_CATRIGE_UN_DETECT, IDX_CATRIGE_UN_DETECT, LEVEL_ERROR);//E14
		}

		m_eep.catridgeDetectPre = m_eep.catridgeDetect;
	}

	m_err.handTimeout++;
	if(m_err.handTimeout >= 5)
	{
//		m_err.handTimeout = 0;
		Check_Max(m_err.handTimeout, COMU_MAX_CNT, IDX_HAND_COMU_ERR, IDX_HAND_COMU_ERR, LEVEL_ERROR);//E04
	}

	m_eep.manufacDay = m_eep.manufacYY*10000 + m_eep.manufacMM*100 + m_eep.manufacDD;
	m_eep.issuedDay = m_eep.issuedYY*10000 + m_eep.issuedMM*100 + m_eep.issuedDD;


	Check_Day(m_eep.manufacYY, m_eep.manufacMM, m_eep.manufacDD, IDX_CATRIGE_MANU_ERR, IDX_CATRIGE_MANU_ERR, LEVEL_ERROR);//E16
	Check_Day(m_eep.issuedYY, m_eep.issuedMM, m_eep.issuedDD, IDX_CATRIGE_ISUE_ERR, IDX_CATRIGE_ISUE_ERR, LEVEL_ERROR);//E17

	for(int i = 1; i <= 7; i++)
	{
		errStatus = Check_Max_Min(m_eep.rfFrqBuff[i], CATRIDGE_FRQ_MAX, CATRIDGE_FRQ_MIN, IDX_CATRIGE_FRQ_ERR, IDX_CATRIGE_FRQ_ERR, LEVEL_ERROR);//E18
		if(errStatus) break;
	}
	for(int i = 1; i <= 77; i++)
	{
		errStatus = Check_Max_Min(m_eep.rfWattBuff[i], CATRIDGE_WATT_MAX, CATRIDGE_WATT_MIN, IDX_CATRIGE_WATT_ERR, IDX_CATRIGE_WATT_ERR, LEVEL_ERROR);//E19
		if(errStatus) break;
	}
	Check_Max(m_eep.remainingShotNum, CATRIDGE_REMAIN_MAX, IDX_CATRIGE_RESHOT_ERR, IDX_CATRIGE_RESHOT_ERR, LEVEL_ERROR);//E21

	Check_Max(m_eep.catridgeId, CATRIDGE_ID_MAX, IDX_CATRIGE_ID_ERR, IDX_CATRIGE_ID_ERR, LEVEL_ERROR);//E23

	Check_Max(m_io.day, m_eep.manufacDay + DAY_MAX, IDX_CATRIGE_MANU_OVER_ERR, IDX_CATRIGE_MANU_OVER_ERR, LEVEL_ERROR);//E24
	Check_Max(m_io.day, m_eep.issuedDay + DAY_MAX, IDX_CATRIGE_ISUE_OVER_ERR, IDX_CATRIGE_ISUE_OVER_ERR, LEVEL_ERROR);//E25
	Check_Status(m_err.preCoolStatus, 0, IDX_PRE_COOL_ERR, IDX_PRE_COOL_ERR, LEVEL_ERROR);//E15

	Check_Min(m_eep.remainingShotNum, CATRIDGE_REMAIN_LOW_3, IDX_CATRIGE_RESHOT_LOW, IDX_CATRIGE_RESHOT_LOW, LEVEL_ERROR);//A02
	Check_Min(m_eep.remainingShotNum, CATRIDGE_REMAIN_MIN, IDX_CATRIGE_RESHOT_ZERO, IDX_CATRIGE_RESHOT_ZERO, LEVEL_ERROR);//A06

#endif

	Error_Check_Check(OK_HP);
	Error_Buff_Clear();

}

void Error_Check_RF()
{
	Error_Buff_Clear();
#if 0
	m_err.rfTimeout++;
	Tx_RF_GenStatus_Check();
	Check_Max(m_err.rfTimeout, COMU_MAX_CNT, IDX_RF_COMU_ERR, IDX_RF_COMU_ERR, LEVEL_ERROR);//E02
	if(m_err.rfTimeout > 5) m_err.rfTimeout = 0;

	Check_Status(m_err.rfStatus, 0, IDX_RF_STATUS_ERR, IDX_RF_STATUS_ERR, LEVEL_ERROR);//E14
#endif

	Error_Check_Check(OK_RF);
	Error_Buff_Clear();

}

void Error_Check_Config()
{
	static uint8_t reCnt = 0;
	static uint32_t timeStamp;
	uint8_t errStatus;

	if(HAL_GetTick()-timeStamp >= 2000)
	{
		Error_Check_Main();
		Error_Check_HP();
		Error_Check_RF();

		timeStamp = HAL_GetTick();
	}




}


void Hand1_Poling_Ctrl(int add, int data1, int data2, int data3, int data4)
{

	if(add != CMD_HP1_ADD)return;

	m_hand1.mode = data1;
	m_hand1.pwmDuty = data2;
	m_hand1.temprature = data3;
	m_hand1.ioStatus = data4;

}

void RF_Watt_All_Calculate()
{
	int idx;
	float wattF;
	wattF = ((float)m_rf.energy /(float)m_rf.pulseDuration);

	m_rf.watt = (uint8_t)(wattF * 10.0);
	if(m_rf.watt > MAX_WATT_IDX) m_rf.watt = MAX_WATT_IDX;

	idx = m_rf.watt;
	for(int i =0 ;i < 7; i++)
	{
		m_rf.rfwattBuff[i] = m_eep.rfWattBuff[idx+(i*11)];
	}
}


void RF_Frq_All_Calculate()
{

	for(int i =0 ;i < 7;i++)
	{
		m_rf.rfFrqBuff[i] = m_eep.rfFrqBuff[i+1];
	}
}

void Tx_RF_GenStatus_Check()
{

	uint8_t len = 0;
	uint8_t dataLen = 0;

	len = RF_NUM_FIX + 1;
	m_rf.txBuff[RF_INDEX_STX] = STX;
	m_rf.txBuff[RF_INDEX_LEN] = len;
	m_rf.txBuff[RF_INDEX_ADDR] = 'B';//ï¿½ï¿½ï¿½Ê·ï¿½ï¿½ï¿½ï¿½ï¿½ B, ï¿½Ã½ï¿½ï¿½ï¿½ b
	m_rf.txBuff[RF_INDEX_CMD] = GEN_STATUS_CHECK;

	m_rf.txBuff[RF_INDEX_DATA] = 0x00;
	dataLen = 3;


	for(int i =0 ;i <= RF_INDEX_DATA ;i++)
	{
		m_rf.txBuff[RF_INDEX_DATA+1] ^= m_rf.txBuff[i];
	}

	m_rf.txBuff[RF_INDEX_DATA+2] = ETX;
	Debug_Tx_GenStatus_Check_Printf();
	Tx_RF_Msg(m_rf.txBuff, len);
	memset(m_rf.txBuff, 0, 30);

}




void Tx_RF_FRQ_Module(uint8_t ch, uint16_t frequency)
{

	uint8_t len = 0;
	uint8_t dataLen = 0;

	len = RF_NUM_FIX + 3;
	m_rf.txBuff[RF_INDEX_STX] = STX;
	m_rf.txBuff[RF_INDEX_LEN] = len;
	m_rf.txBuff[RF_INDEX_ADDR] = 'B';//ï¿½ï¿½ï¿½Ê·ï¿½ï¿½ï¿½ï¿½ï¿½ B, ï¿½Ã½ï¿½ï¿½ï¿½ b
	m_rf.txBuff[RF_INDEX_CMD] = GEN_FREQ_SET;

	m_rf.txBuff[RF_INDEX_DATA] = ch+1;
	m_rf.txBuff[RF_INDEX_DATA+1] = (frequency>>8)&0xff;
	m_rf.txBuff[RF_INDEX_DATA+2] = (frequency)&0xff;
	dataLen = 3;


	for(int i =0 ;i <= RF_INDEX_DATA+2 ;i++)
	{
		m_rf.txBuff[RF_INDEX_DATA+3] ^= m_rf.txBuff[i];
	}
	m_rf.txBuff[RF_INDEX_DATA+4] = ETX;
	Debug_Tx_RF_Frq_Printf(ch+1, frequency);
	Tx_RF_Msg(m_rf.txBuff, len);
	memset(m_rf.txBuff, 0, 30);

}




void Tx_RF_Watt_Module(uint8_t ch, uint16_t watt)
{

	uint8_t len = 0;
	uint8_t dataLen = 0;

	len = RF_NUM_FIX + 3;
	m_rf.txBuff[RF_INDEX_STX] = STX;
	m_rf.txBuff[RF_INDEX_LEN] = len;
	m_rf.txBuff[RF_INDEX_ADDR] = 'B';//ï¿½ï¿½ï¿½Ê·ï¿½ï¿½ï¿½ï¿½ï¿½ B, ï¿½Ã½ï¿½ï¿½ï¿½ b
	m_rf.txBuff[RF_INDEX_CMD] = GEN_OUTPUT_SET;

	m_rf.txBuff[RF_INDEX_DATA] = ch+1;
	m_rf.txBuff[RF_INDEX_DATA+1] = (watt>>8)&0xff;
	m_rf.txBuff[RF_INDEX_DATA+2] = (watt)&0xff;
	dataLen = 3;


	for(int i =0 ;i <= RF_INDEX_DATA+2 ;i++)
	{
		m_rf.txBuff[RF_INDEX_DATA+3] ^= m_rf.txBuff[i];
	}

	m_rf.txBuff[RF_INDEX_DATA+4] = ETX;
	int indData = 0;
	Debug_Tx_RF_Watt_Printf(ch+1, watt);
	Tx_RF_Msg(m_rf.txBuff, len);
	memset(m_rf.txBuff, 0, 30);

}




void Tx_RF_FRQ_ALL_Module( )
{

	uint8_t len = 0;

	len = RF_NUM_FIX + 16;
	m_rf.txBuff[RF_INDEX_STX] = STX;
	m_rf.txBuff[RF_INDEX_LEN] = len;
	m_rf.txBuff[RF_INDEX_ADDR] = 'B';//ï¿½ï¿½ï¿½Ê·ï¿½ï¿½ï¿½ï¿½ï¿½ B, ï¿½Ã½ï¿½ï¿½ï¿½ b
	m_rf.txBuff[RF_INDEX_CMD] = ALL_CH_FREQ_SET;

	RF_Frq_All_Calculate();


	m_rf.txBuff[RF_INDEX_DATA+0] = (m_rf.rfFrqBuff[RF_FRQ_CH0]>>8)&0xff;
	m_rf.txBuff[RF_INDEX_DATA+1] = (m_rf.rfFrqBuff[RF_FRQ_CH0])&0xff;

	m_rf.txBuff[RF_INDEX_DATA+2] = (m_rf.rfFrqBuff[RF_FRQ_CH1]>>8)&0xff;
	m_rf.txBuff[RF_INDEX_DATA+3] = (m_rf.rfFrqBuff[RF_FRQ_CH1])&0xff;

	m_rf.txBuff[RF_INDEX_DATA+4] = (m_rf.rfFrqBuff[RF_FRQ_CH2]>>8)&0xff;
	m_rf.txBuff[RF_INDEX_DATA+5] = (m_rf.rfFrqBuff[RF_FRQ_CH2])&0xff;

	m_rf.txBuff[RF_INDEX_DATA+6] = (m_rf.rfFrqBuff[RF_FRQ_CH3]>>8)&0xff;
	m_rf.txBuff[RF_INDEX_DATA+7] = (m_rf.rfFrqBuff[RF_FRQ_CH3])&0xff;

	m_rf.txBuff[RF_INDEX_DATA+8] = (m_rf.rfFrqBuff[RF_FRQ_CH4]>>8)&0xff;
	m_rf.txBuff[RF_INDEX_DATA+9] = (m_rf.rfFrqBuff[RF_FRQ_CH4])&0xff;

	m_rf.txBuff[RF_INDEX_DATA+10] = (m_rf.rfFrqBuff[RF_FRQ_CH5]>>8)&0xff;
	m_rf.txBuff[RF_INDEX_DATA+11] = (m_rf.rfFrqBuff[RF_FRQ_CH5])&0xff;

	m_rf.txBuff[RF_INDEX_DATA+12] = (m_rf.rfFrqBuff[RF_FRQ_CH6]>>8)&0xff;
	m_rf.txBuff[RF_INDEX_DATA+13] = (m_rf.rfFrqBuff[RF_FRQ_CH6])&0xff;

	m_rf.txBuff[RF_INDEX_DATA+14] = (m_rf.rfFrqBuff[RF_FRQ_CH6]>>8)&0xff;
	m_rf.txBuff[RF_INDEX_DATA+15] = (m_rf.rfFrqBuff[RF_FRQ_CH6])&0xff;

	for(int i =0 ;i <= RF_INDEX_DATA+15 ;i++)
	{
		m_rf.txBuff[RF_INDEX_DATA+16] ^= m_rf.txBuff[i];
	}
	m_rf.txBuff[RF_INDEX_DATA+17] = ETX;
	Debug_Tx_RF_All_Frq_Printf();
	Tx_RF_Msg(m_rf.txBuff, len);
	memset(m_rf.txBuff, 0, 30);

}




void Tx_RF_Watt_ALL_Module_org( )
{

	uint8_t len = 0;
	ddTimeStart1(); //wndksdebug
	len = RF_NUM_FIX + 16;
	m_rf.txBuff[RF_INDEX_STX] = STX;
	m_rf.txBuff[RF_INDEX_LEN] = len;
	m_rf.txBuff[RF_INDEX_ADDR] = 'B';//ï¿½ï¿½ï¿½Ê·ï¿½ï¿½ï¿½ï¿½ï¿½ B, ï¿½Ã½ï¿½ï¿½ï¿½ b
	m_rf.txBuff[RF_INDEX_CMD] = ALL_CH_OUTPUT_SET;

	RF_Watt_All_Calculate();
	m_rf.txBuff[RF_INDEX_DATA+0] = (m_rf.rfwattBuff[RF_WATT_CH0]>>8)&0xff;
	m_rf.txBuff[RF_INDEX_DATA+1] = (m_rf.rfwattBuff[RF_WATT_CH0])&0xff;

	m_rf.txBuff[RF_INDEX_DATA+2] = (m_rf.rfwattBuff[RF_WATT_CH1]>>8)&0xff;
	m_rf.txBuff[RF_INDEX_DATA+3] = (m_rf.rfwattBuff[RF_WATT_CH1])&0xff;

	m_rf.txBuff[RF_INDEX_DATA+4] = (m_rf.rfwattBuff[RF_WATT_CH2]>>8)&0xff;
	m_rf.txBuff[RF_INDEX_DATA+5] = (m_rf.rfwattBuff[RF_WATT_CH2])&0xff;

	m_rf.txBuff[RF_INDEX_DATA+6] = (m_rf.rfwattBuff[RF_WATT_CH3]>>8)&0xff;
	m_rf.txBuff[RF_INDEX_DATA+7] = (m_rf.rfwattBuff[RF_WATT_CH3])&0xff;

	m_rf.txBuff[RF_INDEX_DATA+8] = (m_rf.rfwattBuff[RF_WATT_CH4]>>8)&0xff;
	m_rf.txBuff[RF_INDEX_DATA+9] = (m_rf.rfwattBuff[RF_WATT_CH4])&0xff;

	m_rf.txBuff[RF_INDEX_DATA+10] = (m_rf.rfwattBuff[RF_WATT_CH5]>>8)&0xff;
	m_rf.txBuff[RF_INDEX_DATA+11] = (m_rf.rfwattBuff[RF_WATT_CH5])&0xff;

	m_rf.txBuff[RF_INDEX_DATA+12] = (m_rf.rfwattBuff[RF_WATT_CH6]>>8)&0xff;
	m_rf.txBuff[RF_INDEX_DATA+13] = (m_rf.rfwattBuff[RF_WATT_CH6])&0xff;

	m_rf.txBuff[RF_INDEX_DATA+14] = (m_rf.rfwattBuff[RF_WATT_CH6]>>8)&0xff;
	m_rf.txBuff[RF_INDEX_DATA+15] = (m_rf.rfwattBuff[RF_WATT_CH6])&0xff;


	for(int i =0 ;i <= RF_INDEX_DATA+15 ;i++)
	{
		m_rf.txBuff[RF_INDEX_DATA+16] ^= m_rf.txBuff[i];
	}
	m_rf.txBuff[RF_INDEX_DATA+17] = ETX;
	Debug_Tx_RF_All_Watt_Printf();
	Tx_RF_Msg(m_rf.txBuff, len);
	memset(m_rf.txBuff, 0, 30);
	ddTimeEnd1(); //wndksdebug

}




void Tx_RF_Watt_ALL_Module(uint16_t watt, uint8_t pulseStep)
{

	uint8_t len = 0;
	static uint8_t pulseStepPre;


//	if(pulseStep == m_rf.pulsePreHigh) return;
//	m_rf.pulsePreHigh = pulseStep;


	ddTimeStart1(); //wndksdebug
	len = RF_NUM_FIX + 16;
	m_rf.txBuff[RF_INDEX_STX] = STX;
	m_rf.txBuff[RF_INDEX_LEN] = len;
	m_rf.txBuff[RF_INDEX_ADDR] = 'B';//ï¿½ï¿½ï¿½Ê·ï¿½ï¿½ï¿½ï¿½ï¿½ B, ï¿½Ã½ï¿½ï¿½ï¿½ b
	m_rf.txBuff[RF_INDEX_CMD] = ALL_CH_OUTPUT_SET;



	m_rf.watt = watt;
	if(m_rf.watt > MAX_WATT_IDX) m_rf.watt = MAX_WATT_IDX;
	int idx = m_rf.watt;
	for(int i =0 ;i < 7; i++)
	{
		m_rf.rfwattBuff[i] = m_eep.rfWattBuff[idx+(i*11)];
	}

	m_rf.txBuff[RF_INDEX_DATA+0] = (m_rf.rfwattBuff[RF_WATT_CH0]>>8)&0xff;
	m_rf.txBuff[RF_INDEX_DATA+1] = (m_rf.rfwattBuff[RF_WATT_CH0])&0xff;

	m_rf.txBuff[RF_INDEX_DATA+2] = (m_rf.rfwattBuff[RF_WATT_CH1]>>8)&0xff;
	m_rf.txBuff[RF_INDEX_DATA+3] = (m_rf.rfwattBuff[RF_WATT_CH1])&0xff;

	m_rf.txBuff[RF_INDEX_DATA+4] = (m_rf.rfwattBuff[RF_WATT_CH2]>>8)&0xff;
	m_rf.txBuff[RF_INDEX_DATA+5] = (m_rf.rfwattBuff[RF_WATT_CH2])&0xff;

	m_rf.txBuff[RF_INDEX_DATA+6] = (m_rf.rfwattBuff[RF_WATT_CH3]>>8)&0xff;
	m_rf.txBuff[RF_INDEX_DATA+7] = (m_rf.rfwattBuff[RF_WATT_CH3])&0xff;

	m_rf.txBuff[RF_INDEX_DATA+8] = (m_rf.rfwattBuff[RF_WATT_CH4]>>8)&0xff;
	m_rf.txBuff[RF_INDEX_DATA+9] = (m_rf.rfwattBuff[RF_WATT_CH4])&0xff;

	m_rf.txBuff[RF_INDEX_DATA+10] = (m_rf.rfwattBuff[RF_WATT_CH5]>>8)&0xff;
	m_rf.txBuff[RF_INDEX_DATA+11] = (m_rf.rfwattBuff[RF_WATT_CH5])&0xff;

	m_rf.txBuff[RF_INDEX_DATA+12] = (m_rf.rfwattBuff[RF_WATT_CH6]>>8)&0xff;
	m_rf.txBuff[RF_INDEX_DATA+13] = (m_rf.rfwattBuff[RF_WATT_CH6])&0xff;

	m_rf.txBuff[RF_INDEX_DATA+14] = (m_rf.rfwattBuff[RF_WATT_CH6]>>8)&0xff;
	m_rf.txBuff[RF_INDEX_DATA+15] = (m_rf.rfwattBuff[RF_WATT_CH6])&0xff;


	for(int i =0 ;i <= RF_INDEX_DATA+15 ;i++)
	{
		m_rf.txBuff[RF_INDEX_DATA+16] ^= m_rf.txBuff[i];
	}
	m_rf.txBuff[RF_INDEX_DATA+17] = ETX;
	Debug_Tx_RF_All_Watt_Printf();
	Tx_RF_Msg(m_rf.txBuff, len);
	memset(m_rf.txBuff, 0, 30);


}



void TX_RF_Max_Ontime_Set()
{
	uint8_t len;

	len = RF_NUM_FIX + 2;
	m_rf.txBuff[RF_INDEX_STX] = STX;
	m_rf.txBuff[RF_INDEX_LEN] = len;
	m_rf.txBuff[RF_INDEX_ADDR] = 'B';//ï¿½ï¿½ï¿½Ê·ï¿½ï¿½ï¿½ï¿½ï¿½ B, ï¿½Ã½ï¿½ï¿½ï¿½ b
	m_rf.txBuff[RF_INDEX_CMD] = GEN_MAX_ON_TIME_SET;

	m_rf.txBuff[RF_INDEX_DATA] = (MAX_ONTIME>>8)&0xff;
	m_rf.txBuff[RF_INDEX_DATA+1] = (MAX_ONTIME)&0xff;


	for(int i =0 ;i <= RF_INDEX_DATA+1 ;i++)
	{
		m_rf.txBuff[RF_INDEX_DATA+2] ^= m_rf.txBuff[i];
	}
	m_rf.txBuff[RF_INDEX_DATA+3] = ETX;
	Debug_Tx_RF_MaxOntime_Printf();
	Tx_RF_Msg(m_rf.txBuff, len);
	memset(m_rf.txBuff, 0, 30);
}


void Tx_RF_Watt_Zero_ALL_Module( )
{

	uint8_t len = 0;

	len = RF_NUM_FIX + 16;
	m_rf.txBuff[RF_INDEX_STX] = STX;
	m_rf.txBuff[RF_INDEX_LEN] = len;
	m_rf.txBuff[RF_INDEX_ADDR] = 'B';//ï¿½ï¿½ï¿½Ê·ï¿½ï¿½ï¿½ï¿½ï¿½ B, ï¿½Ã½ï¿½ï¿½ï¿½ b
	m_rf.txBuff[RF_INDEX_CMD] = ALL_CH_OUTPUT_SET;

	RF_Watt_All_Calculate();
	m_rf.txBuff[RF_INDEX_DATA+0] = 0;
	m_rf.txBuff[RF_INDEX_DATA+1] = 0;

	m_rf.txBuff[RF_INDEX_DATA+2] = 0;
	m_rf.txBuff[RF_INDEX_DATA+3] = 0;

	m_rf.txBuff[RF_INDEX_DATA+4] = 0;
	m_rf.txBuff[RF_INDEX_DATA+5] = 0;

	m_rf.txBuff[RF_INDEX_DATA+6] = 0;
	m_rf.txBuff[RF_INDEX_DATA+7] = 0;

	m_rf.txBuff[RF_INDEX_DATA+8] = 0;
	m_rf.txBuff[RF_INDEX_DATA+9] = 0;

	m_rf.txBuff[RF_INDEX_DATA+10] = 0;
	m_rf.txBuff[RF_INDEX_DATA+11] = 0;

	m_rf.txBuff[RF_INDEX_DATA+12] = 0;
	m_rf.txBuff[RF_INDEX_DATA+13] = 0;

	m_rf.txBuff[RF_INDEX_DATA+14] = 0;
	m_rf.txBuff[RF_INDEX_DATA+15] = 0;

	for(int i =0 ;i <= RF_INDEX_DATA+15 ;i++)
	{
		m_rf.txBuff[RF_INDEX_DATA+16] ^= m_rf.txBuff[i];
	}
	m_rf.txBuff[RF_INDEX_DATA+17] = ETX;
	Debug_Tx_RF_All_Zero_Watt_Printf();
	Tx_RF_Msg(m_rf.txBuff, len);
	memset(m_rf.txBuff, 0, 30);

}


void Rx_RF_Get(uint8_t getData)
{
	m_rf.rxBuff[m_rf.rxCnt] = getData;
	m_rf.rxCnt++;
	m_rf.rxCnt %= 30;

	m_rf.lastTimeStamp = HAL_GetTick();
}
void RF_Pwm_On()
{
	uint16_t pulse1Watt = m_rf.pulseBuff[IDX_MAIN_P1_WATT];
	Tx_RF_Watt_ALL_Module(pulse1Watt, PWM_H1_LEVEL );
	m_rf.pluseOn = 1;
	m_rf.pluseLevel = PWM_H1_LEVEL;
	m_rf.pluseTimeStamp = HAL_GetTick();
	m_rf.pulsePreHigh = 0xFF;

	m_rf.pulseEndisChkBuff[1] = 0;
	m_rf.pulseEndisChkBuff[2] = 0;
	m_rf.pulseEndisChkBuff[3] = 0;
	m_rf.pulseEndisChkBuff[4] = 0;
}

void RF_eg_Exp_On()
{
	m_rf.egExpOn = 1;
	m_rf.pluseEgTimeStamp = HAL_GetTick();
	HAL_GPIO_WritePin(RF_Pulse_Signal_GPIO_Port, RF_Pulse_Signal_Pin ,SOF_HIGH);
}


void RF_Pwm_Conter()
{
	if(m_rf.pluseOn)
	{
		switch (m_rf.pluseLevel)
		{
			case PWM_H1_LEVEL:
				HAL_GPIO_WritePin(RF_Pulse_Signal_GPIO_Port, RF_Pulse_Signal_Pin ,SOF_HIGH);
				if(HAL_GetTick() - m_rf.pluseTimeStamp> (m_rf.pulseDuration/ 2 *TIME_100MS))
				{
					m_rf.pluseTimeStamp = HAL_GetTick();
					if(m_rf.interval==0) m_rf.pluseLevel = PWM_H2_LEVEL;
					else m_rf.pluseLevel = PWM_L1_LEVEL;

				}
			break;

			case PWM_L1_LEVEL:
				HAL_GPIO_WritePin(RF_Pulse_Signal_GPIO_Port, RF_Pulse_Signal_Pin ,SOF_LOW);
				if(HAL_GetTick() - m_rf.pluseTimeStamp> m_rf.interval*TIME_100MS)
				{
					m_rf.pluseTimeStamp = HAL_GetTick();
					m_rf.pluseLevel = PWM_H2_LEVEL;
				}
			break;

			case PWM_H2_LEVEL:
				HAL_GPIO_WritePin(RF_Pulse_Signal_GPIO_Port, RF_Pulse_Signal_Pin ,SOF_HIGH);
				if(HAL_GetTick() - m_rf.pluseTimeStamp> (m_rf.pulseDuration / 2*TIME_100MS))
				{
					m_rf.pluseTimeStamp = HAL_GetTick();
					m_rf.pluseLevel = PWM_L2_LEVEL;
				}
			break;

			case PWM_L2_LEVEL:
				HAL_GPIO_WritePin(RF_Pulse_Signal_GPIO_Port, RF_Pulse_Signal_Pin ,SOF_LOW);
				if(HAL_GetTick() - m_rf.pluseTimeStamp> m_rf.postCooling*TIME_100MS)
				{
					m_rf.pluseLevel = PWM_H1_LEVEL;
					m_rf.expEndFlag = 1;

					m_rf.pluseOn = 0;
				}
			break;
		}
	}
}




void RF_Pwm_Conter_Common(uint8_t pulseNum)
{
	static uint8_t pulseCnt;
	if(m_rf.pluseOn)
	{
		switch (m_rf.pluseLevel)
		{
			case PWM_H_LEVEL:
				HAL_GPIO_WritePin(RF_Pulse_Signal_GPIO_Port, RF_Pulse_Signal_Pin ,SOF_HIGH);
				if(HAL_GetTick() - m_rf.pluseTimeStamp> (m_rf.pulseDuration/pulseNum *TIME_100MS))
				{
					m_rf.pluseTimeStamp = HAL_GetTick();
					pulseCnt++;
					if(pulseCnt == pulseNum)
					{
						m_rf.pluseLevel = PWM_POST_LEVEL;
						pulseCnt = 0;
					}
					else
					{
						m_rf.pluseLevel = PWM_L_LEVEL;
					}

				}
			break;

			case PWM_L_LEVEL:
				if(m_rf.interval != 0)HAL_GPIO_WritePin(RF_Pulse_Signal_GPIO_Port, RF_Pulse_Signal_Pin ,SOF_LOW);
				if(HAL_GetTick() - m_rf.pluseTimeStamp> m_rf.interval*TIME_100MS)
				{
					m_rf.pluseTimeStamp = HAL_GetTick();

					m_rf.pluseLevel = PWM_H_LEVEL;
				}
			break;

			case PWM_POST_LEVEL:
				HAL_GPIO_WritePin(RF_Pulse_Signal_GPIO_Port, RF_Pulse_Signal_Pin ,SOF_LOW);
				if(HAL_GetTick() - m_rf.pluseTimeStamp> m_rf.postCooling*TIME_100MS)
				{
					m_rf.pluseLevel = PWM_H1_LEVEL;
					m_rf.expEndFlag = 1;

					m_rf.pluseOn = 0;
				}
			break;

		}
	}
}



void PulseEnDisCheck_org(uint8_t num)
{
//	if(num>4 || num<2) return;
	int numInit = num;

	for(int i = numInit ;i <=4;i++)
	{
		if(m_rf.pulseEndisBuff[num])
		{
			switch(i)
			{
				case 2:
					m_rf.pluseLevel = PWM_H2_LEVEL;
					printf("<2> \r\n");
					return;
				break;
				case 3:
					m_rf.pluseLevel = PWM_H3_LEVEL;
					printf("<3> \r\n");
					return;
				break;
				case 4:
					m_rf.pluseLevel = PWM_H4_LEVEL;
					printf("<4> \r\n");
					return;
				break;
			}
			break;
		}
	}
	m_rf.pluseLevel = PWM_COOL_LEVEL;
	printf("<FF> \r\n");

}



void PulseEnDisCheck()
{
	uint16_t pulse2Watt = m_rf.pulseBuff[IDX_MAIN_P2_WATT];
	uint16_t pulse3Watt = m_rf.pulseBuff[IDX_MAIN_P3_WATT];
	uint16_t pulse4Watt = m_rf.pulseBuff[IDX_MAIN_P4_WATT];

	if(m_rf.pulseEndisBuff[2] && !m_rf.pulseEndisChkBuff[2] )
	{
		m_rf.pulseEndisChkBuff[2] = 1;
		Tx_RF_Watt_ALL_Module(pulse2Watt, PWM_L1_LEVEL);
		m_rf.pluseLevel = PWM_H2_LEVEL;
	}
	else if(m_rf.pulseEndisBuff[3] && !m_rf.pulseEndisChkBuff[3] )
	{
		m_rf.pulseEndisChkBuff[3] = 1;
		Tx_RF_Watt_ALL_Module(pulse3Watt, PWM_L1_LEVEL);
		m_rf.pluseLevel = PWM_H3_LEVEL;
	}
	else if(m_rf.pulseEndisBuff[4] && !m_rf.pulseEndisChkBuff[4] )
	{
		m_rf.pulseEndisChkBuff[4] = 1;
		Tx_RF_Watt_ALL_Module(pulse4Watt, PWM_L1_LEVEL);
		m_rf.pluseLevel = PWM_H4_LEVEL;
	}
	else
	{
		m_rf.pluseLevel = PWM_COOL_LEVEL;
	}


}


void RF_Pwm_Conter_Individual()
{

	uint32_t pulse1Htime = m_rf.pulseBuff[IDX_MAIN_P1_DURATION_TIME] * TIME_100MS;
	uint32_t pulse1Ltime = m_rf.pulseBuff[IDX_MAIN_P1_INTERVAL_TIME]* TIME_100MS;
	uint32_t pulse2Htime = m_rf.pulseBuff[IDX_MAIN_P2_DURATION_TIME]* TIME_100MS;
	uint32_t pulse2Ltime = m_rf.pulseBuff[IDX_MAIN_P2_INTERVAL_TIME]* TIME_100MS;
	uint32_t pulse3Htime = m_rf.pulseBuff[IDX_MAIN_P3_DURATION_TIME]* TIME_100MS;
	uint32_t pulse3Ltime = m_rf.pulseBuff[IDX_MAIN_P3_INTERVAL_TIME]* TIME_100MS;
	uint32_t pulse4Htime = m_rf.pulseBuff[IDX_MAIN_P4_DURATION_TIME]* TIME_100MS;
	uint32_t pulseCooltime = m_rf.pulseBuff[IDX_MAIN_POSTCO0L_TIME]* TIME_100MS;


	uint16_t pulse2Watt = m_rf.pulseBuff[IDX_MAIN_P2_WATT];
	uint16_t pulse3Watt = m_rf.pulseBuff[IDX_MAIN_P3_WATT];
	uint16_t pulse4Watt = m_rf.pulseBuff[IDX_MAIN_P4_WATT];

	if(pulse1Ltime>109)pulse1Ltime -= 109;
	if(pulse2Ltime>109)pulse2Ltime -= 109;
	if(pulse3Ltime>109)pulse3Ltime -= 109;


	if(m_rf.pluseOn)
	{
		switch (m_rf.pluseLevel)
		{
			case PWM_H1_LEVEL:


				HAL_GPIO_WritePin(RF_Pulse_Signal_GPIO_Port, RF_Pulse_Signal_Pin ,SOF_HIGH);
				if(HAL_GetTick() - m_rf.pluseTimeStamp> pulse1Htime)
				{
					m_rf.pluseTimeStamp = HAL_GetTick();
					m_rf.pluseLevel = PWM_L1_LEVEL;
//					Tx_RF_Watt_ALL_Module(pulse2Watt, PWM_L1_LEVEL);
				}
			break;

			case PWM_L1_LEVEL:
				HAL_GPIO_WritePin(RF_Pulse_Signal_GPIO_Port, RF_Pulse_Signal_Pin ,SOF_LOW);
				if(HAL_GetTick() - m_rf.pluseTimeStamp>pulse1Ltime)
				{
					PulseEnDisCheck();
					m_rf.pluseTimeStamp = HAL_GetTick();

				}
			break;

			case PWM_H2_LEVEL:

				HAL_GPIO_WritePin(RF_Pulse_Signal_GPIO_Port, RF_Pulse_Signal_Pin ,SOF_HIGH);
				if(HAL_GetTick() - m_rf.pluseTimeStamp> pulse2Htime)
				{
//					Tx_RF_Watt_ALL_Module(pulse3Watt, PWM_L2_LEVEL);
					m_rf.pluseTimeStamp = HAL_GetTick();
					m_rf.pluseLevel = PWM_L2_LEVEL;
				}
			break;

			case PWM_L2_LEVEL:
				HAL_GPIO_WritePin(RF_Pulse_Signal_GPIO_Port, RF_Pulse_Signal_Pin ,SOF_LOW);
				if(HAL_GetTick() - m_rf.pluseTimeStamp> pulse2Ltime)
				{
					PulseEnDisCheck();
					m_rf.pluseTimeStamp = HAL_GetTick();
				}
			break;

			case PWM_H3_LEVEL:
				HAL_GPIO_WritePin(RF_Pulse_Signal_GPIO_Port, RF_Pulse_Signal_Pin ,SOF_HIGH);
				if(HAL_GetTick() - m_rf.pluseTimeStamp> pulse3Htime)
				{
					m_rf.pluseTimeStamp = HAL_GetTick();
					m_rf.pluseLevel = PWM_L3_LEVEL;
				}
			break;

			case PWM_L3_LEVEL:
				HAL_GPIO_WritePin(RF_Pulse_Signal_GPIO_Port, RF_Pulse_Signal_Pin ,SOF_LOW);
//				Tx_RF_Watt_ALL_Module(pulse4Watt, PWM_L3_LEVEL);
				if(HAL_GetTick() - m_rf.pluseTimeStamp> pulse3Ltime)
				{
					PulseEnDisCheck();
					m_rf.pluseTimeStamp = HAL_GetTick();
				}
			break;

			case PWM_H4_LEVEL:
				HAL_GPIO_WritePin(RF_Pulse_Signal_GPIO_Port, RF_Pulse_Signal_Pin ,SOF_HIGH);
				if(HAL_GetTick() - m_rf.pluseTimeStamp> pulse4Htime)
				{
					m_rf.pluseTimeStamp = HAL_GetTick();
					m_rf.pluseLevel = PWM_COOL_LEVEL;
				}
			break;

			case PWM_COOL_LEVEL:
				HAL_GPIO_WritePin(RF_Pulse_Signal_GPIO_Port, RF_Pulse_Signal_Pin ,SOF_LOW);
				if(HAL_GetTick() - m_rf.pluseTimeStamp> pulseCooltime)
				{
					m_rf.pluseLevel = PWM_H1_LEVEL;
					m_rf.expEndFlag = 1;
					m_rf.pluseOn = 0;
				}
			break;

		}
	}
}


void RF_Pwm_Conter_Config_org()// systick ~~ it.c interupt 1ms caller
{
#if 0
	RF_Pwm_Conter_Common(m_rf.testPulseOption);
#endif

}
void RF_Pwm_Conter_Config()// main while
{
	RF_Pwm_Conter_Individual();
}


void RF_Eg_Exp_Conter()
{
	if(m_rf.egExpOn)
	{
		if(HAL_GetTick()- m_rf.pluseEgTimeStamp > m_rf.pluseEnginerHigh)
		{
			HAL_GPIO_WritePin(RF_Pulse_Signal_GPIO_Port, RF_Pulse_Signal_Pin ,SOF_LOW);
			m_rf.egExpOn = 0;
			m_rf.expEndFlag = 1;
		}
	}
}


void AutoCal_On(uint8_t startTd, uint8_t endTd)
{
	uint8_t trandu;

//	m_rf.autoCalAddr = startTd - CMD_TRANDU_WATT_BASE;
//	m_rf.autoCalAddrEnd = endTd - CMD_TRANDU_WATT_BASE;
//	m_rf.autoCalFlag = 1;
//	m_rf.autoCalStep = STEP0;
//	memcpy(AutoDaDefulteTable, m_eep.rfWattBuff, sizeof(AutoDaDefulteTable));
//	m_rf.autoCalNowDa = AutoDaDefulteTable[m_rf.autoCalAddr];

//	trandu = (m_rf.autoCalAddr-1)/11;

//	Tx_RF_FRQ_ALL_Module();
//	Tx_RF_Watt_Module(trandu, m_rf.autoCalNowDa);

}
void AutoCal_Off()
{
//	m_rf.autoCalAddr = 0;
//	m_rf.autoCalAddrEnd = 0;
//	m_rf.autoCalFlag = 0;
//	m_rf.autoCalStep = STEP0;
//	Tx_LCD_Msg(CMD_LCD_AUTO_CAL, AUTOCAL_STOP);
}


void LCD_Status_Tret()
{
	if(m_rf.pluseOn) return;
	if(m_rf.treatStatus == STATUS_PRECOOLING)
	{
		if(m_hand1.temprature <70)
		{
			m_rf.readyFlag = READY_ON;

			Tx_RF_FRQ_ALL_Module();
//			Tx_RF_Watt_ALL_Module();
			TX_RF_Max_Ontime_Set();

			Tx_LCD_Msg(CMD_LCD_STATUS, STATUS_TRET);
			m_rf.treatStatus = STATUS_TRET;

			m_rf.preCooltime = 0;
			m_err.preCoolStatus = 1;

#if 0
		HAL_Delay(500);
		testExpFlag =1;
#endif
		}

		if(HAL_GetTick()- m_rf.preCooltime> PRECOOL_TIMEOUT && m_rf.preCooltime)
		{
			m_rf.readyFlag = READY_ON;

			Tx_RF_FRQ_ALL_Module();
//			Tx_RF_Watt_ALL_Module();
			TX_RF_Max_Ontime_Set();

			Tx_LCD_Msg(CMD_LCD_STATUS, STATUS_TRET);
			m_rf.treatStatus = STATUS_TRET;

			m_rf.preCooltime = 0;
			m_err.preCoolStatus = 2;
		}

	}


}

void CARTRIGE_REQ_DATA(uint8_t idx)
{
	switch (idx)
	{
		case CART_IDX_CART_ID:
			Tx_LCD_Msg(CMD_CART_ID, m_eep.catridgeId);
		break;
		case CART_IDX_MANUFAC_YY:
			Tx_LCD_Msg(CMD_MANUFAC_YY, m_eep.manufacYY);
		break;
		case CART_IDX_MANUFAC_MM:
			Tx_LCD_Msg(CMD_MANUFAC_MM, m_eep.manufacMM);
		break;
		case CART_IDX_MANUFAC_DD:
			Tx_LCD_Msg(CMD_MANUFAC_DD, m_eep.manufacDD);
		break;
		case CART_IDX_ISSUED_YY:
			Tx_LCD_Msg(CMD_ISSUED_YY, m_eep.issuedYY);
		break;
		case CART_IDX_ISSUED_MM:
			Tx_LCD_Msg(CMD_ISSUED_MM, m_eep.issuedMM);
		break;
		case CART_IDX_ISSUED_DD:
			Tx_LCD_Msg(CMD_ISSUED_DD, m_eep.issuedDD);
		break;
		case CART_IDX_TRANDU1_FRQ:
			Tx_LCD_Msg(CMD_TRANDU1_FRQ, m_eep.rfFrqBuff[1]);
		break;
		case CART_IDX_TRANDU2_FRQ:
			Tx_LCD_Msg(CMD_TRANDU2_FRQ, m_eep.rfFrqBuff[2]);
		break;
		case CART_IDX_TRANDU3_FRQ:
			Tx_LCD_Msg(CMD_TRANDU3_FRQ, m_eep.rfFrqBuff[3]);
		break;
		case CART_IDX_TRANDU4_FRQ:
			Tx_LCD_Msg(CMD_TRANDU4_FRQ, m_eep.rfFrqBuff[4]);
		break;
		case CART_IDX_TRANDU5_FRQ:
			Tx_LCD_Msg(CMD_TRANDU5_FRQ, m_eep.rfFrqBuff[5]);
		break;
		case CART_IDX_TRANDU6_FRQ:
			Tx_LCD_Msg(CMD_TRANDU6_FRQ, m_eep.rfFrqBuff[6]);
		break;
		case CART_IDX_TRANDU7_FRQ:
			Tx_LCD_Msg(CMD_TRANDU7_FRQ, m_eep.rfFrqBuff[7]);
		break;
		case CART_IDX_REMIND_SHOT:
			Tx_LCD_Msg(CMD_REMIND_SHOT, m_eep.remainingShotNum);
		break;

		case CART_IDX_STATUS:

		break;
		case CART_IDX_RTC:

		break;


	}
}
int compare_32(const void *a, const void *b)    // ¿À¸§Â÷¼ø ºñ±³ ÇÔ¼ö (uint32_t ±âÁØ)
{
    int num1 = *(int *)a;
    int num2 = *(int *)b;

    if (num1 < num2)    // a°¡ bº¸´Ù ÀÛÀ» ¶§´Â
        return -1;      // -1 ¹ÝÈ¯

    if (num1 > num2)    // a°¡ bº¸´Ù Å¬ ¶§´Â
        return 1;       // 1 ¹ÝÈ¯

    return 0;    // a¿Í b°¡ °°À» ¶§´Â 0 ¹ÝÈ¯
}

int qsortBuff[20] = {0,};
void AutoCal_Avg()// ¿À¸§Â÷¼øÀ¸·Î Á¤¸®
{
	int sum =0, avg = 0;
	qsort(qsortBuff, sizeof(qsortBuff) / sizeof(int), sizeof(int), compare_32);// u32
	sum += qsortBuff[1];
	sum += qsortBuff[2];
	sum += qsortBuff[3];

	avg = sum/3;
	printf("avg : %d \r\n",avg);
}


int wattDa = 150;
int trandu = 0;
int wattFrq = 11000;
int wattDly = 250;

void AutoCal_Config_New_Range()
{
	static uint8_t cnt;
	if(m_rf.autoCalFlag==0)return;

	switch (m_rf.autoCalStep)
	{
		case STEP0:
			memset(m_rf.FeedBackWBuff, 0, sizeof(m_rf.FeedBackWBuff));
			m_rf.FeedBackCnt = 0;
			Tx_RF_Watt_Module(trandu, wattDa);
			m_rf.autoCalStep = STEP1;
		break;

		case STEP1:
			m_rf.pluseEnginerHigh = 3000;

			AutoCal_Tx_IP_Msg();//¾ÆÀÌµé 0,2,4,6,8,
			HAL_Delay(500);

			RF_eg_Exp_On();
			HAL_Delay(wattDly);
			AutoCal_Tx_IP_Msg();//¿¢Æ¼ºê 1,3,5,7,9

			HAL_Delay(5000); // ÈÞ½Ä


			m_rf.autoCalStep = STEP2;
		break;

		case STEP2:
			int watt[5] ={0,};
			printf("ACal %d %d -> ",trandu, wattDly);

			qsortBuff[0] = m_rf.FeedBackWBuff[1] +(-1*m_rf.FeedBackWBuff[0]);
			printf("%d ",qsortBuff[0]);

			printf("\r\n");

			m_rf.autoCalStep = STEP0;
#if 11
		cnt++;
		if(cnt>20)
		{
			cnt = 0;
			wattDly += 50;
//			Tx_RF_Watt_Zero_ALL_Module();
//			trandu++;
//			if(trandu>6)
//			{
//				m_rf.autoCalStep = STEP3;
//			}
		}

#endif

		break;


		case STEP3:

		break;

	}

}

void AutoCal_Config_New_Fast()
{
	static uint32_t timeStamp;

	if(m_rf.autoCalFlag==0)return;

	switch (m_rf.autoCalStep)
	{
		case STEP0:
			memset(m_rf.FeedBackWBuff, 0, sizeof(m_rf.FeedBackWBuff));
			m_rf.FeedBackCnt = 0;
			Tx_RF_Watt_Module(trandu, wattDa);
//			AutoCal_Tx_Z_Msg();
//			HAL_Delay(5000);
			m_rf.autoCalStep = STEP1;
		break;

		case STEP1:
			m_rf.pluseEnginerHigh = 3000;

			AutoCal_Tx_IP_Msg();//¾ÆÀÌµé 0,2,4,6,8,
			HAL_Delay(500);

			RF_eg_Exp_On();
			HAL_Delay(2500);

			AutoCal_Tx_IP_Msg();//¿¢Æ¼ºê 1,3,5,7,9
			HAL_Delay(2000); // ÈÞ½Ä


			m_rf.autoCalStep = STEP2;
		break;

		case STEP2:
			int watt[5] ={0,};
			printf("ACal %d %d -> ",trandu, wattDa);

			qsortBuff[0] = m_rf.FeedBackWBuff[1] +(-1*m_rf.FeedBackWBuff[0]);
			printf("%d ",qsortBuff[0]);

			printf("\r\n");

			if(wattDa<150)
			{
				wattDa++;
				m_rf.autoCalStep = STEP0;
			}
			else
			{
				Tx_RF_Watt_Zero_ALL_Module();

				wattDa = 1;
				if(trandu<6)
				{
					trandu++;
					m_rf.autoCalStep = STEP0;
				}
				else
				{
					m_rf.autoCalStep = STEP3;
				}


			}


		break;


		case STEP3:

		break;

	}

}

void AutoCal_Config_New()
{
	static uint32_t timeStamp;

	if(m_rf.autoCalFlag==0)return;

	switch (m_rf.autoCalStep)
	{
		case STEP0:
			memset(m_rf.FeedBackWBuff, 0, sizeof(m_rf.FeedBackWBuff));
			m_rf.FeedBackCnt = 0;
			Tx_RF_Watt_Module(trandu, wattDa);
//			AutoCal_Tx_Z_Msg();
//			HAL_Delay(5000);
			m_rf.autoCalStep = STEP1;
		break;

		case STEP1:
			m_rf.pluseEnginerHigh = 3000;
			for(int i =0 ;i < 5;i++)
			{
				AutoCal_Tx_IP_Msg();//¾ÆÀÌµé 0,2,4,6,8,
				HAL_Delay(500);

				RF_eg_Exp_On();
				HAL_Delay(2500);

				AutoCal_Tx_IP_Msg();//¿¢Æ¼ºê 1,3,5,7,9
				HAL_Delay(2000); // ÈÞ½Ä

			}

			m_rf.autoCalStep = STEP2;
		break;

		case STEP2:
			int watt[5] ={0,};
			printf("ACal %d %d -> ",trandu, wattDa);

			if(m_rf.FeedBackCnt<5)// 10°³Áß¿¡ 5°³ ¹Ì¸¸ÀÏ¶§ Åë½ÅºÒ·®
			{
				m_err.autoCalStatus = 1;
			}
			else
			{
				m_err.autoCalStatus = 0;
			}

			qsortBuff[0] = m_rf.FeedBackWBuff[1] +(-1*m_rf.FeedBackWBuff[0]);
			printf("%d ",qsortBuff[0]);

			qsortBuff[1] = m_rf.FeedBackWBuff[3] +(-1*m_rf.FeedBackWBuff[2]);
			printf("%d ",qsortBuff[1]);

			qsortBuff[2] = m_rf.FeedBackWBuff[5] +(-1*m_rf.FeedBackWBuff[4]);
			printf("%d ",qsortBuff[2]);

			qsortBuff[3] = m_rf.FeedBackWBuff[7] +(-1*m_rf.FeedBackWBuff[6]);
			printf("%d ",qsortBuff[3]);

			qsortBuff[4] = m_rf.FeedBackWBuff[9] +(-1*m_rf.FeedBackWBuff[8]);
			printf("%d ",qsortBuff[4]);

			AutoCal_Avg();


			printf("\r\n");

			if(wattDa<200)
			{
				wattDa++;
				m_rf.autoCalStep = STEP0;
			}
			else
			{
				Tx_RF_Watt_Zero_ALL_Module();

				wattDa = 1;
				if(trandu<5)
				{
					trandu++;
					m_rf.autoCalStep = STEP0;
				}
				else
				{
					m_rf.autoCalStep = STEP3;
				}


			}


		break;


		case STEP3:

		break;

		case STEP4:

		break;
	}

}
void AutoCal_Config_New_frq()
{
	static uint32_t timeStamp;

	if(m_rf.autoCalFlag==0)return;

	switch (m_rf.autoCalStep)
	{
		case STEP0:
			memset(m_rf.FeedBackWBuff, 0, sizeof(m_rf.FeedBackWBuff));
			m_rf.FeedBackCnt = 0;

			Tx_RF_Watt_Module(trandu, 100);
			Tx_RF_FRQ_Module(trandu, wattFrq);

			m_rf.autoCalStep = STEP1;
		break;

		case STEP1:
			m_rf.pluseEnginerHigh = 3000;
			for(int i =0 ;i < 5;i++)
			{
				AutoCal_Tx_IP_Msg();//¾ÆÀÌµé 0,2,4,6,8,
				HAL_Delay(500);

				RF_eg_Exp_On();
				HAL_Delay(2500);

				AutoCal_Tx_IP_Msg();//¿¢Æ¼ºê 1,3,5,7,9
				HAL_Delay(2000); // ÈÞ½Ä

			}

			m_rf.autoCalStep = STEP2;
		break;

		case STEP2:
			int watt;
			printf("ACal %d 100 %d -> ",trandu, wattFrq);

			if(m_rf.FeedBackCnt<5)// 10°³Áß¿¡ 5°³ ¹Ì¸¸ÀÏ¶§ Åë½ÅºÒ·®
			{
				m_err.autoCalStatus = 1;
			}
			else
			{
				m_err.autoCalStatus = 0;
			}

			watt = m_rf.FeedBackWBuff[1] +(-1*m_rf.FeedBackWBuff[0]);
			printf("%d ",watt);

			watt = m_rf.FeedBackWBuff[3] +(-1*m_rf.FeedBackWBuff[2]);
			printf("%d ",watt);

			watt = m_rf.FeedBackWBuff[5] +(-1*m_rf.FeedBackWBuff[4]);
			printf("%d ",watt);

			watt = m_rf.FeedBackWBuff[7] +(-1*m_rf.FeedBackWBuff[6]);
			printf("%d ",watt);

			watt = m_rf.FeedBackWBuff[9] +(-1*m_rf.FeedBackWBuff[8]);
			printf("%d ",watt);

			printf("\r\n");

			if(wattFrq<11500)
			{
				wattFrq += 10;
				m_rf.autoCalStep = STEP0;
			}
			else
			{
				Tx_RF_Watt_Zero_ALL_Module();
				if(trandu<5)
				{
					trandu++;
					m_rf.autoCalStep = STEP0;
				}
				else
				{
					m_rf.autoCalStep = STEP3;
				}
			}

		break;


		case STEP3:

		break;

		case STEP4:

		break;
	}

}

void Debug_Rx_Parssing(uint8_t add, uint32_t data)
{
	if(add==0)return;
	switch (add)
	{

		case CMD_TEST_2_PULSE:
			Tx_LCD_Msg(CMD_TEST_2_PULSE, data);
			m_rf.testPulseOption = data;
		break;

		case CMD_TEST_FORCE_PAGE_CHANGE:
			Tx_LCD_Msg(CMD_TEST_FORCE_PAGE_CHANGE, data);
		break;

		case CMD_CAL_TEST:
			m_rf.readyFlag = READY_ON;
			Tx_RF_FRQ_ALL_Module();
			Tx_RF_Watt_Zero_ALL_Module();
			TX_RF_Max_Ontime_Set();
			m_rf.pluseEnginerHigh = 3000;
			m_rf.EnginerFlag = 1;
		break;

		case CMD_CAL_TEST_ZERO:
			AutoCal_Tx_Z_Msg();
		break;

		case CMD_CAL_TEST_EXP:
			uint8_t tdu = data/1000;
			uint16_t da = data%1000;
			Tx_RF_Watt_Zero_ALL_Module();
			Tx_RF_Watt_Module(tdu, da);
			RF_eg_Exp_On();
			m_rf.pluseEnginerHigh = 3000;
		break;

		case CMD_CAL_TEST_IP:
			AutoCal_Tx_IP_Msg();
		break;

		case CMD_CAL_TEST_AUTOSTART:
			m_rf.autoCalFlag = data;
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


		case CMD_FRQ_CH0:
			m_rf.rfFrqBuff[RF_FRQ_CH0] = data;
			Tx_RF_FRQ_Module(RF_FRQ_CH0, data);
			Tx_LCD_Msg(CMD_FRQ_CH0, data);
		break;

		case CMD_FRQ_CH1:
			m_rf.rfFrqBuff[RF_FRQ_CH1] = data;
			Tx_RF_FRQ_Module(RF_FRQ_CH1, data);
			Tx_LCD_Msg(CMD_FRQ_CH1, data);
		break;

		case CMD_FRQ_CH2:
			m_rf.rfFrqBuff[RF_FRQ_CH2] = data;
			Tx_RF_FRQ_Module(RF_FRQ_CH2, data);
			Tx_LCD_Msg(CMD_FRQ_CH2, data);
		break;

		case CMD_FRQ_CH3:
			m_rf.rfFrqBuff[RF_FRQ_CH3] = data;
			Tx_RF_FRQ_Module(RF_FRQ_CH3, data);
			Tx_LCD_Msg(CMD_FRQ_CH3, data);
		break;

		case CMD_FRQ_CH4:
			m_rf.rfFrqBuff[RF_FRQ_CH4] = data;
			Tx_RF_FRQ_Module(RF_FRQ_CH4, data);
			Tx_LCD_Msg(CMD_FRQ_CH4, data);
		break;

		case CMD_FRQ_CH5:
			m_rf.rfFrqBuff[RF_FRQ_CH5] = data;
			Tx_RF_FRQ_Module(RF_FRQ_CH5, data);
			Tx_LCD_Msg(CMD_FRQ_CH5, data);
		break;

		case CMD_FRQ_CH6:
			m_rf.rfFrqBuff[RF_FRQ_CH6] = data;
			Tx_RF_FRQ_Module(RF_FRQ_CH6, data);
			Tx_LCD_Msg(CMD_FRQ_CH6, data);
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

		case CMD_FRQ_CH0:
			m_rf.rfFrqBuff[RF_FRQ_CH0] = data;
			Tx_RF_FRQ_Module(RF_FRQ_CH0, data);
			Tx_LCD_Msg(CMD_FRQ_CH0, data);
		break;

		case CMD_FRQ_CH1:
			m_rf.rfFrqBuff[RF_FRQ_CH1] = data;
			Tx_RF_FRQ_Module(RF_FRQ_CH1, data);
			Tx_LCD_Msg(CMD_FRQ_CH1, data);
		break;

		case CMD_FRQ_CH2:
			m_rf.rfFrqBuff[RF_FRQ_CH2] = data;
			Tx_RF_FRQ_Module(RF_FRQ_CH2, data);
			Tx_LCD_Msg(CMD_FRQ_CH2, data);
		break;

		case CMD_FRQ_CH3:
			m_rf.rfFrqBuff[RF_FRQ_CH3] = data;
			Tx_RF_FRQ_Module(RF_FRQ_CH3, data);
			Tx_LCD_Msg(CMD_FRQ_CH3, data);
		break;

		case CMD_FRQ_CH4:
			m_rf.rfFrqBuff[RF_FRQ_CH4] = data;
			Tx_RF_FRQ_Module(RF_FRQ_CH4, data);
			Tx_LCD_Msg(CMD_FRQ_CH4, data);
		break;

		case CMD_FRQ_CH5:
			m_rf.rfFrqBuff[RF_FRQ_CH5] = data;
			Tx_RF_FRQ_Module(RF_FRQ_CH5, data);
			Tx_LCD_Msg(CMD_FRQ_CH5, data);
		break;

		case CMD_FRQ_CH6:
			m_rf.rfFrqBuff[RF_FRQ_CH6] = data;
			Tx_RF_FRQ_Module(RF_FRQ_CH6, data);
			Tx_LCD_Msg(CMD_FRQ_CH6, data);
		break;

		case CMD_WATT_CH0:
			m_rf.rfwattBuff[RF_WATT_CH0] = data;
			Tx_RF_Watt_Module(RF_WATT_CH0, data);
			Tx_LCD_Msg(CMD_WATT_CH0, data);
			testExpFlag =1;
		break;

		case CMD_WATT_CH1:
			m_rf.rfwattBuff[RF_WATT_CH1] = data;
			Tx_RF_Watt_Module(RF_WATT_CH1, data);
			Tx_LCD_Msg(CMD_WATT_CH1, data);
			testExpFlag =1;

		break;

		case CMD_WATT_CH2:
			m_rf.rfwattBuff[RF_WATT_CH2] = data;
			Tx_RF_Watt_Module(RF_WATT_CH2, data);
			Tx_LCD_Msg(CMD_WATT_CH2, data);
			testExpFlag =1;
		break;

		case CMD_WATT_CH3:
			m_rf.rfwattBuff[RF_WATT_CH3] = data;
			Tx_RF_Watt_Module(RF_WATT_CH3, data);
			Tx_LCD_Msg(CMD_WATT_CH3, data);
			testExpFlag =1;
		break;

		case CMD_WATT_CH4:
			m_rf.rfwattBuff[RF_WATT_CH4] = data;
			Tx_RF_Watt_Module(RF_WATT_CH4, data);
			Tx_LCD_Msg(CMD_WATT_CH4, data);
			testExpFlag =1;
		break;

		case CMD_WATT_CH5:
			m_rf.rfwattBuff[RF_WATT_CH5] = data;
			Tx_RF_Watt_Module(RF_WATT_CH5, data);
			Tx_LCD_Msg(CMD_WATT_CH5, data);
			testExpFlag =1;
		break;

		case CMD_WATT_CH6:
			m_rf.rfwattBuff[RF_WATT_CH6] = data;
			Tx_RF_Watt_Module(RF_WATT_CH6, data);
			Tx_LCD_Msg(CMD_WATT_CH6, data);
			testExpFlag =1;
		break;

		case CMD_PLUSE_NUM:
			if(data == 0) break;
			m_rf.pulseNum = data;
			Tx_LCD_Msg(CMD_PLUSE_NUM, data);
		break;

		case CMD_PLUSE_EN:
			if(data == 0) break;
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
		break;


		case CMD_PLUSE_BTN_UP_DN:
			uint16_t pulseData = 0;
			if(m_rf.pulseNum == 0) break;
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


		case CMD_CAIV_DURATION:
			if(data==0xff)
			{
				m_rf.EnginerFlag = 0;
			}
			else
			{
				TX_RF_Max_Ontime_Set();
				m_rf.pluseEnginerHigh = data*100;
				m_rf.EnginerFlag = 1;
			}
			Tx_LCD_Msg(CMD_CAIV_DURATION, data);

		break;

		case CMD_OK:
			switch (data)
			{
				case ERR_CHK_MAIN:
					Error_Check_Main();
				break;
				case ERR_CHK_HP:
					Error_Check_HP();
				break;
				case ERR_CHK_RF:
					Error_Check_RF();
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


		case CMD_SYS_CHK:
			Tx_LCD_Msg(CMD_SYS_CHK, data);
			CARTRIGE_REQ_DATA(data);
			m_rf.sysChkFlag = 1;
		break;

		case CMD_LCD_STATUS:
			m_rf.treatStatus = data;
			Tx_LCD_Msg(CMD_LCD_STATUS, data);
			if(data == STATUS_PRECOOLING)
			{
				m_rf.preCooltime = HAL_GetTick();
			}
		break;


		case CMD_TRET_READY_OK:
			if(data == READY_ON)
			{
				m_rf.readyFlag = READY_ON;
				Tx_RF_FRQ_ALL_Module();
				Tx_RF_Watt_ALL_Module_org();
				TX_RF_Max_Ontime_Set();
			}
			else if(data == READY_OFF)
			{
				m_rf.readyFlag = READY_OFF;
			}
			Tx_LCD_Msg(CMD_TRET_READY_OK, data);
		break;

		case CMD_DO_ALL_LIVE:
			CMD_Is_All_Live();
		break;

		case CMD_GET_ALL_CART:
			Tx_LCD_Msg(CMD_GET_ALL_CART, 0);
			Tx_Hand1_Msg(CMD_GET_ALL_CART, 0);
		break;

		case CMD_GET_ALL_CART_END:
			Debug_Printf("lcd all cart Recive",1);
			Tx_Hand1_Msg(CMD_GET_ALL_CART_END, 0);

		break;


		case CMD_LCD_AUTO_CAL:
			switch (data)
			{
				case KEY_AUTO_CAL_1_2:
					AutoCal_On(CMD_TRANDU1_WATT10, CMD_TRANDU2_WATT005);
				break;

				case KEY_AUTO_CAL_3_4_5:
					AutoCal_On(CMD_TRANDU3_WATT10, CMD_TRANDU5_WATT005);
				break;

				case KEY_AUTO_CAL_6_7:
					AutoCal_On(CMD_TRANDU6_WATT10, CMD_TRANDU7_WATT005);
				break;

				case KEY_AUTO_CAL_STOP:
				case KEY_AUTO_CAL_BACK:
					AutoCal_Off();
				break;
			}
		break;

		case CMD_TEST_2_PULSE:
			Tx_LCD_Msg(CMD_TEST_2_PULSE, data);
			m_rf.testPulseOption = data;
		break;


		default:
			uint16_t reqAdd, reqData;
			if(data == REQ_DATA)
			{
				if(CMD_TRANDU1_FRQ <= add && add <= CMD_TRANDU7_FRQ)
				{
					reqAdd = add - CMD_TRANDU_FRQ_BASE;
					reqData = m_eep.rfFrqBuff[reqAdd];
				}
				else if(CMD_TRANDU1_WATT10 <= add && add <=CMD_TRANDU7_WATT005)
				{
					reqAdd = add-CMD_TRANDU_WATT_BASE;
					reqData = m_eep.rfWattBuff[reqAdd];
				}
				Tx_LCD_Msg(add, reqData);

			}
			else
			{
				if(CMD_TRANDU1_FRQ <= add && add <=CMD_TRANDU7_FRQ)
				{
					m_eep.rfFrqBuff[add-CMD_TRANDU_FRQ_BASE] = data;
				}
				else if(CMD_TRANDU1_WATT10 <= add && add <=CMD_TRANDU7_WATT005)
				{
					reqAdd = add-CMD_TRANDU_WATT_BASE;
					m_eep.rfWattBuff[reqAdd] = data;
				}
				Tx_LCD_Msg(add, data);
				Tx_Hand1_Msg(add, data);
			}

		break;



	}
}







void Hand_Rx_Parssing(uint8_t add, uint32_t data, uint32_t data2, uint32_t data3, uint32_t data4 )
{
	uint16_t valueTd, valueWatt;
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
				Tx_LCD_Msg(CMD_CART_ID, data);
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
				Tx_LCD_Msg(CMD_REMIND_SHOT, data);
			break;

			case CMD_CATRIDGE_STATUS:
				m_eep.catridgeStatus = data;
				//³Ö¾î¾ßÇÔ
			break;

			case CMD_CATRIDGE_EVENT:
				m_eep.catridgeDetect = data;
				//³Ö¾î¾ßÇÔ
			break;

			case CMD_DO_ALL_LIVE:
				m_hand1.liveChkCnt++;
				//³Ö¾î¾ßÇÔ
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
				for(int i =1 ;i <= 7;i++)
				{
					if(!m_eep.rfFrqBuff[i])eepErr++;
				}
				for(int i =1 ;i <= 77;i++)
				{
					if(!m_eep.rfWattBuff[i])eepErr++;
				}
				if(eepErr==0)
				{
					LCD_Init();
					Tx_LCD_Msg(CMD_GET_ALL_CART_END, 1);

					m_hand1.cartEndFlag = 1;
				}
				else
				{
					m_eep.catridgeRxErrCnt++;
					if(m_eep.catridgeRxErrCnt<3)
					{
						HAL_Delay(1000);
						Debug_Printf("CartErrReCall",1);
						Tx_Hand1_Msg(CMD_GET_ALL_CART, 0);
						m_hand1.cartEndFlag = 2;
					}
					else
					{
						Debug_Printf("CartAllOk",1);
						m_hand1.cartEndFlag = 3;
						m_err.handComuErr = 1;
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


void RF_Rx_Parssing(uint8_t rxID)
{
	uint32_t timeStamp;



	if(rxID == RF_RX_CALLBACK)
	{
		m_rf.lastTimeStamp = 0;
		timeStamp = HAL_GetTick();
		while (HAL_GetTick() -timeStamp< 100 )
		{
			if(m_rf.lastTimeStamp)
			{
				if(HAL_GetTick() - m_rf.lastTimeStamp>50)break;
			}
		}
	}


	if(m_rf.lastTimeStamp == 0) return;

	if(HAL_GetTick() - m_rf.lastTimeStamp>50)
	{
		m_rf.lastTimeStamp = 0;

		memcpy(m_rf.rxBuffPassing, m_rf.rxBuff, 30);
		memset(m_rf.rxBuff, 0, 30);

		Debug_Rx_RF_Printf(m_rf.rxBuffPassing);

		m_rf.rxCnt = 0;
		m_rf.rxCallBackCmd = m_rf.rxBuffPassing[RF_INDEX_CMD];
		switch (m_rf.rxCallBackCmd)
		{
			case GEN_STATUS_CHECK_R:
				m_err.rfTimeout = 0;
				m_err.rfComuErr = 0;
				m_err.rfStatus= m_rf.rxBuffPassing[RF_INDEX_DATA]<<8 |m_rf.rxBuffPassing[RF_INDEX_DATA+1];// ¾ÆÁ÷ ¾ÈÇÔ
				m_rf.liveChkCnt++;
			break;

			case GEN_GET_VERSION_R:
			break;

			case GEN_FREQ_SET_R:
				Debug_Printf("GEN_FREQ_SET_R",1);
			break;

			case GEN_OUTPUT_SET_R://
				Debug_Printf("GEN_OUTPUT_SET_R",1);
			break;

			case GEN_MAX_ON_TIME_SET_R:
				Debug_Printf("GEN_MAX_ON_TIME_SET_R",1);
			break;

			case GEN_RF_VOLTAGE_REQ_R:
				Debug_Printf("GEN_RF_VOLTAGE_REQ_R",1);
			break;

			case ALL_CH_FREQ_SET_R:
				Debug_Printf("ALL_CH_FREQ_SET_R",1);
			break;

			case ALL_CH_OUTPUT_SET_R:
				Debug_Printf("ALL_CH_OUTPUT_SET_R",1);
			break;
		}

		ddTimeEnd1(); //wndksdebug
	}


}


int testTriger=1;
void Rf_Test()
{

	if(testTriger)
	{
		testTriger = 0;
		AutoCal_On(0,6);
	}
}


void CurrentEnergy_Cal()
{
	float pulse1Htime = (float)m_rf.pulseBuff[IDX_MAIN_P1_DURATION_TIME]/10.0;
	float pulse2Htime = (float)m_rf.pulseBuff[IDX_MAIN_P2_DURATION_TIME]/10.0;
	float pulse3Htime = (float)m_rf.pulseBuff[IDX_MAIN_P3_DURATION_TIME]/10.0;
	float pulse4Htime = (float)m_rf.pulseBuff[IDX_MAIN_P4_DURATION_TIME]/10.0;
	float pulse1Watt  = (float)m_rf.pulseBuff[IDX_MAIN_P1_WATT]/10.0;
	float pulse2Watt  = (float)m_rf.pulseBuff[IDX_MAIN_P2_WATT]/10.0;
	float pulse3Watt  = (float)m_rf.pulseBuff[IDX_MAIN_P3_WATT]/10.0;
	float pulse4Watt  = (float)m_rf.pulseBuff[IDX_MAIN_P4_WATT]/10.0;
	float energy = 0;

	if(m_rf.pulseEndisBuff[1]) energy += (pulse1Htime * pulse1Watt);
	if(m_rf.pulseEndisBuff[2]) energy += (pulse2Htime * pulse2Watt);
	if(m_rf.pulseEndisBuff[3]) energy += (pulse3Htime * pulse3Watt);
	if(m_rf.pulseEndisBuff[4]) energy += (pulse4Htime * pulse4Watt);


	m_rf.currentEnergy = energy*100.0;


	Tx_LCD_Msg(CMD_CURRENT_JOULE, m_rf.currentEnergy);

}


void Exp_Config()
{
	uint16_t totalEenerge;
//	if(m_rf.pluseOn != 0 || m_rf.egExpOn != 0) return;
	if(m_rf.readyFlag != READY_ON) return;


	float pulse1Htime = (float)m_rf.pulseBuff[IDX_MAIN_P1_DURATION_TIME]/10.0;
	float pulse2Htime = (float)m_rf.pulseBuff[IDX_MAIN_P2_DURATION_TIME]/10.0;
	float pulse3Htime = (float)m_rf.pulseBuff[IDX_MAIN_P3_DURATION_TIME]/10.0;
	float pulse4Htime = (float)m_rf.pulseBuff[IDX_MAIN_P4_DURATION_TIME]/10.0;
	float pulse1Watt  = (float)m_rf.pulseBuff[IDX_MAIN_P1_WATT]/10.0;
	float pulse2Watt  = (float)m_rf.pulseBuff[IDX_MAIN_P2_WATT]/10.0;
	float pulse3Watt  = (float)m_rf.pulseBuff[IDX_MAIN_P3_WATT]/10.0;
	float pulse4Watt  = (float)m_rf.pulseBuff[IDX_MAIN_P4_WATT]/10.0;



	static uint8_t step = STEP0;

	switch (step)
	{
		case STEP0:
			if(testExpFlag || IS_HP1_SHOT_PUSH()) // ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Ä¡ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
			{
				HAL_Delay(200);
				testExpFlag = 0;
				Tx_LCD_Msg(CMD_LCD_EXP, LCD_EXP_START);
				HAL_Delay(200);//ï¿½Ì°ï¿½ ï¿½Ö¾ï¿½ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½È®ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
				RF_Pwm_On();
				step = STEP1;
			}
		break;

		case STEP1:
			RF_Pwm_Conter_Individual();
			if(m_rf.expEndFlag) step = STEP2;
		break;

		case STEP2:
			if(m_rf.expEndFlag)
			{
				m_rf.expEndFlag = 0;

				m_rf.totaEnergy = m_rf.totaEnergy + m_rf.currentEnergy;
				totalEenerge = m_rf.totaEnergy/10;
				Tx_LCD_Msg(CMD_TOTAL_JOULE, totalEenerge);

				m_rf.currentShot++;
				Tx_LCD_Msg(CMD_CURRENT_SHOT, m_rf.currentShot);

				m_eep.remainingShotNum--;
				Tx_LCD_Msg(CMD_REMIND_SHOT, m_eep.remainingShotNum);
				Tx_LCD_Msg(CMD_LCD_EXP, LCD_EXP_END);
				Tx_Hand1_Msg(CMD_REMIND_SHOT, m_eep.remainingShotNum);
				step = STEP0;
			}
		break;

	}






}
void Rf_Config()
{

#if 1
	LCD_Status_Tret();
	Exp_Config();

#else
	AutoCal_Config_New_Range();

	Rf_Test();
#endif


}


