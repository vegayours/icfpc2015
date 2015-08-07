cmake_minimum_required(VERSION 2.8)

project(icfpc)

include_directories(icfpc)
add_definitions(-std=c++11)

add_subdirectory(icfpc)
add_subdirectory(test)
