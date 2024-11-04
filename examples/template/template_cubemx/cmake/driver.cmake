# Driver core sources
file(GLOB_RECURSE DRIVER_CORE_SOURCES
    "driver/Core/Src/*.c"
)

# Driver core includes
set(DRIVER_CORE_INCLUDES
    "driver/Core/Inc"
)

# Driver defines
set(DRIVER_CORE_DEFINES
    "USE_HAL_DRIVER"
)