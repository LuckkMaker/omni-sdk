/**
  * @file    omni_device_cfg.h
  * @author  LuckkMaker
  * @brief   OMNI device configuration for STM32F1 series
  * @version 1.0.2
  * @date    23-Oct-2024
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef OMNI_DEVICE_CFG_H
#define OMNI_DEVICE_CFG_H

#ifdef __cplusplus
extern "C" {
#endif

#define CONFIG_SOC_FAMILY_STM32F1XX

// GPIO Ports
#define GPIO_PORT0          GPIOA
#define GPIO_PORT1          GPIOB
#define GPIO_PORT2          GPIOC
#define GPIO_PORT3          GPIOD
#define GPIO_PORT4          GPIOE
#define GPIO_PORT5          GPIOF
#define GPIO_PORT6          GPIOG
#define GPIO_PORT7          GPIOH
#define GPIO_PORT8          GPIOI
#define GPIO_PORT9          GPIOJ
#define GPIO_PORT10         GPIOK
#define GPIO_PORT(num)      GPIO_PORT##num

// Get PLL multiplier
#define PLL_MUL(num)        RCC_PLL_MUL##num
// Get PLL source
#define PLL_SRC0            RCC_PLLSOURCE_HSI_DIV2
#define PLL_SRC1            RCC_PLLSOURCE_HSE
#define PLL_SRC(num)        PLL_SRC##num

// OSC type
#define OSC_TYPE_HSE        RCC_OSCILLATORTYPE_HSE
#define OSC_TYPE_HSI        RCC_OSCILLATORTYPE_HSI
#define OSC_TYPE_LSE        RCC_OSCILLATORTYPE_LSE
#define OSC_TYPE_LSI        RCC_OSCILLATORTYPE_LSI

// Get SYSCLK source
#define SYSCLK_SRC0         RCC_SYSCLKSOURCE_HSI
#define SYSCLK_SRC1         RCC_SYSCLKSOURCE_HSE
#define SYSCLK_SRC2         RCC_SYSCLKSOURCE_PLLCLK
#define SYSCLK_SRC(num)     SYSCLK_SRC##num
// Get AHB prescaler
#define AHB_DIV(num)        RCC_SYSCLK_DIV##num
// Get APB1 prescaler
#define APB1_DIV(num)       RCC_HCLK_DIV##num
// Get APB2 prescaler
#define APB2_DIV(num)       RCC_HCLK_DIV##num
// Get USB source
#define USB_SRC0            RCC_USBCLKSOURCE_PLL_DIV1_5
#define USB_SRC1            RCC_USBCLKSOURCE_PLL
#define USB_SRC(num)        USB_SRC##num
// Get flash latency
#define FLASH_LATENCY(num)  FLASH_LATENCY_##num

// Get DMA instance
#define _DMA_INS(num)               DMA##num
#define DMA_INS(num)                _DMA_INS(num)
// Get DMA channel
#define _DMA_CHANNEL(num, channel)  DMA##num##_Channel##channel
#define DMA_CHANNEL(num, channel)   _DMA_CHANNEL(num, channel)
// Get DMA priority
#define DMA_PRIORITY0               DMA_PRIORITY_LOW
#define DMA_PRIORITY1               DMA_PRIORITY_MEDIUM
#define DMA_PRIORITY2               DMA_PRIORITY_HIGH
#define DMA_PRIORITY3               DMA_PRIORITY_VERY_HIGH
#define DMA_PRIORITY(num)           DMA_PRIORITY##num
// Get DMA IRQ number
#define _DMA_IRQ_NUM(num, channel)  DMA##num##_Channel##channel##_IRQn
#define DMA_IRQ_NUM(num, channel)   _DMA_IRQ_NUM(num, channel)

//-------- <<< Use Configuration Wizard in Context Menu >>> --------------------

// <h> Interrupt Configuration
//  <h> USART1 Interrupt Priority
//  <o> USART1 IRQ Priority <0-15>
#define CONFIG_USART1_IRQ_PRIO 1
//  <o> USART2 IRQ Priority <0-15>
#define CONFIG_USART2_IRQ_PRIO 1
//  <o> USART3 IRQ Priority <0-15>
#define CONFIG_USART3_IRQ_PRIO 1
//  <o> UART4 IRQ Priority <0-15>
#define CONFIG_UART4_IRQ_PRIO 1
//  <o> UART5 IRQ Priority <0-15>
#define CONFIG_UART5_IRQ_PRIO 1
//  </h>
//  <h> I2C Interrupt Priority
//  <o> I2C1 Event IRQ Priority <0-15>
#define CONFIG_I2C1_EV_IRQ_PRIO 1
//  <o> I2C1 Error IRQ Priority <0-15>
#define CONFIG_I2C1_ER_IRQ_PRIO 1
//  <o> I2C2 Event IRQ Priority <0-15>
#define CONFIG_I2C2_EV_IRQ_PRIO 1
//  <o> I2C2 Error IRQ Priority <0-15>
#define CONFIG_I2C2_ER_IRQ_PRIO 1
//  </h>
// </h>

// <h> Oscillator Configuration
//  <o> HSE State <0=>Disable <1=>Bypass <2=>Crystal
#define CONFIG_HSE_STATE 2
#if (CONFIG_HSE_STATE == 1)
#define CONFIG_HSE_BYPASS 1
#elif (CONFIG_HSE_STATE == 2)
#define CONFIG_HSE_CRYSTAL 1
#endif /* CONFIG_HSE_STATE */
//  <o> HSE Frequency <4000000-16000000>
#define CONFIG_HSE_FREQ 8000000
#define HSE_VALUE CONFIG_HSE_FREQ
//  <o> HSI State <0=>Disable <1=>Enable
#define CONFIG_HSI_STATE 0
//  <o> HSI Frequency
#define CONFIG_HSI_FREQ 8000000
#define HSI_VALUE CONFIG_HSI_FREQ
//  <o> LSE State <0=>Disable <1=>Bypass <2=>Crystal
#define CONFIG_LSE_STATE 0
#if (CONFIG_LSE_STATE == 1)
#define CONFIG_LSE_BYPASS 1
#elif (CONFIG_LSE_STATE == 2)
#define CONFIG_LSE_CRYSTAL 1
#endif /* CONFIG_LSE_STATE */
//  <o> LSE Frequency
#define CONFIG_LSE_FREQ 32768
#define LSE_VALUE CONFIG_LSE_FREQ
//  <o> LSI State <0=>Disable <1=>Enable
#define CONFIG_LSI_STATE 0
//  <o> LSI Frequency
#define CONFIG_LSI_FREQ 40000
#define LSI_VALUE CONFIG_LSI_FREQ
//  <e> PLL Configuration
//  <i> Enable PLL Configuration
#define CONFIG_PLL 1
//      <o> PLL Source <0=>HSI_DIV2 <1=>HSE
#define CONFIG_PLL_SRC PLL_SRC(1)
//      <o> PLL Multiplier <2-16>
#define CONFIG_PLL_MUL PLL_MUL(9)
//  </e>
// </h>

