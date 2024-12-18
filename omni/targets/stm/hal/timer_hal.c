/**
  * @file    dwt_hal.c
  * @author  LuckkMaker
  * @brief   DWT HAL driver
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
#include "drivers/timer.h"
#include "hal/dwt_hal.h"

static void timer_hal_delay_ms(uint32_t delay);
static void timer_hal_delay_us(uint32_t delay);
static uint32_t timer_hal_get_tick(uint32_t frequency);

const struct timer_driver_api timer_driver = {
    .delay_ms = timer_hal_delay_ms,
    .delay_us = timer_hal_delay_us,
    .get_tick = timer_hal_get_tick,
};

/**
 * @brief Delay for a number of milliseconds
 * 
 * @param delay Number of milliseconds to delay
 */
static void timer_hal_delay_ms(uint32_t delay) {
    dwt_hal_delay_ms(delay);
}

/**
 * @brief Delay for a number of microseconds
 * 
 * @param delay Number of microseconds to delay
 */
static void timer_hal_delay_us(uint32_t delay) {
    dwt_hal_delay_us(delay);
}

/**
 * @brief Get current tick
 * 
 * @return Current tick
 */
static uint32_t timer_hal_get_tick(uint32_t frequency) {
    return dwt_hal_get_tick(frequency);
}
