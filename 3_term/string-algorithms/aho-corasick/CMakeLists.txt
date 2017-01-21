cmake_minimum_required(VERSION 3.6)

project(aho-corasick)

set(SOURCE_FILES main.cpp)

add_definitions(${string-algo_DEFINITIONS})

include_directories(${string-algo_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} string-algo)