#if (CONFIG_HSE_STATE != 0)
#if (CONFIG_LSE_STATE != 0)
#define CONFIG_OSC_TYPE (OSC_TYPE_HSE | OSC_TYPE_LSE)
#else
#if (CONFIG_LSI_STATE != 0)
#define CONFIG_OSC_TYPE (OSC_TYPE_HSE | OSC_TYPE_LSI)
#else
#define CONFIG_OSC_TYPE OSC_TYPE_HSE
#endif /* CONFIG_LSI_STATE */
#endif /* CONFIG_LSE_STATE */
#else
#if (CONFIG_LSE_STATE != 0)
#define CONFIG_OSC_TYPE (OSC_TYPE_HSI | OSC_TYPE_LSE)
#else
#if (CONFIG_LSI_STATE != 0)
#define CONFIG_OSC_TYPE (OSC_TYPE_HSI | OSC_TYPE_LSI)
#else
#define CONFIG_OSC_TYPE OSC_TYPE_HSI
#endif /* CONFIG_LSI_STATE */
#endif /* CONFIG_LSE_STATE */
#endif /* CONFIG_HSE_STATE */

// <h> Clock Configuration
//  <o> Flash Latency <0-2>
#define CONFIG_FLASH_LATENCY FLASH_LATENCY(2)
//  <o> System Clock <1-999999999>
#define CONFIG_SYSCLK_FREQ 72000000
//  <o> System Clock Source <0=>HSI <1=>HSE <2=>PLL
#define CONFIG_SYSCLK_SRC SYSCLK_SRC(2)
//  <o> AHB Prescaler <1=>1 <2=>2 <4=>4 <8=>8 <16=>16 <64=>64 <128=>128 <256=>256 <512=>512
#define CONFIG_AHB_PRESC AHB_DIV(1)
//  <o> APB1 Prescaler <1=>1 <2=>2 <4=>4 <8=>8 <16=>16
#define CONFIG_APB1_PRESC APB1_DIV(2)
//  <o> APB2 Prescaler <1=>1 <2=>2 <4=>4 <8=>8 <16=>16
#define CONFIG_APB2_PRESC APB2_DIV(1)
//  <o> USB Clock Source <0=>PLL_DIV1_5 <1=>PLL
#define CONFIG_USBCLK_SRC USB_SRC(0)
// </h>

// <h> USART (Universal synchronous asynchronous receiver transmitter)
//  <e> USART1
//  <i> Configuration settings for OMNI Driver USART
#define CONFIG_USART_NUM_1 0
//      <o> USART1_TX Pin <0=>NC <1=>PA9
#define CONFIG_USART1_TX_PIN_VAL 0
#if (CONFIG_USART1_TX_PIN_VAL == 0)
#define CONFIG_USART1_TX_DEF 0
#elif (CONFIG_USART1_TX_PIN_VAL == 1)
#define CONFIG_USART1_TX_DEF 1
#define CONFIG_USART1_TX_PORT GPIOA
#define CONFIG_USART1_TX_PIN GPIO_PIN_9
#endif /* CONFIG_USART1_TX_PIN_VAL */
//      <o> USART1_RX Pin <0=>NC <1=>PA10
#define CONFIG_USART1_RX_PIN_VAL 0
#if (CONFIG_USART1_RX_PIN_VAL == 0)
#define CONFIG_USART1_RX_DEF 0
#elif (CONFIG_USART1_RX_PIN_VAL == 1)
#define CONFIG_USART1_RX_DEF 1
#define CONFIG_USART1_RX_PORT GPIOA
#define CONFIG_USART1_RX_PIN GPIO_PIN_10
#endif /* CONFIG_USART1_RX_PIN_VAL */

//      <e> USART1 Pin Full Remap
//      <i> Enable USART1 Pin Remapping
#define CONFIG_USART1_REMAP_FULL 0

//      <o> USART1_TX Pin <0=>NC <1=>PB6
#define CONFIG_USART1_TX_PIN_FULL_VAL 0
#if (CONFIG_USART1_TX_PIN_FULL_VAL == 0)
#define CONFIG_USART1_TX_FULL_DEF 0
#elif (CONFIG_USART1_TX_PIN_FULL_VAL == 1)
#define CONFIG_USART1_TX_FULL_DEF 1
#define CONFIG_USART1_TX_PORT_FULL GPIOB
#define CONFIG_USART1_TX_PIN_FULL GPIO_PIN_6
#endif /* CONFIG_USART1_TX_PIN_FULL_VAL */
//      <o> USART1_RX Pin <0=>NC <1=>PB7
#define CONFIG_USART1_RX_PIN_FULL_VAL 0
#if (CONFIG_USART1_RX_PIN_FULL_VAL == 0)
#define CONFIG_USART1_RX_FULL_DEF 0
#elif (CONFIG_USART1_RX_PIN_FULL_VAL == 1)
#define CONFIG_USART1_RX_FULL_DEF 1
#define CONFIG_USART1_RX_PORT_FULL GPIOB
#define CONFIG_USART1_RX_PIN_FULL GPIO_PIN_7
#endif /* CONFIG_USART1_RX_PIN_FULL_VAL */
//      </e>

