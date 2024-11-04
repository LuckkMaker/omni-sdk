/**
  * @file    usart_hal.c
  * @author  LuckkMaker
  * @brief   USART HAL driver
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
#include "drivers/usart.h"
#include "hal/gpio_hal.h"
#include "hal/dma_hal.h"
#include "hal/irq_hal.h"
#include "ll/usart_ll.h"

static usart_obj_t usart_obj[USART_NUM_MAX];

static int usart_open(usart_num_t usart_num, usart_driver_config_t *config);
static int usart_close(usart_num_t usart_num);
static void usart_start(usart_num_t usart_num);
static void usart_stop(usart_num_t usart_num);
static int usart_poll_write(usart_num_t usart_num, const uint8_t *data, uint32_t len, uint32_t timeout);
static int usart_poll_read(usart_num_t usart_num, void *data, uint32_t len, uint32_t timeout);
static int usart_write(usart_num_t usart_num, const uint8_t *data, uint32_t len);
static int usart_read(usart_num_t usart_num, void *data, uint32_t len);
static usart_driver_status_t usart_get_status(usart_num_t usart_num);
static usart_driver_error_t usart_get_error(usart_num_t usart_num);

const struct usart_driver_api usart_driver = {
    .open = usart_open,
    .close = usart_close,
    .start = usart_start,
    .stop = usart_stop,
    .poll_write = usart_poll_write,
    .poll_read = usart_poll_read,
    .write = usart_write,
    .read = usart_read,
    .get_status = usart_get_status,
    .get_error = usart_get_error,
};

static void usart_hal_irq_register(void);
static void usart_hal_irq_request(usart_obj_t *obj);
static void usart_hal_set_gpio(usart_dev_t *dev);
static void usart_hal_reset_gpio(usart_dev_t *dev);
static void usart_hal_enable_clock(usart_num_t usart_num);
static void usart_hal_reset_clock(usart_num_t usart_num);
static usart_obj_t *usart_hal_get_obj(UART_HandleTypeDef *huart);

static void usart_tx_dma_event_callback(DMA_HandleTypeDef *hdma);
static void usart_rx_dma_event_callback(DMA_HandleTypeDef *hdma);

/**
 * @brief Open the USART port
 * 
 * @param usart_num USART port number
 * @param config Pointer to driver configuration structure
 * @return Operation status
 */
static int usart_open(usart_num_t usart_num, usart_driver_config_t *config) {
    omni_assert(usart_num < USART_NUM_MAX);
    omni_assert_not_null(config);

    usart_obj_t *obj = &usart_obj[usart_num];

    // Set event callback
    if (config->event_cb != NULL) {
        obj->event_cb = config->event_cb;
    } else {
        obj->event_cb = NULL;
    }

    // Get dev information
    obj->dev = usart_ll_get_dev(usart_num);
    omni_assert_not_null(obj->dev);

    UART_HandleTypeDef *handle = obj->dev->handle;

    // Clear status
    obj->status = (usart_driver_status_t){0};

    // Clear error
    obj->error = (usart_driver_error_t){0};

    // Register IRQ
    usart_hal_irq_register();

    // Enable USART clock
    // Note: USART clock should be enabled before GPIO initialization
    usart_hal_enable_clock(usart_num);

    // Initialize GPIO
    usart_hal_set_gpio(obj->dev);

    // Initialize DMA
#if (CONFIG_USART_TX_DMA == 1)
    // Configure USART DMA TX
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
#endif /* (CONFIG_USART_TX_DMA == 1) */

#if (CONFIG_USART_RX_DMA == 1)
     // Configure USART DMA RX
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
#endif /* (CONFIG_USART_RX_DMA == 1) */

    // Initialize IRQ
    NVIC_ClearPendingIRQ(obj->dev->irq_num);
    NVIC_SetPriority(obj->dev->irq_num, \
                    NVIC_EncodePriority(NVIC_GetPriorityGrouping(), obj->dev->irq_prio, 0));
    NVIC_EnableIRQ(obj->dev->irq_num);

    // Initialize UART
    handle->Init.BaudRate = config->baudrate;
    handle->Init.Mode = UART_MODE_TX_RX;
#ifdef USART_CR1_OVER8
    handle->Init.OverSampling = config->baudrate > 5000000U ? UART_OVERSAMPLING_8 : UART_OVERSAMPLING_16;
#else
    handle->Init.OverSampling = UART_OVERSAMPLING_16;
#endif /* USART_CR1_OVER8 */

    switch (config->data_bits) {
        case USART_DATA_BITS_8:
            handle->Init.WordLength = UART_WORDLENGTH_8B;
            break;
        case USART_DATA_BITS_9:
            handle->Init.WordLength = UART_WORDLENGTH_9B;
            break;
        default:
            handle->Init.WordLength = UART_WORDLENGTH_8B;
            break;
    }

    switch (config->stop_bits) {
        case USART_STOP_BITS_1:
            handle->Init.StopBits = UART_STOPBITS_1;
            break;
        case USART_STOP_BITS_2:
            handle->Init.StopBits = UART_STOPBITS_2;
            break;
        default:
            handle->Init.StopBits = UART_STOPBITS_1;
            break;
    }

    switch (config->parity) {
        case USART_PARITY_DISABLE:
            handle->Init.Parity = UART_PARITY_NONE;
            break;
        case USART_PARITY_TYPE_EVEN:
            handle->Init.Parity = UART_PARITY_EVEN;
            break;
        case USART_PARITY_TYPE_ODD:
            handle->Init.Parity = UART_PARITY_ODD;
            break;
        default:
            handle->Init.Parity = UART_PARITY_NONE;
            break;
    }

    switch (config->flow_ctrl) {
        case USART_FLOW_CTRL_DISABLE:
            handle->Init.HwFlowCtl = UART_HWCONTROL_NONE;
            break;
        case USART_FLOW_CTRL_RTS:
            handle->Init.HwFlowCtl = UART_HWCONTROL_RTS;
            break;
        case USART_FLOW_CTRL_CTS:
            handle->Init.HwFlowCtl = UART_HWCONTROL_CTS;
            break;
        case USART_FLOW_CTRL_RTS_CTS:
            handle->Init.HwFlowCtl = UART_HWCONTROL_RTS_CTS;
            break;
        default:
            handle->Init.HwFlowCtl = UART_HWCONTROL_NONE;
            break;
    }

    if (HAL_UART_Init(handle) != HAL_OK) {
        return OMNI_FAIL;
    }

    // Set initialized status
    obj->status.is_initialized = 1;
    // Call event callback
    if (obj->event_cb != NULL) {
        // Set initialized event
        obj->event_cb(USART_EVENT_INITIALIZED);
    }

    return OMNI_OK;
}

