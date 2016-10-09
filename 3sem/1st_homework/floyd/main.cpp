#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>
#include <fstream>

void floyd(std::vector<std::vector<int>> &graph);
using std::cin;
using std::cout;

int main() {
    std::ifstream in("floyd.in");
    std::ofstream out("floyd.out");
    int n;
    in >> n;

    std::vector<std::vector<int>> graph;
    graph.resize(n);
    for (int i = 0; i < n; ++i) {
        graph[i].resize(n);
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            in >> graph[i][j];
        }
    }

    floyd(graph);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            out << graph[i][j] << " ";
        }
        out << std::endl;
    }

    return 0;
}

void floyd(std::vector<std::vector<int>> &graph) {
    for (int k = 0; k < graph.size(); ++k) {
        for (int i = 0; i < graph.size(); ++i) {
            for (int j = 0; j < graph.size(); ++j) {
                graph[i][j] = std::min(graph[i][j], graph[i][k] + graph[k][j]);
            }
        }
    }
    return;
}