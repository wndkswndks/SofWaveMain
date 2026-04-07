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

 uint16_t adcQQ,adcQQ2;

 void Battery_Read(void)
{
    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
    uint16_t adc = (uint16_t)HAL_ADC_GetValue(&hadc1);
    HAL_ADC_Stop(&hadc1);
	adcQQ = adc;

	m_io.battery = 3.3* ((float)adc/4095);
}


//==========================================================================================================
//제미나이
// 데이터시트 및 회로 기반 상수 설정
#define R25          10000.0f   // 25도일 때 저항 (10k)
#define B_VALUE      3984.0f    // B25/85 값
#define T25          298.15f    // 25도를 켈빈 온도로 변환 (273.15 + 25)
#define R_PULLUP     24000.0f   // 사용자 지정 풀업 저항 (24k)
#define ADC_MAX      4095.0f    // STM32F103 12비트 ADC 최대값

/**
 * @brief ADC 값을 입력받아 섭씨 온도를 반환하는 함수
 * @param adc_value ADC_IN으로 읽어들인 RAW 값
 * @return float 계산된 섭씨 온도 (°C)
 */
float Get_NTC_Temperature_j(uint32_t adc_value) {
    if (adc_value == 0) return -99.0f; // Open circuit or GND short error 처리

    // 1. ADC 값을 이용하여 현재 NTC 저항값 계산
    // 풀다운 구성: R_ntc = R_pullup * (V_out / (V_cc - V_out))
    // 전압 비례식에 의해 V_cc 생략 가능: R_ntc = R_pullup * (adc / (4095 - adc))
    float r_ntc = R_PULLUP * ((float)adc_value / (ADC_MAX - (float)adc_value));

    // 2. B-parameter 식을 이용한 온도(Kelvin) 계산
    float temperature;
    temperature = r_ntc / R25;              // R/R0
    temperature = log(temperature);         // ln(R/R0)
    temperature /= B_VALUE;                 // 1/B * ln(R/R0)
    temperature += (1.0f / T25);            // + (1/T0)
    temperature = 1.0f / temperature;       // 켈빈 온도 완성

    // 3. 켈빈 온도를 섭씨 온도로 변환
    float temperature_c = temperature - 273.15f;

    return temperature_c;
}

float Get_NTC_Temperature(uint32_t adc_value) {
    if (adc_value == 0) return -99.0f; // 에러 방지

    // 1. 전압 분배 법칙을 이용한 현재 NTC 저항 계산
    // V_out = (adc_value / 4095) * Vcc
    // R_ntc = R_pullup * (V_out / (Vcc - V_out))
    // 이를 간소화하면:
    float r_ntc = R_PULLUP * ((float)adc_value / (ADC_MAX - (float)adc_value));

    // 2. Steinhart-Hart 식 적용
    float temperature_k;
    temperature_k = 1.0f / ((1.0f / T25) + (1.0f / B_VALUE) * log(r_ntc / R25));

    // 3. 섭씨로 변환
    return temperature_k - 273.15f;
}
/* 메인 루프 사용 예시 */
// uint32_t adc_raw = HAL_ADC_GetValue(&hadc1);
// float current_temp = Get_NTC_Temperature(adc_raw);

//==========================================================================================================
//클로드
/** ADC 분해능: 12-bit → 4096 */
#define NTC_ADC_RESOLUTION  4096U

/** 기준 전압 (mV) */
#define NTC_VREF_MV         3300U

/** 풀업 저항 (Ω) */
#define NTC_R_PULLUP        24000.0f

/** NTC 기준 저항 @ 25°C (Ω) */
#define NTC_R25             10000.0f

/** NTC B 상수 (K) ? 데이터시트 B25/85 = 3984 K */
#define NTC_B_CONST         3984.0f

/** 기준 온도 (K) = 25°C */
#define NTC_T25_K           298.15f

/** ADC 평균 샘플 횟수 (노이즈 저감) */
#define NTC_SAMPLE_COUNT    16U

/** 온도 유효 범위 (°C) ? 데이터시트: -55 ~ +125°C */
#define NTC_TEMP_MIN        -55.0f
#define NTC_TEMP_MAX        125.0f

/** 오류 반환값 (측정 실패 or 범위 초과) */
#define NTC_INVALID_TEMP    -999.0f

/* ─── 공개 함수 ───────────────────────────────────────────── */

/**
 * @brief  NTC 드라이버 초기화 (ADC 보정 실행)
 * @note   HAL_ADC 초기화 이후에 호출할 것
 */
