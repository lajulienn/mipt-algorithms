/**
 * @author Julia Ivanova
 */

#include "hamming_distance.h"

int FindDistance(std::string &string, std::string &pattern) {
  int hamming_distance = 0;
  std::map<int, EmptySpace> string_spaces; // key is position of ? in a string
  std::map<int, EmptySpace> pattern_spaces;
  int id = 1;

  SpacesRegistration(string, string_spaces, id);
  SpacesRegistration(pattern, pattern_spaces, id);

  for (int shift = 0; shift < string.length() - pattern.length() + 1; ++shift) {
    for (int i = 0; i < pattern.length(); ++i) {
      char s1 = string[i + shift];
      char s2 = pattern[i];
      if (s1 != '?' && s2 != '?' && s1 != s2) {
        ++hamming_distance;
      } else if (s1 == '?' && s2 != '?') {
        if (s2 == '0') {
          ++string_spaces[i + shift].comparisons_with_0;
        } else {
          ++string_spaces[i + shift].comparisons_with_1;
        }
      } else if (s2 == '?' && s1 != '?') {
        if (s1 == '0') {
          ++pattern_spaces[i].comparisons_with_0;
        } else {
          ++pattern_spaces[i].comparisons_with_1;
        }
      } else if (s1 == '?' && s2 == '?') {
        int s2_id = string_spaces[i + shift].id;
        pattern_spaces[i].spaces_compared.push_back(s2_id);
      }
    }
  }
  const int sink = id;
  FlowNetwork network(SOURCE, sink, id + 1);
  BuildNetwork(network, string_spaces, sink);
  BuildNetwork(network, pattern_spaces, sink);

  hamming_distance += network.MaxFlowSearch();
  std::vector<int> spaces_with_0 = network.MinimalCut();
  spaces_with_0.erase(spaces_with_0.begin());

  std::set<int> set_of_spaces_with_0(spaces_with_0.begin(), spaces_with_0.end());
  FillString(string, string_spaces, set_of_spaces_with_0);
  FillString(pattern, pattern_spaces, set_of_spaces_with_0);

  return hamming_distance;
}

void BuildNetwork(FlowNetwork &network, const std::map<int, EmptySpace> &spaces, int sink) {
  for (auto element : spaces) {
    EmptySpace space = element.second;
    network.AddEdge(SOURCE, space.id, space.comparisons_with_0);
    network.AddEdge(space.id, SOURCE, 0);
    network.AddEdge(space.id, sink, space.comparisons_with_1);
    network.AddEdge(sink, space.id, 0);
    for (auto neighbor : space.spaces_compared) {
      network.AddEdge(space.id, neighbor, 1);
      network.AddEdge(neighbor, space.id, 1);
    }
  }
}

void FillString(std::string &string, std::map<int, EmptySpace> &spaces, const std::set<int> &spaces_with_0) {
  for (auto element : spaces) {
    int position = element.first;
    EmptySpace space = element.second;
    if (spaces_with_0.find(space.id) != spaces_with_0.end()) {
      string[position] = '0';
    } else {
      string[position] = '1';
    }
  }
}

void SpacesRegistration(const std::string &string, std::map<int, EmptySpace> &spaces, int &id) {
  for (int i = 0; i < string.length(); ++i) {
    if (string[i] == '?') {
      spaces[i] = EmptySpace(id);
      ++id;
    }
  }
}
