/**
  * @file    gpio_hal.c
  * @author  LuckkMaker
  * @brief   GPIO HAL driver
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
#include "drivers/gpio.h"
#include "hal/gpio_hal.h"

#define PIN_PORT(gpio_num)           ((uint8_t)(((gpio_num) >> 4) & 0xFU))
#define PIN_NUM(gpio_num)            ((uint8_t)((gpio_num) & 0xFU))

#define GET_GPIO_PORT(gpio_num)      ((GPIO_TypeDef *)(GPIOA_BASE + (0x400U * PIN_PORT(gpio_num))))
#define GET_GPIO_PIN(gpio_num)       ((uint16_t)(1U << PIN_NUM(gpio_num)))

#if defined(GPIOK)
#define GPIO_PORT_MAX 11U
#elif defined(GPIOJ)
#define GPIO_PORT_MAX 10U
#elif defined(GPIOI)
#define GPIO_PORT_MAX 9U
#elif defined(GPIOH)
#define GPIO_PORT_MAX 8U
#elif defined(GPIOG)
#define GPIO_PORT_MAX 7U
#elif defined(GPIOF)
#define GPIO_PORT_MAX 6U
#elif defined(GPIOE)
#define GPIO_PORT_MAX 5U
#elif defined(GPIOD)
#define GPIO_PORT_MAX 4U
#elif defined(GPIOC)
#define GPIO_PORT_MAX 3U
#elif defined(GPIOB)
#define GPIO_PORT_MAX 2U
#elif defined(GPIOA)
#define GPIO_PORT_MAX 1U
#else
#define GPIO_PORT_MAX 0U
#error Unsupported GPIO peripheral.
#endif

static int gpio_hal_init(uint32_t gpio_num, gpio_driver_config_t *config);
static int gpio_hal_deinit(uint32_t gpio_num);
static int gpio_hal_set_level(uint32_t gpio_num, uint32_t level);
static uint32_t gpio_hal_get_level(uint32_t gpio_num);
static int gpio_hal_toggle(uint32_t gpio_num);

const struct gpio_driver_api gpio_driver = {
    .init = gpio_hal_init,
    .deinit = gpio_hal_deinit,
    .set_level = gpio_hal_set_level,
    .get_level = gpio_hal_get_level,
    .toggle = gpio_hal_toggle,
};

/**
 * @brief Open GPIO
 * 
 * @param gpio_num GPIO number
 * @param config Pointer to GPIO driver configuration structure
 * @return Operation status
 */
static int gpio_hal_init(uint32_t gpio_num, gpio_driver_config_t *config) {
    GPIO_TypeDef *gpio_port;
    uint32_t gpio_pin;
    uint32_t gpio_mode;
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    omni_assert_not_null(config);
    omni_assert(PIN_PORT(gpio_num) < GPIO_PORT_MAX);

    gpio_port = GET_GPIO_PORT(gpio_num);
    gpio_pin = GET_GPIO_PIN(gpio_num);

    if (config->mode == GPIO_MODE_OD_OUTPUT) {
        gpio_mode = GPIO_MODE_OUTPUT_OD;
    } else if (config->mode == GPIO_MODE_PP_OUTPUT) {
        gpio_mode = GPIO_MODE_OUTPUT_PP;
    } else {
        gpio_mode = GPIO_MODE_INPUT;
    }

    // Enable GPIO clock
    gpio_hal_enable_clock(gpio_port);

    HAL_GPIO_WritePin(gpio_port, gpio_pin, (GPIO_PinState)config->level);

    GPIO_InitStruct.Pin = gpio_pin;
    GPIO_InitStruct.Mode = gpio_mode;
    GPIO_InitStruct.Pull = (uint32_t)config->pull;
    GPIO_InitStruct.Speed = (uint32_t)config->speed;
    HAL_GPIO_Init(gpio_port, &GPIO_InitStruct);

    return OMNI_OK;
}

/**
 * @brief Close GPIO
 * 
 * @param gpio_num GPIO number
 * @return Operation status
 */
static int gpio_hal_deinit(uint32_t gpio_num) {
    GPIO_TypeDef *gpio_port;
    uint32_t gpio_pin;
    omni_assert(PIN_PORT(gpio_num) < GPIO_PORT_MAX);

    gpio_port = GET_GPIO_PORT(gpio_num);
    gpio_pin = GET_GPIO_PIN(gpio_num);

    HAL_GPIO_DeInit(gpio_port, gpio_pin);

    return OMNI_OK;
}

/**
 * @brief Set GPIO level
 * 
 * @param gpio_num GPIO number
 * @param level GPIO level
 * @return Operation status
 */
