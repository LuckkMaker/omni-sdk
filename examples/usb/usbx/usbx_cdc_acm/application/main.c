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
#include "tx_api.h"
#include "ux_device_cdc_acm.h"

#define LED_PIN GET_PIN(E, 6)

// Task priority
#define START_THREAD_PRIORITY               2
#define LED_THREAD_PRIORITY                 3

// Task stack size
#define START_THREAD_STACK_SIZE            1024
#define LED_THREAD_STACK_SIZE              1024

// ThreadX object control block
TX_THREAD start_thread;
TX_THREAD led_thread;

// ThreadX object memory
ULONG start_thread_stack[START_THREAD_STACK_SIZE / sizeof(ULONG)];
ULONG led_thread_stack[LED_THREAD_STACK_SIZE / sizeof(ULONG)];

// ThreadX entry function
static void start_thread_entry(ULONG parameter);
static void led_thread_entry(ULONG parameter);

/**
 * @brief The application entry point.
 * 
 * @return int 
 */
int main(void) {
    // Enter the ThreadX kernel
    tx_kernel_enter();

    while (1) {
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

    gpio_driver.init(LED_PIN, &gpio1_config);

    usb_phy_driver_config_t usb_phy_config = {
        .mode = USB_MODE_DEVICE,
        .event_cb = NULL,
    };

    usb_phy_driver.init(USB_NUM_1, &usb_phy_config);
}

/**
 * @brief Define the ThreadX application
 */
void tx_application_define(void* first_unused_memory) {
    // Create the start thread
    tx_thread_create(&start_thread, \
                     "Start Thread", \
                     start_thread_entry, \
                     0, \
                     start_thread_stack, \
                     START_THREAD_STACK_SIZE, \
                     START_THREAD_PRIORITY, \
                     START_THREAD_PRIORITY, \
                     TX_NO_TIME_SLICE, \
                     TX_AUTO_START);

    // Create the led thread
    tx_thread_create(&led_thread, \
                     "Led Thread", \
                     led_thread_entry, \
                     0, \
                     led_thread_stack, \
                     LED_THREAD_STACK_SIZE, \
                     LED_THREAD_PRIORITY, \
                     LED_THREAD_PRIORITY, \
                     TX_NO_TIME_SLICE, \
                     TX_AUTO_START);

    // Create the USBX cdc acm thread
    ux_device_cdc_acm_init();
}

static void start_thread_entry(ULONG parameter) {
    // Setup the application
    setup();

    while (1) {
        tx_thread_sleep(100);
    }
}

static void led_thread_entry(ULONG parameter) {
    UINT delay;
    UINT next_time;
    const UINT frequency = 500;

    // Get time after a frequency
    next_time = tx_time_get() + frequency;

    while (1) {
        // Do something
        gpio_driver.toggle(LED_PIN);

        // Absolute delay
        delay = next_time - tx_time_get();
        next_time += frequency;

        if (delay <= frequency) {
            tx_thread_sleep(delay);
        }
    }
}
