/*
 * eeprom.c
 *
 *  Created on: Sep 11, 2025
 *      Author: Cellah_SW
 */
#include "eeprom.h"

static inline uint8_t CAT24C16_MemAddr8(uint16_t abs_addr)
{
    return (uint8_t)(abs_addr & 0xFF);          // ���?�� 8��Ʈ �ּ�
}

static HAL_StatusTypeDef CAT24C16_WaitReady(I2C_HandleTypeDef *hi2c, uint16_t abs_addr, uint32_t timeout_ms)
{
    uint32_t tick_start = HAL_GetTick();
    uint16_t dev =CAT24C16_ADDRESS_ID;
    while ((HAL_GetTick() - tick_start) < timeout_ms)
    {
        if (HAL_I2C_IsDeviceReady(hi2c, dev, 1, 5) == HAL_OK)
            return HAL_OK;
    }
    return HAL_TIMEOUT;
}

HAL_StatusTypeDef CAT24C16_WriteByte(I2C_HandleTypeDef *hi2c, uint16_t abs_addr, uint8_t data)
{
    if (abs_addr >= CAT24C16_TOTAL_BYTES) return HAL_ERROR;

    uint16_t dev  = CAT24C16_ADDRESS_ID;
    uint8_t  maddr= CAT24C16_MemAddr8(abs_addr);

    HAL_StatusTypeDef st = HAL_I2C_Mem_Write(hi2c, dev, maddr, I2C_MEMADD_SIZE_8BIT, &data, 1, 100);
    if (st != HAL_OK) return st;

    // ���� ���� �Ϸ� ���?ACK ����)
    return CAT24C16_WaitReady(hi2c, abs_addr, 10 /*ms*/);
}

HAL_StatusTypeDef CAT24C16_ReadByte(I2C_HandleTypeDef *hi2c, uint16_t abs_addr, uint8_t *p_data)
{
    if (abs_addr >= CAT24C16_TOTAL_BYTES || p_data == NULL) return HAL_ERROR;

    uint16_t dev  = CAT24C16_ADDRESS_ID;
    uint8_t  maddr= CAT24C16_MemAddr8(abs_addr);

    return HAL_I2C_Mem_Read(hi2c, dev, maddr, I2C_MEMADD_SIZE_8BIT, p_data, 1, 100);
}



uint8_t bufQQ[255] = {0};
void eeprom_test(void)
{
//    // 1) 0x000 ~ 0x00A�� ���� ���?
//    for (uint16_t i = 0; i <= 250; ++i)
//    {
//        uint8_t w = i;  // ���� ����
//        if (CAT24C16_WriteByte(&hi2c1, i, w) != HAL_OK)
//        {
//            // ���� ó��
//            return;
//        }
//    }

    // 2) ���� ���� �б�
    for (uint16_t i = 0; i <= 250; ++i)
    {
        if (CAT24C16_ReadByte(&hi2c1, i, &bufQQ[i]) != HAL_OK)
        {
            // ���� ó��
            return;
        }
    }


}

#define DS1308_ADDR    (0x68 << 1)

extern I2C_HandleTypeDef hi2c1;  // I2C1 ���?����

uint8_t DS1308_Read(uint8_t reg) {
    uint8_t data;
    HAL_I2C_Mem_Read(&hi2c1, DS1308_ADDR, reg, I2C_MEMADD_SIZE_8BIT, &data, 1, 100);
    return data;
}

void DS1308_Write(uint8_t reg, uint8_t data) {
    HAL_I2C_Mem_Write(&hi2c1, DS1308_ADDR, reg, I2C_MEMADD_SIZE_8BIT, &data, 1, 100);
}

// BCD <-> DEC ��ȯ �Լ� (DS1308�� BCD ����)
uint8_t BCD2DEC(uint8_t bcd) {
    return ((bcd >> 4) * 10) + (bcd & 0x0F);
}

uint8_t DEC2BCD(uint8_t dec) {
    return ((dec / 10) << 4) | (dec % 10);
}

// �ð� �б� ���� (0x00: ��, 0x01: ��, 0x02: ��)
void DS1308_GetTime(uint8_t *hour, uint8_t *min, uint8_t *sec)
{
    *sec = BCD2DEC(DS1308_Read(0x00));
    *min = BCD2DEC(DS1308_Read(0x01));
    *hour = BCD2DEC(DS1308_Read(0x02));
}


void DS1308_GetDay(uint8_t *dayOfWeek, uint8_t *DD, uint8_t *MM,  uint8_t *YY)
{
    *dayOfWeek = BCD2DEC(DS1308_Read(0x03));
    *DD = BCD2DEC(DS1308_Read(0x04));
    *MM = BCD2DEC(DS1308_Read(0x05));
    *YY = BCD2DEC(DS1308_Read(0x06));
}

// �ð� ���� ����
void DS1308_SetParts(uint8_t add, uint8_t data)
{
    DS1308_Write(add, DEC2BCD(data));
}


void DS1308_SetTime(uint8_t hour, uint8_t min, uint8_t sec) {
    DS1308_Write(0x00, DEC2BCD(sec));
    DS1308_Write(0x01, DEC2BCD(min));
    DS1308_Write(0x02, DEC2BCD(hour));
}
void DS1308_SetDay(uint8_t dayOfWeek, uint8_t DD, uint8_t MM , uint8_t YY)
{
    DS1308_Write(0x03, DEC2BCD(dayOfWeek));
    DS1308_Write(0x04, DEC2BCD(DD));
    DS1308_Write(0x05, DEC2BCD(MM));
    DS1308_Write(0x06, DEC2BCD(YY));
}

void RTC_Init(void)
{
	// �׽�Ʈ: 12�� 12�� 12�ʷ� �ð� ����
	DS1308_SetTime(23, 59, 40);
	DS1308_SetDay(1,28,9,90);
	HAL_Delay(500); // ���� �� �ణ�� ���?
//	BAT_CHG_ON_H();
}

uint8_t hour, min, sec;
void RTC_Test(void)///
{
	static uint32_t timeStamp;

	if(HAL_GetTick()-timeStamp >= 500)
	{

		timeStamp = HAL_GetTick();
		// RTC�κ��� �ð� �б�
		DS1308_GetTime(&hour, &min, &sec);

		// ���� �� Ȯ�ο� (��: UART ���?- ���� ȯ�濡 �°� ��ü)
//		printf("RTC Time: %02d:%02d:%02d\r\n", hour, min, sec);
	}
}

