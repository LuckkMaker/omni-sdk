/**
  * @file    ring_buffer.c
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

/* Includes ------------------------------------------------------------------*/
#include "ipc/ring_buffer.h"

static int rb_init(ring_buffer_t *rb, uint8_t *pool, uint32_t size);
static int rb_deinit(ring_buffer_t *rb);
static uint32_t rb_get_data_size(ring_buffer_t *rb);
static int rb_enqueue(ring_buffer_t *rb, uint8_t value);
static int rb_dequeue(ring_buffer_t *rb, uint8_t *value);
static ring_buffer_status_t rb_get_status(ring_buffer_t *rb);

const struct ring_buffer_api ring_buffer = {
    .init = rb_init,
    .deinit = rb_deinit,
    .get_data_size = rb_get_data_size,
    .enqueue = rb_enqueue,
    .dequeue = rb_dequeue,
    .get_status = rb_get_status,
};

static bool rb_is_empty(ring_buffer_t *rb);
static bool rb_is_full(ring_buffer_t *rb);

/**
 * @brief Initialize ring buffer
 * 
 * @param rb Pointer to the ring buffer
 * @param pool Pointer to the buffer pool
 * @param size Size of the buffer
 * @return Operation status
 */
static int rb_init(ring_buffer_t *rb, uint8_t *pool, uint32_t size) {
    omni_assert_not_null(rb);
    omni_assert_not_null(pool);
    omni_assert_non_zero(size);

    rb->buffer = pool;
    rb->head = 0;
    rb->tail = 0;
    rb->size = size;

    return OMNI_OK;
}

/**
 * @brief Deinitialize ring buffer
 * 
 * @param rb Pointer to the ring buffer
 * @return Operation status
 */
static int rb_deinit(ring_buffer_t *rb) {
    omni_assert_not_null(rb);

    if (rb->buffer != NULL) {
        rb->buffer = NULL;
    }

    rb->head = 0;
    rb->tail = 0;
    rb->size = 0;

    return OMNI_OK;
}

/**
 * @brief Get the data size of the buffer
 * 
 * @param rb Pointer to the ring buffer
 * @return Data size
 */
static uint32_t rb_get_data_size(ring_buffer_t *rb) {
    omni_assert_not_null(rb);

    if (rb->status.is_empty) {
        return 0;
    } else if (rb->status.is_full) {
        return rb->size;
    } else {
        return (rb->tail - rb->head + rb->size) % rb->size;
    }
}

/**
 * @brief Enqueue the buffer
 * 
 * @param rb Pointer to the ring buffer
 * @param value Value to enqueue
 * @return Operation status
 */
static int rb_enqueue(ring_buffer_t *rb, uint8_t value) {
    omni_assert_not_null(rb);

    if (rb_is_full(rb)) {
        rb->status.is_full = 1;
        return OMNI_FAIL;
    }

    rb->buffer[rb->tail] = value;
    rb->tail = (rb->tail + 1) % rb->size;

    return OMNI_OK;
}

/**
 * @brief Dequeue the buffer
 * 
 * @param rb Pointer to the ring buffer
 * @param value Pointer to the value
 * @return Operation status
 */
static int rb_dequeue(ring_buffer_t *rb, uint8_t *value) {
    omni_assert_not_null(rb);
    omni_assert_not_null(value);

    if (rb_is_empty(rb)) {
        rb->status.is_empty = 1;
        return OMNI_FAIL;
    }

    *value = rb->buffer[rb->head];
    rb->head = (rb->head + 1) % rb->size;

    return OMNI_OK;
}

/**
 * @brief Get the status of the buffer
 * 
 * @param rb Pointer to the ring buffer
 * @return Buffer status
 */
static ring_buffer_status_t rb_get_status(ring_buffer_t *rb) {
    omni_assert_not_null(rb);

    return rb->status;
}

/**
 * @brief Check if the buffer is empty
 * 
 * @param rb Pointer to the ring buffer
 * @return Result
 */
static bool rb_is_empty(ring_buffer_t *rb) {
    return (rb->head == rb->tail);
}

/**
 * @brief Check if the buffer is full
 * 
 * @param rb Pointer to the ring buffer
 * @return Result
 */
static bool rb_is_full(ring_buffer_t *rb) {
    return ((rb->tail + 1) % rb->size == rb->head);
}
