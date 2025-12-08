/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BUZZER_Pin GPIO_PIN_2
#define BUZZER_GPIO_Port GPIOE
#define STATE_B_Pin GPIO_PIN_3
#define STATE_B_GPIO_Port GPIOE
#define STATE_A_Pin GPIO_PIN_4
#define STATE_A_GPIO_Port GPIOE
#define SD__INSERT_SIGNAL2_Pin GPIO_PIN_5
#define SD__INSERT_SIGNAL2_GPIO_Port GPIOE
#define BAT_CHG_ON_Pin GPIO_PIN_6
#define BAT_CHG_ON_GPIO_Port GPIOE
#define LEVEL_SENSOR1_Pin GPIO_PIN_1
#define LEVEL_SENSOR1_GPIO_Port GPIOC
#define LEVEL_SENSOR2_Pin GPIO_PIN_2
#define LEVEL_SENSOR2_GPIO_Port GPIOC
#define FLOWSENSOR_OUT_Pin GPIO_PIN_0
#define FLOWSENSOR_OUT_GPIO_Port GPIOA
#define FLOWSENSOR_OUT_EXTI_IRQn EXTI0_IRQn
#define SPI1_NSS_Pin GPIO_PIN_4
#define SPI1_NSS_GPIO_Port GPIOC
#define SD_INSERT_SIGNAL_Pin GPIO_PIN_5
#define SD_INSERT_SIGNAL_GPIO_Port GPIOC
#define HP1_RST_CONTROL_Pin GPIO_PIN_0
#define HP1_RST_CONTROL_GPIO_Port GPIOB
#define HP1_Boot_CONTROL_Pin GPIO_PIN_1
#define HP1_Boot_CONTROL_GPIO_Port GPIOB
#define HP1_INSERT_Pin GPIO_PIN_7
#define HP1_INSERT_GPIO_Port GPIOE
#define HP1_SHOT_PUSH_Pin GPIO_PIN_8
#define HP1_SHOT_PUSH_GPIO_Port GPIOE
#define HP1_PWR_EN_Pin GPIO_PIN_9
#define HP1_PWR_EN_GPIO_Port GPIOE
#define HP2_Boot_CONTROL_Pin GPIO_PIN_10
#define HP2_Boot_CONTROL_GPIO_Port GPIOE
#define HP2_RST_CONTROL_Pin GPIO_PIN_11
#define HP2_RST_CONTROL_GPIO_Port GPIOE
#define HP2_PWR_EN_Pin GPIO_PIN_12
#define HP2_PWR_EN_GPIO_Port GPIOE
#define HP2_SHOT_PUSH_Pin GPIO_PIN_13
#define HP2_SHOT_PUSH_GPIO_Port GPIOE
#define HP2_INSERT_Pin GPIO_PIN_14
#define HP2_INSERT_GPIO_Port GPIOE
#define MP3_PREVIOUS_VOLMI_Pin GPIO_PIN_12
#define MP3_PREVIOUS_VOLMI_GPIO_Port GPIOB
#define MP3_NEXT_VOLUP_Pin GPIO_PIN_13
#define MP3_NEXT_VOLUP_GPIO_Port GPIOB
#define MP3_PLAY_PAUSE_Pin GPIO_PIN_14
#define MP3_PLAY_PAUSE_GPIO_Port GPIOB
#define MP3_WORK_MODE_Pin GPIO_PIN_15
#define MP3_WORK_MODE_GPIO_Port GPIOB
#define MP3_DEVICE_SWITCH_Pin GPIO_PIN_8
#define MP3_DEVICE_SWITCH_GPIO_Port GPIOD
#define MP3_PLAY_MODE_Pin GPIO_PIN_9
#define MP3_PLAY_MODE_GPIO_Port GPIOD
#define MP3_Segment1_Pin GPIO_PIN_10
#define MP3_Segment1_GPIO_Port GPIOD
#define MP3_Segment2_Pin GPIO_PIN_11
#define MP3_Segment2_GPIO_Port GPIOD
#define MP3_Segment3_Pin GPIO_PIN_12
#define MP3_Segment3_GPIO_Port GPIOD
#define MP3_Segment4_Pin GPIO_PIN_13
#define MP3_Segment4_GPIO_Port GPIOD
#define CILLER_PWR_ON_Pin GPIO_PIN_14
#define CILLER_PWR_ON_GPIO_Port GPIOD
#define WATER_PUMP_PWR_EN_Pin GPIO_PIN_15
#define WATER_PUMP_PWR_EN_GPIO_Port GPIOD
#define CON_SOL2_ON_Pin GPIO_PIN_6
#define CON_SOL2_ON_GPIO_Port GPIOC
#define CON_SOL1_ON_Pin GPIO_PIN_7
#define CON_SOL1_ON_GPIO_Port GPIOC
#define COOLING_LV5_Pin GPIO_PIN_8
#define COOLING_LV5_GPIO_Port GPIOC
#define COOLING_LV4_Pin GPIO_PIN_9
#define COOLING_LV4_GPIO_Port GPIOC
#define COOLING_LV3_Pin GPIO_PIN_8
#define COOLING_LV3_GPIO_Port GPIOA
#define RF_GPIO_IN_Pin GPIO_PIN_11
#define RF_GPIO_IN_GPIO_Port GPIOA
#define RF_Pulse_Signal_Pin GPIO_PIN_12
#define RF_Pulse_Signal_GPIO_Port GPIOA
#define RF_PWR_EN_Pin GPIO_PIN_0
#define RF_PWR_EN_GPIO_Port GPIOD
#define AC_RLY_ON_Pin GPIO_PIN_3
#define AC_RLY_ON_GPIO_Port GPIOD
#define BUFFER_ON_Pin GPIO_PIN_4
#define BUFFER_ON_GPIO_Port GPIOD
#define HANDLE_LED_BLUE_Pin GPIO_PIN_5
#define HANDLE_LED_BLUE_GPIO_Port GPIOD
#define HANDLE_LED_GREED_Pin GPIO_PIN_6
#define HANDLE_LED_GREED_GPIO_Port GPIOD
#define HANDLE_LED_RED_Pin GPIO_PIN_7
#define HANDLE_LED_RED_GPIO_Port GPIOD
#define COOLING_LV2_Pin GPIO_PIN_5
#define COOLING_LV2_GPIO_Port GPIOB
#define COOLING_LV1_Pin GPIO_PIN_6
#define COOLING_LV1_GPIO_Port GPIOB
#define AC_INPUT_STATE_Pin GPIO_PIN_7
#define AC_INPUT_STATE_GPIO_Port GPIOB
#define LED_DR2_Pin GPIO_PIN_0
#define LED_DR2_GPIO_Port GPIOE
#define LED_DR1_Pin GPIO_PIN_1
#define LED_DR1_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
