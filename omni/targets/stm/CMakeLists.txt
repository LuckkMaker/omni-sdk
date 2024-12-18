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

add_library(omni-stm INTERFACE)

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

    omni_lib_src_ifdef(CONFIG_OMNI_DRIVER omni-stm ${OMNI_TARGET_SOURCES})
    omni_lib_src_ifdef(CONFIG_OMNI_DRIVER_TIMER omni-stm hal/timer_hal.c)
    omni_lib_src_ifdef(CONFIG_OMNI_DRIVER_I2C omni-stm hal/i2c_hal.c)
    omni_lib_src_ifdef(CONFIG_OMNI_DRIVER_SPI omni-stm hal/spi_hal.c)
    if(CONFIG_OMNI_FAMILY STREQUAL "stm32h7")
        omni_lib_src_ifdef(CONFIG_OMNI_DRIVER_USART omni-stm hal/usart_hal_v2.c)
    else()
        omni_lib_src_ifdef(CONFIG_OMNI_DRIVER_USART omni-stm hal/usart_hal.c)
    endif()
    omni_lib_src_ifdef(CONFIG_OMNI_DRIVER_USB omni-stm hal/usb_phy_hal.c)
endif()

target_include_directories(omni-stm INTERFACE
    .
)

# link omni-cmsis-cortex-m to omni-stm
target_link_libraries(omni-stm INTERFACE 
    omni-cmsis-cortex-m
    omni-${CONFIG_OMNI_FAMILY}
)