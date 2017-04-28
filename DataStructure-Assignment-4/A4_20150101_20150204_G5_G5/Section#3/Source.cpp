#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

template<class T>
class BSTAVL;

template<class T>
class BSTNode {
protected:
	T key;
	BSTNode<T> *left, *right, *parent;
	char balanceFactor = 0;
public:
	BSTNode() {
		left = right = parent = NULL;
	}
	BSTNode(const T& ky, BSTNode<T> *l = NULL, BSTNode<T> *r = NULL) {
		key = ky;
		left = l, right = r, parent = NULL;
	}
	friend class BSTAVL<T>;

	// Print left, key, right
	void print() {
		if (left) left->print();
		cout << key << " ";
		if (right) right->print();
	}
};

template<class T>
class BSTAVL {
protected:
	BSTNode<T>* root;
public:
	BSTAVL() { root = NULL; }
	bool isEmpty() { return root == NULL; }

	void clear() { clear(root); }
	void clear(BSTNode<T>*& cur_node) {
		if (!cur_node) return;
		clear(cur_node->left);
		clear(cur_node->right);
		delete cur_node;
		cur_node = NULL;
	}

	void printInOrder() {
		if (root) root->print();
		else cout << "[EMPTY BST]";
		cout << endl;
	}

	BSTNode<T>* search(const T& key) { return search(key, root); }
	// Search recursively
	BSTNode<T>* search(const T& key, BSTNode<T>*& cur_node) {
		if (!cur_node || cur_node->key == key)
			return cur_node;
		if (key < cur_node->key)
			return search(key, cur_node->left);
		else
			return search(key, cur_node->right);
	}

	// A flag to show it's balanced or not
	bool balanced;
	void insert(const T& key) {
		balanced = false;
		insert(key, root);
	}
	// Insert recursively
	void insert(const T& key, BSTNode<T>*& cur_node) {
		if (!cur_node)
			cur_node = new BSTNode<T>(key);

		else if (key < cur_node->key) {
			insert(key, cur_node->left);
			if (cur_node->left)
				cur_node->left->parent = cur_node;

			// To balance the tree one time only
			if (!balanced)
				balance(cur_node->left);
		}

		else {
			insert(key, cur_node->right);
			if (cur_node->right)
				cur_node->right->parent = cur_node;

			// To balance the tree one time only
			if (!balanced)
				balance(cur_node->right);
		}
	}

	void balance(BSTNode<T>* cur_child) {
		balanced = true;
		for (BSTNode<T>* cur_parent = cur_child->parent;
			cur_parent != NULL;
			cur_parent = cur_child->parent) {
			// For the original parent before any rotating
			// and the child that's gonna be under it
			BSTNode<T> *new_child, *original_parent;

			// If it's the right child
			if (cur_child == cur_parent->right) {
				if (cur_parent->balanceFactor > 0) {
					original_parent = cur_parent->parent;

					if (cur_child->balanceFactor < 0)
						new_child = rotateRightLeft(cur_parent);
					else
						new_child = rotateLeft(cur_parent);
				}
				else if (cur_parent->balanceFactor < 0) {
					// The 2 children are equal now
					cur_parent->balanceFactor = 0;
					break;
				}
				else {
					cur_parent->balanceFactor = 1;
					cur_child = cur_parent;
					continue;
				}
			}

			// If it's the left child
			else {
				if (cur_parent->balanceFactor < 0) {
					original_parent = cur_parent->parent;

					if (cur_child->balanceFactor > 0)
						new_child = rotateLeftRight(cur_parent);
					else
						new_child = rotateRight(cur_parent);
				}
				else if (cur_parent->balanceFactor > 0) {
					// The 2 children are equal now
					cur_parent->balanceFactor = 0;
					break;
				}
				else {
					cur_parent->balanceFactor = -1;
					cur_child = cur_parent;
					continue;
				}
			}

			// Connect the original parent and the new child
			new_child->parent = original_parent;
			if (original_parent) {
				if (&cur_parent == &original_parent->left)
					original_parent->left = new_child;
				else
					original_parent->right = new_child;
			}
			else
				root = new_child;
			break;
		}
	}

	// Returns the new root after rotation
	BSTNode<T>* rotateLeft(BSTNode<T>*& cur_node) {
		BSTNode<T>* right_node = cur_node->right;

		cur_node->right = right_node->left;
		if (right_node->left)
			right_node->left->parent = cur_node;

		right_node->left = cur_node;
		right_node->parent = cur_node->parent;

		cur_node->parent = right_node;

		if (right_node->balanceFactor == 0) {
			right_node->balanceFactor = -1;
			cur_node->balanceFactor = 1;
		}
		else {
			cur_node->balanceFactor = 0;
			right_node->balanceFactor = 0;
		}

		return right_node;
	}

	// Returns the new root after rotation
	BSTNode<T>* rotateRight(BSTNode<T>*& cur_node) {
		BSTNode<T>* left_node = cur_node->left;

		cur_node->left = left_node->right;
		if (left_node->right)
			left_node->right->parent = cur_node;

		left_node->right = cur_node;
		left_node->parent = cur_node->parent;

		cur_node->parent = left_node;

		if (left_node->balanceFactor == 0) {
			left_node->balanceFactor = 1;
			cur_node->balanceFactor = -1;
		}
		else {
			cur_node->balanceFactor = 0;
			left_node->balanceFactor = 0;
		}

		return left_node;
	}

	BSTNode<T>* rotateRightLeft(BSTNode<T>*& cur_node) {
		cur_node->right = rotateRight(cur_node->right);

		return rotateLeft(cur_node);
	}

	BSTNode<T>* rotateLeftRight(BSTNode<T>*& cur_node) {
		cur_node->left = rotateLeft(cur_node->left);

		return rotateRight(cur_node);
	}
};

int main() {
	BSTAVL<int> x;
	for (int i = 0; i < 1000; i++)
		x.insert(i);
	x.printInOrder();
	cin.get();
}
