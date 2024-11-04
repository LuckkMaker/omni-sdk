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

add_library(omni-targets INTERFACE)

if(NOT ${CONFIG_OMNI_PLATFORM} STREQUAL "")
    set(OMNI_PLATFORM "omni-${CONFIG_OMNI_PLATFORM}")
    add_subdirectory(${CONFIG_OMNI_PLATFORM})
else()
    message(FATAL_ERROR "CONFIG_OMNI_PLATFORM is not set")
endif()

# Add omni device
if(NOT ${CONFIG_OMNI_DRIVER} STREQUAL "")
    set(DEVICE_SOURCE_FILE ${OMNI_FAMILY_DIR}/omni_device_cfg.in)
    set(DEVICE_TARGET_FILE ${OMNI_DEVICE_CFG_DIR}/omni_device_cfg.h)
    omni_add_configure_file(${DEVICE_SOURCE_FILE} ${DEVICE_TARGET_FILE})
endif()

# Add the SVD file
set(SVD_SOURCE_FILE ${CMAKE_CURRENT_LIST_DIR}/svd/${CONFIG_OMNI_TARGET}.svd)
set(SVD_TARGET_FILE ${OMNI_SVD_DIR}/${CONFIG_OMNI_TARGET}.svd)
omni_add_configure_file(${SVD_SOURCE_FILE} ${SVD_TARGET_FILE})

target_link_libraries(omni-targets INTERFACE
    ${OMNI_PLATFORM}
)
