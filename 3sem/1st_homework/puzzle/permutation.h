//
// Created by julia on 08.10.16.
//

#ifndef INC_15_PERMUTATION_PERMUTATION_H_
#define INC_15_PERMUTATION_PERMUTATION_H_

#include <vector>
#include <climits>
#include <string>
#include <set>

class Permutation {
public:
    Permutation(const std::vector<std::vector<short> > &p, int distance_ = INT_MAX, Permutation *parent_ = nullptr,
                bool enqueued_ = false);

    bool IsSolvable() const ;
    std::string GetSolution();

    bool operator==(const Permutation &p) const;
    bool operator<(const Permutation &p) const;

    int GetHeuristic() const { return heuristic_; }
    int GetDistance() const { return distance_; }
    void SetDistance(int distance) { distance_ = distance; }
    Permutation *GetParent() const { return parent_; }
    void SetParent(Permutation *parent) {parent_ = parent; }
    bool IsEnqueued() { return enqueued_; }
    void SetEnqueued() { enqueued_ = true; }
    void SetNotEnqueued() { enqueued_ = false; }

private:
    std::vector<Permutation> GetNeighbours() const;
    int CountHeuristic() const;
    std::pair<int, int> GetPosition(short element) const ;
    int ManhattanDistance(short element, int from_line, int from_column, int size) const;
    template <typename Comparator>
    std::string Restore(std::set<Permutation *, Comparator> &visited, Permutation *current, Permutation *start);

    std::vector<std::vector<short>> permutation_;
    int heuristic_;
    int distance_;
    Permutation *parent_;
    bool enqueued_;
};

#endif //INC_15_PERMUTATION_PERMUTATION_H_
