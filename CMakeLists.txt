cmake_minimum_required(VERSION 3.13)
project(TicTacToe)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Find SDL2 package
find_package(SDL2 REQUIRED)

# Add the game logic library
add_library(game_logic
    src/game_logic.c
    src/constants.c
    include/constants.h
    include/game_logic.h
)

# Add the executable for the main application
add_executable(TicTacToe
    src/main.c
    src/rendering.c
    src/input.c
    include/input.h
    include/rendering.h
)

# Link the game logic library to the main application
target_link_libraries(TicTacToe PUBLIC SDL2 SDL2_mixer SDL2_image game_logic)

# Google Test
# Add GoogleTest directory
add_subdirectory(third_party/googletest)
include_directories(third_party/googletest/googletest/include)

# Test sources
set(TEST_SOURCES test/game_logic_test.cpp)

# Add the test executable
add_executable(runTests ${TEST_SOURCES})

# Link the test executable against gtest, gtest_main, and the game logic library
target_link_libraries(runTests gtest gtest_main game_logic)

# Enable testing
enable_testing()

# Add tests
add_test(NAME game_logic_test COMMAND runTests)
