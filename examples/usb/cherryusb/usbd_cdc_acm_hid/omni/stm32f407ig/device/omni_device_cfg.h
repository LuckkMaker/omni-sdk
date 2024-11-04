/**
  * @file    omni_device_cfg.h
  * @author  LuckkMaker
  * @brief   OMNI device configuration for STM32F4 series
  * @version 1.0.4
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

#define CONFIG_SOC_FAMILY_STM32F4XX

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

// Get PLL P
#define PLL_P(num)          RCC_PLLP_DIV##num
// Get PLL source
#define PLL_SRC0            RCC_PLLSOURCE_HSI
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
// Get flash latency
#define FLASH_LATENCY(num)  FLASH_LATENCY_##num
// Get power regulator voltage scaling
#define PWR_REG_VOLTAGE(num) PWR_REGULATOR_VOLTAGE_SCALE##num

// Get DMA instance
#define _DMA_INS(num)               DMA##num
#define DMA_INS(num)                _DMA_INS(num)
// Get DMA stream
#define _DMA_STREAM(num, stream)    DMA##num##_Stream##stream
#define DMA_STREAM(num, stream)     _DMA_STREAM(num, stream)
// Get DMA channel
#define DMA_CHANNEL(num)            DMA_CHANNEL_##num
// Get DMA priority
#define DMA_PRIORITY0               DMA_PRIORITY_LOW
#define DMA_PRIORITY1               DMA_PRIORITY_MEDIUM
#define DMA_PRIORITY2               DMA_PRIORITY_HIGH
#define DMA_PRIORITY3               DMA_PRIORITY_VERY_HIGH
#define DMA_PRIORITY(num)           DMA_PRIORITY##num
// Get DMA IRQ number
#define _DMA_IRQ_NUM(num, stream)   DMA##num##_Stream##stream##_IRQn
#define DMA_IRQ_NUM(num, stream)    _DMA_IRQ_NUM(num, stream)

//-------- <<< Use Configuration Wizard in Context Menu >>> --------------------

// <h> Interrupt Configuration
//  <h> USART Interrupt Priority
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
//  <o> USART6 IRQ Priority <0-15>
#define CONFIG_USART6_IRQ_PRIO 1
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
//  <o> I2C3 Event IRQ Priority <0-15>
#define CONFIG_I2C3_EV_IRQ_PRIO 1
//  <o> I2C3 Error IRQ Priority <0-15>
#define CONFIG_I2C3_ER_IRQ_PRIO 1
//  </h>
//  <h> USB Interrupt Priority
//  <o> USB_OTG_FS IRQ Priority <0-15>
#define CONFIG_USB_OTG_FS_IRQ_PRIO 1
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
//  <o> HSE Frequency <4000000-26000000>
#define CONFIG_HSE_FREQ 8000000
#define HSE_VALUE CONFIG_HSE_FREQ
//  <o> HSI State <0=>Disable <1=>Enable
#define CONFIG_HSI_STATE 0
//  <o> HSI Frequency
#define CONFIG_HSI_FREQ 16000000
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
#define CONFIG_LSI_FREQ 32000
#define LSI_VALUE CONFIG_LSI_FREQ
//  <e> PLL Configuration
//  <i> Enable PLL Configuration
#define CONFIG_PLL 1
//      <o> PLL Source <0=>HSI <1=>HSE
#define CONFIG_PLL_SRC PLL_SRC(1)
//      <o> PLL M <2-63>
#define CONFIG_PLL_M 8
//      <o> PLL N <50-432>
#define CONFIG_PLL_N 336
//      <o> PLL P <2=>2 <4=>4 <6=>6 <8=>8
#define CONFIG_PLL_P PLL_P(2)
//      <o> PLL Q <2-15>
#define CONFIG_PLL_Q 7
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
//  <o> Flash Latency <0-15>
#define CONFIG_FLASH_LATENCY FLASH_LATENCY(5)
//  <o> Power Regulator Voltage Scaling <1=>Scale 1 <2=>Scale 2 <3=>Scale 3
#define CONFIG_PWR_REG_VOLTAGE PWR_REG_VOLTAGE(1)
//  <o> System Clock <1-999999999>
#define CONFIG_SYSCLK_FREQ 168000000
//  <o> System Clock Source <0=>HSI <1=>HSE <2=>PLL
#define CONFIG_SYSCLK_SRC SYSCLK_SRC(2)
//  <o> AHB Prescaler <1=>1 <2=>2 <4=>4 <8=>8 <16=>16 <64=>64 <128=>128 <256=>256 <512=>512
#define CONFIG_AHB_PRESC AHB_DIV(1)
//  <o> APB1 Prescaler <1=>1 <2=>2 <4=>4 <8=>8 <16=>16
#define CONFIG_APB1_PRESC APB1_DIV(4)
//  <o> APB2 Prescaler <1=>1 <2=>2 <4=>4 <8=>8 <16=>16
#define CONFIG_APB2_PRESC APB2_DIV(2)
// </h>

// <h> USART (Universal synchronous asynchronous receiver transmitter)
//  <e> USART1
//  <i> Configuration settings for OMNI Driver USART
#define CONFIG_USART_NUM_1 1
//      <o> USART1 TX Pin <0=>NC <1=>PA9 <2=>PB6
#define CONFIG_USART1_TX_PIN_VAL 1
#if (CONFIG_USART1_TX_PIN_VAL == 0)
#define CONFIG_USART1_TX_DEF 0
#elif (CONFIG_USART1_TX_PIN_VAL == 1)
#define CONFIG_USART1_TX_DEF 1
#define CONFIG_USART1_TX_PORT GPIOA
#define CONFIG_USART1_TX_PIN GPIO_PIN_9
#define CONFIG_USART1_TX_AF GPIO_AF7_USART1
#elif (CONFIG_USART1_TX_PIN_VAL == 2)
#define CONFIG_USART1_TX_DEF 1
#define CONFIG_USART1_TX_PORT GPIOB
#define CONFIG_USART1_TX_PIN GPIO_PIN_6
#define CONFIG_USART1_TX_AF GPIO_AF7_USART1
#endif /* CONFIG_USART1_TX_PIN_VAL */
//      <o> USART1 RX Pin <0=>NC <1=>PA10 <2=>PB7
#define CONFIG_USART1_RX_PIN_VAL 1
#if (CONFIG_USART1_RX_PIN_VAL == 0)
#define CONFIG_USART1_RX_DEF 0
#elif (CONFIG_USART1_RX_PIN_VAL == 1)
#define CONFIG_USART1_RX_DEF 1
#define CONFIG_USART1_RX_PORT GPIOA
#define CONFIG_USART1_RX_PIN GPIO_PIN_10
#define CONFIG_USART1_RX_AF GPIO_AF7_USART1
#elif (CONFIG_USART1_RX_PIN_VAL == 2)
#define CONFIG_USART1_RX_DEF 1
#define CONFIG_USART1_RX_PORT GPIOB
#define CONFIG_USART1_RX_PIN GPIO_PIN_7
#define CONFIG_USART1_RX_AF GPIO_AF7_USART1
#endif /* CONFIG_USART1_RX_PIN_VAL */
//      <e> DMA TX
//          <i> Enable DMA TX
//          <o1> Number <2=>2
//          <i> Select DMA number
//          <o2> Stream <7=>7
//          <i> Select DMA stream
//          <o3> Channel <4=>4
//          <i> Select DMA channel
//          <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//          <i> Select DMA priority
//          <o5> IRQ priority <0-15>
//          <i> Select DMA IRQ priority
//      </e>
#define CONFIG_USART1_TX_DMA 1
#define CONFIG_USART1_TX_DMA_NUMBER 2
#define CONFIG_USART1_TX_DMA_INS DMA_INS(CONFIG_USART1_TX_DMA_NUMBER)
#define CONFIG_USART1_TX_DMA_STREAM_NUM 7
#define CONFIG_USART1_TX_DMA_STREAM DMA_STREAM(CONFIG_USART1_TX_DMA_NUMBER, CONFIG_USART1_TX_DMA_STREAM_NUM)
#define CONFIG_USART1_TX_DMA_CHANNEL DMA_CHANNEL(4)
#define CONFIG_USART1_TX_DMA_PRIORITY DMA_PRIORITY(0)
#define CONFIG_USART1_TX_DMA_IRQ_PRIO 1
#define CONFIG_USART1_TX_DMA_IRQ_NUM DMA_IRQ_NUM(CONFIG_USART1_TX_DMA_NUMBER, CONFIG_USART1_TX_DMA_STREAM_NUM)
//      <e> DMA RX
//          <i> Enable DMA RX
//          <o1> Number <2=>2
//          <i> Select DMA number
//          <o2> Stream <2=>2 <5=>5
//          <i> Select DMA stream
//          <o3> Channel <4=>4
//          <i> Select DMA channel
//          <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//          <i> Select DMA priority
//          <o5> IRQ priority <0-15>
//          <i> Select DMA IRQ priority
//      </e>
#define CONFIG_USART1_RX_DMA 1
#define CONFIG_USART1_RX_DMA_NUMBER 2
#define CONFIG_USART1_RX_DMA_INS DMA_INS(CONFIG_USART1_RX_DMA_NUMBER)
#define CONFIG_USART1_RX_DMA_STREAM_NUM 2
#define CONFIG_USART1_RX_DMA_STREAM DMA_STREAM(CONFIG_USART1_RX_DMA_NUMBER, CONFIG_USART1_RX_DMA_STREAM_NUM)
#define CONFIG_USART1_RX_DMA_CHANNEL DMA_CHANNEL(4)
#define CONFIG_USART1_RX_DMA_PRIORITY DMA_PRIORITY(0)
#define CONFIG_USART1_RX_DMA_IRQ_PRIO 1
#define CONFIG_USART1_RX_DMA_IRQ_NUM DMA_IRQ_NUM(CONFIG_USART1_RX_DMA_NUMBER, CONFIG_USART1_RX_DMA_STREAM_NUM)
// </e>