/**
 * @brief Close the USART port
 * 
 * @param usart_num USART port number
 * @return Operation status
 */
static int usart_close(usart_num_t usart_num) {
    omni_assert(usart_num < USART_NUM_MAX);

    usart_obj_t *obj = &usart_obj[usart_num];
    omni_assert_not_null(obj);

    // Reset USART clock
    usart_hal_reset_clock(usart_num);

    // Reset GPIO
    usart_hal_reset_gpio(obj->dev);

#if (CONFIG_USART_TX_DMA == 1)
    // Deinitialize USART DMA TX
    if (obj->dev->dma_tx != NULL) {
        HAL_DMA_DeInit(obj->dev->dma_tx->handle);
    }
#endif /* (CONFIG_USART_TX_DMA == 1) */

#if (CONFIG_USART_RX_DMA == 1)
    // Deinitialize USART DMA RX
    if (obj->dev->dma_rx != NULL) {
        HAL_DMA_DeInit(obj->dev->dma_rx->handle);
    }
#endif /* (CONFIG_USART_RX_DMA == 1) */

    // Disable USART IRQ
    NVIC_DisableIRQ(obj->dev->irq_num);

#if (CONFIG_USART_TX_DMA == 1)
    // Disable USART DMA IRQ
    if (obj->dev->dma_tx != NULL) {
        NVIC_DisableIRQ(obj->dev->dma_tx->irq_num);
    }
#endif /* (CONFIG_USART_TX_DMA == 1) */

#if (CONFIG_USART_RX_DMA == 1)
    if (obj->dev->dma_rx != NULL) {
        NVIC_DisableIRQ(obj->dev->dma_rx->irq_num);
    }
#endif /* (CONFIG_USART_RX_DMA == 1) */

    // Clear object
    if (obj->dev != NULL) {
        obj->dev = NULL;
    }

    if (obj->event_cb != NULL) {
        obj->event_cb = NULL;
    }

    usart_obj[usart_num] = (usart_obj_t){0};

    return OMNI_OK;
}

/**
 * @brief Start USART port
 * 
 * @param usart_num USART port number
 */
static void usart_start(usart_num_t usart_num) {
    omni_assert(usart_num < USART_NUM_MAX);

    usart_obj_t *obj = &usart_obj[usart_num];
    omni_assert_not_null(obj);

    UART_HandleTypeDef *handle = obj->dev->handle;

    // Enable USART
    __HAL_UART_ENABLE(handle);
}

/**
 * @brief Stop USART port
 * 
 * @param usart_num USART port number
 */
static void usart_stop(usart_num_t usart_num) {
    omni_assert(usart_num < USART_NUM_MAX);

    usart_obj_t *obj = &usart_obj[usart_num];
    omni_assert_not_null(obj);

    UART_HandleTypeDef *handle = obj->dev->handle;

    // Disable USART
    __HAL_UART_DISABLE(handle);
}

/**
 * @brief Write data to USART with polling
 * 
 * @param usart_num USART port number
 * @param data Pointer to data buffer
 * @param len Length of data buffer
 * @param timeout Timeout in ms
 * @return Operation status
 */
static int usart_poll_write(usart_num_t usart_num, const uint8_t *data, uint32_t len, uint32_t timeout) {
    omni_assert(usart_num < USART_NUM_MAX);
    omni_assert_not_null(data);
    omni_assert_non_zero(len);

    usart_obj_t *obj = &usart_obj[usart_num];
    omni_assert_not_null(obj);

    UART_HandleTypeDef *handle = obj->dev->handle;

    if (HAL_UART_Transmit(handle, (uint8_t *)data, len, timeout) != HAL_OK) {
        return OMNI_FAIL;
    }

    return OMNI_OK;
}

/**
 * @brief Read data from USART with polling
 * 
 * @param usart_num USART port number
 * @param data Pointer to data buffer
 * @param len Length of data buffer
 * @param timeout Timeout in ms
 * @return Operation status
 */
static int usart_poll_read(usart_num_t usart_num, void *data, uint32_t len, uint32_t timeout) {
    omni_assert(usart_num < USART_NUM_MAX);
    omni_assert_not_null(data);
    omni_assert_non_zero(len);

    usart_obj_t *obj = &usart_obj[usart_num];
    omni_assert_not_null(obj);

    UART_HandleTypeDef *handle = obj->dev->handle;

    if (HAL_UART_Receive(handle, (uint8_t *)data, len, timeout) != HAL_OK) {
        return OMNI_FAIL;
    }

    return OMNI_OK;
}

/**
 * @brief Write data to USART port
 * 
 * @param usart_num USART port number
 * @param data Pointer to data buffer
 * @param len Length of data buffer
 * @return Operation status
 */
static int usart_write(usart_num_t usart_num, const uint8_t *data, uint32_t len) {
    omni_assert(usart_num < USART_NUM_MAX);
    omni_assert_not_null(data);
    omni_assert_non_zero(len);

    usart_obj_t *obj = &usart_obj[usart_num];
    omni_assert_not_null(obj);

    UART_HandleTypeDef *handle = obj->dev->handle;

    if (obj->status.tx_busy) {
        return OMNI_BUSY;
    }

    // Prepare transfer data
    obj->data.tx_buffer = (uint8_t*)((uint32_t)data);
    obj->data.tx_num = len;
    obj->data.tx_count = 0;

    obj->status.tx_busy = 1;

#if (CONFIG_USART_TX_DMA == 1)
    handle->hdmatx->XferCpltCallback = usart_tx_dma_event_callback;
    handle->hdmatx->XferHalfCpltCallback = NULL;
    handle->hdmatx->XferErrorCallback = NULL;
    handle->hdmatx->XferAbortCallback = NULL;

    __HAL_UART_CLEAR_FLAG(handle, UART_FLAG_TC);

    HAL_DMA_Start_IT(handle->hdmatx, (uint32_t)obj->data.tx_buffer, (uint32_t)&handle->Instance->DR, len);

    /* Enable the DMA transfer for transmit request by setting the DMAT bit
       in the UART CR3 register */
    ATOMIC_SET_BIT(handle->Instance->CR3, USART_CR3_DMAT);
#else
    /* Enable the UART Transmit data register empty Interrupt */
    __HAL_UART_ENABLE_IT(handle, UART_IT_TXE);
#endif /* (CONFIG_USART_TX_DMA == 1) */

    return OMNI_OK;
}

/**
 * @brief Read data from USART port
 * 
 * @param usart_num USART port number
 * @param data Pointer to data buffer
 * @param len Length of data buffer
 * @return Operation status
 */
