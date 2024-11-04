/**
  * @file    ssd1306.h
  * @author  LuckkMaker
  * @brief   SSD1306 driver for omni
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
#ifndef OMNI_DRIVER_SSD1306_H
#define OMNI_DRIVER_SSD1306_H

/* Includes ------------------------------------------------------------------*/
#include "drivers/display/ssd1306_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief SSD1306 event
 */
#define SSD1306_EVENT_INITIALIZED          (1 << 0)    /**< Initialized */

/**
 * @brief Event callback function
 */
typedef void (*ssd1306_event_callback)(uint32_t event);

/**
 * @brief SSD1306 low-level interface
 */
typedef struct {
    int (*init)(void);
    int (*deinit)(void);
    int (*write_bus)(uint8_t *buffer, uint32_t len);
} ssd1306_driver_io_t;

/**
 * @brief SSD1306 driver configuration
 */
typedef struct ssd1306_driver_config {
    ssd1306_driver_io_t io;             /**< Low-level interface */
    ssd1306_event_callback event_cb;    /**< Event callback */
} ssd1306_driver_config_t;

/**
 * @brief SSD1306 driver status
 */
typedef struct ssd1306_driver_status {
    uint32_t initialized : 1;           /**< Initialized */
} ssd1306_driver_status_t;

/**
 * @brief SSD1306 driver error
 */
typedef struct ssd1306_driver_error {
    uint32_t reserved : 32;             /**< Reserved */
} ssd1306_driver_error_t;

/**
 * @brief SSD1306 driver object
 */
typedef struct {
    ssd1306_driver_status_t status;
    ssd1306_driver_error_t error;
    ssd1306_event_callback event_cb;
} ssd1306_obj_t;

/**
 * @brief Open SSD1306
 */
typedef int (*ssd1306_open_t)(ssd1306_num_t ssd1306_num, ssd1306_driver_config_t *config);

/**
 * @brief Close SSD1306
 */
typedef int (*ssd1306_close_t)(ssd1306_num_t ssd1306_num);

/**
 * @brief Start SSD1306
 */
typedef void (*ssd1306_start_t)(ssd1306_num_t ssd1306_num);

/**
 * @brief Stop SSD1306
 */
typedef void (*ssd1306_stop_t)(ssd1306_num_t ssd1306_num);

/**
 * @brief SSD1306 get status
 */
typedef ssd1306_driver_status_t (*ssd1306_get_status_t)(ssd1306_num_t ssd1306_num);

/**
 * @brief SSD1306 get error
 */
typedef ssd1306_driver_error_t (*ssd1306_get_error_t)(ssd1306_num_t ssd1306_num);

/**
 * @brief SSD1306 driver API
 */
struct ssd1306_driver_api {
    ssd1306_open_t open;
    ssd1306_close_t close;
    ssd1306_start_t start;
    ssd1306_stop_t stop;
    ssd1306_get_status_t get_status;
    ssd1306_get_error_t get_error;
};

extern const struct ssd1306_driver_api ssd1306_driver;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* OMNI_DRIVER_SSD1306_H */
