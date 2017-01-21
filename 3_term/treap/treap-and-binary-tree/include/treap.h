/**
 * @author Julia Ivanova
 */

#ifndef TREAP_TREAP_H
#define TREAP_TREAP_H

#include <memory>

#define TreapNodePtr std::unique_ptr<Treap::Node>

class Treap {
    struct Node {
        Node(long k, long p) : key(k), priority(p) {}

        long key;
        long priority;
        TreapNodePtr left = nullptr;
        TreapNodePtr right = nullptr;
    };
    TreapNodePtr root;

    std::pair<TreapNodePtr, TreapNodePtr> split(TreapNodePtr node, long key);
    void Insert(Node &node, long key, long priority);
    int GetHeight(Node &node);
public:
    void Insert(long key, long priority);
    int GetHeight();
    int GetWidth();
};

#endif //TREAP_TREAP_H
