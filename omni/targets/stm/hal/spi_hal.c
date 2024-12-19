/**
  * @file    spi_hal.c
  * @author  LuckkMaker
  * @brief   SPI HAL driver
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
#include "drivers/spi.h"
#include "hal/gpio_hal.h"
#include "hal/dma_hal.h"
#include "hal/irq_hal.h"
#include "ll/spi_ll.h"

#define _SPI_DATASIZE(bits)     SPI_DATASIZE_##bits##_BIT
#define SPI_DATASIZE(bits)      _SPI_DATASIZE(bits)

static spi_obj_t spi_obj[SPI_NUM_MAX];

static int spi_hal_init(spi_num_t spi_num, spi_driver_config_t *config);
static int spi_hal_deinit(spi_num_t spi_num);
static void spi_hal_start(spi_num_t spi_num);
static void spi_hal_stop(spi_num_t spi_num);
static int spi_hal_send(spi_num_t spi_num, const void *data, uint32_t len);
static int spi_hal_receive(spi_num_t spi_num, void *data, uint32_t len);
static int spi_hal_transfer(spi_num_t spi_num, const void *tx_data, void *rx_data, uint32_t len);
static spi_driver_status_t spi_hal_get_status(spi_num_t spi_num);
static spi_driver_error_t spi_hal_get_error(spi_num_t spi_num);

const struct spi_driver_api spi_driver = {
    .init = spi_hal_init,
    .deinit = spi_hal_deinit,
    .start = spi_hal_start,
    .stop = spi_hal_stop,
    .send = spi_hal_send,
    .receive = spi_hal_receive,
    .transfer = spi_hal_transfer,
    .get_status = spi_hal_get_status,
    .get_error = spi_hal_get_error,
};

static uint32_t spi_hal_get_clock(spi_dev_t *dev);
static int spi_hal_configure(spi_dev_t *dev, spi_driver_config_t *config);
static void spi_hal_irq_register(void);
static void spi_hal_set_gpio(spi_dev_t *dev);
static void spi_hal_reset_gpio(spi_dev_t *dev);
static int spi_hal_enable_clock(spi_num_t spi_num);
static void spi_hal_reset_clock(spi_num_t spi_num);
static spi_obj_t *spi_hal_get_obj(SPI_HandleTypeDef *hspi);

/**
 * @brief Initialize SPI bus
 * 
 * @param spi_num SPI number
 * @param config Pointer to the SPI driver configuration
 * @return Operation status
 */
static int spi_hal_init(spi_num_t spi_num, spi_driver_config_t *config) {
    omni_assert(spi_num < SPI_NUM_MAX);
    omni_assert_not_null(config);

    spi_obj_t *obj = &spi_obj[spi_num];

    // Set event callback
    if (config->event_cb != NULL) {
        obj->event_cb = config->event_cb;
    } else {
        obj->event_cb = NULL;
    }

    // Get dev information
    obj->dev = spi_ll_get_dev(spi_num);
    omni_assert_not_null(obj->dev);

    // Clear status
    obj->status = (spi_driver_status_t){0};

    // Clear error
    obj->error = (spi_driver_error_t){0};

    // Register IRQ
    spi_hal_irq_register();

    // Enable SPI clock
    if (spi_hal_enable_clock(spi_num) != OMNI_OK) {
        return OMNI_FAIL;
    }

    // Initialize GPIO
    spi_hal_set_gpio(obj->dev);

    // Initialize DMA
#if (CONFIG_SPI_TX_DMA == 1)
    // Initialize SPI DMA TX
    if (obj->dev->dma_tx != NULL) {
        dma_hal_enable_clock(obj->dev->dma_tx->ins);

        if (HAL_DMA_Init(obj->dev->dma_tx->handle) != HAL_OK) {
            return OMNI_FAIL;
        }

        __HAL_LINKDMA(obj->dev->handle, hdmatx, *(obj->dev->dma_tx->handle));

        // Enable DMA TX IRQ
        NVIC_ClearPendingIRQ(obj->dev->dma_tx->irq_num);
        NVIC_SetPriority(obj->dev->dma_tx->irq_num, \
            NVIC_EncodePriority(NVIC_GetPriorityGrouping(), obj->dev->dma_tx->irq_prio, 0));
        NVIC_EnableIRQ(obj->dev->dma_tx->irq_num);
    }
#endif /* CONFIG_SPI_TX_DMA */

#if (CONFIG_SPI_RX_DMA == 1)
    // Initialize SPI DMA RX
    if (obj->dev->dma_rx != NULL) {
        dma_hal_enable_clock(obj->dev->dma_rx->ins);

        if (HAL_DMA_Init(obj->dev->dma_rx->handle) != HAL_OK) {
            return OMNI_FAIL;
        }

        __HAL_LINKDMA(obj->dev->handle, hdmarx, *(obj->dev->dma_rx->handle));

        // Enable DMA RX IRQ
        NVIC_ClearPendingIRQ(obj->dev->dma_rx->irq_num);
        NVIC_SetPriority(obj->dev->dma_rx->irq_num, \
            NVIC_EncodePriority(NVIC_GetPriorityGrouping(), obj->dev->dma_rx->irq_prio, 0));
        NVIC_EnableIRQ(obj->dev->dma_rx->irq_num);
    }
#endif /* CONFIG_SPI_RX_DMA */

    // Initialize IRQ
    NVIC_ClearPendingIRQ(obj->dev->irq_num);
    NVIC_SetPriority(obj->dev->irq_num, \
        NVIC_EncodePriority(NVIC_GetPriorityGrouping(), obj->dev->irq_prio, 0));
    NVIC_EnableIRQ(obj->dev->irq_num);

    // Initialize SPI
    if (spi_hal_configure(obj->dev, config) != OMNI_OK) {
        return OMNI_FAIL;
    }

    // Set initialized status
    obj->status.is_initialized = 1;
    // Call event callback
    if (obj->event_cb != NULL) {
        // Set initialized event
        obj->event_cb(SPI_EVENT_INITIALIZED);
    }

    return OMNI_OK;
}

