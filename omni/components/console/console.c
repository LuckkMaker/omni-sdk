/**
  * @file    console.c
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

/* Includes ------------------------------------------------------------------*/
#include "console/console.h"

static int console_open(console_obj_t *obj);
static int console_close(console_obj_t *obj);
static void console_start(console_obj_t *obj);
static console_status_t console_get_status(console_obj_t *obj);
static console_error_t console_get_error(console_obj_t *obj);

const struct console_api console = {
    .open = console_open,
    .close = console_close,
    .start = console_start,
    .get_status = console_get_status,
    .get_error = console_get_error,
};

/**
 * @brief Open console
 * 
 * @param obj Pointer to console object structure
 * @return Operation status
 */
static int console_open(console_obj_t *obj) {
    omni_assert_not_null(obj);

    console_config_t *config = &obj->config;

    // Set event callback
    if (obj->event_cb != NULL) {
        obj->event_cb = obj->event_cb;
    } else {
        obj->event_cb = NULL;
    }

    omni_assert_not_null(config->buffer);
    obj->data.buffer = config->buffer;
    if (obj->data.buffer == NULL) {
        return OMNI_FAIL;
    }

    omni_assert_not_null(obj->shell);
    omni_assert_non_zero(config->buffer_size);
    shellInit(obj->shell, obj->data.buffer, config->buffer_size);

    omni_assert_not_null(obj->log);
    if (obj->log->active) {
#if (SHELL_SUPPORT_END_LINE == 1)
        logRegister(obj->log, obj->shell);
#else
        logRegister(obj->log, NULL);
#endif /* (SHELL_SUPPORT_END_LINE == 1) */
    }

    // Set initialized status
    obj->status.is_initialized = 1;
    // Call event callback
    if (obj->event_cb != NULL) {
        // Set initialized event
        obj->event_cb(CONSOLE_EVENT_INITIALIZED);
    }

    return OMNI_OK;
}

/**
 * @brief Close vonsole
 * 
 * @param obj Pointer to console object structure
 * @return Operation status
 */
static int console_close(console_obj_t *obj) {
    omni_assert_not_null(obj);

    shellDeInit(obj->shell);

    if (obj->log->active) {
        // Unregister log function
        logUnRegister(obj->log);
    }

    if (obj->shell != NULL) {
        obj->shell = NULL;
    }

    if (obj->log != NULL) {
        obj->log = NULL;
    }

    if (obj->data.buffer != NULL) {
        obj->data.buffer = NULL;
    }

    if (obj->event_cb != NULL) {
        obj->event_cb = NULL;
    }

    obj->status = (console_status_t){0};
    obj->error = (console_error_t){0};

    return OMNI_OK;
}

/**
 * @brief Start console driver
 *
 * @param obj Pointer to console object structure
 */
static void console_start(console_obj_t *obj) {
    omni_assert_not_null(obj->shell);

    // Run shell
    shellTask(obj->shell);
}

/**
 * @brief Get console status
 *
 * @param obj Pointer to console object structure
 * @return Console status
 */
static console_status_t console_get_status(console_obj_t *obj) {
    omni_assert_not_null(obj);

    return obj->status;
}

/**
 * @brief Get console error
 *
 * @param obj Pointer to console object structure
 * @return Console error
 */
static console_error_t console_get_error(console_obj_t *obj) {
    omni_assert_not_null(obj);

    return obj->error;
}
