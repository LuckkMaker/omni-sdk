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

if(NOT ${CONFIG_OMNI_FAMILY} STREQUAL "")
    add_subdirectory(${CONFIG_OMNI_FAMILY})
else()
    message(FATAL_ERROR "CONFIG_OMNI_FAMILY is not set")
endif()

add_library(omni-apm INTERFACE)

# Add the drivers
if(NOT ${CONFIG_OMNI_DRIVER} STREQUAL "")

    file(GLOB OMNI_TARGET_SOURCES
        "hal/soc.c"
        "hal/syscalls.c"
        "hal/sysmem.c" 
        "hal/clock_hal.c"
        "hal/dma_hal.c"
        "hal/dwt_hal.c"
        "hal/gpio_hal.c"
        "hal/irq_hal.c"
    )

    omni_lib_src_ifdef(CONFIG_OMNI_DRIVER omni-apm ${OMNI_TARGET_SOURCES})
    omni_lib_src_ifdef(CONFIG_OMNI_DRIVER_TIMER omni-apm hal/timer_hal.c)
    omni_lib_src_ifdef(CONFIG_OMNI_DRIVER_I2C omni-apm hal/i2c_hal.c)
    omni_lib_src_ifdef(CONFIG_OMNI_DRIVER_USART omni-apm hal/usart_hal.c)
    omni_lib_src_ifdef(CONFIG_OMNI_DRIVER_USB omni-apm hal/usb_phy_hal.c)
endif()

target_include_directories(omni-apm INTERFACE
    .
)

# link omni-cmsis-cortex-m to omni-apm
target_link_libraries(omni-apm INTERFACE 
    omni-cmsis-cortex-m
    omni-${CONFIG_OMNI_FAMILY}
)