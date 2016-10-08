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
#include "puzzle.h"
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


    if (!IsSolvable(input)) { // check if the permutation is even
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

    Permutation start(input);
    Permutation finish(solved);

    auto answer = Astar(start, finish);
    out << answer.size() << std::endl << answer << std::endl;
    //}

    return 0;
}