// <e> USART2
// <i> Configuration settings for OMNI Driver USART
#define CONFIG_USART_NUM_2 0
//      <o> USART2 TX Pin <0=>NC <1=>PA2 <2=>PD5
#define CONFIG_USART2_TX_PIN_VAL 0
#if (CONFIG_USART2_TX_PIN_VAL == 0)
#define CONFIG_USART2_TX_DEF 0
#elif (CONFIG_USART2_TX_PIN_VAL == 1)
#define CONFIG_USART2_TX_DEF 1
#define CONFIG_USART2_TX_PORT GPIOA
#define CONFIG_USART2_TX_PIN GPIO_PIN_2
#define CONFIG_USART2_TX_AF GPIO_AF7_USART2
#elif (CONFIG_USART2_TX_PIN_VAL == 2)
#define CONFIG_USART2_TX_DEF 1
#define CONFIG_USART2_TX_PORT GPIOD
#define CONFIG_USART2_TX_PIN GPIO_PIN_5
#define CONFIG_USART2_TX_AF GPIO_AF7_USART2
#endif /* CONFIG_USART2_TX_PIN_VAL */
//      <o> USART2 RX Pin <0=>NC <1=>PA3 <2=>PD6
#define CONFIG_USART2_RX_PIN_VAL 0
#if (CONFIG_USART2_RX_PIN_VAL == 0)
#define CONFIG_USART2_RX_DEF 0
#elif (CONFIG_USART2_RX_PIN_VAL == 1)
#define CONFIG_USART2_RX_DEF 1
#define CONFIG_USART2_RX_PORT GPIOA
#define CONFIG_USART2_RX_PIN GPIO_PIN_3
#define CONFIG_USART2_RX_AF GPIO_AF7_USART2
#elif (CONFIG_USART2_RX_PIN_VAL == 2)
#define CONFIG_USART2_RX_DEF 1
#define CONFIG_USART2_RX_PORT GPIOD
#define CONFIG_USART2_RX_PIN GPIO_PIN_6
#define CONFIG_USART2_RX_AF GPIO_AF7_USART2
#endif /* CONFIG_USART2_RX_PIN_VAL */
//      <e> DMA TX
//          <i> Enable DMA TX
//          <o1> Number <1=>1
//          <i> Select DMA number
//          <o2> Stream <6=>6
//          <i> Select DMA stream
//          <o3> Channel <4=>4
//          <i> Select DMA channel
//          <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//          <i> Select DMA priority
//          <o5> IRQ priority <0-15>
//          <i> Select DMA IRQ priority
//      </e>
#define CONFIG_USART2_TX_DMA 0
#define CONFIG_USART2_TX_DMA_NUMBER 1
#define CONFIG_USART2_TX_DMA_INS DMA_INS(CONFIG_USART2_TX_DMA_NUMBER)
#define CONFIG_USART2_TX_DMA_STREAM_NUM 6
#define CONFIG_USART2_TX_DMA_STREAM DMA_STREAM(CONFIG_USART2_TX_DMA_NUMBER, CONFIG_USART2_TX_DMA_STREAM_NUM)
#define CONFIG_USART2_TX_DMA_CHANNEL DMA_CHANNEL(4)
#define CONFIG_USART2_TX_DMA_PRIORITY DMA_PRIORITY(0)
#define CONFIG_USART2_TX_DMA_IRQ_PRIO 1
#define CONFIG_USART2_TX_DMA_IRQ_NUM DMA_IRQ_NUM(CONFIG_USART2_TX_DMA_NUMBER, CONFIG_USART2_TX_DMA_STREAM_NUM)
//      <e> DMA RX
//          <i> Enable DMA RX
//          <o1> Number <1=>1
//          <i> Select DMA number
//          <o2> Stream <5=>5
//          <i> Select DMA stream
//          <o3> Channel <4=>4
//          <i> Select DMA channel
//          <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//          <i> Select DMA priority
//          <o5> IRQ priority <0-15>
//          <i> Select DMA IRQ priority
//      </e>
#define CONFIG_USART2_RX_DMA 0
#define CONFIG_USART2_RX_DMA_NUMBER 1
#define CONFIG_USART2_RX_DMA_INS DMA_INS(CONFIG_USART2_RX_DMA_NUMBER)
#define CONFIG_USART2_RX_DMA_STREAM_NUM 5
#define CONFIG_USART2_RX_DMA_STREAM DMA_STREAM(CONFIG_USART2_RX_DMA_NUMBER, CONFIG_USART2_RX_DMA_STREAM_NUM)
#define CONFIG_USART2_RX_DMA_CHANNEL DMA_CHANNEL(4)
#define CONFIG_USART2_RX_DMA_PRIORITY DMA_PRIORITY(0)
#define CONFIG_USART2_RX_DMA_IRQ_PRIO 1
#define CONFIG_USART2_RX_DMA_IRQ_NUM DMA_IRQ_NUM(CONFIG_USART2_RX_DMA_NUMBER, CONFIG_USART2_RX_DMA_STREAM_NUM)
// </e>

// <e> USART3
// <i> Configuration settings for OMNI Driver USART
#define CONFIG_USART_NUM_3 0
//      <o> USART3 TX Pin <0=>NC <1=>PB10 <2=>PC10 <3=>PD8
#define CONFIG_USART3_TX_PIN_VAL 0
#if (CONFIG_USART3_TX_PIN_VAL == 0)
#define CONFIG_USART3_TX_DEF 0
#elif (CONFIG_USART3_TX_PIN_VAL == 1)
#define CONFIG_USART3_TX_DEF 1
#define CONFIG_USART3_TX_PORT GPIOB
#define CONFIG_USART3_TX_PIN GPIO_PIN_10
#define CONFIG_USART3_TX_AF GPIO_AF7_USART3
#elif (CONFIG_USART3_TX_PIN_VAL == 2)
#define CONFIG_USART3_TX_DEF 1
#define CONFIG_USART3_TX_PORT GPIOC
#define CONFIG_USART3_TX_PIN GPIO_PIN_10
#define CONFIG_USART3_TX_AF GPIO_AF7_USART3
#elif (CONFIG_USART3_TX_PIN_VAL == 3)
#define CONFIG_USART3_TX_DEF 1
#define CONFIG_USART3_TX_PORT GPIOD
#define CONFIG_USART3_TX_PIN GPIO_PIN_8
#define CONFIG_USART3_TX_AF GPIO_AF7_USART3
#endif /* CONFIG_USART3_TX_PIN_VAL */
//      <o> USART3 RX Pin <0=>NC <1=>PB11 <2=>PC11 <3=>PD9
#define CONFIG_USART3_RX_PIN_VAL 0
#if (CONFIG_USART3_RX_PIN_VAL == 0)
#define CONFIG_USART3_RX_DEF 0
#elif (CONFIG_USART3_RX_PIN_VAL == 1)
#define CONFIG_USART3_RX_DEF 1
#define CONFIG_USART3_RX_PORT GPIOB
#define CONFIG_USART3_RX_PIN GPIO_PIN_11
#define CONFIG_USART3_RX_AF GPIO_AF7_USART3
#elif (CONFIG_USART3_RX_PIN_VAL == 2)
#define CONFIG_USART3_RX_DEF 1
#define CONFIG_USART3_RX_PORT GPIOC
#define CONFIG_USART3_RX_PIN GPIO_PIN_11
#define CONFIG_USART3_RX_AF GPIO_AF7_USART3
#elif (CONFIG_USART3_RX_PIN_VAL == 3)
#define CONFIG_USART3_RX_DEF 1
#define CONFIG_USART3_RX_PORT GPIOD
#define CONFIG_USART3_RX_PIN GPIO_PIN_9
#define CONFIG_USART3_RX_AF GPIO_AF7_USART3
#endif /* CONFIG_USART3_RX_PIN_VAL */
//      <e> DMA TX
//          <i> Enable DMA TX
//          <o1> Number <1=>1
//          <i> Select DMA number
//          <o2> Stream <3=>3 <4=>4
//          <i> Select DMA stream
//          <o3> Channel <4=>4 <7=>7
//          <i> Select DMA channel (if stream 3 is selected, only channel 4 can be used, if stream 4 is selected, only channel 7 can be used)
//          <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//          <i> Select DMA priority
//          <o5> IRQ priority <0-15>
//          <i> Select DMA IRQ priority
//      </e>
#define CONFIG_USART3_TX_DMA 0
#define CONFIG_USART3_TX_DMA_NUMBER 1
#define CONFIG_USART3_TX_DMA_INS DMA_INS(CONFIG_USART3_TX_DMA_NUMBER)
#define CONFIG_USART3_TX_DMA_STREAM_NUM 3
#define CONFIG_USART3_TX_DMA_STREAM DMA_STREAM(CONFIG_USART3_TX_DMA_NUMBER, CONFIG_USART3_TX_DMA_STREAM_NUM)
#define CONFIG_USART3_TX_DMA_CHANNEL DMA_CHANNEL(4)
#define CONFIG_USART3_TX_DMA_PRIORITY DMA_PRIORITY(0)
#define CONFIG_USART3_TX_DMA_IRQ_PRIO 1
#define CONFIG_USART3_TX_DMA_IRQ_NUM DMA_IRQ_NUM(CONFIG_USART3_TX_DMA_NUMBER, CONFIG_USART3_TX_DMA_STREAM_NUM)
//      <e> DMA RX
//          <i> Enable DMA RX
//          <o1> Number <1=>1
//          <i> Select DMA number
//          <o2> Stream <1=>1
//          <i> Select DMA stream
//          <o3> Channel <4=>4
//          <i> Select DMA channel
//          <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//          <i> Select DMA priority
//          <o5> IRQ priority <0-15>
//          <i> Select DMA IRQ priority
//      </e>
#define CONFIG_USART3_RX_DMA 0
#define CONFIG_USART3_RX_DMA_NUMBER 1
#define CONFIG_USART3_RX_DMA_INS DMA_INS(CONFIG_USART3_RX_DMA_NUMBER)
#define CONFIG_USART3_RX_DMA_STREAM_NUM 1
#define CONFIG_USART3_RX_DMA_STREAM DMA_STREAM(CONFIG_USART3_RX_DMA_NUMBER, CONFIG_USART3_RX_DMA_STREAM_NUM)
#define CONFIG_USART3_RX_DMA_CHANNEL DMA_CHANNEL(4)
#define CONFIG_USART3_RX_DMA_PRIORITY DMA_PRIORITY(0)
#define CONFIG_USART3_RX_DMA_IRQ_PRIO 1
#define CONFIG_USART3_RX_DMA_IRQ_NUM DMA_IRQ_NUM(CONFIG_USART3_RX_DMA_NUMBER, CONFIG_USART3_RX_DMA_STREAM_NUM)
// </e>

