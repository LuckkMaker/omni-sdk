/**
  * @file    winusb2_cdc.h
  * @author  LuckkMaker
  * @brief   Header for winusb2_cdc.c file
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
#ifndef WINUSB2_CDC_H
#define WINUSB2_CDC_H

/* Includes ------------------------------------------------------------------*/
#include "usbd_core.h"

#ifdef __cplusplus
extern "C" {
#endif

extern const uint8_t winusbv2_descriptor[];
extern struct usb_bos_descriptor bos_desc;
extern struct usb_msosv2_descriptor msosv2_desc;
extern struct usbd_interface winusb_intf;
extern struct usbd_interface cdc_intf1;
extern struct usbd_interface cdc_intf2;
extern struct usbd_endpoint winusb_out_ep1;
extern struct usbd_endpoint winusb_in_ep1;
extern struct usbd_endpoint cdc_out_ep;
extern struct usbd_endpoint cdc_in_ep;

int winusbv2_init(uint8_t busid, uint32_t reg_base);
void usbd_event_handler(uint8_t busid, uint8_t event);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* WINUSB2_CDC_H */