static int gpio_hal_set_level(uint32_t gpio_num, uint32_t level) {
    GPIO_TypeDef *gpio_port;
    uint32_t gpio_pin;
    omni_assert(PIN_PORT(gpio_num) < GPIO_PORT_MAX);

    gpio_port = GET_GPIO_PORT(gpio_num);
    gpio_pin = GET_GPIO_PIN(gpio_num);

    HAL_GPIO_WritePin(gpio_port, gpio_pin, (GPIO_PinState)level);

    return OMNI_OK;
}

/**
 * @brief Get GPIO level
 * 
 * @param gpio_num GPIO number
 * @return GPIO level
 */
static uint32_t gpio_hal_get_level(uint32_t gpio_num) {
    GPIO_TypeDef *gpio_port;
    uint32_t gpio_pin;
    omni_assert(PIN_PORT(gpio_num) < GPIO_PORT_MAX);

    gpio_port = GET_GPIO_PORT(gpio_num);
    gpio_pin = GET_GPIO_PIN(gpio_num);

    return HAL_GPIO_ReadPin(gpio_port, gpio_pin);
}

/**
 * @brief Toggle GPIO level
 * 
 * @param gpio_num GPIO number
 * @return Operation status
 */
static int gpio_hal_toggle(uint32_t gpio_num) {
    GPIO_TypeDef *gpio_port;
    uint32_t gpio_pin;
    omni_assert(PIN_PORT(gpio_num) < GPIO_PORT_MAX);

    gpio_port = GET_GPIO_PORT(gpio_num);
    gpio_pin = GET_GPIO_PIN(gpio_num);

    HAL_GPIO_TogglePin(gpio_port, gpio_pin);

    return OMNI_OK;
}

/********************* HAL functions **********************/

/**
 * @brief Enable GPIO clock
 * 
 * @param GPIOx GPIO port
 */
void gpio_hal_enable_clock(GPIO_TypeDef *GPIOx) {
#if defined(GPIOA)
    if (GPIOx == GPIOA) {__HAL_RCC_GPIOA_CLK_ENABLE();}
#endif /* GPIOA */
#if defined(GPIOB)
    if (GPIOx == GPIOB) {__HAL_RCC_GPIOB_CLK_ENABLE();}
#endif /* GPIOB */
#if defined(GPIOC)
    if (GPIOx == GPIOC) {__HAL_RCC_GPIOC_CLK_ENABLE();}
#endif /* GPIOC */
#if defined(GPIOD)
    if (GPIOx == GPIOD) {__HAL_RCC_GPIOD_CLK_ENABLE();}
#endif /* GPIOD */
#if defined(GPIOE)
    if (GPIOx == GPIOE) {__HAL_RCC_GPIOE_CLK_ENABLE();}
#endif /* GPIOE */
#if defined(GPIOF)
    if (GPIOx == GPIOF) {__HAL_RCC_GPIOF_CLK_ENABLE();}
#endif /* GPIOF */
#if defined(GPIOG)
    if (GPIOx == GPIOG) {__HAL_RCC_GPIOG_CLK_ENABLE();}
#endif /* GPIOG */
#if defined(GPIOH)
    if (GPIOx == GPIOH) {__HAL_RCC_GPIOH_CLK_ENABLE();}
#endif /* GPIOH */
#if defined(GPIOI)
    if (GPIOx == GPIOI) {__HAL_RCC_GPIOI_CLK_ENABLE();}
#endif /* GPIOI */
}

#if defined(CONFIG_SOC_FAMILY_STM32F1XX)
/**
 * @brief Set GPIO alternate function
 * 
 * @param alternate: GPIO alternate function
 */
void gpio_hal_alternate(uint32_t alternate) {
    uint32_t msk, val;
    volatile uint32_t mapr;

    if (alternate != AFIO_UNAVAILABLE_REMAP) {
        msk = (alternate >> 5) & 0x07;
        val = (alternate >> 8) & 0x0F;

        __HAL_RCC_AFIO_CLK_ENABLE();

        if (alternate & (1 << 12)) {
            /* AF remap and debug I/O config register 2 */
            mapr  = AFIO->MAPR2;
            mapr &= ~(msk << (alternate & 0x1F));
            mapr |=  (val << (alternate & 0x1F));
            AFIO->MAPR2 = mapr;
        } else {
            /* AF remap and debug I/O config register */
            mapr  = AFIO->MAPR;
            mapr &= ~(msk << (alternate & 0x1F));
            mapr |=  (val << (alternate & 0x1F));

            /* Serial wire JTAG configuration */
            msk  =   (AFIO_SWJ_FULL >> 5) & 0x07;
            val  =   (AFIO_SWJ_FULL >> 8) & 0x0F;
            mapr &= ~(msk << (AFIO_SWJ_FULL & 0x1F));
            mapr |=  (val << (AFIO_SWJ_FULL & 0x1F));

            AFIO->MAPR = mapr;
        }
    }
}
#endif /* CONFIG_SOC_FAMILY_STM32F1XX */