static int usart_read(usart_num_t usart_num, void *data, uint32_t len) {
    omni_assert(usart_num < USART_NUM_MAX);
    omni_assert_not_null(data);
    omni_assert_non_zero(len);

    usart_obj_t *obj = &usart_obj[usart_num];
    omni_assert_not_null(obj);

    UART_HandleTypeDef *handle = obj->dev->handle;

    if (obj->status.rx_busy) {
        return OMNI_BUSY;
    }

    // Disable RXNE interrupt
    ATOMIC_CLEAR_BIT(handle->Instance->CR1, USART_CR1_RXNEIE);

    // Prepare transfer data
    obj->data.rx_buffer = (uint8_t*)data;
    obj->data.rx_num = len;
    obj->data.rx_count = 0;

    // Clear error
    obj->error = (usart_driver_error_t){0};

    obj->status.rx_busy = 1;

#if (CONFIG_USART_RX_DMA == 1)
    handle->hdmarx->XferCpltCallback = usart_rx_dma_event_callback;
    handle->hdmarx->XferHalfCpltCallback = NULL;
    handle->hdmarx->XferErrorCallback = NULL;
    handle->hdmarx->XferAbortCallback = NULL;

    HAL_DMA_Start_IT(handle->hdmarx, (uint32_t)&handle->Instance->DR, (uint32_t)obj->data.rx_buffer, len);

    /* Clear the Overrun flag just before enabling the DMA Rx request: can be mandatory for the second transfer */
    __HAL_UART_CLEAR_OREFLAG(handle);

    /* Enable the DMA transfer for the receiver request by setting the DMAR bit
    in the UART CR3 register */
    ATOMIC_SET_BIT(handle->Instance->CR3, USART_CR3_DMAR);

    // Enable IDLE interrupt
    ATOMIC_SET_BIT(handle->Instance->CR1, USART_CR1_IDLEIE);
#else
    // Enable IDLE interrupt
    ATOMIC_SET_BIT(handle->Instance->CR1, USART_CR1_IDLEIE);
    // Enable RXNE interrupt
    ATOMIC_SET_BIT(handle->Instance->CR1, USART_CR1_RXNEIE);
#endif /* (CONFIG_USART_RX_DMA == 1) */

    return OMNI_OK;
}

/**
 * @brief Get USART port status
 * 
 * @param usart_num USART port number
 * @return USART driver status
 */
static usart_driver_status_t usart_get_status(usart_num_t usart_num) {
    omni_assert(usart_num < USART_NUM_MAX);

    usart_obj_t *obj = &usart_obj[usart_num];
    omni_assert_not_null(obj);

    return obj->status;
}

/**
 * @brief Get USART port error
 * 
 * @param usart_num USART port number
 * @return USART driver error
 */
static usart_driver_error_t usart_get_error(usart_num_t usart_num) {
    omni_assert(usart_num < USART_NUM_MAX);

    usart_obj_t *obj = &usart_obj[usart_num];
    omni_assert_not_null(obj);

    return obj->error;
}

/********************* IRQ handlers **********************/
/**
 * @brief USART IRQ handler
 */
static void usart_hal_irq_request(usart_obj_t *obj) {
    uint32_t event = 0;
    uint16_t data = 0;
    omni_assert_not_null(obj);

    UART_HandleTypeDef *handle = obj->dev->handle;

    // HAL_UART_IRQHandler(handle);

    // Check read data register not empty
    if ((__HAL_UART_GET_IT_SOURCE(handle, UART_IT_RXNE) != RESET) && \
        (__HAL_UART_GET_FLAG(handle, UART_FLAG_RXNE) != RESET)) {
        if (obj->status.rx_busy == 0U) {
            // Receive has not been started

            // Disable RXNE interrupt
            ATOMIC_CLEAR_BIT(handle->Instance->CR1, USART_CR1_RXNEIE);
            obj->error.rx_overflow = 1;
            // Set RX overflow event
            event |= USART_EVENT_RX_OVERFLOW;
        } else {
            // Read data from RX FIFO
            data = (uint16_t)(handle->Instance->DR & (uint16_t)0x01FF);
            *(obj->data.rx_buffer++) = (uint8_t)data;

            // If nine bits data and no parity, read the 10th bit
            if ((handle->Init.WordLength == UART_WORDLENGTH_9B) && \
                (handle->Init.Parity == UART_PARITY_NONE)) {
                *(obj->data.rx_buffer++) = (uint8_t)(data >> 8);
            }
            obj->data.rx_count++;

            // Check if all data has been received
            if (obj->data.rx_count == obj->data.rx_num) {
                // Disable IDLE interrupt
                ATOMIC_CLEAR_BIT(handle->Instance->CR1, USART_CR1_IDLEIE);
                // Clear RX busy flag
                obj->status.rx_busy = 0;
                // Set receive complete event
                event |= USART_EVENT_RECEIVE_COMPLETE;
            }
        }
    }

    // Check IDLE interrupt
    // Note: USE HAL API to clear IDLE flag will cause the IDLE flag not be cleared
    if ((LL_USART_IsEnabledIT_IDLE(handle->Instance) & \
        LL_USART_IsActiveFlag_IDLE(handle->Instance)) && \
        ((LL_USART_IsEnabledIT_RXNE(handle->Instance) & \
        LL_USART_IsActiveFlag_RXNE(handle->Instance)) == 0U)) {
        // Clear IDLE flag
        __HAL_UART_CLEAR_IDLEFLAG(handle);

        // Set RX timeout event
        event |= USART_EVENT_RX_TIMEOUT;
    }

    // Transmit data register empty
    if ((__HAL_UART_GET_IT_SOURCE(handle, UART_IT_TXE) != RESET) && \
        (__HAL_UART_GET_FLAG(handle, UART_FLAG_TXE) != RESET)) {
        if (obj->data.tx_num != obj->data.tx_count) {
            // Write data to TX FIFO
            data = *(obj->data.tx_buffer++);

            // If nine bits data and no parity, write the 10th bit
            if ((handle->Init.WordLength == UART_WORDLENGTH_9B) && \
                (handle->Init.Parity == UART_PARITY_NONE)) {
                data |= (*(obj->data.tx_buffer++) << 8);
            }
        }
        obj->data.tx_count++;

        // Write to data register
        handle->Instance->DR = data;

        // Check if all data has been sent
        if (obj->data.tx_count == obj->data.tx_num) {
            // Disable TXE interrupt
            ATOMIC_CLEAR_BIT(handle->Instance->CR1, USART_CR1_TXEIE);

            // Enable TC interrupt
            ATOMIC_SET_BIT(handle->Instance->CR1, USART_CR1_TCIE);

            obj->status.tx_busy = 0;

            // Set Send complete event
            event |= USART_EVENT_SEND_COMPLETE;
        }
    }

    // TX complete
    if ((__HAL_UART_GET_IT_SOURCE(handle, UART_IT_TC) != RESET) && \
        (__HAL_UART_GET_FLAG(handle, UART_FLAG_TC) != RESET)) {

        // Disable TC interrupt
        ATOMIC_CLEAR_BIT(handle->Instance->CR1, USART_CR1_TCIE);

        obj->status.tx_busy = 0;

        // Set TX complete event
        event |= USART_EVENT_TX_COMPLETE;
    }

    // RX overrun error
    if (__HAL_UART_GET_FLAG(handle, UART_FLAG_ORE) != RESET) {
        obj->error.rx_overflow = 1;
        // Set RX overflow event
        event |= USART_EVENT_RX_OVERFLOW;
    }

    // RX framing error
    if (__HAL_UART_GET_FLAG(handle, UART_FLAG_FE) != RESET) {
        obj->error.rx_framing_error = 1;
        // Set RX framing error event
        event |= USART_EVENT_RX_FRAMING_ERROR;
    }

    // RX parity error
    if (__HAL_UART_GET_FLAG(handle, UART_FLAG_PE) != RESET) {
        obj->error.rx_parity_error = 1;
        // Set RX parity error event
        event |= USART_EVENT_RX_PARITY_ERROR;
    }

    if (obj->error.rx_overflow || obj->error.rx_framing_error || \
        obj->error.rx_parity_error) {
        // Disable parity , framing , overrun and idle flag
        __HAL_UART_CLEAR_PEFLAG(handle);
    }

    // Send event
    if ((obj->event_cb != NULL) && (event != 0)) {
        obj->event_cb(event);
    }
}

