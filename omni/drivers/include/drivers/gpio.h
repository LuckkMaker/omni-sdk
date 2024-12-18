/**
  * @file    gpio.h
  * @author  LuckkMaker
  * @brief   GPIO driver for omni
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
#ifndef OMNI_DRIVER_GPIO_H
#define OMNI_DRIVER_GPIO_H

/* Includes ------------------------------------------------------------------*/
#include "drivers/gpio_types.h"
#include "hal/gpio_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief GPIO driver configuration
 */
typedef struct gpio_driver_config {
    gpio_mode_t mode;       /**< GPIO mode */
    gpio_pull_t pull;       /**< GPIO pull */
    gpio_speed_t speed;     /**< GPIO speed */
    gpio_level_t level;     /**< GPIO level */
} gpio_driver_config_t;

/**
 * @brief Initialize GPIO
 */
typedef int (*gpio_init_t)(uint32_t gpio_num, gpio_driver_config_t *config);

/**
 * @brief Deinitialize GPIO
 */
typedef int (*gpio_deinit_t)(uint32_t gpio_num);

/**
 * @brief Set GPIO level
 */
typedef int (*gpio_set_level_t)(uint32_t gpio_num, uint32_t level);

/**
 * @brief Get GPIO level
 */
typedef uint32_t (*gpio_get_level_t)(uint32_t gpio_num);

/**
 * @brief Toggle GPIO level
 */
typedef int (*gpio_toggle_t)(uint32_t gpio_num);

/**
 * @brief GPIO driver API
 */
struct gpio_driver_api {
    gpio_init_t init;
    gpio_deinit_t deinit;
    gpio_set_level_t set_level;
    gpio_get_level_t get_level;
    gpio_toggle_t toggle;
};

extern const struct gpio_driver_api gpio_driver;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* OMNI_DRIVER_GPIO_H */
