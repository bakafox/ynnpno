cmake_minimum_required(VERSION 3.10)

add_executable(bitset_tests tests.cpp)
target_include_directories(bitset_tests PUBLIC ../include)
target_link_libraries(bitset_tests bitset)

add_test(NAME bitset_tests COMMAND bitset_tests)