/**
 * @brief Deinitialize SPI bus
 * 
 * @param spi_num SPI number
 * @return Operation status
 */
static int spi_hal_deinit(spi_num_t spi_num) {
    omni_assert(spi_num < SPI_NUM_MAX);

    spi_obj_t *obj = &spi_obj[spi_num];
    omni_assert_not_null(obj);

    // Reset SPI clock
    spi_hal_reset_clock(spi_num);

    // Reset GPIO
    spi_hal_reset_gpio(obj->dev);

#if (CONFIG_SPI_TX_DMA == 1)
    // Deinitialize SPI DMA TX
    if (obj->dev->dma_tx != NULL) {
        HAL_DMA_DeInit(obj->dev->dma_tx->handle);
    }
#endif /* (CONFIG_SPI_TX_DMA == 1) */

#if (CONFIG_SPI_RX_DMA == 1)
    // Deinitialize SPI DMA RX
    if (obj->dev->dma_rx != NULL) {
        HAL_DMA_DeInit(obj->dev->dma_rx->handle);
    }
#endif /* (CONFIG_SPI_RX_DMA == 1) */

    // Disable SPI IRQ
    NVIC_DisableIRQ(obj->dev->irq_num);

#if (CONFIG_SPI_TX_DMA == 1)
    // Disable DMA TX IRQ
    if (obj->dev->dma_tx != NULL) {
        NVIC_DisableIRQ(obj->dev->dma_tx->irq_num);
    }
#endif /* (CONFIG_SPI_TX_DMA == 1) */

#if (CONFIG_SPI_RX_DMA == 1)
    // Disable DMA RX IRQ
    if (obj->dev->dma_rx != NULL) {
        NVIC_DisableIRQ(obj->dev->dma_rx->irq_num);
    }
#endif /* (CONFIG_SPI_RX_DMA == 1) */

    // Clear object
    if (obj->dev != NULL) {
        obj->dev = NULL;
    }

    if (obj->event_cb != NULL) {
        obj->event_cb = NULL;
    }

    spi_obj[spi_num] = (spi_obj_t){0};

    return OMNI_OK;
}

/**
 * @brief Start SPI bus
 * 
 * @param spi_num SPI number
 */
static void spi_hal_start(spi_num_t spi_num) {
    omni_assert(spi_num < SPI_NUM_MAX);

    spi_obj_t *obj = &spi_obj[spi_num];
    omni_assert_not_null(obj);

    SPI_HandleTypeDef *handle = obj->dev->handle;

    // Enable SPI
    __HAL_SPI_ENABLE(handle);
}

/**
 * @brief Stop SPI bus
 * 
 * @param spi_num SPI number
 */
static void spi_hal_stop(spi_num_t spi_num) {
    omni_assert(spi_num < SPI_NUM_MAX);

    spi_obj_t *obj = &spi_obj[spi_num];
    omni_assert_not_null(obj);

    SPI_HandleTypeDef *handle = obj->dev->handle;

    // Disable SPI
    __HAL_SPI_DISABLE(handle);
}

/**
 * @brief Send data via SPI bus
 * 
 * @param spi_num SPI number
 * @param data Pointer to data buffer
 * @param len Length of data buffer
 * @return Operation status
 */
static int spi_hal_send(spi_num_t spi_num, const void *data, uint32_t len) {
    HAL_StatusTypeDef status;
    omni_assert(spi_num < SPI_NUM_MAX);
    omni_assert_not_null(data);
    omni_assert_non_zero(len);

    spi_obj_t *obj = &spi_obj[spi_num];
    omni_assert_not_null(obj);

    SPI_HandleTypeDef *handle = obj->dev->handle;

    if (obj->status.busy) {
        return OMNI_BUSY;
    }

    // Set busy status
    obj->status.busy = 1;

#if (CONFIG_SPI_TX_DMA == 1)
    status = HAL_SPI_Transmit_DMA(handle, (uint8_t *)data, (uint16_t)len);
#else
    status = HAL_SPI_Transmit_IT(handle, (uint8_t *)data, (uint16_t)len);
#endif /* (CONFIG_SPI_TX_DMA == 1) */

    // Convert HAL status to OMNI status
    switch (status) {
        case HAL_OK:
            break;

        case HAL_BUSY:
            return OMNI_BUSY;

        case HAL_ERROR:
            obj->status.busy = 0;
            return OMNI_FAIL;

        default:
            obj->status.busy = 0;
            return OMNI_FAIL;
    }

    return OMNI_OK;
}

