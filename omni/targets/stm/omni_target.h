/**
  * @file    omni_target.h
  * @author  LuckkMaker
  * @brief   Target specific header file
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
#ifndef OMNI_TARGETS_H
#define OMNI_TARGETS_H

/* Includes ------------------------------------------------------------------*/
#include "omni_device_cfg.h"

#if defined(CONFIG_SOC_FAMILY_STM32H7XX)
#include "stm32h7xx_hal.h"
#elif defined(CONFIG_SOC_FAMILY_STM32F4XX)
#include "stm32f4xx_hal.h"
#include "stm32f4xx_ll_usart.h"
#elif defined(CONFIG_SOC_FAMILY_STM32F1XX)
#include "stm32f1xx_hal.h"
#include "stm32f1xx_ll_usart.h"
#else
#error "Unknown target"
#endif /* CONFIG_SOC_FAMILY_STM32H7XX */

#include "omni_config.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef const struct gpio_pin {
    GPIO_TypeDef *ins;
    uint32_t index;
#if !defined(CONFIG_SOC_FAMILY_STM32F1XX)
    uint32_t alternate;
#endif /* CONFIG_SOC_FAMILY_STM32F1XX */
} gpio_pin_t;

typedef struct gpio_dev {
    GPIO_TypeDef *ins;
    uint32_t pin;
} gpio_dev_t;

typedef const struct dma_dev {
    DMA_HandleTypeDef *handle;
    DMA_TypeDef *ins;
    uint32_t irq_num;
    uint32_t irq_prio;
} dma_dev_t;

typedef const struct i2c_dev {
    I2C_HandleTypeDef *handle;
    IRQn_Type ev_irq_num;
    uint8_t ev_irq_prio;
    IRQn_Type er_irq_num;
    uint8_t er_irq_prio;
#if defined(CONFIG_SOC_FAMILY_STM32F1XX)
    uint32_t alternate;
#endif /* CONFIG_SOC_FAMILY_STM32F1XX */
    gpio_pin_t *scl_pin;
    gpio_pin_t *sda_pin;
    dma_dev_t *dma_tx;
    dma_dev_t *dma_rx;
} i2c_dev_t;

typedef const struct spi_dev {
    SPI_HandleTypeDef *handle;
    uint32_t clock;
    IRQn_Type irq_num;
    uint8_t irq_prio;
#if defined(CONFIG_SOC_FAMILY_STM32F1XX)
    uint32_t alternate;
#endif /* CONFIG_SOC_FAMILY_STM32F1XX */
    gpio_pin_t *cs_pin;
    gpio_pin_t *sck_pin;
    gpio_pin_t *miso_pin;
    gpio_pin_t *mosi_pin;
    dma_dev_t *dma_tx;
    dma_dev_t *dma_rx;
} spi_dev_t;

typedef const struct usart_dev {
    UART_HandleTypeDef *handle;
    IRQn_Type irq_num;
    uint8_t irq_prio;
#if defined(CONFIG_SOC_FAMILY_STM32F1XX)
    uint32_t alternate;
#endif /* CONFIG_SOC_FAMILY_STM32F1XX */
    gpio_pin_t *tx_pin;
    gpio_pin_t *rx_pin;
    dma_dev_t *dma_tx;
    dma_dev_t *dma_rx;
} usart_dev_t;

#if defined(CONFIG_SOC_FAMILY_STM32F1XX)
typedef const struct usb_dev {
    USB_TypeDef *ins;
    uint32_t base;
    IRQn_Type irq_num;
    uint8_t irq_prio;
    gpio_pin_t *dm_pin;
    gpio_pin_t *dp_pin;
} usb_dev_t;
#else
typedef const struct usb_ulpi_pin {
    gpio_pin_t *dir_pin;
    gpio_pin_t *nxt_pin;
    gpio_pin_t *stp_pin;
    gpio_pin_t *clk_pin;
    gpio_pin_t *data[8];
} usb_ulpi_pin_t;

typedef const struct usb_dev {
    PCD_HandleTypeDef *pcd_handle;
    HCD_HandleTypeDef *hcd_handle;
    USB_OTG_GlobalTypeDef *ins;
    IRQn_Type irq_num;
    uint8_t irq_prio;
    gpio_pin_t *dm_pin;
    gpio_pin_t *dp_pin;
    gpio_pin_t *vbus_pin;
    gpio_pin_t *id_pin;
    gpio_pin_t *sof_pin;
    usb_ulpi_pin_t ulpi_pin;
} usb_dev_t;
#endif /* CONFIG_SOC_FAMILY_STM32F1XX */

#ifdef __cplusplus
}
#endif

#endif /* OMNI_TARGETS_H */
