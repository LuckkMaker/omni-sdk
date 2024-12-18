/**
  * @file    i2c_hal.c
  * @author  LuckkMaker
  * @brief   I2C HAL driver
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
#include "drivers/i2c.h"
#include "hal/gpio_hal.h"
#include "hal/dma_hal.h"
#include "hal/irq_hal.h"
#include "ll/i2c_ll.h"

#define I2C_CHECK_DEV_READY_TIMEOUT     1000

static i2c_obj_t i2c_obj[I2C_NUM_MAX];

static int i2c_hal_init(i2c_num_t i2c_num, i2c_driver_config_t *config);
static int i2c_hal_deinit(i2c_num_t i2c_num);
static void i2c_hal_start(i2c_num_t i2c_num);
static void i2c_hal_stop(i2c_num_t i2c_num);
static int i2c_hal_master_transmit(i2c_num_t i2c_num, uint16_t addr, const uint8_t *data, uint32_t len, uint8_t pending);
static int i2c_hal_master_receive(i2c_num_t i2c_num, uint16_t addr, uint8_t *data, uint32_t len, uint8_t pending);
static int i2c_hal_slave_transmit(i2c_num_t i2c_num, const uint8_t *data, uint32_t len);
static int i2c_hal_slave_receive(i2c_num_t i2c_num, uint8_t *data, uint32_t len);
static int i2c_hal_write(i2c_num_t i2c_num, uint16_t dev_addr, uint16_t mem_addr, i2c_mem_addr_size_t mem_addr_size, const uint8_t *data, uint16_t len);
static int i2c_hal_read(i2c_num_t i2c_num, uint16_t dev_addr, uint16_t mem_addr, i2c_mem_addr_size_t mem_addr_size, uint8_t *data, uint16_t len);
static int i2c_hal_is_device_ready(i2c_num_t i2c_num, uint16_t dev_addr, uint32_t trials);
static i2c_driver_status_t i2c_hal_get_status(i2c_num_t i2c_num);
static i2c_driver_error_t i2c_hal_get_error(i2c_num_t i2c_num);

const struct i2c_driver_api i2c_driver = {
    .init = i2c_hal_init,
    .deinit = i2c_hal_deinit,
    .start = i2c_hal_start,
    .stop = i2c_hal_stop,
    .master_transmit = i2c_hal_master_transmit,
    .master_receive = i2c_hal_master_receive,
    .slave_transmit = i2c_hal_slave_transmit,
    .slave_receive = i2c_hal_slave_receive,
    .write = i2c_hal_write,
    .read = i2c_hal_read,
    .is_device_ready = i2c_hal_is_device_ready,
    .get_status = i2c_hal_get_status,
    .get_error = i2c_hal_get_error,
};

static void i2c_hal_irq_register(void);
static void i2c_hal_er_irq_request(i2c_obj_t *obj);
static void i2c_hal_ev_irq_request(i2c_obj_t *obj);
static void i2c_hal_set_gpio(i2c_dev_t *dev);
static void i2c_hal_reset_gpio(i2c_dev_t *dev);
static void i2c_hal_enable_clock(i2c_num_t i2c_num);
static void i2c_hal_reset_clock(i2c_num_t i2c_num);
static i2c_obj_t *i2c_hal_get_obj(I2C_HandleTypeDef *hi2c);

/**
 * @brief Open I2C bus
 * 
 * @param i2c_num I2C number
 * @param config Pointer to the I2C driver configuration
 * @return Operation status
 */
