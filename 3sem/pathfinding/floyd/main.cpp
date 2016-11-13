#include <algorithm>
#include <iostream>
#include <vector>
#include <fstream>

#include "floyd.h"

int main() {
    std::ifstream in("floyd.in");
    std::ofstream out("floyd.out");
    int vertex_number;
    in >> vertex_number;

    std::vector<std::vector<int>> graph;
    graph.resize(vertex_number);
    for (int i = 0; i < vertex_number; ++i) {
        graph[i].resize(vertex_number);
    }
    for (int i = 0; i < vertex_number; ++i) {
        for (int j = 0; j < vertex_number; ++j) {
            in >> graph[i][j];
        }
    }

    auto distances = floyd(graph);

    for (int i = 0; i < vertex_number; ++i) {
        for (int j = 0; j < vertex_number; ++j) {
            out << distances[i][j] << " ";
        }
        out << std::endl;
    }

    return 0;
}
