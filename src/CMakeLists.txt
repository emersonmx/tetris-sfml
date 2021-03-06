# Setup
find_package(SFML 2 REQUIRED graphics system window audio)

include_directories(
    "${SFML_INCLUDE_DIR}"
)

# Targets
add_executable(${PROJECT_NAME}
    Tetris/Main.cpp
    Tetris/App.cpp

    Tetris/States/DefaultState.cpp
    Tetris/States/GameState.cpp
    Tetris/States/MainMenuState.cpp

    Tetris/GameObjects/BlockRenderer.cpp
    Tetris/GameObjects/RandomMiniBlocks.cpp
    Tetris/GameObjects/Tetromino.cpp
    Tetris/GameObjects/GameArea.cpp
    Tetris/GameObjects/GameMenu.cpp
    Tetris/GameObjects/GameOver.cpp

    Tetris/Game/Tetromino.cpp
    Tetris/Game/Tetris.cpp

    Tetris/Assets.cpp
    Tetris/Utils.cpp

    # mxg
    mxg/Application.cpp
    mxg/Game.cpp
)
target_link_libraries(${PROJECT_NAME}
    "${SFML_LIBRARIES}"
)
