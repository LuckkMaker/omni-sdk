/**
  * @file    msc_ram.h
  * @author  LuckkMaker
  * @brief   Header for msc_ram.c file
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
#ifndef MSC_RAM_H
#define MSC_RAM_H

/* Includes ------------------------------------------------------------------*/
#include "usbd_core.h"

#ifdef __cplusplus
extern "C" {
#endif

extern const uint8_t msc_ram_descriptor[];
extern struct usbd_interface msc_intf0;
extern struct usbd_endpoint msc_out_ep;
extern struct usbd_endpoint msc_in_ep;

int msc_ram_init(uint8_t busid, uint32_t reg_base);
void usbd_event_handler(uint8_t busid, uint8_t event);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MSC_RAM_H */
