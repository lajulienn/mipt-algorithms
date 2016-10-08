//
// Created by julia on 08.10.16.
//

#ifndef INC_15_PERMUTATION_PERMUTATION_H_
#define INC_15_PERMUTATION_PERMUTATION_H_

#include <vector>
#include <climits>

class Permutation {
public:
    Permutation(const std::vector<std::vector<short> > &p);

    bool operator==(const Permutation &p);
    bool operator<(const Permutation &p) const;

    std::vector<Permutation> getNeighbours();

    std::vector<std::vector<short>> permutation;
    int heuristic;
};

class Variables {
public:
    Variables(Permutation *id_ = nullptr, int distance_ = INT_MAX, int f_ = INT_MAX, Permutation *parent_ = nullptr,
              bool enqueued_ = false) :
            id(id_), distance(distance_), f(f_), parent(parent_), enqueued(enqueued_) {}

    Permutation *id;
    int distance;
    int f;
    Permutation *parent;
    bool enqueued;
};

#endif //INC_15_PERMUTATION_PERMUTATION_H_
