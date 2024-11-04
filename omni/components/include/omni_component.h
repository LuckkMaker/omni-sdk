/**
  * @file    omni_component.h
  * @author  LuckkMaker
  * @brief   Omni component header file
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
#ifndef OMNI_COMPONENT_H
#define OMNI_COMPONENT_H

/* Includes ------------------------------------------------------------------*/
#if defined(CONFIG_COMPONENT_CHERRYUSB)
#include "cherryusb/usb_device.h"
#endif /* CONFIG_COMPONENT_CHERRYUSB */

#if defined(CONFIG_COMPONENT_CONSOLE)
#include "console/console.h"
#endif /* CONFIG_COMPONENT_CONSOLE */

#if defined(CONFIG_COMPONENT_COMMAND)
#include "command/command.h"
#endif /* CONFIG_COMPONENT_COMMAND */

#if defined(CONFIG_COMPONENT_RING_BUFFER)
#include "ring_buffer/ring_buffer.h"
#endif /* CONFIG_COMPONENT_RING_BUFFER */

#endif /* OMNI_COMPONENT_H */
