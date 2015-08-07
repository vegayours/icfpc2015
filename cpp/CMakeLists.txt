cmake_minimum_required(VERSION 2.8)

project(icfpc)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake", ${CMAKE_MODULE_PATH})

find_package(Folly REQUIRED)

include_directories(icfpc)

add_definitions(-std=c++11 -static)


add_subdirectory(icfpc)
add_subdirectory(test)
