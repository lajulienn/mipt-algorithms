/**
 * @author Julia Ivanova
 */

#include <cstdint>
#include <iostream>
#include <vector>

#include "kruskal_search.h"

int main() {
    uint16_t vertex_quantity;
    uint16_t edge_quantity;
    std::cin >> vertex_quantity >> edge_quantity;

    std::vector<Edge<uint64_t>> graph;
    graph.reserve(edge_quantity);
    for (uint32_t i = 0; i < edge_quantity; ++i) {
        uint16_t from, to;
        uint64_t weight;
        std::cin >> from >> to >> weight;
        graph.push_back(Edge<uint64_t>(from - 1, to - 1, weight));
    }

    std::vector<Edge<uint64_t>> mst = KruskalSearch<uint64_t>(graph, vertex_quantity);
    std::cout << TreeWeightCount<uint64_t>(mst);

    return 0;
}
