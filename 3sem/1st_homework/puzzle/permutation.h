//
// Created by julia on 08.10.16.
//

#ifndef INC_15_PERMUTATION_PERMUTATION_H_
#define INC_15_PERMUTATION_PERMUTATION_H_

#include <vector>
#include <climits>

class Permutation {
public:
    Permutation(const std::vector<std::vector<short> > &p, int distance_ = INT_MAX, Permutation *parent_ = nullptr,
                bool enqueued_ = false);

    bool operator==(const Permutation &p) const;
    bool operator<(const Permutation &p) const;

    std::vector<Permutation> GetNeighbours() const;
    int CountHeuristic() const;
    std::pair<int, int> GetPosition(short element) const ;
    bool IsSolvable() const ;
    int ManhattanDistance(short element, int from_line, int from_column, int size) const;

    int getHeuristic() const { return heuristic_; }
    int getDistance() const { return distance_; }
    void setDistance(int distance) { distance_ = distance; }
    Permutation *getParent() const { return parent_; }
    void setParent(Permutation *parent) {parent_ = parent; }
    bool isEnqueued() { return enqueued_; }
    void setEnqueued() { enqueued_ = true; }
    void setNotEnqueued() { enqueued_ = false; }

private:
    std::vector<std::vector<short>> permutation_;
    int heuristic_;
    int distance_;
    Permutation *parent_;
    bool enqueued_;
};

//class Variables {
//public:
//    Variables(Permutation *id_ = nullptr, int distance_ = INT_MAX, int f_ = INT_MAX, Permutation *parent_ = nullptr,
//              bool enqueued_ = false) :
//            id(id_), distance(distance_), f(f_), parent(parent_), enqueued(enqueued_) {}
//
//    Permutation *id;
//    int distance;
//    int f;
//    Permutation *parent;
//    bool enqueued;
//};

#endif //INC_15_PERMUTATION_PERMUTATION_H_
