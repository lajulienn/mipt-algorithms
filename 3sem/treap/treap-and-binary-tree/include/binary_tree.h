/**
 * @author Julia Ivanova
 */

#ifndef TREAP_BINARY_TREE_H
#define TREAP_BINARY_TREE_H

#include <memory>

#define NodePtr std::unique_ptr<BinaryTree::Node>

class BinaryTree {
    struct Node {
        Node(long k) : key(k) {}

        long key;
        NodePtr left = nullptr;
        NodePtr right = nullptr;
    };

    NodePtr root;

    void Insert(Node &node, long key);
    int GetHeight(Node &node);
public:
    void Insert(long key);
    int GetHeight();
    int GetWidth();
};

#endif //TREAP_BINARY_TREE_H
