/**
  * @file    dwt_hal.h
  * @author  LuckkMaker
  * @brief   Header for dwt_hal.c file
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
#ifndef OMNI_HAL_DWT_H
#define OMNI_HAL_DWT_H

/* Includes ------------------------------------------------------------------*/
#include "include/device.h"

#ifdef __cplusplus
extern "C" {
#endif

int dwt_hal_init(void);
int dwt_hal_deinit(void);
void dwt_hal_delay_us(uint32_t us);
void dwt_hal_delay_ms(uint32_t ms);
uint32_t dwt_hal_get_tick(uint32_t frequency);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* OMNI_HAL_DWT_H */
