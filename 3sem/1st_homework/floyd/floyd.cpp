//
// Created by julia on 09.10.16.
//
#include "floyd.h"

void floyd(std::vector<std::vector<int>> &graph) {
    for (int vertex = 0; vertex < graph.size(); ++vertex) {
        for (int u = 0; u < graph.size(); ++u) {
            for (int v = 0; v < graph.size(); ++v) {
                graph[u][v] = std::min(graph[u][v], graph[u][vertex] + graph[vertex][v]);
            }
        }
    }
    return;
}