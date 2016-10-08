#include "puzzle.h"

#include <cmath>
#include <vector>

std::pair<int, int> GetPosition(short element, const std::vector<std::vector<short>> &permutation) {
    for (int line = 0; line < permutation.size(); ++line) {
        for (int column = 0; column < permutation[line].size(); ++column) {
            if (permutation[line][column] == element)
                return std::make_pair(line, column);
        }
    }
}

bool IsSolvable(const std::vector<std::vector<short>> &permutation) {
    std::vector<short> permutation_list;
    for (int i = 0; i < permutation.size(); ++i) {
        for (int j = 0; j < permutation.size(); ++j) {
            if (permutation[i][j] != 0)
                permutation_list.push_back(permutation[i][j]);
        }
    }

    int n = 0;

    for (int i = 0; i < permutation_list.size(); ++i) {
        for (int j = 0; j < i; ++j) {
            if (permutation_list[j] > permutation_list[i]) {
                ++n;
            }
        }
    }
    return !(n % 2);
}

int ManhattanDistance(const short element, const int from_line, const int from_column, const int size) {
    int to_line = element / size;
    int to_column = element % size;

    return (int) (std::abs(to_line - from_line) + std::abs(to_column - from_column));
}

int GetHeuristic(const std::vector<std::vector<short>> &permutation) {
    int heuristic = 0;
    for (int i = 0; i < permutation.size(); ++i) {
        for (int j = 0; j < permutation.size(); ++j) {
            if (permutation[i][j] == 0 || permutation[i][j] == i + j)
                continue;
            heuristic += ManhattanDistance(permutation[i][j] - 1, i, j, permutation.size());
        }
    }
    return heuristic;
}