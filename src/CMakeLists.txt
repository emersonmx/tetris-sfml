# Setup
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/Config.hpp.in"
    "${PROJECT_BINARY_DIR}/Config.hpp"
)

# Targets
add_executable(${PROJECT_NAME}
    Tetris/Main.cpp
    Tetris/Game/Tetromino.cpp
    Tetris/Game/Tetris.cpp
)