// <e> UART4
// <i> Configuration settings for OMNI Driver USART
#define CONFIG_USART_NUM_4 0
//      <o> UART4 TX Pin <0=>NC <1=>PA0 <2=>PC10
#define CONFIG_UART4_TX_PIN_VAL 0
#if (CONFIG_UART4_TX_PIN_VAL == 0)
#define CONFIG_UART4_TX_DEF 0
#elif (CONFIG_UART4_TX_PIN_VAL == 1)
#define CONFIG_UART4_TX_DEF 1
#define CONFIG_UART4_TX_PORT GPIOA
#define CONFIG_UART4_TX_PIN GPIO_PIN_0
#define CONFIG_UART4_TX_AF GPIO_AF8_UART4
#elif (CONFIG_UART4_TX_PIN_VAL == 2)
#define CONFIG_UART4_TX_DEF 1
#define CONFIG_UART4_TX_PORT GPIOC
#define CONFIG_UART4_TX_PIN GPIO_PIN_10
#define CONFIG_UART4_TX_AF GPIO_AF8_UART4
#endif /* CONFIG_UART4_TX_PIN_VAL */
//      <o> UART4 RX Pin <0=>NC <1=>PA1 <2=>PC11
#define CONFIG_UART4_RX_PIN_VAL 0
#if (CONFIG_UART4_RX_PIN_VAL == 0)
#define CONFIG_UART4_RX_DEF 0
#elif (CONFIG_UART4_RX_PIN_VAL == 1)
#define CONFIG_UART4_RX_DEF 1
#define CONFIG_UART4_RX_PORT GPIOA
#define CONFIG_UART4_RX_PIN GPIO_PIN_1
#define CONFIG_UART4_RX_AF GPIO_AF8_UART4
#elif (CONFIG_UART4_RX_PIN_VAL == 2)
#define CONFIG_UART4_RX_DEF 1
#define CONFIG_UART4_RX_PORT GPIOC
#define CONFIG_UART4_RX_PIN GPIO_PIN_11
#define CONFIG_UART4_RX_AF GPIO_AF8_UART4
#endif /* CONFIG_UART4_RX_PIN_VAL */
//      <e> DMA TX
//          <i> Enable DMA TX
//          <o1> Number <1=>1
//          <i> Select DMA number
//          <o2> Stream <4=>4
//          <i> Select DMA stream
//          <o3> Channel <4=>4
//          <i> Select DMA channel
//          <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//          <i> Select DMA priority
//          <o5> IRQ priority <0-15>
//          <i> Select DMA IRQ priority
//      </e>
#define CONFIG_UART4_TX_DMA 0
#define CONFIG_UART4_TX_DMA_NUMBER 1
#define CONFIG_UART4_TX_DMA_INS DMA_INS(CONFIG_UART4_TX_DMA_NUMBER)
#define CONFIG_UART4_TX_DMA_STREAM_NUM 4
#define CONFIG_UART4_TX_DMA_STREAM DMA_STREAM(CONFIG_UART4_TX_DMA_NUMBER, CONFIG_UART4_TX_DMA_STREAM_NUM)
#define CONFIG_UART4_TX_DMA_CHANNEL DMA_CHANNEL(4)
#define CONFIG_UART4_TX_DMA_PRIORITY DMA_PRIORITY(0)
#define CONFIG_UART4_TX_DMA_IRQ_PRIO 1
#define CONFIG_UART4_TX_DMA_IRQ_NUM DMA_IRQ_NUM(CONFIG_UART4_TX_DMA_NUMBER, CONFIG_UART4_TX_DMA_STREAM_NUM)
//      <e> DMA RX
//          <i> Enable DMA RX
//          <o1> Number <1=>1
//          <i> Select DMA number
//          <o2> Stream <2=>2
//          <i> Select DMA stream
//          <o3> Channel <4=>4
//          <i> Select DMA channel
//          <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//          <i> Select DMA priority
//          <o5> IRQ priority <0-15>
//          <i> Select DMA IRQ priority
//      </e>
#define CONFIG_UART4_RX_DMA 0
#define CONFIG_UART4_RX_DMA_NUMBER 1
#define CONFIG_UART4_RX_DMA_INS DMA_INS(CONFIG_UART4_RX_DMA_NUMBER)
#define CONFIG_UART4_RX_DMA_STREAM_NUM 2
#define CONFIG_UART4_RX_DMA_STREAM DMA_STREAM(CONFIG_UART4_RX_DMA_NUMBER, CONFIG_UART4_RX_DMA_STREAM_NUM)
#define CONFIG_UART4_RX_DMA_CHANNEL DMA_CHANNEL(4)
#define CONFIG_UART4_RX_DMA_PRIORITY DMA_PRIORITY(0)
#define CONFIG_UART4_RX_DMA_IRQ_PRIO 1
#define CONFIG_UART4_RX_DMA_IRQ_NUM DMA_IRQ_NUM(CONFIG_UART4_RX_DMA_NUMBER, CONFIG_UART4_RX_DMA_STREAM_NUM)
// </e>

