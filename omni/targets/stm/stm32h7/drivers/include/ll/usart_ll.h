/**
  * @file    usart_ll.h
  * @author  LuckkMaker
  * @brief   Low-level USART configuration
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
#ifndef OMNI_LL_USART_H
#define OMNI_LL_USART_H

/* Includes ------------------------------------------------------------------*/
#include "drivers/usart_types.h"

#ifdef __cplusplus
extern "C" {
#endif

usart_dev_t* usart_ll_get_dev(usart_num_t usart_num) ;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* OMNI_LL_USART_H */
