cmake_minimum_required(VERSION 3.6)
project(arbitrage)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp arbitrage_search.h arbitrage_search.cpp)
add_executable(arbitrage ${SOURCE_FILES})