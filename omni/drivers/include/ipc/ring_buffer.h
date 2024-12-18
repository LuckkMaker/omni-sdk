/**
  * @file    ring_buffer.h
  * @author  LuckkMaker
  * @brief   Ring buffer component for omni
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
#ifndef OMNI_DRIVERS_RING_BUFFER_H
#define OMNI_DRIVERS_RING_BUFFER_H

/* Includes ------------------------------------------------------------------*/
#include "include/device.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Ring buffer event
 */
#define RING_BUFFER_EVENT_INITIALIZED    (1 << 0)    /**< Initialized */
#define RING_BUFFER_EVENT_EMPTY          (1 << 1)    /**< Empty */
#define RING_BUFFER_EVENT_FULL           (1 << 2)    /**< Full */
#define RING_BUFFER_EVENT_HALF_FULL      (1 << 3)    /**< Half full */

/**
 * @brief Ring buffer status
 */
typedef struct ring_buffer_status {
    uint32_t is_initialized : 1;    /**< Initialized */
    uint32_t is_empty : 1;          /**< Empty */
    uint32_t is_full : 1;           /**< Full */
    uint32_t is_half_full : 1;      /**< Half full */
    uint32_t reserved : 28;         /**< Reserved */
} ring_buffer_status_t;

/**
 * @brief Ring buffer
 */
typedef struct {
    uint8_t *buffer;
    uint8_t head;
    uint8_t tail;
    uint32_t size;
    ring_buffer_status_t status;
} ring_buffer_t;

/**
 * @brief Initialize ring buffer
 */
typedef int (*rb_init_t)(ring_buffer_t *rb, uint8_t *pool, uint32_t size);

/**
 * @brief Deinitialize ring buffer
 */
typedef int (*rb_deinit_t)(ring_buffer_t *rb);

/**
 * @brief Get the data size of the buffer
 */
typedef uint32_t (*rb_get_data_size_t)(ring_buffer_t *rb);

/**
 * @brief Enqueue the buffer
 */
typedef int (*rb_enqueue_t)(ring_buffer_t *rb, uint8_t value);

/**
 * @brief Dequeue the buffer
 */
typedef int (*rb_dequeue_t)(ring_buffer_t *rb, uint8_t *value);

/**
 * @brief Get the status of the buffer
 */
typedef ring_buffer_status_t (*rb_get_status_t)(ring_buffer_t *rb);

/**
 * @brief Ring buffer API
 */
struct ring_buffer_api {
    rb_init_t init;
    rb_deinit_t deinit;
    rb_get_data_size_t get_data_size;
    rb_enqueue_t enqueue;
    rb_dequeue_t dequeue;
    rb_get_status_t get_status;
};

extern const struct ring_buffer_api ring_buffer;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* OMNI_DRIVERS_RING_BUFFER_H */
