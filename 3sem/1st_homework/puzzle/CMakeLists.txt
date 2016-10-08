cmake_minimum_required(VERSION 3.6)
project(15_puzzle)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O0")

set(SOURCE_FILES main.cpp permutation.cpp permutation.h puzzle.cpp puzzle.h astar.cpp astar.h)
add_executable(15_puzzle ${SOURCE_FILES})