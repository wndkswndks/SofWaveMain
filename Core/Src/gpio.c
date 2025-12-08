/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, BUZZER_Pin|BAT_CHG_ON_Pin|HP1_PWR_EN_Pin|HP2_Boot_CONTROL_Pin
                          |HP2_RST_CONTROL_Pin|HP2_PWR_EN_Pin|LED_DR2_Pin|LED_DR1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, SPI1_NSS_Pin|CON_SOL2_ON_Pin|CON_SOL1_ON_Pin|COOLING_LV5_Pin
                          |COOLING_LV4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, HP1_RST_CONTROL_Pin|HP1_Boot_CONTROL_Pin|MP3_PREVIOUS_VOLMI_Pin|MP3_NEXT_VOLUP_Pin
                          |MP3_PLAY_PAUSE_Pin|MP3_WORK_MODE_Pin|COOLING_LV2_Pin|COOLING_LV1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, MP3_DEVICE_SWITCH_Pin|MP3_PLAY_MODE_Pin|MP3_Segment1_Pin|MP3_Segment2_Pin
                          |MP3_Segment3_Pin|MP3_Segment4_Pin|CILLER_PWR_ON_Pin|WATER_PUMP_PWR_EN_Pin
                          |RF_PWR_EN_Pin|AC_RLY_ON_Pin|BUFFER_ON_Pin|HANDLE_LED_BLUE_Pin
                          |HANDLE_LED_GREED_Pin|HANDLE_LED_RED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, COOLING_LV3_Pin|RF_Pulse_Signal_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : BUZZER_Pin BAT_CHG_ON_Pin HP1_PWR_EN_Pin HP2_Boot_CONTROL_Pin
                           HP2_RST_CONTROL_Pin HP2_PWR_EN_Pin LED_DR2_Pin LED_DR1_Pin */
  GPIO_InitStruct.Pin = BUZZER_Pin|BAT_CHG_ON_Pin|HP1_PWR_EN_Pin|HP2_Boot_CONTROL_Pin
                          |HP2_RST_CONTROL_Pin|HP2_PWR_EN_Pin|LED_DR2_Pin|LED_DR1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : STATE_B_Pin STATE_A_Pin SD__INSERT_SIGNAL2_Pin HP1_INSERT_Pin
                           HP1_SHOT_PUSH_Pin HP2_SHOT_PUSH_Pin HP2_INSERT_Pin */
  GPIO_InitStruct.Pin = STATE_B_Pin|STATE_A_Pin|SD__INSERT_SIGNAL2_Pin|HP1_INSERT_Pin
                          |HP1_SHOT_PUSH_Pin|HP2_SHOT_PUSH_Pin|HP2_INSERT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : LEVEL_SENSOR1_Pin LEVEL_SENSOR2_Pin SD_INSERT_SIGNAL_Pin */
  GPIO_InitStruct.Pin = LEVEL_SENSOR1_Pin|LEVEL_SENSOR2_Pin|SD_INSERT_SIGNAL_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : FLOWSENSOR_OUT_Pin */
  GPIO_InitStruct.Pin = FLOWSENSOR_OUT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(FLOWSENSOR_OUT_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : SPI1_NSS_Pin CON_SOL2_ON_Pin CON_SOL1_ON_Pin COOLING_LV5_Pin
                           COOLING_LV4_Pin */
  GPIO_InitStruct.Pin = SPI1_NSS_Pin|CON_SOL2_ON_Pin|CON_SOL1_ON_Pin|COOLING_LV5_Pin
                          |COOLING_LV4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : HP1_RST_CONTROL_Pin HP1_Boot_CONTROL_Pin MP3_PREVIOUS_VOLMI_Pin MP3_NEXT_VOLUP_Pin
                           MP3_PLAY_PAUSE_Pin MP3_WORK_MODE_Pin COOLING_LV2_Pin COOLING_LV1_Pin */
  GPIO_InitStruct.Pin = HP1_RST_CONTROL_Pin|HP1_Boot_CONTROL_Pin|MP3_PREVIOUS_VOLMI_Pin|MP3_NEXT_VOLUP_Pin
                          |MP3_PLAY_PAUSE_Pin|MP3_WORK_MODE_Pin|COOLING_LV2_Pin|COOLING_LV1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : MP3_DEVICE_SWITCH_Pin MP3_PLAY_MODE_Pin MP3_Segment1_Pin MP3_Segment2_Pin
                           MP3_Segment3_Pin MP3_Segment4_Pin CILLER_PWR_ON_Pin WATER_PUMP_PWR_EN_Pin
                           RF_PWR_EN_Pin AC_RLY_ON_Pin BUFFER_ON_Pin HANDLE_LED_BLUE_Pin
                           HANDLE_LED_GREED_Pin HANDLE_LED_RED_Pin */
  GPIO_InitStruct.Pin = MP3_DEVICE_SWITCH_Pin|MP3_PLAY_MODE_Pin|MP3_Segment1_Pin|MP3_Segment2_Pin
                          |MP3_Segment3_Pin|MP3_Segment4_Pin|CILLER_PWR_ON_Pin|WATER_PUMP_PWR_EN_Pin
                          |RF_PWR_EN_Pin|AC_RLY_ON_Pin|BUFFER_ON_Pin|HANDLE_LED_BLUE_Pin
                          |HANDLE_LED_GREED_Pin|HANDLE_LED_RED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : COOLING_LV3_Pin RF_Pulse_Signal_Pin */
  GPIO_InitStruct.Pin = COOLING_LV3_Pin|RF_Pulse_Signal_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : RF_GPIO_IN_Pin */
  GPIO_InitStruct.Pin = RF_GPIO_IN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(RF_GPIO_IN_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : AC_INPUT_STATE_Pin */
  GPIO_InitStruct.Pin = AC_INPUT_STATE_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(AC_INPUT_STATE_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */
