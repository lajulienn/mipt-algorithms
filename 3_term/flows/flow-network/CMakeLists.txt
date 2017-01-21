cmake_minimum_required(VERSION 3.6)

project (FLOW_NETWORK)
set(CMAKE_BUILD_TYPE Release)
set(SOURCE_LIB flow_network.cpp)

set(${PROJECT_NAME}_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include
        CACHE INTERNAL "")

include_directories(${${PROJECT_NAME}_INCLUDE_DIRS})

add_library(flow-network STATIC ${SOURCE_LIB})

# Google Tests
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(flow_network_test flow_network_test.cpp flow_network.cpp)
target_link_libraries(flow_network_test ${GTEST_BOTH_LIBRARIES})
