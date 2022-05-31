@echo off

call .\get_deps.bat

if not exist build mkdir build

cd build

cmake .. "-DCMAKE_TOOLCHAIN_FILE=.\vcpkg\scripts\buildsystems\vcpkg.cmake" "-DVCPKG_TARGET_TRIPLET=x64-windows-static"

cmake --build .
