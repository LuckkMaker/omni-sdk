/**
  * @file    startup_stm32f411xx.c
  * @author  LuckkMaker
  * @brief   CMSIS-Core(M) Device Startup File for STM32F411xx Devices
  * @attention
  *
  * Copyright (c) 2024 LuckkMaker
  * All rights reserved.
  *
  * Licensed under the Apache License, Version 2.0 (the "License");
  * you may not use this file except in compliance with the License.
  * You may obtain a copy of the License at
  *
  *     http://www.apache.org/licenses/LICENSE-2.0
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  */

#include "stm32f4xx.h"

/*---------------------------------------------------------------------------
  External References
 *---------------------------------------------------------------------------*/
#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
extern uint32_t __INITIAL_SP;
extern __NO_RETURN void __PROGRAM_START(void);
#else
extern uint32_t _estack;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sidata;
extern uint32_t _sbss;
extern uint32_t _ebss;

extern void __libc_init_array(void);
#endif /* defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050) */
extern int main(void);
/*---------------------------------------------------------------------------
  Internal References
 *---------------------------------------------------------------------------*/
__NO_RETURN void Reset_Handler  (void);
__NO_RETURN void Default_Handler(void);

/*---------------------------------------------------------------------------
  Exception / Interrupt Handler
 *---------------------------------------------------------------------------*/
