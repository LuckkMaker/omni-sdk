/**
  * @file    startup_stm32h750xx.c
  * @author  LuckkMaker
  * @brief   CMSIS-Core(M) Device Startup File for STM32H750xx Devices
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

#include "stm32h7xx.h"

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
__NO_RETURN void PVD_AVD_IRQHandler                 (void) __attribute__ ((weak, alias("Default_Handler")));
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
__NO_RETURN void ADC1_IRQHandler                    (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void FDCAN1_IT0_IRQHandler              (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void FDCAN2_IT0_IRQHandler              (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void FDCAN1_IT1_IRQHandler              (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void FDCAN2_IT1_IRQHandler              (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void EXTI9_5_IRQHandler                 (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void TIM1_BRK_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void TIM1_UP_IRQHandler                 (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void TIM1_TRG_COM_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
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
__NO_RETURN void USART3_IRQHandler                  (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void EXTI15_10_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void RTC_Alarm_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void TIM8_BRK_TIM12_IRQHandler          (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void TIM8_UP_TIM13_IRQHandler           (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void TIM8_TRG_COM_TIM14_IRQHandler      (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void TIM8_CC_IRQHandler                 (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void DMA1_Stream7_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void FMC_IRQHandler                     (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void SDMMC1_IRQHandler                  (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void TIM5_IRQHandler                    (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void SPI3_IRQHandler                    (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void UART4_IRQHandler                   (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void UART5_IRQHandler                   (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void TIM6_DAC_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void TIM7_IRQHandler                    (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void DMA2_Stream0_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void DMA2_Stream1_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void DMA2_Stream2_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void DMA2_Stream3_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void DMA2_Stream4_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void ETH_IRQHandler                     (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void ETH_WKUP_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void FDCAN_CAL_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void DMA2_Stream5_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void DMA2_Stream6_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void DMA2_Stream7_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void USART6_IRQHandler                  (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void I2C3_EV_IRQHandler                 (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void I2C3_ER_IRQHandler                 (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void OTG_HS_EP1_OUT_IRQHandler          (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void OTG_HS_EP1_IN_IRQHandler           (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void OTG_HS_WKUP_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void OTG_HS_IRQHandler                  (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void DCMI_IRQHandler                    (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void CRYP_IRQHandler                    (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void HASH_RNG_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void FPU_IRQHandler                     (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void UART7_IRQHandler                   (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void UART8_IRQHandler                   (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void SPI4_IRQHandler                    (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void SPI5_IRQHandler                    (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void SPI6_IRQHandler                    (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void SAI1_IRQHandler                    (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void LTDC_IRQHandler                    (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void LTDC_ER_IRQHandler                 (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void DMA2D_IRQHandler                   (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void SAI2_IRQHandler                    (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void QUADSPI_IRQHandler                 (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void LPTIM1_IRQHandler                  (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void CEC_IRQHandler                     (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void I2C4_EV_IRQHandler                 (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void I2C4_ER_IRQHandler                 (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void SPDIF_RX_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void OTG_FS_EP1_OUT_IRQHandler          (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void OTG_FS_EP1_IN_IRQHandler           (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void OTG_FS_WKUP_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void OTG_FS_IRQHandler                  (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void DMAMUX1_OVR_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void HRTIM1_Master_IRQHandler           (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void HRTIM1_TIMA_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void HRTIM1_TIMB_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void HRTIM1_TIMC_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void HRTIM1_TIMD_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void HRTIM1_TIME_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void HRTIM1_FLT_IRQHandler              (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void DFSDM1_FLT0_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void DFSDM1_FLT1_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void DFSDM1_FLT2_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void DFSDM1_FLT3_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void SAI3_IRQHandler                    (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void SWPMI1_IRQHandler                  (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void TIM15_IRQHandler                   (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void TIM16_IRQHandler                   (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void TIM17_IRQHandler                   (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void MDIOS_WKUP_IRQHandler              (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void MDIOS_IRQHandler                   (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void JPEG_IRQHandler                    (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void MDMA_IRQHandler                    (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void SDMMC2_IRQHandler                  (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void HSEM1_IRQHandler                   (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void ADC3_IRQHandler                    (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void DMAMUX2_OVR_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void BDMA_Channel0_IRQHandler           (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void BDMA_Channel1_IRQHandler           (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void BDMA_Channel2_IRQHandler           (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void BDMA_Channel3_IRQHandler           (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void BDMA_Channel4_IRQHandler           (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void BDMA_Channel5_IRQHandler           (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void BDMA_Channel6_IRQHandler           (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void BDMA_Channel7_IRQHandler           (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void COMP1_IRQHandler                   (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void LPTIM2_IRQHandler                  (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void LPTIM3_IRQHandler                  (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void LPTIM4_IRQHandler                  (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void LPTIM5_IRQHandler                  (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void LPUART1_IRQHandler                 (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void CRS_IRQHandler                     (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void ECC_IRQHandler                     (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void SAI4_IRQHandler                    (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void WAKEUP_PIN_IRQHandler              (void) __attribute__ ((weak, alias("Default_Handler")));

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
    PVD_AVD_IRQHandler,                  /* 1  PVD/AVD */
    TAMP_STAMP_IRQHandler,               /* 2  Tamper and TimeStamp */
    RTC_WKUP_IRQHandler,                 /* 3  RTC Wakeup */
    FLASH_IRQHandler,                    /* 4  Flash */
    RCC_IRQHandler,                      /* 5  RCC */
    EXTI0_IRQHandler,                    /* 6  EXTI Line 0 */
    EXTI1_IRQHandler,                    /* 7  EXTI Line 1 */
    EXTI2_IRQHandler,                    /* 8  EXTI Line 2 */
    EXTI3_IRQHandler,                    /* 9  EXTI Line 3 */
    EXTI4_IRQHandler,                    /* 10 EXTI Line 4 */
    DMA1_Stream0_IRQHandler,             /* 11 DMA1 Stream 0 */
    DMA1_Stream1_IRQHandler,             /* 12 DMA1 Stream 1 */
    DMA1_Stream2_IRQHandler,             /* 13 DMA1 Stream 2 */
    DMA1_Stream3_IRQHandler,             /* 14 DMA1 Stream 3 */
    DMA1_Stream4_IRQHandler,             /* 15 DMA1 Stream 4 */
    DMA1_Stream5_IRQHandler,             /* 16 DMA1 Stream 5 */
    DMA1_Stream6_IRQHandler,             /* 17 DMA1 Stream 6 */
    ADC1_IRQHandler,                     /* 18 ADC1, ADC2 and ADC3 */
    FDCAN1_IT0_IRQHandler,               /* 19 FDCAN1_IT0 */
    FDCAN2_IT0_IRQHandler,               /* 20 FDCAN2_IT0 */
    FDCAN1_IT1_IRQHandler,               /* 21 FDCAN1_IT1 */
    FDCAN2_IT1_IRQHandler,               /* 22 FDCAN2_IT1 */
    EXTI9_5_IRQHandler,                  /* 23 EXTI Line 9 to 5 */
    TIM1_BRK_IRQHandler,                 /* 24 TIM1 Break */
    TIM1_UP_IRQHandler,                  /* 25 TIM1 Update */
    TIM1_TRG_COM_IRQHandler,             /* 26 TIM1 Trigger and Commutation */
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
    USART3_IRQHandler,                   /* 39 USART3 */
    EXTI15_10_IRQHandler,                /* 40 EXTI Line[15:10]s */
    RTC_Alarm_IRQHandler,                /* 41 RTC Alarm (A and B) through EXTI Line */
    0,                                   /* 42 Reserved */
    TIM8_BRK_TIM12_IRQHandler,           /* 43 TIM8 Break and TIM12 */
    TIM8_UP_TIM13_IRQHandler,            /* 44 TIM8 Update and TIM13 */
    TIM8_TRG_COM_TIM14_IRQHandler,       /* 45 TIM8 Trigger and Commutation and TIM14 */
    TIM8_CC_IRQHandler,                  /* 46 TIM8 Capture Compare */
    DMA1_Stream7_IRQHandler,             /* 47 DMA1 Stream7 */
    FMC_IRQHandler,                      /* 48 FMC */
    SDMMC1_IRQHandler,                   /* 49 SDMMC1 */
    TIM5_IRQHandler,                     /* 50 TIM5 */
    SPI3_IRQHandler,                     /* 51 SPI3 */
    UART4_IRQHandler,                    /* 52 UART4 */
    UART5_IRQHandler,                    /* 53 UART5 */
    TIM6_DAC_IRQHandler,                 /* 54 TIM6 and DAC1&2 underrun errors */
    TIM7_IRQHandler,                     /* 55 TIM7 */
    DMA2_Stream0_IRQHandler,             /* 56 DMA2 Stream 0 */
    DMA2_Stream1_IRQHandler,             /* 57 DMA2 Stream 1 */
    DMA2_Stream2_IRQHandler,             /* 58 DMA2 Stream 2 */
    DMA2_Stream3_IRQHandler,             /* 59 DMA2 Stream 3 */
    DMA2_Stream4_IRQHandler,             /* 60 DMA2 Stream 4 */
    ETH_IRQHandler,                      /* 61 Ethernet */
    ETH_WKUP_IRQHandler,                 /* 62 Ethernet Wakeup through EXTI line */
    FDCAN_CAL_IRQHandler,                /* 63 FDCAN Calibration unit */
    0,                                   /* 64 Reserved */
    0,                                   /* 65 Reserved */
    0,                                   /* 66 Reserved */
    0,                                   /* 67 Reserved */
    DMA2_Stream5_IRQHandler,             /* 68 DMA2 Stream 5 */
    DMA2_Stream6_IRQHandler,             /* 69 DMA2 Stream 6 */
    DMA2_Stream7_IRQHandler,             /* 70 DMA2 Stream 7 */
    USART6_IRQHandler,                   /* 71 USART6 */
    I2C3_EV_IRQHandler,                  /* 72 I2C3 event */
    I2C3_ER_IRQHandler,                  /* 73 I2C3 error */
    OTG_HS_EP1_OUT_IRQHandler,           /* 74 USB OTG HS End Point 1 Out */
    OTG_HS_EP1_IN_IRQHandler,            /* 75 USB OTG HS End Point 1 In */
    OTG_HS_WKUP_IRQHandler,              /* 76 USB OTG HS Wakeup through EXTI */
    OTG_HS_IRQHandler,                   /* 77 USB OTG HS */
    DCMI_IRQHandler,                     /* 78 DCMI */
    CRYP_IRQHandler,                     /* 79 CRYP crypto */
    HASH_RNG_IRQHandler,                 /* 80 Hash and Rng */
    FPU_IRQHandler,                      /* 81 FPU */
    UART7_IRQHandler,                    /* 82 UART7 */
    UART8_IRQHandler,                    /* 83 UART8 */
    SPI4_IRQHandler,                     /* 84 SPI4 */
    SPI5_IRQHandler,                     /* 85 SPI5 */
    SPI6_IRQHandler,                     /* 86 SPI6 */
    SAI1_IRQHandler,                     /* 87 SAI1 */
    LTDC_IRQHandler,                     /* 88 LTDC */
    LTDC_ER_IRQHandler,                  /* 89 LTDC error */
    DMA2D_IRQHandler,                    /* 90 DMA2D */
    SAI2_IRQHandler,                     /* 91 SAI2 */
    QUADSPI_IRQHandler,                  /* 92 QuadSPI */
    LPTIM1_IRQHandler,                   /* 93 LP Timer1 */
    CEC_IRQHandler,                      /* 94 HDMI CEC */
    I2C4_EV_IRQHandler,                  /* 95 I2C4 Event */
    I2C4_ER_IRQHandler,                  /* 96 I2C4 Error */
    SPDIF_RX_IRQHandler,                 /* 97 SPDIF RX */
    OTG_FS_EP1_OUT_IRQHandler,           /* 98 USB OTG FS End Point 1 Out */
    OTG_FS_EP1_IN_IRQHandler,            /* 99 USB OTG FS End Point 1 In */
    OTG_FS_WKUP_IRQHandler,              /* 100 USB OTG FS Wakeup through EXTI */
    OTG_FS_IRQHandler,                   /* 101 USB OTG FS */
    DMAMUX1_OVR_IRQHandler,              /* 102 DMAMUX1 overrun */
    HRTIM1_Master_IRQHandler,            /* 103 HRTIM Master Timer */
    HRTIM1_TIMA_IRQHandler,              /* 104 HRTIM Timer A */
    HRTIM1_TIMB_IRQHandler,              /* 105 HRTIM Timer B */
    HRTIM1_TIMC_IRQHandler,              /* 106 HRTIM Timer C */
    HRTIM1_TIMD_IRQHandler,              /* 107 HRTIM Timer D */
    HRTIM1_TIME_IRQHandler,              /* 108 HRTIM Timer E */
    HRTIM1_FLT_IRQHandler,               /* 109 HRTIM Fault */
    DFSDM1_FLT0_IRQHandler,              /* 110 DFSDM Filter 0 */
    DFSDM1_FLT1_IRQHandler,              /* 111 DFSDM Filter 1 */
    DFSDM1_FLT2_IRQHandler,              /* 112 DFSDM Filter 2 */
    DFSDM1_FLT3_IRQHandler,              /* 113 DFSDM Filter 3 */
    SAI3_IRQHandler,                     /* 114 SAI3 */
    SWPMI1_IRQHandler,                   /* 115 SWPMI1 */
    TIM15_IRQHandler,                    /* 116 Timer 15 */
    TIM16_IRQHandler,                    /* 117 Timer 16 */
    TIM17_IRQHandler,                    /* 118 Timer 17 */
    MDIOS_WKUP_IRQHandler,               /* 119 MDIOS Wakeup */
    MDIOS_IRQHandler,                    /* 120 MDIOS */
    JPEG_IRQHandler,                     /* 121 JPEG */
    MDMA_IRQHandler,                     /* 122 MDMA */
    0,                                   /* 123 Reserved */
    SDMMC2_IRQHandler,                   /* 124 SDMMC2 */
    HSEM1_IRQHandler,                    /* 125 HSEM1 */
    0,                                   /* 126 Reserved */
    ADC3_IRQHandler,                     /* 127 ADC3 */
    DMAMUX2_OVR_IRQHandler,              /* 128 DMAMUX2 overrun */
    BDMA_Channel0_IRQHandler,            /* 129 BDMA Channel 0 */
    BDMA_Channel1_IRQHandler,            /* 130 BDMA Channel 1 */
    BDMA_Channel2_IRQHandler,            /* 131 BDMA Channel 2 */
    BDMA_Channel3_IRQHandler,            /* 132 BDMA Channel 3 */
    BDMA_Channel4_IRQHandler,            /* 133 BDMA Channel 4 */
    BDMA_Channel5_IRQHandler,            /* 134 BDMA Channel 5 */
    BDMA_Channel6_IRQHandler,            /* 135 BDMA Channel 6 */
    BDMA_Channel7_IRQHandler,            /* 136 BDMA Channel 7 */
    COMP1_IRQHandler,                    /* 137 COMP1 */
    LPTIM2_IRQHandler,                   /* 138 LP Timer 2 */
    LPTIM3_IRQHandler,                   /* 139 LP Timer 3 */
    LPTIM4_IRQHandler,                   /* 140 LP Timer 4 */
    LPTIM5_IRQHandler,                   /* 141 LP Timer 5 */
    LPUART1_IRQHandler,                  /* 142 LP UART1 */
    0,                                   /* 143 Reserved */
    CRS_IRQHandler,                      /* 144 CRS */
    ECC_IRQHandler,                      /* 145 ECC */
    SAI4_IRQHandler,                     /* 146 SAI4 */
    0,                                   /* 147 Reserved */
    0,                                   /* 148 Reserved */
    WAKEUP_PIN_IRQHandler,               /* 149 Wakeup Pin */
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
