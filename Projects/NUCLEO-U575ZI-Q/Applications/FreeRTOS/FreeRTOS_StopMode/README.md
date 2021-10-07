## FreeRTOS_Timers Application Description


How to enter and exit low-power mode with CMSISOS2.0 RTOS API.  

This application creates two threads.  

   + A "RxThread" that blocks on a the "osqueue" message queue to wait for data. As soon as  
     data is available in the "osqueue" the LED1 blinks.  
	 
   + A "TxThread" that waits for a semaphore. Once the semaphore is released (from LPTIM ISR),  
     the "TxThread" puts message in "osqueue".  

Blocking for a finite period allows the kernel to stop tick interrupt
and place STM32 into stop mode - the lowest-power mode possible
that allows the CPU registers and RAM to retain their state.  

In this example, non-used GPIOs are configured to analog, thus helping to reduce
the power consumption of the device.  

#### Notes  

 1. Care must be taken when using HAL_Delay(), this function provides accurate
      delay (in milliseconds) based on variable incremented in HAL time base ISR.  
      This implies that if HAL_Delay() is called from a peripheral ISR process, then
      the HAL time base interrupt must have higher priority (numerically lower) than
      the peripheral interrupt. Otherwise the caller ISR process will be blocked.  
      To change the HAL time base interrupt priority you have to use HAL_NVIC_SetPriority()
      function.  

 2. The application needs to ensure that the HAL time base is always set to 1 millisecond
      to have correct HAL operation.  

 3. The FreeRTOS heap size configTOTAL_HEAP_SIZE defined in FreeRTOSConfig.h is set accordingly to the  
      OS resources memory requirements of the application with +10% margin and rounded to the upper Kbyte boundary.  

For more details about FreeRTOS implementation on STM32Cube, please refer to UM1722 "Developing Applications  
on STM32Cube with RTOS".  

### Keywords


RTOS, FreeRTOS, Thread, Timer  

### Directory contents

    - FreeRTOS/FreeRTOS_StopMode/Src/main.c                              Main program
    - FreeRTOS/FreeRTOS_StopMode/Src/stm32u5xx_hal_timebase_tim.c  HAL timebase file
    - FreeRTOS/FreeRTOS_StopMode/Src/stm32u5xx_it.c                Interrupt handlers
    - FreeRTOS/FreeRTOS_StopMode/Src/stm32u5xx_hal_msp.c           MSP Initialization file
    - FreeRTOS/FreeRTOS_StopMode/Src/system_stm32u5xx.c            STM32U5xx system clock configuration file
    - FreeRTOS/FreeRTOS_StopMode/Inc/main.h                              Main program header file
    - FreeRTOS/FreeRTOS_StopMode/Inc/stm32u5xx_hal_conf.h          HAL Library Configuration file
    - FreeRTOS/FreeRTOS_StopMode/Inc/stm32u5xx_it.h                Interrupt handlers header file
    - FreeRTOS/FreeRTOS_StopMode/Inc/FreeRTOSConfig.h                    FreeRTOS Configuration file
    - FreeRTOS/FreeRTOS_StopMode/Inc/stm32u5xx_nucleo_conf.h           BSP configuration file

### Hardware and Software environment


  - This application runs on STM32U575xx devices.  

  - This application has been tested with NUCLEO-U575ZI-Q board and can be
    easily tailored to any other supported device and development board.


### How to use it ?


In order to make the program work, you must do the following:  
 - Open your preferred toolchain  
 - Rebuild all files and load your image into target memory  
 - Run the example  

