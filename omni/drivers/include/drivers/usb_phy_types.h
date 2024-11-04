/**
  * @file    usb_phy_types.h
  * @author  LuckkMaker
  * @brief   USB PHY drivers types
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
#ifndef OMNI_DRIVER_USB_PHY_TYPES_H
#define OMNI_DRIVER_USB_PHY_TYPES_H

/* Includes ------------------------------------------------------------------*/
#include "include/device.h"

#ifdef __cplusplus
extern "C" {
#endif

#if (CONFIG_USB_DEVICE == 0) && \
    (CONFIG_USB_OTG_FS == 0) && \
    (CONFIG_USB_OTG_HS == 0)
#error "Please enable USB instance in application 'omni_device_cfg.h' file"
#endif

/**
 * @brief USB mode
 */
typedef enum {
    USB_MODE_DEVICE = 0x00,
#if (CONFIG_USB_OTG_FS == 1) || (CONFIG_USB_OTG_HS == 1)
    USB_MODE_HOST = 0x01,
    USB_MODE_OTG = 0x02,
#endif /* (CONFIG_USB_OTG_FS == 1) || (CONFIG_USB_OTG_HS == 1) */
    USB_MODE_MAX,
} usb_mode_t;

/**
 * @brief USB PHY type
 */
typedef enum {
    USB_PHY_TYPE_INT = 0x00,
    USB_PHY_TYPE_EXT = 0x01,
} usb_phy_type_t;

/**
 * @brief USB PHY speed
 */
typedef enum {
    USB_PHY_SPEED_LOW = 0x00,
    USB_PHY_SPEED_FULL = 0x01,
#if (CONFIG_USB_OTG_HS == 1)
    USB_PHY_SPEED_HIGH = 0x02,
#endif /* (CONFIG_USB_OTG_HS == 1) */
} usb_phy_speed_t;

/**
 * @brief USB PHY device
 */
typedef enum {
#if (CONFIG_USB_DEVICE == 1)
    USB_PHY_DEVICE = 0x00,
#endif /* (CONFIG_USB_DEVICE == 1) */
#if (CONFIG_USB_OTG_FS == 1)
    USB_PHY_OTG_FS,
#endif /* (CONFIG_USB_OTG_FS == 1) */
#if (CONFIG_USB_OTG_HS == 1)
    USB_PHY_OTG_HS,
#endif /* (CONFIG_USB_OTG_HS == 1) */
    USB_PHY_MAX,
} usb_phy_t;

/**
 * @brief USB device number
 */
typedef enum {
#if (CONFIG_USB_DEVICE == 1) || (CONFIG_USB_OTG_FS == 1)
    USB_NUM_1 = 0x00,
#endif /* (CONFIG_USB_DEVICE == 1) || (CONFIG_USB_OTG_FS == 1) */
#if (CONFIG_USB_OTG_HS == 1)
    USB_NUM_2,
#endif /* (CONFIG_USB_OTG_HS == 1) */
    USB_NUM_MAX,
} usb_num_t;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* OMNI_DRIVER_USB_PHY_TYPES_H */
