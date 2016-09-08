# Setup
find_package(SFML 2 REQUIRED graphics system window)

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/Config.hpp.in"
    "${PROJECT_BINARY_DIR}/Config.hpp"
)

include_directories(
    "${SFML_INCLUDE_DIR}"
)

# Targets
add_executable(${PROJECT_NAME}
    Tetris/Main.cpp
    Tetris/Game/Tetromino.cpp
    Tetris/Game/Tetris.cpp

    Tetris/Assets.cpp

    Tetris/Utils.cpp
)
target_link_libraries(${PROJECT_NAME}
    "${SFML_LIBRARIES}"
)
