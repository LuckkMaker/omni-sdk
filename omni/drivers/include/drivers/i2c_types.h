/**
  * @file    i2c_types.h
  * @author  LuckkMaker
  * @brief   I2C driver types
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
#ifndef OMNI_DRIVER_I2C_TYPES_H
#define OMNI_DRIVER_I2C_TYPES_H

/* Includes ------------------------------------------------------------------*/
#include "include/device.h"

#ifdef __cplusplus
extern "C" {
#endif

#define I2C_ADDR_10_BITS_FLAG           0x0400
#define I2C_ADDR_GENERAL_CALL_FLAG      0x8000
#define I2C_REQUEST_WRITE               0x00
#define I2C_REQUEST_READ                0x01

/**
 * @brief I2C mode
 */
typedef enum {
    I2C_MODE_I2C = 0x00,
} i2c_mode_t;

/**
 * @brief I2C transfer mode
 */
typedef enum {
    I2C_XFER_MODE_MASTER = 0x00,
    I2C_XFER_MODE_SLAVE = 0x01,
} i2c_xfer_mode_t;

/**
 * @brief I2C direction
 */
typedef enum {
    I2C_DIR_TRANSMITTER = 0x00,
    I2C_DIR_RECEIVER = 0x01,
} i2c_dir_t;

/**
 * @brief I2C bus speed
 */
typedef enum {
    I2C_BUS_SPEED_STANDARD = 0x00,  /**< Standard mode (100 kHz) */
    I2C_BUS_SPEED_FAST = 0x01,      /**< Fast mode (400 kHz) */
    I2C_BUS_SPEED_FAST_PLUS = 0x02, /**< Fast mode plus (1 MHz) */
    I2C_BUS_SPEED_HIGH = 0x03,      /**< High speed mode (3.4 MHz) */
} i2c_bus_speed_t;

/**
 * @brief I2C address length
 */
typedef enum {
    I2C_ADDR_BITS_7 = 0x00,
    I2C_ADDR_BITS_10 = 0x01,
} i2c_addr_bits_t;

/**
 * @brief I2C memory address size
 */
typedef enum {
    I2C_MEM_ADDR_SIZE_8 = 0x00,
    I2C_MEM_ADDR_SIZE_16 = 0x01,
} i2c_mem_addr_size_t;

/**
 * @brief I2C port number
 */
typedef enum {
#if (CONFIG_I2C_NUM_1 == 1)
    I2C_NUM_1 = 0x01,
#endif /* (CONFIG_I2C_NUM_1 == 1) */
#if (CONFIG_I2C_NUM_2 == 1)
    I2C_NUM_2,
#endif /* (CONFIG_I2C_NUM_2 == 1) */
#if (CONFIG_I2C_NUM_3 == 1)
    I2C_NUM_3,
#endif /* (CONFIG_I2C_NUM_3 == 1) */
    I2C_NUM_MAX,
} i2c_num_t;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* OMNI_DRIVER_I2C_TYPES_H */
