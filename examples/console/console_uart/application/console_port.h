/**
  * @file    console_port.h
  * @author  MorroMaker
  * @brief   Header for console_port.c file
  * @attention
  *
  * Copyright (c) 2024 MorroMaker
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
#ifndef CONSOLE_PORT_H
#define CONSOLE_PORT_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "shell.h"
#include "log.h"

short console_shell_write(char *data, unsigned short len);
short console_shell_read(char *data, unsigned short len);
int console_shell_lock(Shell *shell);
int console_shell_unlock(Shell *shell);

int console_log_lock(Log *log);
int console_log_unlock(Log *log);
void console_log_write(char *buffer, short len);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* CONSOLE_PORT_H */
