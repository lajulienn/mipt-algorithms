#ifndef MAX_FLOW_SEARCH_HAMMING_DISTANCE_H
#define MAX_FLOW_SEARCH_HAMMING_DISTANCE_H

#include <vector>
#include <map>
#include <string>
#include <set>

#include "max_flow.h"

struct EmptySpace {
    EmptySpace() {};
    EmptySpace(int id) : id(id), comparisons_with_0(0), comparisons_with_1(0) {}

    int id;
    int comparisons_with_0;
    int comparisons_with_1;
    std::vector<int> spaces_compared;
    char symbol;
};

int FindDistance(std::string &string, std::string &pattern);
void BuildNetwork(Network &network, const std::map<int, EmptySpace> &string_spaces,
                  const std::map<int, EmptySpace> &pattern_spaces, int sink);

#endif //MAX_FLOW_SEARCH_HAMMING_DISTANCE_H
