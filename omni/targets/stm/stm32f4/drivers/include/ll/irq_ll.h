/**
  * @file    irq_ll.h
  * @author  LuckkMaker
  * @brief   Low-level IRQ configuration
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
#ifndef OMNI_LL_IRQ_H
#define OMNI_LL_IRQ_H

/* Includes ------------------------------------------------------------------*/
#include "include/device.h"

#ifdef __cplusplus
extern "C" {
#endif

#if defined(STM32F407xx)
#define CONFIG_IRQ_DEV_NUM 82
#elif defined(STM32F405xx)
#define CONFIG_IRQ_DEV_NUM 82
#elif defined(STM32F411xE)
#define CONFIG_IRQ_DEV_NUM 86
#else
#error "Please select first the target STM32F4xx device used in your application (in stm32f4xx.h file)"
#endif /* STM32F407xx */
#define CONFIG_IRQ_RES_NUM 16

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* OMNI_LL_IRQ_H */
