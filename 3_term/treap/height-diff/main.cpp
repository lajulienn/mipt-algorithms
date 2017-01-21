/**
 * @author Julia Ivanova
 */

#include <iostream>

#include "binary_tree.h"
#include "treap.h"

int main() {
    Treap treap;
    BinaryTree bin_tree;

    int size;
    std::cin >> size;

    for (int i = 0; i < size; ++i) {
        long key, priority;
        std::cin >> key >> priority;
        treap.Insert(key, priority);
        bin_tree.Insert(key);
    }
    std::cout << bin_tree.GetHeight() - treap.GetHeight() << std::endl;
    return 0;
}