#if (CONFIG_USART_NUM_1 == 1)
/**
 * @brief USART1 IRQ handler
 */
static void usart1_irq_handler(void) {
    usart_hal_irq_request(&usart_obj[USART_NUM_1]);
}
#endif /* CONFIG_USART_NUM_1 */

#if (CONFIG_USART_NUM_2 == 1)
/**
 * @brief USART2 IRQ handler
 */
static void usart2_irq_handler(void) {
    usart_hal_irq_request(&usart_obj[USART_NUM_2]);
}
#endif /* CONFIG_USART_NUM_2 */

#if (CONFIG_USART_NUM_3 == 1)
/**
 * @brief USART3 IRQ handler
 */
static void usart3_irq_handler(void) {
    usart_hal_irq_request(&usart_obj[USART_NUM_3]);
}
#endif /* CONFIG_USART_NUM_3 */

#if (CONFIG_USART_NUM_4 == 1)
/**
 * @brief USART4 IRQ handler
 */
static void usart4_irq_handler(void) {
    usart_hal_irq_request(&usart_obj[USART_NUM_4]);
}
#endif /* CONFIG_USART_NUM_4 */

#if (CONFIG_USART_NUM_5 == 1)
/**
 * @brief USART5 IRQ handler
 */
static void usart5_irq_handler(void) {
    usart_hal_irq_request(&usart_obj[USART_NUM_5]);
}
#endif /* CONFIG_USART_NUM_5 */

#if (CONFIG_USART_NUM_6 == 1)
/**
 * @brief USART6 IRQ handler
 */
static void usart6_irq_handler(void) {
    usart_hal_irq_request(&usart_obj[USART_NUM_6]);
}
#endif /* CONFIG_USART_NUM_6 */

#if (CONFIG_USART_NUM_7 == 1)
/**
 * @brief USART7 IRQ handler
 */
static void usart7_irq_handler(void) {
    usart_hal_irq_request(&usart_obj[USART_NUM_7]);
}
#endif /* CONFIG_USART_NUM_7 */

#if (CONFIG_USART_NUM_8 == 1)
/**
 * @brief USART8 IRQ handler
 */
static void usart8_irq_handler(void) {
    usart_hal_irq_request(&usart_obj[USART_NUM_8]);
}
#endif /* CONFIG_USART_NUM_8 */

#if (CONFIG_USART_NUM_9 == 1)
/**
 * @brief USART9 IRQ handler
 */
static void usart9_irq_handler(void) {
    usart_hal_irq_request(&usart_obj[USART_NUM_9]);
}
#endif /* CONFIG_USART_NUM_9 */

#if (CONFIG_USART_NUM_10 == 1)
/**
 * @brief USART10 IRQ handler
 */
static void usart10_irq_handler(void) {
    usart_hal_irq_request(&usart_obj[USART_NUM_10]);
}
#endif /* CONFIG_USART_NUM_10 */

#if (CONFIG_USART_TX_DMA == 1)
#if (CONFIG_USART1_TX_DMA == 1)
void usart1_tx_dma_irq_handler(void) {
    HAL_DMA_IRQHandler(usart_obj[USART_NUM_1].dev->dma_tx->handle);
}
#endif /* (CONFIG_USART1_TX_DMA == 1) */
#if (CONFIG_USART2_TX_DMA == 1)
void usart2_tx_dma_irq_handler(void) {
    HAL_DMA_IRQHandler(usart_obj[USART_NUM_2].dev->dma_tx->handle);
}
#endif /* (CONFIG_USART2_TX_DMA == 1) */
#if (CONFIG_USART3_TX_DMA == 1)
void usart3_tx_dma_irq_handler(void) {
    HAL_DMA_IRQHandler(usart_obj[USART_NUM_3].dev->dma_tx->handle);
}
#endif /* (CONFIG_USART3_TX_DMA == 1) */
#if (CONFIG_USART4_TX_DMA == 1)
void usart4_tx_dma_irq_handler(void) {
    HAL_DMA_IRQHandler(usart_obj[USART_NUM_4].dev->dma_tx->handle);
}
#endif /* (CONFIG_USART4_TX_DMA == 1) */
#if (CONFIG_USART5_TX_DMA == 1)
void usart5_tx_dma_irq_handler(void) {
    HAL_DMA_IRQHandler(usart_obj[USART_NUM_5].dev->dma_tx->handle);
}
#endif /* (CONFIG_USART5_TX_DMA == 1) */
#if (CONFIG_USART6_TX_DMA == 1)
void usart6_tx_dma_irq_handler(void) {
    HAL_DMA_IRQHandler(usart_obj[USART_NUM_6].dev->dma_tx->handle);
}
#endif /* (CONFIG_USART6_TX_DMA == 1) */
#if (CONFIG_USART7_TX_DMA == 1)
void usart7_tx_dma_irq_handler(void) {
    HAL_DMA_IRQHandler(usart_obj[USART_NUM_7].dev->dma_tx->handle);
}
#endif /* (CONFIG_USART7_TX_DMA == 1) */
#if (CONFIG_USART8_TX_DMA == 1)
void usart8_tx_dma_irq_handler(void) {
    HAL_DMA_IRQHandler(usart_obj[USART_NUM_8].dev->dma_tx->handle);
}
#endif /* (CONFIG_USART8_TX_DMA == 1) */
#if (CONFIG_USART9_TX_DMA == 1)
void usart9_tx_dma_irq_handler(void) {
    HAL_DMA_IRQHandler(usart_obj[USART_NUM_9].dev->dma_tx->handle);
}
#endif /* (CONFIG_USART9_TX_DMA == 1) */
#if (CONFIG_USART10_TX_DMA == 1)
void usart10_tx_dma_irq_handler(void) {
    HAL_DMA_IRQHandler(usart_obj[USART_NUM_10].dev->dma_tx->handle);
}
#endif /* (CONFIG_USART10_TX_DMA == 1) */
#endif /*(CONFIG_USART_TX_DMA == 1) */

