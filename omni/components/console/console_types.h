/**
  * @file    console_types.h
  * @author  LuckkMaker
  * @brief   Console component types
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
#ifndef COMPONENT_CONSOLE_TYPES_H
#define COMPONENT_CONSOLE_TYPES_H

/* Includes ------------------------------------------------------------------*/
#include "include/device.h"

#include "libraries/letter_shell/include/shell.h"
#include "libraries/letter_shell/extensions/log/log.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef Shell console_shell_t;
typedef Log console_log_t;
typedef LogLevel console_log_level_t;

typedef struct console_dev {
    console_shell_t *shell;
    console_log_t *log;
} console_dev_t;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* COMPONENT_CONSOLE_TYPES_H */
