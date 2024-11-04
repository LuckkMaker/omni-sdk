/**
  * @file    usb_phy_hal.c
  * @author  LuckkMaker
  * @brief   USB PHY driver
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
#include "drivers/usb_phy.h"
#include "hal/gpio_hal.h"
#include "hal/irq_hal.h"
#include "ll/usb_ll.h"

static usb_phy_obj_t usb_phy_obj[USB_NUM_MAX];

static int usb_phy_open(usb_num_t usb_num, usb_phy_driver_config_t *config);
static int usb_phy_close(usb_num_t usb_num);
static void usb_phy_start(usb_num_t usb_num);
static void usb_phy_stop(usb_num_t usb_num);
static usb_dev_t* usb_phy_get_dev(usb_num_t usb_num);

const struct usb_phy_driver_api usb_phy_driver = {
    .open = usb_phy_open,
    .close = usb_phy_close,
    // .start = usb_phy_start,
    // .stop = usb_phy_stop,
    .get_dev = usb_phy_get_dev,
};

static void usb_phy_hal_irq_register(void);
static void usb_phy_hal_set_gpio(usb_dev_t *dev);
static void usb_phy_hal_reset_gpio(usb_dev_t *dev);
static void usb_phy_hal_enable_clock(usb_num_t usb_num);
static void usb_phy_hal_reset_clock(usb_num_t usb_num);

/**
 * @brief Open USB PHY
 * 
 * @param usb_num USB PHY number
 * @param config Pointer to USB PHY driver configuration structure
 * @return Operation status
 */
static int usb_phy_open(usb_num_t usb_num, usb_phy_driver_config_t *config) {
    omni_assert(usb_num < USB_NUM_MAX);
    omni_assert_not_null(config);

    usb_phy_obj_t *obj = &usb_phy_obj[usb_num];

    // Set event callback
    if (config->event_cb != NULL) {
        obj->event_cb = config->event_cb;
    } else {
        obj->event_cb = NULL;
    }

    // Get dev information
    obj->dev = usb_ll_get_dev(usb_num);
    omni_assert_not_null(obj->dev);

    // Clear status
    obj->status = (usb_phy_driver_status_t){0};

    // Clear error
    obj->error = (usb_phy_driver_error_t){0};

    // Register IRQ
    usb_phy_hal_irq_register();

    // Enable USB PHY clock
    usb_phy_hal_enable_clock(usb_num);

    // Initialize GPIO
#if (CONFIG_USB_OTG_FS == 1) || (CONFIG_USB_OTG_HS == 1)
    usb_phy_hal_set_gpio(obj->dev);
#endif /* CONFIG_USB_OTG_FS || CONFIG_USB_OTG_HS */

    // Initialize DMA
    // Initialize IRQ
    NVIC_ClearPendingIRQ(obj->dev->irq_num);
    NVIC_SetPriority(obj->dev->irq_num, \
                    NVIC_EncodePriority(NVIC_GetPriorityGrouping(), obj->dev->irq_prio, 0));
    NVIC_EnableIRQ(obj->dev->irq_num);

    // Initialize USB PHY
    // Note: The initialization of the USB PHY is done in the cherryusb component

    // Set initialized status
    obj->status.is_initialized = 1;
    // Call event callback
    if (obj->event_cb != NULL) {
        // Set initialized event
        obj->event_cb(USB_PHY_EVENT_INITIALIZED);
    }

    return OMNI_OK;
}

/**
 * @brief Close USB PHY
 * 
 * @param usb_num USB PHY number
 * @return Operation status
 */
static int usb_phy_close(usb_num_t usb_num) {
    omni_assert(usb_num < USB_NUM_MAX);

    usb_phy_obj_t *obj = &usb_phy_obj[usb_num];
    omni_assert_not_null(obj);

    // Reset USB PHY clock
    usb_phy_hal_reset_clock(usb_num);

    // Reset GPIO
#if (CONFIG_USB_OTG_FS == 1) || (CONFIG_USB_OTG_HS == 1)
    usb_phy_hal_reset_gpio(obj->dev);
#endif /* CONFIG_USB_OTG_FS || CONFIG_USB_OTG_HS */

    // Disable IRQ
    NVIC_DisableIRQ(obj->dev->irq_num);

    // Clear object
    if (obj->dev != NULL) {
        obj->dev = NULL;
    }

    if (obj->event_cb != NULL) {
        obj->event_cb = NULL;
    }

    usb_phy_obj[usb_num] = (usb_phy_obj_t){0};

    return OMNI_OK;
}

