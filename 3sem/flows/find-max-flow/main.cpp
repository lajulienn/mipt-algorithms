/**
 * @author Julia Ivanova
 */

#include <iostream>

#include "flow_network.h"

int main() {
    int vertex_quantity;
    std::cin >> vertex_quantity;
    while (vertex_quantity != 0) {
        int source;
        int sink;
        int edge_quantity;
        std::cin >> source >> sink >> edge_quantity;

        FlowNetwork network(source - 1, sink - 1, vertex_quantity);

        for(int i = 0; i < edge_quantity; ++i) {
            int from;
            int to;
            int capacity;
            std::cin >> from >> to >> capacity;
            network.AddEdge(from - 1, to - 1, capacity);
            network.AddEdge(to - 1, from - 1, capacity);
        }

        std::cout << network.MaxFlowSearch();

        std::cin >>vertex_quantity;
    }
    
    return 0;
}