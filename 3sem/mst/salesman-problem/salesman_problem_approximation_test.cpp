#include "salesman_problem_approximation_test.h"

#define _USE_MATH_DEFINES

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cfloat>
#include <cmath>
#include <functional>

TestAnswer::TestAnswer(double average_approx, double approx_rms_deviation) :
        average_approximation(average_approx),
        standard_deviation(approx_rms_deviation) {}

TestAnswer Test(int vertex_count, int test_count) {
    std::srand(std::time(0));
    double approximation_sum = 0;
    double square_approximation_sum = 0;
    for (int test = 0; test < test_count; ++test) {
        std::vector<std::vector<double>> adjacency_matrix = GenerateGraph(vertex_count);

        double real_answer = BrutForceSolution(vertex_count, adjacency_matrix);
        double approximate_answer = ApproximateSolution(vertex_count, adjacency_matrix);
        double approximation = approximate_answer - real_answer;
        approximation_sum += approximation;
        square_approximation_sum += approximation * approximation;
    }
    double average_approximation = approximation_sum / test_count;
    double approximation_rms_deviation = std::sqrt(square_approximation_sum/ test_count);

    return TestAnswer(average_approximation, approximation_rms_deviation);
}

std::vector<std::vector<double>> GenerateGraph(int vertex_count) {
    std::vector<std::vector<double>> adjacency_matrix(vertex_count, std::vector<double>(vertex_count));
    std::vector<std::pair<double, double>> vertices(vertex_count);
    for (auto &vertex : vertices) {
        vertex = GenerateVertex();
    }
    for (int i = 0; i < vertex_count; ++i) {
        for (int j = 0; j < vertex_count; ++j) {
            adjacency_matrix[i][j] = GetDistance(vertices[i], vertices[j]);
        }
    }
    return adjacency_matrix;
}

std::pair<double, double> GenerateVertex() {
    double r = std::rand();
    double phi = std::rand();
    if (r == 0) {
        r = 1;
    }
    if (phi == 0) {
        phi = 1;
    }
    r = 1 / r;
    phi = 1 / phi;

    double x = std::cos(2 * M_PI * phi) * std::sqrt(-2 * std::log(r));
    double y = std::sin(2 * M_PI * phi) * std::sqrt(-2 * std::log(r));

    return std::pair<double, double>(x, y);
}

double GetDistance(const std::pair<double, double> &x, const std::pair<double, double> &y) {
    return std::sqrt((x.first - y.first) * (x.first - y.first) +
                             (x.second - y.second) * (x.second - y.second));
}

double BrutForceSolution(int vertex_count, const std::vector<std::vector<double>> &adjacency_matrix) {
    std::vector<int> permutation(vertex_count);
    for (int i = 0; i < vertex_count; ++i) {
        permutation[i] = i;
    }

    double min_cycle_weight = FLT_MAX;
    while (std::next_permutation(permutation.begin(), permutation.end())) {
        double cycle_weight = GetCycleWeight(permutation, adjacency_matrix);
        if (cycle_weight < min_cycle_weight) {
            min_cycle_weight = cycle_weight;
        }
    }
    return min_cycle_weight;
};

double GetCycleWeight(const std::vector<int> &cycle, const std::vector<std::vector<double>> &adjacency_matrix) {
    double weight = 0;
    for (int i = 0; i < cycle.size() - 1; ++i) {
        int vertex = cycle[i];
        weight += adjacency_matrix[vertex][vertex + 1];
    }
    weight += adjacency_matrix[cycle[cycle.size() - 1]][cycle[0]];
    return weight;
}

double ApproximateSolution(int vertex_count, const std::vector<std::vector<double>> &adjacency_matrix) {
    std::vector<Edge<double>> source_graph;
    for (int i = 0; i < vertex_count; ++i) {
        for (int j = i ; j < vertex_count; ++j) {
            source_graph.emplace_back(i, j, adjacency_matrix[i][j]);
        }
    }
    std::vector<Edge<double>> mst = KruskalSearch<double>(source_graph, vertex_count);
    std::vector<int> cycle = RebuildMst(vertex_count, mst, adjacency_matrix);
    return GetCycleWeight(cycle, adjacency_matrix);
}

std::vector<int> RebuildMst(int vertex_count, const std::vector<Edge<double>> &mst,
                             const std::vector<std::vector<double>> &adjacency_matrix) {

    std::vector<int> cycle;

    int last_vertex_in_chain = 0;
    std::vector<bool> visited(vertex_count, false);

    std::function<void(int)> dfs = [&] (int vertex) {
        cycle.push_back(vertex);
        for (auto &edge : mst) {
            int neighbour = -1;
            if (edge.GetVertexFrom() == vertex && !visited[edge.GetVertexTo()]) {
                neighbour = edge.GetVertexTo();
            } else if (edge.GetVertexTo() == vertex && !visited[edge.GetVertexFrom()]) {
                neighbour = edge.GetVertexFrom();
            }
            if (neighbour != -1) {
                last_vertex_in_chain = neighbour;
                visited[neighbour] = true;
                dfs(neighbour);
            }
        }
    };

    dfs(last_vertex_in_chain);

    return cycle;
}