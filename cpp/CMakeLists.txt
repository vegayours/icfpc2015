cmake_minimum_required(VERSION 2.8)

project(icfpc)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake" ${CMAKE_MODULE_PATH})

if (USE_DYNAMIC_FOLLY)
    find_package(Folly REQUIRED)
else()
    add_library(folly_static STATIC IMPORTED)
    set_target_properties(folly_static PROPERTIES
        IMPORTED_LOCATION /usr/local/lib/libfolly.a
    )
    add_definitions(-static)
endif()

include_directories(icfpc)

add_definitions(-std=c++11 -lglog -ldouble-conversion)

add_subdirectory(icfpc)
add_subdirectory(test)
