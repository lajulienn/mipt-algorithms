cmake_minimum_required(VERSION 3.6)

project(find-max-flow)

set(SOURCE_FILES main.cpp)

add_definitions(${flow-network_DEFINITIONS})

include_directories(${FLOW_NETWORK_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(find-max-flow flow-network)