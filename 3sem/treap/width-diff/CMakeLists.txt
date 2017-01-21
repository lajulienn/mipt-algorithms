cmake_minimum_required(VERSION 3.6)

project(width-diff)

set(SOURCE_FILES main.cpp)

add_definitions(${treap-and-binary-tree_DEFINITIONS})

include_directories(${treap-and-binary-tree_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} treap-and-binary-tree)
