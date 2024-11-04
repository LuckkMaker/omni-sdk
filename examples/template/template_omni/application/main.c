/**
  * @file    main.c
  * @author  LuckkMaker
  * @brief   Main program body
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
#include "main.h"

/* Private includes ----------------------------------------------------------*/
#include <omni.h>

// STM32H750VB PA10
// STM32H743II PB1
// STM32F411CE PC13
// STM32F407IG PE5
#define LED_PIN GET_PIN(E, 6)

uint32_t tick_start = 0;
uint32_t tick_start_us = 0;
uint32_t tick;
uint32_t tick_us;

/**
 * @brief The application entry point.
 * 
 * @return int 
 */
int main(void) {
    setup();

    while (1) {
        // Do something
        gpio_driver.toggle(LED_PIN);
        tick_start = timer_driver.get_tick(1000);
        tick_start_us = timer_driver.get_tick(10000000);
        timer_driver.delay_ms(500);
        tick = timer_driver.get_tick(1000);
        tick_us = timer_driver.get_tick(10000000);
    }
}

/**
 * @brief Setup the application
 */
void setup(void) {
    gpio_driver_config_t gpio1_config = {
        .mode = GPIO_MODE_PP_OUTPUT,
        .pull = GPIO_PULL_NONE,
        .speed = GPIO_SPEED_LEVEL_HIGH,
        .level = GPIO_LEVEL_LOW,
    };

    gpio_driver.open(LED_PIN, &gpio1_config);
}
