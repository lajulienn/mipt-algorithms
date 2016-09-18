#ifndef MY_MAP_
#define MY_MAP_

#include <utility>

template <typename K, typename V>
class MyMap {
public:
	MyMap() : root_(&NIL), size_(0) {}

	void erase(K key);
	void clear();
	bool empty() const { return size_ == 0; }
	V &operator[](K key);
	V operator[](K key) const;
	void dump();
	int size() const { return size_; }
	bool exist(K key) { return TreeSearch(key) != &NIL ? true : false; }

private:

	static const char BLACK = 'B';
	static const char RED = 'R';

	friend class Node;
	struct Node {
		friend class MyMap;
		K key;
		V value;
	private:
		Node(K key = K(), V value = V(), char color = RED) : key(key), value(value), right(&NIL), left(&NIL), parent(&NIL), color(color) {}

		Node *right;
		Node *left;
		Node *parent;

		char color;
	};

	void LeftRotate(Node *x);
	void RightRotate(Node *y);
	void TreeInsert(Node *x);
	void Insert(K key);
	Node *TreeSuccessor(Node *x);
	Node *TreeMinimum(Node *x);
	void eraseFixup(Node *x);
	void TreeDelete(Node *node);

	static Node NIL;
	Node *root_;
	int size_;

	friend class Iterator;
public:
	Node *TreeSearch(K key);

	class Iterator {
	private:
		Iterator(MyMap *m, Node *n) : map(m), node(n) {}

		MyMap *map;
		Node *node;
	public:
		friend class MyMap;

		Iterator(const Iterator &it) : node(it.node) {}
		Iterator &operator++() { node = map->TreeSuccessor(node); return *this; }
		bool operator==(const Iterator &other) { return node == other.node; }
		bool operator!=(const Iterator &other) { return node != other.node; }
		const Node &operator*() { return *node; }
		const Node *operator->() { return node; }
	};

	Iterator begin();
	Iterator end();
	Iterator insert(K key, V value);
};

template <typename K, typename V>
typename MyMap<K, V>::Node MyMap<K, V>::NIL(K(), V(), MyMap<K, V>::BLACK);

template <typename K, typename V>
void MyMap<K, V>::LeftRotate(Node *x) {
	Node *y = x->right;
	x->right = y->left;
	if (y->left != &NIL)
		y->left->parent = x;
	y->parent = x->parent;
	if (x->parent == &NIL) {
		this->root_ = y;
	} else if (x == x->parent->left) {
		x->parent->left = y;
	} else {
		x->parent->right = y;
	}
	y->left = x;
	x->parent = y;
}

template <typename K, typename V>
void MyMap<K, V>::RightRotate(Node *y) {
	Node *x = y->left;
	y->left = x->right;
	if (x->right != &NIL)
		x->right->parent = y;
	x->parent = y->parent;
	if (y->parent == &NIL) {
		root_ = x;
	} else if (y == y->parent->left) {
		y->parent->left = x;
	} else {
		y->parent->right = x;
	}
	x->right = y;
	y->parent = x;
}

template <typename K, typename V>
void MyMap<K, V>::Insert(K key) {
	Node *x = new Node(key);
	TreeInsert(x);
	x->color = RED;
	while (x != root_ && x->parent->color == RED) {
		if (x->parent == x->parent->parent->left) {
			Node *y = x->parent->parent->right;
			if (y->color == RED) {
				x->parent->color = BLACK;
				y->color = BLACK;
				x->parent->parent->color = RED;
				x = x->parent->parent;
			} else {
				if (x == x->parent->right) {
					x = x->parent;
					LeftRotate(x);
				}
				x->parent->color = BLACK;
				x->parent->parent->color = RED;
				RightRotate(x->parent->parent);
			}
		} else {
			Node *y = x->parent->parent->left;
			if (y->color == RED) {
				x->parent->color = BLACK;
				y->color = BLACK;
				x->parent->parent->color = RED;
				x = x->parent->parent;
			} else {
				if (x == x->parent->left) {
					x = x->parent;
					RightRotate(x);
				}
				x->parent->color = BLACK;
				x->parent->parent->color = RED;
				LeftRotate(x->parent->parent);
			}
		}
	} //while
	root_->color = BLACK;
	++size_;
}

template <typename K, typename V>
void MyMap<K, V>::TreeInsert(Node *z) {
	Node *y = &NIL;
	Node *x = root_;
	while (x != &NIL) {
		y = x;
		if (z->key < x->key)
			x = x->left;
		else
			x = x->right;
	}
	z->parent = y;
	if (y == &NIL) {
		root_ = z;
	} else {
		if (z->key < y->key)
			y->left = z;
		else
			y->right = z;
	}
}

