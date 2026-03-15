
cmake -P Mingw64_Configuration.cmake

cmake -DCMAKE_BUILD_TYPE=Debug -S . -B .\BUILD -G "MinGW Makefiles"