#if (CONFIG_USART1_REMAP_FULL)
#define CONFIG_USART1_AF_REMAP  AFIO_USART1_REMAP
#define CONFIG_USART1_TX_PORT   CONFIG_USART1_TX_PORT_FULL
#define CONFIG_USART1_TX_PIN    CONFIG_USART1_TX_PIN_FULL
#define CONFIG_USART1_RX_PORT   CONFIG_USART1_RX_PORT_FULL
#define CONFIG_USART1_RX_PIN    CONFIG_USART1_RX_PIN_FULL
#else
#define CONFIG_USART1_AF_REMAP  AFIO_USART1_NO_REMAP
#endif /* CONFIG_USART1_REMAP_FULL */

//      <e> DMA TX
//          <i> Enable DMA TX
//          <o1> Number <1=>1
//          <i> Select DMA number
//          <o2> Channel <4=>4
//          <i> Select DMA channel
//          <o3> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//          <i> Select DMA priority
//          <o4> IRQ priority <0-15>
//          <i> Select DMA IRQ priority
//      </e>
#define CONFIG_USART1_TX_DMA 0
#define CONFIG_USART1_TX_DMA_NUMBER 1
#define CONFIG_USART1_TX_DMA_INS DMA_INS(CONFIG_USART1_TX_DMA_NUMBER)
#define CONFIG_USART1_TX_DMA_CHANNEL_NUM 4
#define CONFIG_USART1_TX_DMA_CHANNEL DMA_CHANNEL(CONFIG_USART1_TX_DMA_NUMBER, CONFIG_USART1_TX_DMA_CHANNEL_NUM)
#define CONFIG_USART1_TX_DMA_PRIORITY DMA_PRIORITY(0)
#define CONFIG_USART1_TX_DMA_IRQ_PRIO 1
#define CONFIG_USART1_TX_DMA_IRQ_NUM DMA_IRQ_NUM(CONFIG_USART1_TX_DMA_NUMBER, CONFIG_USART1_TX_DMA_CHANNEL_NUM)

//      <e> DMA RX
//          <i> Enable DMA RX
//          <o1> Number <1=>1
//          <i> Select DMA number
//          <o2> Channel <5=>5
//          <i> Select DMA channel
//          <o3> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//          <i> Select DMA priority
//          <o4> IRQ priority <0-15>
//          <i> Select DMA IRQ priority
//      </e>
#define CONFIG_USART1_RX_DMA 0
#define CONFIG_USART1_RX_DMA_NUMBER 1
#define CONFIG_USART1_RX_DMA_INS DMA_INS(CONFIG_USART1_RX_DMA_NUMBER)
#define CONFIG_USART1_RX_DMA_CHANNEL_NUM 5
#define CONFIG_USART1_RX_DMA_CHANNEL DMA_CHANNEL(CONFIG_USART1_RX_DMA_NUMBER, CONFIG_USART1_RX_DMA_CHANNEL_NUM)
#define CONFIG_USART1_RX_DMA_PRIORITY DMA_PRIORITY(0)
#define CONFIG_USART1_RX_DMA_IRQ_PRIO 1
#define CONFIG_USART1_RX_DMA_IRQ_NUM DMA_IRQ_NUM(CONFIG_USART1_RX_DMA_NUMBER, CONFIG_USART1_RX_DMA_CHANNEL_NUM)
//  </e>

//  <e> USART2
//  <i> Configuration settings for OMNI Driver USART
#define CONFIG_USART_NUM_2 0
//      <o> USART2_TX Pin <0=>NC <1=>PA2
#define CONFIG_USART2_TX_PIN_VAL 0
#if (CONFIG_USART2_TX_PIN_VAL == 0)
#define CONFIG_USART2_TX_DEF 0
#elif (CONFIG_USART2_TX_PIN_VAL == 1)
#define CONFIG_USART2_TX_DEF 1
#define CONFIG_USART2_TX_PORT GPIOA
#define CONFIG_USART2_TX_PIN GPIO_PIN_2
#endif /* CONFIG_USART2_TX_PIN_VAL */
//      <o> USART2_RX Pin <0=>NC <1=>PA3
#define CONFIG_USART2_RX_PIN_VAL 0
#if (CONFIG_USART2_RX_PIN_VAL == 0)
#define CONFIG_USART2_RX_DEF 0
#elif (CONFIG_USART2_RX_PIN_VAL == 1)
#define CONFIG_USART2_RX_DEF 1
#define CONFIG_USART2_RX_PORT GPIOA
#define CONFIG_USART2_RX_PIN GPIO_PIN_3
#endif /* CONFIG_USART2_RX_PIN_VAL */

//      <e> USART2 Pin Full Remap
//      <i> Enable USART2 Pin Remapping
#define CONFIG_USART2_REMAP_FULL 0

