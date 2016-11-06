#include "hamming_distance.h"

int FindDistance(std::string &string, std::string &pattern) {
    int hamming_distance = 0;
    std::map<int, EmptySpace> string_spaces; // key is position of ? in a string
    std::map<int, EmptySpace> pattern_spaces;
    int id = 1;

    for (int shift = 0; shift < string.length() - pattern.length() + 1; ++shift) {
        for (int i = 0; i < pattern.length(); ++i) {
            char s1 = string[i + shift];
            char s2 = pattern[i];
            if (s1 != '?' && s2 != '?' && s1 != s2) {
                ++hamming_distance;
            } else if (s1 == '?' && s2 != '?') {
                if (string_spaces.find(i + shift) == string_spaces.end()) {
                    string_spaces[i + shift] = EmptySpace(id);
                    ++id;
                }
                if (s2 == '0') {
                    ++string_spaces[i + shift].comparisons_with_0;
                } else {
                    ++string_spaces[i + shift].comparisons_with_1;
                }
            } else if (s2 == '?' && s1 != '?') {
                if (pattern_spaces.find(i) == pattern_spaces.end()) {
                    pattern_spaces[i] = EmptySpace(id);
                    ++id;
                }
                if (s1 == '0') {
                    ++pattern_spaces[i].comparisons_with_0;
                } else {
                    ++pattern_spaces[i].comparisons_with_1;
                }
            } else if (s1 == '?' && s2 == '?') {
                if (string_spaces.find(i + shift) == string_spaces.end()) {
                    string_spaces[i + shift] = EmptySpace(id);
                    ++id;
                }
                if (pattern_spaces.find(i) == pattern_spaces.end()) {
                    pattern_spaces[i] = EmptySpace(id);
                    ++id;
                }
                int s2_id = string_spaces[i + shift].id;
                pattern_spaces[i].spaces_compared.push_back(s2_id);
            }
        }
    }
    const int source = 0;
    const int sink = id;
    Network network(source, sink, id + 1);
    BuildNetwork(network, string_spaces, pattern_spaces, sink);
    hamming_distance += network.MaxFlowSearch();
    std::vector<int> spaces_with_0 = network.MinimalCut();
    std::set<int> set_of_spaces_with_0(spaces_with_0.begin(), spaces_with_0.end());
    for (auto element : string_spaces) {
        int position = element.first;
        EmptySpace space = element.second;
        if (space.id == source) {
            continue;
        }
        if (set_of_spaces_with_0.find(space.id) != set_of_spaces_with_0.end()) {
            string[position] = '0';
        } else {
            string[position] = '1';
        }
    }
    for (auto element : pattern_spaces) {
        int position = element.first;
        EmptySpace space = element.second;
        if (space.id == source) {
            continue;
        }
        if (set_of_spaces_with_0.find(space.id) != set_of_spaces_with_0.end()) {
            pattern[position] = '0';
        } else {
            pattern[position] = '1';
        }
    }
    return hamming_distance;
}

void BuildNetwork(Network &network, const std::map<int, EmptySpace> &string_spaces,
                  const std::map<int, EmptySpace> &pattern_spaces, int sink) {
    const int source = 0;
    for (auto element : string_spaces) {
        EmptySpace space = element.second;
        network.AddEdge(source, space.id, space.comparisons_with_0);
        network.AddEdge(space.id, source, 0);
        network.AddEdge(space.id, sink, space.comparisons_with_1);
        network.AddEdge(sink, space.id, 0);
        for (auto neighbor : space.spaces_compared) {
            network.AddEdge(space.id, neighbor, 1);
            network.AddEdge(neighbor, space.id, 1);
        }
    }
    for (auto element : pattern_spaces) {
        EmptySpace space = element.second;
        network.AddEdge(source, space.id, space.comparisons_with_0);
        network.AddEdge(space.id, source, 0);
        network.AddEdge(space.id, sink, space.comparisons_with_1);
        network.AddEdge(sink, space.id, 0);
        for (auto neighbor : space.spaces_compared) {
            network.AddEdge(space.id, neighbor, 1);
            network.AddEdge(neighbor, space.id, 1);
        }
    }
}