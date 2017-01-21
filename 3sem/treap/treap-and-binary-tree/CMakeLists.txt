cmake_minimum_required(VERSION 3.6)

project (treap-and-binary-tree)
set(CMAKE_BUILD_TYPE Release)

set(SOURCE_LIB binary_tree.cpp treap.cpp)

set(${PROJECT_NAME}_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include
        CACHE INTERNAL "")

include_directories(${${PROJECT_NAME}_INCLUDE_DIRS})

add_library(${PROJECT_NAME} STATIC ${SOURCE_LIB})


# Google Tests
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