static int i2c_hal_init(i2c_num_t i2c_num, i2c_driver_config_t *config) {
    omni_assert(i2c_num < I2C_NUM_MAX);
    omni_assert_not_null(config);

    i2c_obj_t *obj = &i2c_obj[i2c_num];

    // Set event callback
    if (config->event_cb != NULL) {
        obj->event_cb = config->event_cb;
    } else {
        obj->event_cb = NULL;
    }

    // Get dev information
    obj->dev = i2c_ll_get_dev(i2c_num);
    omni_assert_not_null(obj->dev);

    I2C_HandleTypeDef *handle = obj->dev->handle;

    // Clear status
    obj->status = (i2c_driver_status_t){0};

    // Clear error
    obj->error = (i2c_driver_error_t){0};

    // Register IRQ
    i2c_hal_irq_register();

    // Enable I2C clock
    i2c_hal_enable_clock(i2c_num);

    // Initialize GPIO
    i2c_hal_set_gpio(obj->dev);

    // Initialize DMA
#if (CONFIG_I2C_TX_DMA == 1)
    // Configure DMA TX
    if (obj->dev->dma_tx != NULL) {
        dma_hal_enable_clock(obj->dev->dma_tx->ins);

        if (HAL_DMA_Init(obj->dev->dma_tx->handle) != HAL_OK) {
            return OMNI_FAIL;
        }

        __HAL_LINKDMA(handle, hdmatx, *(obj->dev->dma_tx->handle));

        NVIC_ClearPendingIRQ(obj->dev->dma_tx->irq_num);
        NVIC_SetPriority(obj->dev->dma_tx->irq_num, \
                        NVIC_EncodePriority(NVIC_GetPriorityGrouping(), obj->dev->dma_tx->irq_prio, 0));
        NVIC_EnableIRQ(obj->dev->dma_tx->irq_num);
    }
#endif /* (CONFIG_I2C_TX_DMA == 1) */

#if (CONFIG_I2C_RX_DMA == 1)
     // Configure DMA RX
    if (obj->dev->dma_rx != NULL) {
        dma_hal_enable_clock(obj->dev->dma_rx->ins);

        if (HAL_DMA_Init(obj->dev->dma_rx->handle) != HAL_OK) {
            return OMNI_FAIL;
        }

        __HAL_LINKDMA(handle, hdmarx, *(obj->dev->dma_rx->handle));

        NVIC_ClearPendingIRQ(obj->dev->dma_rx->irq_num);
        NVIC_SetPriority(obj->dev->dma_rx->irq_num, \
                        NVIC_EncodePriority(NVIC_GetPriorityGrouping(), obj->dev->dma_rx->irq_prio, 0));
        NVIC_EnableIRQ(obj->dev->dma_rx->irq_num);
    }
#endif /* (CONFIG_I2C_RX_DMA == 1) */

    // Initialize IRQ
    NVIC_ClearPendingIRQ(obj->dev->er_irq_num);
    NVIC_SetPriority(obj->dev->er_irq_num, \
                    NVIC_EncodePriority(NVIC_GetPriorityGrouping(), obj->dev->er_irq_prio, 0));
    NVIC_EnableIRQ(obj->dev->er_irq_num);

    NVIC_ClearPendingIRQ(obj->dev->ev_irq_num);
    NVIC_SetPriority(obj->dev->ev_irq_num, \
                    NVIC_EncodePriority(NVIC_GetPriorityGrouping(), obj->dev->ev_irq_prio, 0));
    NVIC_EnableIRQ(obj->dev->ev_irq_num);

    // Initialize I2C
    handle->Init.DutyCycle = I2C_DUTYCYCLE_2;
    handle->Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    handle->Init.OwnAddress2 = 0;
    handle->Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    handle->Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

    switch (config->bus_speed) {
        case I2C_BUS_SPEED_STANDARD:
            handle->Init.ClockSpeed = 100000;
            break;
        case I2C_BUS_SPEED_FAST:
            handle->Init.ClockSpeed = 400000;
            break;

        default:
            handle->Init.ClockSpeed = 100000;
            break;
    }

    switch (config->own_addr_bits) {
        case I2C_ADDR_BITS_7:
            handle->Init.OwnAddress1 = config->own_addr & 0x7F;
            handle->Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
            break;
        case I2C_ADDR_BITS_10:
            handle->Init.OwnAddress1 = config->own_addr & 0x3FF;
            handle->Init.AddressingMode = I2C_ADDRESSINGMODE_10BIT;
            break;

        default:
            handle->Init.OwnAddress1 = config->own_addr & 0x7F;
            handle->Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
            break;
    }

    if (HAL_I2C_Init(handle) != HAL_OK) {
        return OMNI_FAIL;
    }

    // Set initialized status
    obj->status.is_initialized = 1;
    // Call event callback
    if (obj->event_cb != NULL) {
        // Set initialized event
        obj->event_cb(I2C_EVENT_INITIALIZED);
    }

    return OMNI_OK;
}

/**
 * @brief Close I2C bus
 * 
 * @param i2c_num I2C number
 * @return Operation status
 */
static int i2c_hal_deinit(i2c_num_t i2c_num) {
    omni_assert(i2c_num < I2C_NUM_MAX);

    i2c_obj_t *obj = &i2c_obj[i2c_num];
    omni_assert_not_null(obj);

    // Reset I2C clock
    i2c_hal_reset_clock(i2c_num);

    // Reset GPIO
    i2c_hal_reset_gpio(obj->dev);

#if (CONFIG_I2C_TX_DMA == 1)
    // Deinitialize I2C DMA TX
    if (obj->dev->dma_tx != NULL) {
        HAL_DMA_DeInit(obj->dev->dma_tx->handle);
    }
#endif /* (CONFIG_I2C_TX_DMA == 1) */

#if (CONFIG_I2C_RX_DMA == 1)
    // Deinitialize I2C DMA RX
    if (obj->dev->dma_rx != NULL) {
        HAL_DMA_DeInit(obj->dev->dma_rx->handle);
    }
#endif /* (CONFIG_I2C_RX_DMA == 1) */

    // Disable I2C IRQ
    NVIC_DisableIRQ(obj->dev->er_irq_num);
    NVIC_DisableIRQ(obj->dev->ev_irq_num);

#if (CONFIG_I2C_TX_DMA == 1)
    // Disable I2C DMA IRQ
    if (obj->dev->dma_tx != NULL) {
        NVIC_DisableIRQ(obj->dev->dma_tx->irq_num);
    }
#endif /* (CONFIG_I2C_TX_DMA == 1) */

#if (CONFIG_I2C_RX_DMA == 1)
    if (obj->dev->dma_rx != NULL) {
        NVIC_DisableIRQ(obj->dev->dma_rx->irq_num);
    }
#endif /* (CONFIG_I2C_RX_DMA == 1) */

    // Clear object
    if (obj->dev != NULL) {
        obj->dev = NULL;
    }

    if (obj->event_cb != NULL) {
        obj->event_cb = NULL;
    }

    i2c_obj[i2c_num] = (i2c_obj_t){0};

    return OMNI_OK;
}

/**
 * @brief Start I2C bus
 * 
 * @param i2c_num I2C number
 */
static void i2c_hal_start(i2c_num_t i2c_num) {
    omni_assert(i2c_num < I2C_NUM_MAX);

    i2c_obj_t *obj = &i2c_obj[i2c_num];
    omni_assert_not_null(obj);

    I2C_HandleTypeDef *handle = obj->dev->handle;

    // Enable I2C
    __HAL_I2C_ENABLE(handle);
}

