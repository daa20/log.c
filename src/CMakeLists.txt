cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(test LANGUAGES C)

option(USE_LIBRARY "Compile sources into a library" OFF)

message(STATUS "Compile sources into a library? ${USE_LIBRARY}")

include(CMakeDependentOption)

#
cmake_dependent_option(
    MAKE_STATIC_LIBRARY "Compile sources into a static library" ON
    "USE_LIBRARY" ON
    )

cmake_dependent_option(
    MAKE_SHARED_LIBRARY "Compile sources into a shared library?" OFF
    "USE_LIBRARY" ON
    )

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

list(APPEND 
    lib_sources 
    log.c
    log.h
    )

if (USE_LIBRARY) 
    if (MAKE_SHARED_LIBRARY)
        message(STATUS "Compile sources into a shared library? ${MAKE_SHARED_LIBRARY}")
        add_library(
            log 
            SHARED
            ${lib_sources}
            )
    endif()

    if (MAKE_STATIC_LIBRARY)
        message(STATUS "Compile sources into a static library? ${MAKE_STATIC_LIBRARY}")
        add_library(
            log
            STATIC
            ${lib_sources}
            )
    endif()
    add_executable(test1 test1.c)
    target_link_libraries(test1 log)
else()
    add_executable(test1 test1.c ${lib_sources})
endif()

