
#include "astar.h"

#include <memory>
#include <map>
#include <set>
#include <algorithm>
#include <iostream>

#include "permutation.h"

std::string GetSolution(Permutation &start, Permutation &finish) {
    const int step_cost = 1;

    std::vector<std::unique_ptr<Permutation>> all_permutations;

    auto visited_comparator = [](const Permutation *a, const Permutation *b) {
        return *a < *b;
    };
    std::set<Permutation *, decltype(visited_comparator)> visited(visited_comparator);

    std::set<std::pair<int, Permutation *>> queue;

    all_permutations.push_back(std::move(std::make_unique<Permutation>(start)));
    Permutation *start_ptr = all_permutations.back().get();
    start_ptr->setDistance(0);
    visited.insert(start_ptr);
    queue.insert({start_ptr->getHeuristic() + start_ptr->getDistance(), start_ptr});

    Permutation *current;
    while (queue.size() != 0) {current = queue.begin()->second;
        int current_f = queue.begin()->first;

        if (*current == finish)
            break;
        queue.erase({current_f, current});
        current->setNotEnqueued();
        for (auto &neighbour : current->GetNeighbours()) {
            int distance = current->getDistance() + step_cost;
            auto it = visited.find(&neighbour);
            if (it == visited.end()) {
                all_permutations.push_back(std::make_unique<Permutation>(neighbour));
                auto neighbour_ptr = all_permutations.back().get();
                neighbour_ptr->setDistance(distance);
                neighbour_ptr->setParent(current);
                neighbour_ptr->setEnqueued();

                visited.insert(neighbour_ptr);
                queue.insert({neighbour_ptr->getHeuristic() + distance, neighbour_ptr});
            } else {
                if (distance < (*it)->getDistance()) {
                    Permutation *neighbour_ptr = *it;
                    if (neighbour.isEnqueued())
                        queue.erase({neighbour_ptr->getHeuristic() + neighbour_ptr->getDistance(), neighbour_ptr});
                    neighbour_ptr->setParent(current);
                    neighbour_ptr->setDistance(distance);
                    queue.insert({distance + neighbour_ptr->getHeuristic(), neighbour_ptr});
                    neighbour_ptr->setEnqueued();
                }
            }
        }
    }

    return  "";//Restore(visited, current, start_ptr);
}

template <typename Comparator>
std::string Restore(std::set<Permutation *, Comparator> &visited,
                    Permutation *current, Permutation *start) {
    std::string reversed_answer;
    while (!(*current == *start)) {
        std::pair<int, int> current_pos = current->GetPosition(0);
        std::pair<int, int> parent_pos = current->getParent()->GetPosition(0);
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
        current = current->getParent();
    }
    std::reverse(reversed_answer.begin(), reversed_answer.end());
    return reversed_answer;
}
#include <algorithm>
#include <climits>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <utility>
#include <vector>
#include <queue>
#include <set>
#include <fstream>

using std::vector;

int CountPermSymbol(const vector<vector<short>> &permutation);

int GetHeuristic(const vector<vector<short>> &permutation);

std::pair<int, int> GetPosition(short element, const vector<vector<short>> &permutation);

bool IsSolvable(const vector<vector<short>> &permutation);

int ManhattanDistance(const short element, const int from_line, const int from_column,
                      const vector<vector<short>> &permutation);

std::string PuzzleSolution(const vector<short> &permutation);

template<typename T>
std::unique_ptr<T> make_unique(T arg) {
    return std::unique_ptr<T>(new T(arg));
}

class Permutation {
public:
    Permutation(const vector<vector<short>> &p);

    vector<vector<short>> permutation;
    int heuristic;
    int distance;
    int f;
    Permutation *parent;
    bool enqueued;

    bool operator==(const Permutation &p) const;

    bool operator<(const Permutation &p) const;

    vector<Permutation> getNeighbours() const;
};

Permutation::Permutation(const vector<vector<short>> &p) {
    permutation = p;
    heuristic = GetHeuristic(permutation);
    distance = INT_MAX;
    f = INT_MAX;
    parent = nullptr;
    enqueued = false;
}

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