// <e> UART5
// <i> Configuration settings for OMNI Driver USART
#define CONFIG_USART_NUM_5 0
//      <o> UART5 TX Pin <0=>NC <1=>PC12
#define CONFIG_UART5_TX_PIN_VAL 0
#if (CONFIG_UART5_TX_PIN_VAL == 0)
#define CONFIG_UART5_TX_DEF 0
#elif (CONFIG_UART5_TX_PIN_VAL == 1)
#define CONFIG_UART5_TX_DEF 1
#define CONFIG_UART5_TX_PORT GPIOC
#define CONFIG_UART5_TX_PIN GPIO_PIN_12
#define CONFIG_UART5_TX_AF GPIO_AF8_UART5
#endif /* CONFIG_UART5_TX_PIN_VAL */
//      <o> UART5 RX Pin <0=>NC <1=>PD2
#define CONFIG_UART5_RX_PIN_VAL 0
#if (CONFIG_UART5_RX_PIN_VAL == 0)
#define CONFIG_UART5_RX_DEF 0
#elif (CONFIG_UART5_RX_PIN_VAL == 1)
#define CONFIG_UART5_RX_DEF 1
#define CONFIG_UART5_RX_PORT GPIOD
#define CONFIG_UART5_RX_PIN GPIO_PIN_2
#define CONFIG_UART5_RX_AF GPIO_AF8_UART5
#endif /* CONFIG_UART5_RX_PIN_VAL */
//      <e> DMA TX
//          <i> Enable DMA TX
//          <o1> Number <1=>1
//          <i> Select DMA number
//          <o2> Stream <7=>7
//          <i> Select DMA stream
//          <o3> Channel <4=>4
//          <i> Select DMA channel
//          <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//          <i> Select DMA priority
//          <o5> IRQ priority <0-15>
//          <i> Select DMA IRQ priority
//      </e>
#define CONFIG_UART5_TX_DMA 0
#define CONFIG_UART5_TX_DMA_NUMBER 1
#define CONFIG_UART5_TX_DMA_INS DMA_INS(CONFIG_UART5_TX_DMA_NUMBER)
#define CONFIG_UART5_TX_DMA_STREAM_NUM 7
#define CONFIG_UART5_TX_DMA_STREAM DMA_STREAM(CONFIG_UART5_TX_DMA_NUMBER, CONFIG_UART5_TX_DMA_STREAM_NUM)
#define CONFIG_UART5_TX_DMA_CHANNEL DMA_CHANNEL(4)
#define CONFIG_UART5_TX_DMA_PRIORITY DMA_PRIORITY(0)
#define CONFIG_UART5_TX_DMA_IRQ_PRIO 1
#define CONFIG_UART5_TX_DMA_IRQ_NUM DMA_IRQ_NUM(CONFIG_UART5_TX_DMA_NUMBER, CONFIG_UART5_TX_DMA_STREAM_NUM)
//      <e> DMA RX
//          <i> Enable DMA RX
//          <o1> Number <1=>1
//          <i> Select DMA number
//          <o2> Stream <0=>0
//          <i> Select DMA stream
//          <o3> Channel <4=>4
//          <i> Select DMA channel
//          <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//          <i> Select DMA priority
//          <o5> IRQ priority <0-15>
//          <i> Select DMA IRQ priority
//      </e>
#define CONFIG_UART5_RX_DMA 0
#define CONFIG_UART5_RX_DMA_NUMBER 1
#define CONFIG_UART5_RX_DMA_INS DMA_INS(CONFIG_UART5_RX_DMA_NUMBER)
#define CONFIG_UART5_RX_DMA_STREAM_NUM 0
#define CONFIG_UART5_RX_DMA_STREAM DMA_STREAM(CONFIG_UART5_RX_DMA_NUMBER, CONFIG_UART5_RX_DMA_STREAM_NUM)
#define CONFIG_UART5_RX_DMA_CHANNEL DMA_CHANNEL(4)
#define CONFIG_UART5_RX_DMA_PRIORITY DMA_PRIORITY(0)
#define CONFIG_UART5_RX_DMA_IRQ_PRIO 1
#define CONFIG_UART5_RX_DMA_IRQ_NUM DMA_IRQ_NUM(CONFIG_UART5_RX_DMA_NUMBER, CONFIG_UART5_RX_DMA_STREAM_NUM)
// </e>

// <e> USART6
// <i> Configuration settings for OMNI Driver USART
#define CONFIG_USART_NUM_6 0
//      <o> USART6 TX Pin <0=>NC <1=>PC6 <2=>PG14
#define CONFIG_USART6_TX_PIN_VAL 0
#if (CONFIG_USART6_TX_PIN_VAL == 0)
#define CONFIG_USART6_TX_DEF 0
#elif (CONFIG_USART6_TX_PIN_VAL == 1)
#define CONFIG_USART6_TX_DEF 1
#define CONFIG_USART6_TX_PORT GPIOC
#define CONFIG_USART6_TX_PIN GPIO_PIN_6
#define CONFIG_USART6_TX_AF GPIO_AF8_USART6
#elif (CONFIG_USART6_TX_PIN_VAL == 2)
#define CONFIG_USART6_TX_DEF 1
#define CONFIG_USART6_TX_PORT GPIOG
#define CONFIG_USART6_TX_PIN GPIO_PIN_14
#define CONFIG_USART6_TX_AF GPIO_AF8_USART6
#endif /* CONFIG_USART6_TX_PIN_VAL */
//      <o> USART6 RX Pin <0=>NC <1=>PC7 <2=>PG9
#define CONFIG_USART6_RX_PIN_VAL 0
#if (CONFIG_USART6_RX_PIN_VAL == 0)
#define CONFIG_USART6_RX_DEF 0
#elif (CONFIG_USART6_RX_PIN_VAL == 1)
#define CONFIG_USART6_RX_DEF 1
#define CONFIG_USART6_RX_PORT GPIOC
#define CONFIG_USART6_RX_PIN GPIO_PIN_7
#define CONFIG_USART6_RX_AF GPIO_AF8_USART6
#elif (CONFIG_USART6_RX_PIN_VAL == 2)
#define CONFIG_USART6_RX_DEF 1
#define CONFIG_USART6_RX_PORT GPIOG
#define CONFIG_USART6_RX_PIN GPIO_PIN_9
#define CONFIG_USART6_RX_AF GPIO_AF8_USART6
#endif /* CONFIG_USART6_RX_PIN_VAL */
//      <e> DMA TX
//          <i> Enable DMA TX
//          <o1> Number <2=>2
//          <i> Select DMA number
//          <o2> Stream <6=>6 <7=>7
//          <i> Select DMA stream
//          <o3> Channel <5=>5
//          <i> Select DMA channel
//          <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//          <i> Select DMA priority
//          <o5> IRQ priority <0-15>
//          <i> Select DMA IRQ priority
//      </e>
#define CONFIG_USART6_TX_DMA 0
#define CONFIG_USART6_TX_DMA_NUMBER 2
#define CONFIG_USART6_TX_DMA_INS DMA_INS(CONFIG_USART6_TX_DMA_NUMBER)
#define CONFIG_USART6_TX_DMA_STREAM_NUM 6
#define CONFIG_USART6_TX_DMA_STREAM DMA_STREAM(CONFIG_USART6_TX_DMA_NUMBER, CONFIG_USART6_TX_DMA_STREAM_NUM)
#define CONFIG_USART6_TX_DMA_CHANNEL DMA_CHANNEL(5)
#define CONFIG_USART6_TX_DMA_PRIORITY DMA_PRIORITY(0)
#define CONFIG_USART6_TX_DMA_IRQ_PRIO 1
#define CONFIG_USART6_TX_DMA_IRQ_NUM DMA_IRQ_NUM(CONFIG_USART6_TX_DMA_NUMBER, CONFIG_USART6_TX_DMA_STREAM_NUM)
//      <e> DMA RX
//          <i> Enable DMA RX
//          <o1> Number <2=>2
//          <i> Select DMA number
//          <o2> Stream <1=>1 <2=>2
//          <i> Select DMA stream
//          <o3> Channel <5=>5
//          <i> Select DMA channel
//          <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//          <i> Select DMA priority
//          <o5> IRQ priority <0-15>
//          <i> Select DMA IRQ priority
//      </e>
#define CONFIG_USART6_RX_DMA 0
#define CONFIG_USART6_RX_DMA_NUMBER 2
#define CONFIG_USART6_RX_DMA_INS DMA_INS(CONFIG_USART6_RX_DMA_NUMBER)
#define CONFIG_USART6_RX_DMA_STREAM_NUM 1
#define CONFIG_USART6_RX_DMA_STREAM DMA_STREAM(CONFIG_USART6_RX_DMA_NUMBER, CONFIG_USART6_RX_DMA_STREAM_NUM)
#define CONFIG_USART6_RX_DMA_CHANNEL DMA_CHANNEL(5)
#define CONFIG_USART6_RX_DMA_PRIORITY DMA_PRIORITY(0)
#define CONFIG_USART6_RX_DMA_IRQ_PRIO 1
#define CONFIG_USART6_RX_DMA_IRQ_NUM DMA_IRQ_NUM(CONFIG_USART6_RX_DMA_NUMBER, CONFIG_USART6_RX_DMA_STREAM_NUM)
// </e>
// </h>

#if ((CONFIG_USART1_TX_DMA == 1) || \
     (CONFIG_USART2_TX_DMA == 1) || \
     (CONFIG_USART3_TX_DMA == 1) || \
     (CONFIG_UART4_TX_DMA == 1) || \
     (CONFIG_UART5_TX_DMA == 1) || \
     (CONFIG_USART6_TX_DMA == 1))
#define CONFIG_USART_TX_DMA 1
#endif
#if ((CONFIG_USART1_RX_DMA == 1) || \
     (CONFIG_USART2_RX_DMA == 1) || \
     (CONFIG_USART3_RX_DMA == 1) || \
     (CONFIG_UART4_RX_DMA == 1) || \
     (CONFIG_UART5_RX_DMA == 1) || \
     (CONFIG_USART6_RX_DMA == 1))
#define CONFIG_USART_RX_DMA 1
#endif

// <h> I2C (Inter-integrated circuit)
//  <e> I2C1
//  <i> Configuration settings for OMNI Driver I2C
#define CONFIG_I2C_NUM_1 0
//      <o> I2C1 SCL Pin <0=>PB6 <1=>PB8
#define CONFIG_I2C1_SCL_PIN_VAL 0
#if (CONFIG_I2C1_SCL_PIN_VAL == 0)
#define CONFIG_I2C1_SCL_DEF 1
#define CONFIG_I2C1_SCL_PORT GPIOB
#define CONFIG_I2C1_SCL_PIN GPIO_PIN_6
#define CONFIG_I2C1_SCL_AF GPIO_AF4_I2C1
#elif (CONFIG_I2C1_SCL_PIN_VAL == 1)
#define CONFIG_I2C1_SCL_DEF 1
#define CONFIG_I2C1_SCL_PORT GPIOB
#define CONFIG_I2C1_SCL_PIN GPIO_PIN_8
#define CONFIG_I2C1_SCL_AF GPIO_AF4_I2C1
#else
#error "Invalid I2C1 SCL Pin Configuration!"
#endif /* CONFIG_I2C1_SCL_PIN_VAL */

