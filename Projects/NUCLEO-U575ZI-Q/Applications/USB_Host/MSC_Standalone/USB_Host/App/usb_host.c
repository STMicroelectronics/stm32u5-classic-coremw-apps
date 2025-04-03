/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    : USB_Host/MSC_Standalone/USB_Host/App/usb_host.c
  * @author  : MCD Application Team
  * @brief   : This file implements the USB Host
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
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/

#include "usb_host.h"
#include "usbh_core.h"
#include "usbh_msc.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
extern char USBDISKPath[4];          /* USB Host logical drive path */
extern FATFS USBDISKFatFs;           /* File system object for USB disk logical drive */
extern void Error_Handler(void);
__IO MSC_APP_State msc_app_state;
/* USER CODE END PV */

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
void USBH_Clock_Config(void);
extern FRESULT msc_explore_disk(char *path, uint8_t recu_level);
/* USER CODE END PFP */

/* USB Host core handle declaration */
USBH_HandleTypeDef hUsbHost;
ApplicationTypeDef Appli_state = APPLICATION_IDLE;

/*
 * -- Insert your variables declaration here --
 */
/* USER CODE BEGIN 0 */
/**
  * @brief USB Clock Configuration
  * @retval None
  */
void USBH_Clock_Config(void)
{
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  __HAL_RCC_PWR_CLK_ENABLE();

  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_CLK48;
  PeriphClkInitStruct.IclkClockSelection = RCC_CLK48CLKSOURCE_PLL2;
  PeriphClkInitStruct.PLL2.PLL2Source = RCC_PLLSOURCE_HSE;
  PeriphClkInitStruct.PLL2.PLL2M = 1;
  PeriphClkInitStruct.PLL2.PLL2N = 18;
  PeriphClkInitStruct.PLL2.PLL2P = 2;
  PeriphClkInitStruct.PLL2.PLL2Q = 3;
  PeriphClkInitStruct.PLL2.PLL2R = 2;
  PeriphClkInitStruct.PLL2.PLL2RGE = RCC_PLLVCIRANGE_1;
  PeriphClkInitStruct.PLL2.PLL2FRACN = 0.0;
  PeriphClkInitStruct.PLL2.PLL2ClockOut = RCC_PLL2_DIVQ;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}
/* USER CODE END 0 */

/*
 * user callback declaration
 */
static void USBH_UserProcess(USBH_HandleTypeDef *phost, uint8_t id);

/*
 * -- Insert your external function declaration here --
 */
/* USER CODE BEGIN 1 */

/**
* @brief  Manages MSC Application Process.
* @param  None
* @retval None
*/
void USBH_MSC_AppProcess(void)
{
  switch(msc_app_state)
  {
  case MSC_APP_WAIT:
    msc_app_state = MSC_APP_FILE_OPERATIONS;
    break;

  case MSC_APP_FILE_OPERATIONS:
    /* Read and Write File Here */
    if(Appli_state == APPLICATION_READY)
    {
      USBH_UsrLog("\n\n*** Files operations ***\n");
      msc_app_state = MSC_APP_EXPLORER;
      if(msc_file_operations() != 0)
      {
        msc_app_state = MSC_APP_IDLE;
        return;
      }
    }
    break;

  case MSC_APP_EXPLORER:
    /* Display disk content */
    if(Appli_state == APPLICATION_READY)
    {
      USBH_UsrLog("\n\n*** Explore Disk ***\n\n");
      msc_explore_disk("0:/", 1);
      msc_app_state = MSC_APP_IDLE;
    }
    break;

  default:
    break;
  }
  if(Appli_state == APPLICATION_DISCONNECT)
  {
    Appli_state = APPLICATION_IDLE;
    USBH_UsrLog("USB device disconnected !!! \n");
    msc_app_state = MSC_APP_WAIT;
  }
}
/* USER CODE END 1 */

/**
  * Init USB host library, add supported class and start the library
  * @retval None
  */
void MX_USB_HOST_Init(void)
{
  /* USER CODE BEGIN USB_HOST_Init_PreTreatment */
  USBH_Clock_Config();
  /* USER CODE END USB_HOST_Init_PreTreatment */

  /* Init host Library, add supported class and start the library. */
  if (USBH_Init(&hUsbHost, USBH_UserProcess, HOST_FS) != USBH_OK)
  {
    Error_Handler();
  }
  if (USBH_RegisterClass(&hUsbHost, USBH_MSC_CLASS) != USBH_OK)
  {
    Error_Handler();
  }
  if (USBH_Start(&hUsbHost) != USBH_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USB_HOST_Init_PostTreatment */
  USBH_UsrLog(" **** USB OTG FS MSC Host **** \n");
  USBH_UsrLog("USB Host library started.\n");

  /* Initialize Application and MSC process */

  USBH_UsrLog("Starting MSC Application");
  USBH_UsrLog("Connect your MSC Device\n");
  msc_app_state = MSC_APP_WAIT;

  /* USER CODE END USB_HOST_Init_PostTreatment */
}

/*
 * Background task
 */
void MX_USB_HOST_Process(void)
{
  /* USB Host Background task */
  USBH_Process(&hUsbHost);

  /* MSC Application Process */
  USBH_MSC_AppProcess();
}
/*
 * user callback definition
 */
static void USBH_UserProcess  (USBH_HandleTypeDef *phost, uint8_t id)
{
  /* USER CODE BEGIN CALL_BACK_1 */
  switch(id)
  {
  case HOST_USER_CONNECTION:
  break;

  case HOST_USER_DISCONNECTION:
    Appli_state = APPLICATION_DISCONNECT;
    if (f_mount(NULL, "", 0) != FR_OK)
    {
      USBH_UsrLog("ERROR : Cannot DeInitialize FatFs! \n");
    }
    if (FATFS_UnLinkDriver(USBDISKPath) != 0)
    {
      USBH_UsrLog("ERROR : Cannot UnLink FatFS Driver! \n");
    }
    break;

  case HOST_USER_CLASS_ACTIVE:
    Appli_state = APPLICATION_READY;
    if(FATFS_LinkDriver(&USBH_Driver, USBDISKPath)==0)
    {
      if (f_mount(&USBDISKFatFs, "", 0)!= FR_OK)
      {
        USBH_UsrLog("ERROR : Cannot Initialize FatFs! \n");
      }
    }
    break;

  default:
  break;
  }
  /* USER CODE END CALL_BACK_1 */
}

/**
  * @}
  */

/**
  * @}
  */

