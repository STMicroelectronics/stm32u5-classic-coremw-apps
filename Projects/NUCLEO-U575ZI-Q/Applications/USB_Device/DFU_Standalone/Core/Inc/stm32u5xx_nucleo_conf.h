/**
  ******************************************************************************
  * @file    stm32u5xx_nucleo_conf.h
  * @author  MCD Application Team
  * @brief   STM32U5XX nucleo board configuration file.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32U5XX_NUCLEO_CONF_H
#define STM32U5XX_NUCLEO_CONF_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx_hal.h"

/* Usage of nucleo board */
#define USE_NUCLEO_144      1U

/* Usage of COM feature */
#define USE_BSP_COM_FEATURE 1U
#define USE_COM_LOG         0U

/* Button user interrupt priority */
#define BSP_BUTTON_USER_IT_PRIORITY 0x07UL  /* Default is lowest priority level */

#ifdef __cplusplus
}
#endif

#endif /* STM32U5XX_NUCLEO_CONF_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
