/**
  * @file    usart.h
  * @author  LuckkMaker
  * @brief   USART driver for omni
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
#ifndef OMNI_DRIVER_USART_H
#define OMNI_DRIVER_USART_H

/* Includes ------------------------------------------------------------------*/
#include "drivers/usart_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief USART event
 */
#define USART_EVENT_INITIALIZED          (1 << 0)    /**< Initialized */
#define USART_EVENT_SEND_COMPLETE        (1 << 1)    /**< Send complete */
#define USART_EVENT_RECEIVE_COMPLETE     (1 << 2)    /**< Receive complete */
#define USART_EVENT_TX_COMPLETE          (1 << 3)    /**< TX complete */
#define USART_EVENT_RX_OVERFLOW          (1 << 4)    /**< RX overflow */
#define USART_EVENT_RX_TIMEOUT           (1 << 5)    /**< RX timeout */
#define USART_EVENT_RX_BREAK             (1 << 6)    /**< RX break */
#define USART_EVENT_RX_FRAMING_ERROR     (1 << 7)    /**< RX framing error */
#define USART_EVENT_RX_PARITY_ERROR      (1 << 8)    /**< RX parity error */
#define USART_EVENT_CTS                  (1 << 9)    /**< CTS change */

/**
 * @brief Event callback function
 */
typedef void (*usart_event_callback)(uint32_t event);

/**
 * @brief USART driver configuration
 */
typedef struct usart_driver_config {
    usart_mode_t mode;               /**< USART mode */
    uint32_t baudrate;              /**< Baudrate setting in bps */
    usart_data_bits_t data_bits;     /**< Data bits */
    usart_stop_bits_t stop_bits;     /**< Stop bits */
    usart_parity_t parity;           /**< Parity */
    usart_flow_ctrl_t flow_ctrl;     /**< Flow control setting */
    usart_event_callback event_cb;   /**< Event callback */
} usart_driver_config_t;

/**
 * @brief USART driver status
 */
typedef struct usart_driver_status {
    uint32_t is_initialized:1;      /**< Initialization status */
    uint32_t tx_busy:1;             /**< TX busy flag */
    uint32_t rx_busy:1;             /**< RX busy flag */
    uint32_t reserved:29;           /**< Reserved */
} usart_driver_status_t;

/**
 * @brief USART driver error
 */
typedef struct usart_driver_error {
    uint32_t rx_overflow:1;         /**< RX overflow flag */
    uint32_t rx_break:1;            /**< RX break flag */
    uint32_t rx_framing_error:1;    /**< RX framing error flag */
    uint32_t rx_parity_error:1;     /**< RX parity error flag */
    uint32_t reserved:28;           /**< Reserved */
} usart_driver_error_t;

/**
 * @brief USART driver data
 */
typedef struct usart_driver_data {
    uint8_t *tx_buffer;             /**< Pointer to TX buffer */
    volatile uint32_t tx_num;       /**< Total number of bytes to sent */
    volatile uint32_t tx_count;     /**< Number of bytes sent */
    uint8_t *rx_buffer;             /**< Pointer to RX buffer */
    volatile uint32_t rx_num;       /**< Total number of bytes to receive */
    volatile uint32_t rx_count;     /**< Number of bytes received */
} usart_driver_data_t;

/**
 * @brief USART object
 */
typedef struct {
    usart_dev_t *dev;
    usart_driver_data_t data;
    usart_mode_t mode;
    volatile usart_driver_status_t status;
    volatile usart_driver_error_t error;
    usart_event_callback event_cb;
} usart_obj_t;

/**
 * @brief Initialize USART port
 */
typedef int (*usart_init_t)(usart_num_t usart_num, usart_driver_config_t *config);

/**
 * @brief Deinitialize USART port
 */
typedef int (*usart_deinit_t)(usart_num_t usart_num);

/**
 * @brief Start USART port
 */
typedef void (*usart_start_t)(usart_num_t usart_num);

/**
 * @brief Stop USART port
 */
typedef void (*usart_stop_t)(usart_num_t usart_num);

/**
 * @brief Send data to USART with polling
 */
typedef int (*usart_poll_send_t)(usart_num_t usart_num, const uint8_t *data, uint32_t len, uint32_t timeout);

/**
 * @brief Receive data from USART with polling
 */
typedef int (*usart_poll_receive_t)(usart_num_t usart_num, void *data, uint32_t len, uint32_t timeout);

/**
 * @brief Send data to USART port
 */
typedef int (*usar_send_t)(usart_num_t usart_num, const uint8_t *data, uint32_t len);

/**
 * @brief Receive data from USART port
 */
typedef int (*usart_receive_t)(usart_num_t usart_num, void *data, uint32_t len);

/**
 * @brief Get USART port status
 */
typedef usart_driver_status_t (*usart_get_status_t)(usart_num_t usart_num);

/**
 * @brief Get USART port error
 */
typedef usart_driver_error_t (*usart_get_error_t)(usart_num_t usart_num);

/**
 * @brief USART driver API
 */
struct usart_driver_api {
    usart_init_t init;
    usart_deinit_t deinit;
    usart_start_t start;
    usart_stop_t stop;
    usart_poll_send_t poll_send;
    usart_poll_receive_t poll_receive;
    usar_send_t send;
    usart_receive_t receive;
    usart_get_status_t get_status;
    usart_get_error_t get_error;
};

extern const struct usart_driver_api usart_driver;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* OMNI_DRIVER_USART_H */
