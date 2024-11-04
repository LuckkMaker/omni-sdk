/**
  * @file    device.h
  * @author  LuckkMaker
  * @brief   Device header file
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
#ifndef OMNI_INC_DEVICE_H
#define OMNI_INC_DEVICE_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>

#include "include/toolchain.h"
#include "include/util.h"
#include "include/assert.h"
#include "omni_config.h"
#if defined(CONFIG_OMNI_DRIVER)
#include "omni_device_cfg.h"
#endif /* CONFIG_OMNI_DRIVER */
#include "omni_target.h"

#ifdef __cplusplus
extern "C" {
#endif

/* OMNI status */
#define OMNI_OK 0
#define OMNI_BUSY 1
#define OMNI_TIMEOUT 2
#define OMNI_FAIL -1

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* OMNI_INC_DEVICE_H */
