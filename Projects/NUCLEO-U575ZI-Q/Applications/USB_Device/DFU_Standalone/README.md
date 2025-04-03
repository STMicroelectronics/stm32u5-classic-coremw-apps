## <b>DFU_Standalone Application Description</b>

Compliant implementation of the Device Firmware Upgrade (DFU)
capability to program the embedded Flash memory through the USB peripheral.

At the beginning of the main program the HAL_Init() function is called to reset all the peripherals,
initialize the Flash interface and the systick. The user is provided with the SystemClock_Config()
function to configure the system clock (SYSCLK) to run at 160 MHz.
The high speed OTG IP in full speed mode (FS) uses
internally a 48-MHz clock, which is generated from HSI48.
The DFU transactions are based on Endpoint 0 (control endpoint) transfer. All requests and status
control are sent/received through this endpoint.

The Internal flash memory is split as follows:
 - DFU area located in [0x08000000 : USBD_DFU_APP_DEFAULT_ADD-1]: Only read access
 - Application area located in [USBD_DFU_APP_DEFAULT_ADD : Device's end address]: Read, Write, and Erase
   access

In this application, two operating modes are available:
 1. DFU operating mode:
    This mode is entered after an MCU reset in case:
     - The DFU mode is forced by the user: the user presses the USER push-button.
     - No valid code found in the application area: a code is considered valid if the MSB of the initial
       Main Stack Pointer (MSP) value located in the first address of the application area is equal to
       0x20000

 2. Run-time application mode:
    This is the normal run-time activities. A binary which toggles LEDs on the NUCLEO-U575ZI-Q board is
    provided in Binary directory.

#### <b>Expected success behavior</b>

When plugged to PC host, the NUCLEO-U575ZI-Q must be properly enumerated as an USB DFU device.
During the enumeration phase, device provides host with the requested descriptors (device, configuration, string).
Those descriptors are used by host driver to identify the device capabilities.
Once the NUCLEO-U575ZI-Q USB device successfully completed the enumeration phase, open STM32CubeProgrammer you can now download and upload to/from media .

#### <b>Error behaviors</b>

  - LED_RED is toggling to indicate a critical error has occured.
  - Host PC shows that USB device does not appear as DFU device.

#### <b>Assumptions if any</b>

User is familiar with USB 2.0 "Universal Serial BUS" specification and DFU class specification.

#### <b>Known limitations</b>

None

#### Notes

 1. After each device reset (unplug the NUCLEO-U575ZI-Q board from PC), Plug the NUCLEO-U575ZI-Q board with Key USER push-button button
pressed to enter the DFU mode.

   Please refer to UM0412, DFuSe USB device firmware upgrade STMicroelectronics extension for more details
on the driver installation and PC host user interface.

 2. A binary HID_Standalone on the NUCLEO-U575ZI-Q board is provided in Binary directory.

 3. The application needs to ensure that the SysTick time base is set to 1 millisecond
      to have correct HAL configuration.

 4. Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.

 5. The built-in USB peripheral of the stm32u5xx does not provide a specific interrupt for USB cable plug/unplug
      detection. The correct way to detect the USB cable plug/unplug is to detect the availability of the VBUS line
      using a normal GPIO pin (external interrupt line).

### USB Library Configuration

It is possible to fine tune needed USB Device features by modifying defines values in USBD configuration
file usbd_conf.h available under the project includes directory, in a way to fit the application
requirements, such as:
 - USBD_DFU_APP_DEFAULT_ADD, specifying the address from where user's application will be downloaded.

Device's end address is the end address of the flash memory and it is dependent on the device in use.

### Keywords

Connectivity, USB_Device, USB, DFU, Firmware upgrade

### Directory contents

  - USB_Device/DFU_Standalone/Core/Src/main.c                           Main program
  - USB_Device/DFU_Standalone/Core/Src/system_stm32u5xx.c               stm32u5xx system clock configuration file
  - USB_Device/DFU_Standalone/Core/Src/stm32u5xx_it.c                   Interrupt handlers
  - USB_Device/DFU_Standalone/USB_Device/App/usb_device.c               USB Device application code
  - USB_Device/DFU_Standalone/USB_Device/App/usb_desc.c                 USB device descriptor
  - USB_Device/DFU_Standalone/USB_Device/App/usbd_dfu_flash.c           Internal flash memory management
  - USB_Device/DFU_Standalone/USB_Device/Target/usbd_conf.c             General low level driver configuration
  - USB_Device/DFU_Standalone/Core/Inc/main.h                           Main program header file
  - USB_Device/DFU_Standalone/Core/Inc/stm32u5xx_it.h                   Interrupt handlers header file
  - USB_Device/DFU_Standalone/Core/Inc/stm32u5xx_hal_conf.h             HAL configuration file
  - USB_Device/DFU_Standalone/USB_Device/App/usb_device.h               USB Device application header file
  - USB_Device/DFU_Standalone/USB_Device/App/usbd_desc.h                USB device descriptor header file
  - USB_Device/DFU_Standalone/USB_Device/App/usbd_dfu_flash.h           Internal flash memory management header file
  - USB_Device/DFU_Standalone/USB_Device/Target/usbd_conf.h             USB device driver Configuration file

### Hardware and Software environment

  - This application runs on STM32U575xx devices.

  - This application has been tested with STMicroelectronics NUCLEO-U575ZI-Q
    board MB1549 Rev. C01 and can be easily tailored to any other supported device
    and development board.

  - NUCLEO-U575ZI-Q board Set-up
    - Connect the NUCLEO-U575ZI-Q board to the PC.
    - Connect the NUCLEO-U575ZI-Q board to the PC through Type-C to standard A Male cable connected to the connector.
     -    to use USB Full Speed (FS)

### How to use it ?

In order to make the program work, you must do the following:
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - To run the application, proceed as follows:
    - Download the appropriate STM32CubeProgrammer from ST web site and install it.
    - Once you've updated the STM32 DFU device driver you must verify from Windows Device Manager
      that DFU driver is selected with the STM32CubeProgrammer driver.
    - Open "STM32CubeProgrammer", select the usb interface and connect to DFU device.
    - Download the "NUCLEO-U575ZI-Q_GPIO_IOToggle_@0x08020000.bin" provided in Binary directory and set the start address.
    - To run the downloaded application, reset the board.