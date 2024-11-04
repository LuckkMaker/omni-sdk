/**
  * @file    app.h
  * @author  LuckkMaker
  * @brief   Header for app.c file.
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
#ifndef APP_H
#define APP_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stddef.h>

/* Exported defines ----------------------------------------------------------*/

/* Application version */
#define APP_VER_MAJOR                               0
#define APP_VER_MINOR                               1
#define APP_VER_PATCH                               0
#define APP_VER                                     (APP_VER_MAJOR * 10000 + APP_VER_MINOR * 100 + APP_VER_PATCH)
#define APP_STR(x)                                  #x
#define APP_PROJECT_VERSION(major, minor, patch)    "v" APP_STR(major, minor, patch)

void setup(void);
void app(void);

#ifdef __cplusplus
}
#endif

#endif /* APP_H */