/**
 * @brief Stop I2C bus
 * 
 * @param i2c_num I2C number
 */
static void i2c_hal_stop(i2c_num_t i2c_num) {
    omni_assert(i2c_num < I2C_NUM_MAX);

    i2c_obj_t *obj = &i2c_obj[i2c_num];
    omni_assert_not_null(obj);

    I2C_HandleTypeDef *handle = obj->dev->handle;

    // Disable I2C
    __HAL_I2C_DISABLE(handle);
}

/**
 * @brief I2C master transmit
 * 
 * @param i2c_num I2C number
 * @param addr Slave address
 * @param data Pointer to data buffer
 * @param len Data length
 * @return Operation status
 */
static int i2c_hal_master_transmit(i2c_num_t i2c_num, uint16_t addr, const uint8_t *data, uint32_t len, uint8_t pending) {
    HAL_StatusTypeDef status;
    uint16_t addr_temp;
    uint32_t option;
    omni_assert(i2c_num < I2C_NUM_MAX);
    omni_assert_not_null(data);
    omni_assert_non_zero(len);

    i2c_obj_t *obj = &i2c_obj[i2c_num];
    omni_assert_not_null(obj);

    if ((addr & ~((uint32_t)I2C_ADDR_10_BITS_FLAG | (uint32_t)I2C_ADDR_GENERAL_CALL_FLAG)) > 0x3FFU) {
        return OMNI_FAIL;
    }

    if (obj->status.busy) {
        return OMNI_BUSY;
    }

    I2C_HandleTypeDef *handle = obj->dev->handle;

    addr_temp = (addr & 0x3FFU);
    if (handle->Init.AddressingMode == I2C_ADDRESSINGMODE_7BIT) {
        addr_temp <<= 1;
    }

    obj->status.busy = 1;

    if (pending) {  // If transfer should not generate STOP at the end
        if (obj->flags.no_stop == 0U) {  // First transfer without STOP generation
            obj->flags.no_stop = 1U;
            option = I2C_FIRST_FRAME;
        } else {  // Any further transfer without STOP generation
            option = I2C_OTHER_FRAME;
        }
    } else {  // If transfer should generate STOP at the end
        if (obj->flags.no_stop != 0U) {
            // If previous request did not generate STOP after transfer, terminate sequence
            obj->flags.no_stop = 0U;
            option = I2C_OTHER_AND_LAST_FRAME;
        } else {
            option = I2C_LAST_FRAME;
        }
    }

#if (CONFIG_I2C_TX_DMA == 1)
    status = HAL_I2C_Master_Seq_Transmit_DMA(handle, addr_temp, (uint8_t *)data, len, option);
#else
    status = HAL_I2C_Master_Seq_Transmit_IT(handle, addr_temp, (uint8_t *)data, len, option);
#endif /* (CONFIG_USART_TX_DMA == 1) */

    if (status == HAL_ERROR) {
        obj->status.busy = 0;
        return OMNI_FAIL;
    }

    return OMNI_OK;
}

/**
 * @brief I2C master receive
 * 
 * @param i2c_num I2C number
 * @param addr Slave address
 * @param data Pointer to data buffer
 * @param len Data length
 * @param pending Pending flag
 * @return Operation status
 */
static int i2c_hal_master_receive(i2c_num_t i2c_num, uint16_t addr, uint8_t *data, uint32_t len, uint8_t pending) {
    HAL_StatusTypeDef status;
    uint16_t addr_temp;
    uint32_t option;
    omni_assert(i2c_num < I2C_NUM_MAX);
    omni_assert_not_null(data);
    omni_assert_non_zero(len);

    i2c_obj_t *obj = &i2c_obj[i2c_num];
    omni_assert_not_null(obj);

    if ((addr & ~((uint32_t)I2C_ADDR_10_BITS_FLAG | (uint32_t)I2C_ADDR_GENERAL_CALL_FLAG)) > 0x3FFU) {
        return OMNI_FAIL;
    }

    if (obj->status.busy) {
        return OMNI_BUSY;
    }

    I2C_HandleTypeDef *handle = obj->dev->handle;

    addr_temp = (addr & 0x3FFU);
    if (handle->Init.AddressingMode == I2C_ADDRESSINGMODE_7BIT) {
        addr_temp <<= 1;
    }

    obj->status.busy = 1;

    if (pending) {  // If transfer should not generate STOP at the end
        if (obj->flags.no_stop == 0U) {  // First transfer without STOP generation
            obj->flags.no_stop = 1U;
            option = I2C_FIRST_FRAME;
        } else {  // Any further transfer without STOP generation
            option = I2C_OTHER_FRAME;
        }
    } else {  // If transfer should generate STOP at the end
        if (obj->flags.no_stop != 0U) {
            // If previous request did not generate STOP after transfer, terminate sequence
            obj->flags.no_stop = 0U;
            option = I2C_OTHER_AND_LAST_FRAME;
        } else {
            option = I2C_LAST_FRAME;
        }
    }

#if (CONFIG_I2C_RX_DMA == 1)
    status = HAL_I2C_Master_Seq_Receive_DMA(handle, addr_temp, data, len, option);
#else
    status = HAL_I2C_Master_Seq_Receive_IT(handle, addr_temp, data, len, option);
#endif /* (CONFIG_USART_RX_DMA == 1) */

    if (status == HAL_ERROR) {
        obj->status.busy = 0;
        return OMNI_FAIL;
    }

    return OMNI_OK;
}