/**
 * @brief Start USB PHY
 * 
 * @param usb_num USB PHY number
 */
static void usb_phy_start(usb_num_t usb_num) {
    UNUSED(usb_num);

    // Start USB PHY
    // Note: The start of the USB PHY is done in the cherryusb component
}

/**
 * @brief Stop USB PHY
 * 
 * @param usb_num USB PHY number
 */
static void usb_phy_stop(usb_num_t usb_num) {
    UNUSED(usb_num);

    // Stop USB PHY
    // Note: The stop of the USB PHY is done in the cherryusb component
}

/**
 * @brief Get USB PHY device information
 * 
 * @param usb_num USB PHY number
 * @return Pointer to USB PHY device information
 */
static usb_dev_t* usb_phy_get_dev(usb_num_t usb_num) {
    omni_assert(usb_num < USB_NUM_MAX);
    if (usb_phy_obj[usb_num].dev != NULL) {
        return usb_phy_obj[usb_num].dev;
    }

    return NULL;
}

/********************* IRQ handlers **********************/
#if (CONFIG_USB_DEVICE == 1)
/**
 * @brief USB IRQ handler
 */
__weak void usbd_irq_handler(void) {
    // When the IRQ handler is needed, it could be implemented in the user file
}
#endif /* CONFIG_USB_DEVICE */
#if (CONFIG_USB_OTG_FS == 1)
/**
 * @brief USB OTG FS IRQ handler
 */
__weak void usbd_fs_irq_handler(void) {
    // When the IRQ handler is needed, it could be implemented in the user file
}
#endif /* CONFIG_USB_OTG_FS */
#if (CONFIG_USB_OTG_HS == 1)
/**
 * @brief USB OTG HS IRQ handler
 */
__weak void usbd_hs_irq_handler(void) {
    // When the IRQ handler is needed, it could be implemented in the user file
}
#endif /* CONFIG_USB_OTG_HS */

/**
 * @brief Register USB PHY IRQ
 */
static void usb_phy_hal_irq_register(void) {
#if (CONFIG_USB_DEVICE == 1)
    irq_hal_register_handler(usb_phy_obj[USB_PHY_DEVICE].dev->irq_num, \
                                usbd_irq_handler);
#endif /* CONFIG_USB_DEVICE == 1 */
#if (CONFIG_USB_OTG_FS == 1)
    irq_hal_register_handler(usb_phy_obj[USB_PHY_OTG_FS].dev->irq_num, \
                                usbd_fs_irq_handler);
#endif /* CONFIG_USB_OTG_FS == 1 */
#if (CONFIG_USB_OTG_HS == 1)
    irq_hal_register_handler(usb_phy_obj[USB_PHY_OTG_HS].dev->irq_num, \
                                usbd_hs_irq_handler);
#endif /* CONFIG_USB_OTG_HS == 1 */
}

/********************* HAL functions **********************/

/**
 * @brief Set GPIO for USB PHY
 * 
 * @param dev USB PHY device information
 */
static void usb_phy_hal_set_gpio(usb_dev_t *dev) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // Enable GPIO clock
    if (dev->dm_pin != NULL) {
        gpio_hal_enable_clock(dev->dm_pin->ins);
    }
    if (dev->dp_pin != NULL) {
        gpio_hal_enable_clock(dev->dp_pin->ins);
    }
    if (dev->vbus_pin != NULL) {
        gpio_hal_enable_clock(dev->vbus_pin->ins);
    }
    if (dev->id_pin != NULL) {
        gpio_hal_enable_clock(dev->id_pin->ins);
    }
    if (dev->sof_pin != NULL) {
        gpio_hal_enable_clock(dev->sof_pin->ins);
    }

    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;

    if (dev->dm_pin != NULL) {
        GPIO_InitStruct.Pin = dev->dm_pin->index;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Alternate = dev->dm_pin->alternate;
        HAL_GPIO_Init(dev->dm_pin->ins, &GPIO_InitStruct);
    }

    if (dev->dp_pin != NULL) {
        GPIO_InitStruct.Pin = dev->dp_pin->index;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Alternate = dev->dp_pin->alternate;
        HAL_GPIO_Init(dev->dp_pin->ins, &GPIO_InitStruct);
    }

    if (dev->vbus_pin != NULL) {
        GPIO_InitStruct.Pin = dev->vbus_pin->index;
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        HAL_GPIO_Init(dev->vbus_pin->ins, &GPIO_InitStruct);
    }

    if (dev->id_pin != NULL) {
        GPIO_InitStruct.Pin = dev->id_pin->index;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        HAL_GPIO_Init(dev->id_pin->ins, &GPIO_InitStruct);
    }

    if (dev->sof_pin != NULL) {
        GPIO_InitStruct.Pin = dev->sof_pin->index;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        HAL_GPIO_Init(dev->sof_pin->ins, &GPIO_InitStruct);
    }
}

