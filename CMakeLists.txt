# compile to a universal library when compiling for mac os
if(APPLE)
    set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64")
endif()

# add subdirectory for godot-cpp
add_subdirectory("godot-cpp" ${CMAKE_SOURCE_DIR}/godot-cpp/)

# this project
cmake_minimum_required(VERSION 3.18)
project(fourinarow CXX)
set(CMAKE_CXX_STANDARD 14)
set(BUILD_PATH ${CMAKE_SOURCE_DIR}/FourInARow/GDNativeLibraries/)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${BUILD_PATH}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${BUILD_PATH}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${BUILD_PATH}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${BUILD_PATH}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BUILD_PATH}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${BUILD_PATH}")

# include files
include_directories(fourinarow 
    ${CMAKE_SOURCE_DIR}/godot-cpp/godot-headers/
    ${CMAKE_SOURCE_DIR}/godot-cpp/include/
    ${CMAKE_SOURCE_DIR}/godot-cpp/include/core/
    ${CMAKE_SOURCE_DIR}/godot-cpp/include/gen/
)

# add source files
file(GLOB_RECURSE script-source "scripts-source/*.cpp")
file(GLOB_RECURSE script-headers "scripts-source/*.h**")

# shared library
add_library(fourinarow SHARED ${script-source} ${script-headers})

# link godot-cpp with fourinarow script library
target_link_libraries(fourinarow godot-cpp)