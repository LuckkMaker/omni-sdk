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
#include "SEGGER_RTT.h"

#define LED1_PIN GET_PIN(E, 5)
#define LED2_PIN GET_PIN(E, 6)

/**
 * @brief The application entry point.
 * 
 * @return int 
 */
int main(void) {
    setup();

    // Sample code to generate a hard fault
    volatile unsigned int* p;
    unsigned int n;
    p = (unsigned int*)0xCCCCCCCC;
    n = *p;

    while (1) {
        gpio_driver.toggle(LED1_PIN);
        gpio_driver.toggle(LED2_PIN);
        SEGGER_RTT_SetTerminal(0);
        SEGGER_RTT_printf(0, "Hello, World!\n");
        timer_driver.delay_ms(200);
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

    gpio_driver.init(LED1_PIN, &gpio1_config);
    gpio_driver.init(LED2_PIN, &gpio1_config);

    SEGGER_RTT_Init();
    SEGGER_RTT_ConfigUpBuffer(0, "RTTUP", NULL, 0, SEGGER_RTT_MODE_NO_BLOCK_SKIP);
    SEGGER_RTT_ConfigDownBuffer(0, "RTTDOWN", NULL, 0, SEGGER_RTT_MODE_NO_BLOCK_SKIP);
}
