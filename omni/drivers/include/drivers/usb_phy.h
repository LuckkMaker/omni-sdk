/**
  * @file    usb_phy.h
  * @author  LuckkMaker
  * @brief   USB phy driver for omni
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
#ifndef OMNI_DRIVER_USB_PHY_H
#define OMNI_DRIVER_USB_PHY_H

/* Includes ------------------------------------------------------------------*/
#include "drivers/usb_phy_types.h"
#include "hal/usb_phy_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief USB phy event
 */
#define USB_PHY_EVENT_INITIALIZED           (1 << 0)    /**< Initialized */

/**
 * @brief Event callback function
 */
typedef void (*usb_phy_event_callback)(uint32_t event);

/**
 * @brief USB PHY driver configuration
 */
typedef struct usb_phy_driver_config {
    usb_mode_t mode;                   /**< USB mode */
    usb_phy_event_callback event_cb;   /**< Event callback */
} usb_phy_driver_config_t;

/**
 * @brief USB PHY driver status
 */
typedef struct usb_phy_driver_status {
    uint32_t is_initialized:1;      /**< Initialization status */
} usb_phy_driver_status_t;

/**
 * @brief USB PHY driver error
 */
typedef struct usb_phy_driver_error {
    uint32_t reserved:32;           /**< Reserved */
} usb_phy_driver_error_t;

/**
 * @brief USB PHY object
 */
typedef struct {
    usb_dev_t *dev;
    usb_mode_t mode;
    volatile usb_phy_driver_status_t status;
    usb_phy_driver_error_t error;
    usb_phy_event_callback event_cb;
} usb_phy_obj_t;

/**
 * @brief Initialize USB PHY
 */
typedef int (*usb_phy_init_t)(usb_num_t usb_num, usb_phy_driver_config_t *config);

/**
 * @brief Deinitialize USB PHY
 */
typedef int (*usb_phy_deinit_t)(usb_num_t usb_num);

/**
 * @brief Start USB PHY
 */
typedef void (*usb_phy_start_t)(usb_num_t usb_num);

/**
 * @brief Stop USB PHY
 */
typedef void (*usb_phy_stop_t)(usb_num_t usb_num);

/**
 * @brief Get USB device
 */
typedef usb_dev_t* (*usb_phy_get_dev_t)(usb_num_t usb_num);

/**
 * @brief USB PHY driver API
 */
struct usb_phy_driver_api {
    usb_phy_init_t init;
    usb_phy_deinit_t deinit;
    usb_phy_start_t start;
    usb_phy_stop_t stop;
    usb_phy_get_dev_t get_dev;
};

extern const struct usb_phy_driver_api usb_phy_driver;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* OMNI_DRIVER_USB_PHY_H */
