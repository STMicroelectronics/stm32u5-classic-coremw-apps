/**
  ******************************************************************************
  * @file    FreeRTOS/FreeRTOS_SecureIOToggle_TrustZone/Secure/Src/main.c
  * @author  MCD Application Team
  * @brief   Main secure program body
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

/* Private includes ----------------------------------------------------------*/
#include <stdio.h>


/* Private typedef -----------------------------------------------------------*/


/* Private define ------------------------------------------------------------*/

/* Non-secure Vector table to jump to (internal Flash Bank2 here)             */
/* Caution: address must correspond to non-secure internal Flash where is     */
/*          mapped in the non-secure vector table                             */
#define VTOR_TABLE_NS_START_ADDR  0x08100000U

/* Private macro -------------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/



/* Private function prototypes -----------------------------------------------*/
static void NonSecure_Init(void);
static void MX_GTZC_Init(void);
static void SystemIsolation_Config(void);
static void CACHE_Enable(void);



/* Private user code ---------------------------------------------------------*/


/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* SAU/IDAU, FPU and interrupts secure/non-secure allocation setup done */
  /* in SystemInit() based on partition_stm32u575xx.h file's definitions. */
  /* Enable SecureFault handler (HardFault is default) */
  SCB->SHCSR |= SCB_SHCSR_SECUREFAULTENA_Msk;

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();
  
  /* Enable the Instruction Cache */
  CACHE_Enable();
  

  /* SAU/IDAU, FPU and interrupts secure/non-secure allocation setup done */
  /* in SystemInit() based on partition_stm32u575xx.h file's definitions. */

  /* Secure/Non-secure Memory and Peripheral isolation configuration */
  SystemIsolation_Config();


  /* GTZC initialisation */
  MX_GTZC_Init();



  /* Initialize all configured peripherals */
  /* All IOs are by default allocated to secure */
  /* Release them all to non-secure except PC.07 (LED1) kept as secure */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  HAL_GPIO_ConfigPinAttributes(GPIOA, GPIO_PIN_ALL, GPIO_PIN_NSEC);
  HAL_GPIO_ConfigPinAttributes(GPIOB, GPIO_PIN_ALL, GPIO_PIN_NSEC);
  HAL_GPIO_ConfigPinAttributes(GPIOC, (GPIO_PIN_ALL & ~(GPIO_PIN_7)), GPIO_PIN_NSEC);
  HAL_GPIO_ConfigPinAttributes(GPIOD, GPIO_PIN_ALL, GPIO_PIN_NSEC);
  HAL_GPIO_ConfigPinAttributes(GPIOE, GPIO_PIN_ALL, GPIO_PIN_NSEC);
  HAL_GPIO_ConfigPinAttributes(GPIOF, GPIO_PIN_ALL, GPIO_PIN_NSEC);
  HAL_GPIO_ConfigPinAttributes(GPIOG, GPIO_PIN_ALL, GPIO_PIN_NSEC);
  HAL_GPIO_ConfigPinAttributes(GPIOH, GPIO_PIN_ALL, GPIO_PIN_NSEC);

  /* Leave the GPIO clocks enabled to let non-secure having I/Os control */

  /* Initialize PC.07 to drive external LED (LED1) */
  BSP_LED_Init(LED1);

  /* Secure SysTick should rather be suspended before calling non-secure  */
  /* in order to avoid wake-up from sleep mode entered by non-secure      */
  /* The Secure SysTick shall be resumed on non-secure callable functions */
  HAL_SuspendTick();
 
 

  /*************** Setup and jump to non-secure *******************************/

  NonSecure_Init();

  /* Non-secure software does not return, this code is not executed */
  /* Infinite loop */
  while (1)
  {

  }

}

/**
  * @brief  Non-secure call function
  *         This function is responsible for Non-secure initialization and switch
  *         to non-secure state
  * @retval None
  */
static void NonSecure_Init(void)
{
  funcptr_NS NonSecure_ResetHandler;

  SCB_NS->VTOR = VTOR_TABLE_NS_START_ADDR;

  /* Set non-secure main stack (MSP_NS) */
  __TZ_set_MSP_NS((*(uint32_t *)VTOR_TABLE_NS_START_ADDR));

  /* Get non-secure reset handler */
  NonSecure_ResetHandler = (funcptr_NS)(*((uint32_t *)((VTOR_TABLE_NS_START_ADDR) + 4U)));

  /* Start non-secure state software application */
  NonSecure_ResetHandler();
}
/**
  * @brief  System Isolation Configuration
  *         This function is responsible for Memory and Peripheral isolation
  *         for secure and non-secure application parts
  * @retval None
  */
