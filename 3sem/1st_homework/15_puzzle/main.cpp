#include <algorithm>
#include <climits>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>
#include <cstdint>
#include <stdlib.h>

using std::vector;

int CountPermSymbol(const vector<vector<uint8_t>> &permutation);
int GetHeuristic(const vector<vector<uint8_t>> &permutation) {
bool IsSolvable(const vector<vector<uint8_t>> &permutation);
int ManhattanDistance(const int element, const int from_line, const int from_column, const vector<vector<uint8_t>> &permutation) {
string PuzzleSolution(const vector<uint8_t> &permutation);

struct Permutation {
    Permutation(vector<vector<uint8_t>> &p);

    vector<vector<uint8_t>> permutation;
    int distance = INT_MAX;
    int heuristic = INT_MAX;
    Permutation *parent;

    bool operator<(const Permutation &p);
    vector<Permutation> getNeighbours();
};
bool Permutation::operator<(const Permutation &p) {
    for(int i = 0; i < permutation.size(); ++i) {
        if (permutation[i] >= p.permutation[i])
            return false;
    }
    return true;
}
vector<Permutation> Permutation::getNeighbours() {
    vector<Permutation> neighbours;
    int zero = GetPosition(this->permutation, 0);
}
Permutation::Permutation(vector<vector<uint8_t>> &p) {
    permutation = std::move(p);
    heuristic =
}

int main() {
    int size = 0;
    cin >> size;

  //  vector<uint8_t> permutation(size * size);
    for (auto &element : permutation)
        cin >> element;

    if (!IsSolvable(permutation, size)){ // check if the permutation is even
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    return 0;
}

bool IsSolvable(const vector<vector<uint8_t>> &permutation) {
    int empty_square_line = 0;
    for (int line = 0; line < permutation.size(); ++line) {
        for (int column = 0; column < permutation[line].size(); ++column) {
            if (permutation[line][column] == 0) {
                empty_square_line = line;
                return CountPermSymbol(permutation) * std::pow(-1, permutation.size() - empty_square_line) == 1;
            }
        }
    }
}

int CountPermSymbol(const vector<vector<uint8_t>> &permutation) {
    vector<uint8_t> permutation_list;
    for (int i = 0; i < permutation.size(); ++i) {
        for (int j = 0; j < permutation.size(); ++j) {
            permutation_list.push_back(permutation[i][j])
        }
    }
    int symbol = 1;
    for (int i = 0; i < permutation.size(); ++i) {
        for (int j = 0; j < permutation.size(); ++j) {
            if (i && j && j > i && permutation[i] > permutation[j])
                symbol *= -1;
        }
    }
    return symbol;
}

int ManhattanDistance(const int element, const int from_line, const int from_column, const int size) {
    int to_line = element / size;
    int to_column = element % size;

    return (int) (abs(to_line - from_line) + abs(to_column - from_column));
}

int GetHeuristic(const vector<vector<uint8_t>> &permutation) {
    int heuristic = 0;
    for (int i = 0; i < permutation.size(); ++i) {
        for (int j = 0; j < permutation.size(); ++j) {
            if (permutation[i][j] == 0 || permutation[i][j] == i + j)
                continue;
            heuristic += ManhattanDistance(permutation[i][j], i, j, permutation.size());
        }
    }
}

string PuzzleSolution(const vector<uint8_t> &permutation) {
    vector<vector<uint8_t>> all_permutations; //we'll put here all new permutations
    vector<string> instructions; // instructions how to get current condition from the start condition
    vector<int> distance(1); // distance from the start to current
    vector<int> heuristic(1); // values of heuristic function heuristic[x] = distance[x] + h(x), h(x) uses manhattan distance
    vector<vector<uint8_t>> heap_to_handle; // permutations we haven't visited yet

    heap_to_handle.push_back(permutation);
    distance[0] = 0;
    heuristic[0] = distance[0] + GetHeuristic(permutation);

    while (heap_to_handle.size() != 0) {
        auto current = heap_to_handle.front()
    }
}



permutation.resize(sqrt(p.size()));
for (int i = 0; i < sqrt(p.size()); ++i)
permutation[i].resize(sqrt(p.size()));
for(int i = 0; i < sqrt(p.size()); ++i) {
for(int j = 0; j < sqrt(p.size()); ++j)
permutation[i][j] = p[i +j];
}

bool found = false;
for (int line = 0; line < permutation.size(); ++line) {
for (int column = 0; column < permutation.size(); ++column) {
if (permutation[line][column] == element) {
from_column = column;
from_line = line;
found = true;
break;
}
if(found)
break;
}
}
