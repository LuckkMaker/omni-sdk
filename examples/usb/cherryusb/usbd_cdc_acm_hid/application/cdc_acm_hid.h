/**
  * @file    cdc_acm_hid.h
  * @author  LuckkMaker
  * @brief   Header for cdc_acm_hid.c file
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
#ifndef CDC_ACM_HID_H
#define CDC_ACM_HID_H

/* Includes ------------------------------------------------------------------*/
#include "usbd_core.h"

#ifdef __cplusplus
extern "C" {
#endif

/*!< custom hid report descriptor size */
#define HID_CUSTOM_REPORT_DESC_SIZE 38

extern const uint8_t cdc_acm_hid_descriptor[];
extern const uint8_t hid_custom_report_desc[HID_CUSTOM_REPORT_DESC_SIZE];
extern struct usbd_interface cdc_intf0;
extern struct usbd_interface cdc_intf1;
extern struct usbd_interface hid_intf;
extern struct usbd_endpoint cdc_out_ep;
extern struct usbd_endpoint cdc_in_ep;
extern struct usbd_endpoint custom_hid_in_ep;
extern struct usbd_endpoint custom_hid_out_ep;

int cdc_acm_hid_init(uint8_t busid, uint32_t reg_base);
uint8_t cdc_acm_data_send(uint8_t busid, uint8_t *data, uint32_t len);
void usbd_cdc_get_out_data(uint8_t busid, uint8_t *data, uint32_t len);
void usbd_event_handler(uint8_t busid, uint8_t event);
void cdc_acm_data_send_with_dtr_test(uint8_t busid);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* CDC_ACM_HID_H */
