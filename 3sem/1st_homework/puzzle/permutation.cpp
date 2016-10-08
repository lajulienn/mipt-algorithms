#include "permutation.h"

#include <vector>

#include "puzzle.h"

Permutation::Permutation(const std::vector<std::vector<short> > &p) {
    permutation = p;
    heuristic = GetHeuristic(permutation);
}

bool Permutation::operator<(const Permutation &p) const {
    return permutation < p.permutation;
}

bool Permutation::operator==(const Permutation &p) {
    for (int i = 0; i < permutation.size(); ++i) {
        if (permutation[i] != p.permutation[i])
            return false;
    }
    return true;
}

std::vector<Permutation> Permutation::getNeighbours() {
    std::vector<Permutation> neighbours;
    int size = permutation.size();
    int zero_line = GetPosition(0, permutation).first;
    int zero_column = GetPosition(0, permutation).second;

    std::vector<std::vector<short>> candidate(permutation);
    if (zero_line > 0) {
        std::swap(candidate[zero_line][zero_column], candidate[zero_line - 1][zero_column]);
        neighbours.push_back(Permutation(candidate));
        std::swap(candidate[zero_line][zero_column], candidate[zero_line - 1][zero_column]);
    }
    if (zero_line < size - 1) {
        std::swap(candidate[zero_line][zero_column], candidate[zero_line + 1][zero_column]);
        neighbours.push_back(Permutation(candidate));
        std::swap(candidate[zero_line][zero_column], candidate[zero_line + 1][zero_column]);
    }
    if (zero_column > 0) {
        std::swap(candidate[zero_line][zero_column], candidate[zero_line][zero_column - 1]);
        neighbours.push_back(Permutation(candidate));
        std::swap(candidate[zero_line][zero_column], candidate[zero_line][zero_column - 1]);
    }
    if (zero_column < size - 1) {
        std::swap(candidate[zero_line][zero_column], candidate[zero_line][zero_column + 1]);
        neighbours.push_back(Permutation(candidate));
        std::swap(candidate[zero_line][zero_column], candidate[zero_line][zero_column + 1]);
    }
    return neighbours;
}