//      <o> I2C1 SDA Pin <0=>PB7 <1=>PB9
#define CONFIG_I2C1_SDA_PIN_VAL 0
#if (CONFIG_I2C1_SDA_PIN_VAL == 0)
#define CONFIG_I2C1_SDA_DEF 1
#define CONFIG_I2C1_SDA_PORT GPIOB
#define CONFIG_I2C1_SDA_PIN GPIO_PIN_7
#define CONFIG_I2C1_SDA_AF GPIO_AF4_I2C1
#elif (CONFIG_I2C1_SDA_PIN_VAL == 1)
#define CONFIG_I2C1_SDA_DEF 1
#define CONFIG_I2C1_SDA_PORT GPIOB
#define CONFIG_I2C1_SDA_PIN GPIO_PIN_9
#define CONFIG_I2C1_SDA_AF GPIO_AF4_I2C1
#else
#error "Invalid I2C1 SDA Pin Configuration!"
#endif /* CONFIG_I2C1_SDA_PIN_VAL */
//      <e> DMA TX
//          <i> Enable DMA TX
//          <o1> Number <1=>1
//          <i> Select DMA number
//          <o2> Stream <6=>6 <7=>7
//          <i> Select DMA stream
//          <o3> Channel <1=>1
//          <i> Select DMA channel
//          <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//          <i> Select DMA priority
//          <o5> IRQ priority <0-15>
//          <i> Select DMA IRQ priority
//      </e>
#define CONFIG_I2C1_TX_DMA 0
#define CONFIG_I2C1_TX_DMA_NUMBER 1
#define CONFIG_I2C1_TX_DMA_INS DMA_INS(CONFIG_I2C1_TX_DMA_NUMBER)
#define CONFIG_I2C1_TX_DMA_STREAM_NUM 6
#define CONFIG_I2C1_TX_DMA_STREAM DMA_STREAM(CONFIG_I2C1_TX_DMA_NUMBER, CONFIG_I2C1_TX_DMA_STREAM_NUM)
#define CONFIG_I2C1_TX_DMA_CHANNEL DMA_CHANNEL(1)
#define CONFIG_I2C1_TX_DMA_PRIORITY DMA_PRIORITY(0)
#define CONFIG_I2C1_TX_DMA_IRQ_PRIO 1
#define CONFIG_I2C1_TX_DMA_IRQ_NUM DMA_IRQ_NUM(CONFIG_I2C1_TX_DMA_NUMBER, CONFIG_I2C1_TX_DMA_STREAM_NUM)
//      <e> DMA RX
//          <i> Enable DMA RX
//          <o1> Number <1=>1
//          <i> Select DMA number
//          <o2> Stream <0=>0 <5=>5
//          <i> Select DMA stream
//          <o3> Channel <1=>1
//          <i> Select DMA channel
//          <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//          <i> Select DMA priority
//          <o5> IRQ priority <0-15>
//          <i> Select DMA IRQ priority
//      </e>
#define CONFIG_I2C1_RX_DMA 0
#define CONFIG_I2C1_RX_DMA_NUMBER 1
#define CONFIG_I2C1_RX_DMA_INS DMA_INS(CONFIG_I2C1_RX_DMA_NUMBER)
#define CONFIG_I2C1_RX_DMA_STREAM_NUM 0
#define CONFIG_I2C1_RX_DMA_STREAM DMA_STREAM(CONFIG_I2C1_RX_DMA_NUMBER, CONFIG_I2C1_RX_DMA_STREAM_NUM)
#define CONFIG_I2C1_RX_DMA_CHANNEL DMA_CHANNEL(1)
#define CONFIG_I2C1_RX_DMA_PRIORITY DMA_PRIORITY(0)
#define CONFIG_I2C1_RX_DMA_IRQ_PRIO 1
#define CONFIG_I2C1_RX_DMA_IRQ_NUM DMA_IRQ_NUM(CONFIG_I2C1_RX_DMA_NUMBER, CONFIG_I2C1_RX_DMA_STREAM_NUM)
//  </e>

//  <e> I2C2
//  <i> Configuration settings for OMNI Driver I2C
#define CONFIG_I2C_NUM_2 0
//      <o> I2C2 SCL Pin <0=>PB10 <1=>PF1 <2=>PH4
#define CONFIG_I2C2_SCL_PIN_VAL 0
#if (CONFIG_I2C2_SCL_PIN_VAL == 0)
#define CONFIG_I2C2_SCL_DEF 1
#define CONFIG_I2C2_SCL_PORT GPIOB
#define CONFIG_I2C2_SCL_PIN GPIO_PIN_10
#define CONFIG_I2C2_SCL_AF GPIO_AF4_I2C2
#elif (CONFIG_I2C2_SCL_PIN_VAL == 1)
#define CONFIG_I2C2_SCL_DEF 1
#define CONFIG_I2C2_SCL_PORT GPIOF
#define CONFIG_I2C2_SCL_PIN GPIO_PIN_1
#define CONFIG_I2C2_SCL_AF GPIO_AF4_I2C2
#elif (CONFIG_I2C2_SCL_PIN_VAL == 2)
#define CONFIG_I2C2_SCL_DEF 1
#define CONFIG_I2C2_SCL_PORT GPIOH
#define CONFIG_I2C2_SCL_PIN GPIO_PIN_4
#define CONFIG_I2C2_SCL_AF GPIO_AF4_I2C2
#else
#error "Invalid I2C2 SCL Pin Configuration!"
#endif /* CONFIG_I2C2_SCL_PIN_VAL */
//      <o> I2C2 SDA Pin <0=>PB11 <1=>PF0 <2=>PH5
#define CONFIG_I2C2_SDA_PIN_VAL 0
#if (CONFIG_I2C2_SDA_PIN_VAL == 0)
#define CONFIG_I2C2_SDA_DEF 1
#define CONFIG_I2C2_SDA_PORT GPIOB
#define CONFIG_I2C2_SDA_PIN GPIO_PIN_11
#define CONFIG_I2C2_SDA_AF GPIO_AF4_I2C2
#elif (CONFIG_I2C2_SDA_PIN_VAL == 1)
#define CONFIG_I2C2_SDA_DEF 1
#define CONFIG_I2C2_SDA_PORT GPIOF
#define CONFIG_I2C2_SDA_PIN GPIO_PIN_0
#define CONFIG_I2C2_SDA_AF GPIO_AF4_I2C2
#elif (CONFIG_I2C2_SDA_PIN_VAL == 2)
#define CONFIG_I2C2_SDA_DEF 1
#define CONFIG_I2C2_SDA_PORT GPIOH
#define CONFIG_I2C2_SDA_PIN GPIO_PIN_5
#define CONFIG_I2C2_SDA_AF GPIO_AF4_I2C2
#else
#error "Invalid I2C2 SDA Pin Configuration!"
#endif /* CONFIG_I2C2_SDA_PIN_VAL */
//      <e> DMA TX
//          <i> Enable DMA TX
//          <o1> Number <1=>1
//          <i> Select DMA number
//          <o2> Stream <7=>7
//          <i> Select DMA stream
//          <o3> Channel <7=>7
//          <i> Select DMA channel
//          <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//          <i> Select DMA priority
//          <o5> IRQ priority <0-15>
//          <i> Select DMA IRQ priority
//      </e>
#define CONFIG_I2C2_TX_DMA 0
#define CONFIG_I2C2_TX_DMA_NUMBER 1
#define CONFIG_I2C2_TX_DMA_INS DMA_INS(CONFIG_I2C2_TX_DMA_NUMBER)
#define CONFIG_I2C2_TX_DMA_STREAM_NUM 7
#define CONFIG_I2C2_TX_DMA_STREAM DMA_STREAM(CONFIG_I2C2_TX_DMA_NUMBER, CONFIG_I2C2_TX_DMA_STREAM_NUM)
#define CONFIG_I2C2_TX_DMA_CHANNEL DMA_CHANNEL(7)
#define CONFIG_I2C2_TX_DMA_PRIORITY DMA_PRIORITY(0)
#define CONFIG_I2C2_TX_DMA_IRQ_PRIO 1
#define CONFIG_I2C2_TX_DMA_IRQ_NUM DMA_IRQ_NUM(CONFIG_I2C2_TX_DMA_NUMBER, CONFIG_I2C2_TX_DMA_STREAM_NUM)
//      <e> DMA RX
//          <i> Enable DMA RX
//          <o1> Number <1=>1
//          <i> Select DMA number
//          <o2> Stream <2=>2 <3=>3
//          <i> Select DMA stream
//          <o3> Channel <7=>7
//          <i> Select DMA channel
//          <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//          <i> Select DMA priority
//          <o5> IRQ priority <0-15>
//          <i> Select DMA IRQ priority
//      </e>
#define CONFIG_I2C2_RX_DMA 0
#define CONFIG_I2C2_RX_DMA_NUMBER 1
#define CONFIG_I2C2_RX_DMA_INS DMA_INS(CONFIG_I2C2_RX_DMA_NUMBER)
#define CONFIG_I2C2_RX_DMA_STREAM_NUM 2
#define CONFIG_I2C2_RX_DMA_STREAM DMA_STREAM(CONFIG_I2C2_RX_DMA_NUMBER, CONFIG_I2C2_RX_DMA_STREAM_NUM)
#define CONFIG_I2C2_RX_DMA_CHANNEL DMA_CHANNEL(7)
#define CONFIG_I2C2_RX_DMA_PRIORITY DMA_PRIORITY(0)
#define CONFIG_I2C2_RX_DMA_IRQ_PRIO 1
#define CONFIG_I2C2_RX_DMA_IRQ_NUM DMA_IRQ_NUM(CONFIG_I2C2_RX_DMA_NUMBER, CONFIG_I2C2_RX_DMA_STREAM_NUM)
//  </e>

