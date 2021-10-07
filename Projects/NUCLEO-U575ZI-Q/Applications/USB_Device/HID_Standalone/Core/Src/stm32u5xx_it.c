/**
  ******************************************************************************
  * @file    USB_Device/HID_Standalone/Core/Src/stm32u5xx_it.c
  * @author  MCD Application Team
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and
  *          peripherals interrupt service routine.
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
#include "stm32u5xx_it.h"
/* Private includes ----------------------------------------------------------*/


/* Private typedef -----------------------------------------------------------*/


/* Private define ------------------------------------------------------------*/


/* Private macro -------------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
extern void SystemClockConfig_Resume(void);

/* Private user code ---------------------------------------------------------*/


/* External variables --------------------------------------------------------*/
extern PCD_HandleTypeDef hpcd_USB_OTG_FS;


/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{


}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{

  while (1)
  {
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{

  while (1)
  {
  }
}

/**
  * @brief This function handles Prefetch fault, memory access fault.
  */
void BusFault_Handler(void)
{

  while (1)
  {
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{

  while (1)
  {
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{


}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{


}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{


}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{

  HAL_IncTick();

}

/******************************************************************************/
/* STM32U5xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32u5xx.s).                    */
/******************************************************************************/
/**
  * @brief  This function handles UCPD1 interrupts.
  * @retval None
  */
void UCPD1_IRQHandler(void)
{
  USBPD_PORT0_IRQHandler();
}

/**
* @brief  This function handles USB-On-The-Go FS/HS global interrupt request.
* @param  None
* @retval None
*/
void OTG_FS_IRQHandler(void)
{

    HAL_PCD_IRQHandler(&hpcd_USB_OTG_FS);

}

/**
  * @brief  This function handles External lines interrupt request.
  * @param  None
  * @retval None
  */

void EXTI13_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(BUTTON_KEY_PIN);
}
