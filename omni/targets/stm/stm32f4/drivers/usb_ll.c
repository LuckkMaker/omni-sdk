/**
  * @file    usb_ll.c
  * @author  LuckkMaker
  * @brief   Low-level USB configuration
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

/* Includes ------------------------------------------------------------------*/
#include "ll/usb_ll.h"

#if defined(USB_OTG_FS) && (CONFIG_USB_OTG_FS == 1)
static gpio_pin_t otg_fs_dm_pin = { CONFIG_USB_OTG_FS_DM_PORT, CONFIG_USB_OTG_FS_DM_PIN, CONFIG_USB_OTG_FS_DM_AF };
static gpio_pin_t otg_fs_dp_pin = { CONFIG_USB_OTG_FS_DP_PORT, CONFIG_USB_OTG_FS_DP_PIN, CONFIG_USB_OTG_FS_DP_AF };
#if (CONFIG_USB_OTG_FS_VBUS_DEF == 1)
static gpio_pin_t otg_fs_vbus_pin = { CONFIG_USB_OTG_FS_VBUS_PORT, CONFIG_USB_OTG_FS_VBUS_PIN, CONFIG_USB_OTG_FS_VBUS_AF };
#endif /* (CONFIG_USB_OTG_FS_VBUS_DEF == 1) */
#if (CONFIG_USB_OTG_FS_ID_DEF == 1)
static gpio_pin_t otg_fs_id_pin = { CONFIG_USB_OTG_FS_ID_PORT, CONFIG_USB_OTG_FS_ID_PIN, CONFIG_USB_OTG_FS_ID_AF };
#endif /* (CONFIG_USB_OTG_FS_ID_DEF == 1) */
#if (CONFIG_USB_OTG_FS_SOF_DEF == 1)
static gpio_pin_t otg_fs_sof_pin = { CONFIG_USB_OTG_FS_SOF_PORT, CONFIG_USB_OTG_FS_SOF_PIN, CONFIG_USB_OTG_FS_SOF_AF };
#endif /* (CONFIG_USB_OTG_FS_SOF_DEF == 1) */
#if (CONFIG_USB_OTG_FS_DEVICE == 1) && (CONFIG_USB_OTG_FS_HOST == 1)
#error "USB OTG FS can't be both device and host"
#endif /* (CONFIG_USB_OTG_FS_DEVICE == 1) && (CONFIG_USB_OTG_FS_HOST == 1) */
#if (CONFIG_USB_OTG_FS_DEVICE == 1)
static PCD_HandleTypeDef otg_fs_handle = {
    .Instance = USB_OTG_FS,
};
#endif /* CONFIG_USB_OTG_FS_DEVICE */
#if (CONFIG_USB_OTG_FS_HOST == 1)
static HCD_HandleTypeDef otg_fs_handle = {
    .Instance = USB_OTG_FS,
};
#endif /* CONFIG_USB_OTG_FS_HOST */
static usb_dev_t otg_fs_dev = {
#if (CONFIG_USB_OTG_FS_DEVICE == 1)
    .pcd_handle = &otg_fs_handle,
#endif /* CONFIG_USB_OTG_FS_DEVICE */
#if (CONFIG_USB_OTG_FS_HOST == 1)
    .hcd_handle = &otg_fs_handle,
#endif /* CONFIG_USB_OTG_FS_HOST */
    .ins = USB_OTG_FS,
    .irq_num = OTG_FS_IRQn,
    .irq_prio = CONFIG_USB_OTG_FS_IRQ_PRIO,
    .dm_pin = &otg_fs_dm_pin,
    .dp_pin = &otg_fs_dp_pin,
#if (CONFIG_USB_OTG_FS_VBUS_DEF == 1)
    .vbus_pin = &otg_fs_vbus_pin,
#endif /* (CONFIG_USB_OTG_FS_VBUS_DEF == 1) */
#if (CONFIG_USB_OTG_FS_ID_DEF == 1)
    .id_pin = &otg_fs_id_pin,
#endif /* (CONFIG_USB_OTG_FS_ID_DEF == 1) */
#if (CONFIG_USB_OTG_FS_SOF_DEF == 1)
    .sof_pin = &otg_fs_sof_pin,
#endif /* (CONFIG_USB_OTG_FS_SOF_DEF == 1) */
};
#endif /* USB_OTG_FS && (CONFIG_USB_OTG_FS == 1) */

/**
 * @brief Get USB PHY dev information
 * 
 * @param usb_num USB PHY number
 * @return USB PHY dev information
 */
usb_dev_t* usb_ll_get_dev(usb_num_t usb_num) {
    switch (usb_num) {
#if (CONFIG_USB_OTG_FS == 1)
        case USB_NUM_1:
            return &otg_fs_dev;
#endif /* CONFIG_USB_OTG_FS */

        default:
            return NULL;
    }

    return NULL;
}
