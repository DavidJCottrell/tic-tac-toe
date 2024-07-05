cmake_minimum_required(VERSION 3.13)
project(TicTacToe)

include_directories(${PROJECT_SOURCE_DIR}/include)

find_package(SDL2 REQUIRED)

add_executable(TicTacToe
    src/main.c
    src/rendering.c
    src/input.c
    src/game_logic.c
    src/constants.c
    include/constants.h
    include/game_logic.h
    include/input.h
    include/rendering.h
)

target_link_directories(TicTacToe PRIVATE ${SDL2_LIBRARY_DIR})
target_link_libraries(TicTacToe PUBLIC SDL2 SDL2_mixer SDL2_image)