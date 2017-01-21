#ifndef RB_TREE
#define RB_TREE

template <typename T>
class RB_tree {
public:
	RB_tree() : root_(&NIL), size_(0) {}

	void RbInsert(T key);
	void RbDelete(T key);
	void Dump();
private:
	struct Node {
		Node(T key = 0, char color = 'R') : right(&NIL), left(&NIL), parent(&NIL), key(key), color(color) {}
		Node *right;
		Node *left;
		Node *parent;
		T key;
		char color;
	};

	void LeftRotate(Node *x);
	void RightRotate(Node *y);
	void TreeInsert(Node *x);
	Node *TreeSuccessor(Node *x);
	Node *TreeMinimum(Node *x);
	void RbDeleteFixup(Node *x);

	static Node NIL;// = Node(0, 'b');
	Node *root_;
	int size_;
public:
	Node *TreeSearch(T key);
};

template <typename T>
typename RB_tree<T>::Node RB_tree<T>::NIL(0, 'B');

template <typename T>
void RB_tree<T>::LeftRotate(Node *x) {
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

template <typename T>
void RB_tree<T>::RightRotate(Node *y) {
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

template <typename T>
void RB_tree<T>::RbInsert(T key) {
	Node *x = new Node(key);
	TreeInsert(x);
	x->color = 'R';
	while (x != root_ && x->parent->color == 'R') {
		if (x->parent == x->parent->parent->left) {
			Node *y = x->parent->parent->right;
			if (y->color == 'R') {
				x->parent->color = 'B';
				y->color = 'B';
				x->parent->parent->color = 'R';
				x = x->parent->parent;
			} else {
				if (x == x->parent->right) {
					x = x->parent;
					LeftRotate(x);
				}
				x->parent->color = 'B';
				x->parent->parent->color = 'R';
				RightRotate(x->parent->parent);
			}
		} else {
			Node *y = x->parent->parent->left;
			if (y->color == 'R') {
				x->parent->color = 'B';
				y->color = 'B';
				x->parent->parent->color = 'R';
				x = x->parent->parent;
			} else {
				if (x == x->parent->left) {
					x = x->parent;
					RightRotate(x);
				}
				x->parent->color = 'B';
				x->parent->parent->color = 'R';
				LeftRotate(x->parent->parent);
			}
		}
	} //while
	root_->color = 'B';
	delete x;
}

template <typename T>
void RB_tree<T>::TreeInsert(Node *z) {
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

template <typename T>
void RB_tree<T>::RbDelete(T key) {
	Node *z = new Node(key);
	Node *y = new Node;
	Node *x = new Node;
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
	if (y != z)
		z->key = y->key;
	if (y->color == 'B')
		RbDeleteFixup(x);
	delete x, y, z;
}

template <typename T>
typename RB_tree<T>::Node *RB_tree<T>::TreeSuccessor(Node *x) {
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

template <typename T>
typename RB_tree<T>::Node *RB_tree<T>::TreeMinimum(Node *x) {
	while (x->left != &NIL)
		x = x->left;
	return x;
}

template <typename T>
void RB_tree<T>::RbDeleteFixup(Node *x) {
	while (x != root_ && x->color == 'B') {
		if (x == x->parent->left) {
			Node *w = new Node;
			w = x->parent->right;
			if (w->color == 'R') {
				w->color = 'B';
				x->parent->color = 'R';
				LeftRotate(x->parent);
				w = x->parent->right;
			}
			if (w->left->color == 'B' && w->right->color == 'R') {
				w->color = 'R';
				x = x->parent;
			} else {
				if (w->right->color == 'B') {
					w->left->color = 'B';
					w->color = 'R';
					RightRotate(w);
					w = x->parent->right;
				}
				w->color = x->parent->color;
				x->parent->color = 'B';
				w->right->color = 'B';
				LeftRotate(x->parent);
				x = root_;
			}
		} else {
			Node *w = x->parent->left;
			if (w->color == 'R') {
				w->color = 'B';
				x->parent->color = 'R';
				RightRotate(x->parent);
				w = x->parent->left;
			}
			if (w->right->color == 'B' && w->left->color == 'R') {
				w->color = 'R';
				x = x->parent;
			} else {
				if (w->left->color == 'B') {
					w->right->color = 'B';
					w->color = 'R';
					LeftRotate(w);
					w = x->parent->left;
				}
				w->color = x->parent->color;
				x->parent->color = 'B';
				w->left->color = 'B';
				RightRotate(x->parent);
				x = root_;
			}
		}
	}//while
}

template <typename T>
void RB_tree<T>::Dump() {
	Node *x = TreeMinimum(root_);
	while (x != &NIL) {
		cout << x->key << " ";
		x = TreeSuccessor(x);
	}
	cout << endl;
}

template <typename T>
typename RB_tree<T>::Node *RB_tree<T>::TreeSearch(T key) {
	Node *x = root_;
	while (x != &NIL && key != x->key) {
		if (key < x->key)
			x = x->left;
		else
			x = x->right;
	}
	return x;
}

#endif