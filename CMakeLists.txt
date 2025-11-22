cmake_minimum_required(VERSION 4.0)
project(full)

set(CMAKE_CXX_STANDARD 26)

# Set default build type to Release
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

add_executable(full main.cpp functions.cpp functions.h
        game.cpp)
