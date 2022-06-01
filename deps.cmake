
set(VCPKG_INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/installed)

if(WIN32)
    set(VCPKG_INCLUDE_DIR ${VCPKG_INSTALL_DIR}/x64-windows-static/include)
endif()
if(LINUX)
    set(VCPKG_INCLUDE_DIR ${VCPKG_INSTALL_DIR}/x64-linux/include)
endif()

set(Boost_INCLUDE_DIR ${VCPKG_INCLUDE_DIR})

find_package(Boost COMPONENTS iostreams REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

add_subdirectory(${VERITA_FRAMEWORKS_DIR}/Boxer)

set(VERITA_LIBRARIES
    Boost::boost
    Boost::iostreams
    Boxer
    fmt::fmt
    glfw
)
