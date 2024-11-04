/**
  * @file    timer.h
  * @author  LuckkMaker
  * @brief   Timer driver for omni
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
#ifndef OMNI_DRIVER_TIMER_H
#define OMNI_DRIVER_TIMER_H

/* Includes ------------------------------------------------------------------*/
#include "drivers/timer_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Timer delay ms function
 */
typedef void (*timer_delay_ms_t)(uint32_t delay);

/**
 * @brief Timer delay us function
 */
typedef void (*timer_delay_us_t)(uint32_t delay);

/**
 * @brief Get current tick
 */
typedef uint32_t (*timer_get_tick_t)(uint32_t frequency);

/**
 * @brief Timer driver API
 */
struct timer_driver_api {
    timer_delay_ms_t delay_ms;
    timer_delay_us_t delay_us;
    timer_get_tick_t get_tick;
};

extern const struct timer_driver_api timer_driver;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* OMNI_DRIVER_TIMER_H */