void NTC_Init(void);

/**
 * @brief  현재 온도를 섭씨(°C)로 반환
 * @return 온도(°C), 측정 실패 시 NTC_INVALID_TEMP
 */
float NTC_ReadTemperature(void);

/**
 * @brief  ADC 원시값으로부터 NTC 저항값(Ω) 계산
 * @param  adc_raw  12-bit ADC 값 (0~4095)
 * @return NTC 저항값(Ω)
 */
float NTC_CalcResistance(uint16_t adc_raw);

/**
 * @brief  NTC 저항값으로부터 온도(°C) 계산 (B-파라미터 방정식)
 * @param  resistance  NTC 저항값(Ω)
 * @return 온도(°C)
 */
float NTC_CalcTemperature(float resistance);

/**
 * @brief  ADC 멀티 샘플링 평균값 취득
 * @param  count  샘플 횟수
 * @return 평균 ADC 원시값
 */
uint16_t NTC_GetADCAverage(uint32_t count);



/**
 * @file    ntc.c
 * @brief   NTCALUG03A103GC NTC 온도 측정 드라이버 구현
 *
 * 참고 데이터시트: Vishay NTCALUG03A / LUG39A Mini Lug Series
 *   - R25 = 10 kΩ, B25/85 = 3984 K, tolerance ±2%
 *
 * 온도 계산 흐름:
 *   ADC raw → V_ADC → R_NTC → T(K) → T(°C)
 */


/* ─── 내부 함수 선언 ──────────────────────────────────────── */
static uint16_t ADC_ReadOnce(void);

/* ???????????????????????????????????????????????????????????
 * 공개 함수 구현
 * ??????????????????????????????????????????????????????????? */

/**
 * @brief NTC 드라이버 초기화
 *        STM32F103의 ADC는 사용 전 보정(Calibration)을 권장.
 */
void NTC_Init(void)
{
    /* ADC 보정 실행 ? HAL_ADCEx_Calibration_Start()는
     * STM32F1 HAL에서 지원됨 (F4/F7는 다를 수 있음)         */
    if (HAL_ADCEx_Calibration_Start(&hadc2) != HAL_OK)
    {
        /* 보정 실패 시 Error_Handler() 호출 또는 로깅 처리 */
        Error_Handler();
    }
}

/**
 * @brief 온도 측정 메인 함수
 *
 * 내부 동작:
 *   1. NTC_SAMPLE_COUNT 회 ADC 샘플링 후 평균
 *   2. ADC raw → R_NTC 계산
 *   3. R_NTC → °C 변환 (B-파라미터 방정식)
 *   4. 유효 범위 확인 후 반환
 */
float NTC_ReadTemperature(void)
{
    /* 1. 멀티 샘플 평균 ADC 값 취득 */
    uint16_t adc_avg = NTC_GetADCAverage(NTC_SAMPLE_COUNT);

    /* ADC 포화 체크 (단선: 4095, 단락: 0) */
    if (adc_avg == 0 || adc_avg >= (NTC_ADC_RESOLUTION - 1))
    {
        return NTC_INVALID_TEMP;
    }

    /* 2. ADC → NTC 저항 */
    float resistance = NTC_CalcResistance(adc_avg);

    /* 3. 저항 → 온도 */
    float temperature = NTC_CalcTemperature(resistance);

    /* 4. 동작 범위 체크 */
    if (temperature < NTC_TEMP_MIN || temperature > NTC_TEMP_MAX)
    {
        return NTC_INVALID_TEMP;
    }

    return temperature;
}

/**
 * @brief ADC raw → NTC 저항값(Ω) 계산
 *
 * 전압 분배 회로:
 *   V_ADC = Vref × R_NTC / (R_pullup + R_NTC)
 *   → R_NTC = R_pullup × ADC_raw / (ADC_resolution - ADC_raw)
 *
 * @param adc_raw  0~4095 (12-bit ADC)
 * @return         R_NTC (Ω)
 */
float NTC_CalcResistance(uint16_t adc_raw)
{
    /*
     * NTC가 풀다운에 연결되어 있으므로:
     *   V_ADC = 3.3 × R_NTC / (R_pullup + R_NTC)
     *   ADC_raw / ADC_res = R_NTC / (R_pullup + R_NTC)
     *   → R_NTC = R_pullup × ADC_raw / (ADC_res - ADC_raw)
     */
    float adc_f = (float)adc_raw;
    float res_f = (float)NTC_ADC_RESOLUTION;

    return NTC_R_PULLUP * adc_f / (res_f - adc_f);
}

