/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : app_freertos.c
 * Description        : FreeRTOS applicative file
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
#include "app_freertos.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "../User_App/InputHandler/InputHandler.h"
#include "../User_App/OutputHandler/OutputHandler.h"

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
    .priority = (osPriority_t)osPriorityNormal,
    .stack_size = 128 * 4};
/* Definitions for InputHandlerTask */
osThreadId_t InputHandlerTaskHandle;
const osThreadAttr_t InputHandlerTask_attributes = {
    .name = "InputHandlerTask",
    .priority = (osPriority_t)osPriorityNormal,
    .stack_size = 128 * 4};
/* Definitions for OutputHandlerTask */
osThreadId_t OutputHandlerTaskHandle;
const osThreadAttr_t OutputHandlerTask_attributes = {
    .name = "OutputHandlerTask",
    .priority = (osPriority_t)osPriorityNormal,
    .stack_size = 128 * 4};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

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
  /* creation of defaultTask */
  defaultTaskHandle =
      osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of InputHandlerTask */
  InputHandlerTaskHandle =
      osThreadNew(InputHandler, NULL, &InputHandlerTask_attributes);

  /* creation of OutputHandlerTask */
  OutputHandlerTaskHandle =
      osThreadNew(OutputHandler, NULL, &OutputHandlerTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */
}
/* USER CODE BEGIN Header_StartDefaultTask */
/**
 * @brief Function implementing the defaultTask thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument) {
  /* USER CODE BEGIN defaultTask */
  UNUSED(argument);
  /* Infinite loop */
  for (;;) {
    osDelay(1);
  }
  /* USER CODE END defaultTask */
}

/* USER CODE BEGIN Header_InputHandler */
/**
 * @brief Function implementing the InputHandlerTask thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_InputHandler */
void InputHandler(void *argument) {
  /* USER CODE BEGIN InputHandlerTask */
  UNUSED(argument);

  InputHandler_Init();
  /* Infinite loop */
  for (;;) {
    InputHandler_Loop();
  }
  /* USER CODE END InputHandlerTask */
}

/* USER CODE BEGIN Header_OutputHandler */
/**
 * @brief Function implementing the OutputHandlerTask thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_OutputHandler */
void OutputHandler(void *argument) {
  /* USER CODE BEGIN OutputHandlerTask */
  UNUSED(argument);
  OutputHandler_Init();
  /* Infinite loop */
  for (;;) {
    OutputHandler_Loop();
  }
  /* USER CODE END OutputHandlerTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
