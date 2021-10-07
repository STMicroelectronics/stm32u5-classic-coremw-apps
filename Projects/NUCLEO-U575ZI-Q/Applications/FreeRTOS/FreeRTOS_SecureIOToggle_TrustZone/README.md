## FreeRTOS_SecureIOToggle_TrustZone Application Description

How to use FreeRTOS when the TrustZone feature is enabled (TZEN=1).

The purpose of this application is to declare a secure IO with HAL GPIO and to toggle it
every 200ms using a non-secure FreeRTOS task via a non-secure callable API provided by
the secure application.   All other IOs are released to non-secure application.

The secure IO is PC.07 which corresponds to LED1 and the non-secure application switches on
the non-secure IO PB.07 which corresponds to LED2 when an error occurs.

This project is composed of two sub-projects:  
- one for the secure application part (Project_s)  
- one for the non-secure application part (Project_ns).  

Please remember that on system with security enabled, the system always boots in secure and
the secure application is responsible for launching the non-secure application.

This project mainly shows how to switch from secure application to non-secure application
thanks to the system isolation performed to split the internal Flash and internal SRAM memories
into two halves:  
 - the first half for the secure application and  
 - the second half for the non-secure application.  

User Option Bytes configuration:  
Please note the internal Flash is fully secure by default in TZEN=1 and User Option Bytes
SECWM1_PSTRT/SECWM1_PEND and SECWM2_PSTRT/SECWM2_PEND should be set according to the application
configuration.   Here the proper User Option Bytes setup in line with the project linker/scatter
file is as follows:  
    TZEN=1  
    DBANK=1  
    SECWM1_PSTRT=0x0  SECWM1_PEND=0x7F  meaning all 128 pages of Bank1 set as secure  
    SECWM2_PSTRT=0x1  SECWM2_PEND=0x0   meaning no page of Bank2 set as secure, hence Bank2 non-secure  

This project is targeted to run on STM32U575xx device on NUCLEO-U575ZI-Q boards from STMicroelectronics.  

This example configures the maximum system clock frequency at 160Mhz.  

#### Notes
 1. Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt.   Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
	  

### Keywords


Security, RTOS, FreeRTOS, TrustZone, Thread, GPIO, toggle


### Directory contents
  - Secure/Src/main.c                            Secure Main program
  - Secure/Src/secure_nsc.c                      Secure Non-secure callable functions
  - Secure/Src/stm32U5xx_hal_msp.c               Secure HAL MSP module
  - Secure/Src/stm32U5xx_it.c                    Secure Interrupt handlers
  - Secure/Src/system_stm32U5xx_s.c              Secure STM32U5xx system clock configuration file
  - Secure/Inc/main.h                            Secure Main program header file
  - Secure/Inc/partition_stm32U575xx.h           STM32U5 Device System Configuration file
  - Secure/Inc/stm32U5xx_hal_conf.h              Secure HAL Configuration file
  - Secure/Inc/stm32U5xx_it.h                    Secure Interrupt handlers header file
  - Secure_nsclib/secure_nsc.h                   Secure Non-Secure Callable (NSC) module header file
  - NonSecure/Src/main.c                         Non-secure Main program
  - NonSecure/Src/stm32u5xx_hal_msp.c            Non-secure HAL MSP module
  - NonSecure/Src/stm32U5xx_hal_timebase_tim.c   Non-secure HAL TimeBase module
  - NonSecure/Src/stm32U5xx_it.c                 Non-secure Interrupt handlers
  - NonSecure/Src/system_stm32U5xx_ns.c          Non-secure STM32U5xx system clock configuration file
  - NonSecure/Inc/main.h                         Non-secure Main program header file
  - NonSecure/Inc/stm32U5xx_hal_conf.h           Non-secure HAL Configuration file
  - NonSecure/Inc/stm32U5xx_it.h                 Non-secure Interrupt handlers header file
  - Common/FreeRTOSConfig.h                      FreeRTOS configuration file


### Hardware and Software environment  

  - This example runs on STM32U575xx devices with security enabled (TZEN=1).    

  - This example has been tested with STMicroelectronics NUCLEO-U575ZI-Q  
    board and can be easily tailored to any other supported device  
    and development board.    

  - User Option Bytes requirement (with STM32CubeProgrammer tool)  
     TZEN = 1                          System with TrustZone-M enabled  
     DBANK = 1                         Dual bank mode  
     SECWM1_PSTRT=0x0  SECWM1_PEND=0x7F  All 128 pages of internal Flash Bank1 set as secure  
     SECWM2_PSTRT=0x1  SECWM2_PEND=0x0   No page of internal Flash Bank2 set as secure, hence Bank2 non-secure  


### How to use it ?

In order to make the program work, you must do the following :  

 - Make sure that the system is configured with the security enable (TZEN=1) (option byte)  

IAR  
 - Open your toolchain  
 - Open Multi-projects workspace file Project.eww  
 - Set the "FreeRTOS_SecureIOToggle_TrustZone_S" as active application (Set as Active)  
 - Rebuild FreeRTOS_SecureIOToggle_TrustZone_S project  
 - Rebuild FreeRTOS_SecureIOToggle_TrustZone_NS project  
 - Load the secure and non-secures images into target memory (Ctrl + D)  
 - Run the example