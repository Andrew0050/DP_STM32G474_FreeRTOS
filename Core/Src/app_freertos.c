/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : app_freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
//#include "hrtim.h"
//#include "sys_config.h"
//#include "i2c.h"
#include "usart.h"
#include "stdio.h"
#include "string.h"

//extern USART_HandleTypeDef husart1;
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
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 4
};
/* Definitions for LED */
osThreadId_t LEDHandle;
const osThreadAttr_t LED_attributes = {
  .name = "LED",
  .priority = (osPriority_t) osPriorityLow,
  .stack_size = 64 * 4
};
/* Definitions for UART */
osThreadId_t UARTHandle;
const osThreadAttr_t UART_attributes = {
  .name = "UART",
  .priority = (osPriority_t) osPriorityLow,
  .stack_size = 64 * 4
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void LED_Task(void *argument);
void UART_Task(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* Hook prototypes */
void vApplicationStackOverflowHook(xTaskHandle xTask, signed char *pcTaskName);

/* USER CODE BEGIN 4 */
void vApplicationStackOverflowHook(xTaskHandle xTask, signed char *pcTaskName)
{
   /* Run time stack overflow checking is performed if
   configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2. This hook function is
   called if a stack overflow is detected. */
}
/* USER CODE END 4 */

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

  /* creation of LED */
  LEDHandle = osThreadNew(LED_Task, NULL, &LED_attributes);

  /* creation of UART */
  UARTHandle = osThreadNew(UART_Task, NULL, &UART_attributes);

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
	//uint8_t str_buf[64];
	//uint8_t t = 1;
	//uint8_t taskCount;
	//size_t freeHeapSize = xPortGetFreeHeapSize();

  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_LED_Task */
/**
* @brief Function implementing the LED thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_LED_Task */
void LED_Task(void *argument)
{
  /* USER CODE BEGIN LED_Task */
  /* Infinite loop */
  for(;;)
  {
		HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
    osDelay(1000);
  }
  /* USER CODE END LED_Task */
}

/* USER CODE BEGIN Header_UART_Task */
/**
* @brief Function implementing the UART thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_UART_Task */
void UART_Task(void *argument)
{
  /* USER CODE BEGIN UART_Task */
  (void ) argument;
	char tx[] = "FreeRTOS usart_thread test...\r\n";
  /* Infinite loop */
  for(;;)
  {
		HAL_UART_Transmit(&huart1, (uint8_t *)tx, sizeof(tx), 0xffff);
    osDelay(1000);
  }
  /* USER CODE END UART_Task */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
