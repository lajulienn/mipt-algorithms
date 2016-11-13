cmake_minimum_required(VERSION 3.6)
project(arbitrage)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp arbitrage_search.h arbitrage_search.cpp)
add_executable(arbitrage ${SOURCE_FILES})

# Google Tests
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(arbitrage_search_test arbitrage_search_test.cpp arbitrage_search.cpp)
target_link_libraries(arbitrage_search_test ${GTEST_BOTH_LIBRARIES})
