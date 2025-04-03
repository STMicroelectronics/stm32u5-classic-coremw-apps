/**
  ******************************************************************************
  * @file    usbpd.c
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

/* Includes ------------------------------------------------------------------*/
#include "usbpd.h"
#include "main.h"

/* Private variables ---------------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/


/* USBPD init function */
void MX_USBPD_Init(void)
{
  /* Initialize the Device Policy Manager */
  if (USBPD_OK != USBPD_DPM_InitCore())
  {
    Error_Handler();
  }

  if (USBPD_OK != USBPD_DPM_InitOS())
  {
    Error_Handler();
  }
}


/**
  * @}
  */

/**
  * @}
  */