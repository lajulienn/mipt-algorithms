cmake_minimum_required(VERSION 3.6)
project(floyd)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp floyd.cpp floyd.h)
add_executable(floyd ${SOURCE_FILES})

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(floyd_test floyd.cpp floyd_test.cpp)
target_link_libraries(floyd_test ${GTEST_BOTH_LIBRARIES})
