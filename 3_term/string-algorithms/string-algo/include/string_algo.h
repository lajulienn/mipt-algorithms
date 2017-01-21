/**
 * @author Julia Ivanova
 */

#ifndef STRING_ALGORITHMS_STRING_ALGO_H
#define STRING_ALGORITHMS_STRING_ALGO_H

#include <string>
#include <vector>

std::vector<int> StringToPrefix(const std::string &);
std::vector<int> StringToZ(const std::string &);
std::vector<int> PrefixToZ(const std::vector<int> &);
std::vector<int> ZToPrefix(const std::vector<int> &);
std::string PrefixToString(const std::vector<int> &);
std::string ZToString(std::vector<int>);

std::vector<int> FindSubstring(std::string &pattern, const std::string &);

int DifferentSubstringsCount(std::string &string);
std::vector<int> BuildSufArray(const std::string &string);
std::vector<int> BuildLcp(const std::string &, const std::vector<int> &);

#endif //STRING_ALGORITHMS_STRING_ALGO_H
