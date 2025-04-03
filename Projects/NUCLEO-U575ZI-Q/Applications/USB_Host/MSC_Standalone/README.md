#### <b>MSC_Standalone Application Description</b>

This application is a part of the USB Host Library package using STM32Cube firmware. It describes how to use
USB host application based on the Mass Storage Class (MSC) on the STM32U5xx devices.

This is a typical application on how to use the STM32U5xx USB OTG Host peripheral to operate with an USB
flash disk using the Bulk Only Transfer (BOT) and Small Computer System Interface (SCSI) transparent
commands combined with a file system FatFs (Middleware component).

At the beginning of the main program the HAL_Init() function is called to reset
all the peripherals, initialize the Flash interface and the systick.
The SystemClock_Config() function is used to configure the system clock for STM32U575xx Devices :
The CPU at 160MHz

The High speed OTG IP in full speed mode
USB module uses internally a 48-MHz clock which is coming from HSE with MCO from STLINK-V3E as clock input.

####  <b>Expected success behavior</b>

When a USB flash disk is plugged to NUCLEO-U575ZI-Q board, a message will be displayed on the UART HyperTerminal showing the Vendor ID and the Product ID of the attached device.
After enumeration phase, the host proceeds to file operations :

  - Create a "USBHost.txt" file.
  - Write a small text in the created file.
  - Read the written text and check data integrity.
  - Close the File.
  - Display the whole USB flash disk content (recursion level 2).

During the file operations process, a message will be displayed on the HyperTerminal to indicate the outcome of each operation (create/write/read/close).
If all operations were successful, a message will be displayed on the HyperTerminal to indicate the end of operations.

#### <b>Error behaviors</b>

  - Errors are detected (such as unsupported device, enumeration fail, file operations fail) and the corresponding message is displayed on the HyperTerminal.
  - LED_RED is toggling to indicate a critical error has occured.

#### <b>Assumptions if any</b>

User is familiar with USB 2.0 "Universal Serial BUS" specification and mass storage class specification.

#### <b>Known limitations</b>

None

#### <b>Notes</b>

 1. Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.

 2. The application needs to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

For more details about the STM32Cube USB Host library, please refer to UM1720
"STM32Cube USB Host library".


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

### <b>Keywords</b>

Connectivity, USB_Host, USB, FatFs, File system, MSC, Mass Storage, BOT, SCSI, Removable drive, Write, Read, Format

### <b>Directory contents</b>

   - USB_Host/MSC_Standalone/USB_Host/Target/usbh_conf.c           General low level driver configuration
   - USB_Host/MSC_Standalone/USB_Host/Target/usbh_conf.h           USB Host driver Configuration file
   - USB_Host/MSC_Standalone/USB_Host/App/explorer.c               Explore the USB flash disk content
   - USB_Host/MSC_Standalone/USB_Host/App/file_operations.c        Write/read file on the disk
   - USB_Host/MSC_Standalone/USB_Host/App/usbh_diskio.c            USB diskio interface for FatFs
   - USB_Host/MSC_Standalone/USB_Host/App/host.c                   MSC State Machine
   - USB_Host/MSC_Standalone/Core/Src/main.c                       Main program
   - USB_Host/MSC_Standalone/Core/Src/system_stm32u5xx.c           STM32U5xx system clock configuration file
   - USB_Host/MSC_Standalone/Core/Src/stm32u5xx_it.c               Interrupt handlers
   - USB_Host/MSC_Standalone/Core/Src/stm32u5xx_hal_msp.c          HAL MSP Module
   - USB_Host/MSC_Standalone/Core/Inc/main.h                       Main program header file
   - USB_Host/MSC_Standalone/Core/Inc/stm32u5xx_it.h               Interrupt handlers header file
   - USB_Host/MSC_Standalone/Core/Inc/stm32u5xx_hal_conf.h         HAL configuration file
   - USB_Host/MSC_Standalone/Core/Inc/ffconf.h                     FatFs Module Configuration file

### <b>Hardware and Software environment</b>

  - This application runs on STM32U575xx devices.

  - This application has been tested with STMicroelectronics NUCLEO-U575ZI-Q
    boards MB1549 Rev. C01 and can be easily tailored to any other supported device
    and development board.

  - NUCLEO-U575ZI-Q Set-up
    - To use the HSE clock with MCO from STLINK-V3E as an input, the following configuration is needed:
      • SB47 OFF and SB49 ON. Only PH1 can be connected to CN11 as an I/O.
      • SB48 ON. MCO is connected to PH0 and R5 on the STLINK-V3E side and must be connected to provide the MCO to the STLINK-V3E output.
      • SB4 and SB5 OFF. The external crystal is not connected to HSE.

    - Plug the USB key into the NUCLEO-U575ZI-Q board through 'USB Type C-Male
      to A-Female' cable to the connector:
      -  CN15: to use USB Full Speed (FS)
               Please ensure that jumper JP6 is fitted in 5V_USB_C position.

    - Nucleo board is sink only,this host example is only for reference and the user should provide a 5V for Vbus.


  -Connect ST-Link cable to the PC USB port to display data on the HyperTerminal.
    A virtual COM port will then appear in the HyperTerminal:

     - Hyperterminal configuration:
      - Data Length = 8 Bits
      - One Stop Bit
      - No parity
      - BaudRate = 115200 baud
      - Flow control: None

### <b>How to use it ?</b>

In order to make the program work, you must do the following :
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Open the configured uart hyperterminal in order to display debug messages.
 - Run the application
 - Open the configured uart hyperterminal in order to display debug messages.

#### <b>Notes</b>

   The user has to check the list of the COM ports in Device Manager to find out the number of the
   COM ports that have been assigned (by OS) to the Stlink VCP .