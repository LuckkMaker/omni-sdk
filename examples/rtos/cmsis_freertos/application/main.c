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
#include "cmsis_os2.h"

#define LED1_PIN GET_PIN(E, 5)
#define LED2_PIN GET_PIN(E, 6)

static osThreadId_t start_thread_id = NULL;
static osThreadId_t led_thread_id = NULL;

static const osThreadAttr_t start_thread_attr = {
    .name = "start_thread",
    .priority = osPriorityNormal,
    .stack_size = 512,
};

static const osThreadAttr_t led_thread_attr = {
    .name = "led_thread",
    .priority = osPriorityNormal,
    .stack_size = 256,
};

static void create_thread(void);
static void start_thread(void *argument);
static void led_thread(void *argument);

/**
 * @brief The application entry point.
 * 
 * @return int 
 */
int main(void) {
    setup();

    // Initialize the RTOS scheduler
    osKernelInitialize();

    // Create the start thread
    start_thread_id = osThreadNew(start_thread, NULL, &start_thread_attr);

    // Start the RTOS scheduler
    osKernelStart();

    while (1) {
        // Do something
    }
}

/**
 * @brief Setup the application
 */
void setup(void) {
}

/**
 * @brief Create thread
 */
static void create_thread(void) {
    led_thread_id = osThreadNew(led_thread, NULL, &led_thread_attr);
}

/**
 * @brief Start thread
 */
static void start_thread(void *argument) {
    create_thread();
    osThreadTerminate(start_thread_id);

    while (1) {
        // Do something
    }
}

/**
 * @brief Thread for LED
 */
static void led_thread(void *argument) {
    uint16_t freq = 500;
    uint32_t tick;

    gpio_driver_config_t gpio1_config = {
        .mode = GPIO_MODE_PP_OUTPUT,
        .pull = GPIO_PULL_NONE,
        .speed = GPIO_SPEED_LEVEL_HIGH,
        .level = GPIO_LEVEL_LOW,
    };

    /* Get the current tick */
    tick = osKernelGetTickCount();

    gpio_driver.init(LED1_PIN, &gpio1_config);
    gpio_driver.init(LED2_PIN, &gpio1_config);

    while (1) {
        gpio_driver.toggle(LED1_PIN);
        gpio_driver.toggle(LED2_PIN);

        /* Relatively accurate delay */
        tick += freq;
        osDelayUntil(tick);
    }
}
