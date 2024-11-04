/**
  * @file    ssd1306.c
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

/* Includes ------------------------------------------------------------------*/
#include "drivers/display/ssd1306.h"

static ssd1306_obj_t *p_ssd1306_obj[SSD1306_NUM_MAX];

static int ssd1306_open(ssd1306_num_t ssd1306_num, ssd1306_driver_config_t *config);
static int ssd1306_close(ssd1306_num_t ssd1306_num);
static void ssd1306_start(ssd1306_num_t ssd1306_num);
static void ssd1306_stop(ssd1306_num_t ssd1306_num);
static ssd1306_driver_status_t ssd1306_get_status(ssd1306_num_t ssd1306_num);
static ssd1306_driver_error_t ssd1306_get_error(ssd1306_num_t ssd1306_num);

const struct ssd1306_driver_api ssd1306_driver = {
    .open = ssd1306_open,
    .close = ssd1306_close,
    .start = ssd1306_start,
    .stop = ssd1306_stop,
    .get_status = ssd1306_get_status,
    .get_error = ssd1306_get_error,
};

/**
 * @brief Open SSD1306
 *
 * @param ssd1306_num SSD1306 number
 * @param config Pointer to SSD1306 driver configuration
 * @return Operation status
 */
static int ssd1306_open(ssd1306_num_t ssd1306_num, ssd1306_driver_config_t *config) {
    omni_assert(ssd1306_num < SSD1306_NUM_MAX);
    omni_assert_not_null(config);

    p_ssd1306_obj[ssd1306_num] = (ssd1306_obj_t *)OMNI_MALLOC(sizeof(ssd1306_obj_t));
    if (p_ssd1306_obj[ssd1306_num] == NULL) {
        return OMNI_FAIL;
    }

    // Set event callback
    if (config->event_cb != NULL) {
        p_ssd1306_obj[ssd1306_num]->event_cb = config->event_cb;
    } else {
        p_ssd1306_obj[ssd1306_num]->event_cb = NULL;
    }

    ssd1306_obj_t *obj = p_ssd1306_obj[ssd1306_num];

    // Call status
    obj->status = (ssd1306_driver_status_t){0};

    // Call error
    obj->error = (ssd1306_driver_error_t){0};

    // Initialize IO
    omni_assert_not_null(config->io);
    if (config->io.init() != OMNI_OK) {
        return OMNI_FAIL;
    }

    // Initialize SSD1306
}

/**
 * @brief Close SSD1306
 *
 * @param ssd1306_num SSD1306 number
 * @return Operation status
 */
static int ssd1306_close(ssd1306_num_t ssd1306_num) {
    omni_assert(ssd1306_num < SSD1306_NUM_MAX);

    ssd1306_obj_t *obj = p_ssd1306_obj[ssd1306_num];
    omni_assert_not_null(obj);

    // Close IO
    if (obj->config->io.close() != OMNI_OK) {
        return OMNI_FAIL;
    }

    // Free object
    if (p_ssd1306_obj[ssd1306_num] != NULL) {
        OMNI_FREE(p_ssd1306_obj[ssd1306_num]);
        p_ssd1306_obj[ssd1306_num] = NULL;
    }

    return OMNI_OK;
}

/**
 * @brief Start SSD1306
 *
 * @param ssd1306_num SSD1306 number
 */
static void ssd1306_start(ssd1306_num_t ssd1306_num) {
    omni_assert(ssd1306_num < SSD1306_NUM_MAX);

    ssd1306_obj_t *obj = p_ssd1306_obj[ssd1306_num];
    omni_assert_not_null(obj);

    uint8_t cmd_buf[] = {
        SSD1306_SET_DISPLAY_ON,
    }
}

/**
 * @brief SSD1306 write command
 *
 * @param ssd1306_num SSD1306 number
 * @param buffer Pointer to buffer
 * @param len Buffer length
 * @return Operation status
 */
static int ssd1306_write_cmd(ssd1306_num_t ssd1306_num, uint8_t *buffer, uint32_t len) {
    omni_assert(ssd1306_num < SSD1306_NUM_MAX);
    omni_assert_not_null(buffer);
    omni_assert_non_zero(len);

    ssd1306_obj_t *obj = p_ssd1306_obj[ssd1306_num];
    omni_assert_not_null(obj);

    uint8_t *cmd_buf = (uint8_t *)OMNI_MALLOC(len + 1);
    cmd_buf[0] = SSD1306_CMD_STREAM;

    for (uint32_t i = 0; i < len; i++) {
        cmd_buf[i + 1] = buffer[i];
    }

    if (obj->config->io.write_bus(buffer, len + 1) != OMNI_OK) {
        OMNI_FREE(cmd_buf);
        return OMNI_FAIL;
    }

    OMNI_FREE(cmd_buf);

    return OMNI_OK;
}

/**
 * @brief SSD1306 write data
 *
 * @param ssd1306_num SSD1306 number
 * @param buffer Pointer to buffer
 * @param len Buffer length
 * @return Operation status
 */
static int ssd1306_write_data(ssd1306_num_t ssd1306_num, uint8_t *buffer, uint32_t len) {
    omni_assert(ssd1306_num < SSD1306_NUM_MAX);
    omni_assert_not_null(buffer);
    omni_assert_non_zero(len);

    ssd1306_obj_t *obj = p_ssd1306_obj[ssd1306_num];
    omni_assert_not_null(obj);

    uint8_t *data_buf = (uint8_t *)OMNI_MALLOC(len + 1);
    data_buf[0] = SSD1306_DATA_STREAM;

    for (uint32_t i = 0; i < len; i++) {
        data_buf[i + 1] = buffer[i];
    }

    if (obj->config->io.write_bus(buffer, len + 1) != OMNI_OK) {
        OMNI_FREE(data_buf);
        return OMNI_FAIL;
    }

    OMNI_FREE(data_buf);

    return OMNI_OK;
}
