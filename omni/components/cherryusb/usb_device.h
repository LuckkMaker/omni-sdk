/**
  * @file    usb_device.h
  * @author  LuckkMaker
  * @brief   Cherryusb device component for omni
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
#ifndef COMPONENT_CHERRYUSB_USB_DEVICE_H
#define COMPONENT_CHERRYUSB_USB_DEVICE_H

/* Includes ------------------------------------------------------------------*/
#include "drivers/usb_phy.h"
#include "usbd_core.h"

#if defined(CONFIG_CHERRYUSB_DEVICE_CDC)
#include "usbd_cdc.h"
#endif /* CONFIG_CHERRYUSB_DEVICE_CDC */

#if defined(CONFIG_CHERRYUSB_DEVICE_HID)
#include "usbd_hid.h"
#endif /* CONFIG_CHERRYUSB_DEVICE_HID */

#if defined(CONFIG_CHERRYUSB_DEVICE_MSC)
#include "usbd_msc.h"
#endif /* CONFIG_CHERRYUSB_DEVICE_MSC */

#if defined(CONFIG_CHERRYUSB_DEVICE_DFU)
#include "usbd_dfu.h"
#endif /* CONFIG_CHERRYUSB_DEVICE_DFU */

#ifdef __cplusplus
extern "C" {
#endif

#define USBD_ITF_MAX_NUM    8
#define USBD_EP_MAX_NUM     CONFIG_USBDEV_EP_NUM

/**
 * @brief USB device interface type
 */
typedef enum {
    USB_ITF_TYPE_CDC = 0x01,
    USB_ITF_TYPE_HID = 0x02,
    USB_ITF_TYPE_MSC = 0x03,
    USB_ITF_TYPE_WINUSB = 0x04,
    USB_ITF_TYPE_DFU = 0x05,
    USB_ITF_TYPE_CUSTOM = 0xFF,
} usbd_itf_type_t;

/**
 * @brief USB device interface
 */
typedef struct usbd_itf {
    usbd_itf_type_t type;
    struct usbd_interface *interface;
    uint8_t ep_num_max;
    struct usbd_endpoint *ep[USBD_EP_MAX_NUM];
} usbd_itf_t;

/**
 * @brief Cherryusb device component configuration
 */
typedef struct usbd_config {
    uint8_t busid;
    const uint8_t *descriptor;
    struct usb_bos_descriptor *bos;
#if defined(CONFIG_CHERRYUSB_DEVICE_HID)
    const uint8_t *hid_report_desc;                 // HID report descriptor
    uint32_t hid_report_desc_size;                  // HID report descriptor size
#endif /* CONFIG_CHERRYUSB_DEVICE_HID */
#if defined(CONFIG_CHERRYUSB_DEVICE_WINUSB)
    struct usb_msosv2_descriptor *msosv2;           // Microsoft OS 2.0 descriptor
#endif /* CONFIG_CHERRYUSB_DEVICE_WINUSB */
    struct usbd_itf *itf[USBD_ITF_MAX_NUM];         // USB interface
    void (*usbd_event_callback)(uint8_t busid, uint8_t event);
} usbd_config_t;

/**
 * @brief Initialize usb device
 */
typedef int (*usbd_init_t)(usb_num_t usb_num, usbd_config_t *config);

/**
 * @brief Deinitialize usb device
 */
typedef int (*usbd_deinit_t)(usb_num_t usb_num);

/**
 * @brief USB device component API
 */
struct usb_device_api {
    usbd_init_t init;
    usbd_deinit_t deinit;
};

extern const struct usb_device_api usb_device;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* COMPONENT_CHERRYUSB_USB_DEVICE_H */