#if (CONFIG_USART_RX_DMA == 1)
#if (CONFIG_USART1_RX_DMA == 1)
void usart1_rx_dma_irq_handler(void) {
    HAL_DMA_IRQHandler(usart_obj[USART_NUM_1].dev->dma_rx->handle);
}
#endif /* (CONFIG_USART1_RX_DMA == 1) */
#if (CONFIG_USART2_RX_DMA == 1)
void usart2_rx_dma_irq_handler(void) {
    HAL_DMA_IRQHandler(usart_obj[USART_NUM_2].dev->dma_rx->handle);
}
#endif /* (CONFIG_USART2_RX_DMA == 1) */
#if (CONFIG_USART3_RX_DMA == 1)
void usart3_rx_dma_irq_handler(void) {
    HAL_DMA_IRQHandler(usart_obj[USART_NUM_3].dev->dma_rx->handle);
}
#endif /* (CONFIG_USART3_RX_DMA == 1) */
#if (CONFIG_USART4_RX_DMA == 1)
void usart4_rx_dma_irq_handler(void) {
    HAL_DMA_IRQHandler(usart_obj[USART_NUM_4].dev->dma_rx->handle);
}
#endif /* (CONFIG_USART4_RX_DMA == 1) */
#if (CONFIG_USART5_RX_DMA == 1)
void usart5_rx_dma_irq_handler(void) {
    HAL_DMA_IRQHandler(usart_obj[USART_NUM_5].dev->dma_rx->handle);
}
#endif /* (CONFIG_USART5_RX_DMA == 1) */
#if (CONFIG_USART6_RX_DMA == 1)
void usart6_rx_dma_irq_handler(void) {
    HAL_DMA_IRQHandler(usart_obj[USART_NUM_6].dev->dma_rx->handle);
}
#endif /* (CONFIG_USART6_RX_DMA == 1) */
#if (CONFIG_USART7_RX_DMA == 1)
void usart7_rx_dma_irq_handler(void) {
    HAL_DMA_IRQHandler(usart_obj[USART_NUM_7].dev->dma_rx->handle);
}
#endif /* (CONFIG_USART7_RX_DMA == 1) */
#if (CONFIG_USART8_RX_DMA == 1)
void usart8_rx_dma_irq_handler(void) {
    HAL_DMA_IRQHandler(usart_obj[USART_NUM_8].dev->dma_rx->handle);
}
#endif /* (CONFIG_USART8_RX_DMA == 1) */
#if (CONFIG_USART9_RX_DMA == 1)
void usart9_rx_dma_irq_handler(void) {
    HAL_DMA_IRQHandler(usart_obj[USART_NUM_9].dev->dma_rx->handle);
}
#endif /* (CONFIG_USART9_RX_DMA == 1) */
#if (CONFIG_USART10_RX_DMA == 1)
void usart10_rx_dma_irq_handler(void) {
    HAL_DMA_IRQHandler(usart_obj[USART_NUM_10].dev->dma_rx->handle);
}
#endif /* (CONFIG_USART10_RX_DMA == 1) */
#endif /*(CONFIG_USART_RX_DMA == 1) */

/**
 * @brief Register USART IRQ
 */
