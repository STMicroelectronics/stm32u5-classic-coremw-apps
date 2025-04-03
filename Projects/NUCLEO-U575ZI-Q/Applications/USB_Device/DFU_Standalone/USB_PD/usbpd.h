/**
  ******************************************************************************
  * @file    usbpd.h
  * @author  MCD Application Team
  * @brief   This file contains the device define.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __usbpd_H
#define __usbpd_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "usbpd_core.h"
#include "usbpd_dpm_core.h"
#include "usbpd_dpm_conf.h"


/* Global variables ---------------------------------------------------------*/


/* USBPD init function */
void MX_USBPD_Init(void);


#ifdef __cplusplus
}
#endif
#endif /*__usbpd_H */

/**
  * @}
  */

/**
  * @}
  */
