/**
  * @file    omni_target.h
  * @author  LuckkMaker
  * @brief   Target specific header file
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
#ifndef OMNI_TARGETS_H
#define OMNI_TARGETS_H

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

#include "omni_config.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef const struct gpio_pin {
    GPIO_TypeDef *ins;
    uint32_t index;
    uint32_t alternate;
} gpio_pin_t;

typedef struct gpio_dev {
    GPIO_TypeDef *ins;
    uint32_t pin;
} gpio_dev_t;

#ifdef __cplusplus
}
#endif

#endif /* OMNI_TARGETS_H */
