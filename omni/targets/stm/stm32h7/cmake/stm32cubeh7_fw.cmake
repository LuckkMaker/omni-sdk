if(NOT DEFINED CONFIG_OMNI_DRIVER)
    file(GLOB TARGET_DRIVER_SOURCES
        "stm32cubeh7_fw/STM32H7xx_HAL_Driver/Src/*.c"
    )
else()
    file(GLOB TARGET_DRIVER_SOURCES
        "stm32cubeh7_fw/STM32H7xx_HAL_Driver/Src/*.c"
        "stm32cubeh7_fw/CMSIS/Device/ST/STM32H7xx/Source/Templates/system_stm32h7xx.c"
    )
endif()

set(TARGET_DRIVER_DEFINES
    USE_HAL_DRIVER
    # USE_FULL_LL_DRIVER
)

# First, include stm32xxx_hal_conf.h from the application project
if(NOT DEFINED CONFIG_OMNI_DRIVER)
set(TARGET_DRIVER_INCLUDES
    stm32cubeh7_fw/STM32H7xx_HAL_Driver/Inc
    stm32cubeh7_fw/STM32H7xx_HAL_Driver/Inc/Legacy
    stm32cubeh7_fw/CMSIS/Device/ST/STM32H7xx/Include
)
else()
set(TARGET_DRIVER_INCLUDES
    stm32cubeh7_fw
    stm32cubeh7_fw/STM32H7xx_HAL_Driver/Inc
    stm32cubeh7_fw/STM32H7xx_HAL_Driver/Inc/Legacy
    stm32cubeh7_fw/CMSIS/Device/ST/STM32H7xx/Include
)
endif()