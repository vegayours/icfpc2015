set(LIB_SRC
    stub_fun.cpp
)

add_library(icfpc_lib ${LIB_SRC})

include_directories(${FOLLY_INCLUDE_DIR})
add_executable(icfpc_main main.cpp)
target_link_libraries(icfpc_main ${FOLLY_LIBRARY} icfpc_lib)