/**
 * @brief Receive data via SPI bus
 * 
 * @param spi_num SPI number
 * @param data Pointer to data buffer
 * @param len Length of data buffer
 * @return Operation status
 */
static int spi_hal_receive(spi_num_t spi_num, void *data, uint32_t len) {
    HAL_StatusTypeDef status;
    omni_assert(spi_num < SPI_NUM_MAX);
    omni_assert_not_null(data);
    omni_assert_non_zero(len);

    spi_obj_t *obj = &spi_obj[spi_num];
    omni_assert_not_null(obj);

    SPI_HandleTypeDef *handle = obj->dev->handle;

    if (obj->status.busy) {
        return OMNI_BUSY;
    }

    // Set busy status
    obj->status.busy = 1;

#if ((CONFIG_SPI_TX_DMA == 1) && (CONFIG_SPI_RX_DMA == 1))
    status = HAL_SPI_TransmitReceive_DMA(handle, (uint8_t *)data, (uint8_t *)data, (uint16_t)len);
#else
    status = HAL_SPI_TransmitReceive_IT(handle, (uint8_t *)data, (uint8_t *)data, (uint16_t)len);
#endif /* ((CONFIG_SPI_TX_DMA == 1) && (CONFIG_SPI_RX_DMA == 1)) */

    // Convert HAL status to OMNI status
    switch (status) {
        case HAL_OK:
            break;

        case HAL_BUSY:
            return OMNI_BUSY;

        case HAL_ERROR:
            obj->status.busy = 0;
            return OMNI_FAIL;

        default:
            obj->status.busy = 0;
            return OMNI_FAIL;
    }

    return OMNI_OK;
}

/**
 * @brief Transfer data via SPI bus
 * 
 * @param spi_num SPI number
 * @param tx_data Pointer to TX data buffer
 * @param rx_data Pointer to RX data buffer
 * @param len Length of data buffer
 * @return Operation status
 */
static int spi_hal_transfer(spi_num_t spi_num, const void *tx_data, void *rx_data, uint32_t len) {
    HAL_StatusTypeDef status;
    omni_assert(spi_num < SPI_NUM_MAX);
    omni_assert_not_null(tx_data);
    omni_assert_not_null(rx_data);
    omni_assert_non_zero(len);

    spi_obj_t *obj = &spi_obj[spi_num];
    omni_assert_not_null(obj);

    SPI_HandleTypeDef *handle = obj->dev->handle;

    if (obj->status.busy) {
        return OMNI_BUSY;
    }

    // Set busy status
    obj->status.busy = 1;

#if ((CONFIG_SPI_TX_DMA == 1) && (CONFIG_SPI_RX_DMA == 1))
    status = HAL_SPI_TransmitReceive_DMA(handle, (uint8_t *)tx_data, (uint8_t *)rx_data, (uint16_t)len);
#else
    status = HAL_SPI_TransmitReceive_IT(handle, (uint8_t *)tx_data, (uint8_t *)rx_data, (uint16_t)len);
#endif /* ((CONFIG_SPI_TX_DMA == 1) && (CONFIG_SPI_RX_DMA == 1)) */

    // Convert HAL status to OMNI status
    switch (status) {
        case HAL_OK:
            break;

        case HAL_BUSY:
            return OMNI_BUSY;

        case HAL_ERROR:
            obj->status.busy = 0;
            return OMNI_FAIL;

        default:
            obj->status.busy = 0;
            return OMNI_FAIL;
    }

    return OMNI_OK;
}

/**
 * @brief Get SPI bus status
 * 
 * @param spi_num SPI number
 * @return SPI driver status
 */
static spi_driver_status_t spi_hal_get_status(spi_num_t spi_num) {
    omni_assert(spi_num < SPI_NUM_MAX);

    spi_obj_t *obj = &spi_obj[spi_num];
    omni_assert_not_null(obj);

    return obj->status;
}

/**
 * @brief Get SPI bus error
 * 
 * @param spi_num SPI number
 * @return SPI driver error
 */
static spi_driver_error_t spi_hal_get_error(spi_num_t spi_num) {
    omni_assert(spi_num < SPI_NUM_MAX);

    spi_obj_t *obj = &spi_obj[spi_num];
    omni_assert_not_null(obj);

    return obj->error;
}

/********************* IRQ handlers **********************/

/**
 * @brief SPI IRQ handler
 */
static void spi_hal_irq_request(spi_obj_t *obj) {
    omni_assert_not_null(obj);

    SPI_HandleTypeDef *handle = obj->dev->handle;

    HAL_SPI_IRQHandler(handle);
}

#if (CONFIG_SPI_NUM_1 == 1)
/**
 * @brief SPI1 IRQ handler
 */
static void spi1_irq_handler(void) {
    spi_hal_irq_request(&spi_obj[SPI_NUM_1]);
}
#endif /* CONFIG_SPI_NUM_1 */

