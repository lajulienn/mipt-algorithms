#include "permutation.h"

#include <cmath>

Permutation::Permutation(const std::vector<std::vector<short> > &p) :
    permutation(p),
    heuristic(CountHeuristic()) {}


bool Permutation::operator<(const Permutation &p) const {
    return permutation < p.permutation;
}

bool Permutation::operator==(const Permutation &p) const {
    for (int i = 0; i < permutation.size(); ++i) {
        if (permutation[i] != p.permutation[i])
            return false;
    }
    return true;
}

std::vector<Permutation> Permutation::GetNeighbours() const {
    std::vector<Permutation> neighbours;
    int size = permutation.size();
    int zero_line = GetPosition(0).first;
    int zero_column = GetPosition(0).second;

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

std::pair<int, int> Permutation::GetPosition(short element) const {
    for (int line = 0; line < permutation.size(); ++line) {
        for (int column = 0; column < permutation[line].size(); ++column) {
            if (permutation[line][column] == element)
                return {line, column};
        }
    }
}

bool Permutation::IsSolvable() const {
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

int Permutation::ManhattanDistance(const short element, const int from_line, const int from_column, const int size) const {
    int to_line = element / size;
    int to_column = element % size;

    return (int) (std::abs(to_line - from_line) + std::abs(to_column - from_column));
}

int Permutation::CountHeuristic() const {
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