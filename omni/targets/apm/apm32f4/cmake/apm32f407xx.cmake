# Set the target flags
set(TARGET_FLAGS "-mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard" CACHE STRING "Target flags" FORCE)

if(NOT DEFINED CONFIG_OMNI_DRIVER)
    set(STARTUP_SOURCE_FILE ${CONFIG_OMNI_TARGET}/toolchain/gcc/startup_apm32f407xx.S)
    set(STARTUP_TARGET_FILE ${OMNI_STARTUP_CFG_DIR}/startup_apm32f407xx.S)
else()
    set(STARTUP_SOURCE_FILE ${CONFIG_OMNI_TARGET}/toolchain/startup_apm32f407xx.c)
    set(STARTUP_TARGET_FILE ${OMNI_STARTUP_CFG_DIR}/startup_apm32f407xx.c)
endif()

if (CONFIG_OMNI_BOARD STREQUAL "apm32f407ig")
    set(LS_SOURCE_FILE ${CONFIG_OMNI_TARGET}/toolchain/gcc/apm32f407xg_flash.ld)
    set(LS_TARGET_FILE ${OMNI_STARTUP_CFG_DIR}/apm32f407xg_flash.ld)
else()
    message(FATAL_ERROR "CONFIG_OMNI_BOARD is not set")
endif()

set(TARGET_CORE_DEFINES
    APM32F407xx
)