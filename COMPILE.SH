cmake -S . -B build
cmake --build build
cd build && ctest
cd ../src && ./bitset_example
