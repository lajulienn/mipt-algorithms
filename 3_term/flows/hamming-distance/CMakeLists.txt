cmake_minimum_required(VERSION 3.6)

project(hamming_distance)

set(SOURCE_FILES main.cpp hamming_distance.h hamming_distance.cpp)

add_definitions(${flow-network_DEFINITIONS})

include_directories(${FLOW_NETWORK_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(hamming_distance flow-network)

# Google Tests
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(hamming-distance-test hamming_distance_test.cpp hamming_distance.cpp)
target_link_libraries(hamming-distance-test ${GTEST_BOTH_LIBRARIES})
target_link_libraries(hamming-distance-test flow-network)