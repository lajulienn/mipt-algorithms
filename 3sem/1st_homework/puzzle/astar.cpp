#include "astar.h"

#include <memory>
#include <map>
#include <set>
#include <algorithm>

#include "puzzle.h"
#include "permutation.h"


std::string Astar(Permutation &start, Permutation &finish) {
    const int step_cost = 1;

    std::vector<std::unique_ptr<Permutation>> all_permutations;

    std::map<Permutation, Variables> viewed;

    std::set<std::pair<int, Permutation *>> queue;

    all_permutations.push_back(std::move(std::make_unique<Permutation>(start)));
    Permutation *start_ptr = all_permutations.back().get();
    viewed[start] = Variables(start_ptr, 0, 0 + start.heuristic);
    queue.insert({viewed[start].f, start_ptr});
    Permutation *current = start_ptr;
    uint64_t step_count = 0;
    while (queue.size() != 0) {
        current = queue.begin()->second;
        int current_f = queue.begin()->first;

        if (*current == finish)
            break;
        queue.erase({current_f, current});
        Variables &current_var = viewed[*current];
        current_var.enqueued = false;
        for (auto &neighbour : current->getNeighbours()) {
            int distance = current_var.distance + step_cost;
            auto it = viewed.find(neighbour);
            if (it == viewed.end()) {
                all_permutations.push_back(std::make_unique<Permutation>(neighbour));
                viewed[neighbour] = Variables(all_permutations.back().get(), distance, distance + neighbour.heuristic,
                                              current, true);
                queue.insert({distance + neighbour.heuristic, all_permutations.back().get()});
            } else {
                Variables &neighbour_var = viewed[neighbour];
                if (distance < neighbour_var.distance) {
                    neighbour_var.parent = current; // changed start_ptr --> current
                    neighbour_var.distance = distance;
                    neighbour_var.f = distance + neighbour.heuristic;
                    //if (!neighbour_var.enqueued) {
                    queue.insert({distance + neighbour.heuristic, neighbour_var.id});
                    neighbour_var.enqueued = true;
                    //}
                }
            }
        }
    }
    // after we found a solution
    std::string reversed_answer;
    while (!(*current == start)) {
        std::pair<int, int> current_pos = GetPosition(0, current->permutation);
        std::pair<int, int> parent_pos = GetPosition(0, viewed[*current].parent->permutation);
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
        current = viewed[*current].parent;
    }
    std::reverse(reversed_answer.begin(), reversed_answer.end());
    return reversed_answer;
}