//  <e> I2C3
//  <i> Configuration settings for OMNI Driver I2C
#define CONFIG_I2C_NUM_3 0
//      <o> I2C3 SCL Pin <0=>PA8 <1=>PH7
#define CONFIG_I2C3_SCL_PIN_VAL 0
#if (CONFIG_I2C3_SCL_PIN_VAL == 0)
#define CONFIG_I2C3_SCL_DEF 1
#define CONFIG_I2C3_SCL_PORT GPIOA
#define CONFIG_I2C3_SCL_PIN GPIO_PIN_8
#define CONFIG_I2C3_SCL_AF GPIO_AF4_I2C3
#elif (CONFIG_I2C3_SCL_PIN_VAL == 1)
#define CONFIG_I2C3_SCL_DEF 1
#define CONFIG_I2C3_SCL_PORT GPIOH
#define CONFIG_I2C3_SCL_PIN GPIO_PIN_7
#define CONFIG_I2C3_SCL_AF GPIO_AF4_I2C3
#else
#error "Invalid I2C3 SCL Pin Configuration!"
#endif /* CONFIG_I2C3_SCL_PIN_VAL */
//      <o> I2C3 SDA Pin <0=>PC9 <1=>PH8
#define CONFIG_I2C3_SDA_PIN_VAL 0
#if (CONFIG_I2C3_SDA_PIN_VAL == 0)
#define CONFIG_I2C3_SDA_DEF 1
#define CONFIG_I2C3_SDA_PORT GPIOC
#define CONFIG_I2C3_SDA_PIN GPIO_PIN_9
#define CONFIG_I2C3_SDA_AF GPIO_AF4_I2C3
#elif (CONFIG_I2C3_SDA_PIN_VAL == 1)
#define CONFIG_I2C3_SDA_DEF 1
#define CONFIG_I2C3_SDA_PORT GPIOH
#define CONFIG_I2C3_SDA_PIN GPIO_PIN_8
#define CONFIG_I2C3_SDA_AF GPIO_AF4_I2C3
#else
#error "Invalid I2C3 SDA Pin Configuration!"
#endif /* CONFIG_I2C3_SDA_PIN_VAL */
//      <e> DMA TX
//          <i> Enable DMA TX
//          <o1> Number <1=>1
//          <i> Select DMA number
//          <o2> Stream <4=>4
//          <i> Select DMA stream
//          <o3> Channel <3=>3
//          <i> Select DMA channel
//          <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//          <i> Select DMA priority
//          <o5> IRQ priority <0-15>
//          <i> Select DMA IRQ priority
//      </e>
#define CONFIG_I2C3_TX_DMA 0
#define CONFIG_I2C3_TX_DMA_NUMBER 1
#define CONFIG_I2C3_TX_DMA_INS DMA_INS(CONFIG_I2C3_TX_DMA_NUMBER)
#define CONFIG_I2C3_TX_DMA_STREAM_NUM 4
#define CONFIG_I2C3_TX_DMA_STREAM DMA_STREAM(CONFIG_I2C3_TX_DMA_NUMBER, CONFIG_I2C3_TX_DMA_STREAM_NUM)
#define CONFIG_I2C3_TX_DMA_CHANNEL DMA_CHANNEL(3)
#define CONFIG_I2C3_TX_DMA_PRIORITY DMA_PRIORITY(0)
#define CONFIG_I2C3_TX_DMA_IRQ_PRIO 1
#define CONFIG_I2C3_TX_DMA_IRQ_NUM DMA_IRQ_NUM(CONFIG_I2C3_TX_DMA_NUMBER, CONFIG_I2C3_TX_DMA_STREAM_NUM)
//      <e> DMA RX
//          <i> Enable DMA RX
//          <o1> Number <1=>1
//          <i> Select DMA number
//          <o2> Stream <2=>2
//          <i> Select DMA stream
//          <o3> Channel <3=>3
//          <i> Select DMA channel
//          <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//          <i> Select DMA priority
//          <o5> IRQ priority <0-15>
//          <i> Select DMA IRQ priority
//      </e>
#define CONFIG_I2C3_RX_DMA 0
#define CONFIG_I2C3_RX_DMA_NUMBER 1
#define CONFIG_I2C3_RX_DMA_INS DMA_INS(CONFIG_I2C3_RX_DMA_NUMBER)
#define CONFIG_I2C3_RX_DMA_STREAM_NUM 2
#define CONFIG_I2C3_RX_DMA_STREAM DMA_STREAM(CONFIG_I2C3_RX_DMA_NUMBER, CONFIG_I2C3_RX_DMA_STREAM_NUM)
#define CONFIG_I2C3_RX_DMA_CHANNEL DMA_CHANNEL(3)
#define CONFIG_I2C3_RX_DMA_PRIORITY DMA_PRIORITY(0)
#define CONFIG_I2C3_RX_DMA_IRQ_PRIO 1
#define CONFIG_I2C3_RX_DMA_IRQ_NUM DMA_IRQ_NUM(CONFIG_I2C3_RX_DMA_NUMBER, CONFIG_I2C3_RX_DMA_STREAM_NUM)
//  </e>
// </h>

#if ((CONFIG_I2C1_TX_DMA == 1) || \
     (CONFIG_I2C2_TX_DMA == 1) || \
     (CONFIG_I2C3_TX_DMA == 1))
#define CONFIG_I2C_TX_DMA 1
#endif
#if ((CONFIG_I2C1_RX_DMA == 1) || \
     (CONFIG_I2C2_RX_DMA == 1) || \
     (CONFIG_I2C3_RX_DMA == 1))
#define CONFIG_I2C_RX_DMA 1
#endif

// <h> USB (Universal serial bus)
//  <e> USB OTG FS (USB Number 1)
//  <i> Configuration settings for OMNI Driver USB OTG FS
#define CONFIG_USB_OTG_FS 1
//      <o> USB OTG FS DM Pin <0=>PA11
#define CONFIG_USB_OTG_FS_DM_PIN_VAL 0
#if (CONFIG_USB_OTG_FS_DM_PIN_VAL == 0)
#define CONFIG_USB_OTG_FS_DM_DEF 1
#define CONFIG_USB_OTG_FS_DM_PORT GPIOA
#define CONFIG_USB_OTG_FS_DM_PIN GPIO_PIN_11
#define CONFIG_USB_OTG_FS_DM_AF GPIO_AF10_OTG_FS
#endif /* CONFIG_USB_OTG_FS_DM_PIN_VAL */
//      <o> USB OTG FS DP Pin <0=>PA12
#define CONFIG_USB_OTG_FS_DP_PIN_VAL 0
#if (CONFIG_USB_OTG_FS_DP_PIN_VAL == 0)
#define CONFIG_USB_OTG_FS_DP_DEF 1
#define CONFIG_USB_OTG_FS_DP_PORT GPIOA
#define CONFIG_USB_OTG_FS_DP_PIN GPIO_PIN_12
#define CONFIG_USB_OTG_FS_DP_AF GPIO_AF10_OTG_FS
#endif /* CONFIG_USB_OTG_FS_DP_PIN_VAL */
//      <o> USB OTG FS ID Pin <0=>NC <1=>PA10
#define CONFIG_USB_OTG_FS_ID_PIN_VAL 0
#if (CONFIG_USB_OTG_FS_ID_PIN_VAL == 0)
#define CONFIG_USB_OTG_FS_ID_DEF 0
#elif (CONFIG_USB_OTG_FS_ID_PIN_VAL == 1)
#define CONFIG_USB_OTG_FS_ID_DEF 1
#define CONFIG_USB_OTG_FS_ID_PORT GPIOA
#define CONFIG_USB_OTG_FS_ID_PIN GPIO_PIN_10
#define CONFIG_USB_OTG_FS_ID_AF GPIO_AF10_OTG_FS
#endif /* CONFIG_USB_OTG_FS_ID_PIN_VAL */
//      <o> USB OTG FS VBUS Pin <0=>NC <1=>PA9
#define CONFIG_USB_OTG_FS_VBUS_PIN_VAL 0
#if (CONFIG_USB_OTG_FS_VBUS_PIN_VAL == 0)
#define CONFIG_USB_OTG_FS_VBUS_DEF 0
#elif (CONFIG_USB_OTG_FS_VBUS_PIN_VAL == 1)
#define CONFIG_USB_OTG_FS_VBUS_DEF 1
#define CONFIG_USB_OTG_FS_VBUS_PORT GPIOA
#define CONFIG_USB_OTG_FS_VBUS_PIN GPIO_PIN_9
#define CONFIG_USB_OTG_FS_VBUS_AF GPIO_AF10_OTG_FS
#endif /* CONFIG_USB_OTG_FS_VBUS_PIN_VAL */
//      <o> USB OTG FS SOF Output Pin <0=>NC <1=>PA8
#define CONFIG_USB_OTG_FS_SOF_PIN_VAL 0
#if (CONFIG_USB_OTG_FS_SOF_PIN_VAL == 0)
#define CONFIG_USB_OTG_FS_SOF_DEF 0
#elif (CONFIG_USB_OTG_FS_SOF_PIN_VAL == 1)
#define CONFIG_USB_OTG_FS_SOF_DEF 1
#define CONFIG_USB_OTG_FS_SOF_PORT GPIOA
#define CONFIG_USB_OTG_FS_SOF_PIN GPIO_PIN_8
#define CONFIG_USB_OTG_FS_SOF_AF GPIO_AF10_OTG_FS
#endif /* CONFIG_USB_OTG_FS_SOF_PIN_VAL */

