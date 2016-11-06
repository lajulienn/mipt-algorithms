cmake_minimum_required(VERSION 3.6)
project(max_flow_search)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp max_flow.h max_flow.cpp main.cpp hamming_distance.h hamming_distance.cpp)
add_executable(max_flow_search ${SOURCE_FILES})