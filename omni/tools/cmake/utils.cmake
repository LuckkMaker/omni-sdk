function(omni_lib_src lib source)
    target_sources(${lib} INTERFACE ${source} ${ARGN})
endfunction()

function(omni_lib_src_ifdef condition lib source)
    if(${${condition}})
      omni_lib_src(${lib} ${source} ${ARGN})
    endif()
endfunction()

function(omni_lib_inc lib include)
    target_include_directories(${lib} INTERFACE ${include} ${ARGN})
endfunction()

function(omni_lib_inc_ifdef condition lib include)
    if(${${condition}})
        omni_lib_inc(${lib} ${include} ${ARGN})
    endif()
endfunction()

function(omni_add_subdirectory_ifdef condition source_dir)
    if(${${condition}})
        add_subdirectory(${source_dir} ${ARGN})
    endif()
endfunction()

function(omni_lib_link_ifdef condition lib target)
    if(${${condition}})
        target_link_libraries(${lib} INTERFACE ${target})
    endif()
endfunction()

function(omni_add_configure_file source_file target_file)
    if(NOT EXISTS ${target_file})
        configure_file(${source_file} ${target_file} @ONLY)
    endif()
endfunction()

function(omni_set_linker_file target name path)
    set(LINKER_FILE_NAME ${name})
    set(LINKER_FILE_PATH ${path})

    set(LinkerScriptTarget ${LINKER_FILE_NAME}-ld)
    add_custom_target(${LinkerScriptTarget} DEPENDS ${LINKER_FILE_PATH} VERBATIM)
    add_dependencies(${target} ${LinkerScriptTarget})

    target_link_options(${target} INTERFACE
        "-T" "${LINKER_FILE_PATH}"
    )
endfunction()
