/**
 * @author Julia Ivanova
 */

#include <vector>
#include <queue>
#include "include/binary_tree.h"

void BinaryTree::Insert(long key) {
    if(root == nullptr) {
        root = NodePtr(new BinaryTree::Node(key));
        return;
    }
    Insert(*root, key);
}

void BinaryTree::Insert(Node &node, long key) {
    if (node.key < key) {
        if (node.left == nullptr) {
            node.left = NodePtr(new BinaryTree::Node(key));
        } else {
            Insert(*(node.left), key);
        }
    } else {
        if (node.right == nullptr) {
            node.right = NodePtr(new BinaryTree::Node(key));
        } else {
            Insert(*(node.right), key);
        }
    }
    return;
}

int BinaryTree::GetHeight(BinaryTree::Node &node) {
    int left = 0;
    int right = 0;
    if(node.left != nullptr) {
        left = GetHeight(*(node.left));
    }
    if(node.right != nullptr) {
        right = GetHeight(*(node.right));
    }

    return std::max(left, right) + 1;
}

int BinaryTree::GetHeight() {
    return root != nullptr ? GetHeight(*root) : 0;
}

int BinaryTree::GetWidth() {
    if (root == nullptr) {
        return 0;
    }
    int height = this->GetHeight();
    std::vector<int> width(height);
    width[0] = 0;
    std::queue<std::pair<Node &, int>> queue;
    queue.push({*root, 0});
    while (!queue.empty()) {
        Node &node = queue.front().first;
        int level = queue.front().second;
        queue.pop();
        if (node.left != nullptr) {
            ++width[level + 1];
            queue.push({*(node.left), level + 1});
        }
        if (node.right != nullptr) {
            ++width[level + 1];
            queue.push({*(node.right), level + 1});
        }
    }
    int max_width = 0;
    for (auto x : width) {
        if (x > max_width) {
            max_width = x;
        }
    }
    return max_width;
}