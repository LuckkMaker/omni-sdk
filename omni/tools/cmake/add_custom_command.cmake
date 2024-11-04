# add_custom_target(project-debug-make
#     COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Debug
#     COMMAND ${Python3_EXECUTABLE} ${OMNI_PYTHON_SCRIPTS_DIR}/clear_old_kconfig.py ${OMNI_BASE}/.config ${OMNI_BASE}/.config.old
#     COMMAND ${Python3_EXECUTABLE} ${OMNI_PYTHON_SCRIPTS_DIR}/kconfig.py --handwritten-input-configs ${OMNI_BASE}/Kconfig ${OMNI_BASE}/.config ${OMNI_KCONFIG_DIR}/omni_kconfig.h ${OMNI_KCONFIG_DIR}/kconfigLog.txt ${OMNI_BASE}/.config ${APPLICATION_SOURCE_DIR}/prj.conf
#     COMMAND ${Python3_EXECUTABLE} ${OMNI_PYTHON_SCRIPTS_DIR}/update_omni_kconfig_h.py
#     COMMAND ${Python3_EXECUTABLE} ${OMNI_PYTHON_SCRIPTS_DIR}/convert_kconfig_to_cmake.py
#     COMMENT "Reconfiguring CMake project with Debug build type"
#     WORKING_DIRECTORY ${OMNI_BASE}
# )

# add_custom_target(project-debug-clean
#     COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --config Debug --target clean
#     COMMENT "Cleaning up build directory"
#     WORKING_DIRECTORY ${OMNI_BASE}
# )

# add_custom_target(project-debug-build
#     COMMAND ${Python3_EXECUTABLE} ${OMNI_PYTHON_SCRIPTS_DIR}/clear_old_kconfig.py ${OMNI_BASE}/.config ${OMNI_BASE}/.config.old
#     COMMAND ${Python3_EXECUTABLE} ${OMNI_PYTHON_SCRIPTS_DIR}/kconfig.py --handwritten-input-configs ${OMNI_BASE}/Kconfig ${OMNI_BASE}/.config ${OMNI_KCONFIG_DIR}/omni_kconfig.h ${OMNI_KCONFIG_DIR}/kconfigLog.txt ${OMNI_BASE}/.config ${APPLICATION_SOURCE_DIR}/prj.conf
#     COMMAND ${Python3_EXECUTABLE} ${OMNI_PYTHON_SCRIPTS_DIR}/update_omni_kconfig_h.py
#     COMMAND ${Python3_EXECUTABLE} ${OMNI_PYTHON_SCRIPTS_DIR}/convert_kconfig_to_cmake.py
#     COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --config Debug --target all -- -j6
#     COMMENT "Reconfiguring and building project with MinGW in Debug mode"
#     WORKING_DIRECTORY ${OMNI_BASE}
# )

# add_custom_target(kconfig
#     COMMAND ${Python3_EXECUTABLE} ${OMNI_PYTHON_SCRIPTS_DIR}/clear_old_kconfig.py
#     COMMAND ${Python3_EXECUTABLE} ${OMNI_PYTHON_SCRIPTS_DIR}/kconfig.py ${OMNI_BASE}/Kconfig ${OMNI_BASE}/.config ${OMNI_BASE}/omni_kconfig.h ${OMNI_BASE}/kconfigLog.txt ${OMNI_BASE}/.config
#     COMMAND ${Python3_EXECUTABLE} ${OMNI_PYTHON_SCRIPTS_DIR}/convert_kconfig_to_cmake.py
#     COMMENT "Running kconfig.py script"
#     WORKING_DIRECTORY ${OMNI_BASE}
# )

add_custom_target(menuconfig
    COMMAND ${Python3_EXECUTABLE} ${OMNI_PYTHON_SCRIPTS_DIR}/run_menuconfig.py
    COMMENT "Running kconfig menuconfig"
    WORKING_DIRECTORY ${OMNI_BASE}
)

# add_custom_target(kconfig
#     COMMAND ${Python3_EXECUTABLE} ${OMNI_PYTHON_SCRIPTS_DIR}/clear_old_kconfig.py ${OMNI_BASE}/.config ${OMNI_BASE}/.config.old
#     COMMAND ${Python3_EXECUTABLE} ${OMNI_PYTHON_SCRIPTS_DIR}/kconfig.py --handwritten-input-configs ${OMNI_BASE}/Kconfig ${OMNI_BASE}/.config ${OMNI_KCONFIG_DIR}/omni_kconfig.h ${OMNI_KCONFIG_DIR}/kconfigLog.txt ${OMNI_BASE}/.config ${APPLICATION_SOURCE_DIR}/prj.conf
#     COMMAND ${Python3_EXECUTABLE} ${OMNI_PYTHON_SCRIPTS_DIR}/convert_kconfig_to_cmake.py
#     COMMENT "Running kconfig.py script with project configuration"
#     WORKING_DIRECTORY ${OMNI_KCONFIG_DIR}
# )
