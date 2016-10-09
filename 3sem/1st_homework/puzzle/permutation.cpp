#include "permutation.h"

#include <algorithm>
#include <cmath>
#include <fstream>
#include <memory>

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
std::string Permutation::GetSolution() {
    std::vector<std::vector<short>> solved;
    solved.resize(permutation_.size());
    for (auto &x : solved)
        x.resize(permutation_.size());

    for (short i = 0; i < permutation_.size(); ++i) {
        for (short j = 0; j < permutation_.size(); ++j)
            solved[i][j] =(short) (i * permutation_.size() + j + 1);
    }
    solved[permutation_.size() - 1][permutation_.size() - 1] = 0;

    Permutation finish(solved);

    const int step_cost = 1;

    std::vector<std::unique_ptr<Permutation>> all_permutations;

    auto visited_comparator = [](const Permutation *a, const Permutation *b) {
        return *a < *b;
    };
    std::set<Permutation *, decltype(visited_comparator)> visited(visited_comparator);

    std::set<std::pair<int, Permutation *>> queue;

    //all_permutations.push_back(std::move(std::make_unique<Permutation>(this)));
    SetDistance(0);
    visited.insert(this);
    queue.insert({GetHeuristic() + GetDistance(), this});

    Permutation *current;
    while (queue.size() != 0) {current = queue.begin()->second;
        int current_f = queue.begin()->first;

        if (*current == finish)
            break;
        queue.erase({current_f, current});
        current->setNotEnqueued();
        for (auto &neighbour : current->GetNeighbours()) {
            int distance = current->GetDistance() + step_cost;
            auto it = visited.find(&neighbour);
            if (it == visited.end()) {
                all_permutations.push_back(std::make_unique<Permutation>(neighbour));
                auto neighbour_ptr = all_permutations.back().get();
                neighbour_ptr->SetDistance(distance);
                neighbour_ptr->setParent(current);
                neighbour_ptr->setEnqueued();

                visited.insert(neighbour_ptr);
                queue.insert({neighbour_ptr->GetHeuristic() + distance, neighbour_ptr});
            } else {
                if (distance < (*it)->GetDistance()) {
                    Permutation *neighbour_ptr = *it;
                    if (neighbour.isEnqueued())
                        queue.erase({neighbour_ptr->GetHeuristic() + neighbour_ptr->GetDistance(), neighbour_ptr});
                    neighbour_ptr->setParent(current);
                    neighbour_ptr->SetDistance(distance);
                    queue.insert({distance + neighbour_ptr->GetHeuristic(), neighbour_ptr});
                    neighbour_ptr->setEnqueued();
                }
            }
        }
    }

    return Restore(visited, current, this);
}

template <typename Comparator>
std::string Permutation::Restore(std::set<Permutation *, Comparator> &visited,
                    Permutation *current, Permutation *start) {
    std::string reversed_answer;
    while (!(*current == *start)) {
        std::pair<int, int> current_pos = current->GetPosition(0);
        std::pair<int, int> parent_pos = current->GetParent()->GetPosition(0);
        if (current_pos.first == parent_pos.first) { // the same line
            if (current_pos.second == parent_pos.second + 1) {
                reversed_answer.append("R");
            } else if (current_pos.second == parent_pos.second - 1) {
                reversed_answer.append("L");
            }
        } else { // the same column
            if (current_pos.first == parent_pos.first + 1) {
                reversed_answer.append("D");
            } else if (current_pos.first == parent_pos.first - 1) {
                reversed_answer.append("U");
            }
        }
        current = current->GetParent();
    }
    std::reverse(reversed_answer.begin(), reversed_answer.end());
    return reversed_answer;
}