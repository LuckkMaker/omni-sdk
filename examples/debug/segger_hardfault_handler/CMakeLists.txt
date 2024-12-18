cmake_minimum_required(VERSION 3.26)

# Set the board to be used for omni
set(BOARD stm32f407ig)

# omni settings need to be set before including omni
find_package(OMNI REQUIRED HINTS $ENV{OMNI_BASE})
project(segger_hardfault_handler)

target_sources(app INTERFACE
    # Add user sources here
    application/main.c
    application/SEGGER_HardFaultHandler.c
    application/HardFaultHandler.S
)

target_compile_definitions(app INTERFACE
    # Add user defined symbols
)

target_include_directories(app INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
    # Add user defined include paths
    application
)