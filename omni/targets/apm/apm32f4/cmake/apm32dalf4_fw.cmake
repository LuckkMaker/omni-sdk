if(NOT DEFINED CONFIG_OMNI_DRIVER)
    file(GLOB TARGET_DRIVER_SOURCES
        "apm32dalf4_fw/APM32F4xx_DAL_Driver/Source/*.c"
    )
else()
    file(GLOB TARGET_DRIVER_SOURCES
        "apm32dalf4_fw/APM32F4xx_DAL_Driver/Source/*.c"
        "apm32dalf4_fw/CMSIS/Device/Geehy/APM32F4xx/Source/system_apm32f4xx.c"
    )
endif()

set(TARGET_DRIVER_DEFINES
    USE_DAL_DRIVER
    # USE_FULL_DDL_DRIVER
)

# First, include stm32xxx_hal_conf.h from the application project
if(NOT DEFINED CONFIG_OMNI_DRIVER)
set(TARGET_DRIVER_INCLUDES
    apm32dalf4_fw/APM32F4xx_DAL_Driver/Include
    apm32dalf4_fw/APM32F4xx_DAL_Driver/Include/Legacy
    apm32dalf4_fw/CMSIS/Device/Geehy/APM32F4xx/Include
)
else()
set(TARGET_DRIVER_INCLUDES
    apm32dalf4_fw
    apm32dalf4_fw/APM32F4xx_DAL_Driver/Include
    apm32dalf4_fw/APM32F4xx_DAL_Driver/Include/Legacy
    apm32dalf4_fw/CMSIS/Device/Geehy/APM32F4xx/Include
)
endif()