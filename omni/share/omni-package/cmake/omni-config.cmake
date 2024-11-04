set(OMNI_BASE $ENV{OMNI_BASE})

string(REPLACE "\\" "/" OMNI_BASE $ENV{OMNI_BASE})
string(REGEX REPLACE "/$" "" OMNI_BASE ${OMNI_BASE})
set(OMNI_DIR ${OMNI_BASE}/share/omni-package/cmake CACHE PATH
"The directory containing a CMake configuration file for omni." FORCE
)

# message(STATUS "OMNI_DIR: ${OMNI_DIR}")

include(${OMNI_BASE}/CMakeLists.txt)