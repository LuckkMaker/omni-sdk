# Set the target flags
set(TARGET_FLAGS "-mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard" CACHE STRING "Target flags" FORCE)

if(NOT DEFINED CONFIG_OMNI_DRIVER)
    set(STARTUP_SOURCE_FILE ${CONFIG_OMNI_TARGET}/toolchain/gcc/startup_stm32f411xe.s)
    set(STARTUP_TARGET_FILE ${OMNI_STARTUP_CFG_DIR}/startup_stm32f411xe.s)
else()
    set(STARTUP_SOURCE_FILE ${CONFIG_OMNI_TARGET}/toolchain/startup_stm32f411xx.c)
    set(STARTUP_TARGET_FILE ${OMNI_STARTUP_CFG_DIR}/startup_stm32f411xx.c)
endif()

if (CONFIG_OMNI_BOARD STREQUAL "stm32f411ce")
    set(LS_SOURCE_FILE ${CONFIG_OMNI_TARGET}/toolchain/gcc/stm32f411xe_flash.ld)
    set(LS_TARGET_FILE ${OMNI_STARTUP_CFG_DIR}/stm32f411xe_flash.ld)
else()
    message(FATAL_ERROR "CONFIG_OMNI_BOARD is not set")
endif()

set(TARGET_CORE_DEFINES
    STM32F411xE
)