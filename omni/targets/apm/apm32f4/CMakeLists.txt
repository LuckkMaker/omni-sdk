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

include(cmake/apm32dalf4_fw.cmake)
include(cmake/${CONFIG_OMNI_TARGET}.cmake)

add_library(omni-apm32f4 INTERFACE)

# Add the ll drivers
if(NOT ${CONFIG_OMNI_DRIVER} STREQUAL "")

endif()

# Add the startup file
# STARTUP_SOURCE_FILE and STARTUP_TARGET_FILE are defined in the CONFIG_OMNI_TARGET.cmake file
omni_add_configure_file(${STARTUP_SOURCE_FILE} ${STARTUP_TARGET_FILE})

# Add the linker file and set the linker script for the target
# LS_SOURCE_FILE and LS_TARGET_FILE are defined in the CONFIG_OMNI_TARGET.cmake file
if(DEFINED CONFIG_OMNI_DRIVER)
    omni_add_configure_file(${LS_SOURCE_FILE} ${LS_TARGET_FILE})
    omni_set_linker_file(omni-apm32f4 ${CONFIG_OMNI_BOARD} ${LS_TARGET_FILE})
endif()

target_compile_definitions(omni-apm32f4 INTERFACE
    ${TARGET_DRIVER_DEFINES}
    ${TARGET_CORE_DEFINES}
)

target_include_directories(omni-apm32f4 INTERFACE
    ${TARGET_DRIVER_INCLUDES}
    drivers/include
    .
)

target_sources(omni-apm32f4 INTERFACE
    ${TARGET_DRIVER_SOURCES}
    ${STARTUP_TARGET_FILE}
)