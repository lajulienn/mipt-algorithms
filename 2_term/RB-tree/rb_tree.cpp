#include "rb_tree.h"

void LeftRotate(RB_tree *tree, Node *x) {
	Node *y = x->right;
	x->right = y->left;
	if (y->left != NIL)
		y->left->parent = x;
	y->parent = x->parent;
	if (x->parent == NIL) {
		tree->root = y;
	} else if (x == x->parent->left) {
		x->parent->left = y;
	} else {
		x->parent->right = y;
	}
	y->left = x;
	x->parent = y;
}

void RightRotate(RB_tree *tree, Node *y) {
	Node *x = y->left;
	y->left = x->right;
	if (x->right != NIL)
		x->right->parent = y;
	x->parent = y->parent;
	if (y->parent == NIL) {
		tree->root = x;
	} else if (y == y->parent->left) {
		y->parent->left = x;
	} else {
		y->parent->right = x;
	}
	x->right = y;
	y->parent = x;
}

void RbInsert(RB_tree *tree, Node *x) {
	TreeInsert(tree, x);
	x->color = 'R';
	while (x != tree->root && x->parent->color == 'R') {
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
					LeftRotate(tree, x);
				}
				x->parent->color = 'B';
				x->parent->parent->color = 'R';
				RightRotate(tree, x->parent->parent);
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
					RightRotate(tree, x);
				}
				x->parent->color = 'B';
				x->parent->parent->color = 'R';
				LeftRotate(tree, x->parent->parent);
			}
		}
	} //while
	tree->root->color = 'B';
}