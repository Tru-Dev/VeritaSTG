@echo off

if not exist vcpkg\vcpkg.exe call vcpkg\bootstrap-vcpkg.bat

vcpkg\vcpkg install ^
    boost-dll:x64-windows-static ^
    boost-iostreams:x64-windows-static ^
    boost-locale:x64-windows-static ^
    fmt:x64-windows-static ^
    glfw3:x64-windows-static

