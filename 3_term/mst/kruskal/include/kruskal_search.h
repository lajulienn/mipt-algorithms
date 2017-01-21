#ifndef MST_KRUSKAL_KRUSKAL_SEARCH_H_
#define MST_KRUSKAL_KRUSKAL_SEARCH_H_

#include <algorithm>
#include <cstdint>
#include <vector>

class DisjointSetSystem {
public:
    DisjointSetSystem(const std::vector<uint16_t> &separate_elements);
    uint16_t GetComponent(uint16_t element) const;
    void UniteComponents(uint16_t first_component, uint16_t second_component);
private:
    std::vector<uint16_t> parent_;
    std::vector<uint16_t> rank_;
};

template <typename T>
class Edge {
public:
    Edge(uint16_t from, uint16_t to, uint32_t weight) :
            vertex_from_(from),
            vertex_to_(to),
            weight_(weight) {}

    uint16_t GetVertexFrom() const { return vertex_from_; }
    uint16_t GetVertexTo() const { return vertex_to_; }
    T GetWeight() const { return weight_; }
private:
    uint16_t vertex_from_;
    uint16_t vertex_to_;
    T weight_;
};

template <typename T>
std::vector<Edge<T>> KruskalSearch(std::vector<Edge<T>> source_graph, uint16_t vertex_quantity) {
    std::vector<uint16_t> vertices(vertex_quantity);
    for (uint16_t i = 0; i < vertices.size(); ++i) {
        vertices[i] = i;
    }
    DisjointSetSystem forest(vertices);

    sort(source_graph.begin(), source_graph.end(),
         [](const Edge<T> &a, const Edge<T> &b) { return a.GetWeight() < b.GetWeight(); });

    std::vector<Edge<T>> mst;
    for (auto &edge : source_graph) {
        uint16_t first_component = forest.GetComponent(edge.GetVertexFrom());
        uint16_t second_component = forest.GetComponent(edge.GetVertexTo());
        if (first_component != second_component) {
            mst.push_back(edge);
            forest.UniteComponents(first_component, second_component);
        }
    }

    return mst;
}

template <typename T>
T TreeWeightCount(const std::vector<Edge<T>> &tree) {
    T sum_weight = 0;
    for (auto &edge : tree) {
        sum_weight += edge.GetWeight();
    }
    return  sum_weight;
}


#endif //MST_KRUSKAL_KRUSKAL_SEARCH_H_
