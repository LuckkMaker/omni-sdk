/**
  * @file    spi_ll.c
  * @author  LuckkMaker
  * @brief   Low-level SPI configuration
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
#include "ll/spi_ll.h"

#if defined(SPI1) && (CONFIG_SPI_NUM_1 == 1)
#if (CONFIG_SPI1_NSS_DEF == 1)
static gpio_pin_t spi1_cs_pin = { CONFIG_SPI1_NSS_PORT, CONFIG_SPI1_NSS_PIN, CONFIG_SPI1_NSS_AF };
#endif /* (CONFIG_SPI1_NSS_DEF == 1) */
#if (CONFIG_SPI1_SCK_DEF == 1)
static gpio_pin_t spi1_sck_pin = { CONFIG_SPI1_SCK_PORT, CONFIG_SPI1_SCK_PIN, CONFIG_SPI1_SCK_AF };
#endif /* (CONFIG_SPI1_SCK_DEF == 1) */
#if (CONFIG_SPI1_MISO_DEF == 1)
static gpio_pin_t spi1_miso_pin = { CONFIG_SPI1_MISO_PORT, CONFIG_SPI1_MISO_PIN, CONFIG_SPI1_MISO_AF };
#endif /* (CONFIG_SPI1_MISO_DEF == 1) */
#if (CONFIG_SPI1_MOSI_DEF == 1)
static gpio_pin_t spi1_mosi_pin = { CONFIG_SPI1_MOSI_PORT, CONFIG_SPI1_MOSI_PIN, CONFIG_SPI1_MOSI_AF };
#endif /* (CONFIG_SPI1_MOSI_DEF == 1) */
#if (CONFIG_SPI1_TX_DMA == 1)
static DMA_HandleTypeDef spi1_tx_dma_handle = {
    .Instance = CONFIG_SPI1_TX_DMA_STREAM,
    .Init = {
        .Channel = CONFIG_SPI1_TX_DMA_CHANNEL,
        .Direction = DMA_MEMORY_TO_PERIPH,
        .PeriphInc = DMA_PINC_DISABLE,
        .MemInc = DMA_MINC_ENABLE,
        .PeriphDataAlignment = DMA_PDATAALIGN_BYTE,
        .MemDataAlignment = DMA_MDATAALIGN_BYTE,
        .Mode = DMA_NORMAL,
        .Priority = CONFIG_SPI1_TX_DMA_PRIORITY,
        .FIFOMode = DMA_FIFOMODE_DISABLE,
        .FIFOThreshold = DMA_FIFO_THRESHOLD_FULL,
        .MemBurst = DMA_MBURST_SINGLE,
        .PeriphBurst = DMA_PBURST_SINGLE,
    },
};
static dma_dev_t spi1_tx_dma = {
    .handle = &spi1_tx_dma_handle,
    .ins = CONFIG_SPI1_TX_DMA_INS,
    .irq_num = CONFIG_SPI1_TX_DMA_IRQ_NUM,
    .irq_prio = CONFIG_SPI1_TX_DMA_IRQ_PRIO,
};
#endif /* (CONFIG_SPI1_TX_DMA == 1) */
#if (CONFIG_SPI1_RX_DMA == 1)
static DMA_HandleTypeDef spi1_rx_dma_handle = {
    .Instance = CONFIG_SPI1_RX_DMA_STREAM,
    .Init = {
        .Channel = CONFIG_SPI1_RX_DMA_CHANNEL,
        .Direction = DMA_PERIPH_TO_MEMORY,
        .PeriphInc = DMA_PINC_DISABLE,
        .MemInc = DMA_MINC_ENABLE,
        .PeriphDataAlignment = DMA_PDATAALIGN_BYTE,
        .MemDataAlignment = DMA_MDATAALIGN_BYTE,
        .Mode = DMA_NORMAL,
        .Priority = CONFIG_SPI1_RX_DMA_PRIORITY,
        .FIFOMode = DMA_FIFOMODE_DISABLE,
        .FIFOThreshold = DMA_FIFO_THRESHOLD_FULL,
        .MemBurst = DMA_MBURST_SINGLE,
        .PeriphBurst = DMA_PBURST_SINGLE,
    },
};
static dma_dev_t spi1_rx_dma = {
    .handle = &spi1_rx_dma_handle,
    .ins = CONFIG_SPI1_RX_DMA_INS,
    .irq_num = CONFIG_SPI1_RX_DMA_IRQ_NUM,
    .irq_prio = CONFIG_SPI1_RX_DMA_IRQ_PRIO,
};
#endif /* (CONFIG_SPI1_RX_DMA == 1) */
static SPI_HandleTypeDef spi1_handle = {
    .Instance = SPI1
};
static spi_dev_t spi1_dev = {
    .handle = &spi1_handle,
    .irq_num = SPI1_IRQn,
    .irq_prio = CONFIG_SPI1_IRQ_PRIO,
    .clock = CONFIG_SPI1_CLK_FREQ,
#if (CONFIG_SPI1_NSS_DEF == 1)
    .cs_pin = &spi1_cs_pin,
#endif /* (CONFIG_SPI1_NSS_DEF == 1) */
#if (CONFIG_SPI1_SCK_DEF == 1)
    .sck_pin = &spi1_sck_pin,
#endif /* (CONFIG_SPI1_SCK_DEF == 1) */
#if (CONFIG_SPI1_MISO_DEF == 1)
    .miso_pin = &spi1_miso_pin,
#endif /* (CONFIG_SPI1_MISO_DEF == 1) */
#if (CONFIG_SPI1_MOSI_DEF == 1)
    .mosi_pin = &spi1_mosi_pin,
#endif /* (CONFIG_SPI1_MOSI_DEF == 1) */
#if (CONFIG_SPI1_TX_DMA == 1)
    .dma_tx = &spi1_tx_dma,
#endif /* (CONFIG_SPI1_TX_DMA == 1) */
#if (CONFIG_SPI1_RX_DMA == 1)
    .dma_rx = &spi1_rx_dma,
#endif /* (CONFIG_SPI1_RX_DMA == 1) */
};
#endif /* SPI1 && (CONFIG_SPI_NUM_1 == 1) */

/**
 * @brief Get SPI device information
 * 
 * @param spi_num SPI bus number
 * @return SPI device information
 */
spi_dev_t* spi_ll_get_dev(spi_num_t spi_num) {
    switch (spi_num) {
#if (CONFIG_SPI_NUM_1 == 1)
        case SPI_NUM_1:
            return &spi1_dev;
#endif /* (CONFIG_SPI_NUM_1 == 1) */

#if (CONFIG_SPI_NUM_2 == 1)
        case SPI_NUM_2:
            return &spi2_dev;
#endif /* (CONFIG_SPI_NUM_2 == 1) */

#if (CONFIG_SPI_NUM_3 == 1)
        case SPI_NUM_3:
            return &spi3_dev;
#endif /* (CONFIG_SPI_NUM_3 == 1) */

#if (CONFIG_SPI_NUM_4 == 1)
        case SPI_NUM_4:
            return &spi4_dev;
#endif /* (CONFIG_SPI_NUM_4 == 1) */

#if (CONFIG_SPI_NUM_5 == 1)
        case SPI_NUM_5:
            return &spi5_dev;
#endif /* (CONFIG_SPI_NUM_5 == 1) */

#if (CONFIG_SPI_NUM_6 == 1)
        case SPI_NUM_6:
            return &spi6_dev;
#endif /* (CONFIG_SPI_NUM_6 == 1) */

        default:
            return NULL;
    }

    return NULL;
}
