#include "astar.h"

#include <memory>
#include <map>
#include <set>
#include <algorithm>
#include <iostream>

#include "permutation.h"

std::string GetSolution(Permutation &start, Permutation &finish) {
    const int step_cost = 1;

    std::vector<std::unique_ptr<Permutation>> all_permutations;

    auto visited_comparator = [](const Permutation *a, const Permutation *b) {
        return *a < *b;
    };
    std::set<Permutation *, decltype(visited_comparator)> visited(visited_comparator);

    std::set<std::pair<int, Permutation *>> queue;

    all_permutations.push_back(std::move(std::make_unique<Permutation>(start)));
    Permutation *start_ptr = all_permutations.back().get();
    start_ptr->setDistance(0);
    visited.insert(start_ptr);
    queue.insert({start_ptr->getHeuristic() + start_ptr->getDistance(), start_ptr});

    Permutation *current;
    while (queue.size() != 0) {current = queue.begin()->second;
        int current_f = queue.begin()->first;

        if (*current == finish)
            break;
        queue.erase({current_f, current});
        current->setNotEnqueued();
        for (auto &neighbour : current->GetNeighbours()) {
            int distance = current->getDistance() + step_cost;
            auto it = visited.find(&neighbour);
            if (it == visited.end()) {
                all_permutations.push_back(std::make_unique<Permutation>(neighbour));
                auto neighbour_ptr = all_permutations.back().get();
                neighbour_ptr->setDistance(distance);
                neighbour_ptr->setParent(current);
                neighbour_ptr->setEnqueued();

                visited.insert(neighbour_ptr);
                queue.insert({neighbour_ptr->getHeuristic() + distance, neighbour_ptr});
            } else {
                if (distance < (*it)->getDistance()) {
                    Permutation *neighbour_ptr = *it;
                    if (neighbour.isEnqueued())
                        queue.erase({neighbour_ptr->getHeuristic() + neighbour_ptr->getDistance(), neighbour_ptr});
                    neighbour_ptr->setParent(current);
                    neighbour_ptr->setDistance(distance);
                    queue.insert({distance + neighbour_ptr->getHeuristic(), neighbour_ptr});
                    neighbour_ptr->setEnqueued();
                }
            }
        }
    }

    return Restore(visited, current, start_ptr);
}

template <typename Comparator>
std::string Restore(std::set<Permutation *, Comparator> &visited,
                    Permutation *current, Permutation *start) {
    std::string reversed_answer;
    while (!(*current == *start)) {
        std::pair<int, int> current_pos = current->GetPosition(0);
        std::pair<int, int> parent_pos = current->getParent()->GetPosition(0);
        if (current_pos.first == parent_pos.first) { // the same line
            if (current_pos.second == parent_pos.second + 1) {
                reversed_answer.append("R");
            } else if (current_pos.second == parent_pos.second - 1) {
                reversed_answer.append("L");
            }
        } else { // the same column
            if (current_pos.first == parent_pos.first + 1) {
                reversed_answer.append("D");
            } else if (current_pos.first == parent_pos.first - 1) {
                reversed_answer.append("U");
            }
        }
        current = current->getParent();
    }
    std::reverse(reversed_answer.begin(), reversed_answer.end());
    return reversed_answer;
}