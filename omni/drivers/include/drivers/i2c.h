/**
  * @file    i2c.h
  * @author  LuckkMaker
  * @brief   I2C driver for omni
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
#ifndef OMNI_DRIVER_I2C_H
#define OMNI_DRIVER_I2C_H

/* Includes ------------------------------------------------------------------*/
#include "drivers/i2c_types.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief I2C event
 */
#define I2C_EVENT_INITIALIZED          (1 << 0)    /**< Initialized */
#define I2C_EVENT_TRANSFER_COMPLETE    (1 << 1)    /**< Master/Slave transmit/receive complete */
#define I2C_EVENT_TRANSFER_INCOMPLETE  (1 << 2)    /**< Master/Slave transmit/receive incomplete */
#define I2C_EVENT_GENERAL_CALL         (1 << 3)    /**< General call */
#define I2C_EVENT_SLAVE_TRANSMIT       (1 << 4)    /**< Addressed as slave for transmit but transmit operation is not set */
#define I2C_EVENT_SLAVE_RECEIVE        (1 << 5)    /**< Addressed as slave for receive but receive operation is not set */
#define I2C_EVENT_BUS_ERROR            (1 << 6)    /**< Bus error */
#define I2C_EVENT_ARBITRATION_LOST     (1 << 7)    /**< Arbitration lost */
#define I2C_EVENT_ADDRESS_NACK         (1 << 8)    /**< Address not acknowledged from slave */

/**
 * @brief Event callback function
 */
typedef void (*i2c_event_callback)(uint32_t event);

/**
 * @brief I2C driver configuration
 */
typedef struct i2c_driver_config {
    i2c_mode_t mode;                 /**< I2C mode */
    i2c_bus_speed_t bus_speed;       /**< Bus speed */
    i2c_addr_bits_t own_addr_bits;   /**< Own address bits */
    uint16_t own_addr;               /**< Own address */
    i2c_event_callback event_cb;     /**< Event callback */
} i2c_driver_config_t;

/**
 * @brief I2C driver status
 */
typedef struct i2c_driver_status {
    uint32_t is_initialized:1;      /**< Initialization status */
    uint32_t busy:1;                /**< Busy flag */
    uint32_t general_call:1;        /**< General call */
    uint32_t reserved:29;           /**< Reserved */
} i2c_driver_status_t;

/**
 * @brief I2C driver error
 */
typedef struct i2c_driver_error {
    uint32_t bus_error:1;           /**< Bus error */
    uint32_t arbitration_lost:1;    /**< Arbitration lost */
    uint32_t reserved:30;           /**< Reserved */
} i2c_driver_error_t;

/**
 * @brief I2C driver data
 */
typedef struct i2c_driver_data {
    uint8_t *buffer;                /**< Pointer to transfer buffer */
    volatile uint32_t num;          /**< Total number of bytes to transfer */
    volatile uint32_t count;        /**< Number of bytes transferred */
} i2c_driver_data_t;

/**
 * @brief I2C driver flags
 */
typedef struct i2c_driver_flags {
    uint32_t pending:1;             /**< Pending flag */
    uint32_t no_stop:1;             /**< No stop flag */
    uint32_t xfer_set:1;            /**< Transfer set flag */
    uint32_t reserved:29;           /**< Reserved */
} i2c_driver_flags_t;

/**
 * @brief I2C object
 */
typedef struct {
    i2c_dev_t *dev;
    i2c_driver_data_t data;
    i2c_mode_t mode;
    volatile uint32_t device_addr;
    volatile i2c_dir_t direction;
    volatile i2c_xfer_mode_t xfer_mode;
    volatile i2c_driver_flags_t flags;
    volatile i2c_driver_status_t status;
    volatile i2c_driver_error_t error;
    i2c_event_callback event_cb;
} i2c_obj_t;

/**
 * @brief Open I2C BUS
 */
typedef int (*i2c_open_t)(i2c_num_t i2c_num, i2c_driver_config_t *config);

/**
 * @brief Close I2C BUS
 */
typedef int (*i2c_close_t)(i2c_num_t i2c_num);

/**
 * @brief Start I2C BUS
 */
typedef void (*i2c_start_t)(i2c_num_t i2c_num);

/**
 * @brief Stop I2C BUS
 */
typedef void (*i2c_stop_t)(i2c_num_t i2c_num);

/**
 * @brief I2C master transmit
 */
typedef int (*i2c_master_transmit_t)(i2c_num_t i2c_num, uint16_t addr, const uint8_t *data, uint32_t len, uint8_t pending);

/**
 * @brief I2C master receive
 */
typedef int (*i2c_master_receive_t)(i2c_num_t i2c_num, uint16_t addr, uint8_t *data, uint32_t len, uint8_t pending);

/**
 * @brief I2C slave transmit
 */
typedef int (*i2c_slave_transmit_t)(i2c_num_t i2c_num, const uint8_t *data, uint32_t len);

/**
 * @brief I2C slave receive
 */
typedef int (*i2c_slave_receive_t)(i2c_num_t i2c_num, uint8_t *data, uint32_t len);

/**
 * @brief I2C write memory
 */
typedef int (*i2c_write_t)(i2c_num_t i2c_num, uint16_t dev_addr, uint16_t mem_addr, i2c_mem_addr_size_t mem_addr_size, const uint8_t *data, uint16_t len);

/**
 * @brief I2C read memory
 */
typedef int (*i2c_read_t)(i2c_num_t i2c_num, uint16_t dev_addr, uint16_t mem_addr, i2c_mem_addr_size_t mem_addr_size, uint8_t *data, uint16_t len);

/**
 * @brief I2C is device ready
 */
typedef int (*i2c_is_device_ready_t)(i2c_num_t i2c_num, uint16_t dev_addr, uint32_t trials);

/**
 * @brief I2C get status
 */
typedef i2c_driver_status_t (*i2c_get_status_t)(i2c_num_t i2c_num);

/**
 * @brief I2C get error
 */
typedef i2c_driver_error_t (*i2c_get_error_t)(i2c_num_t i2c_num);

/**
 * @brief I2C driver API
 */
struct i2c_driver_api {
    i2c_open_t open;
    i2c_close_t close;
    i2c_start_t start;
    i2c_stop_t stop;
    i2c_master_transmit_t master_transmit;
    i2c_master_receive_t master_receive;
    i2c_slave_transmit_t slave_transmit;
    i2c_slave_receive_t slave_receive;
    i2c_write_t write;
    i2c_read_t read;
    i2c_is_device_ready_t is_device_ready;
    i2c_get_status_t get_status;
    i2c_get_error_t get_error;
};

extern const struct i2c_driver_api i2c_driver;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* OMNI_DRIVER_I2C_H */
