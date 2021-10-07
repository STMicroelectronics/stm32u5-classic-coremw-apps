/**
  ******************************************************************************
  * @file    FreeRTOS\FreeRTOS_StopMode\Src\main.c
  * @author  MCD Application Team
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/


/* Private typedef -----------------------------------------------------------*/


/* Private define ------------------------------------------------------------*/


/* Private macro -------------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/
LPTIM_HandleTypeDef LptimHandle;

osThreadId_t TxThreadHandle;
const osThreadAttr_t TxThread_attributes = {
  .name = "TxThread",
  .priority = (osPriority_t) osPriorityBelowNormal,
  .stack_size = 512 
};
osThreadId_t RxThreadHandle;
const osThreadAttr_t RxThread_attributes = {
  .name = "RxThread",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 512
};
osMessageQueueId_t osqueueHandle;
const osMessageQueueAttr_t osqueue_attributes = {
  .name = "osqueue"
};
osSemaphoreId_t osSemaphoreHandle;
const osSemaphoreAttr_t osSemaphore_attributes = {
  .name = "osSemaphore"
};

uint32_t   osQueueMsg;
uint32_t Queue_value = 100;
__IO uint32_t OsStatus = 0;

/* Private function prototypes -----------------------------------------------*/
static void MX_LPTIM1_Init(void);
void QueueSendThread(void *argument);
void QueueReceiveThread(void *argument);
void SystemClock_Config(void);
static void CACHE_Enable(void);


/* Private user code ---------------------------------------------------------*/


/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{


  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();
  
  /* Enable the Instruction Cache */
  CACHE_Enable();



  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize LEDs */
  BSP_LED_Init(LED1);
  MX_LPTIM1_Init();
  /* Initialize all configured peripherals */
  if (HAL_LPTIM_Counter_Start_IT(&LptimHandle) != HAL_OK)
  {
    Error_Handler();
  }
  osKernelInitialize();
  /* add mutexes, ... */

  /* add semaphores, ... */
    osSemaphoreHandle = osSemaphoreNew(1, 1, &osSemaphore_attributes);

  /* Create the timer(s) */

  

  /* definition and creation of LEDThread */
  TxThreadHandle = osThreadNew(QueueSendThread, NULL, &TxThread_attributes);
  RxThreadHandle = osThreadNew(QueueReceiveThread, NULL, &RxThread_attributes);


  osqueueHandle = osMessageQueueNew (1, sizeof(uint16_t), &osqueue_attributes);


  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */

  /* Infinite loop */
  while (1)
  {

  }
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follows :
  *            System Clock source            = PLL (MSI)
  *            SYSCLK(Hz)                     = 160000000
  *            HCLK(Hz)                       = 160000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 1
  *            APB2 Prescaler                 = 1
  *            APB3 Prescaler                 = 1
  *            MSI Frequency(Hz)              = 4000000
  *            PLL_MBOOST                     = 1
  *            PLL_M                          = 1
  *            PLL_N                          = 80
  *            PLL_Q                          = 2
  *            PLL_R                          = 2
  *            PLL_P                          = 2
  *            Flash Latency(WS)              = 4
  * @param  None
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};

  /* Enable voltage range 1 for frequency above 100 Mhz */
  __HAL_RCC_PWR_CLK_ENABLE();
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);
  __HAL_RCC_PWR_CLK_DISABLE();

  /* MSI Oscillator enabled at reset (4Mhz), activate PLL with MSI as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_4;
  RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLMBOOST = RCC_PLLMBOOST_DIV1;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 80;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLFRACN= 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    /* Initialization Error */
    while(1);
  }

  /* Select PLL as system clock source and configure bus clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | \
                                 RCC_CLOCKTYPE_PCLK2  | RCC_CLOCKTYPE_PCLK3);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_HCLK_DIV1;
  if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    /* Initialization Error */
    while(1);
  }
}

/**
  * @brief LptimHandle Initialization Function
  * @param None
  * @retval None
  */
static void MX_LPTIM1_Init(void)
{




  LptimHandle.Instance = LPTIM1;
  LptimHandle.Init.Clock.Source = LPTIM_CLOCKSOURCE_APBCLOCK_LPOSC;
  LptimHandle.Init.Clock.Prescaler = LPTIM_PRESCALER_DIV2;
  LptimHandle.Init.Trigger.Source = LPTIM_TRIGSOURCE_SOFTWARE;
  LptimHandle.Init.UpdateMode = LPTIM_UPDATE_IMMEDIATE;
  LptimHandle.Init.CounterSource = LPTIM_COUNTERSOURCE_INTERNAL;
  LptimHandle.Init.Input1Source = LPTIM_INPUT1SOURCE_GPIO;
  LptimHandle.Init.Input2Source = LPTIM_INPUT2SOURCE_GPIO;
  LptimHandle.Init.RepetitionCounter = 0;

  /* Initialize LPTIM peripheral according to the passed parameters */
  if (HAL_LPTIM_Init(&LptimHandle) != HAL_OK)
  {
    Error_Handler();
  }
  


}

/**
  * @brief  Autoreload match callback in non blocking mode 
  * @param  hlptim : LPTIM handle
  * @retval None
  */
void HAL_LPTIM_AutoReloadMatchCallback(LPTIM_HandleTypeDef *hlptim)
{
  osSemaphoreRelease(osSemaphoreHandle);
}

/**
  * @brief  Function implementing the LEDThread thread.
  * @param  argument: Not used
  * @retval None
  */
static void QueueSendThread(void *argument)
{


  for (;;)
  {
    if (osSemaphoreHandle != NULL)
    {
      /* Try to obtain the semaphore */
      OsStatus = osSemaphoreAcquire(osSemaphoreHandle, osWaitForever);
      if (OsStatus == osOK)
      {
        osMessageQueuePut(osqueueHandle, &Queue_value, 100, NULL);
      }
    }

  }


}
/**
* @brief Function implementing the QueueReceiveThread thread.
* @param argument: Not used
* @retval None
*/
void QueueReceiveThread(void *argument)
{

  for (;;)
  {
    OsStatus = osMessageQueueGet(osqueueHandle, &osQueueMsg, NULL, 100);

    if (OsStatus == osOK)
    {
      if (osQueueMsg == Queue_value)
      {
        BSP_LED_Toggle(LED1);
        osDelay(1000);
      }
    }
  }
}


/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
  {
  /* User can add his own implementation to report the HAL error return state */

}

/**
  * @brief  Enable ICACHE with 1-way set-associative configuration.
  * @param  None
  * @retval None
  */
static void CACHE_Enable(void)
{
  /* Configure ICACHE associativity mode */
  HAL_ICACHE_ConfigAssociativityMode(ICACHE_1WAY);

  /* Enable ICACHE */
  HAL_ICACHE_Enable();
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(char *file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {}
}
#endif /* USE_FULL_ASSERT */


