/**
  * @file    console.h
  * @author  LuckkMaker
  * @brief   Console component for omni
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
#ifndef COMPONENT_CONSOLE_H
#define COMPONENT_CONSOLE_H

/* Includes ------------------------------------------------------------------*/
#include "console/console_types.h"

#ifdef __cplusplus
extern "C" {
#endif

// Alias for log functions
#define log_error       logError
#define log_warning     logWarning
#define log_info        logInfo
#define log_debug       logDebug

/**
 * @brief Console event
 */
#define CONSOLE_EVENT_INITIALIZED       (1 << 0)    /**< Initialized */

/**
 * @brief Event callback function
 */
typedef void (*console_event_callback)(uint32_t event);

/**
 * @brief Console configuration
 */
typedef struct console_config {
    void *buffer;
    uint32_t buffer_size;
} console_config_t;

/**
 * @brief Console status
 */
typedef struct console_status {
    uint32_t is_initialized:1;      /**< Initialization status */
    uint32_t reserved:31;           /**< Reserved */
} console_status_t;

/**
 * @brief Console error
 */
typedef struct console_error {
    uint32_t reserved:32;           /**< Reserved */
} console_error_t;

/**
 * @brief Console data
 */
typedef struct console_data {
    void *buffer;                /**< Pointer to shell buffer */
} console_data_t;

/**
 * @brief Console object structure
 */
typedef struct {
    console_shell_t *shell;
    console_log_t *log;
    console_config_t config;
    console_data_t data;
    volatile console_status_t status;
    volatile console_error_t error;
    console_event_callback event_cb;
} console_obj_t;

/**
 * @brief Open console
 */
typedef int (*console_open_t)(console_obj_t *obj);

/**
 * @brief Close console
 */
typedef int (*console_close_t)(console_obj_t *obj);

/**
 * @brief Start console
 */
typedef void (*console_start_t)(console_obj_t *obj);

/**
 * @brief Stop console
 */
typedef void (*console_stop_t)(console_obj_t *obj);

/**
 * @brief Console get status
 */
typedef console_status_t (*console_get_status_t)(console_obj_t *obj);

/**
 * @brief Console get error
 */
typedef console_error_t (*console_get_error_t)(console_obj_t *obj);

/**
 * @brief Console API
 */
struct console_api {
    console_open_t open;
    console_close_t close;
    console_start_t start;
    // console_stop_t stop;
    console_get_status_t get_status;
    console_get_error_t get_error;
};

extern const struct console_api console;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* COMPONENT_CONSOLE_H */
