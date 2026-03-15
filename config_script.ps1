
cmake -P mingw64_configuration.cmake

cmake -DCMAKE_BUILD_TYPE=Debug -S . -B .\BUILD -G "MinGW Makefiles"