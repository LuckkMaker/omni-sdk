/**
  * @file    usb_ll.h
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef OMNI_LL_USB_H
#define OMNI_LL_USB_H

/* Includes ------------------------------------------------------------------*/
#include "drivers/usb_phy_types.h"

#ifdef __cplusplus
extern "C" {
#endif

usb_dev_t* usb_ll_get_dev(usb_num_t usb_num);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* OMNI_LL_USB_H */
