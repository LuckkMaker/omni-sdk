cmake_minimum_required(VERSION 3.26)

# Set the board to be used for omni
set(BOARD stm32f407ig)

# omni settings need to be set before including omni
find_package(OMNI REQUIRED HINTS $ENV{OMNI_BASE})
project(ram_boot)

include("cmake/driver.cmake")

target_sources(app INTERFACE
    ${DRIVER_CORE_SOURCES}
    # Add user sources here
    application/main.c
)

target_compile_definitions(app INTERFACE
    ${DRIVER_CORE_DEFINES}
    # Add user defined symbols
)

target_include_directories(app INTERFACE
    ${DRIVER_CORE_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}
    # Add user defined include paths
    application
)