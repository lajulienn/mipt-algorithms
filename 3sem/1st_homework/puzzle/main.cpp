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

int main() {
    //std::cin >> size;
    const int size = 3;
    std::ifstream in("puzzle.in");
    std::ofstream out("puzzle.out");

    std::vector<std::vector<short>> input;
    input.resize(size);
    for (auto &x : input)
        x.resize(size);
    for (int line = 0; line < size; ++line) {
        for (int column = 0; column < size; ++column)
            in >> input[line][column];
    }
    Permutation start(input);

    if (!start.IsSolvable()) { // check if the permutation is even
        out << "-1\n";
        return 0;
    }

    auto answer = start.GetSolution();
    out << answer.size() << std::endl << answer << std::endl;

    return 0;
}



