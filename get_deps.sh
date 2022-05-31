
if [ ! -f vcpkg/vcpkg ]; then vcpkg/bootstrap-vcpkg.sh; fi


vcpkg/vcpkg install \
    boost-dll:x64-linux \
    boost-iostreams:x64-linux \
    boost-locale:x64-linux \
    fmt:x64-linux \
    glfw3:x64-linux