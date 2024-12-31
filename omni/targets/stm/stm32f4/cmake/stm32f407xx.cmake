# Set the target flags
set(TARGET_FLAGS "-mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard" CACHE STRING "Target flags" FORCE)

if(NOT DEFINED CONFIG_OMNI_DRIVER)
    set(STARTUP_SOURCE_FILE ${CONFIG_OMNI_TARGET}/toolchain/gcc/startup_stm32f407xx.s)
    set(STARTUP_TARGET_FILE ${OMNI_STARTUP_CFG_DIR}/startup_stm32f407xx.s)
else()
    set(STARTUP_SOURCE_FILE ${CONFIG_OMNI_TARGET}/toolchain/startup_stm32f407xx.c)
    set(STARTUP_TARGET_FILE ${OMNI_STARTUP_CFG_DIR}/startup_stm32f407xx.c)
endif()

if (CONFIG_OMNI_BOARD STREQUAL "stm32f407ig")
    set(LS_SOURCE_FILE ${CONFIG_OMNI_TARGET}/toolchain/gcc/stm32f407xg_flash.ld)
    set(LS_TARGET_FILE ${OMNI_STARTUP_CFG_DIR}/stm32f407xg_flash.ld)
    set(SCT_SOURCE_FILE ${CONFIG_OMNI_TARGET}/toolchain/arm/stm32f407xg_flash.sct)
    set(SCT_TARGET_FILE ${OMNI_STARTUP_CFG_DIR}/stm32f407xg_flash.sct)
else()
    message(FATAL_ERROR "CONFIG_OMNI_BOARD is not set")
endif()

set(TARGET_CORE_DEFINES
    STM32F407xx
)