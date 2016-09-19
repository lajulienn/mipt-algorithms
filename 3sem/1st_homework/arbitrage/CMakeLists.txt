cmake_minimum_required(VERSION 3.6)
project(1st_homework)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES trade_arbitrage.cpp)
add_executable(1st_homework ${SOURCE_FILES})