#if (CONFIG_SPI_NUM_2 == 1)
/**
 * @brief SPI2 IRQ handler
 */
static void spi2_irq_handler(void) {
    spi_hal_irq_request(&spi_obj[SPI_NUM_2]);
}
#endif /* CONFIG_SPI_NUM_2 */

#if (CONFIG_SPI_NUM_3 == 1)
/**
 * @brief SPI3 IRQ handler
 */
static void spi3_irq_handler(void) {
    spi_hal_irq_request(&spi_obj[SPI_NUM_3]);
}
#endif /* CONFIG_SPI_NUM_3 */

#if (CONFIG_SPI_NUM_4 == 1)
/**
 * @brief SPI4 IRQ handler
 */
static void spi4_irq_handler(void) {
    spi_hal_irq_request(&spi_obj[SPI_NUM_4]);
}
#endif /* CONFIG_SPI_NUM_4 */

#if (CONFIG_SPI_NUM_5 == 1)
/**
 * @brief SPI5 IRQ handler
 */
static void spi5_irq_handler(void) {
    spi_hal_irq_request(&spi_obj[SPI_NUM_5]);
}
#endif /* CONFIG_SPI_NUM_5 */

#if (CONFIG_SPI_NUM_6 == 1)
/**
 * @brief SPI6 IRQ handler
 */
static void spi6_irq_handler(void) {
    spi_hal_irq_request(&spi_obj[SPI_NUM_6]);
}
#endif /* CONFIG_SPI_NUM_6 */

#if (CONFIG_SPI_TX_DMA == 1)
#if (CONFIG_SPI1_TX_DMA == 1)
void spi1_tx_dma_irq_handler(void) {
    HAL_DMA_IRQHandler(spi_obj[SPI_NUM_1].dev->dma_tx->handle);
}
#endif /* (CONFIG_SPI1_TX_DMA == 1) */
#if (CONFIG_SPI2_TX_DMA == 1)
void spi2_tx_dma_irq_handler(void) {
    HAL_DMA_IRQHandler(spi_obj[SPI_NUM_2].dev->dma_tx->handle);
}
#endif /* (CONFIG_SPI2_TX_DMA == 1) */
#if (CONFIG_SPI3_TX_DMA == 1)
void spi3_tx_dma_irq_handler(void) {
    HAL_DMA_IRQHandler(spi_obj[SPI_NUM_3].dev->dma_tx->handle);
}
#endif /* (CONFIG_SPI3_TX_DMA == 1) */
#if (CONFIG_SPI4_TX_DMA == 1)
void spi4_tx_dma_irq_handler(void) {
    HAL_DMA_IRQHandler(spi_obj[SPI_NUM_4].dev->dma_tx->handle);
}
#endif /* (CONFIG_SPI4_TX_DMA == 1) */
#if (CONFIG_SPI5_TX_DMA == 1)
void spi5_tx_dma_irq_handler(void) {
    HAL_DMA_IRQHandler(spi_obj[SPI_NUM_5].dev->dma_tx->handle);
}
#endif /* (CONFIG_SPI5_TX_DMA == 1) */
#if (CONFIG_SPI6_TX_DMA == 1)
void spi6_tx_dma_irq_handler(void) {
    HAL_DMA_IRQHandler(spi_obj[SPI_NUM_6].dev->dma_tx->handle);
}
#endif /* (CONFIG_SPI6_TX_DMA == 1) */
#endif /* (CONFIG_SPI_TX_DMA == 1) */

#if (CONFIG_SPI_RX_DMA == 1)
#if (CONFIG_SPI1_RX_DMA == 1)
void spi1_rx_dma_irq_handler(void) {
    HAL_DMA_IRQHandler(spi_obj[SPI_NUM_1].dev->dma_rx->handle);
}
#endif /* (CONFIG_SPI1_RX_DMA == 1) */
#if (CONFIG_SPI2_RX_DMA == 1)
void spi2_rx_dma_irq_handler(void) {
    HAL_DMA_IRQHandler(spi_obj[SPI_NUM_2].dev->dma_rx->handle);
}
#endif /* (CONFIG_SPI2_RX_DMA == 1) */
#if (CONFIG_SPI3_RX_DMA == 1)
void spi3_rx_dma_irq_handler(void) {
    HAL_DMA_IRQHandler(spi_obj[SPI_NUM_3].dev->dma_rx->handle);
}
#endif /* (CONFIG_SPI3_RX_DMA == 1) */
#if (CONFIG_SPI4_RX_DMA == 1)
void spi4_rx_dma_irq_handler(void) {
    HAL_DMA_IRQHandler(spi_obj[SPI_NUM_4].dev->dma_rx->handle);
}
#endif /* (CONFIG_SPI4_RX_DMA == 1) */
#if (CONFIG_SPI5_RX_DMA == 1)
void spi5_rx_dma_irq_handler(void) {
    HAL_DMA_IRQHandler(spi_obj[SPI_NUM_5].dev->dma_rx->handle);
}
#endif /* (CONFIG_SPI5_RX_DMA == 1) */
#if (CONFIG_SPI6_RX_DMA == 1)
void spi6_rx_dma_irq_handler(void) {
    HAL_DMA_IRQHandler(spi_obj[SPI_NUM_6].dev->dma_rx->handle);
}
#endif /* (CONFIG_SPI6_RX_DMA == 1) */
#endif /* (CONFIG_SPI_RX_DMA == 1) */

