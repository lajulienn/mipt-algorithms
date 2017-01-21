cmake_minimum_required(VERSION 3.6)

project (kruskal)
set(CMAKE_BUILD_TYPE Release)
set(SOURCE_LIB kruskal_search.cpp)

set(${PROJECT_NAME}_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include
        CACHE INTERNAL "")

include_directories(${${PROJECT_NAME}_INCLUDE_DIRS})

add_library(kruskal STATIC ${SOURCE_LIB})