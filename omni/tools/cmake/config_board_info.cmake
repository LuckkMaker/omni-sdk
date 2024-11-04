set(BOARD_PROPERTIES 
#  "board_name" "board_family" "board_target" "board_platform"

# stm32f1 family
    "stm32f103cb" "stm32f1" "stm32f103xx" "stm" 
    "stm32f103ze" "stm32f1" "stm32f103xx" "stm"

# stm32f4 family
    "stm32f405rg" "stm32f4" "stm32f405xx" "stm"
    "stm32f407ig" "stm32f4" "stm32f407xx" "stm"
    "stm32f411ce" "stm32f4" "stm32f411xx" "stm"

# stm32h7 family
    "stm32h743ii" "stm32h7" "stm32h743xx" "stm"
    "stm32h750vb" "stm32h7" "stm32h750xx" "stm"

# apm32f4 family
    # "apm32f405rg" "apm32f4" "apm32f405xx" "apm"
    "apm32f407ig" "apm32f4" "apm32f407xx" "apm"
)

set(BOARD_FOUND FALSE)

# 获取 BOARD_PROPERTIES 的长度
list(LENGTH BOARD_PROPERTIES num_properties)

# 计算有效的索引范围
math(EXPR max_index "${num_properties} - 1")

# 循环迭代
foreach(i RANGE 0 ${max_index} 4)
    list(GET BOARD_PROPERTIES ${i} element)
    if(BOARD MATCHES "^${element}")
        list(GET BOARD_PROPERTIES ${i} BOARD_NAME)
        
        math(EXPR index1 "${i} + 1")
        list(GET BOARD_PROPERTIES ${index1} BOARD_FAMILY)
        
        math(EXPR index2 "${i} + 2")
        list(GET BOARD_PROPERTIES ${index2} BOARD_TARGET)
        
        math(EXPR index3 "${i} + 3")
        list(GET BOARD_PROPERTIES ${index3} BOARD_PLATFORM)
        
        set(BOARD_FOUND TRUE)
        break()
    endif()
endforeach()

if(NOT BOARD_FOUND)
    message(FATAL_ERROR "Board not supported for ${BOARD}, Please specify it from top-level CMakeLists.txt\n"
        "Available boards options:\n"
        "  stm32f103cb  - Platform: stm, Family: stm32f1, Target: stm32f103xx\n"
        "  stm32f103ze  - Platform: stm, Family: stm32f1, Target: stm32f103xx\n"
        "  stm32f405rg  - Platform: stm, Family: stm32f4, Target: stm32f405xx\n"
        "  stm32f407ig  - Platform: stm, Family: stm32f4, Target: stm32f407xx\n"
        "  stm32f411ce  - Platform: stm, Family: stm32f4, Target: stm32f411xx\n"
        "  stm32h743ii  - Platform: stm, Family: stm32h7, Target: stm32h743xx\n"
        "  stm32h750vb  - Platform: stm, Family: stm32h7, Target: stm32h750xx\n"
        "  ------------------------------------------------------------------\n"
        "  apm32f407ig  - Platform: apm, Family: apm32f4, Target: apm32f407xx\n" 
        )
    message(STATUS "")
else()
    # message(STATUS "Board: ${BOARD_NAME}")
    # message(STATUS "Family: ${BOARD_FAMILY}")
    # message(STATUS "Target: ${BOARD_TARGET}")
    # message(STATUS "Platform: ${BOARD_PLATFORM}")

    set(CONFIG_OMNI_PLATFORM "${BOARD_PLATFORM}")
    set(CONFIG_OMNI_FAMILY "${BOARD_FAMILY}")
    set(CONFIG_OMNI_TARGET "${BOARD_TARGET}")
    set(CONFIG_OMNI_BOARD "${BOARD_NAME}")
endif()
