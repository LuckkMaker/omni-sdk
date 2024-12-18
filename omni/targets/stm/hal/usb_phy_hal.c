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

static int usb_phy_hal_init(usb_num_t usb_num, usb_phy_driver_config_t *config);
static int usb_phy_hal_deinit(usb_num_t usb_num);
static void usb_phy_hal_start(usb_num_t usb_num);
static void usb_phy_hal_stop(usb_num_t usb_num);
static usb_dev_t* usb_phy_hal_get_dev(usb_num_t usb_num);

const struct usb_phy_driver_api usb_phy_driver = {
    .init = usb_phy_hal_init,
    .deinit = usb_phy_hal_deinit,
    .start = usb_phy_hal_start,
    .stop = usb_phy_hal_stop,
    .get_dev = usb_phy_hal_get_dev,
};

static int usb_phy_hal_set_device(usb_dev_t *dev);
static int usb_phy_hal_set_host(usb_dev_t *dev);
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
static int usb_phy_hal_init(usb_num_t usb_num, usb_phy_driver_config_t *config) {
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

#if defined(CONFIG_SOC_FAMILY_STM32H7XX)
    RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USB;
    PeriphClkInitStruct.UsbClockSelection = RCC_USBCLKSOURCE_HSI48;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK) {
        return OMNI_FAIL;
    }

    HAL_PWREx_EnableUSBVoltageDetector();
#endif /* CONFIG_SOC_FAMILY_STM32H7XX */

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
#if (CONFIG_USB_USBX == 1)
    if (obj->mode == USB_MODE_DEVICE) {
        if (usb_phy_set_device(obj->dev) != OMNI_OK) {
            return OMNI_FAIL;
        }
    } else if (obj->mode == USB_MODE_HOST) {
        if (usb_phy_set_host(obj->dev) != OMNI_OK) {
            return OMNI_FAIL;
        }
    }
