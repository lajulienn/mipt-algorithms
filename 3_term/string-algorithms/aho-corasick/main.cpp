/**
 * @author Julia Ivanova
 */

#include <iostream>
#include <string>

#include "aho_corasick.h"

int main() {
    std::string pattern;
    std::string text;

    std::cin >> pattern >> text;

    PatternFinder finder = PatternFinder(pattern);
    std::vector<int> entry = finder.FindOccurrences(text);

    for (auto x : entry) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    return 0;
}