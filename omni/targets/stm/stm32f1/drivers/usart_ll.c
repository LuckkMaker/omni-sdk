/**
  * @file    usart_ll.c
  * @author  LuckkMaker
  * @brief   Low-level USART configuration
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

/* Includes ------------------------------------------------------------------*/
#include "ll/usart_ll.h"
#include "ll/gpio_ll.h"

#if defined(USART1) && (CONFIG_USART_NUM_1 == 1)
#if (CONFIG_USART1_TX_DEF == 1)
static gpio_pin_t usart1_tx_pin = { CONFIG_USART1_TX_PORT, CONFIG_USART1_TX_PIN };
#if (CONFIG_USART1_TX_DMA == 1)
static DMA_HandleTypeDef usart1_tx_dma_handle = {
    .Instance = CONFIG_USART1_TX_DMA_CHANNEL,
    .Init = {
        .Direction = DMA_MEMORY_TO_PERIPH,
        .PeriphInc = DMA_PINC_DISABLE,
        .MemInc = DMA_MINC_ENABLE,
        .PeriphDataAlignment = DMA_PDATAALIGN_BYTE,
        .MemDataAlignment = DMA_MDATAALIGN_BYTE,
        .Mode = DMA_NORMAL,
        .Priority = CONFIG_USART1_TX_DMA_PRIORITY,
    },
};
static dma_dev_t usart1_tx_dma = {
    .handle = &usart1_tx_dma_handle,
    .ins = CONFIG_USART1_TX_DMA_INS,
    .irq_num = CONFIG_USART1_TX_DMA_IRQ_NUM,
    .irq_prio = CONFIG_USART1_TX_DMA_IRQ_PRIO,
};
#endif /* (CONFIG_USART1_TX_DMA == 1) */
#endif /* (CONFIG_USART1_TX_DEF == 1) */
#if (CONFIG_USART1_RX_DEF == 1)
static gpio_pin_t usart1_rx_pin = { CONFIG_USART1_RX_PORT, CONFIG_USART1_RX_PIN };
#if (CONFIG_USART1_RX_DMA == 1)
static DMA_HandleTypeDef usart1_rx_dma_handle = {
    .Instance = CONFIG_USART1_RX_DMA_CHANNEL,
    .Init = {
        .Direction = DMA_PERIPH_TO_MEMORY,
        .PeriphInc = DMA_PINC_DISABLE,
        .MemInc = DMA_MINC_ENABLE,
        .PeriphDataAlignment = DMA_PDATAALIGN_BYTE,
        .MemDataAlignment = DMA_MDATAALIGN_BYTE,
        .Mode = DMA_NORMAL,
        .Priority = CONFIG_USART1_RX_DMA_PRIORITY,
    },
};
static dma_dev_t usart1_rx_dma = {
    .handle = &usart1_rx_dma_handle,
    .ins = CONFIG_USART1_RX_DMA_INS,
    .irq_num = CONFIG_USART1_RX_DMA_IRQ_NUM,
    .irq_prio = CONFIG_USART1_RX_DMA_IRQ_PRIO,
};
#endif /* (CONFIG_USART1_RX_DMA == 1) */
#endif /* (CONFIG_USART1_RX_DEF == 1) */
static UART_HandleTypeDef usart1_handle = {
    .Instance = USART1,
};
static usart_dev_t usart1_dev = {
    .handle = &usart1_handle,
    .irq_num = USART1_IRQn,
    .irq_prio = CONFIG_USART1_IRQ_PRIO,
    .alternate = CONFIG_USART1_AF_REMAP,
#if (CONFIG_USART1_TX_DEF == 1)
    .tx_pin = &usart1_tx_pin,
#endif /* (CONFIG_USART1_TX_DEF == 1) */
#if (CONFIG_USART1_RX_DEF == 1)
    .rx_pin = &usart1_rx_pin,
#endif /* (CONFIG_USART1_RX_DEF == 1) */
#if (CONFIG_USART1_TX_DMA == 1)
    .dma_tx = &usart1_tx_dma,
#endif /* (CONFIG_USART1_TX_DMA == 1) */
#if (CONFIG_USART1_RX_DMA == 1)
    .dma_rx = &usart1_rx_dma,
#endif /* (CONFIG_USART1_RX_DMA == 1) */
};
#endif /* USART1 && (CONFIG_USART_NUM_1 == 1) */
#if defined(USART2) && (CONFIG_USART_NUM_2 == 1)
#if (CONFIG_USART2_TX_DEF == 1)
static gpio_pin_t usart2_tx_pin = { CONFIG_USART2_TX_PORT, CONFIG_USART2_TX_PIN };
#if (CONFIG_USART2_TX_DMA == 1)
static dma_dev_t usart2_tx_dma = {
    .ins = CONFIG_USART2_TX_DMA_NUMBER,
    .id = CONFIG_USART2_TX_DMA_CHANNEL,
    .irq_num = CONFIG_USART2_TX_DMA_IRQ_NUM,
    .irq_prio = CONFIG_USART2_TX_DMA_IRQ_PRIO,
    .mode = LL_DMA_MODE_NORMAL,
    .direction = LL_DMA_DIRECTION_MEMORY_TO_PERIPH,
    .priority = CONFIG_USART2_TX_DMA_PRIORITY,
};
#endif /* (CONFIG_USART2_TX_DMA == 1) */
#endif /* (CONFIG_USART2_TX_DEF == 1) */
#if (CONFIG_USART2_RX_DEF == 1)
static gpio_pin_t usart2_rx_pin = { CONFIG_USART2_RX_PORT, CONFIG_USART2_RX_PIN };
#if (CONFIG_USART2_RX_DMA == 1)
static dma_dev_t usart2_rx_dma = {
    .ins = CONFIG_USART2_RX_DMA_NUMBER,
    .id = CONFIG_USART2_RX_DMA_CHANNEL,
    .irq_num = CONFIG_USART2_RX_DMA_IRQ_NUM,
    .irq_prio = CONFIG_USART2_RX_DMA_IRQ_PRIO,
    .mode = LL_DMA_MODE_NORMAL,
    .direction = LL_DMA_DIRECTION_PERIPH_TO_MEMORY,
    .priority = CONFIG_USART2_RX_DMA_PRIORITY,
};
#endif /* (CONFIG_USART2_RX_DMA == 1) */
#endif /* (CONFIG_USART2_RX_DEF == 1) */
static usart_dev_t usart2_dev = {
    .ins = USART2,
    .irq_num = USART2_IRQn,
    .irq_prio = CONFIG_USART2_IRQ_PRIO,
    .alternate = CONFIG_USART2_AF_REMAP,
#if (CONFIG_USART2_TX_DEF == 1)
    .tx_pin = &usart2_tx_pin,
#endif /* (CONFIG_USART2_TX_DEF == 1) */
#if (CONFIG_USART2_RX_DEF == 1)
    .rx_pin = &usart2_rx_pin,
#endif /* (CONFIG_USART2_RX_DEF == 1) */
#if (CONFIG_USART2_TX_DMA == 1)
    .dma_tx = &usart2_tx_dma,
#endif /* (CONFIG_USART2_TX_DMA == 1) */
#if (CONFIG_USART2_RX_DMA == 1)
    .dma_rx = &usart2_rx_dma,
#endif /* (CONFIG_USART2_RX_DMA == 1) */
};
#endif /* USART2 && (CONFIG_USART_NUM_2 == 1) */
#if defined(USART3) && (CONFIG_USART_NUM_3 == 1)
#if (CONFIG_USART3_TX_DEF == 1)
static gpio_pin_t usart3_tx_pin = { CONFIG_USART3_TX_PORT, CONFIG_USART3_TX_PIN };
#if (CONFIG_USART3_TX_DMA == 1)
static dma_dev_t usart3_tx_dma = {
    .ins = CONFIG_USART3_TX_DMA_NUMBER,
    .id = CONFIG_USART3_TX_DMA_CHANNEL,
    .irq_num = CONFIG_USART3_TX_DMA_IRQ_NUM,
    .irq_prio = CONFIG_USART3_TX_DMA_IRQ_PRIO,
    .mode = LL_DMA_MODE_NORMAL,
    .direction = LL_DMA_DIRECTION_MEMORY_TO_PERIPH,
    .priority = CONFIG_USART3_TX_DMA_PRIORITY,
};
#endif /* (CONFIG_USART3_TX_DMA == 1) */
#endif /* (CONFIG_USART3_TX_DEF == 1) */
#if (CONFIG_USART3_RX_DEF == 1)
static gpio_pin_t usart3_rx_pin = { CONFIG_USART3_RX_PORT, CONFIG_USART3_RX_PIN };
#if (CONFIG_USART3_RX_DMA == 1)
static dma_dev_t usart3_rx_dma = {
    .ins = CONFIG_USART3_RX_DMA_NUMBER,
    .id = CONFIG_USART3_RX_DMA_CHANNEL,
    .irq_num = CONFIG_USART3_RX_DMA_IRQ_NUM,
    .irq_prio = CONFIG_USART3_RX_DMA_IRQ_PRIO,
    .mode = LL_DMA_MODE_NORMAL,
    .direction = LL_DMA_DIRECTION_PERIPH_TO_MEMORY,
    .priority = CONFIG_USART3_RX_DMA_PRIORITY,
};
#endif /* (CONFIG_USART3_RX_DMA == 1) */
#endif /* (CONFIG_USART3_RX_DEF == 1) */
static usart_dev_t usart3_dev = {
    .ins = USART3,
    .irq_num = USART3_IRQn,
    .irq_prio = CONFIG_USART3_IRQ_PRIO,
    .alternate = CONFIG_USART3_AF_REMAP,
#if (CONFIG_USART3_TX_DEF == 1)
    .tx_pin = &usart3_tx_pin,
#endif /* (CONFIG_USART3_TX_DEF == 1) */
#if (CONFIG_USART3_RX_DEF == 1)
    .rx_pin = &usart3_rx_pin,
#endif /* (CONFIG_USART3_RX_DEF == 1) */
#if (CONFIG_USART3_TX_DMA == 1)
    .dma_tx = &usart3_tx_dma,
#endif /* (CONFIG_USART3_TX_DMA == 1) */
#if (CONFIG_USART3_RX_DMA == 1)
    .dma_rx = &usart3_rx_dma,
#endif /* (CONFIG_USART3_RX_DMA == 1) */
};
#endif /* USART3 && (CONFIG_USART_NUM_3 == 1) */
#if defined(UART4) && (CONFIG_USART_NUM_4 == 1)
#if (CONFIG_USART4_TX_DEF == 1)
static gpio_pin_t usart4_tx_pin = { CONFIG_USART4_TX_PORT, CONFIG_USART4_TX_PIN };
#if (CONFIG_USART4_TX_DMA == 1)
static dma_dev_t usart4_tx_dma = {
    .ins = CONFIG_USART4_TX_DMA_NUMBER,
    .id = CONFIG_USART4_TX_DMA_CHANNEL,
    .irq_num = CONFIG_USART4_TX_DMA_IRQ_NUM,
    .irq_prio = CONFIG_USART4_TX_DMA_IRQ_PRIO,
    .mode = LL_DMA_MODE_NORMAL,
    .direction = LL_DMA_DIRECTION_MEMORY_TO_PERIPH,
    .priority = CONFIG_USART4_TX_DMA_PRIORITY,
};
#endif /* (CONFIG_USART4_TX_DMA == 1) */
#endif /* (CONFIG_USART4_TX_DEF == 1) */
#if (CONFIG_USART4_RX_DEF == 1)
static gpio_pin_t usart4_rx_pin = { CONFIG_USART4_RX_PORT, CONFIG_USART4_RX_PIN };
#if (CONFIG_USART4_RX_DMA == 1)
static dma_dev_t usart4_rx_dma = {
    .ins = CONFIG_USART4_RX_DMA_NUMBER,
    .id = CONFIG_USART4_RX_DMA_CHANNEL,
    .irq_num = CONFIG_USART4_RX_DMA_IRQ_NUM,
    .irq_prio = CONFIG_USART4_RX_DMA_IRQ_PRIO,
    .mode = LL_DMA_MODE_NORMAL,
    .direction = LL_DMA_DIRECTION_PERIPH_TO_MEMORY,
    .priority = CONFIG_USART4_RX_DMA_PRIORITY,
};
#endif /* (CONFIG_USART4_RX_DMA == 1) */
#endif /* (CONFIG_USART4_RX_DEF == 1) */
static usart_dev_t usart4_dev = {
    .ins = UART4,
    .irq_num = UART4_IRQn,
    .irq_prio = CONFIG_USART4_IRQ_PRIO,
    .alternate = CONFIG_USART4_AF_REMAP,
#if (CONFIG_USART4_TX_DEF == 1)
    .tx_pin = &usart4_tx_pin,
#endif /* (CONFIG_USART4_TX_DEF == 1) */
#if (CONFIG_USART4_RX_DEF == 1)
    .rx_pin = &usart4_rx_pin,
#endif /* (CONFIG_USART4_RX_DEF == 1) */
#if (CONFIG_USART4_TX_DMA == 1)
    .dma_tx = &usart4_tx_dma,
#endif /* (CONFIG_USART4_TX_DMA == 1) */
#if (CONFIG_USART4_RX_DMA == 1)
    .dma_rx = &usart4_rx_dma,
#endif /* (CONFIG_USART4_RX_DMA == 1) */
};
#endif /* UART4 && (CONFIG_USART_NUM_4 == 1) */
#if defined(UART5) && (CONFIG_USART_NUM_5 == 1)
#if (CONFIG_USART5_TX_DEF == 1)
static gpio_pin_t usart5_tx_pin = { CONFIG_USART5_TX_PORT, CONFIG_USART5_TX_PIN };
#if (CONFIG_USART5_TX_DMA == 1)
static dma_dev_t usart5_tx_dma = {
    .ins = CONFIG_USART5_TX_DMA_NUMBER,
    .id = CONFIG_USART5_TX_DMA_CHANNEL,
    .irq_num = CONFIG_USART5_TX_DMA_IRQ_NUM,
    .irq_prio = CONFIG_USART5_TX_DMA_IRQ_PRIO,
    .mode = LL_DMA_MODE_NORMAL,
    .direction = LL_DMA_DIRECTION_MEMORY_TO_PERIPH,
    .priority = CONFIG_USART5_TX_DMA_PRIORITY,
};
#endif /* (CONFIG_USART5_TX_DMA == 1) */
#endif /* (CONFIG_USART5_TX_DEF == 1) */
#if (CONFIG_USART5_RX_DEF == 1)
static gpio_pin_t usart5_rx_pin = { CONFIG_USART5_RX_PORT, CONFIG_USART5_RX_PIN };
#if (CONFIG_USART5_RX_DMA == 1)
static dma_dev_t usart5_rx_dma = {
    .ins = CONFIG_USART5_RX_DMA_NUMBER,
    .id = CONFIG_USART5_RX_DMA_CHANNEL,
    .irq_num = CONFIG_USART5_RX_DMA_IRQ_NUM,
    .irq_prio = CONFIG_USART5_RX_DMA_IRQ_PRIO,
    .mode = LL_DMA_MODE_NORMAL,
    .direction = LL_DMA_DIRECTION_PERIPH_TO_MEMORY,
    .priority = CONFIG_USART5_RX_DMA_PRIORITY,
};
#endif /* (CONFIG_USART5_RX_DMA == 1) */
#endif /* (CONFIG_USART5_RX_DEF == 1) */
static usart_dev_t usart5_dev = {
    .ins = UART5,
    .irq_num = UART5_IRQn,
    .irq_prio = CONFIG_USART5_IRQ_PRIO,
    .alternate = CONFIG_USART5_AF_REMAP,
#if (CONFIG_USART5_TX_DEF == 1)
    .tx_pin = &usart5_tx_pin,
#endif /* (CONFIG_USART5_TX_DEF == 1) */
#if (CONFIG_USART5_RX_DEF == 1)
    .rx_pin = &usart5_rx_pin,
#endif /* (CONFIG_USART5_RX_DEF == 1) */
#if (CONFIG_USART5_TX_DMA == 1)
    .dma_tx = &usart5_tx_dma,
#endif /* (CONFIG_USART5_TX_DMA == 1) */
#if (CONFIG_USART5_RX_DMA == 1)
    .dma_rx = &usart5_rx_dma,
#endif /* (CONFIG_USART5_RX_DMA == 1) */
};
#endif /* UART5 && (CONFIG_USART_NUM_5 == 1) */

