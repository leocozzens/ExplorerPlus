cmake_minimum_required(VERSION 3.15)
project(ExplorerPlus VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SCRIPT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(${SCRIPT_DIR}/remotes.cmake)
include(${SCRIPT_DIR}/compile.cmake)

set(BIN_DIR ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(LIB_DIR ${CMAKE_CURRENT_BINARY_DIR}/lib)
set(SYM_DIR ${CMAKE_CURRENT_BINARY_DIR}/symbols)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY      ${BIN_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY      ${LIB_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY      ${LIB_DIR})
set(CMAKE_COMPILE_PDB_OUTPUT_DIRECTORY  ${SYM_DIR})
set(CMAKE_PDB_OUTPUT_DIRECTORY          ${SYM_DIR})

set(MODULES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/modules)
set(MODULES app)
include_directories(${MODULES_DIR})
foreach(MODULE ${MODULES})
    add_subdirectory(${MODULES_DIR}/${MODULE})
endforeach()

set(LOCAL_TARGETS ${PROJECT_NAME})
foreach(TARGET IN LISTS LOCAL_TARGETS)
    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        target_compile_definitions(${TARGET} PUBLIC RELEASE_BUILD NDEBUG)
        if(MSVC)
            set_target_properties(${TARGET} PROPERTIES LINK_FLAGS "/INCREMENTAL:NO")
        endif()
        message(STATUS "Added release preprocessor macros.")
    elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_compile_definitions(${TARGET} PUBLIC DEBUG_BUILD)
        if (MSVC)
            target_compile_options(${TARGET} PRIVATE
                /Zi            # debug symbols
                /Od            # disable optimizations
                /W4            # warning level 4 (MSVC equivalent of -Wall)
                /WX            # treat warnings as errors
                /permissive-   # enforce standard conformance
            )
        else()
            target_compile_options(${TARGET} PRIVATE
                -g             # debug symbols
                -O0            # disable optimizations
                -Wall          # enable most warnings
                -Wextra        # extra warnings
                -Wpedantic     # enforce standard conformance
                -Werror        # treat all warnings as errors
                -fsanitize=address,undefined -fno-omit-frame-pointer
            )
            target_link_options(${TARGET} PRIVATE -fsanitize=address,undefined)
        endif()
        message(STATUS "Added debug preprocessor macros.")
    endif()
endforeach()