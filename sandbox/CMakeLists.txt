# Setup
find_package(SFML 2 REQUIRED graphics system window)

include_directories(
    "${PROJECT_SOURCE_DIR}/src"
    "${SFML_INCLUDE_DIR}"
)

# Targets
add_executable(braces
    braces.cpp
)

add_executable(umap
    umap.cpp
)

add_executable(blocks
    blocks.cpp
)
target_link_libraries(blocks
    "${SFML_LIBRARIES}"
)

add_executable(game_prototype
    game_prototype.cpp
    ${PROJECT_SOURCE_DIR}/src/Tetris/Game/Tetromino.cpp
)
target_link_libraries(game_prototype
    "${SFML_LIBRARIES}"
)
