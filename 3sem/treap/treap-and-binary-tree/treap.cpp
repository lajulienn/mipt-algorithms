/**
 * @author Julia Ivanova
 */

#include "include/treap.h"

#include <iostream>
#include <vector>
#include <queue>

std::pair<TreapNodePtr, TreapNodePtr> Treap::split(TreapNodePtr node, long key) {
    if (node == nullptr) {
        return std::pair<TreapNodePtr, TreapNodePtr>(nullptr, nullptr);
    } else if (key > node->key) {
        std::pair<TreapNodePtr, TreapNodePtr> partition = split(std::move(node->right), key);
        node->right = std::move(partition.first);
        return std::pair<TreapNodePtr, TreapNodePtr>(std::move(node), std::move(partition.second));
    } else {
        std::pair<TreapNodePtr, TreapNodePtr> partition = split(std::move(node->left), key);
        node->left = std::move(partition.second);
        return std::pair<TreapNodePtr, TreapNodePtr>(std::move(partition.first), std::move(node));
    }
};

void Treap::Insert(long key, long priority) {
    if (root == nullptr) {
        root = TreapNodePtr(new Treap::Node(key, priority));
    } else if (root->priority < priority) {
        std::pair<TreapNodePtr, TreapNodePtr> partition = split(std::move(root), key);
        root = TreapNodePtr(new Treap::Node(key, priority));
        root->left = std::move(partition.first);
        root->right = std::move(partition.second);
    } else {
        Insert(*root, key, priority);
    }
}

void Treap::Insert(Node &node, long key, long priority) {
    TreapNodePtr node_to_split = nullptr;
    bool leftIsSplited = false;

    if (key < node.key && node.left != nullptr && node.left->priority < priority) {
        node_to_split = std::move(node.left);
        leftIsSplited = true;
    } else if (key >= node.key && node.right != nullptr && node.right->priority < priority) {
        node_to_split = std::move(node.right);
    }
    if (node_to_split != nullptr) {
        std::pair<TreapNodePtr, TreapNodePtr> partition = split(std::move(node_to_split), key);
        TreapNodePtr new_node = TreapNodePtr(new Treap::Node(key, priority));
        new_node->left = std::move(partition.first);
        new_node->right = std::move(partition.second);
        if (leftIsSplited) {
            node.left = std::move(new_node);
        } else {
            node.right = std::move(new_node);
        }
        return;
    } else if (key < node.key) {
        if (node.left == nullptr) {
            node.left =  TreapNodePtr(new Treap::Node(key, priority));
            return;
        }
        Insert(*(node.left), key, priority);
    } else {
        if (node.right == nullptr) {
            node.right = TreapNodePtr(new Treap::Node(key, priority));
            return;
        }
        Insert(*(node.right), key, priority);
    }
}

int Treap::GetHeight(Treap::Node &node) {
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

int Treap::GetHeight() {
    return root != nullptr ? GetHeight(*root) : 0;
}

int Treap::GetWidth() {
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
