# STM32U5 Classic Core Middleware (CoreMW) MCU Firmware Package

![latest tag](https://img.shields.io/github/v/tag/STMicroelectronics/stm32u5-classic-coremw-apps.svg?color=brightgreen)

![freertos](https://img.shields.io/badge/freertos-v10.3.1-blue.svg) ![usb_device](https://img.shields.io/badge/usb_device-v2.7.1-blue.svg) ![usb_host](https://img.shields.io/badge/usb_host-v3.3.5-blue.svg)

## Description

**STM32Cube** is an STMicroelectronics original initiative to ease developers' life by reducing efforts, time and cost.

**Classic CoreMW** is a collection of middleware stacks and associated applications allowing RTOS management, File System operations and connectivity through USB and Ethernet. It is based on:
* ST's proprietary stacks: ST USB Device and ST USB Host
* Third parties' stacks: FreeRTOS

This package is **exclusively** published on GitHub (and is neither available in STM32CubeU5, STM32CubeMX nor STM32CubeIDE available on www.st.com). 
It contains the integration of the Classic CoreMW stacks with STM32U5 devices, allowing users to get quick access to pre-built projects integrating them.

#### *Note*

 * The repository containing this package has been created using the `git submodule` command. Please refer to the ["How to use"](README.md#how-to-use) section explaining how to clone this repository and how to get the latest updates.

## List of applications

The **STM32U5 Classic CoreMW** package contains the following applications:

Middleware    | Application                        | Short Description
--------------|------------------------------------|------------------------------------------------------------------------
FreeRTOS      | FreeRTOS_SecureIOToggle_TrustZone  | Shows how to use FreeRTOS when the TrustZone feature is enabled (TZEN=1)
FreeRTOS      | FreeRTOS_StopMode                  | Shows how to enter and exit low-power mode with CMSIS-RTOS API v2
FreeRTOS      | FreeRTOS_Template                  | Provides a reference template based on the STM32Cube HAL API that can be used to build any firmware application using FreeRTOS
ST USB Device | CDC_Standalone                     | Shows how to use USB device application based on the Device Communication Class (CDC) following the PSTN subprotocol
ST USB Device | HID_Standalone                     | Shows a typical application where the STM32 MCU is enumerated as a HID device
ST USB Host   | HID_Standalone                     | Shows how to use USB host application based on the Human Interface Class (HID) to connect a mouse or a keyboard

#### *Note*

 * Only *FreeRTOS_Template* application is provided with preconfigured projects for *Keil MDK-ARM* and *STM32CubeIDE* toolchains. All others are provided **only** with preconfigured projects for *EWARM* toolchain.
 * Projects in this package have not been generated with STM32CubeMX (**i.e.**, no `.ioc` files are delivered).

## Boards available

 * STM32U5
   * [NUCLEO-U575ZI-Q](https://www.st.com/en/evaluation-tools/nucleo-u575zi-q.html)

## Development Toolchains and Compilers

 * IAR Embedded Workbench for ARM (EWARM) toolchain **V8.50.6** + ST-LINK, patch available [here](https://github.com/STMicroelectronics/STM32CubeU5/tree/main/Utilities/PC_Software/IDEs_Patches/EWARM)
   * This patch supports STM32U575/585 devices
 * RealView Microcontroller Development Kit (MDK-ARM) toolchain **V5.32** + ST-LINK, patch available [here](https://github.com/STMicroelectronics/STM32CubeU5/tree/main/Utilities/PC_Software/IDEs_Patches/MDK-ARM):
   * This patch supports STM32U575/585 devices
 * STM32CubeIDE **v1.7.0**

## Dependencies

This package has been developed and tested using the list of components detailed in the table below.

Name                       |   Version
---------------------------|---------------
Cortex-M CMSIS             |   V5.6.0_cm33
STM32U5xx CMSIS            |   V1.0.0
STM32U5xx HAL              |   V1.0.0
BSP STM32U5xx NUCLEO       |   V1.0.0
BSP Common                 |   V7.1.0
BSP mfxstm32l152           |   V3.0.3
FreeRTOS                   |   V10.3.1 (ST_Tag_31-August-2020)
STM32 USB Device Library   |   V2.7.1
STM32 USB Host Library     |   V3.3.5
STM32 USBPD Core Library   |   V4.0.0
STM32 USBPD Device Library |   u5_v3.0.0

## How to use

This repository intrinsically contains the applications (projects and source files) located under folder `./Projects`. It also contains the CMSIS Core files under folder `./Drivers/CMSIS/Include` for size optimization reason. Other dependencies such as the HAL and BSP drivers, or the middleware libraries themselves are linked using the `git submodule` command. Please check the instructions below for a proper use.

---

#### *Note*

 * USB-PD library is momentarily contained in this repository pending its publication on GitHub. Once published, it will be added as a submodule like the other components.

---

* To clone this repository along with the linked submodules, option `--recursive` has to be specified as shown below.

```
git clone --recursive https://github.com/STMicroelectronics/stm32u5-classic-coremw-apps.git
```

* To get the latest updates, issue the following **two** commands (with the repository `stm32u5-classic-coremw-apps` as the **current working directory**).

```
git pull
git submodule update --init --recursive
```

#### *Note*

 * If GitHub "Download ZIP" option is used instead of the `git clone` command, then the required components have to be collected manually by the user.

## Known Limitations

 * USB Host application project can run correctly on NUCLEO-U575ZI-Q only after some hardware modifications:
   * Connect an external HSE clock circuitry on PH0 and PH1, to ensure HSE as source clock. Detailed schematic information can be found in this [document](https://www.st.com/en/evaluation-tools/nucleo-u575zi-q.html)
   * Add external circuitry allowing to provide Vbus (5V) source controlled by a GPIO from STM32U5 device (for example STMPS2141STR following the example of this [board](https://www.st.com/resource/en/schematic_pack/mb1364-h743zi-c01_schematic.pdf) in sheet 7).

## Troubleshooting

Please refer to the [CONTRIBUTING.md](CONTRIBUTING.md) guide.
