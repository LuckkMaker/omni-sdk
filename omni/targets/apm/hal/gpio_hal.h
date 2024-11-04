/**
  * @file    gpio_hal.h
  * @author  LuckkMaker
  * @brief   Header file of gpio_hal.c
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
#ifndef OMNI_HAL_GPIO_H
#define OMNI_HAL_GPIO_H

/* Includes ------------------------------------------------------------------*/
#include "include/device.h"

#ifdef __cplusplus
extern "C" {
#endif

#define APM32_PORT(port)    GPIO##port##_BASE
#define GET_PIN(PORT, PIN)  ((16 * ( (APM32_PORT(PORT) - GPIOA_BASE) / (0x0400UL) )) + PIN)

void gpio_hal_enable_clock(GPIO_TypeDef *GPIOx);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* OMNI_HAL_GPIO_H */
