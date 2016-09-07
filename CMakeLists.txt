# Project settings
cmake_minimum_required(VERSION 2.6)
project(tetris)

set(tetris_VERSION_MAJOR 0)
set(tetris_VERSION_MINOR 1)
set(tetris_VERSION_REVISION 0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

configure_file(
    "${PROJECT_SOURCE_DIR}/src/Tetris/Config.hpp.in"
    "${PROJECT_BINARY_DIR}/Config.hpp"
)

option(BUILD_SANDBOX "Build sandbox code" OFF)
option(BUILD_TESTS "Build tests" OFF)

# Compiler settings
if (CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE Debug)
endif()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic")
endif()

if (CMAKE_COMPILER_IS_GNUCC)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fmessage-length=0")
endif()
if (CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmessage-length=0")
endif()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__NO_INLINE__ -D_USE_MATH_DEFINES")
    set(CMAKE_EXE_LINKER_FLAGS "-Wl,--subsystem,windows")
endif()

# Includes and libraries settings
include(FindPkgConfig)

# Executable settings
include_directories(
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_BINARY_DIR}
)

add_subdirectory(src)
add_subdirectory(lib)

if (BUILD_SANDBOX)
    add_subdirectory(sandbox)
endif()

if (BUILD_TESTS)
    add_subdirectory(test)
endif()
