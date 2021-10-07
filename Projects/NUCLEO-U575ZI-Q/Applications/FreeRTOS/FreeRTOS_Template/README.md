## FreeRTOS_Template Application Description

This project provides a reference template based on the STM32Cube HAL API that can be used
to build any firmware application using FreeRTOS.

This application creates a thread that toggle LED1 every 200 ms.

#### Notes
 1. Care must be taken when using HAL_Delay(), this function provides accurate
      delay (in milliseconds) based on variable incremented in HAL time base ISR.  
      This implies that if HAL_Delay() is called from a peripheral ISR process, then
      the HAL time base interrupt must have higher priority (numerically lower) than
      the peripheral interrupt. Otherwise the caller ISR process will be blocked.  
      To change the HAL time base interrupt priority you have to use HAL_NVIC_SetPriority()
      function.  
      
The template project calls also CACHE_Enable() function in order to enable the Instruction
and Data Caches. This function is provided as template implementation that the User may
integrate in his application in order to enhance the performance.  
      
This project is targeted to run on STM32U575xx devices on NUCLEO-U575ZI-Q boards from STMicroelectronics.  

 2. The application needs to ensure that the HAL time base is always set to 1 millisecond
      to have correct HAL operation.

 3. The FreeRTOS heap size configTOTAL_HEAP_SIZE defined in FreeRTOSConfig.h is set accordingly to the
      OS resources memory requirements of the application with +10% margin and rounded to the upper Kbyte boundary.

For more details about FreeRTOS implementation on STM32Cube, please refer to UM1722 "Developing Applications
on STM32Cube with RTOS".

### Keywords

RTOS, FreeRTOS, Thread

### Directory contents 

    - FreeRTOS/FreeRTOS_Template/Src/main.c                       Main program
    - FreeRTOS/FreeRTOS_Template/Src/stm32u5xx_hal_timebase_tim.c HAL timebase file
    - FreeRTOS/FreeRTOS_Template/Src/stm32u5xx_it.c               Interrupt handlers
    - FreeRTOS/FreeRTOS_Template/Src/system_stm32u5xx.c           STM32U5xx system clock configuration file
    - FreeRTOS/FreeRTOS_Template/Inc/main.h                       Main program header file
    - FreeRTOS/FreeRTOS_Template/Inc/stm32u5xx_hal_conf.h         HAL Library Configuration file
    - FreeRTOS/FreeRTOS_Template/Inc/stm32u5xx_it.h               Interrupt handlers header file
    - FreeRTOS/FreeRTOS_Template/Inc/FreeRTOSConfig.h             FreeRTOS Configuration file
    - FreeRTOS/FreeRTOS_Template/Inc/stm32u5xx_nucleo_conf.h      BSP configuration file

### Hardware and Software environment  

  - This application runs on STM32U575xx devices.  

  - This application has been tested with NUCLEO-U575ZI-Q board and can be
    easily tailored to any other supported device and development board.  


### How to use it ? 

In order to make the program work, you must do the following :  
 - Open your preferred toolchain   
 - Rebuild all files and load your image into target memory  
 - Run the example  

