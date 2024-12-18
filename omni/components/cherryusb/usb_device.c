/**
  * @file    usb_device.c
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

/* Includes ------------------------------------------------------------------*/
#include "cherryusb/usb_device.h"
#include "hal/irq_hal.h"

extern void USBD_IRQHandler(uint8_t busid);

static int usbd_init(usb_num_t usb_num, usbd_config_t *config);
static int usbd_deinit(usb_num_t usb_num);

const struct usb_device_api usb_device = {
    .init = usbd_init,
    .deinit = usbd_deinit,
};

static void add_endpoint(uint8_t busid, struct usbd_itf *itf);

/**
 * @brief Initialize USB device
 * 
 * @param usb_num USB PHY number
 * @param config Pointer to CherryUSB device configuration structure
 * @return Operation status
 */
static int usbd_init(usb_num_t usb_num, usbd_config_t *config) {
#if defined(CONFIG_CHERRYUSB_DEVICE_MSC)
    uint8_t ep_in_addr;
    uint8_t ep_out_addr;
#endif /* CONFIG_CHERRYUSB_DEVICE_MSC */
    usb_dev_t *usb_dev;

    omni_assert_not_null(config);

    // Initialize USB PHY
    usb_phy_driver_config_t usb_phy_config = {
        .mode = USB_MODE_DEVICE,
        .event_cb = NULL, // When using cherryusb, the USB PHY event callback is not used
    };

    if (usb_phy_driver.init(usb_num, &usb_phy_config) != OMNI_OK) {
        return OMNI_FAIL;
    }

    // Get USB phy device
    usb_dev = usb_phy_driver.get_dev(usb_num);
    if (usb_dev == NULL) {
        usb_phy_driver.deinit(usb_num);
        return OMNI_FAIL;
    }

    /***************** USB device initialization *****************/
    omni_assert_not_null(config->descriptor);
    omni_assert_not_null(config->itf[0]);
    omni_assert_not_null(config->usbd_event_callback);

    usbd_desc_register(config->busid, config->descriptor);

    if (config->bos != NULL) {
        usbd_bos_desc_register(config->busid, config->bos);
    }

#if defined(CONFIG_CHERRYUSB_DEVICE_WINUSB)
    // Register Microsoft OS 2.0 descriptor
    if (config->msosv2 != NULL) {
        usbd_msosv2_desc_register(config->busid, config->msosv2);
    }
#endif /* CONFIG_CHERRYUSB_DEVICE_WINUSB */

    // Register USB interface
    for (uint8_t i = 0; i < USBD_ITF_MAX_NUM; i++) {
        if (config->itf[i] != NULL) {
            if (config->itf[i]->type == USB_ITF_TYPE_CDC) {
#if defined(CONFIG_CHERRYUSB_DEVICE_CDC)
                // Add interface
                usbd_add_interface(config->busid, usbd_cdc_acm_init_intf(config->busid, config->itf[i]->interface));
                // Add endpoints
                add_endpoint(config->busid, config->itf[i]);
#endif /* CONFIG_CHERRYUSB_DEVICE_CDC */
            } else if (config->itf[i]->type == USB_ITF_TYPE_HID) {
#if defined(CONFIG_CHERRYUSB_DEVICE_HID)
                omni_assert_not_null(config->hid_report_desc);
                // Add interface
                usbd_add_interface(config->busid, usbd_hid_init_intf(config->busid, \
                                                                     config->itf[i]->interface, \
                                                                     config->hid_report_desc, \
                                                                     config->hid_report_desc_size));
                // Add endpoints
                add_endpoint(config->busid, config->itf[i]);
#endif /* CONFIG_CHERRYUSB_DEVICE_HID */
            } else if (config->itf[i]->type == USB_ITF_TYPE_MSC) {
#if defined(CONFIG_CHERRYUSB_DEVICE_MSC)
                for (uint8_t j = 0; j < config->itf[i]->ep_num_max; j++) {
                    if (config->itf[i]->ep[j]->ep_addr & 0x80) {
                        ep_in_addr = config->itf[i]->ep[j]->ep_addr;
                    } else {
                        ep_out_addr = config->itf[i]->ep[j]->ep_addr;
                    }
                }
                // Add interface and endpoints
                usbd_add_interface(config->busid, usbd_msc_init_intf(config->busid, \
                                                                     config->itf[i]->interface, \
                                                                     ep_out_addr, \
                                                                     ep_in_addr));
#endif /* CONFIG_CHERRYUSB_DEVICE_MSC */
            } else {
                // Add interface
                usbd_add_interface(config->busid, config->itf[i]->interface);
                // Add endpoints
                add_endpoint(config->busid, config->itf[i]);
            }
        }
    }

    // Register USB event callback and initialize USB device
    if (usbd_initialize(config->busid, (uint32_t)usb_dev->ins, config->usbd_event_callback) != 0U) {
        usb_phy_driver.deinit(usb_num);
        return OMNI_FAIL;
    }

    return OMNI_OK;
}

/**
 * @brief Deinitialize USB device
 * 
 * @param usb_num USB PHY number
 * @return Operation status
 */
static int usbd_deinit(usb_num_t usb_num) {
    // TODO: Implement USB device close function
    return OMNI_OK;
}

/********************* IRQ handlers **********************/

void usbd_fs_irq_handler(void) {
    USBD_IRQHandler(0);
    // TODO: Using Configuration Wizard to determine the number of USB PHY
}

void usbd_hs_irq_handler(void) {
    USBD_IRQHandler(1);
}

/**
 * @brief Add USB endpoint
 * 
 * @param busid USB bus ID
 * @param itf Pointer to USB interface
 */
static void add_endpoint(uint8_t busid, struct usbd_itf *itf) {
    for (uint8_t i = 0; i < itf->ep_num_max; i++) {
        usbd_add_endpoint(busid, itf->ep[i]);
    }
}