//      <o> USART2_TX Pin <0=>NC <1=>PD5
#define CONFIG_USART2_TX_PIN_FULL_VAL 0
#if (CONFIG_USART2_TX_PIN_FULL_VAL == 0)
#define CONFIG_USART2_TX_FULL_DEF 0
#elif (CONFIG_USART2_TX_PIN_FULL_VAL == 1)
#define CONFIG_USART2_TX_FULL_DEF 1
#define CONFIG_USART2_TX_PORT_FULL GPIOD
#define CONFIG_USART2_TX_PIN_FULL GPIO_PIN_5
#endif /* CONFIG_USART2_TX_PIN_FULL_VAL */
//      <o> USART2_RX Pin <0=>NC <1=>PD6
#define CONFIG_USART2_RX_PIN_FULL_VAL 0
#if (CONFIG_USART2_RX_PIN_FULL_VAL == 0)
#define CONFIG_USART2_RX_FULL_DEF 0
#elif (CONFIG_USART2_RX_PIN_FULL_VAL == 1)
#define CONFIG_USART2_RX_FULL_DEF 1
#define CONFIG_USART2_RX_PORT_FULL GPIOD
#define CONFIG_USART2_RX_PIN_FULL GPIO_PIN_6
#endif /* CONFIG_USART2_RX_PIN_FULL_VAL */
//      </e>

#if (CONFIG_USART2_REMAP_FULL)
#define CONFIG_USART2_AF_REMAP  AFIO_USART2_REMAP
#define CONFIG_USART2_TX_PORT   CONFIG_USART2_TX_PORT_FULL
#define CONFIG_USART2_TX_PIN    CONFIG_USART2_TX_PIN_FULL
#define CONFIG_USART2_RX_PORT   CONFIG_USART2_RX_PORT_FULL
#define CONFIG_USART2_RX_PIN    CONFIG_USART2_RX_PIN_FULL
#else
#define CONFIG_USART2_AF_REMAP  AFIO_USART2_NO_REMAP
#endif /* CONFIG_USART2_REMAP_FULL */

//      <e> DMA TX
//          <i> Enable DMA TX
//          <o1> Number <1=>1
//          <i> Select DMA number
//          <o2> Channel <7=>7
//          <i> Select DMA channel
//          <o3> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//          <i> Select DMA priority
//          <o4> IRQ priority <0-15>
//          <i> Select DMA IRQ priority
//      </e>
#define CONFIG_USART2_TX_DMA 0
#define CONFIG_USART2_TX_DMA_NUMBER 1
#define CONFIG_USART2_TX_DMA_INS DMA_INS(CONFIG_USART2_TX_DMA_NUMBER)
#define CONFIG_USART2_TX_DMA_CHANNEL_NUM 7
#define CONFIG_USART2_TX_DMA_CHANNEL DMA_CHANNEL(CONFIG_USART2_TX_DMA_NUMBER, CONFIG_USART2_TX_DMA_CHANNEL_NUM)
#define CONFIG_USART2_TX_DMA_PRIORITY DMA_PRIORITY(0)
#define CONFIG_USART2_TX_DMA_IRQ_PRIO 1
#define CONFIG_USART2_TX_DMA_IRQ_NUM DMA_IRQ_NUM(CONFIG_USART2_TX_DMA_NUMBER, CONFIG_USART2_TX_DMA_CHANNEL_NUM)

//      <e> DMA RX
//          <i> Enable DMA RX
//          <o1> Number <1=>1
//          <i> Select DMA number
//          <o2> Channel <6=>6
//          <i> Select DMA channel
//          <o3> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//          <i> Select DMA priority
//          <o4> IRQ priority <0-15>
//          <i> Select DMA IRQ priority
//      </e>
#define CONFIG_USART2_RX_DMA 0
#define CONFIG_USART2_RX_DMA_NUMBER 1
#define CONFIG_USART2_RX_DMA_INS DMA_INS(CONFIG_USART2_RX_DMA_NUMBER)
#define CONFIG_USART2_RX_DMA_CHANNEL_NUM 6
#define CONFIG_USART2_RX_DMA_CHANNEL DMA_CHANNEL(CONFIG_USART2_RX_DMA_NUMBER, CONFIG_USART2_RX_DMA_CHANNEL_NUM)
#define CONFIG_USART2_RX_DMA_PRIORITY DMA_PRIORITY(0)
#define CONFIG_USART2_RX_DMA_IRQ_PRIO 1
#define CONFIG_USART2_RX_DMA_IRQ_NUM DMA_IRQ_NUM(CONFIG_USART2_RX_DMA_NUMBER, CONFIG_USART2_RX_DMA_CHANNEL_NUM)
//  </e>

//  <e> USART3
//  <i> Configuration settings for OMNI Driver USART
#define CONFIG_USART_NUM_3 0
//      <o> USART3_TX Pin <0=>NC <1=>PB10
#define CONFIG_USART3_TX_PIN_VAL 0
#if (CONFIG_USART3_TX_PIN_VAL == 0)
#define CONFIG_USART3_TX_DEF 0
#elif (CONFIG_USART3_TX_PIN_VAL == 1)
#define CONFIG_USART3_TX_DEF 1
#define CONFIG_USART3_TX_PORT GPIOB
#define CONFIG_USART3_TX_PIN GPIO_PIN_10
#endif /* CONFIG_USART3_TX_PIN_VAL */
//      <o> USART3_RX Pin <0=>NC <1=>PB11
#define CONFIG_USART3_RX_PIN_VAL 0
#if (CONFIG_USART3_RX_PIN_VAL == 0)
#define CONFIG_USART3_RX_DEF 0
#elif (CONFIG_USART3_RX_PIN_VAL == 1)
#define CONFIG_USART3_RX_DEF 1
#define CONFIG_USART3_RX_PORT GPIOB
#define CONFIG_USART3_RX_PIN GPIO_PIN_11
#endif /* CONFIG_USART3_RX_PIN_VAL */

//      <e> USART3 Partial Pin Remap
//      <i> Enable USART3 Partial Pin Remapping
#define CONFIG_USART3_REMAP_PARTIAL 0