/**
 * @brief Register USART IRQ
 */
static void spi_hal_irq_register(void) {
#if (CONFIG_SPI_NUM_1 == 1)
    irq_hal_register_handler(spi_obj[SPI_NUM_1].dev->irq_num, \
                                spi1_irq_handler);
#if (CONFIG_SPI1_TX_DMA == 1)
    irq_hal_register_handler(spi_obj[SPI_NUM_1].dev->dma_tx->irq_num, \
                                spi1_tx_dma_irq_handler);
#endif /* (CONFIG_SPI1_TX_DMA == 1) */
#if (CONFIG_SPI1_RX_DMA == 1)
    irq_hal_register_handler(spi_obj[SPI_NUM_1].dev->dma_rx->irq_num, \
                                spi1_rx_dma_irq_handler);
#endif /* (CONFIG_SPI1_RX_DMA == 1) */
#endif /* (CONFIG_SPI_NUM_1 == 1) */
#if (CONFIG_SPI_NUM_2 == 1)
    irq_hal_register_handler(spi_obj[SPI_NUM_2].dev->irq_num, \
                                spi2_irq_handler);
#if (CONFIG_SPI2_TX_DMA == 1)
    irq_hal_register_handler(spi_obj[SPI_NUM_2].dev->dma_tx->irq_num, \
                                spi2_tx_dma_irq_handler);
#endif /* (CONFIG_SPI2_TX_DMA == 1) */
#if (CONFIG_SPI2_RX_DMA == 1)
    irq_hal_register_handler(spi_obj[SPI_NUM_2].dev->dma_rx->irq_num, \
                                spi2_rx_dma_irq_handler);
#endif /* (CONFIG_SPI2_RX_DMA == 1) */
#endif /* (CONFIG_SPI_NUM_2 == 1) */
#if (CONFIG_SPI_NUM_3 == 1)
    irq_hal_register_handler(spi_obj[SPI_NUM_3].dev->irq_num, \
                                spi3_irq_handler);
#if (CONFIG_SPI3_TX_DMA == 1)
    irq_hal_register_handler(spi_obj[SPI_NUM_3].dev->dma_tx->irq_num, \
                                spi3_tx_dma_irq_handler);
#endif /* (CONFIG_SPI3_TX_DMA == 1) */
#if (CONFIG_SPI3_RX_DMA == 1)
    irq_hal_register_handler(spi_obj[SPI_NUM_3].dev->dma_rx->irq_num, \
                                spi3_rx_dma_irq_handler);
#endif /* (CONFIG_SPI3_RX_DMA == 1) */
#endif /* (CONFIG_SPI_NUM_3 == 1) */
#if (CONFIG_SPI_NUM_4 == 1)
    irq_hal_register_handler(spi_obj[SPI_NUM_4].dev->irq_num, \
                                spi4_irq_handler);
#if (CONFIG_SPI4_TX_DMA == 1)
    irq_hal_register_handler(spi_obj[SPI_NUM_4].dev->dma_tx->irq_num, \
                                spi4_tx_dma_irq_handler);
#endif /* (CONFIG_SPI4_TX_DMA == 1) */
#if (CONFIG_SPI4_RX_DMA == 1)
    irq_hal_register_handler(spi_obj[SPI_NUM_4].dev->dma_rx->irq_num, \
                                spi4_rx_dma_irq_handler);
#endif /* (CONFIG_SPI4_RX_DMA == 1) */
#endif /* (CONFIG_SPI_NUM_4 == 1) */
#if (CONFIG_SPI_NUM_5 == 1)
    irq_hal_register_handler(spi_obj[SPI_NUM_5].dev->irq_num, \
                                spi5_irq_handler);
#if (CONFIG_SPI5_TX_DMA == 1)
    irq_hal_register_handler(spi_obj[SPI_NUM_5].dev->dma_tx->irq_num, \
                                spi5_tx_dma_irq_handler);
#endif /* (CONFIG_SPI5_TX_DMA == 1) */
#if (CONFIG_SPI5_RX_DMA == 1)
    irq_hal_register_handler(spi_obj[SPI_NUM_5].dev->dma_rx->irq_num, \
                                spi5_rx_dma_irq_handler);
#endif /* (CONFIG_SPI5_RX_DMA == 1) */
#endif /* (CONFIG_SPI_NUM_5 == 1) */
#if (CONFIG_SPI_NUM_6 == 1)
    irq_hal_register_handler(spi_obj[SPI_NUM_6].dev->irq_num, \
                                spi6_irq_handler);
#if (CONFIG_SPI6_TX_DMA == 1)
    irq_hal_register_handler(spi_obj[SPI_NUM_6].dev->dma_tx->irq_num, \
                                spi6_tx_dma_irq_handler);
#endif /* (CONFIG_SPI6_TX_DMA == 1) */
#if (CONFIG_SPI6_RX_DMA == 1)
    irq_hal_register_handler(spi_obj[SPI_NUM_6].dev->dma_rx->irq_num, \
                                spi6_rx_dma_irq_handler);
#endif /* (CONFIG_SPI6_RX_DMA == 1) */
#endif /* (CONFIG_SPI_NUM_6 == 1) */
}

