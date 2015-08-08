set(LIB_SRC
    common/board.cpp
    common/unit.cpp
    game/game.cpp
    game/stupid.cpp
    game/unit_stream.cpp
    emulator/load.cpp
    emulator/show_board.cpp
)

add_library(icfpc_lib ${LIB_SRC})

add_executable(emulator emulator/emulator.cpp)
add_executable(solver solver.cpp)
add_definitions(-ldouble-conversion -lglog)
target_link_libraries(emulator icfpc_lib double-conversion glog)
target_link_libraries(solver icfpc_lib double-conversion glog)

if (NOT USE_STATIC_FOLLY)
    #target_link_libraries(icfpc_main ${FOLLY_LIBRARY})
    target_link_libraries(emulator ${FOLLY_LIBRARY})
    target_link_libraries(solver ${FOLLY_LIBRARY})
else()
    #target_link_libraries(icfpc_main folly_static)
    target_link_libraries(emulator folly_static)
    target_link_libraries(solver folly_static)
endif()
