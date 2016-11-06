/**
 * @author Julia Ivanova
 */

#ifndef INC_MAX_FLOW_SEARCH_MAX_FLOW_H_
#define INC_MAX_FLOW_SEARCH_MAX_FLOW_H_

#include <vector>

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

#endif //INC_MAX_FLOW_SEARCH_MAX_FLOW_H_
