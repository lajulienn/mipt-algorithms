//
// Created by julia on 09.10.16.
//

#ifndef INC_15_PUZZLE_ASTAR_H_
#define INC_15_PUZZLE_ASTAR_H_

#include "permutation.h"
#include <set>
#include <string>

std::string GetSolution(Permutation &start, Permutation &finish);
//std::string Restore(std::set<Permutation *, bool(*)(const Permutation *, const Permutation *)> &visited, Permutation *current, Permutation *start);

template <typename Comparator>
std::string Restore(std::set<Permutation *, Comparator> &visited, Permutation *current, Permutation *start);

#endif //INC_15_PUZZLE_ASTAR_H_
