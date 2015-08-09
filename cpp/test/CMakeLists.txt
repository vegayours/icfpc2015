# setup gtest
add_subdirectory(gtest)

enable_testing()

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(SRC
    rng_test.cpp
    unit_test.cpp
)

# unit tests
add_executable(run_tests ${SRC})
target_link_libraries(run_tests gtest gtest_main icfpc_lib ${FOLLY_LIBRARY})