/**
 * @brief Get USART device information
 * 
 * @param usart_num USART port number
 * @return USART device information
 */
usart_dev_t* usart_ll_get_dev(usart_num_t usart_num) {
    switch (usart_num) {
#if (CONFIG_USART_NUM_1 == 1)
        case USART_NUM_1:
            return &usart1_dev;
#endif /* CONFIG_USART_NUM_1 */

#if (CONFIG_USART_NUM_2 == 1)
        case USART_NUM_2:
            return &usart2_dev;
#endif /* CONFIG_USART_NUM_2 */

#if (CONFIG_USART_NUM_3 == 1)
        case USART_NUM_3:
            return &usart3_dev;
#endif /* CONFIG_USART_NUM_3 */

#if (CONFIG_USART_NUM_4 == 1)
        case USART_NUM_4:
            return &usart4_dev;
#endif /* CONFIG_USART_NUM_4 */

#if (CONFIG_USART_NUM_5 == 1)
        case USART_NUM_5:
            return &usart5_dev;
#endif /* CONFIG_USART_NUM_5 */

#if (CONFIG_USART_NUM_6 == 1)
        case USART_NUM_6:
            return &usart6_dev;
#endif /* CONFIG_USART_NUM_6 */

#if (CONFIG_USART_NUM_7 == 1)
        case USART_NUM_7:
            return &uart7_dev;
#endif /* CONFIG_USART_NUM_7 */

#if (CONFIG_USART_NUM_8 == 1)
        case USART_NUM_8:
            return &uart8_dev;
#endif /* CONFIG_USART_NUM_8 */

#if (CONFIG_USART_NUM_9 == 1)
        case USART_NUM_9:
            return &uart9_dev;
#endif /* CONFIG_USART_NUM_9 */

#if (CONFIG_USART_NUM_10 == 1)
        case USART_NUM_10:
            return &uart10_dev;
#endif /* CONFIG_USART_NUM_10 */

        default:
            return NULL;
    }

    return NULL;
}
