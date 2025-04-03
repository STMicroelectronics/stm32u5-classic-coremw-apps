## HID_Standalone Application Description

This application is a part of the USB Host Library package using STM32Cube firmware. It describes how to use
USB host application based on the Human Interface Class (HID) on the STM32U575xx devices.

This is a typical application on how to use the STM32U575AIIxQ USB OTG Host peripheral to interact with an USB
HID Device such as a Mouse or a Keyboard.

At the beginning of the main program the HAL_Init() function is called to reset
all the peripherals, initialize the Flash interface and the systick.
The SystemClock_Config() function is used to configure the system clock for STM32U575xx Devices :
The CPU at 160MHz

The High speed OTG IP in full speed mode USB module uses internally a 48-MHz clock which is coming from HSE with MCO from STLINK-V3E as clock input.

#### <b>Expected success behavior</b>

When a HID device is plugged to NUCLEO-U575ZI-Q board, a message will be displayed on the UART HyperTerminal showing
the Vendor ID and Product ID of the attached device.
After enumeration phase, a message will indicate that the device is ready for use.
The host must be able to properly decode HID reports sent by the corresponding device and display those information on the HyperTerminal.

The received HID reports are used by host to identify:
- in case of a mouse
   - (x,y) mouse position
   - Wheel position
   - Pressed mouse buttons

- in case of a keyboard
   - Pressed key

#### <b>Error behaviors</b>

  - Errors are detected (such as unsupported device, enumeration fail) and the corresponding message is displayed on the HyperTerminal.
  - LED_RED is toggling to indicate a critical error has occured.

#### <b>Assumptions if any</b>

User is familiar with USB 2.0 "Universal Serial BUS" specification and HID class specification.

#### <b>Known limitations</b>

None

#### Notes

 1. Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.

 2. The application needs to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.


For more details about the STM32Cube USB Host library, please refer to UM1720
"STM32Cube USB Host library".

-  2. In case of using an AZERTY keyboard, user should add "AZERTY_KEYBOARD" define to ensure correct
displaying taped characters.

It is possible to fine tune needed USB Host features by modifying defines values in USBH configuration
file “usbh_conf.h” available under the project includes directory, in a way to fit the application
requirements, such as:
- Level of debug: USBH_DEBUG_LEVEL
                  0: No debug messages
                  1: Only User messages are shown
                  2: User and Error messages are shown
                  3: All messages and internal debug messages are shown
   By default debug messages are displayed on the debugger IO terminal; to redirect the Library
   messages to uart terminal, stm32u5xx_hal_uart.c driver needs to be added to the application sources.
   Debug messages are displayed on the uart terminal using ST-Link.


### Keywords

Connectivity, USB_Host, USB, HID, Human Interface, Mouse, Keyboard

### Directory contents

  - USB_Host/HID_Standalone/Core/Src/main.c                         Main program
  - USB_Host/HID_Standalone/Core/Src/system_stm32u5xx.c             STM32U5xx system clock configuration File
  - USB_Host/HID_Standalone/Core/Src/stm32u5xx_it.c                 Interrupt handlers
  - USB_Host/HIS_Standalone/Core/Src/stm32u5xx_hal_msp.c            HAL MSP Module
  - USB_Host/HID_Standalone/Core/Inc/main.h                         Main program header File
  - USB_Host/HID_Standalone/Core/Inc/stm32u5xx_hal_conf.h           HAL configuration File
  - USB_Host/HID_Standalone/Core/Inc/stm32u5xx_it.h                 Interrupt handlers header File
  - USB_Host/HID_Standalone/USB_Host/App/usb_host.c                 HID State Machine
  - USB_Host/HID_Standalone/USB_Host/App/mouse.c                    HID mouse functions File
  - USB_Host/HID_Standalone/USB_Host/App/keyboard.c                 HID keyboard functions File
  - USB_Host/HID_Standalone/USB_Host/App/usb_host.h                 HID State Machine Header File
  - USB_Host/HID_Standalone/USB_Host/App/mouse.h                    HID mouse functions Header File
  - USB_Host/HID_Standalone/USB_Host/App/keyboard.h                 HID keyboard functions Header File
  - USB_Host/HID_Standalone/USB_Host/Target/usbh_conf.c             General low level driver configuration
  - USB_Host/HID_Standalone/USB_Host/Target/usbh_conf.h             USB Host driver configuration File

### Hardware and Software environment

  - This application runs on STM32U575xx devices.

  - This application has been tested with STMicroelectronics NUCLEO-U575ZI-Q boards MB1549 Rev. C01 with hardware modifications
    detailed below and can be easily tailored to any other supported device and development board.

  - NUCLEO-U575ZI-Q Set-up
    - To use the HSE clock with MCO from STLINK-V3E as an input, the following configuration is needed:
      • SB47 OFF and SB49 ON. Only PH1 can be connected to CN11 as an I/O.
      • SB48 ON. MCO is connected to PH0 and R5 on the STLINK-V3E side and must be connected to provide the MCO to the STLINK-V3E output.
      • SB4 and SB5 OFF. The external crystal is not connected to HSE.

    - USB Host application project can run correctly on NUCLEO-U575ZI-Q only after some hardware modifications:
       - Connect an external HSE clock circuitry on PH0 and PH1, to ensure HSE as source clock. Detailed schematic information can be found in this  [document](https://www.st.com/en/evaluation-tools/nucleo-u575zi-q.html)
       - Add external circuitry allowing to provide Vbus (5V) source controlled by a GPIO from STM32U5 device (for example STMPS2141STR following the example of this [board](https://www.st.com/resource/en/schematic_pack/mb1364-h743zi-c01_schematic.pdf) in sheet 7.
    - Plug the USB key into the NUCLEO-U575ZI-Q board through 'USB Type-C
      to A-Female' cable to the connector:
      - CN15: to use USB Full Speed (FS)
               Please ensure that jumper JP6 is fitted in 5V_USB_C position.

      - Connect ST-Link cable to the PC USB port to display data on the HyperTerminal.
    A virtual COM port will then appear in the HyperTerminal:

     - Hyperterminal configuration:
      - Data Length = 8 Bits
      - One Stop Bit
      - No parity
      - BaudRate = 115200 baud
      - Flow control: None

    - Nucleo board is sink only,this host example is only for reference and the user should provide a 5V for Vbus.

### How to use it ?

In order to make the program work, you must do the following :
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Open the configured uart hyperterminal in order to display debug messages.
 - Run the application
 - Open the configured uart hyperterminal in order to display debug messages.

#### Notes

   The user has to check the list of the COM ports in Device Manager to find out the number of the
   COM ports that have been assigned (by OS) to the Stlink VCP.