//      <e> Device
//      <i> Enable Device
#define CONFIG_USB_OTG_FS_DEVICE 0
//          <q> Enable VBUS Sensing
//          <i> Enable VBUS Sensing
#define CONFIG_USB_OTG_FS_VBUS_SENSING 0
//      </e>

//      <e> Host
//      <i> Enable Host
#define CONFIG_USB_OTG_FS_HOST 0

//          <e> VBUS Power Pin
//          <i> Configure Pin to drive external VBUS switch
//          <i> GPIO Port (x = A..H, y = 0..15) or (x = I, y = 0..11)
//              <o1> Active State <0=>Low <1=>High
//              <i> Select active state
//              <o2> Port <0=>GPIOA <1=>GPIOB <2=>GPIOC <3=>GPIOD
//                        <4=>GPIOE <5=>GPIOF <6=>GPIOG <7=>GPIOH <8=>GPIOI
//              <i> Select GPIO port
//              <o3> Pin <0-15>
//              <i> Select GPIO pin
//          </e>
#define CONFIG_USB_OTG_FS_VBUS_POWER 0
#define CONFIG_USB_OTG_FS_VBUS_POWER_ACTIVE 0
#define CONFIG_USB_OTG_FS_VBUS_POWER_PORT GPIO_PORT(0)
#define CONFIG_USB_OTG_FS_VBUS_POWER_PIN 0

//          <e> Overcurrent Detection Pin
//          <i> Configure Pin to detect overcurrent condition
//          <i> GPIO Port (x = A..H, y = 0..15) or (x = I, y = 0..11)
//              <o1> Active State <0=>Low <1=>High
//              <i> Select active state
//              <o2> Port <0=>GPIOA <1=>GPIOB <2=>GPIOC <3=>GPIOD
//                        <4=>GPIOE <5=>GPIOF <6=>GPIOG <7=>GPIOH <8=>GPIOI
//              <i> Select GPIO port
//              <o3> Pin <0-15>
//              <i> Select GPIO pin
//          </e>
#define CONFIG_USB_OTG_FS_OVERCURRENT 0
#define CONFIG_USB_OTG_FS_OVERCURRENT_ACTIVE 0
#define CONFIG_USB_OTG_FS_OVERCURRENT_PORT GPIO_PORT(0)
#define CONFIG_USB_OTG_FS_OVERCURRENT_PIN 0
//      </e>
// </e>

// <e> USB OTG HS (USB Number 2)
// <i> Configuration settings for OMNI Driver USB OTG HS
#define CONFIG_USB_OTG_HS 0
//      <o> PHY <0=>On-Chip Full-Speed PHY <1=>External ULPI PHY
#define CONFIG_USB_OTG_HS_PHY 0
//      <q> DMA
//      <i> Use dedicated DMA for transfers
//      <i> If DMA is used all transfers data buffers must be 32-bit aligned
#define CONFIG_USB_OTG_HS_DMA 0
//      <o> USB OTG HS DM Pin <0=>PB14
#define CONFIG_USB_OTG_HS_DM_PIN_VAL 0
#if (CONFIG_USB_OTG_HS_DM_PIN_VAL == 0)
#define CONFIG_USB_OTG_HS_DM_DEF 1
#define CONFIG_USB_OTG_HS_DM_PORT GPIOB
#define CONFIG_USB_OTG_HS_DM_PIN GPIO_PIN_14
#define CONFIG_USB_OTG_HS_DM_AF GPIO_AF10_OTG_HS
#endif /* CONFIG_USB_OTG_HS_DM_PIN_VAL */
//      <o> USB OTG HS DP Pin <0=>PB15
#define CONFIG_USB_OTG_HS_DP_PIN_VAL 0
#if (CONFIG_USB_OTG_HS_DP_PIN_VAL == 0)
#define CONFIG_USB_OTG_HS_DP_DEF 1
#define CONFIG_USB_OTG_HS_DP_PORT GPIOB
#define CONFIG_USB_OTG_HS_DP_PIN GPIO_PIN_15
#define CONFIG_USB_OTG_HS_DP_AF GPIO_AF10_OTG_HS
#endif /* CONFIG_USB_OTG_HS_DP_PIN_VAL */
//      <o> USB OTG HS ID Pin <0=>NC <1=>PB12
#define CONFIG_USB_OTG_HS_ID_PIN_VAL 0
#if (CONFIG_USB_OTG_HS_ID_PIN_VAL == 0)
#define CONFIG_USB_OTG_HS_ID_DEF 0
#elif (CONFIG_USB_OTG_HS_ID_PIN_VAL == 1)
#define CONFIG_USB_OTG_HS_ID_DEF 1
#define CONFIG_USB_OTG_HS_ID_PORT GPIOB
#define CONFIG_USB_OTG_HS_ID_PIN GPIO_PIN_12
#define CONFIG_USB_OTG_HS_ID_AF GPIO_AF10_OTG_HS
#endif /* CONFIG_USB_OTG_HS_ID_PIN_VAL */
//      <o> USB OTG HS VBUS Pin <0=>NC <1=>PB13
#define CONFIG_USB_OTG_HS_VBUS_PIN_VAL 0
#if (CONFIG_USB_OTG_HS_VBUS_PIN_VAL == 0)
#define CONFIG_USB_OTG_HS_VBUS_DEF 0
#elif (CONFIG_USB_OTG_HS_VBUS_PIN_VAL == 1)
#define CONFIG_USB_OTG_HS_VBUS_DEF 1
#define CONFIG_USB_OTG_HS_VBUS_PORT GPIOB
#define CONFIG_USB_OTG_HS_VBUS_PIN GPIO_PIN_13
#endif /* CONFIG_USB_OTG_HS_VBUS_PIN_VAL */
//      <o> USB OTG HS SOF Output Pin <0=>NC <1=>PA4
#define CONFIG_USB_OTG_HS_SOF_PIN_VAL 0
#if (CONFIG_USB_OTG_HS_SOF_PIN_VAL == 0)
#define CONFIG_USB_OTG_HS_SOF_DEF 0
#elif (CONFIG_USB_OTG_HS_SOF_PIN_VAL == 1)
#define CONFIG_USB_OTG_HS_SOF_DEF 1
#define CONFIG_USB_OTG_HS_SOF_PORT GPIOA
#define CONFIG_USB_OTG_HS_SOF_PIN GPIO_PIN_4
#define CONFIG_USB_OTG_HS_SOF_AF GPIO_AF12_OTG_HS_FS
#endif /* CONFIG_USB_OTG_HS_SOF_PIN_VAL */

