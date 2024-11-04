cmake_minimum_required(VERSION 3.26)

# specify cross-compilers and tools
set(CMAKE_C_STANDARD                11)
set(CMAKE_C_STANDARD_REQUIRED       ON)
set(CMAKE_C_EXTENSIONS              ON)
set(CMAKE_CXX_STANDARD              17)
set(CMAKE_CXX_STANDARD_REQUIRED     ON)
set(CMAKE_CXX_EXTENSIONS            ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS	ON)

if(NOT DEFINED APPLICATION_SOURCE_DIR)
    set(APPLICATION_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR} CACHE PATH "Application Source Directory")
endif()

if(NOT DEFINED BOARD)
    message(FATAL_ERROR "Board is not defined")
endif()

set(OMNI_PYTHON_SCRIPTS_DIR ${OMNI_BASE}/tools/python)
set(OMNI_CMAKE_SCRIPTS_DIR ${OMNI_BASE}/tools/cmake)
set(OMNI_KCONFIG_DIR ${CMAKE_BINARY_DIR}/omni/kconfig)
set(OMNI_SVD_DIR ${APPLICATION_SOURCE_DIR}/tools/svd)

# Generate boards Kconfig file in the build directory, because the Kconfig file can not be set some variables
# configure_file(${OMNI_BASE}/boards/Kconfig.in ${OMNI_BASE}/boards/Kconfig @ONLY)

# Accoding to the board name, set the platform, family, target and board name
include(${OMNI_CMAKE_SCRIPTS_DIR}/config_board_info.cmake)
include(${OMNI_CMAKE_SCRIPTS_DIR}/utils.cmake)

# After setting the board name, set the platform, family, target and board name
set(OMNI_BOARD_CFG_DIR ${APPLICATION_SOURCE_DIR}/omni/${CONFIG_OMNI_BOARD})
set(OMNI_FAMILY_DIR ${OMNI_BASE}/targets/${BOARD_PLATFORM}/${BOARD_FAMILY})

# Set the directories for the configuration files
set(OMNI_STARTUP_CFG_DIR ${OMNI_BOARD_CFG_DIR}/startup)
set(OMNI_DEVICE_CFG_DIR ${OMNI_BOARD_CFG_DIR}/device)
set(OMNI_DRIVER_CFG_DIR ${OMNI_BOARD_CFG_DIR}/driver)
set(OMNI_RTOS_CFG_DIR ${OMNI_BOARD_CFG_DIR}/rtos)
set(OMNI_USB_CFG_DIR ${OMNI_BOARD_CFG_DIR}/usb)
set(OMNI_CONSOLE_CFG_DIR ${OMNI_BOARD_CFG_DIR}/console)
set(OMNI_DEBUG_CFG_DIR ${OMNI_BOARD_CFG_DIR}/debug)

# message(STATUS "APPLICATION_SOURCE_DIR: ${APPLICATION_SOURCE_DIR}")

# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Run omni config script
include(${OMNI_CMAKE_SCRIPTS_DIR}/omni_config_scripts.cmake)

add_library(app INTERFACE)

set(OUTPUT_FILE_NAME "omni")
set(CMAKE_PROJECT_NAME omni)

include(${OMNI_CMAKE_SCRIPTS_DIR}/gcc_arm_none_eabi.cmake)

# Enable CMake support for ASM and C languages
enable_language(C ASM)

# Create an executable object type
add_executable(${CMAKE_PROJECT_NAME})

# Must add before the MCU specific flags
add_subdirectory(${OMNI_BASE}/targets ${CMAKE_BINARY_DIR}/omni/targets)

# MCU specific flags
if(NOT DEFINED TARGET_FLAGS)
    message(FATAL_ERROR "Target flags not defined")
endif()
message(STATUS "Target flags: ${TARGET_FLAGS}")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${TARGET_FLAGS}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mthumb -mthumb-interwork")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -ffunction-sections -fdata-sections -fno-common -fmessage-length=0")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-unused-function")  # Suppress unused function warnings
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-unused-parameter") # Suppress unused parameter warnings

if (CMAKE_BUILD_TYPE MATCHES Debug)
    message(STATUS "Debug optimization")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -g3")
elseif (CMAKE_BUILD_TYPE MATCHES RelWithDebInfo)
    message(STATUS "Maximum optimization for speed, debug info included")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Ofast -g")