/**
 * @brief I2C slave transmit
 * 
 * @param i2c_num I2C number
 * @param data Pointer to data buffer
 * @param len Data length
 * @return Operation status
 */
static int i2c_hal_slave_transmit(i2c_num_t i2c_num, const uint8_t *data, uint32_t len) {
    HAL_StatusTypeDef status;
    omni_assert(i2c_num < I2C_NUM_MAX);
    omni_assert_not_null(data);
    omni_assert_non_zero(len);

    i2c_obj_t *obj = &i2c_obj[i2c_num];
    omni_assert_not_null(obj);

    if (len > UINT16_MAX) {
        // HAL does not handle 32-bit count in transfer
        return OMNI_FAIL;
    }

    if (obj->status.busy) {
        return OMNI_BUSY;
    }

    I2C_HandleTypeDef *handle = obj->dev->handle;

    if (HAL_I2C_GetState(handle) != HAL_I2C_STATE_LISTEN) {
        return OMNI_FAIL;
    }

    // Clear status
    obj->status = (i2c_driver_status_t){0};

    // Clear error
    obj->error = (i2c_driver_error_t){0};

    obj->status.busy = 1;
    obj->flags.xfer_set = 1;

#if (CONFIG_I2C_TX_DMA == 1)
    status = HAL_I2C_Slave_Seq_Transmit_DMA(handle, (uint8_t *)data, len, I2C_NEXT_FRAME);
#else
    status = HAL_I2C_Slave_Seq_Transmit_IT(handle, (uint8_t *)data, len, I2C_NEXT_FRAME);
#endif /* (CONFIG_I2C_TX_DMA == 1) */

    if (status == HAL_ERROR) {
        obj->status.busy = 0;
        return OMNI_FAIL;
    }

    return OMNI_OK;
}

/**
 * @brief I2C slave receive
 * 
 * @param i2c_num I2C number
 * @param data Pointer to data buffer
 * @param len Data length
 * @return Operation status
 */
static int i2c_hal_slave_receive(i2c_num_t i2c_num, uint8_t *data, uint32_t len) {
    HAL_StatusTypeDef status;
    omni_assert(i2c_num < I2C_NUM_MAX);
    omni_assert_not_null(data);
    omni_assert_non_zero(len);

    i2c_obj_t *obj = &i2c_obj[i2c_num];
    omni_assert_not_null(obj);

    if (len > UINT16_MAX) {
        // HAL does not handle 32-bit count in transfer
        return OMNI_FAIL;
    }

    if (obj->status.busy) {
        return OMNI_BUSY;
    }

    // Clear status
    obj->status = (i2c_driver_status_t){0};

    // Clear error
    obj->error = (i2c_driver_error_t){0};

    obj->status.busy = 1;
    obj->flags.xfer_set = 1;

    I2C_HandleTypeDef *handle = obj->dev->handle;

#if (CONFIG_I2C_RX_DMA == 1)
    status = HAL_I2C_Slave_Seq_Receive_DMA(handle, (uint8_t *)data, len, I2C_NEXT_FRAME);
#else
    status = HAL_I2C_Slave_Seq_Receive_IT(handle, (uint8_t *)data, len, I2C_NEXT_FRAME);
#endif /* (CONFIG_I2C_RX_DMA == 1) */

    if (status == HAL_ERROR) {
        obj->status.busy = 0;
        return OMNI_FAIL;
    }

    return OMNI_OK;
}

/**
 * @brief I2C write memory
 * 
 * @param i2c_num I2C number
 * @param dev_addr Device address
 * @param mem_addr Memory address
 * @param mem_addr_size Memory address size
 * @param data Pointer to data buffer
 * @param len Data length
 * @return Operation status
 */
static int i2c_hal_write(i2c_num_t i2c_num, uint16_t dev_addr, uint16_t mem_addr, i2c_mem_addr_size_t mem_addr_size, const uint8_t *data, uint16_t len) {
    HAL_StatusTypeDef status;
    uint16_t addr_temp;
    uint32_t mem_addr_temp;
    omni_assert(i2c_num < I2C_NUM_MAX);
    omni_assert_not_null(data);
    omni_assert_non_zero(len);

    i2c_obj_t *obj = &i2c_obj[i2c_num];
    omni_assert_not_null(obj);

    if ((dev_addr & ~((uint32_t)I2C_ADDR_10_BITS_FLAG | (uint32_t)I2C_ADDR_GENERAL_CALL_FLAG)) > 0x3FFU) {
        return OMNI_FAIL;
    }

    if (obj->status.busy) {
        return OMNI_BUSY;
    }

    I2C_HandleTypeDef *handle = obj->dev->handle;

    addr_temp = (dev_addr & 0x3FFU);
    if (handle->Init.AddressingMode == I2C_ADDRESSINGMODE_7BIT) {
        addr_temp <<= 1;
    }

    obj->status.busy = 1;

    if (mem_addr_size == I2C_MEM_ADDR_SIZE_8) {
        mem_addr_temp = I2C_MEMADD_SIZE_8BIT;
    } else {
        mem_addr_temp = I2C_MEMADD_SIZE_16BIT;
    }

#if (CONFIG_I2C_TX_DMA == 1)
    status = HAL_I2C_Mem_Write_DMA(handle, addr_temp, mem_addr, mem_addr_temp, (uint8_t *)data, len);
#else
    status = HAL_I2C_Mem_Write_IT(handle, addr_temp, mem_addr, mem_addr_temp, (uint8_t *)data, len);
#endif /* (CONFIG_USART_TX_DMA == 1) */

    if (status == HAL_ERROR) {
        obj->status.busy = 0;
        return OMNI_FAIL;
    }

    return OMNI_OK;
}

