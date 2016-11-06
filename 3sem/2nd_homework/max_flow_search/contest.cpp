#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <string>
#include <set>
#include <climits>
#include <queue>

class Network {
public:
    Network(int source, int sink, int vertex_number);
    void AddEdge(int from, int to, int capacity);
    int MaxFlowSearch();
    std::vector<int> MinimalCut();
private:
    struct Edge {
        Edge(int v, int c);

        int to;
        int capacity;
        int flow;
    };

    bool Bfs();
    int Dfs(int vertex, int min_path_capacity);
    void UsualDfs(int vertex, std::vector<bool> &visited);

    int source_;
    int sink_;
    int vertex_number_;
    std::vector<std::vector<Edge>> adjacency_list_;
    std::vector<int> distance_;
    std::vector<int> first_not_deleted_edge_;
};

struct EmptySpace {
    EmptySpace() {};
    EmptySpace(int id) : id(id), comparisons_with_0(0), comparisons_with_1(0) {}

    int id;
    int comparisons_with_0;
    int comparisons_with_1;
    std::vector<int> spaces_compared;
    char symbol;
};

int FindDistance(std::string &string, std::string &pattern);
void BuildNetwork(Network &network, const std::map<int, EmptySpace> &string_spaces,
                  const std::map<int, EmptySpace> &pattern_spaces, int sink);

int main() {
    std::string string;
    std::string pattern;

    std::cin >> string >> pattern;

    std::cout << FindDistance(string, pattern) << std::endl;
    std::cout << string << std::endl;
    std::cout << pattern << std::endl;

    return 0;
}

Network::Network(int source, int sink, int vertex_number)
        : source_(source),
          sink_(sink),
          vertex_number_(vertex_number),
          distance_(std::vector<int>(vertex_number, INT_MAX)),
          first_not_deleted_edge_(std::vector<int>(vertex_number, 0)),
          adjacency_list_(std::vector<std::vector<Edge>>(vertex_number)) { }

Network::Edge::Edge(int v, int c) : to(v), capacity(c), flow(0) {}

void Network::AddEdge(int from, int to, int capacity) {
        bool exists = false;
        for (auto &edge : adjacency_list_[from]) {
            if (edge.to == to) {
                edge.capacity += capacity;
                exists = true;
                break;
            }
        }
        if (exists) {
            for (auto &edge : adjacency_list_[to]) {
                if (edge.to == from) {
                    edge.capacity += capacity;
                    break;
                }
            }
        } else {
            adjacency_list_[from].emplace_back(to, capacity);
            adjacency_list_[to].emplace_back(from, capacity);
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
int FindDistance(std::string &string, std::string &pattern) {
    int hamming_distance = 0;
    std::map<int, EmptySpace> string_spaces; // key is position of ? in a string
    std::map<int, EmptySpace> pattern_spaces;
    int id = 1;

    for (int shift = 0; shift < string.length() - pattern.length() + 1; ++shift) {
        for (int i = 0; i < pattern.length(); ++i) {
            char s1 = string[i + shift];
            char s2 = pattern[i];
            if (s1 != '?' && s2 != '?' && s1 != s2) {
                ++hamming_distance;
            } else if (s1 == '?' && s2 != '?') {
                if (string_spaces.find(i + shift) == string_spaces.end()) {
                    string_spaces[i + shift] = EmptySpace(id);
                    ++id;
                }
                if (s2 == '0') {
                    ++string_spaces[i + shift].comparisons_with_0;
                } else {
                    ++string_spaces[i + shift].comparisons_with_1;
                }
            } else if (s2 == '?' && s1 != '?') {
                if (pattern_spaces.find(i) == pattern_spaces.end()) {
                    pattern_spaces[i] = EmptySpace(id);
                    ++id;
                }
                if (s1 == '0') {
                    ++pattern_spaces[i].comparisons_with_0;
                } else {
                    ++pattern_spaces[i].comparisons_with_1;
                }
            } else if (s1 == '?' && s2 == '?') {
                if (pattern_spaces.find(i) == pattern_spaces.end()) {
                    pattern_spaces[i] = EmptySpace(id);
                    ++id;
                }
                int s2_id = string_spaces[i + shift].id;
                pattern_spaces[i].spaces_compared.push_back(s2_id);
            }
        }
    }
    const int source = 0;
    const int sink = id;
    Network network(source, sink, id + 1);
    BuildNetwork(network, string_spaces, pattern_spaces, sink);
    hamming_distance += network.MaxFlowSearch();
    std::vector<int> spaces_with_0 = network.MinimalCut();
    spaces_with_0.erase(spaces_with_0.begin());
    std::set<int> set_of_spaces_with_0(spaces_with_0.begin(), spaces_with_0.end());
    for (auto element : string_spaces) {
        int position = element.first;
        EmptySpace space = element.second;
        if (set_of_spaces_with_0.find(space.id) != set_of_spaces_with_0.end()) {
            string[position] = '0';
        } else {
            string[position] = '1';
        }
    }
    for (auto element : pattern_spaces) {
        int position = element.first;
        EmptySpace space = element.second;
        if (set_of_spaces_with_0.find(space.id) != set_of_spaces_with_0.end()) {
            pattern[position] = '0';
        } else {
            pattern[position] = '1';
        }
    }
    return hamming_distance;
}

void BuildNetwork(Network &network, const std::map<int, EmptySpace> &string_spaces,
                  const std::map<int, EmptySpace> &pattern_spaces, int sink) {
    const int source = 0;
    for (auto element : string_spaces) {
        EmptySpace space = element.second;
        network.AddEdge(source, space.id, space.comparisons_with_0);
        network.AddEdge(space.id, sink, space.comparisons_with_1);
        for (auto neighbor : space.spaces_compared) {
            network.AddEdge(space.id, neighbor, 1);
            network.AddEdge(neighbor, space.id, 1);
        }
    }
    for (auto element : pattern_spaces) {
        EmptySpace space = element.second;
        network.AddEdge(source, space.id, space.comparisons_with_0);
        network.AddEdge(space.id, sink, space.comparisons_with_1);
        for (auto neighbor : space.spaces_compared) {
            network.AddEdge(space.id, neighbor, 1);
            network.AddEdge(neighbor, space.id, 1);
        }
    }
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

std::vector<int> Network::MinimalCut() {
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

void Network::UsualDfs(int vertex, std::vector<bool> &visited) {
    visited[vertex] = true;
    for (auto &neighbor : adjacency_list_[vertex]) {
        if (!visited[neighbor.to] && neighbor.capacity > neighbor.flow) {
            UsualDfs(neighbor.to, visited);
        }
    }
}
