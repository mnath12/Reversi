# CMake generated Testfile for 
# Source directory: /Users/moinak/Documents/College/Year 2/Spring 2023/CS 211-0/hw5
# Build directory: /Users/moinak/Documents/College/Year 2/Spring 2023/CS 211-0/hw5/cmake-build-debug
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(Test_model_test "model_test")
set_tests_properties(Test_model_test PROPERTIES  _BACKTRACE_TRIPLES "/Users/moinak/Documents/College/Year 2/Spring 2023/CS 211-0/hw5/.cs211/cmake/211commands.cmake;90;add_test;/Users/moinak/Documents/College/Year 2/Spring 2023/CS 211-0/hw5/CMakeLists.txt;25;add_test_program;/Users/moinak/Documents/College/Year 2/Spring 2023/CS 211-0/hw5/CMakeLists.txt;0;")
add_test(Test_helper_test "helper_test")
set_tests_properties(Test_helper_test PROPERTIES  _BACKTRACE_TRIPLES "/Users/moinak/Documents/College/Year 2/Spring 2023/CS 211-0/hw5/.cs211/cmake/211commands.cmake;90;add_test;/Users/moinak/Documents/College/Year 2/Spring 2023/CS 211-0/hw5/CMakeLists.txt;32;add_test_program;/Users/moinak/Documents/College/Year 2/Spring 2023/CS 211-0/hw5/CMakeLists.txt;0;")
subdirs(".cs211/lib/catch")
subdirs(".cs211/lib/ge211")
