# Set the target flags
set(TARGET_FLAGS "-mcpu=cortex-m7 -mfpu=fpv5-d16 -mfloat-abi=hard" CACHE STRING "Target flags" FORCE)

if(NOT DEFINED CONFIG_OMNI_DRIVER)
    set(STARTUP_SOURCE_FILE ${CONFIG_OMNI_TARGET}/toolchain/gcc/startup_stm32h750xx.s)
    set(STARTUP_TARGET_FILE ${OMNI_STARTUP_CFG_DIR}/startup_stm32h750xx.s)
else()
    set(STARTUP_SOURCE_FILE ${CONFIG_OMNI_TARGET}/toolchain/startup_stm32h750xx.c)
    set(STARTUP_TARGET_FILE ${OMNI_STARTUP_CFG_DIR}/startup_stm32h750xx.c)
endif()

if (CONFIG_OMNI_BOARD STREQUAL "stm32h750vb")
    set(LS_SOURCE_FILE ${CONFIG_OMNI_TARGET}/toolchain/gcc/stm32h750xb_flash.ld)
    set(LS_TARGET_FILE ${OMNI_STARTUP_CFG_DIR}/stm32h750xb_flash.ld)
    set(SCT_SOURCE_FILE ${CONFIG_OMNI_TARGET}/toolchain/arm/stm32h750xb_flash.sct)
    set(SCT_TARGET_FILE ${OMNI_STARTUP_CFG_DIR}/stm32h750xb_flash.sct)
else()
    message(FATAL_ERROR "CONFIG_OMNI_BOARD is not set")
endif()

set(TARGET_CORE_DEFINES
    STM32H750xx
)