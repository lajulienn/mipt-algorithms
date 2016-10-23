#include "floyd.h"

std::vector<std::vector<int>> floyd(const std::vector<std::vector<int>> &graph) {
    std::vector<std::vector<int>> distances = graph;

    for (int vertex = 0; vertex < distances.size(); ++vertex) {
        for (int u = 0; u < distances.size(); ++u) {
            for (int v = 0; v < distances.size(); ++v) {
                distances[u][v] = std::min(distances[u][v], distances[u][vertex] + distances[vertex][v]);
            }
        }
    }

    return distances;
}