/********************* Callback functions **********************/
void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi) {
    spi_obj_t *obj = spi_hal_get_obj(hspi);
    omni_assert_not_null(obj);

    // Clear busy status
    obj->status.busy = 0;

    if (obj->event_cb != NULL) {
        // Set TX complete event
        obj->event_cb(SPI_EVENT_TRANSFER_COMPLETE);
    }
}

void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi) {
    spi_obj_t *obj = spi_hal_get_obj(hspi);
    omni_assert_not_null(obj);

    // Clear busy status
    obj->status.busy = 0;

    if (obj->event_cb != NULL) {
        // Set RX complete event
        obj->event_cb(SPI_EVENT_TRANSFER_COMPLETE);
    }
}

void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi) {
    spi_obj_t *obj = spi_hal_get_obj(hspi);
    omni_assert_not_null(obj);

    // Clear busy status
    obj->status.busy = 0;

    if (obj->event_cb != NULL) {
        // Set TX/RX complete event
        obj->event_cb(SPI_EVENT_TRANSFER_COMPLETE);
    }
}

void HAL_SPI_ErrorCallback(SPI_HandleTypeDef *hspi) {
    uint32_t error;
    uint32_t event = 0;
    spi_obj_t *obj = spi_hal_get_obj(hspi);
    omni_assert_not_null(obj);

    // Clear busy status
    obj->status.busy = 0;

    // Get error
    error = HAL_SPI_GetError(hspi);

    if (error & HAL_SPI_ERROR_OVR) {
        event |= SPI_EVENT_TRANSFER_LOST;
    }

    if (error & HAL_SPI_ERROR_MODF) {
        event |= SPI_EVENT_MODE_FAULT;
    }

    if ((obj->event_cb != NULL) && (event != 0)) {
        // Set error event
        obj->event_cb(event);
    }
}

/********************* Private functions **********************/

/**
 * @brief Configure SPI
 * 
 * @param dev SPI device information
 * @param config Pointer to the SPI driver configuration
 * @return Operation status
 */
static int spi_hal_configure(spi_dev_t *dev, spi_driver_config_t *config) {
    uint32_t spi_clock = 0;
    SPI_HandleTypeDef *handle = dev->handle;

    if ((SPI_OP_DATA_SIZE_GET(config->option) != 8U) && (SPI_OP_DATA_SIZE_GET(config->option) != 16U)) {
        return OMNI_FAIL;
    }

    if (SPI_OP_MODE_GET(config->option) == SPI_OP_MODE_MASTER) {
        handle->Init.Mode = SPI_MODE_MASTER;
    } else {
        handle->Init.Mode = SPI_MODE_SLAVE;
    }

    if (SPI_OP_DIR_LINES_GET(config->option) == SPI_OP_DIR_LINES_SINGLE) {
        handle->Init.Direction = SPI_DIRECTION_1LINE;
    } else {
        handle->Init.Direction = SPI_DIRECTION_2LINES;
    }

    if (SPI_OP_CPOL_GET(config->option) == SPI_OP_CPOL_LOW) {
        handle->Init.CLKPolarity = SPI_POLARITY_LOW;
    } else {
        handle->Init.CLKPolarity = SPI_POLARITY_HIGH;
    }

    if (SPI_OP_CPHA_GET(config->option) == SPI_OP_CPHA_1EDGE) {
        handle->Init.CLKPhase = SPI_PHASE_1EDGE;
    } else {
        handle->Init.CLKPhase = SPI_PHASE_2EDGE;
    }

    if (SPI_OP_DATA_SIZE_GET(config->option) == 8U) {
        handle->Init.DataSize = SPI_DATASIZE_8BIT;
    } else {
        handle->Init.DataSize = SPI_DATASIZE_16BIT;
    }

    if (SPI_OP_BIT_ORDER_GET(config->option) == SPI_OP_BIT_ORDER_MSB) {
        handle->Init.FirstBit = SPI_FIRSTBIT_MSB;
    } else {
        handle->Init.FirstBit = SPI_FIRSTBIT_LSB;
    }

    if (SPI_OP_SLAVE_SEL_GET(config->option) == SPI_OP_SLAVE_SEL_NONE) {
        handle->Init.NSS = SPI_NSS_SOFT;
#if defined(SPI_NSS_PULSE_DISABLE)
        handle->Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
#endif /* SPI_NSS_PULSE_DISABLE */
    } else if (SPI_OP_SLAVE_SEL_GET(config->option) == SPI_OP_SLAVE_SEL_SOFT) {
        handle->Init.NSS = SPI_NSS_SOFT;
#if defined(SPI_NSS_PULSE_DISABLE)
        handle->Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
#endif /* SPI_NSS_PULSE_DISABLE */
    } else {
        if (SPI_OP_MODE_GET(config->option) == SPI_OP_MODE_MASTER) {
            handle->Init.NSS = SPI_NSS_HARD_OUTPUT;
        } else {
            handle->Init.NSS = SPI_NSS_HARD_INPUT;
        }
    }

    if (SPI_OP_PROTOCOL_GET(config->option) == SPI_OP_PROTOCOL_MOTOROLA) {
        handle->Init.TIMode = SPI_TIMODE_DISABLE;
    } else {
        handle->Init.TIMode = SPI_TIMODE_ENABLE;
    }

    // TODO: H7 set NSS and FIFO

    // Set frequency
    spi_clock = spi_hal_get_clock(dev);
    if (spi_clock != 0) {
        if ((spi_clock >> 1) <= config->frequency) {
            handle->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
        } else if ((spi_clock >> 2) <= config->frequency) {
            handle->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
        } else if ((spi_clock >> 3) <= config->frequency) {
            handle->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
        } else if ((spi_clock >> 4) <= config->frequency) {
            handle->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
        } else if ((spi_clock >> 5) <= config->frequency) {
            handle->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
        } else if ((spi_clock >> 6) <= config->frequency) {
            handle->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
        } else if ((spi_clock >> 7) <= config->frequency) {
            handle->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_128;
        } else {
            handle->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
        }
    } else {
        return OMNI_FAIL;
    }

    if (HAL_SPI_Init(handle) != HAL_OK) {
        return OMNI_FAIL;
    }

    return OMNI_OK;
}