//      <o> USART3_TX Pin <0=>NC <1=>PC10
#define CONFIG_USART3_TX_PIN_PARTIAL_VAL 0
#if (CONFIG_USART3_TX_PIN_PARTIAL_VAL == 0)
#define CONFIG_USART3_TX_PARTIAL_DEF 0
#elif (CONFIG_USART3_TX_PIN_PARTIAL_VAL == 1)
#define CONFIG_USART3_TX_PARTIAL_DEF 1
#define CONFIG_USART3_TX_PORT_PARTIAL GPIOC
#define CONFIG_USART3_TX_PIN_PARTIAL GPIO_PIN_10
#endif /* CONFIG_USART3_TX_PIN_PARTIAL_VAL */
//      <o> USART3_RX Pin <0=>NC <1=>PC11
#define CONFIG_USART3_RX_PIN_PARTIAL_VAL 0
#if (CONFIG_USART3_RX_PIN_PARTIAL_VAL == 0)
#define CONFIG_USART3_RX_PARTIAL_DEF 0
#elif (CONFIG_USART3_RX_PIN_PARTIAL_VAL == 1)
#define CONFIG_USART3_RX_PARTIAL_DEF 1
#define CONFIG_USART3_RX_PORT_PARTIAL GPIOC
#define CONFIG_USART3_RX_PIN_PARTIAL GPIO_PIN_11
#endif /* CONFIG_USART3_RX_PIN_PARTIAL_VAL */
//      </e>

//      <e> USART3 Full Pin Remap
//      <i> Enable USART3 Full Pin Remapping
#define CONFIG_USART3_REMAP_FULL 0

//      <o> USART3_TX Pin <0=>NC <1=>PD8
#define CONFIG_USART3_TX_PIN_FULL_VAL 0
#if (CONFIG_USART3_TX_PIN_FULL_VAL == 0)
#define CONFIG_USART3_TX_FULL_DEF 0
#elif (CONFIG_USART3_TX_PIN_FULL_VAL == 1)
#define CONFIG_USART3_TX_FULL_DEF 1
#define CONFIG_USART3_TX_PORT_FULL GPIOD
#define CONFIG_USART3_TX_PIN_FULL GPIO_PIN_8
#endif /* CONFIG_USART3_TX_PIN_FULL_VAL */
//      <o> USART3_RX Pin <0=>NC <1=>PD9
#define CONFIG_USART3_RX_PIN_FULL_VAL 0
#if (CONFIG_USART3_RX_PIN_FULL_VAL == 0)
#define CONFIG_USART3_RX_FULL_DEF 0
#elif (CONFIG_USART3_RX_PIN_FULL_VAL == 1)
#define CONFIG_USART3_RX_FULL_DEF 1
#define CONFIG_USART3_RX_PORT_FULL GPIOD
#define CONFIG_USART3_RX_PIN_FULL GPIO_PIN_9
#endif /* CONFIG_USART3_RX_PIN_FULL_VAL */
//      </e>

#if ((CONFIG_USART3_REMAP_FULL == 1) && (CONFIG_USART3_REMAP_PARTIAL == 1))
#error "USART3 Full and Partial Pin Remap cannot be enabled at the same time!"
#endif /* ((CONFIG_USART3_REMAP_FULL == 1) && (CONFIG_USART3_REMAP_PARTIAL == 1)) */

#if (CONFIG_USART3_REMAP_FULL)
#define CONFIG_USART3_AF_REMAP  AFIO_USART3_REMAP_FULL
#define CONFIG_USART3_TX_PORT   CONFIG_USART3_TX_PORT_FULL
#define CONFIG_USART3_TX_PIN    CONFIG_USART3_TX_PIN_FULL
#define CONFIG_USART3_RX_PORT   CONFIG_USART3_RX_PORT_FULL
#define CONFIG_USART3_RX_PIN    CONFIG_USART3_RX_PIN_FULL
#elif (CONFIG_USART3_REMAP_PARTIAL)
#define CONFIG_USART3_AF_REMAP  AFIO_USART3_REMAP_PARTIAL
#define CONFIG_USART3_TX_PORT   CONFIG_USART3_TX_PORT_PARTIAL
#define CONFIG_USART3_TX_PIN    CONFIG_USART3_TX_PIN_PARTIAL
#define CONFIG_USART3_RX_PORT   CONFIG_USART3_RX_PORT_PARTIAL
#define CONFIG_USART3_RX_PIN    CONFIG_USART3_RX_PIN_PARTIAL
#endif /* CONFIG_USART3_REMAP_FULL */

//      <e> DMA TX
//          <i> Enable DMA TX
//          <o1> Number <1=>1
//          <i> Select DMA number
//          <o2> Channel <2=>2
//          <i> Select DMA channel
//          <o3> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//          <i> Select DMA priority
//          <o4> IRQ priority <0-15>
//          <i> Select DMA IRQ priority
//      </e>
#define CONFIG_USART3_TX_DMA 0
#define CONFIG_USART3_TX_DMA_NUMBER 1
#define CONFIG_USART3_TX_DMA_INS DMA_INS(CONFIG_USART3_TX_DMA_NUMBER)
#define CONFIG_USART3_TX_DMA_CHANNEL_NUM 2
#define CONFIG_USART3_TX_DMA_CHANNEL DMA_CHANNEL(CONFIG_USART3_TX_DMA_NUMBER, CONFIG_USART3_TX_DMA_CHANNEL_NUM)
#define CONFIG_USART3_TX_DMA_PRIORITY DMA_PRIORITY(0)
#define CONFIG_USART3_TX_DMA_IRQ_PRIO 1
#define CONFIG_USART3_TX_DMA_IRQ_NUM DMA_IRQ_NUM(CONFIG_USART3_TX_DMA_NUMBER, CONFIG_USART3_TX_DMA_CHANNEL_NUM)

