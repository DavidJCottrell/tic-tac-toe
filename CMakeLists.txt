cmake_minimum_required(VERSION 3.13)
project(TicTacToe)

# Check if the Conan toolchain file exists and include it
if(EXISTS "${CMAKE_BINARY_DIR}/conan_toolchain.cmake")
    include("${CMAKE_BINARY_DIR}/conan_toolchain.cmake")
else()
    message(FATAL_ERROR "Conan toolchain file not found: ${CMAKE_BINARY_DIR}/conan_toolchain.cmake. Please run 'conan install .' first.")
endif()

if (APPLE)
    execute_process(COMMAND xcrun --show-sdk-path OUTPUT_VARIABLE CMAKE_OSX_SYSROOT OUTPUT_STRIP_TRAILING_WHITESPACE)
endif()


include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${CONAN_INCLUDE_DIRS})


find_package(SDL2 REQUIRED)


add_library(game_logic
    src/game_logic.c
    src/constants.c
    include/constants.h
    include/game_logic.h
)


add_executable(TicTacToe
    src/main.c
    src/rendering.c
    src/input.c
    include/input.h
    include/rendering.h
)

target_link_libraries(TicTacToe SDL2::SDL2 SDL2::SDL2main game_logic)


# GoogleTest
find_package(GTest REQUIRED)

set(TEST_SOURCES test/game_logic_test.cpp)

add_executable(runTests ${TEST_SOURCES})

target_link_libraries(runTests GTest::gtest GTest::gtest_main game_logic)

enable_testing()

add_test(NAME game_logic_test COMMAND runTests)