# Copyright (c) 2024 LuckkMaker
# All rights reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

omni_add_subdirectory_ifdef(CONFIG_RTOS_CMSIS_FREERTOS cmsis-freertos)
omni_lib_link_ifdef(CONFIG_RTOS_CMSIS_FREERTOS omni-rtos omni-cmsis-freertos)
omni_add_subdirectory_ifdef(CONFIG_RTOS_CMSIS_RTX cmsis-rtx)
omni_lib_link_ifdef(CONFIG_RTOS_CMSIS_RTX omni-rtos omni-cmsis-rtx)
omni_add_subdirectory_ifdef(CONFIG_RTOS_THREADX threadx)
omni_lib_link_ifdef(CONFIG_RTOS_THREADX omni-rtos omni-threadx)

omni_add_subdirectory_ifdef(CONFIG_USB_CHERRYUSB cherryusb)
omni_lib_link_ifdef(CONFIG_USB_CHERRYUSB omni-core omni-cherryusb)
omni_add_subdirectory_ifdef(CONFIG_USB_STM32 stm32_usb_device)
omni_lib_link_ifdef(CONFIG_USB_STM32 omni-core omni-stm32-usb-device)
omni_add_subdirectory_ifdef(CONFIG_USB_USBX usbx)
omni_lib_link_ifdef(CONFIG_USB_USBX omni-core omni-usbx)

omni_add_subdirectory_ifdef(CONFIG_U8G2 u8g2)
omni_lib_link_ifdef(CONFIG_U8G2 omni-core u8g2)

omni_add_subdirectory_ifdef(CONFIG_SEGGER_RTT segger_rtt)
omni_lib_link_ifdef(CONFIG_SEGGER_RTT omni-core omni-segger-rtt)

omni_add_subdirectory_ifdef(CONFIG_SHELL_LETTER letter_shell)
omni_lib_link_ifdef(CONFIG_SHELL_LETTER omni-core omni-letter-shell)

omni_add_subdirectory_ifdef(CONFIG_LUA lua)
omni_lib_link_ifdef(CONFIG_LUA omni-core omni-lua)