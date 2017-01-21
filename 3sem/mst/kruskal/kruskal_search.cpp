/**
 * @author Julia Ivanova
 */

#include "include/kruskal_search.h"

DisjointSetSystem::DisjointSetSystem(const std::vector<uint16_t> &separate_elements) :
        parent_(std::vector<uint16_t>(separate_elements)),
        rank_(std::vector<uint16_t>(separate_elements.size(), 0)) {}

uint16_t DisjointSetSystem::GetComponent(uint16_t element) const {
    uint16_t parent = parent_[element];
    if(element == parent) {
        return element;
    } else {
        return GetComponent(parent);
    }
}

void DisjointSetSystem::UniteComponents(uint16_t first_element, uint16_t second_element) {
    first_element = GetComponent(first_element);
    second_element = GetComponent(second_element);
    if (first_element == second_element) {
        return;
    }
    if (rank_[first_element] == rank_[second_element]) {
        ++rank_[first_element];
    }
    if (rank_[first_element] < rank_[second_element]) {
        parent_[first_element] = second_element;
    } else {
        parent_[second_element] = first_element;
    }
}