template <typename K, typename V>
void MyMap<K, V>::erase(K key) {
	Node *z = TreeSearch(key);
	if (z == &NIL)
		return;
	Node *y;
	Node *x;
	if (z->left == &NIL || z->right == &NIL) {
		y = z;
	} else {
		y = TreeSuccessor(z);
	}

	if (y->left != &NIL) {
		x = y->left;
	} else {
		x = y->right;
	}
	x->parent = y->parent;
	if (y->parent == &NIL) {
		root_ = x;
	} else {
		if (y == y->parent->left) {
			y->parent->left = x;
		} else {
			y->parent->right = x;
		}
	}
	if (y != z){
		z->key = y->key;
		z->value = y->value;
	}
	if (y->color == BLACK)
		eraseFixup(x);
	--size_;
	delete y; //z
}

template <typename K, typename V>
typename MyMap<K, V>::Node *MyMap<K, V>::TreeSuccessor(Node *x) {
	if (x->right != &NIL) {
		return TreeMinimum(x->right);
	}
	Node *y = x->parent;
	while (y != &NIL && x == y->right) {
		x = x->parent;
		y = y->parent;
	}
	return y;
}

template <typename K, typename V>
typename MyMap<K, V>::Node *MyMap<K, V>::TreeMinimum(Node *x) {
	while (x->left != &NIL)
		x = x->left;
	return x;
}

template <typename K, typename V>
void MyMap<K, V>::eraseFixup(Node *x) {
	while (x != root_ && x->color == BLACK) {
		if (x == x->parent->left) {
			Node *w = x->parent->right;
			if (w->color == RED) {
				w->color = BLACK;
				x->parent->color = RED;
				LeftRotate(x->parent);
				w = x->parent->right;
			}
			if (w->left->color == BLACK && w->right->color == RED) {
				w->color = RED;
				x = x->parent;
			} else {
				if (w->right->color == BLACK) {
					w->left->color = BLACK;
					w->color = RED;
					RightRotate(w);
					w = x->parent->right;
				}
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->right->color = BLACK;
				LeftRotate(x->parent);
				x = root_;
			}
			//delete w;
		} else {
			Node *w = x->parent->left;
			if (w->color == RED) {
				w->color = BLACK;
				x->parent->color = RED;
				RightRotate(x->parent);
				w = x->parent->left;
			}
			if (w->right->color == BLACK && w->left->color == RED) {
				w->color = RED;
				x = x->parent;
			} else {
				if (w->left->color == BLACK) {
					w->right->color = BLACK;
					w->color = RED;
					LeftRotate(w);
					w = x->parent->left;
				}
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->left->color = BLACK;
				RightRotate(x->parent);
				x = root_;
			}
			//delete w;
		}
	}//while
}

template <typename K, typename V>
void MyMap<K, V>::dump() {
	for (auto x : *this) {
		cout << x.key << " " << x.value << endl;
	}
}

template <typename K, typename V>
typename MyMap<K, V>::Node *MyMap<K, V>::TreeSearch(K key) {
	Node *x = root_;
	while (x != &NIL && key != x->key) {
		if (key < x->key)
			x = x->left;
		else
			x = x->right;
	}
	return x;
}

template <typename K, typename V>
V &MyMap<K, V>::operator[](const K key) {
	Node *x = TreeSearch(key);
	if (x == &NIL) {
		Insert(key);
		x = TreeSearch(key);
	}
	return x->value;
}

template <typename K, typename V>
V MyMap<K, V>::operator[](const K key) const {
	Node *x = TreeSearch(key);
	if (x == &NIL) {
		Insert(key);
		x = TreeSearch(key);
	}
	return x->value;
}

template <typename K, typename V>
typename MyMap<K, V>::Iterator MyMap<K, V>::begin() {
	return Iterator(this, TreeMinimum(root_));
}

template <typename K, typename V>
typename MyMap<K, V>::Iterator MyMap<K, V>::end() {
	return Iterator(this, &NIL);
}

template <typename K, typename V>
typename MyMap<K, V>::Iterator MyMap<K, V>::insert(K key, V value) {
	Node *node = TreeSearch(key);
	if (node != &NIL) {
		return Iterator(this, node);
	}
	operator[](key) = value;
	return Iterator(this, TreeSearch(key));
}

template <typename K, typename V>
void MyMap<K, V>::clear() {
	if (root_ == &NIL)
		return;
	TreeDelete(root_);
	root_ = &NIL;
	size_ = 0;
}

template <typename K, typename V>
void MyMap<K, V>::TreeDelete(Node *node) {
	if (node->left != &NIL) {
		TreeDelete(node->left);
	}
	if (node->right != &NIL) {
		TreeDelete(node->right);
	}
	delete node;
}

#endif