vector<Permutation> Permutation::getNeighbours() const {
    vector<Permutation> neighbours;
    int size = permutation.size();
    int zero_line = GetPosition(0, permutation).first;
    int zero_column = GetPosition(0, permutation).second;

    vector<vector<short>> candidate(permutation);
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

std::string Astar(Permutation &start, Permutation &finish);

int main() {
    int size = 3;
    //std::cin >> size;
    vector<vector<short>> input;
    input.resize(size);
    for (auto &x : input)
        x.resize(size);
    //std::ifstream in("input.txt");
    freopen("puzzle.in", "r", stdin);
    auto &in = std::cin;
    //std::ofstream out("/home/julia/Projects/mipt-algorithms/3sem/1st-homework/15-puzzle/output.txt");
    freopen("puzzle.out", "w", stdout);
    auto &out = std::cout;

    for (int i = 0; i < 400; ++i) {
        for (int line = 0; line < size; ++line) {
            for (int column = 0; column < size; ++column)
                in >> input[line][column];
        }

        if (!IsSolvable(input)) { // check if the permutation is even
            out << "-1\n";
            continue;
        }

        vector<vector<short>> solved;
        solved.resize(size);
        for (auto &x : solved)
            x.resize(size);

        for (short i = 0; i < size; ++i) {
            for (short j = 0; j < size; ++j)
                solved[i][j] = i * size + j + 1;
        }
        solved[size - 1][size - 1] = 0;

        Permutation start(input);
        Permutation finish(solved);

        auto answer = Astar(start, finish);
        out << answer.size() << std::endl << answer << std::endl;
    }

    return 0;
}

std::pair<int, int> GetPosition(short element, const vector<vector<short>> &permutation) {
    for (int line = 0; line < permutation.size(); ++line) {
        for (int column = 0; column < permutation[line].size(); ++column) {
            if (permutation[line][column] == element)
                return std::make_pair(line, column);
        }
    }
}

bool IsSolvable(const vector<vector<short>> &permutation) {
    vector<short> permutation_list;
    for (int i = 0; i < permutation.size(); ++i) {
        for (int j = 0; j < permutation.size(); ++j) {
            if (permutation[i][j] != 0)
                permutation_list.push_back(permutation[i][j]);
        }
    }

      int n = 0;

    for (int i = 0; i < permutation_list.size(); ++i) {
        //if (permutation_list[i] != 0) {
            for (int j = 0; j < i; ++j) {
                if (permutation_list[j] > permutation_list[i]) {
                    ++n;
                    //std::cout << permutation_list[j] << " > " << permutation_list[i] << ", n = " << n << std::endl;
                }
            }
        //}
    }
    //n += permutation.size() - GetPosition(0, permutation).first - 1;
    //std::cout <<"final n = " << n << "\n";
    return !(n % 2);
}

int ManhattanDistance(const short element, const int from_line, const int from_column, const int size) {
    int to_line = element / size;
    int to_column = element % size;

    return (int) (std::abs(to_line - from_line) + std::abs(to_column - from_column));
}

int GetHeuristic(const vector<vector<short>> &permutation) {
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

std::string Astar(Permutation &start, Permutation &finish) {
    const int step_cost = 1;

    //std::vector<std::unique_ptr<Permutation>> all_permutations;
    std::set<Permutation> visited;
    auto queue_comparator = [](Permutation *a, Permutation *b) {
        return a->f > b->f;
    };
    std::set<Permutation, decltype(queue_comparator)> queue(queue_comparator);

//    auto queue_comparator = [&visited](Permutation *a, Permutation *b) {
//        return a->f > b->f;
//    };
    //std::priority_queue<Permutation *, std::vector<Permutation *>, decltype(queue_comparator)> queue(queue_comparator);

    //all_permutations.push_back(std::move(make_unique<Permutation>(start)));
    //Permutation *start_ptr = all_permutations.back().get();

    start.distance = 0;
    start.f = 0;
    start.enqueued = true;
    visited.insert(start);
    queue.insert(start);
    Permutation current = start;
    //uint64_t step_count = 0;
    while (queue.size() != 0) {
        current = *queue.begin();
//        for (auto st : queue) {
//            if (visited[*st].f < visited[*current].f)
//                current = st;
//        }
        if (current == finish)
            break;
        queue.erase(current);
        //++step_count;
        //Variables &current_var = visited[*current];
        current.enqueued = false;
        visited.erase(current);
        visited.insert(current);
        //if (step_count < 100)
        // std::cout << current->heuristic << ' ' << current_var.distance << std::endl;
        for (auto &neighbour : current.getNeighbours()) {
            int distance = current.distance + step_cost;
            auto it = visited.find(neighbour);
            if (it == visited.end()) {
                //all_permutations.push_back(make_unique<Permutation>(neighbour));
                neighbour.distance = distance;
                neighbour.f = distance + neighbour.heuristic;
                neighbour.parent = visited.find(current);
                visited.insert(all_permutations.back().get());
                queue.insert(all_permutations.back().get());
                neighbour.enqueued = true;
            } else {
                if (distance < (*it)->distance) {
                    Permutation *neighbour_ptr = *it;
                    neighbour_ptr->distance = distance;
                    neighbour_ptr->f = distance + neighbour.heuristic;
                    neighbour_ptr->parent = current;
                    visited.erase(neighbour_ptr);
                    visited.insert(neighbour_ptr);

                    if (!neighbour_ptr->enqueued) {
                    queue.insert(neighbour_ptr);
                    neighbour_ptr->enqueued = true;
                    }
                }
            }
        }
    }
    // after we found a solution
    std::string reversed_answer;
    while (!(*current == start)) {
        std::pair<int, int> current_pos = GetPosition(0, current->permutation);
        std::pair<int, int> parent_pos = GetPosition(0, current->parent->permutation);
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
        current = current->parent;
    }
    std::reverse(reversed_answer.begin(), reversed_answer.end());
    return reversed_answer;
}

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <vector>
#include <queue>
#include <fstream>

#include "permutation.h"
#include "astar.h"


int main() {
    const int size = 3;
    //std::cin >> size;
    std::vector<std::vector<short>> input;
    input.resize(size);
    for (auto &x : input)
        x.resize(size);
    //std::ifstream in("input.txt");
    freopen("puzzle.in", "r", stdin);
    auto &in = std::cin;
    //std::ofstream out("/home/julia/Projects/mipt-algorithms/3sem/1st-homework/15-puzzle/output.txt");


    freopen("puzzle.out", "w", stdout);
    auto &out = std::cout;

    //for (int i = 0; i < 400; ++i) {
    for (int line = 0; line < size; ++line) {
        for (int column = 0; column < size; ++column)
            in >> input[line][column];
    }

    Permutation start(input);

    if (!start.IsSolvable()) { // check if the permutation is even
        out << "-1\n";
        return 0;
    }

    std::vector<std::vector<short>> solved;
    solved.resize(size);
    for (auto &x : solved)
        x.resize(size);

    for (short i = 0; i < size; ++i) {
        for (short j = 0; j < size; ++j)
            solved[i][j] = i * size + j + 1;
    }
    solved[size - 1][size - 1] = 0;

    Permutation finish(solved);

    auto answer = GetSolution(start, finish);
    out << answer.size() << std::endl << answer << std::endl;
    //}

    return 0;
}




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
