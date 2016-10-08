//
// Created by julia on 08.10.16.
//

#ifndef INC_15_PUZZLE_PUZZLE_H_
#define INC_15_PUZZLE_PUZZLE_H_

#include <vector>
#include <utility>

int GetHeuristic(const std::vector<std::vector<short>> &permutation);

std::pair<int, int> GetPosition(short element, const std::vector<std::vector<short>> &permutation);

bool IsSolvable(const std::vector<std::vector<short>> &permutation);

int ManhattanDistance(const short element, const int from_line, const int from_column,
                      const std::vector<std::vector<short>> &permutation);

#endif //INC_15_PUZZLE_PUZZLE_H_