/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : freertos.c
 * Description        : Code for freertos applications
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "st7735s.h"
#include "spi.h"
#include "tim.h"
#include "myfft.h"
#include <stdio.h>
#include <math.h>
extern uint8_t FPS;
uint8_t FPS = 0;
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 2048 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
extern uint16_t counter;
uint16_t counter = 0;
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
	/* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
	/* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
	/* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
	/* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
	/* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
	/* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
 * @brief  Function implementing the defaultTask thread.
 * @param  argument: Not used
 * @retval None
 */

/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
	// ST7735S_HandleTypeDef st7735;
	// ST7735S_Init(&st7735, &hspi1, LCD_CD_GPIO_Port, LCD_CD_Pin, LCD_RST_GPIO_Port, LCD_RST_Pin, LCD_BKL_GPIO_Port, LCD_BKL_Pin);
	// ST7735S_LCD_Init(&st7735);
	// /* Infinite loop */

	// HAL_TIM_Base_Start_IT(&htim2);
	// const uint16_t color_map[8] = {
	//     ST7735S_COLOR_BLACK,
	//     ST7735S_COLOR_BLUE,
	//     ST7735S_COLOR_RED,
	//     ST7735S_COLOR_GREEN,
	//     ST7735S_COLOR_CYAN,
	//     ST7735S_COLOR_MAGENTA,
	//     ST7735S_COLOR_YELLOW,
	//     ST7735S_COLOR_WHITE,
	// };
	// int k = 0;
	MYFFT_HandleTypeDef myfft;
	MYFFT_Init(&myfft, 1024);
	for (int i = 0; i < 1024; i++)
	{
		myfft.input_signal[i] = 0.8 * arm_sin_f32(2 * 3.14 * i / 1024) + arm_sin_f32(20 * 3.14 * i / 1024); // 1 Hz æ­£å¼¦æ³?
	}
	MYFFT_GetResult(&myfft);
	// æ‰“å°å¹…å?¼ç»“æž?
	for (int i = 0; i < 1024 / 2; i++)
	{
		printf("Frequency bin %d: Magnitude = %d\r\n", i, (int)(100 * myfft.result[i]));
	}
	printf("input_signal:%p ouput_signal_complex:%p myfft.result:%p\r\n", myfft.input_signal, myfft.ouput_signal_complex, myfft.result);
	while (1)
	{
		// if (k >= 8)
		//     k = 0;
		// ST7735_ShowBlock(&st7735, color_map[k]);
		// k++;
		// FPS++;
		// osDelay(10); // 60 FPS
		osDelay(1000); // 1 FPS
	}

  /* USER CODE END StartDefaultTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

