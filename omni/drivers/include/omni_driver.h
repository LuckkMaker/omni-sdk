/**
  * @file    omni_driver.h
  * @author  LuckkMaker
  * @brief   Omni driver header file
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
#ifndef OMNI_DRIVER_H
#define OMNI_DRIVER_H

/* Includes ------------------------------------------------------------------*/
#include "include/device.h"
#if defined(CONFIG_OMNI_DRIVER)
#include "drivers/init.h"
#include "drivers/gpio.h"
#include "drivers/timer.h"

#if defined(CONFIG_OMNI_DRIVER_I2C)
#include "drivers/i2c.h"
#endif /* CONFIG_OMNI_DRIVER_I2C */

#if defined(CONFIG_OMNI_DRIVER_USART)
#include "drivers/usart.h"
#endif /* CONFIG_OMNI_DRIVER_USART */

#if defined(CONFIG_OMNI_DRIVER_USB)
#include "drivers/usb_phy.h"
#endif /* CONFIG_OMNI_DRIVER_USB */

#if defined(CONFIG_SSD1306)
#include "display/ssd1306.h"
#endif /* CONFIG_SSD1306 */

#endif /* CONFIG_OMNI_DRIVER */

#endif /* OMNI_DRIVER_H */
