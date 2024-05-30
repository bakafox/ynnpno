cmake_minimum_required(VERSION 3.10)

add_library(bitset bitset.cpp)
target_include_directories(bitset PUBLIC ../include)

add_executable(bitset_example main.cpp)
target_link_libraries(bitset_example bitset)
