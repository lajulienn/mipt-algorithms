#ifndef SALESMAN_PROBLEM_SALESMAN_PROBLEM_APPROXIMATION_TEST_H
#define SALESMAN_PROBLEM_SALESMAN_PROBLEM_APPROXIMATION_TEST_H

#include <vector>
#include "kruskal_search.h"

struct TestAnswer {
    TestAnswer(double average_approx, double approx_rms_deviation);
    double average_approximation;
    double standard_deviation;
};

TestAnswer Test(int vertex_count, int test_count);
std::vector<std::vector<double>> GenerateGraph(int vertex_count);
std::pair<double, double> GenerateVertex();
double GetDistance(const std::pair<double, double> &x, const std::pair<double, double> &y);
double BrutForceSolution(int vertex_count, const std::vector<std::vector<double>> &adjacency_matrix);
double GetCycleWeight(const std::vector<int> &cycle, const std::vector<std::vector<double>> &adjacency_matrix);
double ApproximateSolution(int vertex_count, const std::vector<std::vector<double>> &adjacency_matrix);
std::vector<int> RebuildMst(int vertex_count, const std::vector<Edge<double>> &mst,
                             const std::vector<std::vector<double>> &adjacency_matrix);

#endif //SALESMAN_PROBLEM_SALESMAN_PROBLEM_APPROXIMATION_TEST_H