//      <e> DMA RX
//          <i> Enable DMA RX
//          <o1> Number <1=>1
//          <i> Select DMA number
//          <o2> Channel <3=>3
//          <i> Select DMA channel
//          <o3> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//          <i> Select DMA priority
//          <o4> IRQ priority <0-15>
//          <i> Select DMA IRQ priority
//      </e>
#define CONFIG_USART3_RX_DMA 0
#define CONFIG_USART3_RX_DMA_NUMBER 1
#define CONFIG_USART3_RX_DMA_INS DMA_INS(CONFIG_USART3_RX_DMA_NUMBER)
#define CONFIG_USART3_RX_DMA_CHANNEL_NUM 3
#define CONFIG_USART3_RX_DMA_CHANNEL DMA_CHANNEL(CONFIG_USART3_RX_DMA_NUMBER, CONFIG_USART3_RX_DMA_CHANNEL_NUM)
#define CONFIG_USART3_RX_DMA_PRIORITY DMA_PRIORITY(0)
#define CONFIG_USART3_RX_DMA_IRQ_PRIO 1
#define CONFIG_USART3_RX_DMA_IRQ_NUM DMA_IRQ_NUM(CONFIG_USART3_RX_DMA_NUMBER, CONFIG_USART3_RX_DMA_CHANNEL_NUM)
//  </e>

//  <e> UART4
//  <i> Configuration settings for OMNI Driver UART
#define CONFIG_UART_NUM_4 0
#define CONFIG_UART4_AF_REMAP AFIO_UNAVAILABLE_REMAP
//      <o> UART4_TX Pin <0=>NC <1=>PC10
#define CONFIG_UART4_TX_PIN_VAL 0
#if (CONFIG_UART4_TX_PIN_VAL == 0)
#define CONFIG_UART4_TX_DEF 0
#elif (CONFIG_UART4_TX_PIN_VAL == 1)
#define CONFIG_UART4_TX_DEF 1
#define CONFIG_UART4_TX_PORT GPIOC
#define CONFIG_UART4_TX_PIN GPIO_PIN_10
#endif /* CONFIG_UART4_TX_PIN_VAL */
//      <o> UART4_RX Pin <0=>NC <1=>PC11
#define CONFIG_UART4_RX_PIN_VAL 0
#if (CONFIG_UART4_RX_PIN_VAL == 0)
#define CONFIG_UART4_RX_DEF 0
#elif (CONFIG_UART4_RX_PIN_VAL == 1)
#define CONFIG_UART4_RX_DEF 1
#define CONFIG_UART4_RX_PORT GPIOC
#define CONFIG_UART4_RX_PIN GPIO_PIN_11
#endif /* CONFIG_UART4_RX_PIN_VAL */

//      <e> DMA TX
//          <i> Enable DMA TX
//          <o1> Number <2=>2
//          <i> Select DMA number
//          <o2> Channel <5=>5
//          <i> Select DMA channel
//          <o3> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//          <i> Select DMA priority
//          <o4> IRQ priority <0-15>
//          <i> Select DMA IRQ priority
//      </e>
#define CONFIG_UART4_TX_DMA 0
#define CONFIG_UART4_TX_DMA_NUMBER 2
#define CONFIG_UART4_TX_DMA_INS DMA_INS(CONFIG_UART4_TX_DMA_NUMBER)
#define CONFIG_UART4_TX_DMA_CHANNEL_NUM 5
#define CONFIG_UART4_TX_DMA_CHANNEL DMA_CHANNEL(CONFIG_UART4_TX_DMA_NUMBER, CONFIG_UART4_TX_DMA_CHANNEL_NUM)
#define CONFIG_UART4_TX_DMA_PRIORITY DMA_PRIORITY(0)
#define CONFIG_UART4_TX_DMA_IRQ_PRIO 1
#define CONFIG_UART4_TX_DMA_IRQ_NUM DMA_IRQ_NUM(CONFIG_UART4_TX_DMA_NUMBER, CONFIG_UART4_TX_DMA_CHANNEL_NUM)

//      <e> DMA RX
//          <i> Enable DMA RX
//          <o1> Number <2=>2
//          <i> Select DMA number
//          <o2> Channel <3=>3
//          <i> Select DMA channel
//          <o3> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//          <i> Select DMA priority
//          <o4> IRQ priority <0-15>
//          <i> Select DMA IRQ priority
//      </e>
#define CONFIG_UART4_RX_DMA 0
#define CONFIG_UART4_RX_DMA_NUMBER 2
#define CONFIG_UART4_RX_DMA_INS DMA_INS(CONFIG_UART4_RX_DMA_NUMBER)
#define CONFIG_UART4_RX_DMA_CHANNEL_NUM 3
#define CONFIG_UART4_RX_DMA_CHANNEL DMA_CHANNEL(CONFIG_UART4_RX_DMA_NUMBER, CONFIG_UART4_RX_DMA_CHANNEL_NUM)
#define CONFIG_UART4_RX_DMA_PRIORITY DMA_PRIORITY(0)
#define CONFIG_UART4_RX_DMA_IRQ_PRIO 1
#define CONFIG_UART4_RX_DMA_IRQ_NUM DMA_IRQ_NUM(CONFIG_UART4_RX_DMA_NUMBER, CONFIG_UART4_RX_DMA_CHANNEL_NUM)
//  </e>

