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
#include "application/main.h"

/* Private includes ----------------------------------------------------------*/
#include <omni.h>
#include "cmsis_os2.h"

#define ECO_RX_BUFFER_SIZE  KB(4)

#define LED_PIN GET_PIN(E, 5)

// Thread
static osThreadId_t start_thread_id = NULL;
static osThreadId_t led_thread_id = NULL;
static osThreadId_t eco_thread_id = NULL;

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

static const osThreadAttr_t eco_thread_attr = {
    .name = "eco_thread",
    .priority = osPriorityAboveNormal,
    .stack_size = 1024,
};

static void create_thread(void);
static void start_thread(void *argument);
static void led_thread(void *argument);
static void eco_thread(void *argument);

uint8_t rx_buffer[ECO_RX_BUFFER_SIZE];
uint32_t rx_buffer_ptr_in = 0;
uint32_t rx_buffer_ptr_out = 0;

static void cdc_periodic_timer_callback(void *argument);
static void uart1_event_callback(uint32_t event);

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
    gpio_driver_config_t gpio1_config = {
        .mode = GPIO_MODE_PP_OUTPUT,
        .pull = GPIO_PULL_NONE,
        .speed = GPIO_SPEED_LEVEL_HIGH,
        .level = GPIO_LEVEL_LOW,
    };

    gpio_driver.open(LED_PIN, &gpio1_config);

    usart_driver_config_t uart1_config = {
        .mode = USART_MODE_UART,
        .baudrate = 115200,
        .data_bits = USART_DATA_BITS_8,
        .stop_bits = USART_STOP_BITS_1,
        .parity = USART_PARITY_DISABLE,
        .flow_ctrl = USART_FLOW_CTRL_DISABLE,
        .event_cb = uart1_event_callback,
    };

    usart_driver.open(USART_NUM_1, &uart1_config);

    usart_driver.read(USART_NUM_1, rx_buffer, 1);
}

/**
 * @brief Create thread
 */
static void create_thread(void) {
    led_thread_id = osThreadNew(led_thread, NULL, &led_thread_attr);
    eco_thread_id = osThreadNew(eco_thread, NULL, &eco_thread_attr);
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

    gpio_driver.open(LED_PIN, &gpio1_config);

    while (1) {
        gpio_driver.toggle(LED_PIN);

        /* Relatively accurate delay */
        tick += freq;
        osDelayUntil(tick);
    }
}

/**
 * @brief Thread for ECO
 */
static void eco_thread(void *argument) {
    uint16_t freq = 5;
    uint32_t tick;
    uint32_t buffer_ptr;
    uint32_t buffer_size;

    /* Get the current tick */
    tick = osKernelGetTickCount();

    while (1) {
        if (rx_buffer_ptr_in != rx_buffer_ptr_out) {
            if (rx_buffer_ptr_out > rx_buffer_ptr_in) {
                buffer_size = ECO_RX_BUFFER_SIZE - rx_buffer_ptr_out;
            } else {
                buffer_size = rx_buffer_ptr_in - rx_buffer_ptr_out;
            }

            buffer_ptr = rx_buffer_ptr_out;

            if (usart_driver.write(USART_NUM_1, (uint8_t*)(rx_buffer + buffer_ptr), buffer_size) == 0) {
                rx_buffer_ptr_out += buffer_size;

                if (rx_buffer_ptr_out >= ECO_RX_BUFFER_SIZE) {
                    rx_buffer_ptr_out = 0;
                }
            }
        }

        /* Relatively accurate delay */
        tick += freq;
        osDelayUntil(tick);
    }
}

/**
 * @brief UART event callback function
 * 
 * @param event 
 */
static void uart1_event_callback(uint32_t event) {
    if (event & USART_EVENT_RX_TIMEOUT) {
        // Do something
    }

    if (event & USART_EVENT_RECEIVE_COMPLETE) {
        rx_buffer_ptr_in++;

        if (rx_buffer_ptr_in >= ECO_RX_BUFFER_SIZE) {
            rx_buffer_ptr_in = 0;
        }

        usart_driver.read(USART_NUM_1, (uint8_t*)(rx_buffer + rx_buffer_ptr_in), 1);
    }

    if (event & USART_EVENT_SEND_COMPLETE) {
    }
}
