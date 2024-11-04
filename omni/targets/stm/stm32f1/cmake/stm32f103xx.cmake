# Set the target flags
set(TARGET_FLAGS "-mcpu=cortex-m3" CACHE STRING "Target flags" FORCE)

if(NOT DEFINED CONFIG_OMNI_DRIVER)
    if (CONFIG_OMNI_BOARD STREQUAL "stm32f103cb")
        set(STARTUP_SOURCE_FILE ${CONFIG_OMNI_TARGET}/toolchain/gcc/startup_stm32f103xb.s)
        set(STARTUP_TARGET_FILE ${OMNI_STARTUP_CFG_DIR}/startup_stm32f103xb.s)
    elseif (CONFIG_OMNI_BOARD STREQUAL "stm32f103ze")
        set(STARTUP_SOURCE_FILE ${CONFIG_OMNI_TARGET}/toolchain/gcc/startup_stm32f103xe.s)
        set(STARTUP_TARGET_FILE ${OMNI_STARTUP_CFG_DIR}/startup_stm32f103xe.s)
    else()
        message(FATAL_ERROR "CONFIG_OMNI_BOARD is not set")
    endif()
else()
    set(STARTUP_SOURCE_FILE ${CONFIG_OMNI_TARGET}/toolchain/startup_stm32f103xx.c)
    set(STARTUP_TARGET_FILE ${OMNI_STARTUP_CFG_DIR}/startup_stm32f103xx.c)
endif()

if (CONFIG_OMNI_BOARD STREQUAL "stm32f103cb")
    set(COMPILE_DEFINITION STM32F103xB)
    set(LS_SOURCE_FILE ${CONFIG_OMNI_TARGET}/toolchain/gcc/stm32f103cbtx_flash.ld)
    set(LS_TARGET_FILE ${OMNI_STARTUP_CFG_DIR}/stm32f103cbtx_flash.ld)
elseif (CONFIG_OMNI_BOARD STREQUAL "stm32f103ze")
    set(COMPILE_DEFINITION STM32F103xE)
    set(LS_SOURCE_FILE ${CONFIG_OMNI_TARGET}/toolchain/gcc/stm32f103zetx_flash.ld)
    set(LS_TARGET_FILE ${OMNI_STARTUP_CFG_DIR}/stm32f103zetx_flash.ld)
else()
    message(FATAL_ERROR "CONFIG_OMNI_BOARD is not set")
endif()

set(TARGET_CORE_DEFINES
    ${COMPILE_DEFINITION}
)