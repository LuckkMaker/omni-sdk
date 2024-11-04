/**
  * @file    i2c_ll.c
  * @author  LuckkMaker
  * @brief   Low-level I2C configuration
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
#include "ll/i2c_ll.h"
#include "ll/gpio_ll.h"

#if defined(I2C1) && (CONFIG_I2C_NUM_1 == 1)
#if (CONFIG_I2C1_SCL_DEF == 1) && (CONFIG_I2C1_SDA_DEF == 1)
static gpio_pin_t i2c1_scl_pin = { CONFIG_I2C1_SCL_PORT, CONFIG_I2C1_SCL_PIN };
static gpio_pin_t i2c1_sda_pin = { CONFIG_I2C1_SDA_PORT, CONFIG_I2C1_SDA_PIN };
#if (CONFIG_I2C1_TX_DMA == 1)
static DMA_HandleTypeDef i2c1_tx_dma_handle = {
    .Instance = CONFIG_I2C1_TX_DMA_CHANNEL,
    .Init = {
        .Direction = DMA_MEMORY_TO_PERIPH,
        .PeriphInc = DMA_PINC_DISABLE,
        .MemInc = DMA_MINC_ENABLE,
        .PeriphDataAlignment = DMA_PDATAALIGN_BYTE,
        .MemDataAlignment = DMA_MDATAALIGN_BYTE,
        .Mode = DMA_NORMAL,
        .Priority = CONFIG_I2C1_TX_DMA_PRIORITY,
    },
};
static dma_dev_t i2c1_tx_dma = {
    .handle = &i2c1_tx_dma_handle,
    .ins = CONFIG_I2C1_TX_DMA_INS,
    .irq_num = CONFIG_I2C1_TX_DMA_IRQ_NUM,
    .irq_prio = CONFIG_I2C1_TX_DMA_IRQ_PRIO,
};
#endif /* (CONFIG_I2C1_TX_DMA == 1) */
#if (CONFIG_I2C1_RX_DMA == 1)
static DMA_HandleTypeDef i2c1_rx_dma_handle = {
    .Instance = CONFIG_I2C1_RX_DMA_CHANNEL,
    .Init = {
        .Direction = DMA_PERIPH_TO_MEMORY,
        .PeriphInc = DMA_PINC_DISABLE,
        .MemInc = DMA_MINC_ENABLE,
        .PeriphDataAlignment = DMA_PDATAALIGN_BYTE,
        .MemDataAlignment = DMA_MDATAALIGN_BYTE,
        .Mode = DMA_NORMAL,
        .Priority = CONFIG_I2C1_RX_DMA_PRIORITY,
    },
};
static dma_dev_t i2c1_rx_dma = {
    .handle = &i2c1_rx_dma_handle,
    .ins = CONFIG_I2C1_RX_DMA_INS,
    .irq_num = CONFIG_I2C1_RX_DMA_IRQ_NUM,
    .irq_prio = CONFIG_I2C1_RX_DMA_IRQ_PRIO,
};
#endif /* (CONFIG_I2C1_RX_DMA == 1) */
#endif /* (CONFIG_I2C1_SCL_DEF == 1) && (CONFIG_I2C1_SDA_DEF == 1) */
static I2C_HandleTypeDef i2c1_handle = {
    .Instance = I2C1
};
static i2c_dev_t i2c1_dev = {
    .handle = &i2c1_handle,
    .er_irq_num = I2C1_ER_IRQn,
    .er_irq_prio = CONFIG_I2C1_ER_IRQ_PRIO,
    .ev_irq_num = I2C1_EV_IRQn,
    .ev_irq_prio = CONFIG_I2C1_EV_IRQ_PRIO,
    .alternate = CONFIG_I2C1_AF_REMAP,
#if (CONFIG_I2C1_SCL_DEF == 1)
    .scl_pin = &i2c1_scl_pin,
#endif /* (CONFIG_I2C1_SCL_DEF == 1) */
#if (CONFIG_I2C1_SDA_DEF == 1)
    .sda_pin = &i2c1_sda_pin,
#endif /* (CONFIG_I2C1_SDA_DEF == 1) */
#if (CONFIG_I2C1_TX_DMA == 1)
    .dma_tx = &i2c1_tx_dma,
#endif /* (CONFIG_I2C1_TX_DMA == 1) */
#if (CONFIG_I2C1_RX_DMA == 1)
    .dma_rx = &i2c1_rx_dma,
#endif /* (CONFIG_I2C1_RX_DMA == 1) */
};
#endif /* I2C1 && (CONFIG_I2C_NUM_1 == 1) */
#if defined(I2C2) && (CONFIG_I2C_NUM_2 == 1)
#if (CONFIG_I2C2_SCL_DEF == 1) && (CONFIG_I2C2_SDA_DEF == 1)
static gpio_pin_t i2c2_scl_pin = { CONFIG_I2C2_SCL_PORT, CONFIG_I2C2_SCL_PIN };
static gpio_pin_t i2c2_sda_pin = { CONFIG_I2C2_SDA_PORT, CONFIG_I2C2_SDA_PIN };
#if (CONFIG_I2C2_TX_DMA == 1)
static DMA_HandleTypeDef i2c2_tx_dma_handle = {
    .Instance = CONFIG_I2C2_TX_DMA_CHANNEL,
    .Init = {
        .Direction = DMA_MEMORY_TO_PERIPH,
        .PeriphInc = DMA_PINC_DISABLE,
        .MemInc = DMA_MINC_ENABLE,
        .PeriphDataAlignment = DMA_PDATAALIGN_BYTE,
        .MemDataAlignment = DMA_MDATAALIGN_BYTE,
        .Mode = DMA_NORMAL,
        .Priority = CONFIG_I2C2_TX_DMA_PRIORITY,
    },
};
static dma_dev_t i2c2_tx_dma = {
    .handle = &i2c2_tx_dma_handle,
    .ins = CONFIG_I2C2_TX_DMA_INS,
    .irq_num = CONFIG_I2C2_TX_DMA_IRQ_NUM,
    .irq_prio = CONFIG_I2C2_TX_DMA_IRQ_PRIO,
};
#endif /* (CONFIG_I2C2_TX_DMA == 1) */
#if (CONFIG_I2C2_RX_DMA == 1)
static DMA_HandleTypeDef i2c2_rx_dma_handle = {
    .Instance = CONFIG_I2C2_RX_DMA_STREAM,
    .Init = {
        .Channel = CONFIG_I2C2_RX_DMA_CHANNEL,
        .Direction = DMA_PERIPH_TO_MEMORY,
        .PeriphInc = DMA_PINC_DISABLE,
        .MemInc = DMA_MINC_ENABLE,
        .PeriphDataAlignment = DMA_PDATAALIGN_BYTE,
        .MemDataAlignment = DMA_MDATAALIGN_BYTE,
        .Mode = DMA_NORMAL,
        .Priority = CONFIG_I2C2_RX_DMA_PRIORITY,
    },
};
static dma_dev_t i2c2_rx_dma = {
    .handle = &i2c2_rx_dma_handle,
    .ins = CONFIG_I2C2_RX_DMA_INS,
    .irq_num = CONFIG_I2C2_RX_DMA_IRQ_NUM,
    .irq_prio = CONFIG_I2C2_RX_DMA_IRQ_PRIO,
};
#endif /* (CONFIG_I2C2_RX_DMA == 1) */
#endif /* (CONFIG_I2C2_SCL_DEF == 1) && (CONFIG_I2C2_SDA_DEF == 1) */
static I2C_HandleTypeDef i2c2_handle = {
    .Instance = I2C2
};
static i2c_dev_t i2c2_dev = {
    .handle = &i2c2_handle,
    .er_irq_num = I2C2_ER_IRQn,
    .er_irq_prio = CONFIG_I2C2_ER_IRQ_PRIO,
    .ev_irq_num = I2C2_EV_IRQn,
    .ev_irq_prio = CONFIG_I2C2_EV_IRQ_PRIO,
    .alternate = CONFIG_I2C2_AF_REMAP,
#if (CONFIG_I2C2_SCL_DEF == 1)
    .scl_pin = &i2c2_scl_pin,
#endif /* (CONFIG_I2C2_SCL_DEF == 1) */
#if (CONFIG_I2C2_SDA_DEF == 1)
    .sda_pin = &i2c2_sda_pin,
#endif /* (CONFIG_I2C2_SDA_DEF == 1) */
#if (CONFIG_I2C2_TX_DMA == 1)
    .dma_tx = &i2c2_tx_dma,
#endif /* (CONFIG_I2C2_TX_DMA == 1) */
#if (CONFIG_I2C2_RX_DMA == 1)
    .dma_rx = &i2c2_rx_dma,
#endif /* (CONFIG_I2C2_RX_DMA == 1) */
};
#endif /* I2C2 && (CONFIG_I2C_NUM_2 == 1) */

/**
 * @brief Get I2C device information
 * 
 * @param i2c_num I2C number
 * @return Pointer to I2C device information
 */
i2c_dev_t* i2c_ll_get_dev(i2c_num_t i2c_num) {
    switch (i2c_num) {
#if (CONFIG_I2C_NUM_1 == 1)
        case I2C_NUM_1:
            return &i2c1_dev;
#endif /* (CONFIG_I2C_NUM_1 == 1) */
#if (CONFIG_I2C_NUM_2 == 1)
        case I2C_NUM_2:
            return &i2c2_dev;
#endif /* (CONFIG_I2C_NUM_2 == 1) */

        default:
            return NULL;
    }

    return NULL;
}