static void usart_hal_irq_register(void) {
#if (CONFIG_USART_NUM_1 == 1)
    irq_hal_register_handler(usart_obj[USART_NUM_1].dev->irq_num, \
                                usart1_irq_handler);
#if (CONFIG_USART1_TX_DMA == 1)
    irq_hal_register_handler(usart_obj[USART_NUM_1].dev->dma_tx->irq_num, \
                                usart1_tx_dma_irq_handler);
#endif /* (CONFIG_USART1_TX_DMA == 1) */
#if (CONFIG_USART1_RX_DMA == 1)
    irq_hal_register_handler(usart_obj[USART_NUM_1].dev->dma_rx->irq_num, \
                                usart1_rx_dma_irq_handler);
#endif /* (CONFIG_USART1_RX_DMA == 1) */
#endif /* (CONFIG_USART_NUM_1 == 1) */
#if (CONFIG_USART_NUM_2 == 1)
    irq_hal_register_handler(usart_obj[USART_NUM_2].dev->irq_num, \
                                usart2_irq_handler);
#if (CONFIG_USART2_TX_DMA == 1)
    irq_hal_register_handler(usart_obj[USART_NUM_2].dev->dma_tx->irq_num, \
                                usart2_tx_dma_irq_handler);
#endif /* (CONFIG_USART2_TX_DMA == 1) */
#if (CONFIG_USART2_RX_DMA == 1)
    irq_hal_register_handler(usart_obj[USART_NUM_2].dev->dma_rx->irq_num, \
                                usart2_rx_dma_irq_handler);
#endif /* (CONFIG_USART2_RX_DMA == 1) */
#endif /* (CONFIG_USART_NUM_2 == 1) */
#if (CONFIG_USART_NUM_3 == 1)
    irq_hal_register_handler(usart_obj[USART_NUM_3].dev->irq_num, \
                                usart3_irq_handler);
#if (CONFIG_USART3_TX_DMA == 1)
    irq_hal_register_handler(usart_obj[USART_NUM_3].dev->dma_tx->irq_num, \
                                usart3_tx_dma_irq_handler);
#endif /* (CONFIG_USART3_TX_DMA == 1) */
#if (CONFIG_USART3_RX_DMA == 1)
    irq_hal_register_handler(usart_obj[USART_NUM_3].dev->dma_rx->irq_num, \
                                usart3_rx_dma_irq_handler);
#endif /* (CONFIG_USART3_RX_DMA == 1) */
#endif /* (CONFIG_USART_NUM_3 == 1) */
#if (CONFIG_USART_NUM_4 == 1)
    irq_hal_register_handler(usart_obj[USART_NUM_4].dev->irq_num, \
                                usart4_irq_handler);
#if (CONFIG_USART4_TX_DMA == 1)
    irq_hal_register_handler(usart_obj[USART_NUM_4].dev->dma_tx->irq_num, \
                                usart4_tx_dma_irq_handler);
#endif /* (CONFIG_USART4_TX_DMA == 1) */
#if (CONFIG_USART4_RX_DMA == 1)
    irq_hal_register_handler(usart_obj[USART_NUM_4].dev->dma_rx->irq_num, \
                                usart4_rx_dma_irq_handler);
#endif /* (CONFIG_USART4_RX_DMA == 1) */
#endif /* (CONFIG_USART_NUM_4 == 1) */
#if (CONFIG_USART_NUM_5 == 1)
    irq_hal_register_handler(usart_obj[USART_NUM_5].dev->irq_num, \
                                usart5_irq_handler);
#if (CONFIG_USART5_TX_DMA == 1)
    irq_hal_register_handler(usart_obj[USART_NUM_5].dev->dma_tx->irq_num, \
                                usart5_tx_dma_irq_handler);
#endif /* (CONFIG_USART5_TX_DMA == 1) */
#if (CONFIG_USART5_RX_DMA == 1)
    irq_hal_register_handler(usart_obj[USART_NUM_5].dev->dma_rx->irq_num, \
                                usart5_rx_dma_irq_handler);
#endif /* (CONFIG_USART5_RX_DMA == 1) */
#endif /* (CONFIG_USART_NUM_5 == 1) */
#if (CONFIG_USART_NUM_6 == 1)
    irq_hal_register_handler(usart_obj[USART_NUM_6].dev->irq_num, \
                                usart6_irq_handler);
#if (CONFIG_USART6_TX_DMA == 1)
    irq_hal_register_handler(usart_obj[USART_NUM_6].dev->dma_tx->irq_num, \
                                usart6_tx_dma_irq_handler);
#endif /* (CONFIG_USART6_TX_DMA == 1) */
#if (CONFIG_USART6_RX_DMA == 1)
    irq_hal_register_handler(usart_obj[USART_NUM_6].dev->dma_rx->irq_num, \
                                usart6_rx_dma_irq_handler);
#endif /* (CONFIG_USART6_RX_DMA == 1) */
#endif /* (CONFIG_USART_NUM_6 == 1) */
#if (CONFIG_USART_NUM_7 == 1)
    irq_hal_register_handler(usart_obj[USART_NUM_7].dev->irq_num, \
                                usart7_irq_handler);
#if (CONFIG_USART7_TX_DMA == 1)
    irq_hal_register_handler(usart_obj[USART_NUM_7].dev->dma_tx->irq_num, \
                                usart7_tx_dma_irq_handler);
#endif /* (CONFIG_USART7_TX_DMA == 1) */
#if (CONFIG_USART7_RX_DMA == 1)
    irq_hal_register_handler(usart_obj[USART_NUM_7].dev->dma_rx->irq_num, \
                                usart7_rx_dma_irq_handler);
#endif /* (CONFIG_USART7_RX_DMA == 1) */
#endif /* (CONFIG_USART_NUM_7 == 1) */
#if (CONFIG_USART_NUM_8 == 1)
    irq_hal_register_handler(usart_obj[USART_NUM_8].dev->irq_num, \
                                usart8_irq_handler);
#if (CONFIG_USART8_TX_DMA == 1)
    irq_hal_register_handler(usart_obj[USART_NUM_8].dev->dma_tx->irq_num, \
                                usart8_tx_dma_irq_handler);
#endif /* (CONFIG_USART8_TX_DMA == 1) */
#if (CONFIG_USART8_RX_DMA == 1)
    irq_hal_register_handler(usart_obj[USART_NUM_8].dev->dma_rx->irq_num, \
                                usart8_rx_dma_irq_handler);
#endif /* (CONFIG_USART8_RX_DMA == 1) */
#endif /* (CONFIG_USART_NUM_8 == 1) */
#if (CONFIG_USART_NUM_9 == 1)
    irq_hal_register_handler(usart_obj[USART_NUM_9].dev->irq_num, \
                                usart9_irq_handler);
#if (CONFIG_USART9_TX_DMA == 1)
    irq_hal_register_handler(usart_obj[USART_NUM_9].dev->dma_tx->irq_num, \
                                usart9_tx_dma_irq_handler);
#endif /* (CONFIG_USART9_TX_DMA == 1) */
#if (CONFIG_USART9_RX_DMA == 1)
    irq_hal_register_handler(usart_obj[USART_NUM_9].dev->dma_rx->irq_num, \
                                usart9_rx_dma_irq_handler);
#endif /* (CONFIG_USART9_RX_DMA == 1) */
#endif /* (CONFIG_USART_NUM_9 == 1) */
#if (CONFIG_USART_NUM_10 == 1)
    irq_hal_register_handler(usart_obj[USART_NUM_10].dev->irq_num, \
                                usart10_irq_handler);
#if (CONFIG_USART10_TX_DMA == 1)
    irq_hal_register_handler(usart_obj[USART_NUM_10].dev->dma_tx->irq_num, \
                                usart10_tx_dma_irq_handler);
#endif /* (CONFIG_USART10_TX_DMA == 1) */
#if (CONFIG_USART10_RX_DMA == 1)
    irq_hal_register_handler(usart_obj[USART_NUM_10].dev->dma_rx->irq_num, \
                                usart10_rx_dma_irq_handler);
#endif /* (CONFIG_USART10_RX_DMA == 1) */
#endif /* (CONFIG_USART_NUM_10 == 1) */
}

