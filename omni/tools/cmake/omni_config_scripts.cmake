# Find Python3
find_package(Python3 REQUIRED Interpreter)

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/omni/kconfig)

# execute_process(
#     COMMAND ${Python3_EXECUTABLE} ${OMNI_PYTHON_SCRIPTS_DIR}/copy_kconfig_files.py ${BOARD} ${OMNI_KCONFIG_DIR}
#     WORKING_DIRECTORY ${OMNI_BASE}
#     RESULT_VARIABLE result
# )
# if(result)
#     message(FATAL_ERROR "copy_kconfig_files.py failed with exit code ${result}")
# endif()

execute_process(
    COMMAND ${Python3_EXECUTABLE} ${OMNI_PYTHON_SCRIPTS_DIR}/clear_old_kconfig.py ${OMNI_BASE}/.config ${OMNI_BASE}/.config.old
    WORKING_DIRECTORY ${OMNI_BASE}
    RESULT_VARIABLE result
)
if(result)
    message(FATAL_ERROR "remove_old_kconfig.py failed with exit code ${result}")
endif()

# Run kconfig.py script
execute_process(
    COMMAND ${Python3_EXECUTABLE} ${OMNI_PYTHON_SCRIPTS_DIR}/kconfig.py --handwritten-input-configs ${OMNI_BASE}/Kconfig ${OMNI_BASE}/.config ${OMNI_KCONFIG_DIR}/omni_kconfig.h ${OMNI_KCONFIG_DIR}/kconfigLog.txt ${OMNI_BASE}/.config ${APPLICATION_SOURCE_DIR}/prj.conf
    WORKING_DIRECTORY ${OMNI_BASE}
    RESULT_VARIABLE result
)
if(result)
    message(FATAL_ERROR "kconfig.py failed with exit code ${result}")
endif()

# Run update_omni_kconfig_h.py script
execute_process(
    COMMAND ${Python3_EXECUTABLE} ${OMNI_PYTHON_SCRIPTS_DIR}/update_omni_kconfig_h.py
    WORKING_DIRECTORY ${OMNI_KCONFIG_DIR}
    RESULT_VARIABLE result
)
if(result)
    message(FATAL_ERROR "update_omni_kconfig_h.py failed with exit code ${result}")
endif()

# After kconfig.py script, we need to convert Kconfig to CMake
execute_process(
    COMMAND ${Python3_EXECUTABLE} ${OMNI_PYTHON_SCRIPTS_DIR}/convert_kconfig_to_cmake.py
    WORKING_DIRECTORY ${OMNI_KCONFIG_DIR}
    RESULT_VARIABLE result
)
if(result)
    message(FATAL_ERROR "convert_kconfig_to_cmake.py failed with exit code ${result}")
endif()

include(${OMNI_KCONFIG_DIR}/omni_kconfig.cmake)

# Run update_omni_cmake_setting.py script
# execute_process(
#     COMMAND ${Python3_EXECUTABLE} ${OMNI_PYTHON_SCRIPTS_DIR}/update_omni_cmake_setting.py
#     WORKING_DIRECTORY ${OMNI_BASE}
#     RESULT_VARIABLE result
# )
# if(result)
#     message(FATAL_ERROR "update_omni_cmake_setting.py failed with exit code ${result}")
# endif()

# omni settings start
# include(${OMNI_CMAKE_SCRIPTS_DIR}/omni_option_setting.cmake)
# omni settings end
