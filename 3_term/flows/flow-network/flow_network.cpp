/**
 * @author Julia Ivanova
 */

#include "include/flow_network.h"

#include <climits>
#include <queue>

FlowNetwork::FlowNetwork(int source, int sink, int vertex_number)
        : source_(source),
          sink_(sink),
          vertex_number_(vertex_number),
          distance_(std::vector<int>(vertex_number, INT_MAX)),
          first_not_deleted_edge_(std::vector<int>(vertex_number, 0)),
          adjacency_list_(std::vector<std::vector<Edge>>(vertex_number)) {}

FlowNetwork::Edge::Edge(int v, int c) : to(v), capacity(c), flow(0) {}

void FlowNetwork::AddEdge(int from, int to, int capacity) {
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

bool FlowNetwork::Bfs() {
    distance_.assign(adjacency_list_.size(), INT_MAX);
    distance_[source_] = 0;

    std::queue<int> queue;
    queue.push(source_);
    while (!queue.empty()) {
        int vertex = queue.front();
        queue.pop();
        for (auto &edge : adjacency_list_[vertex]) {
            if (edge.flow < edge.capacity && distance_[edge.to] == INT_MAX) {
                distance_[edge.to] = distance_[vertex] + 1;
                queue.push(edge.to);
            }
        }
    }
    return distance_[sink_] != INT_MAX;
}


int FlowNetwork::Dfs(int vertex, int min_path_capacity) {
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

int FlowNetwork::MaxFlowSearch() {
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

std::vector<int> FlowNetwork::MinimalCut() {
    std::vector<bool> visited(vertex_number_, false);
    UsualDfs(source_, visited);

    std::vector<int> min_cut;
    for (int i = 0; i < vertex_number_; ++i) {
        if(visited[i]) {
            min_cut.push_back(i);
        }
    }
    return min_cut;
}

void FlowNetwork::UsualDfs(int vertex, std::vector<bool> &visited) {
    visited[vertex] = true;
    for (auto &neighbor : adjacency_list_[vertex]) {
        if (!visited[neighbor.to] && neighbor.capacity > neighbor.flow) {
            UsualDfs(neighbor.to, visited);
        }
    }
}
