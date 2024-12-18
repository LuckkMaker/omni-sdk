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

#if defined(USART1) && (CONFIG_USART_NUM_1 == 1)
#if (CONFIG_USART1_TX_DEF == 1)
static gpio_pin_t usart1_tx_pin = { CONFIG_USART1_TX_PORT, CONFIG_USART1_TX_PIN, CONFIG_USART1_TX_AF };
#if (CONFIG_USART1_TX_DMA == 1)
static DMA_HandleTypeDef usart1_tx_dma_handle = {
    .Instance = CONFIG_USART1_TX_DMA_STREAM,
    .Init = {
        .Request = DMA_REQUEST_USART1_TX,
        .Direction = DMA_MEMORY_TO_PERIPH,
        .PeriphInc = DMA_PINC_DISABLE,
        .MemInc = DMA_MINC_ENABLE,
        .PeriphDataAlignment = DMA_PDATAALIGN_BYTE,
        .MemDataAlignment = DMA_MDATAALIGN_BYTE,
        .Mode = DMA_NORMAL,
        .Priority = CONFIG_USART1_TX_DMA_PRIORITY,
        .FIFOMode = DMA_FIFOMODE_DISABLE,
        .FIFOThreshold = DMA_FIFO_THRESHOLD_FULL,
        .MemBurst = DMA_MBURST_SINGLE,
        .PeriphBurst = DMA_PBURST_SINGLE,
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
static gpio_pin_t usart1_rx_pin = { CONFIG_USART1_RX_PORT, CONFIG_USART1_RX_PIN, CONFIG_USART1_RX_AF };
#if (CONFIG_USART1_RX_DMA == 1)
static DMA_HandleTypeDef usart1_rx_dma_handle = {
    .Instance = CONFIG_USART1_RX_DMA_STREAM,
    .Init = {
        .Request = DMA_REQUEST_USART1_RX,
        .Direction = DMA_PERIPH_TO_MEMORY,
        .PeriphInc = DMA_PINC_DISABLE,
        .MemInc = DMA_MINC_ENABLE,
        .PeriphDataAlignment = DMA_PDATAALIGN_BYTE,
        .MemDataAlignment = DMA_MDATAALIGN_BYTE,
        .Mode = DMA_NORMAL,
        .Priority = CONFIG_USART1_RX_DMA_PRIORITY,
        .FIFOMode = DMA_FIFOMODE_DISABLE,
        .FIFOThreshold = DMA_FIFO_THRESHOLD_FULL,
        .MemBurst = DMA_MBURST_SINGLE,
        .PeriphBurst = DMA_PBURST_SINGLE,
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
    .Instance = USART1
};
static usart_dev_t usart1_dev = {
    .handle = &usart1_handle,
    .irq_num = USART1_IRQn,
    .irq_prio = CONFIG_USART1_IRQ_PRIO,
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
static gpio_pin_t usart2_tx_pin = { CONFIG_USART2_TX_PORT, CONFIG_USART2_TX_PIN, CONFIG_USART2_TX_AF };
#if (CONFIG_USART2_TX_DMA == 1)
static DMA_HandleTypeDef usart2_tx_dma_handle = {
    .Instance = CONFIG_USART2_TX_DMA_STREAM,
    .Init = {
        .Request = DMA_REQUEST_USART2_TX,
        .Direction = DMA_MEMORY_TO_PERIPH,
        .PeriphInc = DMA_PINC_DISABLE,
        .MemInc = DMA_MINC_ENABLE,
        .PeriphDataAlignment = DMA_PDATAALIGN_BYTE,
        .MemDataAlignment = DMA_MDATAALIGN_BYTE,
        .Mode = DMA_NORMAL,
        .Priority = CONFIG_USART2_TX_DMA_PRIORITY,
        .FIFOMode = DMA_FIFOMODE_DISABLE,
        .FIFOThreshold = DMA_FIFO_THRESHOLD_FULL,
        .MemBurst = DMA_MBURST_SINGLE,
        .PeriphBurst = DMA_PBURST_SINGLE,
    },
};
static dma_dev_t usart2_tx_dma = {
    .handle = &usart2_tx_dma_handle,
    .ins = CONFIG_USART2_TX_DMA_INS,
    .irq_num = CONFIG_USART2_TX_DMA_IRQ_NUM,
    .irq_prio = CONFIG_USART2_TX_DMA_IRQ_PRIO,
};
#endif /* (CONFIG_USART2_TX_DMA == 1) */
#endif /* (CONFIG_USART2_TX_DEF == 1) */
#if (CONFIG_USART2_RX_DEF == 1)
static gpio_pin_t usart2_rx_pin = { CONFIG_USART2_RX_PORT, CONFIG_USART2_RX_PIN, CONFIG_USART2_RX_AF };
#if (CONFIG_USART2_RX_DMA == 1)
static DMA_HandleTypeDef usart2_rx_dma_handle = {
    .Instance = CONFIG_USART2_RX_DMA_STREAM,
    .Init = {
        .Request = DMA_REQUEST_USART2_RX,
        .Direction = DMA_PERIPH_TO_MEMORY,
        .PeriphInc = DMA_PINC_DISABLE,
        .MemInc = DMA_MINC_ENABLE,
        .PeriphDataAlignment = DMA_PDATAALIGN_BYTE,
        .MemDataAlignment = DMA_MDATAALIGN_BYTE,
        .Mode = DMA_NORMAL,
        .Priority = CONFIG_USART2_RX_DMA_PRIORITY,
        .FIFOMode = DMA_FIFOMODE_DISABLE,
        .FIFOThreshold = DMA_FIFO_THRESHOLD_FULL,
        .MemBurst = DMA_MBURST_SINGLE,
        .PeriphBurst = DMA_PBURST_SINGLE,
    },
};
static dma_dev_t usart2_rx_dma = {
    .handle = &usart2_rx_dma_handle,
    .ins = CONFIG_USART2_RX_DMA_INS,
    .irq_num = CONFIG_USART2_RX_DMA_IRQ_NUM,
    .irq_prio = CONFIG_USART2_RX_DMA_IRQ_PRIO,
};
#endif /* (CONFIG_USART2_RX_DMA == 1) */
#endif /* (CONFIG_USART2_RX_DEF == 1) */
static UART_HandleTypeDef usart2_handle = {
    .Instance = USART2
};
static usart_dev_t usart2_dev = {
    .handle = &usart2_handle,
    .irq_num = USART2_IRQn,
    .irq_prio = CONFIG_USART2_IRQ_PRIO,
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
static gpio_pin_t usart3_tx_pin = { CONFIG_USART3_TX_PORT, CONFIG_USART3_TX_PIN, CONFIG_USART3_TX_AF };
#if (CONFIG_USART3_TX_DMA == 1)
static DMA_HandleTypeDef usart3_tx_dma_handle = {
    .Instance = CONFIG_USART3_TX_DMA_STREAM,
    .Init = {
        .Request = DMA_REQUEST_USART3_TX,
        .Direction = DMA_MEMORY_TO_PERIPH,
        .PeriphInc = DMA_PINC_DISABLE,
        .MemInc = DMA_MINC_ENABLE,
        .PeriphDataAlignment = DMA_PDATAALIGN_BYTE,
        .MemDataAlignment = DMA_MDATAALIGN_BYTE,
        .Mode = DMA_NORMAL,
        .Priority = CONFIG_USART3_TX_DMA_PRIORITY,
        .FIFOMode = DMA_FIFOMODE_DISABLE,
        .FIFOThreshold = DMA_FIFO_THRESHOLD_FULL,
        .MemBurst = DMA_MBURST_SINGLE,
        .PeriphBurst = DMA_PBURST_SINGLE,
    },
};
static dma_dev_t usart3_tx_dma = {
    .handle = &usart3_tx_dma_handle,
    .ins = CONFIG_USART3_TX_DMA_INS,
    .irq_num = CONFIG_USART3_TX_DMA_IRQ_NUM,
    .irq_prio = CONFIG_USART3_TX_DMA_IRQ_PRIO,
};
#endif /* (CONFIG_USART3_TX_DMA == 1) */
#endif /* (CONFIG_USART3_TX_DEF == 1) */
#if (CONFIG_USART3_RX_DEF == 1)
static gpio_pin_t usart3_rx_pin = { CONFIG_USART3_RX_PORT, CONFIG_USART3_RX_PIN, CONFIG_USART3_RX_AF };
#if (CONFIG_USART3_RX_DMA == 1)
static DMA_HandleTypeDef usart3_rx_dma_handle = {
    .Instance = CONFIG_USART3_RX_DMA_STREAM,
    .Init = {
        .Request = DMA_REQUEST_USART3_RX,
        .Direction = DMA_PERIPH_TO_MEMORY,
        .PeriphInc = DMA_PINC_DISABLE,
        .MemInc = DMA_MINC_ENABLE,
        .PeriphDataAlignment = DMA_PDATAALIGN_BYTE,
        .MemDataAlignment = DMA_MDATAALIGN_BYTE,
        .Mode = DMA_NORMAL,
        .Priority = CONFIG_USART3_RX_DMA_PRIORITY,
        .FIFOMode = DMA_FIFOMODE_DISABLE,
        .FIFOThreshold = DMA_FIFO_THRESHOLD_FULL,
        .MemBurst = DMA_MBURST_SINGLE,
        .PeriphBurst = DMA_PBURST_SINGLE,
    },
};
static dma_dev_t usart3_rx_dma = {
    .handle = &usart3_rx_dma_handle,
    .ins = CONFIG_USART3_RX_DMA_INS,
    .irq_num = CONFIG_USART3_RX_DMA_IRQ_NUM,
    .irq_prio = CONFIG_USART3_RX_DMA_IRQ_PRIO,
};
#endif /* (CONFIG_USART3_RX_DMA == 1) */
#endif /* (CONFIG_USART3_RX_DEF == 1) */
static UART_HandleTypeDef usart3_handle = {
    .Instance = USART3
};
static usart_dev_t usart3_dev = {
    .handle = &usart3_handle,
    .irq_num = USART3_IRQn,
    .irq_prio = CONFIG_USART3_IRQ_PRIO,
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
static gpio_pin_t usart4_tx_pin = { CONFIG_USART4_TX_PORT, CONFIG_USART4_TX_PIN, CONFIG_USART4_TX_AF };
#if (CONFIG_USART4_TX_DMA == 1)
static DMA_HandleTypeDef usart4_tx_dma_handle = {
    .Instance = CONFIG_USART4_TX_DMA_STREAM,
    .Init = {
        .Request = DMA_REQUEST_UART4_TX,
        .Direction = DMA_MEMORY_TO_PERIPH,
        .PeriphInc = DMA_PINC_DISABLE,
        .MemInc = DMA_MINC_ENABLE,
        .PeriphDataAlignment = DMA_PDATAALIGN_BYTE,
        .MemDataAlignment = DMA_MDATAALIGN_BYTE,
        .Mode = DMA_NORMAL,
        .Priority = CONFIG_USART4_TX_DMA_PRIORITY,
        .FIFOMode = DMA_FIFOMODE_DISABLE,
        .FIFOThreshold = DMA_FIFO_THRESHOLD_FULL,
        .MemBurst = DMA_MBURST_SINGLE,
        .PeriphBurst = DMA_PBURST_SINGLE,
    },
};
static dma_dev_t usart4_tx_dma = {
    .handle = &usart4_tx_dma_handle,
    .ins = CONFIG_USART4_TX_DMA_INS,
    .irq_num = CONFIG_USART4_TX_DMA_IRQ_NUM,
    .irq_prio = CONFIG_USART4_TX_DMA_IRQ_PRIO,
};
#endif /* (CONFIG_USART4_TX_DMA == 1) */
#endif /* (CONFIG_USART4_TX_DEF == 1) */
#if (CONFIG_USART4_RX_DEF == 1)
static gpio_pin_t usart4_rx_pin = { CONFIG_USART4_RX_PORT, CONFIG_USART4_RX_PIN, CONFIG_USART4_RX_AF };
#if (CONFIG_USART4_RX_DMA == 1)
static DMA_HandleTypeDef usart4_rx_dma_handle = {
    .Instance = CONFIG_USART4_RX_DMA_STREAM,
    .Init = {
        .Request = DMA_REQUEST_UART4_RX,
        .Direction = DMA_PERIPH_TO_MEMORY,
        .PeriphInc = DMA_PINC_DISABLE,
        .MemInc = DMA_MINC_ENABLE,
        .PeriphDataAlignment = DMA_PDATAALIGN_BYTE,
        .MemDataAlignment = DMA_MDATAALIGN_BYTE,
        .Mode = DMA_NORMAL,
        .Priority = CONFIG_USART4_RX_DMA_PRIORITY,
        .FIFOMode = DMA_FIFOMODE_DISABLE,
        .FIFOThreshold = DMA_FIFO_THRESHOLD_FULL,
        .MemBurst = DMA_MBURST_SINGLE,
        .PeriphBurst = DMA_PBURST_SINGLE,
    },
};
static dma_dev_t usart4_rx_dma = {
    .handle = &usart4_rx_dma_handle,
    .ins = CONFIG_USART4_RX_DMA_INS,
    .irq_num = CONFIG_USART4_RX_DMA_IRQ_NUM,
    .irq_prio = CONFIG_USART4_RX_DMA_IRQ_PRIO,
};
#endif /* (CONFIG_USART4_RX_DMA == 1) */
#endif /* (CONFIG_USART4_RX_DEF == 1) */
static UART_HandleTypeDef usart4_handle = {
    .Instance = UART4
};
static usart_dev_t usart4_dev = {
    .handle = &usart4_handle,
    .irq_num = UART4_IRQn,
    .irq_prio = CONFIG_USART4_IRQ_PRIO,
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
static gpio_pin_t usart5_tx_pin = { CONFIG_USART5_TX_PORT, CONFIG_USART5_TX_PIN, CONFIG_USART5_TX_AF };
#if (CONFIG_USART5_TX_DMA == 1)
static DMA_HandleTypeDef usart5_tx_dma_handle = {
    .Instance = CONFIG_USART5_TX_DMA_STREAM,
    .Init = {
        .Request = DMA_REQUEST_UART5_TX,
        .Direction = DMA_MEMORY_TO_PERIPH,
        .PeriphInc = DMA_PINC_DISABLE,
        .MemInc = DMA_MINC_ENABLE,
        .PeriphDataAlignment = DMA_PDATAALIGN_BYTE,
        .MemDataAlignment = DMA_MDATAALIGN_BYTE,
        .Mode = DMA_NORMAL,
        .Priority = CONFIG_USART5_TX_DMA_PRIORITY,
        .FIFOMode = DMA_FIFOMODE_DISABLE,
        .FIFOThreshold = DMA_FIFO_THRESHOLD_FULL,
        .MemBurst = DMA_MBURST_SINGLE,
        .PeriphBurst = DMA_PBURST_SINGLE,
    },
};
static dma_dev_t usart5_tx_dma = {
    .handle = &usart5_tx_dma_handle,
    .ins = CONFIG_USART5_TX_DMA_INS,
    .irq_num = CONFIG_USART5_TX_DMA_IRQ_NUM,
    .irq_prio = CONFIG_USART5_TX_DMA_IRQ_PRIO,
};
#endif /* (CONFIG_USART5_TX_DMA == 1) */
#endif /* (CONFIG_USART5_TX_DEF == 1) */
#if (CONFIG_USART5_RX_DEF == 1)
static gpio_pin_t usart5_rx_pin = { CONFIG_USART5_RX_PORT, CONFIG_USART5_RX_PIN, CONFIG_USART5_RX_AF };
#if (CONFIG_USART5_RX_DMA == 1)
static DMA_HandleTypeDef usart5_rx_dma_handle = {
    .Instance = CONFIG_USART5_RX_DMA_STREAM,
    .Init = {
        .Request = DMA_REQUEST_UART5_RX,
        .Direction = DMA_PERIPH_TO_MEMORY,
        .PeriphInc = DMA_PINC_DISABLE,
        .MemInc = DMA_MINC_ENABLE,
        .PeriphDataAlignment = DMA_PDATAALIGN_BYTE,
        .MemDataAlignment = DMA_MDATAALIGN_BYTE,
        .Mode = DMA_NORMAL,
        .Priority = CONFIG_USART5_RX_DMA_PRIORITY,
        .FIFOMode = DMA_FIFOMODE_DISABLE,
        .FIFOThreshold = DMA_FIFO_THRESHOLD_FULL,
        .MemBurst = DMA_MBURST_SINGLE,
        .PeriphBurst = DMA_PBURST_SINGLE,
    },
};
static dma_dev_t usart5_rx_dma = {
    .handle = &usart5_rx_dma_handle,
    .ins = CONFIG_USART5_RX_DMA_INS,
    .irq_num = CONFIG_USART5_RX_DMA_IRQ_NUM,
    .irq_prio = CONFIG_USART5_RX_DMA_IRQ_PRIO,
};
#endif /* (CONFIG_USART5_RX_DMA == 1) */
#endif /* (CONFIG_USART5_RX_DEF == 1) */
static UART_HandleTypeDef usart5_handle = {
    .Instance = UART5
};
static usart_dev_t usart5_dev = {
    .handle = &usart5_handle,
    .irq_num = UART5_IRQn,
    .irq_prio = CONFIG_USART5_IRQ_PRIO,
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
#if defined(USART6) && (CONFIG_USART_NUM_6 == 1)
#if (CONFIG_USART6_TX_DEF == 1)
static gpio_pin_t usart6_tx_pin = { CONFIG_USART6_TX_PORT, CONFIG_USART6_TX_PIN, CONFIG_USART6_TX_AF };
#if (CONFIG_USART6_TX_DMA == 1)
static DMA_HandleTypeDef usart6_tx_dma_handle = {
    .Instance = CONFIG_USART6_TX_DMA_STREAM,
    .Init = {
        .Request = DMA_REQUEST_USART6_TX,
        .Direction = DMA_MEMORY_TO_PERIPH,
        .PeriphInc = DMA_PINC_DISABLE,
        .MemInc = DMA_MINC_ENABLE,
        .PeriphDataAlignment = DMA_PDATAALIGN_BYTE,
        .MemDataAlignment = DMA_MDATAALIGN_BYTE,
        .Mode = DMA_NORMAL,
        .Priority = CONFIG_USART6_TX_DMA_PRIORITY,
        .FIFOMode = DMA_FIFOMODE_DISABLE,
        .FIFOThreshold = DMA_FIFO_THRESHOLD_FULL,
        .MemBurst = DMA_MBURST_SINGLE,
        .PeriphBurst = DMA_PBURST_SINGLE,
    },
};
static dma_dev_t usart6_tx_dma = {
    .handle = &usart6_tx_dma_handle,
    .ins = CONFIG_USART6_TX_DMA_INS,
    .irq_num = CONFIG_USART6_TX_DMA_IRQ_NUM,
    .irq_prio = CONFIG_USART6_TX_DMA_IRQ_PRIO,
};
#endif /* (CONFIG_USART6_TX_DMA == 1) */
#endif /* (CONFIG_USART6_TX_DEF == 1) */
#if (CONFIG_USART6_RX_DEF == 1)
static gpio_pin_t usart6_rx_pin = { CONFIG_USART6_RX_PORT, CONFIG_USART6_RX_PIN, CONFIG_USART6_RX_AF };
#if (CONFIG_USART6_RX_DMA == 1)
static DMA_HandleTypeDef usart6_rx_dma_handle = {
    .Instance = CONFIG_USART6_RX_DMA_STREAM,
    .Init = {
        .Request = DMA_REQUEST_USART6_RX,
        .Direction = DMA_PERIPH_TO_MEMORY,
        .PeriphInc = DMA_PINC_DISABLE,
        .MemInc = DMA_MINC_ENABLE,
        .PeriphDataAlignment = DMA_PDATAALIGN_BYTE,
        .MemDataAlignment = DMA_MDATAALIGN_BYTE,
        .Mode = DMA_NORMAL,
        .Priority = CONFIG_USART6_RX_DMA_PRIORITY,
        .FIFOMode = DMA_FIFOMODE_DISABLE,
        .FIFOThreshold = DMA_FIFO_THRESHOLD_FULL,
        .MemBurst = DMA_MBURST_SINGLE,
        .PeriphBurst = DMA_PBURST_SINGLE,
    },
};
static dma_dev_t usart6_rx_dma = {
    .handle = &usart6_rx_dma_handle,
    .ins = CONFIG_USART6_RX_DMA_INS,
    .irq_num = CONFIG_USART6_RX_DMA_IRQ_NUM,
    .irq_prio = CONFIG_USART6_RX_DMA_IRQ_PRIO,
};
#endif /* (CONFIG_USART6_RX_DMA == 1) */
#endif /* (CONFIG_USART6_RX_DEF == 1) */
static UART_HandleTypeDef usart6_handle = {
    .Instance = USART6
};
static usart_dev_t usart6_dev = {
    .handle = &usart6_handle,
    .irq_num = USART6_IRQn,
    .irq_prio = CONFIG_USART6_IRQ_PRIO,
#if (CONFIG_USART6_TX_DEF == 1)
    .tx_pin = &usart6_tx_pin,
#endif /* (CONFIG_USART6_TX_DEF == 1) */
#if (CONFIG_USART6_RX_DEF == 1)
    .rx_pin = &usart6_rx_pin,
#endif /* (CONFIG_USART6_RX_DEF == 1) */
#if (CONFIG_USART6_TX_DMA == 1)
    .dma_tx = &usart6_tx_dma,
#endif /* (CONFIG_USART6_TX_DMA == 1) */
#if (CONFIG_USART6_RX_DMA == 1)
    .dma_rx = &usart6_rx_dma,
#endif /* (CONFIG_USART6_RX_DMA == 1) */
};
#endif /* USART6 && (CONFIG_USART_NUM_6 == 1) */
#if defined(UART7) && (CONFIG_USART_NUM_7 == 1)
#if (CONFIG_USART7_TX_DEF == 1)
static gpio_pin_t usart7_tx_pin = { CONFIG_USART7_TX_PORT, CONFIG_USART7_TX_PIN, CONFIG_USART7_TX_AF };
#if (CONFIG_USART7_TX_DMA == 1)
static DMA_HandleTypeDef usart7_tx_dma_handle = {
    .Instance = CONFIG_USART7_TX_DMA_STREAM,
    .Init = {
        .Request = DMA_REQUEST_UART7_TX,
        .Direction = DMA_MEMORY_TO_PERIPH,
        .PeriphInc = DMA_PINC_DISABLE,
        .MemInc = DMA_MINC_ENABLE,
        .PeriphDataAlignment = DMA_PDATAALIGN_BYTE,
        .MemDataAlignment = DMA_MDATAALIGN_BYTE,
        .Mode = DMA_NORMAL,
        .Priority = CONFIG_USART7_TX_DMA_PRIORITY,
        .FIFOMode = DMA_FIFOMODE_DISABLE,
        .FIFOThreshold = DMA_FIFO_THRESHOLD_FULL,
        .MemBurst = DMA_MBURST_SINGLE,
        .PeriphBurst = DMA_PBURST_SINGLE,
    },
};
static dma_dev_t usart7_tx_dma = {
    .handle = &usart7_tx_dma_handle,
    .ins = CONFIG_USART7_TX_DMA_INS,
    .irq_num = CONFIG_USART7_TX_DMA_IRQ_NUM,
    .irq_prio = CONFIG_USART7_TX_DMA_IRQ_PRIO,
};
#endif /* (CONFIG_USART7_TX_DMA == 1) */
#endif /* (CONFIG_USART7_TX_DEF == 1) */
#if (CONFIG_USART7_RX_DEF == 1)
static gpio_pin_t usart7_rx_pin = { CONFIG_USART7_RX_PORT, CONFIG_USART7_RX_PIN, CONFIG_USART7_RX_AF };
#if (CONFIG_USART7_RX_DMA == 1)
static DMA_HandleTypeDef usart7_rx_dma_handle = {
    .Instance = CONFIG_USART7_RX_DMA_STREAM,
    .Init = {
        .Request = DMA_REQUEST_UART7_RX,
        .Direction = DMA_PERIPH_TO_MEMORY,
        .PeriphInc = DMA_PINC_DISABLE,
        .MemInc = DMA_MINC_ENABLE,
        .PeriphDataAlignment = DMA_PDATAALIGN_BYTE,
        .MemDataAlignment = DMA_MDATAALIGN_BYTE,
        .Mode = DMA_NORMAL,
        .Priority = CONFIG_USART7_RX_DMA_PRIORITY,
        .FIFOMode = DMA_FIFOMODE_DISABLE,
        .FIFOThreshold = DMA_FIFO_THRESHOLD_FULL,
        .MemBurst = DMA_MBURST_SINGLE,
        .PeriphBurst = DMA_PBURST_SINGLE,
    },
};
static dma_dev_t usart7_rx_dma = {
    .handle = &usart7_rx_dma_handle,
    .ins = CONFIG_USART7_RX_DMA_INS,
    .irq_num = CONFIG_USART7_RX_DMA_IRQ_NUM,
    .irq_prio = CONFIG_USART7_RX_DMA_IRQ_PRIO,
};
#endif /* (CONFIG_USART7_RX_DMA == 1) */
#endif /* (CONFIG_USART7_RX_DEF == 1) */
static UART_HandleTypeDef usart7_handle = {
    .Instance = UART7
};
static usart_dev_t uart7_dev = {
    .handle = &usart7_handle,
    .irq_num = UART7_IRQn,
    .irq_prio = CONFIG_USART7_IRQ_PRIO,
#if (CONFIG_USART7_TX_DEF == 1)
    .tx_pin = &usart7_tx_pin,
#endif /* (CONFIG_USART7_TX_DEF == 1) */
#if (CONFIG_USART7_RX_DEF == 1)
    .rx_pin = &usart7_rx_pin,
#endif /* (CONFIG_USART7_RX_DEF == 1) */
#if (CONFIG_USART7_TX_DMA == 1)
    .dma_tx = &usart7_tx_dma,
#endif /* (CONFIG_USART7_TX_DMA == 1) */
#if (CONFIG_USART7_RX_DMA == 1)
    .dma_rx = &usart7_rx_dma,
#endif /* (CONFIG_USART7_RX_DMA == 1) */
};
#endif /* UART7 && (CONFIG_USART_NUM_7 == 1) */
#if defined(UART8) && (CONFIG_USART_NUM_8 == 1)
#if (CONFIG_USART8_TX_DEF == 1)
static gpio_pin_t usart8_tx_pin = { CONFIG_USART8_TX_PORT, CONFIG_USART8_TX_PIN, CONFIG_USART8_TX_AF };
#if (CONFIG_USART8_TX_DMA == 1)
static DMA_HandleTypeDef usart8_tx_dma_handle = {
    .Instance = CONFIG_USART8_TX_DMA_STREAM,
    .Init = {
        .Request = DMA_REQUEST_UART8_TX,
        .Direction = DMA_MEMORY_TO_PERIPH,
        .PeriphInc = DMA_PINC_DISABLE,
        .MemInc = DMA_MINC_ENABLE,
        .PeriphDataAlignment = DMA_PDATAALIGN_BYTE,
        .MemDataAlignment = DMA_MDATAALIGN_BYTE,
        .Mode = DMA_NORMAL,
        .Priority = CONFIG_USART8_TX_DMA_PRIORITY,
        .FIFOMode = DMA_FIFOMODE_DISABLE,
        .FIFOThreshold = DMA_FIFO_THRESHOLD_FULL,
        .MemBurst = DMA_MBURST_SINGLE,
        .PeriphBurst = DMA_PBURST_SINGLE,
    },
};
static dma_dev_t usart8_tx_dma = {
    .handle = &usart8_tx_dma_handle,
    .ins = CONFIG_USART8_TX_DMA_INS,
    .irq_num = CONFIG_USART8_TX_DMA_IRQ_NUM,
    .irq_prio = CONFIG_USART8_TX_DMA_IRQ_PRIO,
};
#endif /* (CONFIG_USART8_TX_DMA == 1) */
#endif /* (CONFIG_USART8_TX_DEF == 1) */
#if (CONFIG_USART8_RX_DEF == 1)
static gpio_pin_t usart8_rx_pin = { CONFIG_USART8_RX_PORT, CONFIG_USART8_RX_PIN, CONFIG_USART8_RX_AF };
#if (CONFIG_USART8_RX_DMA == 1)
static DMA_HandleTypeDef usart8_rx_dma_handle = {
    .Instance = CONFIG_USART8_RX_DMA_STREAM,
    .Init = {
        .Request = DMA_REQUEST_UART8_RX,
        .Direction = DMA_PERIPH_TO_MEMORY,
        .PeriphInc = DMA_PINC_DISABLE,
        .MemInc = DMA_MINC_ENABLE,
        .PeriphDataAlignment = DMA_PDATAALIGN_BYTE,
        .MemDataAlignment = DMA_MDATAALIGN_BYTE,
        .Mode = DMA_NORMAL,
        .Priority = CONFIG_USART8_RX_DMA_PRIORITY,
        .FIFOMode = DMA_FIFOMODE_DISABLE,
        .FIFOThreshold = DMA_FIFO_THRESHOLD_FULL,
        .MemBurst = DMA_MBURST_SINGLE,
        .PeriphBurst = DMA_PBURST_SINGLE,
    },
};
static dma_dev_t usart8_rx_dma = {
    .handle = &usart8_rx_dma_handle,
    .ins = CONFIG_USART8_RX_DMA_INS,
    .irq_num = CONFIG_USART8_RX_DMA_IRQ_NUM,
    .irq_prio = CONFIG_USART8_RX_DMA_IRQ_PRIO,
};
#endif /* (CONFIG_USART8_RX_DMA == 1) */
#endif /* (CONFIG_USART8_RX_DEF == 1) */
static UART_HandleTypeDef usart8_handle = {
    .Instance = UART8
};
static usart_dev_t uart8_dev = {
    .handle = &usart8_handle,
    .irq_num = UART8_IRQn,
    .irq_prio = CONFIG_USART8_IRQ_PRIO,
#if (CONFIG_USART8_TX_DEF == 1)
    .tx_pin = &usart8_tx_pin,
#endif /* (CONFIG_USART8_TX_DEF == 1) */
#if (CONFIG_USART8_RX_DEF == 1)
    .rx_pin = &usart8_rx_pin,
#endif /* (CONFIG_USART8_RX_DEF == 1) */
#if (CONFIG_USART8_TX_DMA == 1)
    .dma_tx = &usart8_tx_dma,
#endif /* (CONFIG_USART8_TX_DMA == 1) */
#if (CONFIG_USART8_RX_DMA == 1)
    .dma_rx = &usart8_rx_dma,
#endif /* (CONFIG_USART8_RX_DMA == 1) */
};
#endif /* UART8 && (CONFIG_USART_NUM_8 == 1) */

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
#endif /* (CONFIG_USART_NUM_1 == 1) */

#if (CONFIG_USART_NUM_2 == 1)
        case USART_NUM_2:
            return &usart2_dev;
#endif /* (CONFIG_USART_NUM_2 == 1) */

#if (CONFIG_USART_NUM_3 == 1)
        case USART_NUM_3:
            return &usart3_dev;
#endif /* (CONFIG_USART_NUM_3 == 1) */

#if (CONFIG_USART_NUM_4 == 1)
        case USART_NUM_4:
            return &usart4_dev;
#endif /* (CONFIG_USART_NUM_4 == 1) */

#if (CONFIG_USART_NUM_5 == 1)
        case USART_NUM_5:
            return &usart5_dev;
#endif /* (CONFIG_USART_NUM_5 == 1) */

#if (CONFIG_USART_NUM_6 == 1)
        case USART_NUM_6:
            return &usart6_dev;
#endif /* (CONFIG_USART_NUM_6 == 1) */

#if (CONFIG_USART_NUM_7 == 1)
        case USART_NUM_7:
            return &uart7_dev;
#endif /* (CONFIG_USART_NUM_7 == 1) */

#if (CONFIG_USART_NUM_8 == 1)
        case USART_NUM_8:
            return &uart8_dev;
#endif /* (CONFIG_USART_NUM_8 == 1) */

#if (CONFIG_USART_NUM_9 == 1)
        case USART_NUM_9:
            return &uart9_dev;
#endif /* (CONFIG_USART_NUM_9 == 1) */

#if (CONFIG_USART_NUM_10 == 1)
        case USART_NUM_10:
            return &uart10_dev;
#endif /* (CONFIG_USART_NUM_10 == 1) */

        default:
            return NULL;
    }

    return NULL;
}
