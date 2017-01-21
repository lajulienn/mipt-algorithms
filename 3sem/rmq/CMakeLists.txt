cmake_minimum_required(VERSION 3.6)
project(rmq)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp rmq.cpp rmq.h)

add_executable(rmq ${SOURCE_FILES})