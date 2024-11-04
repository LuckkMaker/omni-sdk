/**
  * @file    startup_apm32f407xx.c
  * @author  LuckkMaker
  * @brief   CMSIS-Core(M) Device Startup File for APM32F407xx Devices
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

#include "apm32f4xx.h"
#include "drivers/init.h"

/*---------------------------------------------------------------------------
  External References
 *---------------------------------------------------------------------------*/
extern uint32_t _end_stack;
extern uint32_t _start_address_data;
extern uint32_t _end_address_data;
extern uint32_t _start_address_init_data;
extern uint32_t _start_address_bss;
extern uint32_t _end_address_bss;

extern void __libc_init_array(void);
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
__NO_RETURN void WWDT_IRQHandler                    (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void PVD_IRQHandler                     (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void TAMP_STAMP_IRQHandler              (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void RTC_WKUP_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void FLASH_IRQHandler                   (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void RCM_IRQHandler                     (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void EINT0_IRQHandler                   (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void EINT1_IRQHandler                   (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void EINT2_IRQHandler                   (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void EINT3_IRQHandler                   (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void EINT4_IRQHandler                   (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void DMA1_STR0_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void DMA1_STR1_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void DMA1_STR2_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void DMA1_STR3_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void DMA1_STR4_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void DMA1_STR5_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void DMA1_STR6_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void ADC_IRQHandler                     (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void CAN1_TX_IRQHandler                 (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void CAN1_RX0_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void CAN1_RX1_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void CAN1_SCE_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void EINT9_5_IRQHandler                 (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void TMR1_BRK_TMR9_IRQHandler           (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void TMR1_UP_TMR10_IRQHandler           (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void TMR1_TRG_COM_TMR11_IRQHandler      (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void TMR1_CC_IRQHandler                 (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void TMR2_IRQHandler                    (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void TMR3_IRQHandler                    (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void TMR4_IRQHandler                    (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void I2C1_EV_IRQHandler                 (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void I2C1_ER_IRQHandler                 (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void I2C2_EV_IRQHandler                 (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void I2C2_ER_IRQHandler                 (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void SPI1_IRQHandler                    (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void SPI2_IRQHandler                    (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void USART1_IRQHandler                  (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void USART2_IRQHandler                  (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void USART3_IRQHandler                  (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void EINT15_10_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void RTC_Alarm_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void OTG_FS_WKUP_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void TMR8_BRK_TMR12_IRQHandler          (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void TMR8_UP_TMR13_IRQHandler           (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void TMR8_TRG_COM_TMR14_IRQHandler      (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void TMR8_CC_IRQHandler                 (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void DMA1_STR7_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void EMMC_IRQHandler                    (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void SDIO_IRQHandler                    (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void TMR5_IRQHandler                    (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void SPI3_IRQHandler                    (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void UART4_IRQHandler                   (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void UART5_IRQHandler                   (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void TMR6_DAC_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void TMR7_IRQHandler                    (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void DMA2_STR0_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void DMA2_STR1_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void DMA2_STR2_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void DMA2_STR3_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void DMA2_STR4_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void ETH_IRQHandler                     (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void ETH_WKUP_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void CAN2_TX_IRQHandler                 (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void CAN2_RX0_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void CAN2_RX1_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void CAN2_SCE_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void OTG_FS_IRQHandler                  (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void DMA2_STR5_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void DMA2_STR6_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void DMA2_STR7_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void USART6_IRQHandler                  (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void I2C3_EV_IRQHandler                 (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void I2C3_ER_IRQHandler                 (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void OTG_HS1_EP1_OUT_IRQHandler         (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void OTG_HS1_EP1_IN_IRQHandler          (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void OTG_HS1_WKUP_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void OTG_HS1_IRQHandler                 (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void DCI_IRQHandler                     (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void HASH_RNG_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void FPU_IRQHandler                     (void) __attribute__ ((weak, alias("Default_Handler")));

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
    (VECTOR_TABLE_Type)(&_end_stack),       /*     Initial Stack Pointer */
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
    WWDT_IRQHandler,                     /* 0  Window Watchdog Timer */
    PVD_IRQHandler,                      /* 1  Power Voltage Detector */
    TAMP_STAMP_IRQHandler,               /* 2  Tamper and TimeStamp */
    RTC_WKUP_IRQHandler,                 /* 3  RTC Wakeup */
    FLASH_IRQHandler,                    /* 4  Flash */
    RCM_IRQHandler,                      /* 5  Reset Clock Management */
    EINT0_IRQHandler,                    /* 6  External Interrupt 0 */
    EINT1_IRQHandler,                    /* 7  External Interrupt 1 */
    EINT2_IRQHandler,                    /* 8  External Interrupt 2 */
    EINT3_IRQHandler,                    /* 9  External Interrupt 3 */
    EINT4_IRQHandler,                    /* 10 External Interrupt 4 */
    DMA1_STR0_IRQHandler,                /* 11 DMA1 Stream 0 */
    DMA1_STR1_IRQHandler,                /* 12 DMA1 Stream 1 */
    DMA1_STR2_IRQHandler,                /* 13 DMA1 Stream 2 */
    DMA1_STR3_IRQHandler,                /* 14 DMA1 Stream 3 */
    DMA1_STR4_IRQHandler,                /* 15 DMA1 Stream 4 */
    DMA1_STR5_IRQHandler,                /* 16 DMA1 Stream 5 */
    DMA1_STR6_IRQHandler,                /* 17 DMA1 Stream 6 */
    ADC_IRQHandler,                      /* 18 ADC1, ADC2 and ADC3 */
    CAN1_TX_IRQHandler,                  /* 19 CAN1 TX */
    CAN1_RX0_IRQHandler,                 /* 20 CAN1 RX0 */
    CAN1_RX1_IRQHandler,                 /* 21 CAN1 RX1 */
    CAN1_SCE_IRQHandler,                 /* 22 CAN1 SCE */
    EINT9_5_IRQHandler,                  /* 23 External Interrupt 9 to 5 */
    TMR1_BRK_TMR9_IRQHandler,            /* 24 Timer 1 Break and Timer 9 */
    TMR1_UP_TMR10_IRQHandler,            /* 25 Timer 1 Update and Timer 10 */
    TMR1_TRG_COM_TMR11_IRQHandler,       /* 26 Timer 1 Trigger and Commutation and Timer 11 */
    TMR1_CC_IRQHandler,                  /* 27 Timer 1 Capture Compare */
    TMR2_IRQHandler,                     /* 28 Timer 2 */
    TMR3_IRQHandler,                     /* 29 Timer 3 */
    TMR4_IRQHandler,                     /* 30 Timer 4 */
    I2C1_EV_IRQHandler,                  /* 31 I2C1 Event */
    I2C1_ER_IRQHandler,                  /* 32 I2C1 Error */
    I2C2_EV_IRQHandler,                  /* 33 I2C2 Event */
    I2C2_ER_IRQHandler,                  /* 34 I2C2 Error */
    SPI1_IRQHandler,                     /* 35 SPI1 */
    SPI2_IRQHandler,                     /* 36 SPI2 */
    USART1_IRQHandler,                   /* 37 USART1 */
    USART2_IRQHandler,                   /* 38 USART2 */
    USART3_IRQHandler,                   /* 39 USART3 */
    EINT15_10_IRQHandler,                /* 40 External Interrupt 15 to 10 */
    RTC_Alarm_IRQHandler,                /* 41 RTC Alarm (A and B) through EXTI Line */
    OTG_FS_WKUP_IRQHandler,              /* 42 USB OTG FS Wakeup */
    TMR8_BRK_TMR12_IRQHandler,           /* 43 Timer 8 Break and Timer 12 */
    TMR8_UP_TMR13_IRQHandler,            /* 44 Timer 8 Update and Timer 13 */
    TMR8_TRG_COM_TMR14_IRQHandler,       /* 45 Timer 8 Trigger and Commutation and Timer 14 */
    TMR8_CC_IRQHandler,                  /* 46 Timer 8 Capture Compare */
    DMA1_STR7_IRQHandler,                /* 47 DMA1 Stream 7 */
    EMMC_IRQHandler,                     /* 48 EMMC */
    SDIO_IRQHandler,                     /* 49 SDIO */
    TMR5_IRQHandler,                     /* 50 Timer 5 */
    SPI3_IRQHandler,                     /* 51 SPI3 */
    UART4_IRQHandler,                    /* 52 UART4 */
    UART5_IRQHandler,                    /* 53 UART5 */
    TMR6_DAC_IRQHandler,                 /* 54 Timer 6 and DAC */
    TMR7_IRQHandler,                     /* 55 Timer 7 */
    DMA2_STR0_IRQHandler,                /* 56 DMA2 Stream 0 */
    DMA2_STR1_IRQHandler,                /* 57 DMA2 Stream 1 */
    DMA2_STR2_IRQHandler,                /* 58 DMA2 Stream 2 */
    DMA2_STR3_IRQHandler,                /* 59 DMA2 Stream 3 */
    DMA2_STR4_IRQHandler,                /* 60 DMA2 Stream 4 */
    ETH_IRQHandler,                      /* 61 Ethernet */
    ETH_WKUP_IRQHandler,                 /* 62 Ethernet Wakeup */
    CAN2_TX_IRQHandler,                  /* 63 CAN2 TX */
    CAN2_RX0_IRQHandler,                 /* 64 CAN2 RX0 */
    CAN2_RX1_IRQHandler,                 /* 65 CAN2 RX1 */
    CAN2_SCE_IRQHandler,                 /* 66 CAN2 SCE */
    OTG_FS_IRQHandler,                   /* 67 USB OTG FS */
    DMA2_STR5_IRQHandler,                /* 68 DMA2 Stream 5 */
    DMA2_STR6_IRQHandler,                /* 69 DMA2 Stream 6 */
    DMA2_STR7_IRQHandler,                /* 70 DMA2 Stream 7 */
    USART6_IRQHandler,                   /* 71 USART6 */
    I2C3_EV_IRQHandler,                  /* 72 I2C3 Event */
    I2C3_ER_IRQHandler,                  /* 73 I2C3 Error */
    OTG_HS1_EP1_OUT_IRQHandler,          /* 74 USB OTG HS End Point 1 Out */
    OTG_HS1_EP1_IN_IRQHandler,           /* 75 USB OTG HS End Point 1 In */
    OTG_HS1_WKUP_IRQHandler,             /* 76 USB OTG HS Wakeup */
    OTG_HS1_IRQHandler,                  /* 77 USB OTG HS */
    DCI_IRQHandler,                      /* 78 DCI */
    0,                                   /* 79 Reserved */
    HASH_RNG_IRQHandler,                 /* 80 HASH and RNG */
    FPU_IRQHandler,                      /* 81 FPU */
};

#if defined ( __GNUC__ )
#pragma GCC diagnostic pop
#endif

/*---------------------------------------------------------------------------
  Reset Handler called on controller reset
 *---------------------------------------------------------------------------*/
__NO_RETURN void Reset_Handler(void)
{
    __set_MSP((uint32_t)(&_end_stack));

    /* Copy the data segment initializers from flash to SRAM */
    uint32_t src = (uint32_t) &_start_address_init_data;
    uint32_t dest = (uint32_t) &_start_address_data;
    if (src != dest) {
        for (; dest < (uint32_t) &_end_address_data;) {
            *(uint32_t *) dest = *(uint32_t *) src;
            src += 4;
            dest += 4;
        }
    }

    /* Zero fill the bss segment */
    for (dest = (uint32_t) &_start_address_bss; dest < (uint32_t) &_end_address_bss;) {
        *(uint32_t *) dest = 0;
        dest += 4;
    }

    SystemInit();                    /* CMSIS System Initialization */

    __libc_init_array();             /* Initialize C Library */

#if defined(CONFIG_OMNI_DRIVER)
    driver_init();                   /* Initialize drivers */
#endif /* CONFIG_OMNI_DRIVER */

    main();                          /* Enter main */

    HardFault_Handler();             /* main() shouldn't return */

    while(1);                        /* Avoid compiler warning */
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
