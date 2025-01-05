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
#include <stdio.h>
#include <stdarg.h>
#include <omni.h>
#include "drivers/usart.h"
#include "tx_api.h"
#include "tx_execution_profile.h"
#include "SEGGER_RTT.h"

#define DEBUG_USE_SEGGER_RTT 1

#define LED_PIN GET_PIN(E, 6)

// Task priority
#define START_THREAD_PRIORITY               2
#define LED_THREAD_PRIORITY                 3
#define DEBUG_THREAD_PRIORITY               4

// Task stack size
#define START_THREAD_STACK_SIZE            1024
#define LED_THREAD_STACK_SIZE              1024
#define DEBUG_THREAD_STACK_SIZE            4096

// ThreadX object control block
TX_THREAD start_thread;
TX_THREAD led_thread;
TX_THREAD debug_thread;

// ThreadX object memory
ULONG start_thread_stack[START_THREAD_STACK_SIZE / sizeof(ULONG)];
ULONG led_thread_stack[LED_THREAD_STACK_SIZE / sizeof(ULONG)];
ULONG debug_thread_stack[DEBUG_THREAD_STACK_SIZE / sizeof(ULONG)];

// ThreadX entry function
static void start_thread_entry(ULONG parameter);
static void led_thread_entry(ULONG parameter);
static void debug_thread_entry(ULONG parameter);

// ThreadX mutex
static TX_MUTEX debug_printf_mutex;

extern EXECUTION_TIME _tx_execution_idle_time_total;
extern EXECUTION_TIME _tx_execution_isr_time_total;
extern EXECUTION_TIME _tx_execution_thread_time_total;

volatile double cpu_usage;

static void debug_printf(const char *fmt, ...);
static void uart1_event_callback(uint32_t event);

/**
 * @brief The application entry point.
 * 
 * @return int 
 */
int main(void) {
    setup();

    // Enter the ThreadX kernel
    tx_kernel_enter();

    while (1) {
    }
}

/**
 * @brief Setup the application
 */
void setup(void) {
    driver_init();

    gpio_driver_config_t gpio1_config = {
        .mode = GPIO_MODE_PP_OUTPUT,
        .pull = GPIO_PULL_NONE,
        .speed = GPIO_SPEED_LEVEL_HIGH,
        .level = GPIO_LEVEL_LOW,
    };

    gpio_driver.init(LED_PIN, &gpio1_config);

#if (DEBUG_USE_SEGGER_RTT == 0)
    usart_driver_config_t uart1_config = {
        .mode = USART_MODE_UART,
        .baudrate = 115200,
        .data_bits = USART_DATA_BITS_8,
        .stop_bits = USART_STOP_BITS_1,
        .parity = USART_PARITY_DISABLE,
        .flow_ctrl = USART_FLOW_CTRL_DISABLE,
        .event_cb = uart1_event_callback,
    };

    usart_driver.init(USART_NUM_1, &uart1_config);
#endif // DEBUG_USE_SEGGER_RTT == 0
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

    // Create the debug thread
    tx_thread_create(&debug_thread, \
                     "Debug Thread", \
                     debug_thread_entry, \
                     0, \
                     debug_thread_stack, \
                     DEBUG_THREAD_STACK_SIZE, \
                     DEBUG_THREAD_PRIORITY, \
                     DEBUG_THREAD_PRIORITY, \
                     TX_NO_TIME_SLICE, \
                     TX_AUTO_START);
}

static void start_thread_entry(ULONG parameter) {
    uint32_t counter = 0;
    // Calculate the CPU usage
    EXECUTION_TIME idle_time = 0;
    EXECUTION_TIME total_time = 0;
    EXECUTION_TIME delta_idle_time = 0;
    EXECUTION_TIME delta_total_time = 0;

    // Setup the application

    // Create the debug printf mutex
    tx_mutex_create(&debug_printf_mutex, "Debug Printf Mutex", TX_NO_INHERIT);

    idle_time = _tx_execution_idle_time_total;
    total_time = _tx_execution_isr_time_total + _tx_execution_thread_time_total + _tx_execution_idle_time_total;

    while (1) {
        counter++;
        if (counter == 200) {
            counter = 0;
            delta_idle_time = _tx_execution_idle_time_total - idle_time;
            delta_total_time = _tx_execution_isr_time_total + _tx_execution_thread_time_total + _tx_execution_idle_time_total - total_time;
            cpu_usage = (double)delta_idle_time / (double)delta_total_time;
            cpu_usage = 100.0 - cpu_usage * 100.0;
            idle_time = _tx_execution_idle_time_total;
            total_time = _tx_execution_isr_time_total + _tx_execution_thread_time_total + _tx_execution_idle_time_total;
        }
        tx_thread_sleep(1);
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

static void debug_thread_entry(ULONG parameter) {
    TX_THREAD *thread_ptr;
    thread_ptr = &start_thread;

    while (1) {
        debug_printf("===================================================================\r\n");
        debug_printf("CPU Usage:                    %5.2f%%\r\n", cpu_usage);
        debug_printf("Thread Execution Time:        %.9fs\r\n", (double)_tx_execution_thread_time_total / SystemCoreClock);
        debug_printf("IDLE Execution Time:          %.9fs\r\n", (double)_tx_execution_idle_time_total / SystemCoreClock);
        debug_printf("ISR Execution Time:           %.9fs\r\n", (double)_tx_execution_isr_time_total / SystemCoreClock);
        debug_printf("System Total Execution Time:  %.9fs\r\n", (double)(_tx_execution_thread_time_total + _tx_execution_idle_time_total + _tx_execution_isr_time_total) / SystemCoreClock);
        debug_printf("===================================================================\r\n");
        debug_printf(" Priority  StackSize  CurStack  MaxStack  ThreadName\r\n");

        while (thread_ptr != (TX_THREAD *)0) {
            debug_printf("   %2d        %5d     %5d    %5d      %s\r\n", \
                            thread_ptr->tx_thread_priority, \
                            thread_ptr->tx_thread_stack_size, \
                            (int)thread_ptr->tx_thread_stack_end - (int)thread_ptr->tx_thread_stack_ptr, \
                            (int)thread_ptr->tx_thread_stack_end - (int)thread_ptr->tx_thread_stack_highest_ptr, \
                            thread_ptr->tx_thread_name);

            thread_ptr = thread_ptr->tx_thread_created_next;
            if (thread_ptr == &start_thread) {
                break;
            }
        }
        tx_thread_sleep(500);
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
        // Do something
    }

    if (event & USART_EVENT_SEND_COMPLETE) {
        // Do something
    }
}

static void debug_printf(const char *fmt, ...) {
    char buffer[200 + 1];
    va_list args;

    va_start(args, fmt);
    (void)vsnprintf((char *)&buffer[0], \
                    (size_t)sizeof(buffer), \
                    (const char *)fmt, \
                    args);
    va_end(args);

    tx_mutex_get(&debug_printf_mutex, TX_WAIT_FOREVER);

    printf("%s", buffer);

    tx_mutex_put(&debug_printf_mutex);
}

/**
 * @brief GCC I/O library putchar function
 * 
 * @param ch 
 * @return int 
 */
int __io_putchar(int ch) {
#if (DEBUG_USE_SEGGER_RTT == 1)
    SEGGER_RTT_Write(0, &ch, 1);
#else
    usart_driver.poll_send(USART_NUM_1, (uint8_t*)&ch, 1, 0x1000);
#endif
    return ch;
}
