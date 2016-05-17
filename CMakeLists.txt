# Project settings
cmake_minimum_required(VERSION 2.6)
project(tetris)

set(tetris_VERSION_MAJOR 0)
set(tetris_VERSION_MINOR 0)
set(tetris_VERSION_REVISION 0)

configure_file(
    "${PROJECT_SOURCE_DIR}/src/Tetris/Config.hpp.in"
    "${PROJECT_BINARY_DIR}/Config.hpp"
)

# Compiler settings
if (CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE Debug)
endif()

if (WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__NO_INLINE__ -D_USE_MATH_DEFINES")
    set(CMAKE_EXE_LINKER_FLAGS "-Wl,--subsystem,windows")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
if (CMAKE_COMPILER_IS_GNUCC)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fmessage-length=0")
endif()
if (CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmessage-length=0")
endif()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Includes and libraries settings
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

include(FindPkgConfig)

find_package(SFML 2 REQUIRED graphics system window)
if (SFML_FOUND)
    set(EXTRA_INCLUDES ${EXTRA_INCLUDES} ${SFML_INCLUDE_DIR})
    set(EXTRA_LIBS ${EXTRA_LIBS} ${SFML_LIBRARIES})
endif()

# Executable settings
include_directories(${PROJECT_SOURCE_DIR}/src
    ${PROJECT_BINARY_DIR}
    ${EXTRA_INCLUDES}
)

add_executable(${PROJECT_NAME}
    src/Tetris/Main.cpp
    src/Tetris/Game/Tetris.cpp
    src/Tetris/Game/Tetromino.cpp

    src/MXG/Application.cpp
    src/MXG/Game.cpp
    src/MXG/Random.cpp
)

target_link_libraries(${PROJECT_NAME}
    ${EXTRA_LIBS}
)