/**
 * @brief I2C read memory
 * 
 * @param i2c_num I2C number
 * @param dev_addr Device address
 * @param mem_addr Memory address
 * @param mem_addr_size Memory address size
 * @param data Pointer to data buffer
 * @param len Data length
 * @return Operation status
 */
static int i2c_hal_read(i2c_num_t i2c_num, uint16_t dev_addr, uint16_t mem_addr, i2c_mem_addr_size_t mem_addr_size, uint8_t *data, uint16_t len) {
    HAL_StatusTypeDef status;
    uint16_t addr_temp;
    uint32_t mem_addr_temp;
    omni_assert(i2c_num < I2C_NUM_MAX);
    omni_assert_not_null(data);
    omni_assert_non_zero(len);

    i2c_obj_t *obj = &i2c_obj[i2c_num];
    omni_assert_not_null(obj);

    if ((dev_addr & ~((uint32_t)I2C_ADDR_10_BITS_FLAG | (uint32_t)I2C_ADDR_GENERAL_CALL_FLAG)) > 0x3FFU) {
        return OMNI_FAIL;
    }

    if (obj->status.busy) {
        return OMNI_BUSY;
    }

    I2C_HandleTypeDef *handle = obj->dev->handle;

    addr_temp = (dev_addr & 0x3FFU);
    if (handle->Init.AddressingMode == I2C_ADDRESSINGMODE_7BIT) {
        addr_temp <<= 1;
    }

    obj->status.busy = 1;

    if (mem_addr_size == I2C_MEM_ADDR_SIZE_8) {
        mem_addr_temp = I2C_MEMADD_SIZE_8BIT;
    } else {
        mem_addr_temp = I2C_MEMADD_SIZE_16BIT;
    }

#if (CONFIG_I2C_RX_DMA == 1)
    status = HAL_I2C_Mem_Read_DMA(handle, addr_temp, mem_addr, mem_addr_temp, data, len);
#else
    status = HAL_I2C_Mem_Read_IT(handle, addr_temp, mem_addr, mem_addr_temp, data, len);
#endif /* (CONFIG_USART_RX_DMA == 1) */

    if (status == HAL_ERROR) {
        obj->status.busy = 0;
        return OMNI_FAIL;
    }

    return OMNI_OK;
}

/**
 * @brief I2C check device ready
 * 
 * @param i2c_num I2C number
 * @param dev_addr Device address
 * @param trials Number of trials
 * @return Operation status
 */
static int i2c_hal_is_device_ready(i2c_num_t i2c_num, uint16_t dev_addr, uint32_t trials) {
    uint16_t addr_temp;
    omni_assert(i2c_num < I2C_NUM_MAX);

    i2c_obj_t *obj = &i2c_obj[i2c_num];
    omni_assert_not_null(obj);

    if ((dev_addr & ~((uint32_t)I2C_ADDR_10_BITS_FLAG | (uint32_t)I2C_ADDR_GENERAL_CALL_FLAG)) > 0x3FFU) {
        return OMNI_FAIL;
    }

    if (obj->status.busy) {
        return OMNI_BUSY;
    }

    I2C_HandleTypeDef *handle = obj->dev->handle;

    addr_temp = (dev_addr & 0x3FFU);
    if (handle->Init.AddressingMode == I2C_ADDRESSINGMODE_7BIT) {
        addr_temp <<= 1;
    }

    obj->status.busy = 1;

    if (HAL_I2C_IsDeviceReady(handle, addr_temp, trials, I2C_CHECK_DEV_READY_TIMEOUT) != HAL_OK) {
        obj->status.busy = 0;
        return OMNI_FAIL;
    }

    obj->status.busy = 0;

    return OMNI_OK;
}

/**
 * @brief I2C get status
 *
 * @param i2c_num I2C number
 * @return I2C driver status
 */
static i2c_driver_status_t i2c_hal_get_status(i2c_num_t i2c_num) {
    omni_assert(i2c_num < I2C_NUM_MAX);

    i2c_obj_t *obj = &i2c_obj[i2c_num];
    omni_assert_not_null(obj);

    return obj->status;
}

/**
 * @brief I2C get error
 *
 * @param i2c_num I2C number
 * @return I2C driver error
 */
static i2c_driver_error_t i2c_hal_get_error(i2c_num_t i2c_num) {
    omni_assert(i2c_num < I2C_NUM_MAX);

    i2c_obj_t *obj = &i2c_obj[i2c_num];
    omni_assert_not_null(obj);

    return obj->error;
}

/********************* IRQ handlers **********************/
/**
 * @brief I2C event IRQ handler
 */
static void i2c_hal_ev_irq_request(i2c_obj_t *obj) {
    HAL_I2C_EV_IRQHandler(obj->dev->handle);
}
/**
 * @brief I2C error IRQ handler
 */
static void i2c_hal_er_irq_request(i2c_obj_t *obj) {
    HAL_I2C_ER_IRQHandler(obj->dev->handle);
}
#if (CONFIG_I2C_NUM_1 == 1)
/**
 * @brief I2C1 event IRQ handler
 */
static void i2c1_event_irq_handler(void) {
    i2c_hal_ev_irq_request(&i2c_obj[I2C_NUM_1]);
}
/**
 * @brief I2C1 error IRQ handler
 */
