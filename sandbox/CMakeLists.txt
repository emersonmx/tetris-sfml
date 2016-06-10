add_executable(braces
    braces.cpp
)

add_executable(umap
    umap.cpp
)

add_executable(blocks
    blocks.cpp
)
target_link_libraries(blocks ${EXTRA_LIBS})

add_executable(game_prototype
    game_prototype.cpp
    ${PROJECT_SOURCE_DIR}/src/MXG/Application.cpp
    ${PROJECT_SOURCE_DIR}/src/Tetris/Game/Tetromino.cpp
)
target_link_libraries(game_prototype ${EXTRA_LIBS})