static void SystemIsolation_Config(void)
{
  uint32_t index;
  MPCBB_ConfigTypeDef MPCBB_desc;

  /* Enable GTZC peripheral clock */
  __HAL_RCC_GTZC1_CLK_ENABLE();
  /* __HAL_RCC_GTZC2_CLK_ENABLE(); */

  /* -------------------------------------------------------------------------*/
  /*                   Memory isolation configuration                         */
  /* Initializes the memory that secure application books for non secure      */
  /* -------------------------------------------------------------------------*/

  /* -------------------------------------------------------------------------*/
  /* Internal RAM :                                                  */
  /* The booking is done through GTZC MPCBB.                         */
  /* Internal SRAMs are secured by default and configured by block   */
  /* of 512 bytes.                                                   */
  /* Internal SRAM3 (starting from 0x20040000) will be configured as */
  /* fully non-secure.                                               */
 
  MPCBB_desc.SecureRWIllegalMode = GTZC_MPCBB_SRWILADIS_ENABLE;
  MPCBB_desc.InvertSecureState   = GTZC_MPCBB_INVSECSTATE_NOT_INVERTED;
  MPCBB_desc.AttributeConfig.MPCBB_LockConfig_array[0] = 0x00000000U;  /* Unlocked configuration */

  for (index=0; index<32; index++)
  {
    /* Non-secure blocks */
    MPCBB_desc.AttributeConfig.MPCBB_SecConfig_array[index] = 0x00000000U;
  }

  if (HAL_GTZC_MPCBB_ConfigMem(SRAM3_BASE, &MPCBB_desc) != HAL_OK)
  {
    /* Initialization Error */
    while(1);
  }

  /* -------------------------------------------------------------------------*/
  /* Internal Flash */
  /* The booking is done in both IDAU/SAU and FLASH interface */

  /* Setup done based on Flash dual-bank mode described with 1 area per bank  */
  /* Non-secure Flash memory area starting from 0x08100000 (Bank2)            */
  /* Flash memory is secured by default and modified with Option Byte Loading */
  /* Insure SECWM2_PSTRT > SECWM2_PEND in order to have all Bank2 non-secure  */

  /* -------------------------------------------------------------------------*/
  /* External OctoSPI memory */
  /* The booking is done in both IDAU/SAU and GTZC MPCWM interface */

  /* Default secure configuration */
  /* Else need to use HAL_GTZC_TZSC_MPCWM_ConfigMemAttributes() */

  /* -------------------------------------------------------------------------*/
  /* External NOR/FMC memory */
  /* The booking is done in both IDAU/SAU and GTZC MPCWM interface */

  /* Default secure configuration */
  /* Else need to use HAL_GTZC_TZSC_MPCWM_ConfigMemAttributes() */

  /* -------------------------------------------------------------------------*/
  /* External NAND/FMC memory */
  /* The booking is done in both IDAU/SAU and GTZC MPCWM interface */

  /* Default secure configuration */
  /* Else need to use HAL_GTZC_TZSC_MPCWM_ConfigMemAttributes() */


  /* -------------------------------------------------------------------------*/
  /*                   Peripheral isolation configuration                     */
  /* Initializes the peripherals and features that secure application books   */
  /* for secure (RCC, PWR, RTC, EXTI, DMA, OTFDEC, etc..) or leave them to    */
  /* non-secure (GPIO (secured by default))                                   */
  /* -------------------------------------------------------------------------*/

  /* Enable all illegal access interrupts in GTZC TZIC */
  if(HAL_GTZC_TZIC_EnableIT(GTZC_PERIPH_ALL) != HAL_OK)
  {
    /* Initialization Error */
    while(1);
  }

  /* Enable GTZC secure interrupt */
  HAL_NVIC_SetPriority(GTZC_IRQn, 0, 0); /* Highest priority level */
  HAL_NVIC_EnableIRQ(GTZC_IRQn);
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
  if(HAL_ICACHE_Enable() != HAL_OK)
  {
    /* Initialization Error */
    while(1);
  }
}

/**
  * @brief GTZC Initialization Function
  * @param None
  * @retval None
  */
static void MX_GTZC_Init(void)
{



  MPCBB_ConfigTypeDef MPCBB2_NonSecureArea_Desc = {0};


  
  MPCBB2_NonSecureArea_Desc.SecureRWIllegalMode = GTZC_MPCBB_SRWILADIS_ENABLE;
  MPCBB2_NonSecureArea_Desc.InvertSecureState = GTZC_MPCBB_INVSECSTATE_NOT_INVERTED;
  MPCBB2_NonSecureArea_Desc.AttributeConfig.MPCBB_SecConfig_array[0] =   0x00000000;
  MPCBB2_NonSecureArea_Desc.AttributeConfig.MPCBB_SecConfig_array[1] =   0x00000000;
  MPCBB2_NonSecureArea_Desc.AttributeConfig.MPCBB_SecConfig_array[2] =   0x00000000;
  MPCBB2_NonSecureArea_Desc.AttributeConfig.MPCBB_SecConfig_array[3] =   0x00000000;
  MPCBB2_NonSecureArea_Desc.AttributeConfig.MPCBB_SecConfig_array[4] =   0x00000000;
  MPCBB2_NonSecureArea_Desc.AttributeConfig.MPCBB_SecConfig_array[5] =   0x00000000;
  MPCBB2_NonSecureArea_Desc.AttributeConfig.MPCBB_SecConfig_array[6] =   0x00000000;
  MPCBB2_NonSecureArea_Desc.AttributeConfig.MPCBB_SecConfig_array[7] =   0x00000000;
  MPCBB2_NonSecureArea_Desc.AttributeConfig.MPCBB_LockConfig_array[0] =   0x00000000;
  if (HAL_GTZC_MPCBB_ConfigMem(SRAM2_BASE, &MPCBB2_NonSecureArea_Desc) != HAL_OK)
  {
    Error_Handler();
  }


}



/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
  }
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* Infinite loop */
  while (1)
  {
  }
}
#endif /* USE_FULL_ASSERT */