static void i2c1_error_irq_handler(void) {
    i2c_hal_er_irq_request(&i2c_obj[I2C_NUM_1]);
}
#endif /* (CONFIG_I2C_NUM_1 == 1) */
#if (CONFIG_I2C_NUM_2 == 1)
/**
 * @brief I2C2 event IRQ handler
 */
static void i2c2_event_irq_handler(void) {
    i2c_hal_ev_irq_request(&i2c_obj[I2C_NUM_2]);
}
/**
 * @brief I2C2 error IRQ handler
 */
static void i2c2_error_irq_handler(void) {
    i2c_hal_er_irq_request(&i2c_obj[I2C_NUM_2]);
}
#endif /* (CONFIG_I2C_NUM_2 == 1) */
#if (CONFIG_I2C_NUM_3 == 1)
/**
 * @brief I2C3 event IRQ handler
 */
static void i2c3_event_irq_handler(void) {
    i2c_hal_ev_irq_request(&i2c_obj[I2C_NUM_3]);
}
/**
 * @brief I2C3 error IRQ handler
 */
static void i2c3_error_irq_handler(void) {
    i2c_hal_er_irq_request(&i2c_obj[I2C_NUM_3]);
}
#endif /* (CONFIG_I2C_NUM_3 == 1) */

#if (CONFIG_I2C_TX_DMA == 1)
#if (CONFIG_I2C1_TX_DMA == 1)
void i2c1_tx_dma_irq_handler(void) {
    HAL_DMA_IRQHandler(i2c_obj[I2C_NUM_1].dev->dma_tx->handle);
}
#endif /* (CONFIG_I2C1_TX_DMA == 1) */
#if (CONFIG_I2C2_TX_DMA == 1)
void i2c2_tx_dma_irq_handler(void) {
    HAL_DMA_IRQHandler(i2c_obj[I2C_NUM_2].dev->dma_tx->handle);
}
#endif /* (CONFIG_I2C2_TX_DMA == 1) */
#if (CONFIG_I2C3_TX_DMA == 1)
void i2c3_tx_dma_irq_handler(void) {
    HAL_DMA_IRQHandler(i2c_obj[I2C_NUM_3].dev->dma_tx->handle);
}
#endif /* (CONFIG_I2C3_TX_DMA == 1) */
#endif /*(CONFIG_I2C_TX_DMA == 1) */

#if (CONFIG_I2C_RX_DMA == 1)
#if (CONFIG_I2C1_RX_DMA == 1)
void i2c1_rx_dma_irq_handler(void) {
    HAL_DMA_IRQHandler(i2c_obj[I2C_NUM_1].dev->dma_rx->handle);
}
#endif /* (CONFIG_I2C1_RX_DMA == 1) */
#if (CONFIG_I2C2_RX_DMA == 1)
void i2c2_rx_dma_irq_handler(void) {
    HAL_DMA_IRQHandler(i2c_obj[I2C_NUM_2].dev->dma_rx->handle);
}
#endif /* (CONFIG_I2C2_RX_DMA == 1) */
#if (CONFIG_I2C3_RX_DMA == 1)
void i2c3_rx_dma_irq_handler(void) {
    HAL_DMA_IRQHandler(i2c_obj[I2C_NUM_3].dev->dma_rx->handle);
}
#endif /* (CONFIG_I2C3_RX_DMA == 1) */
#endif /*(CONFIG_I2C_RX_DMA == 1) */

/**
 * @brief Register I2C IRQ
 */
static void i2c_hal_irq_register(void) {
#if (CONFIG_I2C_NUM_1 == 1)
    irq_hal_register_handler(i2c_obj[I2C_NUM_1].dev->er_irq_num, \
                                i2c1_error_irq_handler);
    irq_hal_register_handler(i2c_obj[I2C_NUM_1].dev->ev_irq_num, \
                                i2c1_event_irq_handler);
#if (CONFIG_I2C1_TX_DMA == 1)
    irq_hal_register_handler(i2c_obj[I2C_NUM_1].dev->dma_tx->irq_num, \
                                i2c1_tx_dma_irq_handler);
#endif /* (CONFIG_I2C1_TX_DMA == 1) */
#if (CONFIG_I2C1_RX_DMA == 1)
    irq_hal_register_handler(i2c_obj[I2C_NUM_1].dev->dma_rx->irq_num, \
                                i2c1_rx_dma_irq_handler);
#endif /* (CONFIG_I2C1_RX_DMA == 1) */
#endif /* (CONFIG_I2C_NUM_1 == 1) */
#if (CONFIG_I2C_NUM_2 == 1)
    irq_hal_register_handler(i2c_obj[I2C_NUM_2].dev->er_irq_num, \
                                i2c2_error_irq_handler);
    irq_hal_register_handler(i2c_obj[I2C_NUM_2].dev->ev_irq_num, \
                                i2c2_event_irq_handler);
#if (CONFIG_I2C2_TX_DMA == 1)
    irq_hal_register_handler(i2c_obj[I2C_NUM_2].dev->dma_tx->irq_num, \
                                i2c2_tx_dma_irq_handler);
#endif /* (CONFIG_I2C2_TX_DMA == 1) */
#if (CONFIG_I2C2_RX_DMA == 1)
    irq_hal_register_handler(i2c_obj[I2C_NUM_2].dev->dma_rx->irq_num, \
                                i2c2_rx_dma_irq_handler);
#endif /* (CONFIG_I2C2_RX_DMA == 1) */
#endif /* (CONFIG_I2C_NUM_2 == 1) */
#if (CONFIG_I2C_NUM_3 == 1)
    irq_hal_register_handler(i2c_obj[I2C_NUM_3].dev->er_irq_num, \
                                i2c3_error_irq_handler);
    irq_hal_register_handler(i2c_obj[I2C_NUM_3].dev->ev_irq_num, \
                                i2c3_event_irq_handler);
#if (CONFIG_I2C3_TX_DMA == 1)
    irq_hal_register_handler(i2c_obj[I2C_NUM_3].dev->dma_tx->irq_num, \
                                i2c3_tx_dma_irq_handler);
#endif /* (CONFIG_I2C3_TX_DMA == 1) */
#if (CONFIG_I2C3_RX_DMA == 1)
    irq_hal_register_handler(i2c_obj[I2C_NUM_3].dev->dma_rx->irq_num, \
                                i2c3_rx_dma_irq_handler);
#endif /* (CONFIG_I2C3_RX_DMA == 1) */
#endif /* (CONFIG_I2C_NUM_3 == 1) */
}

