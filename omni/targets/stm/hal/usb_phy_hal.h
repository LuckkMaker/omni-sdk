/**
  * @file    usb_phy_hal.h
  * @author  LuckkMaker
  * @brief   Header file of usb_phy_hal.c
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
#ifndef OMNI_HAL_USB_PHY_H
#define OMNI_HAL_USB_PHY_H

/* Includes ------------------------------------------------------------------*/
#include "include/device.h"

#ifdef __cplusplus
extern "C" {
#endif

void usbd_irq_handler(void);
void usbd_fs_irq_handler(void);
void usbd_hs_irq_handler(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* OMNI_HAL_USB_PHY_H */
