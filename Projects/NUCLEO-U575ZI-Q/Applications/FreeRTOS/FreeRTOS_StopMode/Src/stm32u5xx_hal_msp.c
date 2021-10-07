/**
  ******************************************************************************
  * @file    FreeRTOS/FreeRTOS_StopMode/Src/stm32u5xx_hal_msp.c
  * @author  MCD Application Team
  * @brief   This file provides code for the MSP Initialization
  *                      and de-Initialization codes.
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



/* Private typedef -----------------------------------------------------------*/


/* Private define ------------------------------------------------------------*/


/* Private macro -------------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/


/* External functions ------------------------------------------------------- */



/**
  * Initializes the Global MSP.
  */
void HAL_MspInit(void)
{


  __HAL_RCC_PWR_CLK_ENABLE();

  HAL_PWREx_DisableUCPDDeadBattery();
}

/**
* @brief  LPTIM MSP Init
* @param  hlptim : LPTIM handle
* @retval None
*/
void HAL_LPTIM_MspInit(LPTIM_HandleTypeDef *hlptim)
{
  if(hlptim->Instance==LPTIM1)
  {
    RCC_PeriphCLKInitTypeDef RCC_PeriphCLKInitStruct;
    RCC_OscInitTypeDef RCC_OscInitStruct;		
	  
    /* Enable LSE clock */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSE;
    RCC_OscInitStruct.LSEState = RCC_LSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
      Error_Handler();
    }
	  
    /* Select the LSE clock as LPTIM1 peripheral clock */
    RCC_PeriphCLKInitStruct.PeriphClockSelection = RCC_PERIPHCLK_LPTIM1;
    RCC_PeriphCLKInitStruct.Lptim1ClockSelection = RCC_LPTIM1CLKSOURCE_LSE;
    HAL_RCCEx_PeriphCLKConfig(&RCC_PeriphCLKInitStruct); 
		
    /* Enable LPTIM clock */
    __HAL_RCC_LPTIM1_CLK_ENABLE();
	  
    /* Force & Release the LPTIM Periheral Clock Reset */  
    /* Force the LPTIM Peripheral Clock Reset */
    __HAL_RCC_LPTIM1_FORCE_RESET();
	  
    /* Release the LPTIM Peripheral Clock Reset */
    __HAL_RCC_LPTIM1_RELEASE_RESET();
	  
    /* Enable and set LPTIM Interrupt to the highest priority */
    HAL_NVIC_SetPriority(LPTIM1_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(LPTIM1_IRQn);
  }
}

/**
* @brief LPTIM MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param hlptim: LPTIM handle pointer
* @retval None
*/
void HAL_LPTIM_MspDeInit(LPTIM_HandleTypeDef* hlptim)
{
  if(hlptim->Instance==LPTIM1)
  {
    /* Force the LPTIM Peripheral Clock Reset */
    __HAL_RCC_LPTIM1_FORCE_RESET();

    /* Release the LPTIM Peripheral Clock Reset */
    __HAL_RCC_LPTIM1_RELEASE_RESET();

    /* Peripheral clock disable */
    __HAL_RCC_LPTIM1_CLK_DISABLE();

    /* LPTIM1 interrupt DeInit */
    HAL_NVIC_DisableIRQ(LPTIM1_IRQn);

  }

}

/**
  * @}
  */

/**
  * @}
  */