// <h> External ULPI Pins
//      <o> ULPI CK Pin <0=>PA5
#define CONFIG_USB_OTG_HS_ULPI_CK_PIN_VAL 0
#if (CONFIG_USB_OTG_HS_ULPI_CK_PIN_VAL == 0)
#define CONFIG_USB_OTG_HS_ULPI_CK_PORT GPIOA
#define CONFIG_USB_OTG_HS_ULPI_CK_PIN GPIO_PIN_5
#define CONFIG_USB_OTG_HS_ULPI_CK_AF GPIO_AF10_OTG_HS
#endif /* CONFIG_USB_OTG_HS_ULPI_CK_PIN_VAL */
//      <o> ULPI STP Pin <0=>PC0
#define CONFIG_USB_OTG_HS_ULPI_STP_PIN_VAL 0
#if (CONFIG_USB_OTG_HS_ULPI_STP_PIN_VAL == 0)
#define CONFIG_USB_OTG_HS_ULPI_STP_PORT GPIOC
#define CONFIG_USB_OTG_HS_ULPI_STP_PIN GPIO_PIN_0
#define CONFIG_USB_OTG_HS_ULPI_STP_AF GPIO_AF10_OTG_HS
#endif /* CONFIG_USB_OTG_HS_ULPI_STP_PIN_VAL */
//      <o> ULPI DIR Pin <0=>PC2 <1=>PI11
#define CONFIG_USB_OTG_HS_ULPI_DIR_PIN_VAL 0
#if (CONFIG_USB_OTG_HS_ULPI_DIR_PIN_VAL == 0)
#define CONFIG_USB_OTG_HS_ULPI_DIR_PORT GPIOC
#define CONFIG_USB_OTG_HS_ULPI_DIR_PIN GPIO_PIN_2
#define CONFIG_USB_OTG_HS_ULPI_DIR_AF GPIO_AF10_OTG_HS
#elif (CONFIG_USB_OTG_HS_ULPI_DIR_PIN_VAL == 1)
#define CONFIG_USB_OTG_HS_ULPI_DIR_PORT GPIOI
#define CONFIG_USB_OTG_HS_ULPI_DIR_PIN GPIO_PIN_11
#define CONFIG_USB_OTG_HS_ULPI_DIR_AF GPIO_AF10_OTG_HS
#endif /* CONFIG_USB_OTG_HS_ULPI_DIR_PIN_VAL */
//      <o> ULPI NXT Pin <0=>PC3 <1=>PH4
#define CONFIG_USB_OTG_HS_ULPI_NXT_PIN_VAL 0
#if (CONFIG_USB_OTG_HS_ULPI_NXT_PIN_VAL == 0)
#define CONFIG_USB_OTG_HS_ULPI_NXT_PORT GPIOC
#define CONFIG_USB_OTG_HS_ULPI_NXT_PIN GPIO_PIN_3
#define CONFIG_USB_OTG_HS_ULPI_NXT_AF GPIO_AF10_OTG_HS
#elif (CONFIG_USB_OTG_HS_ULPI_NXT_PIN_VAL == 1)
#define CONFIG_USB_OTG_HS_ULPI_NXT_PORT GPIOH
#define CONFIG_USB_OTG_HS_ULPI_NXT_PIN GPIO_PIN_4
#define CONFIG_USB_OTG_HS_ULPI_NXT_AF GPIO_AF10_OTG_HS
#endif /* CONFIG_USB_OTG_HS_ULPI_NXT_PIN_VAL */
//      <o> ULPI D0 Pin <0=>PA3
#define CONFIG_USB_OTG_HS_ULPI_D0_PIN_VAL 0
#if (CONFIG_USB_OTG_HS_ULPI_D0_PIN_VAL == 0)
#define CONFIG_USB_OTG_HS_ULPI_D0_PORT GPIOA
#define CONFIG_USB_OTG_HS_ULPI_D0_PIN GPIO_PIN_3
#define CONFIG_USB_OTG_HS_ULPI_D0_AF GPIO_AF10_OTG_HS
#endif /* CONFIG_USB_OTG_HS_ULPI_D0_PIN_VAL */
//      <o> ULPI D1 Pin <0=>PB0
#define CONFIG_USB_OTG_HS_ULPI_D1_PIN_VAL 0
#if (CONFIG_USB_OTG_HS_ULPI_D1_PIN_VAL == 0)
#define CONFIG_USB_OTG_HS_ULPI_D1_PORT GPIOB
#define CONFIG_USB_OTG_HS_ULPI_D1_PIN GPIO_PIN_0
#define CONFIG_USB_OTG_HS_ULPI_D1_AF GPIO_AF10_OTG_HS
#endif /* CONFIG_USB_OTG_HS_ULPI_D1_PIN_VAL */
//      <o> ULPI D2 Pin <0=>PB1
#define CONFIG_USB_OTG_HS_ULPI_D2_PIN_VAL 0
#if (CONFIG_USB_OTG_HS_ULPI_D2_PIN_VAL == 0)
#define CONFIG_USB_OTG_HS_ULPI_D2_PORT GPIOB
#define CONFIG_USB_OTG_HS_ULPI_D2_PIN GPIO_PIN_1
#define CONFIG_USB_OTG_HS_ULPI_D2_AF GPIO_AF10_OTG_HS
#endif /* CONFIG_USB_OTG_HS_ULPI_D2_PIN_VAL */
//      <o> ULPI D3 Pin <0=>PB10
#define CONFIG_USB_OTG_HS_ULPI_D3_PIN_VAL 0
#if (CONFIG_USB_OTG_HS_ULPI_D3_PIN_VAL == 0)
#define CONFIG_USB_OTG_HS_ULPI_D3_PORT GPIOB
#define CONFIG_USB_OTG_HS_ULPI_D3_PIN GPIO_PIN_10
#define CONFIG_USB_OTG_HS_ULPI_D3_AF GPIO_AF10_OTG_HS
#endif /* CONFIG_USB_OTG_HS_ULPI_D3_PIN_VAL */
//      <o> ULPI D4 Pin <0=>PB11
#define CONFIG_USB_OTG_HS_ULPI_D4_PIN_VAL 0
#if (CONFIG_USB_OTG_HS_ULPI_D4_PIN_VAL == 0)
#define CONFIG_USB_OTG_HS_ULPI_D4_PORT GPIOB
#define CONFIG_USB_OTG_HS_ULPI_D4_PIN GPIO_PIN_11
#define CONFIG_USB_OTG_HS_ULPI_D4_AF GPIO_AF10_OTG_HS
#endif /* CONFIG_USB_OTG_HS_ULPI_D4_PIN_VAL */
//      <o> ULPI D5 Pin <0=>PB12
#define CONFIG_USB_OTG_HS_ULPI_D5_PIN_VAL 0
#if (CONFIG_USB_OTG_HS_ULPI_D5_PIN_VAL == 0)
#define CONFIG_USB_OTG_HS_ULPI_D5_PORT GPIOB
#define CONFIG_USB_OTG_HS_ULPI_D5_PIN GPIO_PIN_12
#define CONFIG_USB_OTG_HS_ULPI_D5_AF GPIO_AF10_OTG_HS
#endif /* CONFIG_USB_OTG_HS_ULPI_D5_PIN_VAL */
//      <o> ULPI D6 Pin <0=>PB13
#define CONFIG_USB_OTG_HS_ULPI_D6_PIN_VAL 0
#if (CONFIG_USB_OTG_HS_ULPI_D6_PIN_VAL == 0)
#define CONFIG_USB_OTG_HS_ULPI_D6_PORT GPIOB
#define CONFIG_USB_OTG_HS_ULPI_D6_PIN GPIO_PIN_13
#define CONFIG_USB_OTG_HS_ULPI_D6_AF GPIO_AF10_OTG_HS
#endif /* CONFIG_USB_OTG_HS_ULPI_D6_PIN_VAL */
//      <o> ULPI D7 Pin <0=>PB5
#define CONFIG_USB_OTG_HS_ULPI_D7_PIN_VAL 0
#if (CONFIG_USB_OTG_HS_ULPI_D7_PIN_VAL == 0)
#define CONFIG_USB_OTG_HS_ULPI_D7_PORT GPIOB
#define CONFIG_USB_OTG_HS_ULPI_D7_PIN GPIO_PIN_5
#define CONFIG_USB_OTG_HS_ULPI_D7_AF GPIO_AF10_OTG_HS
#endif /* CONFIG_USB_OTG_HS_ULPI_D7_PIN_VAL */
// </h>

//      <e> Device
//      <i> Enable Device
#define CONFIG_USB_OTG_HS_DEVICE 0
//          <q> Enable VBUS Sensing
//          <i> Enable VBUS Sensing
#define CONFIG_USB_OTG_HS_VBUS_SENSING 0
//      </e>

//      <e> Host
//      <i> Enable Host
#define CONFIG_USB_OTG_HS_HOST 0

//          <e> VBUS Power Pin
//          <i> Configure Pin to drive external VBUS switch
//          <i> GPIO Port (x = A..H, y = 0..15) or (x = I, y = 0..11)
//              <o1> Active State <0=>Low <1=>High
//              <i> Select active state
//              <o2> Port <0=>GPIOA <1=>GPIOB <2=>GPIOC <3=>GPIOD
//                        <4=>GPIOE <5=>GPIOF <6=>GPIOG <7=>GPIOH <8=>GPIOI
//              <i> Select GPIO port
//              <o3> Pin <0-15>
//              <i> Select GPIO pin
//          </e>
#define CONFIG_USB_OTG_HS_VBUS_POWER 0
#define CONFIG_USB_OTG_HS_VBUS_POWER_ACTIVE 0
#define CONFIG_USB_OTG_HS_VBUS_POWER_PORT GPIO_PORT(0)
#define CONFIG_USB_OTG_HS_VBUS_POWER_PIN 0

//          <e> Overcurrent Detection Pin
//          <i> Configure Pin to detect overcurrent condition
//          <i> GPIO Port (x = A..H, y = 0..15) or (x = I, y = 0..11)
//              <o1> Active State <0=>Low <1=>High
//              <i> Select active state
//              <o2> Port <0=>GPIOA <1=>GPIOB <2=>GPIOC <3=>GPIOD
//                        <4=>GPIOE <5=>GPIOF <6=>GPIOG <7=>GPIOH <8=>GPIOI
//              <i> Select GPIO port
//              <o3> Pin <0-15>
//              <i> Select GPIO pin
//          </e>
#define CONFIG_USB_OTG_HS_OVERCURRENT 0
#define CONFIG_USB_OTG_HS_OVERCURRENT_ACTIVE 0
#define CONFIG_USB_OTG_HS_OVERCURRENT_PORT GPIO_PORT(0)
#define CONFIG_USB_OTG_HS_OVERCURRENT_PIN 0
//      </e>
// </e>
// </h>

//-------- <<< end of configuration section >>> --------------------------------

#ifdef __cplusplus
}
#endif

#endif /* OMNI_DEVICE_CFG_H */