//  <e> UART5
//  <i> Configuration settings for OMNI Driver USART
#define CONFIG_USART_NUM_5 0
#define CONFIG_UART5_AF_REMAP AFIO_UNAVAILABLE_REMAP
//      <o> UART5_TX Pin <0=>NC <1=>PC12
#define CONFIG_UART5_TX_PIN_VAL 0
#if (CONFIG_UART5_TX_PIN_VAL == 0)
#define CONFIG_UART5_TX_DEF 0
#elif (CONFIG_UART5_TX_PIN_VAL == 1)
#define CONFIG_UART5_TX_DEF 1
#define CONFIG_UART5_TX_PORT GPIOC
#define CONFIG_UART5_TX_PIN GPIO_PIN_12
#endif /* CONFIG_UART5_TX_PIN_VAL */
//      <o> UART5_RX Pin <0=>NC <1=>PD2
#define CONFIG_UART5_RX_PIN_VAL 0
#if (CONFIG_UART5_RX_PIN_VAL == 0)
#define CONFIG_UART5_RX_DEF 0
#elif (CONFIG_UART5_RX_PIN_VAL == 1)
#define CONFIG_UART5_RX_DEF 1
#define CONFIG_UART5_RX_PORT GPIOD
#define CONFIG_UART5_RX_PIN GPIO_PIN_2
#endif /* CONFIG_UART5_RX_PIN_VAL */
//  </e>
// </h>

#if ((CONFIG_USART1_TX_DMA == 1) || \
     (CONFIG_USART2_TX_DMA == 1) || \
     (CONFIG_USART3_TX_DMA == 1) || \
     (CONFIG_UART4_TX_DMA == 1) || \
     (CONFIG_UART5_TX_DMA == 1))
#define CONFIG_USART_TX_DMA 1
#endif
#if ((CONFIG_USART1_RX_DMA == 1) || \
     (CONFIG_USART2_RX_DMA == 1) || \
     (CONFIG_USART3_RX_DMA == 1) || \
     (CONFIG_UART4_RX_DMA == 1) || \
     (CONFIG_UART5_RX_DMA == 1))
#define CONFIG_USART_RX_DMA 1
#endif

// <h> I2C (Inter-Integrated Circuit)
//  <e> I2C1
//  <i> Configuration settings for OMNI Driver I2C
#define CONFIG_I2C_NUM_1 1
//      <o> I2C1_SCL Pin <0=>PB6
#define CONFIG_I2C1_SCL_PIN_VAL 0
#if (CONFIG_I2C1_SCL_PIN_VAL == 0)
#define CONFIG_I2C1_SCL_DEF 1
#define CONFIG_I2C1_SCL_PORT GPIOB
#define CONFIG_I2C1_SCL_PIN GPIO_PIN_6
#endif /* CONFIG_I2C1_SCL_PIN_VAL */
//      <o> I2C1_SDA Pin <0=>PB7
#define CONFIG_I2C1_SDA_PIN_VAL 0
#if (CONFIG_I2C1_SDA_PIN_VAL == 0)
#define CONFIG_I2C1_SDA_DEF 1
#define CONFIG_I2C1_SDA_PORT GPIOB
#define CONFIG_I2C1_SDA_PIN GPIO_PIN_7
#endif /* CONFIG_I2C1_SDA_PIN_VAL */

//      <e> I2C1 Pin Full Remap
//      <i> Enable I2C1 Pin Remapping
#define CONFIG_I2C1_REMAP_FULL 0

//      <o> I2C1_SCL Pin <0=>PB8
#define CONFIG_I2C1_SCL_PIN_FULL_VAL 0
#if (CONFIG_I2C1_SCL_PIN_FULL_VAL == 0)
#define CONFIG_I2C1_SCL_FULL_DEF 1
#define CONFIG_I2C1_SCL_PORT_FULL GPIOB
#define CONFIG_I2C1_SCL_PIN_FULL GPIO_PIN_8
#endif /* CONFIG_I2C1_SCL_PIN_FULL_VAL */
//      <o> I2C1_SDA Pin <0=>PB9
#define CONFIG_I2C1_SDA_PIN_FULL_VAL 0
#if (CONFIG_I2C1_SDA_PIN_FULL_VAL == 0)
#define CONFIG_I2C1_SDA_FULL_DEF 1
#define CONFIG_I2C1_SDA_PORT_FULL GPIOB
#define CONFIG_I2C1_SDA_PIN_FULL GPIO_PIN_9
#endif /* CONFIG_I2C1_SDA_PIN_FULL_VAL */
//      </e>

#if (CONFIG_I2C1_REMAP_FULL)
#define CONFIG_I2C1_AF_REMAP    AFIO_I2C1_REMAP
#define CONFIG_I2C1_SCL_PORT    CONFIG_I2C1_SCL_PORT_FULL
#define CONFIG_I2C1_SCL_PIN     CONFIG_I2C1_SCL_PIN_FULL
#define CONFIG_I2C1_SDA_PORT    CONFIG_I2C1_SDA_PORT_FULL
#define CONFIG_I2C1_SDA_PIN     CONFIG_I2C1_SDA_PIN_FULL
#else
#define CONFIG_I2C1_AF_REMAP  AFIO_I2C1_NO_REMAP
#endif /* CONFIG_I2C1_REMAP_FULL */

//      <e> DMA TX
//          <i> Enable DMA TX
//          <o1> Number <1=>1
//          <i> Select DMA number
//          <o2> Channel <6=>6
//          <i> Select DMA channel
//          <o3> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//          <i> Select DMA priority
//          <o4> IRQ priority <0-15>
//          <i> Select DMA IRQ priority
//      </e>
#define CONFIG_I2C1_TX_DMA 1
#define CONFIG_I2C1_TX_DMA_NUMBER 1
#define CONFIG_I2C1_TX_DMA_INS DMA_INS(CONFIG_I2C1_TX_DMA_NUMBER)
#define CONFIG_I2C1_TX_DMA_CHANNEL_NUM 6
#define CONFIG_I2C1_TX_DMA_CHANNEL DMA_CHANNEL(CONFIG_I2C1_TX_DMA_NUMBER, CONFIG_I2C1_TX_DMA_CHANNEL_NUM)
#define CONFIG_I2C1_TX_DMA_PRIORITY DMA_PRIORITY(0)
#define CONFIG_I2C1_TX_DMA_IRQ_PRIO 1
#define CONFIG_I2C1_TX_DMA_IRQ_NUM DMA_IRQ_NUM(CONFIG_I2C1_TX_DMA_NUMBER, CONFIG_I2C1_TX_DMA_CHANNEL_NUM)

