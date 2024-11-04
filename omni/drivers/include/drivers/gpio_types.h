/**
  * @file    gpio_types.h
  * @author  LuckkMaker
  * @brief   GPIO driver types
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
#ifndef OMNI_DRIVER_GPIO_TYPES_H
#define OMNI_DRIVER_GPIO_TYPES_H

/* Includes ------------------------------------------------------------------*/
#include "include/device.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief GPIO output mode
 */
typedef enum {
    GPIO_MODE_DEFAULT_INPUT = 0x00,
    GPIO_MODE_PP_OUTPUT = 0x01,
    GPIO_MODE_OD_OUTPUT = 0x02,
} gpio_mode_t;

/**
 * @brief GPIO pull
 */
typedef enum {
    GPIO_PULL_NONE = 0x00,
    GPIO_PULL_UP = 0x01,
    GPIO_PULL_DOWN = 0x02,
} gpio_pull_t;

/**
 * @brief GPIO speed
 */
typedef enum {
    GPIO_SPEED_LEVEL_LOW = 0x00,
    GPIO_SPEED_LEVEL_MEDIUM = 0x01,
    GPIO_SPEED_LEVEL_HIGH = 0x02,
    GPIO_SPEED_LEVEL_VERYHIGH = 0x03,
} gpio_speed_t;

/**
 * @brief GPIO level
 */
typedef enum {
    GPIO_LEVEL_LOW = 0x00,
    GPIO_LEVEL_HIGH = 0x01,
} gpio_level_t;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* OMNI_DRIVER_GPIO_TYPES_H */
