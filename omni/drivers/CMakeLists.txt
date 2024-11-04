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

add_library(omni-drivers INTERFACE)

# if(NOT ${CONFIG_OMNI_DRIVER} STREQUAL "")
#     set(DRIVER_CFG_SOURCE_FILE ${OMNI_BASE}/drivers/omni_driver_cfg.in)
#     set(DRIVER_CFG_TARGET_FILE ${OMNI_DRIVER_CFG_DIR}/omni_driver_cfg.h)
#     omni_add_configure_file(${DRIVER_CFG_SOURCE_FILE} ${DRIVER_CFG_TARGET_FILE})
# endif()

omni_lib_src_ifdef(CONFIG_OMNI_DRIVER omni-drivers init.c)
omni_lib_src_ifdef(CONFIG_SSD1306 omni-drivers display/ssd1306.c)

target_include_directories(omni-drivers INTERFACE
    include
)
