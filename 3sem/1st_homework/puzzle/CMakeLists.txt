cmake_minimum_required(VERSION 3.6)
project(15_puzzle)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -O0")

set(SOURCE_FILES main.cpp permutation.cpp permutation.h)
add_executable(15_puzzle ${SOURCE_FILES})

# Google Tests
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(15_puzzle_test permutation_test.cpp permutation.cpp)
target_link_libraries(15_puzzle_test ${GTEST_BOTH_LIBRARIES})