#endif /* CONFIG_USB_USBX */

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
static int usb_phy_hal_deinit(usb_num_t usb_num) {
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
static void usb_phy_hal_start(usb_num_t usb_num) {
    omni_assert(usb_num < USB_NUM_MAX);

    usb_phy_obj_t *obj = &usb_phy_obj[usb_num];
    omni_assert_not_null(obj);

    // Start USB PHY
#if (CONFIG_USB_OTG_FS_DEVICE == 1) || (CONFIG_USB_OTG_HS_DEVICE == 1)
    HAL_PCD_Start(obj->dev->pcd_handle);
#endif /* CONFIG_USB_OTG_FS_DEVICE || CONFIG_USB_OTG_HS_DEVICE */
#if (CONFIG_USB_OTG_FS_HOST == 1) || (CONFIG_USB_OTG_HS_HOST == 1)
    HAL_HCD_Start(obj->dev->hcd_handle);
#endif /* CONFIG_USB_OTG_FS_HOST || CONFIG_USB_OTG_HS_HOST */
}

/**
 * @brief Stop USB PHY
 * 
 * @param usb_num USB PHY number
 */
static void usb_phy_hal_stop(usb_num_t usb_num) {
    omni_assert(usb_num < USB_NUM_MAX);

    usb_phy_obj_t *obj = &usb_phy_obj[usb_num];
    omni_assert_not_null(obj);

    // Stop USB PHY
#if (CONFIG_USB_OTG_FS_DEVICE == 1) || (CONFIG_USB_OTG_HS_DEVICE == 1)
    HAL_PCD_Stop(obj->dev->pcd_handle);
#endif /* CONFIG_USB_OTG_FS_DEVICE || CONFIG_USB_OTG_HS_DEVICE */
#if (CONFIG_USB_OTG_FS_HOST == 1) || (CONFIG_USB_OTG_HS_HOST == 1)
    HAL_HCD_Stop(obj->dev->hcd_handle);
#endif /* CONFIG_USB_OTG_FS_HOST || CONFIG_USB_OTG_HS_HOST */
}

/**
 * @brief Get USB PHY device information
 * 
 * @param usb_num USB PHY number
 * @return Pointer to USB PHY device information
 */
static usb_dev_t* usb_phy_hal_get_dev(usb_num_t usb_num) {
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
#if (CONFIG_USB_OTG_FS_DEVICE == 1)
    HAL_PCD_IRQHandler(usb_phy_obj[USB_PHY_OTG_FS].dev->pcd_handle);
#endif /* CONFIG_USB_OTG_FS_DEVICE */
#if (CONFIG_USB_OTG_FS_HOST == 1)
    HAL_HCD_IRQHandler(usb_phy_obj[USB_PHY_OTG_FS].dev->hcd_handle);
#endif /* CONFIG_USB_OTG_FS_HOST */
}
#endif /* CONFIG_USB_OTG_FS */
#if (CONFIG_USB_OTG_HS == 1)
/**
 * @brief USB OTG HS IRQ handler
 */
__weak void usbd_hs_irq_handler(void) {
    // When the IRQ handler is needed, it could be implemented in the user file
#if (CONFIG_USB_OTG_HS_DEVICE == 1)
    HAL_PCD_IRQHandler(usb_phy_obj[USB_PHY_OTG_HS].dev->pcd_handle);
#endif /* CONFIG_USB_OTG_HS_DEVICE */
#if (CONFIG_USB_OTG_HS_HOST == 1)
    HAL_HCD_IRQHandler(usb_phy_obj[USB_PHY_OTG_HS].dev->hcd_handle);
#endif /* CONFIG_USB_OTG_HS_HOST */
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

/**
 * @brief Set USB PHY as device
 * 
 * @param dev USB PHY device information
 * 
 * @return Operation status
 */
static int usb_phy_hal_set_device(usb_dev_t *dev) {
    PCD_HandleTypeDef *handle = (PCD_HandleTypeDef *)dev->pcd_handle;
    omni_assert_not_null(handle);

    // Set USB PHY as device
#if (CONFIG_USB_OTG_FS_DEVICE == 1)
    handle->Init.speed = PCD_SPEED_FULL;
    handle->Init.dma_enable = DISABLE;
    handle->Init.phy_itface = PCD_PHY_EMBEDDED;
#else
    handle->Init.speed = PCD_SPEED_HIGH;
    handle->Init.dma_enable = USB_OTG_DMA_ENABLE;
    handle->Init.phy_itface = USB_OTG_PHY;
#endif /* CONFIG_USB_OTG_FS_DEVICE == 1 */
    handle->Init.dev_endpoints = USB_OTG_ENDPOINT_NUMBER;
    handle->Init.Sof_enable = USB_OTG_SOF_ENABLE;
    handle->Init.low_power_enable = USB_OTG_LOW_POWER_ENABLE;
    handle->Init.vbus_sensing_enable = USB_OTG_VBUS_SENSING_ENABLE;
    handle->Init.lpm_enable = DISABLE;
    handle->Init.use_dedicated_ep1 = DISABLE;
    if (HAL_PCD_Init(handle) != HAL_OK) {
        return OMNI_FAIL;
    }

    HAL_PCDEx_SetRxFiFo(handle, CONFIG_USB_OTG_RX_FIFO_SIZE);
    HAL_PCDEx_SetTxFiFo(handle, 0, CONFIG_USB_OTG_TX_FIFO_0_SIZE);
#if defined(CONFIG_USB_OTG_TX_FIFO_1_SIZE) && (CONFIG_USB_OTG_TX_FIFO_1_SIZE > 0)
    HAL_PCDEx_SetTxFiFo(handle, 1, CONFIG_USB_OTG_TX_FIFO_1_SIZE);
#endif /* CONFIG_USB_OTG_FS_TX_FIFO_1_SIZE > 0 */
#if defined(CONFIG_USB_OTG_TX_FIFO_2_SIZE) && (CONFIG_USB_OTG_TX_FIFO_2_SIZE > 0)
    HAL_PCDEx_SetTxFiFo(handle, 2, CONFIG_USB_OTG_TX_FIFO_2_SIZE);
#endif /* CONFIG_USB_OTG_FS_TX_FIFO_2_SIZE > 0 */
#if defined(CONFIG_USB_OTG_TX_FIFO_3_SIZE) && (CONFIG_USB_OTG_TX_FIFO_3_SIZE > 0)
    HAL_PCDEx_SetTxFiFo(handle, 3, CONFIG_USB_OTG_TX_FIFO_3_SIZE);
#endif /* CONFIG_USB_OTG_FS_TX_FIFO_3_SIZE > 0 */
#if defined(CONFIG_USB_OTG_TX_FIFO_4_SIZE) && (CONFIG_USB_OTG_TX_FIFO_4_SIZE > 0)
    HAL_PCDEx_SetTxFiFo(handle, 4, CONFIG_USB_OTG_TX_FIFO_4_SIZE);
#endif /* CONFIG_USB_OTG_FS_TX_FIFO_4_SIZE > 0 */
#if defined(CONFIG_USB_OTG_TX_FIFO_5_SIZE) && (CONFIG_USB_OTG_TX_FIFO_5_SIZE > 0)
    HAL_PCDEx_SetTxFiFo(handle, 5, CONFIG_USB_OTG_TX_FIFO_5_SIZE);
#endif /* CONFIG_USB_OTG_FS_TX_FIFO_5_SIZE > 0 */

    return OMNI_OK;
}

/**
 * @brief Set USB PHY as host
 * 
 * @param dev USB PHY device information
 * 
 * @return Operation status
 */
static int usb_phy_hal_set_host(usb_dev_t *dev) {
    HCD_HandleTypeDef *handle = (HCD_HandleTypeDef *)dev->hcd_handle;
    omni_assert_not_null(handle);

    // Set USB PHY as host
#if (CONFIG_USB_OTG_FS_HOST == 1)
    handle->Init.speed = HCD_SPEED_FULL;
    handle->Init.phy_itface = HCD_PHY_EMBEDDED;
#else
    handle->Init.speed = HCD_SPEED_HIGH;
    handle->Init.phy_itface = USB_OTG_PHY;
#endif /* CONFIG_USB_OTG_FS_HOST == 1 */
    handle->Init.Host_channels = CONFIG_USB_OTG_CHANNEL_NUMBER;
    handle->Init.dma_enable = USB_OTG_DMA_ENABLE;
    handle->Init.Sof_enable = USB_OTG_SOF_ENABLE;
    handle->Init.vbus_sensing_enable = USB_OTG_VBUS_SENSING_ENABLE;
    if (HAL_HCD_Init(handle) != HAL_OK) {
        return OMNI_FAIL;
    }

    return OMNI_OK;
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
