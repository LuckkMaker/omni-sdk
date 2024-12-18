/**
  * @file    init.c
  * @author  LuckkMaker
  * @brief   Initialization functions for Omni
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
#include "drivers/init.h"
#include "hal/irq_hal.h"
#include "drivers/clock.h"

/**
 * @brief Initialize driver
 */
void driver_init(void) {
    // Initialize device
    device_init();

    // Initialize interrupt
    interrupt_init();

    // Initialize power
    power_init();

    // Initialize clock
    if (clock_driver.init() != OMNI_OK) {
        error_handler();
    }

    // Initialize watchdog
    watchdog_init();
}

/**
 * @brief Initialize interrupt
 */
void interrupt_init(void) {
    // Set interrupt priority grouping
    irq_hal_set_priority_grouping(IRQ_PRIORITY_GROUP_4);
}

/**
 * @brief Initialize device
 */
__weak void device_init(void) {
}

/**
 * @brief Initialize power
 */
__weak void power_init(void) {
}

/**
 * @brief Initialize watchdog
 */
__weak void watchdog_init(void) {
}

/**
 * @brief Error handler
 */
__weak void error_handler(void) {
    __disable_irq();

    while (1) {
    }
}