/**
 * @brief Get SPI clock
 * 
 * @param dev SPI device information
 * @return SPI clock
 */
static uint32_t spi_hal_get_clock(spi_dev_t *dev) {
    return dev->clock;
}

/**
 * @brief Set GPIO for SPI
 * 
 * @param dev SPI device information
 */
static void spi_hal_set_gpio(spi_dev_t *dev) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    if (dev->mosi_pin != NULL) {
        gpio_hal_enable_clock(dev->mosi_pin->ins);
    }

    if (dev->miso_pin != NULL) {
        gpio_hal_enable_clock(dev->miso_pin->ins);
    }

    if (dev->sck_pin != NULL) {
        gpio_hal_enable_clock(dev->sck_pin->ins);
    }

    if (dev->cs_pin != NULL) {
        gpio_hal_enable_clock(dev->cs_pin->ins);
    }

    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

    if (dev->mosi_pin != NULL) {
        GPIO_InitStruct.Pin = dev->mosi_pin->index;
        GPIO_InitStruct.Alternate = dev->mosi_pin->alternate;
        HAL_GPIO_Init(dev->mosi_pin->ins, &GPIO_InitStruct);
    }

    if (dev->miso_pin != NULL) {
        GPIO_InitStruct.Pin = dev->miso_pin->index;
        GPIO_InitStruct.Alternate = dev->miso_pin->alternate;
        HAL_GPIO_Init(dev->miso_pin->ins, &GPIO_InitStruct);
    }

    if (dev->sck_pin != NULL) {
        GPIO_InitStruct.Pin = dev->sck_pin->index;
        GPIO_InitStruct.Alternate = dev->sck_pin->alternate;
        HAL_GPIO_Init(dev->sck_pin->ins, &GPIO_InitStruct);
    }

    if (dev->cs_pin != NULL) {
        GPIO_InitStruct.Pin = dev->cs_pin->index;
        GPIO_InitStruct.Alternate = dev->cs_pin->alternate;
        HAL_GPIO_Init(dev->cs_pin->ins, &GPIO_InitStruct);
    }
}

/**
 * @brief Reset GPIO for SPI
 * 
 * @param dev SPI device information
 */
static void spi_hal_reset_gpio(spi_dev_t *dev) {
    if (dev->mosi_pin != NULL) {
        HAL_GPIO_DeInit(dev->mosi_pin->ins, dev->mosi_pin->index);
    }

    if (dev->miso_pin != NULL) {
        HAL_GPIO_DeInit(dev->miso_pin->ins, dev->miso_pin->index);
    }

    if (dev->sck_pin != NULL) {
        HAL_GPIO_DeInit(dev->sck_pin->ins, dev->sck_pin->index);
    }

    if (dev->cs_pin != NULL) {
        HAL_GPIO_DeInit(dev->cs_pin->ins, dev->cs_pin->index);
    }
}

/**
 * @brief Enable SPI clock
 * 
 * @param spi_num SPI number
 *
 * @return Operation status
 */
