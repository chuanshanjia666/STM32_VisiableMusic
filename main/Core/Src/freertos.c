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
#include <stdio.h>
#include "arm_math.h"
#define FFT_SIZE 1024
float32_t input[FFT_SIZE];  // 输入数据（实数）
float32_t output[FFT_SIZE]; // 输出幅�??
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
  .stack_size = 128 * 4,
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
    ST7735S_HandleTypeDef st7735;
    ST7735S_Init(&st7735, &hspi1, LCD_CD_GPIO_Port, LCD_CD_Pin, LCD_RST_GPIO_Port, LCD_RST_Pin, LCD_BKL_GPIO_Port, LCD_BKL_Pin);
    ST7735S_LCD_Init(&st7735);
    /* Infinite loop */

    HAL_TIM_Base_Start_IT(&htim2);
    const uint16_t color_map[8] = {
        ST7735S_COLOR_BLACK,
        ST7735S_COLOR_BLUE,
        ST7735S_COLOR_RED,
        ST7735S_COLOR_GREEN,
        ST7735S_COLOR_CYAN,
        ST7735S_COLOR_MAGENTA,
        ST7735S_COLOR_YELLOW,
        ST7735S_COLOR_WHITE,
    };
    int k = 0;
    // 初始化FFT实例
    arm_rfft_fast_instance_f32 fft_inst;
    arm_rfft_fast_init_f32(&fft_inst, FFT_SIZE);

    // 填充输入数据（例如从ADC读取�?
    for (int i = 0; i < FFT_SIZE; i++)
    {
      input[i] =0; // 填充实际数据
    }

    // 执行FFT（输入和输出缓冲区可以是同一个）
    arm_rfft_fast_f32(&fft_inst, input, output, 0);

    // 计算幅�?�（输出为复数，格式为[real0, imag0, real1, imag1, ...]�?
    for (int i = 0; i < FFT_SIZE / 2; i++)
    {
      output[i] = sqrtf(output[2 * i] * output[2 * i] + output[2 * i + 1] * output[2 * i + 1]);
    }
    while (1)
    {
        // if(k>=8)
        //     k = 0;
        // for (uint8_t line = 0; line < 160; line++)
        // {
        //     for (uint8_t row = 0; row < 128; row++)
        //     {
        //         ST7735_ShowPoint(&st7735, row, line, color_map[k]);
        //         // osDelay(100);
        //     }
        // }
        // k++;
        ST7735_ShowBlock(&st7735, 0, 0, 127, 159, color_map[k]);
    }
    


  /* USER CODE END StartDefaultTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