/* Exceptions */
__NO_RETURN void NMI_Handler            (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void HardFault_Handler      (void) __attribute__ ((weak));
__NO_RETURN void MemManage_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void BusFault_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void UsageFault_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void SVC_Handler            (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void DebugMon_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void PendSV_Handler         (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void SysTick_Handler        (void) __attribute__ ((weak, alias("Default_Handler")));

/* Interrupts */
__NO_RETURN void WWDG_IRQHandler                    (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void PVD_IRQHandler                     (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void TAMP_STAMP_IRQHandler              (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void RTC_WKUP_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void FLASH_IRQHandler                   (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void RCC_IRQHandler                     (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void EXTI0_IRQHandler                   (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void EXTI1_IRQHandler                   (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void EXTI2_IRQHandler                   (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void EXTI3_IRQHandler                   (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void EXTI4_IRQHandler                   (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void DMA1_Stream0_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void DMA1_Stream1_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void DMA1_Stream2_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void DMA1_Stream3_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void DMA1_Stream4_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void DMA1_Stream5_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void DMA1_Stream6_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void ADC_IRQHandler                     (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void EXTI9_5_IRQHandler                 (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void TIM1_BRK_TIM9_IRQHandler           (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void TIM1_UP_TIM10_IRQHandler           (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void TIM1_TRG_COM_TIM11_IRQHandler      (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void TIM1_CC_IRQHandler                 (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void TIM2_IRQHandler                    (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void TIM3_IRQHandler                    (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void TIM4_IRQHandler                    (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void I2C1_EV_IRQHandler                 (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void I2C1_ER_IRQHandler                 (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void I2C2_EV_IRQHandler                 (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void I2C2_ER_IRQHandler                 (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void SPI1_IRQHandler                    (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void SPI2_IRQHandler                    (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void USART1_IRQHandler                  (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void USART2_IRQHandler                  (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void EXTI15_10_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void RTC_Alarm_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void OTG_FS_WKUP_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void DMA1_Stream7_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void SDIO_IRQHandler                    (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void TIM5_IRQHandler                    (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void SPI3_IRQHandler                    (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void DMA2_Stream0_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void DMA2_Stream1_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void DMA2_Stream2_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void DMA2_Stream3_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void DMA2_Stream4_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void OTG_FS_IRQHandler                  (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void DMA2_Stream5_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void DMA2_Stream6_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void DMA2_Stream7_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void USART6_IRQHandler                  (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void I2C3_EV_IRQHandler                 (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void I2C3_ER_IRQHandler                 (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void FPU_IRQHandler                     (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void SPI4_IRQHandler                    (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void SPI5_IRQHandler                    (void) __attribute__ ((weak, alias("Default_Handler")));

/*----------------------------------------------------------------------------
  Exception / Interrupt Vector table
 *----------------------------------------------------------------------------*/

#if defined ( __GNUC__ )
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#endif

// Note: The vector table is need a name of .vectors and placed in the linker script SECTIONS(CMSIS 6)
extern const VECTOR_TABLE_Type __VECTOR_TABLE[];
       const VECTOR_TABLE_Type __VECTOR_TABLE[] __VECTOR_TABLE_ATTRIBUTE = {
#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
    (VECTOR_TABLE_Type)(&__INITIAL_SP),  /*     Initial Stack Pointer */
#else
    (VECTOR_TABLE_Type)(&_estack),       /*     Initial Stack Pointer */
#endif
    Reset_Handler,                       /*     Reset Handler */
    NMI_Handler,                         /* -14 NMI Handler */
    HardFault_Handler,                   /* -13 Hard Fault Handler */
    MemManage_Handler,                   /* -12 MPU Fault Handler */
    BusFault_Handler,                    /* -11 Bus Fault Handler */
    UsageFault_Handler,                  /* -10 Usage Fault Handler */
    0,                                   /*     Reserved */
    0,                                   /*     Reserved */
    0,                                   /*     Reserved */
    0,                                   /*     Reserved */
    SVC_Handler,                         /*  -5 SVCall Handler */
    DebugMon_Handler,                    /*  -4 Debug Monitor Handler */
    0,                                   /*     Reserved */
    PendSV_Handler,                      /*  -2 PendSV Handler */
    SysTick_Handler,                     /*  -1 SysTick Handler */

    /* Interrupts */
    WWDG_IRQHandler,                     /* 0  Window WatchDog */
    PVD_IRQHandler,                      /* 1  PVD through EXTI Line detection */
    TAMP_STAMP_IRQHandler,               /* 2  Tamper and TimeStamps through the EXTI line */
    RTC_WKUP_IRQHandler,                 /* 3  RTC Wakeup through the EXTI line */
    FLASH_IRQHandler,                    /* 4  FLASH */
    RCC_IRQHandler,                      /* 5  RCC */
    EXTI0_IRQHandler,                    /* 6  EXTI Line0 */
    EXTI1_IRQHandler,                    /* 7  EXTI Line1 */
    EXTI2_IRQHandler,                    /* 8  EXTI Line2 */
    EXTI3_IRQHandler,                    /* 9  EXTI Line3 */
    EXTI4_IRQHandler,                    /* 10 EXTI Line4 */
    DMA1_Stream0_IRQHandler,             /* 11 DMA1 Stream 0 */
    DMA1_Stream1_IRQHandler,             /* 12 DMA1 Stream 1 */
    DMA1_Stream2_IRQHandler,             /* 13 DMA1 Stream 2 */
    DMA1_Stream3_IRQHandler,             /* 14 DMA1 Stream 3 */
    DMA1_Stream4_IRQHandler,             /* 15 DMA1 Stream 4 */
    DMA1_Stream5_IRQHandler,             /* 16 DMA1 Stream 5 */
    DMA1_Stream6_IRQHandler,             /* 17 DMA1 Stream 6 */
    ADC_IRQHandler,                      /* 18 ADC1, ADC2 and ADC3s */
    0,                                   /* 19 Reserved */
    0,                                   /* 20 Reserved */
    0,                                   /* 21 Reserved */
    0,                                   /* 22 Reserved */
    EXTI9_5_IRQHandler,                  /* 23 EXTI Line[9:5]s */
    TIM1_BRK_TIM9_IRQHandler,            /* 24 TIM1 Break and TIM9 */
    TIM1_UP_TIM10_IRQHandler,            /* 25 TIM1 Update and TIM10 */
    TIM1_TRG_COM_TIM11_IRQHandler,       /* 26 TIM1 Trigger and Commutation and TIM11 */
    TIM1_CC_IRQHandler,                  /* 27 TIM1 Capture Compare */
    TIM2_IRQHandler,                     /* 28 TIM2 */
    TIM3_IRQHandler,                     /* 29 TIM3 */
    TIM4_IRQHandler,                     /* 30 TIM4 */
    I2C1_EV_IRQHandler,                  /* 31 I2C1 Event */
    I2C1_ER_IRQHandler,                  /* 32 I2C1 Error */
    I2C2_EV_IRQHandler,                  /* 33 I2C2 Event */
    I2C2_ER_IRQHandler,                  /* 34 I2C2 Error */
    SPI1_IRQHandler,                     /* 35 SPI1 */
    SPI2_IRQHandler,                     /* 36 SPI2 */
    USART1_IRQHandler,                   /* 37 USART1 */
    USART2_IRQHandler,                   /* 38 USART2 */
    0,                                   /* 39 Reserved */
    EXTI15_10_IRQHandler,                /* 40 EXTI Line[15:10]s */
    RTC_Alarm_IRQHandler,                /* 41 RTC Alarm (A and B) through EXTI Line */
    OTG_FS_WKUP_IRQHandler,              /* 42 USB OTG FS Wakeup through EXTI line */
    0,                                   /* 43 Reserved */
    0,                                   /* 44 Reserved */
    0,                                   /* 45 Reserved */
    0,                                   /* 46 Reserved */
    DMA1_Stream7_IRQHandler,             /* 47 DMA1 Stream7 */
    0,                                   /* 48 Reserved */
    SDIO_IRQHandler,                     /* 49 SDIO */
    TIM5_IRQHandler,                     /* 50 TIM5 */
    SPI3_IRQHandler,                     /* 51 SPI3 */
    0,                                   /* 52 Reserved */
    0,                                   /* 53 Reserved */
    0,                                   /* 54 Reserved */
    0,                                   /* 55 Reserved */
    DMA2_Stream0_IRQHandler,             /* 56 DMA2 Stream 0 */
    DMA2_Stream1_IRQHandler,             /* 57 DMA2 Stream 1 */
    DMA2_Stream2_IRQHandler,             /* 58 DMA2 Stream 2 */
    DMA2_Stream3_IRQHandler,             /* 59 DMA2 Stream 3 */
    DMA2_Stream4_IRQHandler,             /* 60 DMA2 Stream 4 */
    0,                                   /* 61 Reserved */
    0,                                   /* 62 Reserved */
    0,                                   /* 63 Reserved */
    0,                                   /* 64 Reserved */
    0,                                   /* 65 Reserved */
    0,                                   /* 66 Reserved */
    OTG_FS_IRQHandler,                   /* 67 USB OTG FS */
    DMA2_Stream5_IRQHandler,             /* 68 DMA2 Stream 5 */
    DMA2_Stream6_IRQHandler,             /* 69 DMA2 Stream 6 */
    DMA2_Stream7_IRQHandler,             /* 70 DMA2 Stream 7 */
    USART6_IRQHandler,                   /* 71 USART6 */
    I2C3_EV_IRQHandler,                  /* 72 I2C3 event */
    I2C3_ER_IRQHandler,                  /* 73 I2C3 error */
    0,                                   /* 74 Reserved */
    0,                                   /* 75 Reserved */
    0,                                   /* 76 Reserved */
    0,                                   /* 77 Reserved */
    0,                                   /* 78 Reserved */
    0,                                   /* 79 Reserved */
    0,                                   /* 80 Reserved */
    FPU_IRQHandler,                      /* 81 FPU */
    0,                                   /* 82 Reserved */
    0,                                   /* 83 Reserved */
    SPI4_IRQHandler,                     /* 84 SPI4 */
    SPI5_IRQHandler,                     /* 85 SPI5 */
};

#if defined ( __GNUC__ )
#pragma GCC diagnostic pop
#endif

/*---------------------------------------------------------------------------
  Reset Handler called on controller reset
 *---------------------------------------------------------------------------*/
__NO_RETURN void Reset_Handler(void)
{
#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
    __set_PSP((uint32_t)(&__INITIAL_SP));

    SystemInit();                    /* CMSIS System Initialization */

    __PROGRAM_START();               /* Enter PreMain (C library entry point) */
#else
    __set_MSP((uint32_t)(&_estack));

    /* Copy the data segment initializers from flash to SRAM */
    uint32_t src = (uint32_t) &_sidata;
    uint32_t dest = (uint32_t) &_sdata;
    if (src != dest) {
        for (; dest < (uint32_t) &_edata;) {
            *(uint32_t *) dest = *(uint32_t *) src;
            src += 4;
            dest += 4;
        }
    }

    /* Zero fill the bss segment */
    for (dest = (uint32_t) &_sbss; dest < (uint32_t) &_ebss;) {
        *(uint32_t *) dest = 0;
        dest += 4;
    }

    SystemInit();                    /* CMSIS System Initialization */

    __libc_init_array();             /* Initialize C Library */

    main();                          /* Enter main */

    HardFault_Handler();             /* main() shouldn't return */

    while(1);                        /* Avoid compiler warning */
#endif /* defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050) */
}

#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wmissing-noreturn"
#endif

/*---------------------------------------------------------------------------
  Hard Fault Handler
 *---------------------------------------------------------------------------*/
void HardFault_Handler(void)
{
    while(1);
}

/*---------------------------------------------------------------------------
  Default Handler for Exceptions / Interrupts
 *---------------------------------------------------------------------------*/
void Default_Handler(void)
{
    // Get the vector number
    uint32_t vector = __get_IPSR();
    vector -= 16;

    while(1);
}

#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #pragma clang diagnostic pop
#endif
