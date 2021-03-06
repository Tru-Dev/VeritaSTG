cmake_minimum_required(VERSION 3.18)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(APP_NAME VeritaSTG)

project(${APP_NAME})

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(WINDOWS TRUE)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(LINUX TRUE)
else()
    message(FATAL_ERROR "Only Windows and Linux are supported as of now.")
    return()
endif()

find_package(OpenGL REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS})

set(VERITA_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(VERITA_INCLUDE_DIR ${VERITA_SOURCE_DIR}/include)
set(VERITA_FRAMEWORKS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/frameworks)

include(deps.cmake)

include(src.cmake)

set(APP_SRC ${VERITA_SOURCE} ${VERITA_HEADERS} ${VERITA_FRAMEWORK_SOURCE})

include_directories(${VERITA_INCLUDE})

add_library(${APP_NAME}-lib STATIC ${APP_SRC})
target_link_libraries(${APP_NAME}-lib PRIVATE ${OPENGL_LIBRARIES} ${VERITA_LIBRARIES})
target_include_directories(${APP_NAME}-lib PRIVATE ${VCPKG_INCLUDE_DIR})
set_target_properties(
    ${APP_NAME}-lib PROPERTIES
    OUTPUT_NAME ${APP_NAME}
    MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"
)

if(LINUX)
    add_executable(${APP_NAME}-bin ${VERITA_SOURCE_DIR}/runtime/linux/main.cpp)
    target_link_libraries(${APP_NAME}-bin PRIVATE ${APP_NAME}-lib)
    set_target_properties(${APP_NAME}-bin PROPERTIES OUTPUT_NAME ${APP_NAME})
elseif(WINDOWS)
    set(WIN32_RUNTIME_DIR ${VERITA_SOURCE_DIR}/runtime/win32)
    set(CMAKE_EXE_LINKER_FLAGS
        "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup"
    )
    add_executable(${APP_NAME}-bin
        ${WIN32_RUNTIME_DIR}/main.cpp
        ${WIN32_RUNTIME_DIR}/resource.h
        ${WIN32_RUNTIME_DIR}/VeritaSTG.rc
    )
    target_link_libraries(${APP_NAME}-bin PRIVATE ${APP_NAME}-lib)
    set_target_properties(${APP_NAME}-bin PROPERTIES
        OUTPUT_NAME ${APP_NAME}
        MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"
    )
endif()
