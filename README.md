# STM32U5 Classic Core Middleware (CoreMW) MCU Firmware Package

![latest tag](https://img.shields.io/github/v/tag/STMicroelectronics/stm32u5-classic-coremw-apps.svg?color=brightgreen)

![freertos](https://img.shields.io/badge/freertos-v10.6.2-blue.svg) ![fatfs](https://img.shields.io/badge/fatfs-v0.15-blue.svg) ![usb_device](https://img.shields.io/badge/usb_device-v2.11.3-blue.svg) ![usb_host](https://img.shields.io/badge/usb_host-v3.5.3-blue.svg)

## Description

**STM32Cube** is an STMicroelectronics original initiative to ease developers' life by reducing efforts, time and cost.

**Classic CoreMW** is a collection of middleware stacks and associated applications allowing RTOS management, File System operations and connectivity through USB and Ethernet. It is based on:
* ST's proprietary stacks: ST USB Device and ST USB Host
* Third parties' stacks: FreeRTOS and FatFS

This package is **exclusively** published on GitHub (and is neither available in STM32CubeU5, STM32CubeMX nor STM32CubeIDE available on www.st.com).
It contains the integration of the Classic CoreMW stacks with STM32U5 devices, allowing users to get quick access to pre-built projects integrating them.

#### *Note*

 * The repository containing this package has been created using the `git submodule` command. Please refer to the ["How to use"](README.md#how-to-use) section explaining how to clone this repository and how to get the latest updates.

## List of applications

The **STM32U5 Classic CoreMW** package contains the following applications:

Middleware    | Application                        | Short Description
--------------|------------------------------------|------------------------------------------------------------------------
FatFs         | FatFs_RAMDISK_Standalone           | Shows a typical application where the STM32 MCU write and read back a Fat Format text file from RAMDISK
ST USB Device | CDC_Standalone                     | Shows how to use USB device application based on the Device Communication Class (CDC) following the PSTN
ST USB Device | HID_Standalone                     | Shows a typical application where the STM32 MCU is enumerated as a HID device
ST USB Device | DFU_Standalone                     | Shows a typical application where the STM32 MCU is enumerated as a DFU device
ST USB Host   | HID_Standalone                     | Shows how to use USB host application based on the Human Interface Class (HID) to connect a mouse or a keyboard
ST USB Host   | MSC_Standalone                     | Shows how to use USB host application based on the Mass Storage Class (MSC) to communicate with a usb flash disk

#### *Note*

 * *FreeRTOS* Middleware and examples are delivered on STM32U5 in the form of X-CUBE-FREERTOS that is available from [st.com](https://www.st.com/en/embedded-software/x-cube-freertos.html), from [GitHub](https://github.com/STMicroelectronics/x-cube-freertos) and from STM32CubeMX.
 * Only *FatFs_RAMDISK_Standalone* application is provided with preconfigured projects for *EWARM*, *Keil MDK-ARM* and *STM32CubeIDE* toolchains. All others are provided **only** with preconfigured projects for *EWARM* toolchain.
 * Projects in this package have not been generated with STM32CubeMX (**i.e.**, no `.ioc` files are delivered).

## Boards available

 * STM32U5
   * [NUCLEO-U575ZI-Q](https://www.st.com/en/evaluation-tools/nucleo-u575zi-q.html)

## Development Toolchains and Compilers

 * IAR Embedded Workbench for ARM (EWARM) toolchain **V8.50.9** + ST-LINK, patch available [here](https://github.com/STMicroelectronics/STM32CubeU5/tree/main/Utilities/PC_Software/IDEs_Patches/EWARM)
   * This patch supports STM32U575/585 devices
 * RealView Microcontroller Development Kit (MDK-ARM) toolchain **V5.39** + ST-LINK, patch available [here](https://github.com/STMicroelectronics/STM32CubeU5/tree/main/Utilities/PC_Software/IDEs_Patches/MDK-ARM):
   * This patch supports STM32U575/585 devices
 * STM32CubeIDE **v1.17.0**

## Dependencies

This package has been developed and tested using the list of components detailed in the table below.

Name                       |   Version
---------------------------|---------------
Cortex-M CMSIS             |   V5.9.0
STM32U5xx CMSIS            |   V1.4.1
STM32U5xx HAL              |   V1.6.1
BSP STM32U5xx NUCLEO       |   V1.2.2
BSP Common                 |   V7.3.0
BSP mfxstm32l152           |   V4.0.1
FreeRTOS                   |   V10.6.2
FatFs                      |   R0.15
STM32 USB Device Library   |   V2.11.3
STM32 USB Host Library     |   V3.5.3

## How to use

This repository intrinsically contains the applications (projects and source files) located under folder `./Projects`. It also contains the CMSIS Core files under folder `./Drivers/CMSIS/Include` for size optimization reason. Other dependencies such as the HAL and BSP drivers, or the middleware libraries themselves are linked using the `git submodule` command. Please check the instructions below for a proper use.

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
   * Add external circuitry allowing to provide Vbus (5V) source controlled by a GPIO from STM32U5 device (for example STMPS2141STR following the example of this [board](https://www.st.com/resource/en/schematic_pack/mb1364-h743zi-c01_schematic.pdf) in sheet 7).

## Troubleshooting

Please refer to the [CONTRIBUTING.md](CONTRIBUTING.md) guide.
