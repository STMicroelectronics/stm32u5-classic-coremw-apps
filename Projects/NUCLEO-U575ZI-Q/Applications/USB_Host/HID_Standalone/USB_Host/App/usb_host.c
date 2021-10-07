/**
  ******************************************************************************
  * @file    : USB_Host/HID_Standalone/USB_Host/App/usb_host.c
  * @author  : MCD Application Team
  * @brief   : This file implements the USB Host
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

#include "usb_host.h"
#include "usbh_core.h"
#include "usbh_hid.h"



/* Private variables ---------------------------------------------------------*/
__IO HID_APP_State hid_app_state;

/* Private function prototypes -----------------------------------------------*/
void USBH_Clock_Config(void);
extern void HID_MOUSE_App(USBH_HandleTypeDef *phost);
extern void HID_KEYBRD_App(USBH_HandleTypeDef *phost);
extern void Error_Handler(void);

/* USB Host core handle declaration */
USBH_HandleTypeDef hUsbHost;
ApplicationTypeDef Appli_state = APPLICATION_IDLE;

/*
 * -- Insert your variables declaration here --
 */
/**
  * @brief USB Clock Configuration
  * @retval None
  */
void USBH_Clock_Config(void)
{
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};

  __HAL_RCC_PWR_CLK_ENABLE();
  /* Enable HSI48 */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_CLK48;
  PeriphClkInitStruct.Clk48ClockSelection  = RCC_CLK48CLKSOURCE_HSI48;
  HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct)!= HAL_OK)
  {
    Error_Handler();
  }
}

/*
 * user callback declaration
 */
static void USBH_UserProcess(USBH_HandleTypeDef *phost, uint8_t id);

/*
 * -- Insert your external function declaration here --
 */

/**
* @brief  Manages HID Application Process.
* @param  None
* @retval None
*/
void USBH_HID_AppProcess(void)
{
  switch(hid_app_state)
  {
  case HID_APP_WAIT:
    if(Appli_state == APPLICATION_READY)
    {
      if(USBH_HID_GetDeviceType(&hUsbHost) == HID_KEYBOARD)
      {
        hid_app_state = HID_APP_KEYBOARD;
        USBH_UsrLog("Use Keyboard to tape characters:");

      }
      else if(USBH_HID_GetDeviceType(&hUsbHost) == HID_MOUSE)
      {

        hid_app_state = HID_APP_MOUSE;
        USBH_UsrLog("USB HID Host Mouse App...");

      }
    }
    break;

  case HID_APP_MOUSE:
    if(Appli_state == APPLICATION_READY)
    {
      HID_MOUSE_App(&hUsbHost);
    }
    break;

  case HID_APP_KEYBOARD:
    if(Appli_state == APPLICATION_READY)
    {
      HID_KEYBRD_App(&hUsbHost);
    }
    break;

  default:
    break;
  }

  if(Appli_state == APPLICATION_DISCONNECT)
  {
    Appli_state = APPLICATION_IDLE;
    USBH_ErrLog("USB device disconnected !!! \n");
    hid_app_state = HID_APP_WAIT;
  }
}

/**
  * Init USB host library, add supported class and start the library
  * @retval None
  */
void MX_USB_HOST_Init(void)
{
  USBH_Clock_Config();


  /* Init host Library, add supported class and start the library. */
  if (USBH_Init(&hUsbHost, USBH_UserProcess, HOST_FS) != USBH_OK)
  {
    Error_Handler();
  }
  if (USBH_RegisterClass(&hUsbHost, USBH_HID_CLASS) != USBH_OK)
  {
    Error_Handler();
  }
  if (USBH_Start(&hUsbHost) != USBH_OK)
  {
    Error_Handler();
  }
  USBH_UsrLog(" **** USB OTG FS HID Host **** \n");
  USBH_UsrLog("USB Host library started.\n");

  /* Initialize Application and HID process */

  USBH_UsrLog("Starting HID Application");
  USBH_UsrLog("Connect your HID Device\n");
  hid_app_state = HID_APP_WAIT;

}

/*
 * Background task
 */
void MX_USB_HOST_Process(void)
{
  /* USB Host Background task */
  USBH_Process(&hUsbHost);

  /* HID Application Process */
  USBH_HID_AppProcess();
}
/*
 * user callback definition
 */
static void USBH_UserProcess  (USBH_HandleTypeDef *phost, uint8_t id)
{
  switch(id)
  {
  case HOST_USER_CONNECTION:
  break;

  case HOST_USER_DISCONNECTION:
  Appli_state = APPLICATION_DISCONNECT;
  break;

  case HOST_USER_CLASS_ACTIVE:
  Appli_state = APPLICATION_READY;
  break;

  default:
  break;
  }
}

/**
  * @}
  */

/**
  * @}
  */
