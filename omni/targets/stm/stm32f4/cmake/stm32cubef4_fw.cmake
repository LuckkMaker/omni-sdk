if(NOT DEFINED CONFIG_OMNI_DRIVER)
    file(GLOB TARGET_DRIVER_SOURCES
        "stm32cubef4_fw/STM32F4xx_HAL_Driver/Src/*.c"
    )
else()
    file(GLOB TARGET_DRIVER_SOURCES
        "stm32cubef4_fw/STM32F4xx_HAL_Driver/Src/*.c"
        "stm32cubef4_fw/CMSIS/Device/ST/STM32F4xx/Source/Templates/system_stm32f4xx.c"
    )
endif()

set(TARGET_DRIVER_DEFINES
    USE_HAL_DRIVER
    # USE_FULL_LL_DRIVER
)

# First, include stm32xxx_hal_conf.h from the application project
if(NOT DEFINED CONFIG_OMNI_DRIVER)
set(TARGET_DRIVER_INCLUDES
    stm32cubef4_fw/STM32F4xx_HAL_Driver/Inc
    stm32cubef4_fw/STM32F4xx_HAL_Driver/Inc/Legacy
    stm32cubef4_fw/CMSIS/Device/ST/STM32F4xx/Include
)
else()
set(TARGET_DRIVER_INCLUDES
    stm32cubef4_fw
    stm32cubef4_fw/STM32F4xx_HAL_Driver/Inc
    stm32cubef4_fw/STM32F4xx_HAL_Driver/Inc/Legacy
    stm32cubef4_fw/CMSIS/Device/ST/STM32F4xx/Include
)
endif()