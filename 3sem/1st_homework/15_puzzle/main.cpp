#include <algorithm>
#include <climits>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <map>
#include <set>
#include <utility>
#include <vector>
#include <queue>
#include <set>

using std::vector;

int CountPermSymbol(const vector<vector<short>> &permutation);
int GetHeuristic(const vector<vector<short>> &permutation);
std::pair<int, int> GetPosition(short element, const vector<vector<short>> &permutation);
bool IsSolvable(const vector<vector<short>> &permutation);
int ManhattanDistance(const short element, const int from_line, const int from_column, const vector<vector<short>> &permutation);
std::string PuzzleSolution(const vector<short> &permutation);

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
    for(int i = 0; i < permutation.size(); ++i) {
        if (permutation[i] >= p.permutation[i])
            return false;
    }
    return true;
}
bool Permutation::operator==(const Permutation &p) {
    for(int i = 0; i < permutation.size(); ++i) {
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
    Variables(int distance_ = INT_MAX, int f_ = INT_MAX, Permutation *parent_ = nullptr) :
            distance(distance_), f(f_), parent(parent_) {}
    int distance;
    int f;
    Permutation *parent;
};

std::string Astar(Permutation &start, Permutation &finish);


int main() {
    int size = 0;
    std::cin >> size;
    vector<vector<short>> input;
    input.resize(size);
    for (auto &x : input)
        x.resize(size);
    for (int line = 0; line < size; ++line) {
        for (int column = 0; column < size; ++column)
            std::cin >> input[line][column];
    }

    if (!IsSolvable(input)){ // check if the permutation is even
        std::cout << "IMPOSSIBLE\n";
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

    std::cout << Astar(start, finish);

    return 0;
}

bool IsSolvable(const vector<vector<short>> &permutation) {
    return CountPermSymbol(permutation) == 1;
}

std::pair<int, int> GetPosition(short element, const vector<vector<short>> &permutation) {
    for (int line = 0; line < permutation.size(); ++line) {
        for (int column = 0; column < permutation[line].size(); ++column) {
            if (permutation[line][column] == element)
                return std::make_pair(line, column);
        }
    }
}

int CountPermSymbol(const vector<vector<short>> &permutation) {
    vector<short> permutation_list;
    for (int i = 0; i < permutation.size(); ++i) {
        for (int j = 0; j < permutation.size(); ++j) {
            if (permutation[i][j] != 0)
                permutation_list.push_back(permutation[i][j]);
            else
                permutation_list.push_back(permutation.size() * permutation.size());
        }
    }
    int symbol = 1;
    for (int i = 0; i < permutation_list.size(); ++i) {
        for (int j = 0; j < permutation_list.size(); ++j) {
            if (j > i && permutation_list[i] > permutation_list[j])
                symbol *= -1;
        }
    }
    return symbol;
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
            heuristic += ManhattanDistance(permutation[i][j], i, j, permutation.size());
        }
    }
}

std::string Astar(Permutation &start, Permutation &finish) {
    const int step_cost = 1;

    std::map<Permutation, Variables> viewed;

    auto queue_comparator = [&viewed](const Permutation &a, const Permutation &b) {
        return viewed[a].f > viewed[b].f;
    };
    std::priority_queue<Permutation, std::vector<Permutation>, decltype(queue_comparator)> queue(queue_comparator);

    viewed.insert(std::make_pair(start, Variables()));
    queue.push(start);
    Permutation current = start;
    while (queue.size() != 0) {
         current = queue.top();
        if(current == finish) {

            break;
        }
        queue.pop();
        //viewed.insert(current);
        for (auto &v : current.getNeighbours()) {
            Variables current_var = viewed[current];
            int distance = current_var.distance + step_cost;
            Variables &v_it = viewed[v];
            if (distance < v_it.distance)  {
                v_it.parent = &(current);
                v_it.distance = distance;
                v_it.f = distance + v.heuristic;
                //if (нет в очереди)
                queue.push(v);
            }
        }
    }
    // after we found a solution
    std::string reversed_answer;
    while (!(current == start)) {

    }

    return std::string("Found!\n");
}
