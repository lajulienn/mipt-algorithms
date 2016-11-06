
#include <iostream>
#include <vector>
#include <climits>
#include <queue>

class Network {
public:
    Network(int source, int sink, int vertex_number, int edge_number);
    void AddEdge(int from, int to, int capacity);
    int MaxFlowSearch();
private:
    struct Edge {
        Edge(int v, int c) : to(v), capacity(c), flow(0) {}

        int to;
        int capacity;
        int flow;
    };

    bool Bfs();
    int Dfs(int vertex, int min_path_capacity);

    int source_;
    int sink_;
    int vertex_number_;
    int edge_number_;
    std::vector<std::vector<Edge>> adjacency_list_;
    std::vector<int> distance_;
    std::vector<int> first_not_deleted_edge_;
};


int main() {
    int vertex_quantity;
    std::cin >> vertex_quantity;
    //while (vertex_quantity != 0) {
        int source = 1;
        int sink;
        int edge_quantity;
        //std::cin >> source >> sink >> edge_quantity;
    std::cin >> edge_quantity;

        Network network(source - 1, vertex_quantity - 1, vertex_quantity, edge_quantity);

        for(int i = 0; i < edge_quantity; ++i) {
            int from;
            int to;
            int capacity;
            std::cin >> from >> to >> capacity;
            network.AddEdge(from - 1, to - 1, capacity);
        }

        std::cout << network.MaxFlowSearch();

        //std::cin >>vertex_quantity;
    //}
    
    return 0;
}

Network::Network(int source, int sink, int vertex_number, int edge_number)
        : source_(source),
          sink_(sink),
          vertex_number_(vertex_number),
          edge_number_(edge_number),
          distance_(std::vector<int>(vertex_number, INT_MAX)),
          first_not_deleted_edge_(std::vector<int>(vertex_number, 0)),
          adjacency_list_(std::vector<std::vector<Edge>>(vertex_number)) { }

void Network::AddEdge(int from, int to, int capacity) {
        bool exists = false;
        for (auto &edge : adjacency_list_[from]) {
            if (edge.to == to) {
                edge.capacity += capacity;
                exists = true;
                break;
            }
        }
        if (!exists) {
            adjacency_list_[from].emplace_back(to, capacity);
            adjacency_list_[to].emplace_back(from, 0);
        }
}

bool Network::Bfs() {
    distance_.assign(adjacency_list_.size(), INT_MAX);
    distance_[source_] = 0;

    std::queue<int> queue;
    queue.push(source_);
    while (!queue.empty()) {
        int vertex = queue.front();
        queue.pop();
        if (vertex == sink_) break;
        for (auto &edge : adjacency_list_[vertex]) {
            if (edge.flow < edge.capacity && distance_[edge.to] == INT_MAX) {
                distance_[edge.to] = distance_[vertex] + 1;
                queue.push(edge.to);
            }
        }
    }
    return distance_[sink_] != INT_MAX;
}


int Network::Dfs(int vertex, int min_path_capacity) {
    if (vertex == sink_ || min_path_capacity == 0) {
        return min_path_capacity;
    }

    for (int i = first_not_deleted_edge_[vertex]; i < adjacency_list_[vertex].size(); ++i) {
        Edge &edge = adjacency_list_[vertex][i];
        if (distance_[edge.to] == distance_[vertex] + 1) {
            int flow_growth = Dfs(edge.to, std::min(min_path_capacity, edge.capacity - edge.flow));
            if (flow_growth != 0) {
                edge.flow += flow_growth;
                for (auto &reversed : adjacency_list_[edge.to]) {
                    if (reversed.to == vertex) {
                        reversed.flow -= flow_growth;
                        break;
                    }
                }
                return flow_growth;
            }
        }
        ++first_not_deleted_edge_[vertex];
    }
    return 0;
}

int Network::MaxFlowSearch() {
    int max_flow = 0;

    while(Bfs()) {
        first_not_deleted_edge_.assign(vertex_number_, 0);
        int flow = Dfs(source_, INT_MAX);
        while(flow != 0) {
            max_flow += flow;
            flow = Dfs(source_, INT_MAX);
        }
    }
    return max_flow;
}
