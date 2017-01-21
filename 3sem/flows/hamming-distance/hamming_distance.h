#ifndef FLOWS_HAMMING_DISTANCE_HAMMING_DISTANCE_H
#define FLOWS_HAMMING_DISTANCE_HAMMING_DISTANCE_H

#include <vector>
#include <map>
#include <string>
#include <set>

#include "flow_network.h"

const int SOURCE = 0;

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
void BuildNetwork(FlowNetwork &network, const std::map<int, EmptySpace> &spaces, int sink);
void FillString(std::string &string, std::map<int, EmptySpace> &spaces, const std::set<int> &spaces_with_0);
void SpacesRegistration(const std::string &string, std::map<int, EmptySpace> &spaces, int &id);

#endif //FLOWS_HAMMING_DISTANCE_HAMMING_DISTANCE_H