static int spi_hal_enable_clock(spi_num_t spi_num) {
#if defined(CONFIG_SPI_CLOCK)
    RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
#endif /* CONFIG_SPI_CLOCK */

    switch (spi_num) {
#if defined(SPI1) && (CONFIG_SPI_NUM_1 == 1)
        case SPI_NUM_1:
#if defined(CONFIG_SPI_CLOCK)
            PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_SPI1;
            PeriphClkInitStruct.Spi123ClockSelection = CONFIG_SPI1_CLK_SRC;
            if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK) {
                return OMNI_FAIL;
            }
#endif /* CONFIG_SPI_CLOCK */
            __HAL_RCC_SPI1_CLK_ENABLE();
            break;
#endif /* SPI1 && (CONFIG_SPI_NUM_1 == 1) */

#if defined(SPI2) && (CONFIG_SPI_NUM_2 == 1)
        case SPI_NUM_2:
            __HAL_RCC_SPI2_CLK_ENABLE();
            break;
#endif /* SPI2 && (CONFIG_SPI_NUM_2 == 1) */

#if defined(SPI3) && (CONFIG_SPI_NUM_3 == 1)
        case SPI_NUM_3:
            __HAL_RCC_SPI3_CLK_ENABLE();
            break;
#endif /* SPI3 && (CONFIG_SPI_NUM_3 == 1) */

#if defined(SPI4) && (CONFIG_SPI_NUM_4 == 1)
        case SPI_NUM_4:
            __HAL_RCC_SPI4_CLK_ENABLE();
            break;
#endif /* SPI4 && (CONFIG_SPI_NUM_4 == 1) */

#if defined(SPI5) && (CONFIG_SPI_NUM_5 == 1)
        case SPI_NUM_5:
            __HAL_RCC_SPI5_CLK_ENABLE();
            break;
#endif /* SPI5 && (CONFIG_SPI_NUM_5 == 1) */

#if defined(SPI6) && (CONFIG_SPI_NUM_6 == 1)
        case SPI_NUM_6:
            __HAL_RCC_SPI6_CLK_ENABLE();
            break;
#endif /* SPI6 && (CONFIG_SPI_NUM_6 == 1) */

        default:
            return OMNI_FAIL;
    }

    return OMNI_OK;
}

/**
 * @brief Reset SPI clock
 * 
 * @param spi_num SPI number
 */
static void spi_hal_reset_clock(spi_num_t spi_num) {
    switch (spi_num) {
#if defined(SPI1) && (CONFIG_SPI_NUM_1 == 1)
        case SPI_NUM_1:
            __HAL_RCC_SPI1_CLK_DISABLE();
            break;
#endif /* SPI1 && (CONFIG_SPI_NUM_1 == 1) */

#if defined(SPI2) && (CONFIG_SPI_NUM_2 == 1)
        case SPI_NUM_2:
            __HAL_RCC_SPI2_CLK_DISABLE();
            break;
#endif /* SPI2 && (CONFIG_SPI_NUM_2 == 1) */

#if defined(SPI3) && (CONFIG_SPI_NUM_3 == 1)
        case SPI_NUM_3:
            __HAL_RCC_SPI3_CLK_DISABLE();
            break;
#endif /* SPI3 && (CONFIG_SPI_NUM_3 == 1) */

#if defined(SPI4) && (CONFIG_SPI_NUM_4 == 1)
        case SPI_NUM_4:
            __HAL_RCC_SPI4_CLK_DISABLE();
            break;
#endif /* SPI4 && (CONFIG_SPI_NUM_4 == 1) */

#if defined(SPI5) && (CONFIG_SPI_NUM_5 == 1)
        case SPI_NUM_5:
            __HAL_RCC_SPI5_CLK_DISABLE();
            break;
#endif /* SPI5 && (CONFIG_SPI_NUM_5 == 1) */

#if defined(SPI6) && (CONFIG_SPI_NUM_6 == 1)
        case SPI_NUM_6:
            __HAL_RCC_SPI6_CLK_DISABLE();
            break;
#endif /* SPI6 && (CONFIG_SPI_NUM_6 == 1) */

        default:
            break;
    }
}

/**
 * @brief Get SPI object
 * 
 * @param hspi SPI handle
 * @return Pointer to SPI object
 */
static spi_obj_t *spi_hal_get_obj(SPI_HandleTypeDef *hspi) {
    spi_obj_t *obj = NULL;

#if defined(SPI1) && (CONFIG_SPI_NUM_1 == 1)
    if (hspi->Instance == SPI1) {
        obj = &spi_obj[SPI_NUM_1];
    }
#endif /* SPI1 && (CONFIG_SPI_NUM_1 == 1) */

#if defined(SPI2) && (CONFIG_SPI_NUM_2 == 1)
    if (hspi->Instance == SPI2) {
        obj = &spi_obj[SPI_NUM_2];
    }
#endif /* SPI2 && (CONFIG_SPI_NUM_2 == 1) */

#if defined(SPI3) && (CONFIG_SPI_NUM_3 == 1)
    if (hspi->Instance == SPI3) {
        obj = &spi_obj[SPI_NUM_3];
    }
#endif /* SPI3 && (CONFIG_SPI_NUM_3 == 1) */

#if defined(SPI4) && (CONFIG_SPI_NUM_4 == 1)
    if (hspi->Instance == SPI4) {
        obj = &spi_obj[SPI_NUM_4];
    }
#endif /* SPI4 && (CONFIG_SPI_NUM_4 == 1) */

#if defined(SPI5) && (CONFIG_SPI_NUM_5 == 1)
    if (hspi->Instance == SPI5) {
        obj = &spi_obj[SPI_NUM_5];
    }
#endif /* SPI5 && (CONFIG_SPI_NUM_5 == 1) */

#if defined(SPI6) && (CONFIG_SPI_NUM_6 == 1)
    if (hspi->Instance == SPI6) {
        obj = &spi_obj[SPI_NUM_6];
    }
#endif /* SPI6 && (CONFIG_SPI_NUM_6 == 1) */

    return obj;
}
