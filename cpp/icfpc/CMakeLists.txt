set(LIB_SRC
    common/board.cpp
    emulator/load_board.cpp
    emulator/show_board.cpp
    emulator/load_units.cpp
)

add_library(icfpc_lib ${LIB_SRC})

add_executable(emulator_app emulator.cpp)
add_definitions(-ldouble-conversion -lglog)
target_link_libraries(emulator_app icfpc_lib double-conversion glog)

if (NOT USE_STATIC_FOLLY)
    #target_link_libraries(icfpc_main ${FOLLY_LIBRARY})
    target_link_libraries(emulator_app ${FOLLY_LIBRARY})
else()
    #target_link_libraries(icfpc_main folly_static)
    target_link_libraries(emulator_app folly_static)
endif()