elseif (CMAKE_BUILD_TYPE MATCHES Release)
    message(STATUS "Maximum optimization for speed")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Ofast")
elseif (CMAKE_BUILD_TYPE MATCHES MinSizeRel)
    message(STATUS "Maximum optimization for size")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Os -g0")
else ()
    message(STATUS "Minimal optimization, debug info included")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Og -g")
endif ()

set(CMAKE_ASM_FLAGS "${CMAKE_C_FLAGS} -x assembler-with-cpp -MMD -MP")
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -fno-rtti -fno-exceptions -fno-threadsafe-statics")

set(CMAKE_C_LINK_FLAGS "${TARGET_FLAGS}")

if(NOT DEFINED CONFIG_OMNI_DRIVER)
    if(NOT EXISTS ${LINKER_SCRIPT})
        message(FATAL_ERROR "Linker script not found: ${LINKER_SCRIPT}")
    endif()
    set(CMAKE_C_LINK_FLAGS "${CMAKE_C_LINK_FLAGS} -T ${LINKER_SCRIPT}")
endif()

set(CMAKE_C_LINK_FLAGS "${CMAKE_C_LINK_FLAGS} --specs=nano.specs")
set(CMAKE_C_LINK_FLAGS "${CMAKE_C_LINK_FLAGS} -Wl,-Map=${OUTPUT_FILE_NAME}.map -Wl,--gc-sections")
set(CMAKE_C_LINK_FLAGS "${CMAKE_C_LINK_FLAGS} -Wl,--start-group -lc -lm -Wl,--end-group")
set(CMAKE_C_LINK_FLAGS "${CMAKE_C_LINK_FLAGS} -Wl,--print-memory-usage")

set(CMAKE_CXX_LINK_FLAGS "${CMAKE_C_LINK_FLAGS}")

# include(${OMNI_CMAKE_SCRIPTS_DIR}/omni_default_config.cmake)

add_library(omni-interface INTERFACE)

add_library(omni-core INTERFACE)
add_library(omni-rtos INTERFACE)

target_link_libraries(omni-interface INTERFACE
    omni-rtos
    omni-core
)

target_include_directories(omni-interface INTERFACE
    ${OMNI_BASE}
    ${OMNI_KCONFIG_DIR}
    ${OMNI_DEVICE_CFG_DIR}
    ${OMNI_RTOS_CFG_DIR}
    ${OMNI_USB_CFG_DIR}
    ${OMNI_CONSOLE_CFG_DIR}
    ${OMNI_DEBUG_CFG_DIR}
)

add_subdirectory(${OMNI_BASE}/cmsis ${CMAKE_BINARY_DIR}/omni/cmsis)
add_subdirectory(${OMNI_BASE}/drivers ${CMAKE_BINARY_DIR}/omni/drivers)
# add_subdirectory(${OMNI_BASE}/targets ${CMAKE_BINARY_DIR}/omni/targets)
add_subdirectory(${OMNI_BASE}/components ${CMAKE_BINARY_DIR}/omni/components)
add_subdirectory(${OMNI_BASE}/libraries ${CMAKE_BINARY_DIR}/omni/libraries)

if(OMNI_TEST STREQUAL ON)
    add_subdirectory(test)
endif()

target_link_libraries(omni-core INTERFACE
    omni-cmsis
    omni-targets
    omni-components
)

if(NOT ${CONFIG_OMNI_DRIVER} STREQUAL "")
    target_link_libraries(omni-core INTERFACE
        omni-drivers
    )
endif()

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined library search paths
)

# Add sources to executable
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user sources here
)

# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined include paths
)

# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    $<$<CONFIG:Debug>:DEBUG>
    # Add user defined symbols
)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    app
    omni-interface
)

set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES OUTPUT_NAME ${OUTPUT_FILE_NAME})

set(HEX_FILE ${CMAKE_BINARY_DIR}/${OUTPUT_FILE_NAME}.hex)
set(BIN_FILE ${CMAKE_BINARY_DIR}/${OUTPUT_FILE_NAME}.bin)

add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${CMAKE_PROJECT_NAME}> ${HEX_FILE}
        COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${CMAKE_PROJECT_NAME}> ${BIN_FILE}
        COMMENT "Building ${HEX_FILE}
Building ${BIN_FILE}")

# Add custom command
include(${OMNI_CMAKE_SCRIPTS_DIR}/add_custom_command.cmake)