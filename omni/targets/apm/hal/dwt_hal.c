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
#include "hal/dwt_hal.h"

#define DWT_GET_CYCLE_COUNT()   DWT->CYCCNT
#define DWT_RESET_CYCLE_COUNT() DWT->CYCCNT = 0

/**
 * @brief Initialize DWT
 * 
 * @return Operation status
 */
int dwt_hal_init(void) {
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    DWT_RESET_CYCLE_COUNT();
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;

    return OMNI_OK;
}

/**
 * @brief Deinitialize DWT
 * 
 * @return Operation status
 */
int dwt_hal_deinit(void) {
    // Disable DWT unit
    DWT->CTRL &= ~DWT_CTRL_CYCCNTENA_Msk;

    return OMNI_OK;
}

/**
 * @brief Delay for a number of microseconds
 * 
 * @param us Number of microseconds to delay
 */
void dwt_hal_delay_us(uint32_t us) {
    uint32_t start = DWT_GET_CYCLE_COUNT();
    // Calculate number of cycles per microsecond
    uint32_t cycles = us * (SystemCoreClock / 1000000);

    while ((DWT_GET_CYCLE_COUNT() - start) < cycles) {
    }
}

/**
 * @brief Delay for a number of milliseconds
 * 
 * @param ms Number of milliseconds to delay
 */
void dwt_hal_delay_ms(uint32_t ms) {
    dwt_hal_delay_us(ms * 1000);
}

/**
 * @brief Get tick
 * 
 * @return Current tick
 */
uint32_t dwt_hal_get_tick(uint32_t frequency) {
    return DWT_GET_CYCLE_COUNT() / (SystemCoreClock / frequency);
}
