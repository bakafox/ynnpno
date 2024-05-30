cmake_minimum_required(VERSION 3.10)

add_executable(bitset_tests tests.cpp)
target_include_directories(bitset_tests PUBLIC ../include ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
target_link_libraries(bitset_tests bitset gtest_main)

add_test(NAME bitset_tests COMMAND bitset_tests)
