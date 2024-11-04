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
#include "console_port.h"
#include "cmsis_os2.h"

#define LED_PIN GET_PIN(E, 5)

// Thread
static osThreadId_t start_thread_id = NULL;
static osThreadId_t led_thread_id = NULL;
static osThreadId_t console_thread_id = NULL;

static const osThreadAttr_t start_thread_attr = {
    .name = "start_thread",
    .priority = osPriorityNormal,
    .stack_size = 512,
};

static const osThreadAttr_t led_thread_attr = {
    .name = "led_thread",
    .priority = osPriorityNormal,
    .stack_size = 512,
};

static const osThreadAttr_t console_thread_attr = {
    .name = "console_thread",
    .priority = osPriorityNormal,
    .stack_size = 1024,
};

// Queue
osMessageQueueId_t uart1_rx_queue_id = NULL;

static void create_thread(void);
static void start_thread(void *argument);
static void led_thread(void *argument);
static void console_thread(void *argument);

static void uart1_event_callback(uint32_t event);

uint8_t uart_rx_data;

console_obj_t console1;
uint8_t console_buffer[512];

extern Shell console_shell;
extern Log console_log;
extern osMutexId_t console_shell_mutex;
extern osMutexId_t console_log_mutex;

/**
 * @brief The application entry point.
 * 
 * @return int 
 */
int main(void) {
    setup();

    // Initialize the RTOS scheduler
    osKernelInitialize();

    // Create message queue
    uart1_rx_queue_id = osMessageQueueNew(1, sizeof(uint8_t), NULL);

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
    console_thread_id = osThreadNew(console_thread, NULL, &console_thread_attr);
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
        log_info("log info");

        /* Relatively accurate delay */
        tick += freq;
        osDelayUntil(tick);
    }
}

/**
 * @brief Thread for console
 */
static void console_thread(void *argument) {
    uint16_t freq = 50;
    uint32_t tick;

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

    usart_driver.read(USART_NUM_1, &uart_rx_data, 1);

    // Create console mutex
    // Mutex need to be created at shell thread
    console_shell_mutex = osMutexNew(NULL);
    console_log_mutex = osMutexNew(NULL);

    console1.shell = &console_shell;
    console1.log = &console_log;
    console1.config.buffer = console_buffer;
    console1.config.buffer_size = ARRAY_SIZE(console_buffer);
    if (console.open(&console1) != OMNI_OK) {
        error_handler();
    }

    /* Get the current tick */
    tick = osKernelGetTickCount();

    while (1) {
        console.start(&console1);

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
        // shellHandler(&console_shell, uart_rx_data);
        osMessageQueuePut(uart1_rx_queue_id, &uart_rx_data, 0, 0);
        usart_driver.read(USART_NUM_1, &uart_rx_data, 1);
    }

    if (event & USART_EVENT_SEND_COMPLETE) {
        // Do something
    }
}
