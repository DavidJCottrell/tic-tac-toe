# Setup

## Create the build directory

`mkdir build && cd build`

## Install dependencies with conan

`conan install .. --build=missing --output-folder=.`

## Generate build files

`cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release`

## Build

`cmake --build .`

## Run

`./TicTacToe`
