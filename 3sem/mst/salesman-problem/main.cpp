#include <iostream>

#include "salesman_problem_approximation_test.h"

const int lower_bound = 4;
const int upper_bound = 7;
const int test_count = 100;

int main() {
    std::cout.width(12); std::cout << std::left << "vertex num";
    std::cout.width(15); std::cout << std::left << "approximation";
    std::cout.width(15); std::cout<< std::left << "standard_deviation" << std::endl;

    for (int vertex_count = lower_bound; vertex_count <= upper_bound; ++vertex_count) {
        TestAnswer test = Test(vertex_count, test_count);

        std::cout.width(12); std::cout << std::left << vertex_count;
        std::cout.width(15); std::cout << std::left << test.average_approximation;
        std::cout.width(15); std::cout << std::left << test.standard_deviation << std::endl;
    }

    return 0;
}