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

    bool operator==(const Permutation &p);

    bool operator<(const Permutation &p) const;

    vector<Permutation> getNeighbours();
};

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

vector<Permutation> Permutation::getNeighbours() {
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

Permutation::Permutation(const vector<vector<short>> &p) {
    permutation = p;
    heuristic = GetHeuristic(permutation);
}

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

    //for (int i = 0; i < 400; ++i) {
        for (int line = 0; line < size; ++line) {
            for (int column = 0; column < size; ++column)
                in >> input[line][column];
        }

        if (!IsSolvable(input)) { // check if the permutation is even
            out << "-1\n";
            return 0;
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
    //}

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

    std::vector<std::unique_ptr<Permutation>> all_permutations;

    std::map<Permutation, Variables> viewed;

    auto queue_comparator = [&viewed](Permutation *a, Permutation *b) {
        return viewed[*a].f > viewed[*b].f;
    };
    std::set<Permutation *> queue;
    //std::priority_queue<Permutation *, std::vector<Permutation *>, decltype(queue_comparator)> queue(queue_comparator);

    all_permutations.push_back(std::move(make_unique<Permutation>(start)));
    Permutation *start_ptr = all_permutations.back().get(); // changed on back
    viewed[start] = Variables(start_ptr, 0, 0 + start.heuristic);
    queue.insert(start_ptr);
    Permutation *current = start_ptr;
    uint64_t step_count = 0;
    while (queue.size() != 0) {
        current = *queue.begin();
        for (auto st : queue) {
            if (viewed[*st].f < viewed[*current].f)
                current = st;
        }
        if (*current == finish)
            break;
        queue.erase(current);
        ++step_count;
        Variables &current_var = viewed[*current];
        current_var.enqueued = false;
        //if (step_count < 100)
        // std::cout << current->heuristic << ' ' << current_var.distance << std::endl;
        for (auto &neighbour : current->getNeighbours()) {
            int distance = current_var.distance + step_cost;
            auto it = viewed.find(neighbour);
            if (it == viewed.end()) {
                all_permutations.push_back(make_unique<Permutation>(neighbour));
                viewed[neighbour] = Variables(all_permutations.back().get(), distance, distance + neighbour.heuristic,
                                              current, true);
                queue.insert(all_permutations.back().get());
            } else {
                Variables &neighbour_var = viewed[neighbour];
                if (distance < neighbour_var.distance) {
                    neighbour_var.parent = current; // changed start_ptr --> current
                    neighbour_var.distance = distance;
                    neighbour_var.f = distance + neighbour.heuristic;
                    //if (!neighbour_var.enqueued) {
                    queue.insert(neighbour_var.id);
                    neighbour_var.enqueued = true;
                    //}
                }
            }
        }
    }
    // after we found a solution
    std::string reversed_answer;
    while (!(*current == start)) {
        std::pair<int, int> current_pos = GetPosition(0, current->permutation);
        std::pair<int, int> parent_pos = GetPosition(0, viewed[*current].parent->permutation);
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
        current = viewed[*current].parent;
    }
    std::reverse(reversed_answer.begin(), reversed_answer.end());
    return reversed_answer;
}
