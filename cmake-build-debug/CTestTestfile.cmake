# CMake generated Testfile for 
# Source directory: /home/david/projects/TicTacToe
# Build directory: /home/david/projects/TicTacToe/cmake-build-debug
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(game_logic_test "/home/david/projects/TicTacToe/cmake-build-debug/runTests")
set_tests_properties(game_logic_test PROPERTIES  _BACKTRACE_TRIPLES "/home/david/projects/TicTacToe/CMakeLists.txt;48;add_test;/home/david/projects/TicTacToe/CMakeLists.txt;0;")
subdirs("third_party/googletest")