/********************* Callback functions **********************/
void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *hi2c) {
    i2c_obj_t *obj = i2c_hal_get_obj(hi2c);
    omni_assert_not_null(obj);

    obj->status.busy = 0U;

    if (obj->event_cb != NULL) {
        obj->event_cb(I2C_EVENT_TRANSFER_COMPLETE);
    }
}

void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c) {
    i2c_obj_t *obj = i2c_hal_get_obj(hi2c);
    omni_assert_not_null(obj);

    obj->status.busy = 0U;

    if (obj->event_cb != NULL) {
        obj->event_cb(I2C_EVENT_TRANSFER_COMPLETE);
    }
}

void HAL_I2C_MemTxCpltCallback(I2C_HandleTypeDef *hi2c) {
    i2c_obj_t *obj = i2c_hal_get_obj(hi2c);
    omni_assert_not_null(obj);

    obj->status.busy = 0U;

    if (obj->event_cb != NULL) {
        obj->event_cb(I2C_EVENT_TRANSFER_COMPLETE);
    }
}

void HAL_I2C_MemRxCpltCallback(I2C_HandleTypeDef *hi2c) {
    i2c_obj_t *obj = i2c_hal_get_obj(hi2c);
    omni_assert_not_null(obj);

    obj->status.busy = 0U;

    if (obj->event_cb != NULL) {
        obj->event_cb(I2C_EVENT_TRANSFER_COMPLETE);
    }
}

void HAL_I2C_AddrCallback(I2C_HandleTypeDef *hi2c, uint8_t TransferDirection, uint16_t AddrMatchCode) {
    uint32_t event = 0;
    i2c_obj_t *obj = i2c_hal_get_obj(hi2c);
    omni_assert_not_null(obj);

    if (obj->flags.xfer_set == 0) {
        if (TransferDirection == I2C_DIRECTION_TRANSMIT) {
            // Master is transmitter, slave enters receiver mode
            event |= I2C_EVENT_SLAVE_RECEIVE;
        } else {
            // Master is receiver, slave enters transmitter mode
            event |= I2C_EVENT_SLAVE_TRANSMIT;
        }

        if  (AddrMatchCode == 0) {
            // General call
            event |= I2C_EVENT_GENERAL_CALL;
            obj->status.general_call = 1;
        }

        if ((obj->event_cb != NULL) && (event != 0)) {
            obj->event_cb(event);
        }

        // Nothing to receive, set NACK
        CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_ACK);

    } else {
        obj->status.busy = 1;
    }

    __HAL_I2C_CLEAR_ADDRFLAG(hi2c);
}

void HAL_I2C_SlaveTxCpltCallback(I2C_HandleTypeDef *hi2c) {
    i2c_obj_t *obj = i2c_hal_get_obj(hi2c);
    omni_assert_not_null(obj);

    obj->flags.xfer_set = 0;
    obj->status.busy = 0U;

    if (obj->event_cb != NULL) {
        obj->event_cb(I2C_EVENT_TRANSFER_COMPLETE);
    }
}

void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c) {
    i2c_obj_t *obj = i2c_hal_get_obj(hi2c);
    omni_assert_not_null(obj);

    obj->flags.xfer_set = 0;
    obj->status.busy = 0U;

    if (obj->event_cb != NULL) {
        obj->event_cb(I2C_EVENT_TRANSFER_COMPLETE);
    }
}

void HAL_I2C_ListenCpltCallback(I2C_HandleTypeDef *hi2c) {
    i2c_obj_t *obj = i2c_hal_get_obj(hi2c);
    omni_assert_not_null(obj);

    HAL_I2C_EnableListen_IT(hi2c);
}

void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *hi2c) {
    uint32_t event = 0;
    uint32_t error = 0;
    i2c_obj_t *obj = i2c_hal_get_obj(hi2c);
    omni_assert_not_null(obj);

    error = HAL_I2C_GetError(hi2c);

    event = I2C_EVENT_TRANSFER_COMPLETE | I2C_EVENT_TRANSFER_INCOMPLETE;

    if ((error & HAL_I2C_ERROR_ARLO) != 0) {
        obj->error.arbitration_lost = 1;
        event |= I2C_EVENT_ARBITRATION_LOST;
    }

    if ((error & HAL_I2C_ERROR_BERR) != 0) {
        obj->error.bus_error = 1;
        event |= I2C_EVENT_BUS_ERROR;
    }

    if ((error & HAL_I2C_ERROR_AF) != 0) {
        // Acknowledge not received
        if ((hi2c->XferCount == 0) && (hi2c->XferSize > 0)) {
            // Slave address was not acknowledged
            event |= I2C_EVENT_ADDRESS_NACK;
        }
    }

    obj->status.busy = 0U;

    if (obj->event_cb != NULL) {
        obj->event_cb(event);
    }
}