/**
 * @brief NTC 저항값 → 온도(°C) 계산
 *
 * B-파라미터 방정식:
 *   1/T = 1/T25 + (1/B) × ln(R_NTC / R25)
 *   T(°C) = T(K) - 273.15
 *
 * @param resistance  R_NTC (Ω)
 * @return            온도 (°C)
 */
float NTC_CalcTemperature(float resistance)
{
    /*
     * 1/T = 1/T25 + (1/B) * ln(R/R25)
     * T   = 1 / (1/T25 + (1/B) * ln(R/R25))
     */
    float ln_ratio = logf(resistance / NTC_R25);
    float inv_T    = (1.0f / NTC_T25_K) + (1.0f / NTC_B_CONST) * ln_ratio;
    float temp_K   = 1.0f / inv_T;

    return temp_K - 273.15f;
}

/**
 * @brief ADC 멀티 샘플 평균
 *
 * @param count  샘플 횟수 (권장: 16 이상)
 * @return       평균 ADC raw 값
 */
uint16_t NTC_GetADCAverage(uint32_t count)
{
    uint32_t sum = 0;

    for (uint32_t i = 0; i < count; i++)
    {
        sum += ADC_ReadOnce();
    }

    return (uint16_t)(sum / count);
}

/* ???????????????????????????????????????????????????????????
 * 내부 함수 구현
 * ??????????????????????????????????????????????????????????? */

/**
 * @brief ADC 단일 변환 1회 수행 후 결과 반환
 * @return 12-bit ADC raw 값 (오류 시 0)
 */
static uint16_t ADC_ReadOnce(void)
{
    if (HAL_ADC_Start(&hadc2) != HAL_OK)
    {
        return 0;
    }

    if (HAL_ADC_PollForConversion(&hadc2, 10U) != HAL_OK)
    {
        HAL_ADC_Stop(&hadc2);
        return 0;
    }

    uint16_t value = (uint16_t)HAL_ADC_GetValue(&hadc2);
    HAL_ADC_Stop(&hadc2);
	adcQQ2 = value;

    return value;
}




//==========================================================================================================

float chillerTemp;
 uint8_t cntLow, cntHigh;
 uint8_t flagLow = 1, flagHigh;
uint8_t chilFlag = 0;
uint32_t chilTerm = 0;

void Chiller_Temperature_Read()
{
	static uint32_t timeStamp, timeStamp2;
	HAL_ADC_Start(&hadc2);
    HAL_ADC_PollForConversion(&hadc2, HAL_MAX_DELAY);
    uint32_t adc = (uint16_t)HAL_ADC_GetValue(&hadc2);
    HAL_ADC_Stop(&hadc2);
	adcQQ2 = adc;
	chillerTemp = Get_NTC_Temperature_j(adc);


if(HAL_GetTick()-timeStamp >= 1000)
{
	timeStamp = HAL_GetTick();
	int Data = chillerTemp*10.0;
	printf("[244,%d]\r\n",Data);
}
static uint8_t once = 1;

if(once)
{
	if(chillerTemp > 14) return;
	else once = 0;
}

if(HAL_GetTick()>120000)
{
	if(HAL_GetTick()-timeStamp2 >= chilTerm)
	{
		timeStamp2 = HAL_GetTick();
		if (chilFlag)
		{
			chilFlag = 0;
			AC_RLY_H();
			printf("[233,%d]\r\n",200);
			chilTerm =170000;
		}
		else
		{
			chilFlag = 1;
			AC_RLY_L();
			printf("[233,%d]\r\n",20);
			chilTerm =70000;
		}
	}

}

//	if(HAL_GetTick()-timeStamp >= 200)
//	{
//		timeStamp = HAL_GetTick();
//		if (chillerTemp <= 14)
//		{
//			cntLow++;
//			if(cntLow>=10 && flagHigh)
//			{

//				cntLow = 0;
//				flagLow = 1;
//				flagHigh = 0;
//				AC_RLY_L();
//				HAL_Delay(1000);
//				AC_RLY_H();
//			}
//			cntHigh = 0;
//		}
//		else if (chillerTemp >= 17)
//		{
//			cntHigh++;
//			if(cntHigh >= 10 && flagLow)
//			{
//				cntHigh = 0;
//				flagHigh = 1;
//				flagLow = 0;
//			}
//			cntLow = 0;
//		}


//	}
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
	AC_RLY_H();



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

float temperatureQQ;

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
	Chiller_Temperature_Read();
//	temperatureQQ = NTC_ReadTemperature();

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


