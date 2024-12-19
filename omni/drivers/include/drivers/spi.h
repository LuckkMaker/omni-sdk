/**
  * @file    spi.h
  * @author  LuckkMaker
  * @brief   SPI driver for omni
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
#ifndef OMNI_DRIVER_SPI_H
#define OMNI_DRIVER_SPI_H

/* Includes ------------------------------------------------------------------*/
#include "drivers/spi_types.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief SPI event
 */
#define SPI_EVENT_INITIALIZED          (1 << 0)    /**< Initialized */
#define SPI_EVENT_TRANSFER_COMPLETE    (1 << 1)    /**< Data transfer complete */
#define SPI_EVENT_TRANSFER_LOST        (1 << 2)    /**< Receive overflow or transmit underflow */
#define SPI_EVENT_MODE_FAULT           (1 << 3)    /**< Master mode fault */

/**
 * @brief Event callback function
 */
typedef void (*spi_event_callback)(uint32_t event);

/**
 * @brief SPI driver configuration
 */
typedef struct spi_driver_config {
    /**
     * @brief SPI option
     * 
     * It is a bit-field value that can be a combination of the following values:
     * - 0: Master or slave mode @ref SPI mode
     * - 1..2: Direction @ref SPI direction
     * - 3: Polarity @ref SPI clock polarity
     * - 4: Phase @ref SPI clock phase
     * - 5..10: Data size (4..16 bits)
     * - 11: Bit order @ref SPI bit order
     * - 12..13: Slave select @ref SPI slave select
     * - 14: Control SS @ref SPI control slave select
     * - 15: Protocol mode @ref SPI protocol mode
     * - 16..31: Reserved
     */
    spi_option_t option;            /**< SPI option */
    uint32_t frequency;             /**< SPI frequency */
    spi_event_callback event_cb;    /**< Event callback */
} spi_driver_config_t;

/**
 * @brief SPI driver status
 */
typedef struct spi_driver_status {
    uint32_t is_initialized:1;      /**< Initialization status */
    uint32_t busy:1;                /**< Busy flag */
    uint32_t reserved:31;           /**< Reserved */
} spi_driver_status_t;

/**
 * @brief SPI driver error
 */
typedef struct spi_driver_error {
    uint32_t bus_error:1;           /**< Bus error */
    uint32_t reserved:31;           /**< Reserved */
} spi_driver_error_t;

/**
 * @brief SPI driver data
 */
typedef struct spi_driver_data {
    uint8_t *tx_buffer;             /**< Pointer to TX buffer */
    volatile uint32_t tx_num;       /**< Total number of bytes to sent */
    volatile uint32_t tx_count;     /**< Number of bytes sent */
    uint8_t *rx_buffer;             /**< Pointer to RX buffer */
    volatile uint32_t rx_num;       /**< Total number of bytes to receive */
    volatile uint32_t rx_count;     /**< Number of bytes received */
} spi_driver_data_t;

/**
 * @brief SPI object
 */
typedef struct {
    spi_dev_t *dev;
    spi_driver_data_t data;
    volatile spi_driver_status_t status;
    volatile spi_driver_error_t error;
    spi_event_callback event_cb;
} spi_obj_t;

/**
 * @brief Initialize SPI bus
 */
typedef int (*spi_init_t)(spi_num_t spi_num, spi_driver_config_t *config);

/**
 * @brief Deinitialize SPI bus
 */
typedef int (*spi_deinit_t)(spi_num_t spi_num);

/**
 * @brief Start SPI bus
 */
typedef void (*spi_start_t)(spi_num_t spi_num);

/**
 * @brief Stop SPI bus
 */
typedef void (*spi_stop_t)(spi_num_t spi_num);

/**
 * @brief Send data to SPI bus
 */
typedef int (*spi_send_t)(spi_num_t spi_num, const void *data, uint32_t len);

/**
 * @brief Receive data from SPI bus
 */
typedef int (*spi_receive_t)(spi_num_t spi_num, void *data, uint32_t len);

/**
 * @brief Transfer data to SPI bus
 */
typedef int (*spi_transfer_t)(spi_num_t spi_num, const void *tx_data, void *rx_data, uint32_t len);

/**
 * @brief Get SPI bus status
 */
typedef spi_driver_status_t (*spi_get_status_t)(spi_num_t spi_num);

/**
 * @brief Get SPI bus error
 */
typedef spi_driver_error_t (*spi_get_error_t)(spi_num_t spi_num);

/**
 * @brief SPI driver API
 */
struct spi_driver_api {
    spi_init_t init;
    spi_deinit_t deinit;
    spi_start_t start;
    spi_stop_t stop;
    spi_send_t send;
    spi_receive_t receive;
    spi_transfer_t transfer;
    spi_get_status_t get_status;
    spi_get_error_t get_error;
};

extern const struct spi_driver_api spi_driver;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* OMNI_DRIVER_SPI_H */
