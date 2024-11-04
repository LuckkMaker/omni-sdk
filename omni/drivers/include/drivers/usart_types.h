/**
  * @file    usart_types.h
  * @author  LuckkMaker
  * @brief   USART driver types
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef OMNI_DRIVER_USART_TYPES_H
#define OMNI_DRIVER_USART_TYPES_H

/* Includes ------------------------------------------------------------------*/
#include "include/device.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief USART mode
 */
typedef enum {
    USART_MODE_UART = 0x00,
} usart_mode_t;

/**
 * @brief USART data bits
 */
typedef enum {
    USART_DATA_BITS_8 = 0x00,
    USART_DATA_BITS_9 = 0x01,
} usart_data_bits_t;

/**
 * @brief USART stop bits
 */
typedef enum {
    USART_STOP_BITS_0_5 = 0x00,
    USART_STOP_BITS_1 = 0x01,
    USART_STOP_BITS_1_5 = 0x02,
    USART_STOP_BITS_2 = 0x03,
} usart_stop_bits_t;

/**
 * @brief USART parity
 */
typedef enum {
    USART_PARITY_DISABLE = 0x00,
    USART_PARITY_TYPE_EVEN = 0x01,
    USART_PARITY_TYPE_ODD = 0x02,
} usart_parity_t;

/**
 * @brief USART flow control
 */
typedef enum {
    USART_FLOW_CTRL_DISABLE = 0x00,
    USART_FLOW_CTRL_RTS = 0x01,
    USART_FLOW_CTRL_CTS = 0x02,
    USART_FLOW_CTRL_RTS_CTS = 0x03,
} usart_flow_ctrl_t;

/**
 * @brief USART port number
 */
typedef enum {
#if (CONFIG_USART_NUM_1 == 1)
    USART_NUM_1 = 0x00,
#endif /* (CONFIG_USART_NUM_1 == 1) */
#if (CONFIG_USART_NUM_2 == 1)
    USART_NUM_2,
#endif /* (CONFIG_USART_NUM_2 == 1) */
#if (CONFIG_USART_NUM_3 == 1)
    USART_NUM_3,
#endif /* (CONFIG_USART_NUM_3 == 1) */
#if (CONFIG_USART_NUM_4 == 1)
    USART_NUM_4,
#endif /* (CONFIG_USART_NUM_4 == 1) */
#if (CONFIG_USART_NUM_5 == 1)
    USART_NUM_5,
#endif /* (CONFIG_USART_NUM_5 == 1) */
#if (CONFIG_USART_NUM_6 == 1)
    USART_NUM_6,
#endif /* (CONFIG_USART_NUM_6 == 1) */
#if (CONFIG_USART_NUM_7 == 1)
    USART_NUM_7,
#endif /* (CONFIG_USART_NUM_7 == 1) */
#if (CONFIG_USART_NUM_8 == 1)
    USART_NUM_8,
#endif /* (CONFIG_USART_NUM_8 == 1) */
#if (CONFIG_USART_NUM_9 == 1)
    USART_NUM_9,
#endif /* (CONFIG_USART_NUM_9 == 1) */
#if (CONFIG_USART_NUM_10 == 1)
    USART_NUM_10,
#endif /* (CONFIG_USART_NUM_10 == 1) */
    USART_NUM_MAX,
} usart_num_t;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* OMNI_DRIVER_USART_TYPES_H */
