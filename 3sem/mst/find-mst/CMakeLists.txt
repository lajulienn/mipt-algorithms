cmake_minimum_required(VERSION 3.6)

project(find-mst)

set(SOURCE_FILES main.cpp)

add_definitions(${kruskal_DEFINITIONS})

include_directories(${kruskal_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(find-mst kruskal)