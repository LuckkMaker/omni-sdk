/**
  * @file    console_port.c
  * @author  MorroMaker
  * @brief   Console port file
  * @attention
  *
  * Copyright (c) 2024 MorroMaker
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
#include "console_port.h"

#include <stdbool.h>
#include "omni.h"
#include "cmsis_os2.h"

extern osMessageQueueId_t uart1_rx_queue_id;
extern uint8_t uart_rx_data;

osMutexId_t console_shell_mutex;
osMutexId_t console_log_mutex;

Shell console_shell = {
    .read = console_shell_read,
    .write = console_shell_write,
    .lock = console_shell_lock,
    .unlock = console_shell_unlock,
};

Log console_log = {
    .write = console_log_write,
    .active = true,
    .level = LOG_DEBUG,
};

/**
  * @brief  Console shell write
  * @param  data
  * @param  len
  * @retval character to be written
  */
short console_shell_write(char *data, unsigned short len) {
    // uart_tx_busy = 1;
    // uart_driver.write(USART_NUM_1, (uint8_t *)data, len);
    // while (uart_tx_busy) {
    //     osDelay(1);
    // }
    usart_driver.poll_send(USART_NUM_1, (uint8_t *)data, len, 0x1FF);

    return len;
}

/**
  * @brief  Console shell read
  * @param  data
  * @param  len
  * @retval read character
  */
short console_shell_read(char *data, unsigned short len) {
    // if (usart_driver.receive(USART_NUM_1, (uint8_t *)data, len) != 0) {
    // // if (uart_driver.poll_read(USART_NUM_1, (uint8_t *)data, len, 0x1FF) != 0) {
    //     return 0;
    // } else {
    //     return 1;
    // }
    if (osMessageQueueGet(uart1_rx_queue_id, &uart_rx_data, NULL, 0x1FF) == osOK) {
        *data = uart_rx_data;
        return 1;
    } else {
        return 0;
    }
}

/**
  * @brief  Console shell lock
  * @param  shell
  * @retval 0
  */
int console_shell_lock(Shell *shell) {
    osMutexAcquire(console_shell_mutex, osWaitForever);
    return 0;
}

/**
  * @brief  Console shell unlock
  * @param  shell
  * @retval 0
  */
int console_shell_unlock(Shell *shell) {
    osMutexRelease(console_shell_mutex);
    return 0;
}

/**
  * @brief  Console log write
  * @param  data
  * @param  len
  * @retval character to be written
  */
void console_log_write(char *buffer, short len) {
#if SHELL_SUPPORT_END_LINE == 1
    if (console_log.shell != NULL) {
        shellWriteEndLine(console_log.shell, buffer, len);
    }
#else
    uart_driver.poll_write(USART_NUM_1, (uint8_t *)buffer, len, 0x1FF);
#endif
}

/**
  * @brief  Console log lock
  * @param  log
  * @retval 0
  */
int console_log_lock(Log *log) {
    osMutexAcquire(console_log_mutex, osWaitForever);
    return 0;
}

/**
  * @brief  Console log unlock
  * @param  log
  * @retval 0
  */
int console_log_unlock(Log *log) {
    osMutexRelease(console_log_mutex);
    return 0;
}
