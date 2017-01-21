#include <iostream>
#include <string>

#include "hamming_distance.h"

int main() {
    std::string string;
    std::string pattern;

    std::cin >> string >> pattern;

    std::cout << FindDistance(string, pattern) << std::endl;
    std::cout << string << std::endl;
    std::cout << pattern << std::endl;

    return 0;
}