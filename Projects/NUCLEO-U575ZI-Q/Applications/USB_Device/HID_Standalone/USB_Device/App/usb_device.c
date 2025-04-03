/**
  ******************************************************************************
  * @file    USB_Device/HID_Standalone/USB_Device/App/usb_device.c
  * @author  MCD Application Team
  * @brief   This file implements the USB Device
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

#include "usb_device.h"
#include "usbd_core.h"
#include "usbd_desc.h"
#include "usbd_hid.h"

#include "main.h"

/* Private variables ---------------------------------------------------------*/
__IO uint32_t remotewakeupon = 0;
uint8_t HID_Buffer[4];

extern PCD_HandleTypeDef hpcd_USB_OTG_FS;

#define CURSOR_STEP     5

/* Private function prototypes -----------------------------------------------*/
static void GetPointerData(uint8_t *pbuf);
extern void SystemClockConfig_Resume(void);

/* USB Device Core handle declaration. */
USBD_HandleTypeDef hUsbDeviceFS;

extern USBD_DescriptorsTypeDef HID_Desc;

/*
 * -- Insert your variables declaration here --
 */
/*
 * -- Insert your external function declaration here --
 */

/**
  * @brief  Gets Pointer Data.
  * @param  pbuf: Pointer to report
  * @retval None
  */
void GetPointerData(uint8_t * pbuf)
{
  static int8_t cnt = 0;
  int8_t x = 0, y = 0;

  if (cnt++ > 0)
  {
    x = CURSOR_STEP;
  }
  else
  {
    x = -CURSOR_STEP;
  }
  pbuf[0] = 0;
  pbuf[1] = x;
  pbuf[2] = y;
  pbuf[3] = 0;
}

/**
  * @brief  GPIO EXTI Callback function
  *         Handle remote-wakeup through key button
  * @param  GPIO_Pin
  * @retval None
  */
void HAL_GPIO_EXTI_Rising_Callback(uint16_t GPIO_Pin)
{
  if (GPIO_Pin == BUTTON_KEY_PIN)
  {
    if ((((USBD_HandleTypeDef *) hpcd_USB_OTG_FS.pData)->dev_remote_wakeup == 1) &&
        (((USBD_HandleTypeDef *) hpcd_USB_OTG_FS.pData)->dev_state ==
         USBD_STATE_SUSPENDED))
    {
#ifndef USBD_LPM_SLEEP_CONFIG
      if ((&hpcd_USB_OTG_FS)->Init.low_power_enable)
      {
        SystemClockConfig_Resume();
        __HAL_PCD_UNGATE_PHYCLOCK(&hpcd_USB_OTG_FS);
      }
#endif
      /* Activate Remote wakeup */
      HAL_PCD_ActivateRemoteWakeup((&hpcd_USB_OTG_FS));

      /* Remote wakeup delay */
      HAL_Delay(10);

      /* Disable Remote wakeup */
      HAL_PCD_DeActivateRemoteWakeup((&hpcd_USB_OTG_FS));

      /* change state to configured */
      ((USBD_HandleTypeDef *) hpcd_USB_OTG_FS.pData)->dev_state = USBD_STATE_CONFIGURED;

      /* Change remote_wakeup feature to 0 */
      ((USBD_HandleTypeDef *) hpcd_USB_OTG_FS.pData)->dev_remote_wakeup = 0;
      remotewakeupon = 1;
    }
    else if (((USBD_HandleTypeDef *) hpcd_USB_OTG_FS.pData)->dev_state ==
         USBD_STATE_CONFIGURED)
    {
      GetPointerData(HID_Buffer);
      USBD_HID_SendReport(&hUsbDeviceFS, HID_Buffer, 4);
    }
  }
}


/**
  * Init USB device Library, add supported class and start the library
  * @retval None
  */
void MX_USB_Device_Init(void)
{
  /* Init Device Library, add supported class and start the library. */
  if (USBD_Init(&hUsbDeviceFS, &HID_Desc, DEVICE_FS) != USBD_OK)
  {
    Error_Handler();
  }
  if (USBD_RegisterClass(&hUsbDeviceFS, &USBD_HID) != USBD_OK)
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