/********************* DMA callback functions **********************/
static void usart_tx_dma_event_callback(DMA_HandleTypeDef *hdma) {
    UART_HandleTypeDef *huart = (UART_HandleTypeDef *)((DMA_HandleTypeDef *)hdma)->Parent;
    usart_obj_t *obj = usart_hal_get_obj(huart);
    omni_assert_not_null(obj);

    /* DMA Normal mode*/
#if defined(CONFIG_SOC_FAMILY_STM32F1XX)
    if ((hdma->Instance->CCR & DMA_CCR_CIRC) == 0U) {
#else
    if ((hdma->Instance->CR & DMA_SxCR_CIRC) == 0U) {
#endif /* CONFIG_SOC_FAMILY_STM32F1XX */
        obj->data.tx_count = 0;

        /* Disable the DMA transfer for transmit request by setting the DMAT bit
        in the UART CR3 register */
        ATOMIC_CLEAR_BIT(huart->Instance->CR3, USART_CR3_DMAT);

        /* Enable the UART Transmit Complete Interrupt */
        ATOMIC_SET_BIT(huart->Instance->CR1, USART_CR1_TCIE);
    } else {
        if (obj->event_cb != NULL) {
            obj->event_cb(USART_EVENT_SEND_COMPLETE);
        }
    }
}

static void usart_rx_dma_event_callback(DMA_HandleTypeDef *hdma) {
    UART_HandleTypeDef *huart = (UART_HandleTypeDef *)((DMA_HandleTypeDef *)hdma)->Parent;
    usart_obj_t *obj = usart_hal_get_obj(huart);
    omni_assert_not_null(obj);

    /* DMA Normal mode*/
#if defined(CONFIG_SOC_FAMILY_STM32F1XX)
    if ((hdma->Instance->CCR & DMA_CCR_CIRC) == 0U) {
#else
    if ((hdma->Instance->CR & DMA_SxCR_CIRC) == 0U) {
#endif /* CONFIG_SOC_FAMILY_STM32F1XX */
        obj->data.rx_count = 0;

        /* Disable the DMA transfer for the receiver request by setting the DMAR bit
        in the UART CR3 register */
        ATOMIC_CLEAR_BIT(huart->Instance->CR3, USART_CR3_DMAR);

        // Disable IDLE interrupt
        ATOMIC_CLEAR_BIT(huart->Instance->CR1, USART_CR1_IDLEIE);

        obj->status.rx_busy = 0;

        // Enable RXNE interrupt
        ATOMIC_SET_BIT(huart->Instance->CR1, USART_CR1_RXNEIE);
    }

    if (obj->event_cb != NULL) {
        obj->event_cb(USART_EVENT_RECEIVE_COMPLETE);
    }
}

/********************* Callback functions **********************/
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {
    usart_obj_t *obj = usart_hal_get_obj(huart);
    omni_assert_not_null(obj);

    obj->status.tx_busy = 0;

    if (obj->event_cb != NULL) {
        obj->event_cb(USART_EVENT_SEND_COMPLETE);
    }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    usart_obj_t *obj = usart_hal_get_obj(huart);
    omni_assert_not_null(obj);

    obj->status.rx_busy = 0;

    if (obj->event_cb != NULL) {
        obj->event_cb(USART_EVENT_RECEIVE_COMPLETE);
    }
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart) {
    uint32_t event = 0;
    usart_obj_t *obj = usart_hal_get_obj(huart);
    omni_assert_not_null(obj);

    if (huart->ErrorCode & HAL_UART_ERROR_ORE) {
        obj->error.rx_overflow = 1;
        event |= USART_EVENT_RX_OVERFLOW;
    }

    if (huart->ErrorCode & HAL_UART_ERROR_FE) {
        obj->error.rx_framing_error = 1;
        event |= USART_EVENT_RX_FRAMING_ERROR;
    }

    if (huart->ErrorCode & HAL_UART_ERROR_PE) {
        obj->error.rx_parity_error = 1;
        event |= USART_EVENT_RX_PARITY_ERROR;
    }

    if ((obj->event_cb != NULL) && (event != 0)) {
        obj->event_cb(event);
    }
}

/********************* HAL functions **********************/

/**
 * @brief Set GPIO for USART
 * 
 * @param dev USART device information
 */
static void usart_hal_set_gpio(usart_dev_t *dev) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    if (dev->tx_pin != NULL) {
        gpio_hal_enable_clock(dev->tx_pin->ins);
    }

    if (dev->rx_pin != NULL) {
        gpio_hal_enable_clock(dev->rx_pin->ins);
    }

    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

    if (dev->tx_pin != NULL) {
        GPIO_InitStruct.Pin = dev->tx_pin->index;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
#if defined(CONFIG_SOC_FAMILY_STM32F4XX)
        GPIO_InitStruct.Alternate = dev->tx_pin->alternate;
#endif /* CONFIG_SOC_FAMILY_STM32F4XX */
        HAL_GPIO_Init(dev->tx_pin->ins, &GPIO_InitStruct);
    }

    if (dev->rx_pin != NULL) {
        GPIO_InitStruct.Pin = dev->rx_pin->index;
#if defined(CONFIG_SOC_FAMILY_STM32F1XX)
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
#else
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
#endif /* CONFIG_SOC_FAMILY_STM32F1XX */
#if defined(CONFIG_SOC_FAMILY_STM32F4XX)
        GPIO_InitStruct.Alternate = dev->rx_pin->alternate;
#endif /* CONFIG_SOC_FAMILY_STM32F4XX */
        HAL_GPIO_Init(dev->rx_pin->ins, &GPIO_InitStruct);
    }

#if defined(CONFIG_SOC_FAMILY_STM32F1XX)
    // Remap GPIO
    if (dev->alternate != AFIO_UNAVAILABLE_REMAP) {
        gpio_hal_alternate(dev->alternate);
    }
#endif /* CONFIG_SOC_FAMILY_STM32F1XX */
}

/**
 * @brief Reset GPIO for USART
 * 
 * @param dev USART device information
 */
static void usart_hal_reset_gpio(usart_dev_t *dev) {
    if (dev->tx_pin != NULL) {
        HAL_GPIO_DeInit(dev->tx_pin->ins, dev->tx_pin->index);
    }

    if (dev->rx_pin != NULL) {
        HAL_GPIO_DeInit(dev->rx_pin->ins, dev->rx_pin->index);
    }
}

/**
 * @brief Enable USART clock
 * 
 * @param usart_num USART port number
 */
static void usart_hal_enable_clock(usart_num_t usart_num) {
    switch (usart_num) {
#if defined(USART1) && (CONFIG_USART_NUM_1 == 1)
        case USART_NUM_1:
            __HAL_RCC_USART1_CLK_ENABLE();
            break;
#endif /* USART1 && CONFIG_USART_NUM_1 */

#if defined(USART2) && (CONFIG_USART_NUM_2 == 1)
        case USART_NUM_2:
            __HAL_RCC_USART2_CLK_ENABLE();
            break;
#endif /* USART2 && CONFIG_USART_NUM_2 */

#if defined(USART3) && (CONFIG_USART_NUM_3 == 1)
        case USART_NUM_3:
            __HAL_RCC_USART3_CLK_ENABLE();
            break;
#endif /* USART3 && CONFIG_USART_NUM_3 */

#if defined(UART4) && (CONFIG_USART_NUM_4 == 1)
        case USART_NUM_4:
            __HAL_RCC_UART4_CLK_ENABLE();
            break;
#endif /* UART4 && CONFIG_USART_NUM_4 */

#if defined(UART5) && (CONFIG_USART_NUM_5 == 1)
        case USART_NUM_5:
            __HAL_RCC_UART5_CLK_ENABLE();
            break;
#endif /* UART5 && CONFIG_USART_NUM_5 */

#if defined(USART6) && (CONFIG_USART_NUM_6 == 1)
        case USART_NUM_6:
            __HAL_RCC_USART6_CLK_ENABLE();
            break;
#endif /* USART6 && CONFIG_USART_NUM_6 */

#if defined(UART7) && (CONFIG_USART_NUM_7 == 1)
        case USART_NUM_7:
            __HAL_RCC_UART7_CLK_ENABLE();
            break;
#endif /* UART7 && CONFIG_USART_NUM_7 */

#if defined(UART8) && (CONFIG_USART_NUM_8 == 1)
        case USART_NUM_8:
            __HAL_RCC_UART8_CLK_ENABLE();
            break;
#endif /* UART8 && CONFIG_USART_NUM_8 */

#if defined(UART9) && (CONFIG_USART_NUM_9 == 1)
        case USART_NUM_9:
            __HAL_RCC_UART9_CLK_ENABLE();
            break;
#endif /* UART9 && CONFIG_USART_NUM_9 */

#if defined(UART10) && (CONFIG_USART_NUM_10 == 1)
        case USART_NUM_10:
            __HAL_RCC_UART10_CLK_ENABLE();
            break;
#endif /* UART10 && CONFIG_USART_NUM_10 */

        default:
            break;
    }
}

/**
 * @brief Reset USART clock
 * 
 * @param usart_num USART port number
 */
static void usart_hal_reset_clock(usart_num_t usart_num) {
    switch (usart_num) {
        case USART_NUM_1:
            __HAL_RCC_USART1_CLK_DISABLE();
            break;

#if defined(USART2) && (CONFIG_USART_NUM_2 == 1)
        case USART_NUM_2:
            __HAL_RCC_USART2_CLK_DISABLE();
            break;
#endif /* USART2 && CONFIG_USART_NUM_2 */

#if defined(USART3) && (CONFIG_USART_NUM_3 == 1)
        case USART_NUM_3:
            __HAL_RCC_USART3_CLK_DISABLE();
            break;

#endif /* USART3 && CONFIG_USART_NUM_3 */

#if defined(UART4) && (CONFIG_USART_NUM_4 == 1)
        case USART_NUM_4:
            __HAL_RCC_UART4_CLK_DISABLE();
            break;
#endif /* UART4 && CONFIG_USART_NUM_4 */

#if defined(UART5) && (CONFIG_USART_NUM_5 == 1)
        case USART_NUM_5:
            __HAL_RCC_UART5_CLK_DISABLE();
            break;
#endif /* UART5 && CONFIG_USART_NUM_5 */

#if defined(USART6) && (CONFIG_USART_NUM_6 == 1)
        case USART_NUM_6:
            __HAL_RCC_USART6_CLK_DISABLE();
            break;
#endif /* USART6 && CONFIG_USART_NUM_6 */

#if defined(UART7) && (CONFIG_USART_NUM_7 == 1)
        case USART_NUM_7:
            __HAL_RCC_UART7_CLK_DISABLE();
            break;
#endif /* UART7 && CONFIG_USART_NUM_7 */

#if defined(UART8) && (CONFIG_USART_NUM_8 == 1)
        case USART_NUM_8:
            __HAL_RCC_UART8_CLK_DISABLE();
            break;
#endif /* UART8 && CONFIG_USART_NUM_8 */

#if defined(UART9) && (CONFIG_USART_NUM_9 == 1)
        case USART_NUM_9:
            __HAL_RCC_UART9_CLK_DISABLE();
            break;
#endif /* UART9 && CONFIG_USART_NUM_9 */

#if defined(UART10) && (CONFIG_USART_NUM_10 == 1)
        case USART_NUM_10:
            __HAL_RCC_UART10_CLK_DISABLE();
            break;
#endif /* UART10 && CONFIG_USART_NUM_10 */

        default:
            break;
    }
}

/**
 * @brief Get USART object
 * 
 * @param huart USART handle
 * @return Pointer to USART object
 */
static usart_obj_t *usart_hal_get_obj(UART_HandleTypeDef *huart) {
    usart_obj_t *obj = NULL;

#if defined(USART1) && (CONFIG_USART_NUM_1 == 1)
    if (huart->Instance == USART1) {
        obj = &usart_obj[USART_NUM_1];
    }
#endif /* USART1 && CONFIG_USART_NUM_1 */

#if defined(USART2) && (CONFIG_USART_NUM_2 == 1)
    if (huart->Instance == USART2) {
        obj = &usart_obj[USART_NUM_2];
    }
#endif /* USART2 && CONFIG_USART_NUM_2 */

#if defined(USART3) && (CONFIG_USART_NUM_3 == 1)
    if (huart->Instance == USART3) {
        obj = &usart_obj[USART_NUM_3];
    }
#endif /* USART3 && CONFIG_USART_NUM_3 */

#if defined(UART4) && (CONFIG_USART_NUM_4 == 1)
    if (huart->Instance == UART4) {
        obj = &usart_obj[USART_NUM_4];
    }
#endif /* UART4 && CONFIG_USART_NUM_4 */

#if defined(UART5) && (CONFIG_USART_NUM_5 == 1)
    if (huart->Instance == UART5) {
        obj = &usart_obj[USART_NUM_5];
    }
#endif /* UART5 && CONFIG_USART_NUM_5 */

#if defined(USART6) && (CONFIG_USART_NUM_6 == 1)
    if (huart->Instance == USART6) {
        obj = &usart_obj[USART_NUM_6];
    }
#endif /* USART6 && CONFIG_USART_NUM_6 */

#if defined(UART7) && (CONFIG_USART_NUM_7 == 1)
    if (huart->Instance == UART7) {
        obj = &usart_obj[USART_NUM_7];
    }
#endif /* UART7 && CONFIG_USART_NUM_7 */

#if defined(UART8) && (CONFIG_USART_NUM_8 == 1)
    if (huart->Instance == UART8) {
        obj = &usart_obj[USART_NUM_8];
    }
#endif /* UART8 && CONFIG_USART_NUM_8 */

#if defined(UART9) && (CONFIG_USART_NUM_9 == 1)
    if (huart->Instance == UART9) {
        obj = &usart_obj[USART_NUM_9];
    }
#endif /* UART9 && CONFIG_USART_NUM_9 */

#if defined(UART10) && (CONFIG_USART_NUM_10 == 1)
    if (huart->Instance == UART10) {
        obj = &usart_obj[USART_NUM_10];
    }
#endif /* UART10 && CONFIG_USART_NUM_10 */

    return obj;
}