/**
 * @brief Reset GPIO for USB PHY
 * 
 * @param dev USB PHY device information
 */
static void usb_phy_hal_reset_gpio(usb_dev_t *dev) {
    if (dev->dm_pin != NULL) {
        HAL_GPIO_DeInit(dev->dm_pin->ins, dev->dm_pin->index);
    }
    if (dev->dp_pin != NULL) {
        HAL_GPIO_DeInit(dev->dp_pin->ins, dev->dp_pin->index);
    }
    if (dev->vbus_pin != NULL) {
        HAL_GPIO_DeInit(dev->vbus_pin->ins, dev->vbus_pin->index);
    }
    if (dev->id_pin != NULL) {
        HAL_GPIO_DeInit(dev->id_pin->ins, dev->id_pin->index);
    }
    if (dev->sof_pin != NULL) {
        HAL_GPIO_DeInit(dev->sof_pin->ins, dev->sof_pin->index);
    }
}

/**
 * @brief Enable USB PHY clock
 * 
 * @param usb_num USB PHY number
 */
static void usb_phy_hal_enable_clock(usb_num_t usb_num) {
    switch (usb_num) {
#if defined(USB) && (CONFIG_USB_DEVICE == 1)
        case USB_NUM_0:
            __HAL_RCC_USB_CLK_ENABLE();
            break;
#endif /* USB && (CONFIG_USB_DEVICE == 1) */
#if defined(USB_OTG_FS) && (CONFIG_USB_OTG_FS == 1)
        case USB_NUM_1:
            __HAL_RCC_USB_OTG_FS_CLK_ENABLE();
            break;
#endif /* USB_OTG_FS && (CONFIG_USB_OTG_FS == 1) */

#if defined(USB_OTG_HS) && (CONFIG_USB_OTG_HS == 1)
        case USB_NUM_2:
            __USB_OTG_HS_CLK_ENABLE();
            break;
#endif /* USB_OTG_HS && (CONFIG_USB_OTG_HS == 1) */

        default:
            break;
    }
}

/**
 * @brief Reset USB PHY clock
 * 
 * @param usb_num USB PHY number
 */
static void usb_phy_hal_reset_clock(usb_num_t usb_num) {
    switch (usb_num) {
#if defined(USB) && (CONFIG_USB_DEVICE == 1)
        case USB_NUM_0:
            __HAL_RCC_USB_FORCE_RESET();
            __HAL_RCC_USB_RELEASE_RESET();
            break;
#endif /* USB && (CONFIG_USB_DEVICE == 1) */
#if defined(USB_OTG_FS) && (CONFIG_USB_OTG_FS == 1)
        case USB_NUM_1:
            __HAL_RCC_USB_OTG_FS_FORCE_RESET();
            __HAL_RCC_USB_OTG_FS_RELEASE_RESET();
            break;
#endif /* USB_OTG_FS && (CONFIG_USB_OTG_FS == 1) */

#if defined(USB_OTG_HS) && (CONFIG_USB_OTG_HS == 1)
        case USB_NUM_2:
            __HAL_RCC_USB_OTG_HS_FORCE_RESET();
            __HAL_RCC_USB_OTG_HS_RELEASE_RESET();
            break;
#endif /* USB_OTG_HS && (CONFIG_USB_OTG_HS == 1) */

        default:
            break;
    }
}
