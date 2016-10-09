#include "permutation.h"

#include <climits>
#include <cmath>

Permutation::Permutation(const std::vector<std::vector<short> > &p, int distance,
                         Permutation *parent, bool enqueued) :
    permutation_(p),
    heuristic_(CountHeuristic()),
    distance_(distance),
    parent_(parent),
    enqueued_(enqueued) {}


bool Permutation::operator<(const Permutation &p) const {
    return permutation_ < p.permutation_;
}

bool Permutation::operator==(const Permutation &p) const {
    return permutation_ == p.permutation_;
}

std::vector<Permutation> Permutation::GetNeighbours() const {
    std::vector<Permutation> neighbours;
    int size = permutation_.size();
    int zero_line = GetPosition(0).first;
    int zero_column = GetPosition(0).second;

    std::vector<std::vector<short>> candidate(permutation_);
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
    for (int line = 0; line < permutation_.size(); ++line) {
        for (int column = 0; column < permutation_[line].size(); ++column) {
            if (permutation_[line][column] == element)
                return {line, column};
        }
    }
}

bool Permutation::IsSolvable() const {
    std::vector<short> permutation_list;
    for (int i = 0; i < permutation_.size(); ++i) {
        for (int j = 0; j < permutation_.size(); ++j) {
            if (permutation_[i][j] != 0)
                permutation_list.push_back(permutation_[i][j]);
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
    for (int i = 0; i < permutation_.size(); ++i) {
        for (int j = 0; j < permutation_.size(); ++j) {
            if (permutation_[i][j] == 0 || permutation_[i][j] == i + j)
                continue;
            heuristic += ManhattanDistance(permutation_[i][j] - 1, i, j, permutation_.size());
        }
    }
    return heuristic;
}