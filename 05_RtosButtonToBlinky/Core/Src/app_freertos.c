/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : app_freertos.c
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
#include "../../User_App/InputHandler/InputHandler.h"
#include "../../User_App/OutputHandler/OutputHandler.h"
#include "../../User_App/DataModel/DataModel.h"

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

static DataModel_t g_tButtonEvent = {0};

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
    .name = "defaultTask",
    .priority = (osPriority_t)osPriorityNormal,
    .stack_size = 128 * 4};
/* Definitions for Input_Handler */
osThreadId_t Input_HandlerHandle;
const osThreadAttr_t Input_Handler_attributes = {
    .name = "Input_Handler",
    .priority = (osPriority_t)osPriorityNormal,
    .stack_size = 128 * 4};
/* Definitions for Output_Handler */
osThreadId_t Output_HandlerHandle;
const osThreadAttr_t Output_Handler_attributes = {
    .name = "Output_Handler",
    .priority = (osPriority_t)osPriorityNormal,
    .stack_size = 128 * 4};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void InputHandler(void *argument);
void OutputHandler(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
 * @brief  FreeRTOS initialization
 * @param  None
 * @retval None
 */
void MX_FREERTOS_Init(void)
{
    /* USER CODE BEGIN Init */
    DataModel_Init(&g_tButtonEvent);

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
    defaultTaskHandle =
        osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

    /* creation of Input_Handler */
    Input_HandlerHandle =
        osThreadNew(InputHandler, NULL, &Input_Handler_attributes);

    /* creation of Output_Handler */
    Output_HandlerHandle =
        osThreadNew(OutputHandler, NULL, &Output_Handler_attributes);

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
    /* Infinite loop */
    for (;;)
    {
        osDelay(1);
    }
    /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_InputHandler */
/**
 * @brief Function implementing the Input_Handler thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_InputHandler */
void InputHandler(void *argument)
{
    /* USER CODE BEGIN InputHandler */
    /* Initialize the Input Handler */
    InputHandler_Init(&g_tButtonEvent);
    /* Infinite loop */
    for (;;)
    {
        InputHandler_Loop();
        osDelay(1);
    }
    /* USER CODE END InputHandler */
}

/* USER CODE BEGIN Header_OutputHandler */
/**
 * @brief Function implementing the Output_Handler thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_OutputHandler */
void OutputHandler(void *argument)
{
    /* USER CODE BEGIN OutputHandler */
    OutputHandler_Init(&g_tButtonEvent);
    /* Infinite loop */
    for (;;)
    {
        OutputHandler_Loop();
        osDelay(1);
    }
    /* USER CODE END OutputHandler */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
