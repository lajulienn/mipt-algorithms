cmake_minimum_required(VERSION 3.6)

project(salesman-problem)

set(SOURCE_FILES main.cpp salesman_problem_approximation_test.cpp salesman_problem_approximation_test.h)

add_definitions(${kruskal_DEFINITIONS})

include_directories(${kruskal_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(salesman-problem kruskal)