//      <e> DMA RX
//          <i> Enable DMA RX
//          <o1> Number <1=>1
//          <i> Select DMA number
//          <o2> Channel <7=>7
//          <i> Select DMA channel
//          <o3> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//          <i> Select DMA priority
//          <o4> IRQ priority <0-15>
//          <i> Select DMA IRQ priority
//      </e>
#define CONFIG_I2C1_RX_DMA 1
#define CONFIG_I2C1_RX_DMA_NUMBER 1
#define CONFIG_I2C1_RX_DMA_INS DMA_INS(CONFIG_I2C1_RX_DMA_NUMBER)
#define CONFIG_I2C1_RX_DMA_CHANNEL_NUM 7
#define CONFIG_I2C1_RX_DMA_CHANNEL DMA_CHANNEL(CONFIG_I2C1_RX_DMA_NUMBER, CONFIG_I2C1_RX_DMA_CHANNEL_NUM)
#define CONFIG_I2C1_RX_DMA_PRIORITY DMA_PRIORITY(0)
#define CONFIG_I2C1_RX_DMA_IRQ_PRIO 1
#define CONFIG_I2C1_RX_DMA_IRQ_NUM DMA_IRQ_NUM(CONFIG_I2C1_RX_DMA_NUMBER, CONFIG_I2C1_RX_DMA_CHANNEL_NUM)
//  </e>

//  <e> I2C2
//  <i> Configuration settings for OMNI Driver I2C
#define CONFIG_I2C_NUM_2 0
#define CONFIG_I2C2_AF_REMAP AFIO_UNAVAILABLE_REMAP
//      <o> I2C2_SCL Pin <0=>PB10
#define CONFIG_I2C2_SCL_PIN_VAL 0
#if (CONFIG_I2C2_SCL_PIN_VAL == 0)
#define CONFIG_I2C2_SCL_DEF 1
#define CONFIG_I2C2_SCL_PORT GPIOB
#define CONFIG_I2C2_SCL_PIN GPIO_PIN_10
#endif /* CONFIG_I2C2_SCL_PIN_VAL */
//      <o> I2C2_SDA Pin <0=>PB11
#define CONFIG_I2C2_SDA_PIN_VAL 0
#if (CONFIG_I2C2_SDA_PIN_VAL == 0)
#define CONFIG_I2C2_SDA_DEF 1
#define CONFIG_I2C2_SDA_PORT GPIOB
#define CONFIG_I2C2_SDA_PIN GPIO_PIN_11
#endif /* CONFIG_I2C2_SDA_PIN_VAL */

//      <e> DMA TX
//          <i> Enable DMA TX
//          <o1> Number <1=>1
//          <i> Select DMA number
//          <o2> Channel <4=>4
//          <i> Select DMA channel
//          <o3> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//          <i> Select DMA priority
//          <o4> IRQ priority <0-15>
//          <i> Select DMA IRQ priority
//      </e>
#define CONFIG_I2C2_TX_DMA 0
#define CONFIG_I2C2_TX_DMA_NUMBER 1
#define CONFIG_I2C2_TX_DMA_INS DMA_INS(CONFIG_I2C2_TX_DMA_NUMBER)
#define CONFIG_I2C2_TX_DMA_CHANNEL_NUM 4
#define CONFIG_I2C2_TX_DMA_CHANNEL DMA_CHANNEL(CONFIG_I2C2_TX_DMA_NUMBER, CONFIG_I2C2_TX_DMA_CHANNEL_NUM)
#define CONFIG_I2C2_TX_DMA_PRIORITY DMA_PRIORITY(0)
#define CONFIG_I2C2_TX_DMA_IRQ_PRIO 1
#define CONFIG_I2C2_TX_DMA_IRQ_NUM DMA_IRQ_NUM(CONFIG_I2C2_TX_DMA_NUMBER, CONFIG_I2C2_TX_DMA_CHANNEL_NUM)

//      <e> DMA RX
//          <i> Enable DMA RX
//          <o1> Number <1=>1
//          <i> Select DMA number
//          <o2> Channel <5=>5
//          <i> Select DMA channel
//          <o3> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//          <i> Select DMA priority
//          <o4> IRQ priority <0-15>
//          <i> Select DMA IRQ priority
//      </e>
#define CONFIG_I2C2_RX_DMA 0
#define CONFIG_I2C2_RX_DMA_NUMBER 1
#define CONFIG_I2C2_RX_DMA_INS DMA_INS(CONFIG_I2C2_RX_DMA_NUMBER)
#define CONFIG_I2C2_RX_DMA_CHANNEL_NUM 5
#define CONFIG_I2C2_RX_DMA_CHANNEL DMA_CHANNEL(CONFIG_I2C2_RX_DMA_NUMBER, CONFIG_I2C2_RX_DMA_CHANNEL_NUM)
#define CONFIG_I2C2_RX_DMA_PRIORITY DMA_PRIORITY(0)
#define CONFIG_I2C2_RX_DMA_IRQ_PRIO 1
#define CONFIG_I2C2_RX_DMA_IRQ_NUM DMA_IRQ_NUM(CONFIG_I2C2_RX_DMA_NUMBER, CONFIG_I2C2_RX_DMA_CHANNEL_NUM)
//  </e>
// </h>

#if ((CONFIG_I2C1_TX_DMA == 1) || \
     (CONFIG_I2C2_TX_DMA == 1))
#define CONFIG_I2C_TX_DMA 1
#endif
#if ((CONFIG_I2C1_RX_DMA == 1) || \
     (CONFIG_I2C2_RX_DMA == 1))
#define CONFIG_I2C_RX_DMA 1
#endif

#ifdef __cplusplus
}
#endif

#endif /* OMNI_DEVICE_CFG_H */
