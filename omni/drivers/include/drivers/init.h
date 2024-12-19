/**
  * @file    init.h
  * @author  LuckkMaker
  * @brief   Header for init.c file
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
#ifndef OMNI_DRIVER_INIT_H
#define OMNI_DRIVER_INIT_H

/* Includes ------------------------------------------------------------------*/
#include "include/device.h"

#ifdef __cplusplus
extern "C" {
#endif

void driver_init(void);

void interrupt_init(void);
void device_init(void);
void power_init(void);
void watchdog_init(void);
void error_handler(char *file, uint32_t line);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* OMNI_DRIVER_INIT_H */