/********************* HAL functions **********************/

/**
 * @brief Set GPIO for I2C
 * 
 * @param dev I2C device information
 */
static void i2c_hal_set_gpio(i2c_dev_t *dev) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    if (dev->scl_pin != NULL) {
        gpio_hal_enable_clock(dev->scl_pin->ins);
    }

    if (dev->sda_pin != NULL) {
        gpio_hal_enable_clock(dev->sda_pin->ins);
    }

    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

    if (dev->scl_pin != NULL) {
        GPIO_InitStruct.Pin = dev->scl_pin->index;
#if defined(CONFIG_SOC_FAMILY_STM32F4XX)
        GPIO_InitStruct.Alternate = dev->scl_pin->alternate;
#endif /* CONFIG_SOC_FAMILY_STM32F4XX */
        HAL_GPIO_Init(dev->scl_pin->ins, &GPIO_InitStruct);
    }

    if (dev->sda_pin != NULL) {
        GPIO_InitStruct.Pin = dev->sda_pin->index;
#if defined(CONFIG_SOC_FAMILY_STM32F4XX)
        GPIO_InitStruct.Alternate = dev->sda_pin->alternate;
#endif /* CONFIG_SOC_FAMILY_STM32F4XX */
        HAL_GPIO_Init(dev->sda_pin->ins, &GPIO_InitStruct);
    }

#if defined(CONFIG_SOC_FAMILY_STM32F1XX)
    // Remap GPIO
    if (dev->alternate != AFIO_UNAVAILABLE_REMAP) {
        gpio_hal_alternate(dev->alternate);
    }
#endif /* CONFIG_SOC_FAMILY_STM32F1XX */
}

/**
 * @brief Reset GPIO for I2C
 * 
 * @param dev I2C device information
 */
static void i2c_hal_reset_gpio(i2c_dev_t *dev) {
    if (dev->scl_pin != NULL) {
        HAL_GPIO_DeInit(dev->scl_pin->ins, dev->scl_pin->index);
    }

    if (dev->sda_pin != NULL) {
        HAL_GPIO_DeInit(dev->sda_pin->ins, dev->sda_pin->index);
    }
}

/**
 * @brief Enable I2C clock
 * 
 * @param i2c_num I2C number
 */
static void i2c_hal_enable_clock(i2c_num_t i2c_num) {
    switch (i2c_num) {
#if defined(I2C1) && (CONFIG_I2C_NUM_1 == 1)
        case I2C_NUM_1:
            __HAL_RCC_I2C1_CLK_ENABLE();
            break;
#endif /* I2C1 && (CONFIG_I2C_NUM_1 == 1) */

#if defined(I2C2) && (CONFIG_I2C_NUM_2 == 1)
        case I2C_NUM_2:
            __HAL_RCC_I2C2_CLK_ENABLE();
            break;
#endif /* I2C2 && (CONFIG_I2C_NUM_2 == 1) */

#if defined(I2C3) && (CONFIG_I2C_NUM_3 == 1)
        case I2C_NUM_3:
            __HAL_RCC_I2C3_CLK_ENABLE();
            break;
#endif /* I2C3 && (CONFIG_I2C_NUM_3 == 1) */

        default:
            break;
    }
}

/**
 * @brief Reset I2C clock
 * 
 * @param i2c_num I2C number
 */
static void i2c_hal_reset_clock(i2c_num_t i2c_num) {
    switch (i2c_num) {
#if defined(I2C1) && (CONFIG_I2C_NUM_1 == 1)
        case I2C_NUM_1:
            __HAL_RCC_I2C1_CLK_DISABLE();
            break;
#endif /* I2C1 && (CONFIG_I2C_NUM_1 == 1) */

#if defined(I2C2) && (CONFIG_I2C_NUM_2 == 1)
        case I2C_NUM_2:
            __HAL_RCC_I2C2_CLK_DISABLE();
            break;
#endif /* I2C2 && (CONFIG_I2C_NUM_2 == 1) */

#if defined(I2C3) && (CONFIG_I2C_NUM_3 == 1)
        case I2C_NUM_3:
            __HAL_RCC_I2C3_CLK_DISABLE();
            break;
#endif /* I2C3 && (CONFIG_I2C_NUM_3 == 1) */

        default:
            break;
    }
}

/**
 * @brief Get I2C object
 *
 * @param hi2c I2C handle
 * @return Pointer to I2C object
 */
static i2c_obj_t *i2c_hal_get_obj(I2C_HandleTypeDef *hi2c) {
    i2c_obj_t *obj = NULL;

#if defined(I2C1) && (CONFIG_I2C_NUM_1 == 1)
    if (hi2c->Instance == I2C1) {
        obj = &i2c_obj[I2C_NUM_1];
    }
#endif /* I2C1 && CONFIG_I2C_NUM_1 */

#if defined(I2C2) && (CONFIG_I2C_NUM_2 == 1)
    if (hi2c->Instance == I2C2) {
        obj = &i2c_obj[I2C_NUM_2];
    }
#endif /* I2C2 && CONFIG_I2C_NUM_2 */

#if defined(I2C3) && (CONFIG_I2C_NUM_3 == 1)
    if (hi2c->Instance == I2C3) {
        obj = &i2c_obj[I2C_NUM_3];
    }
#endif /* I2C3 && CONFIG_I2C_NUM_3 */

    return obj;
}
