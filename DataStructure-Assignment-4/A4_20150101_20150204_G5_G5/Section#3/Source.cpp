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

	void printInorder() {
		if (root) printInorder(root);
		else cout << "[EMPTY BST]";
		cout << endl;
	}
	void printInorder(BSTNode<T>* cur_node) {
		if (cur_node->left)
			printInorder(cur_node->left);
		cout << cur_node->key << " ";
		if (cur_node->right)
			printInorder(cur_node->right);
	}

	void printPreorder() {
		if (root) printPreorder(root);
		else cout << "[EMPTY BST]";
		cout << endl;
	}
	void printPreorder(BSTNode<T>* cur_node) {
		cout << cur_node->key << " ";
		if (cur_node->left)
			printPreorder(cur_node->left);
		if (cur_node->right)
			printPreorder(cur_node->right);
	}

	void printPostorder() {
		if (root) printPostorder(root);
		else cout << "[EMPTY BST]";
		cout << endl;
	}
	void printPostorder(BSTNode<T>* cur_node) {
		if (cur_node->left)
			printPostorder(cur_node->left);
		if (cur_node->right)
			printPostorder(cur_node->right);
		cout << cur_node->key << " ";
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
				balanceAddition(cur_node->left);
		}

		else {
			insert(key, cur_node->right);
			if (cur_node->right)
				cur_node->right->parent = cur_node;

			// To balance the tree one time only
			if (!balanced)
				balanceAddition(cur_node->right);
		}
	}

	// Balance the tree after a node is added
	void balanceAddition(BSTNode<T>* cur_child) {
		balanced = true;

		// We loop from cur_child up to the root
		// Fixing nodes with wrong balance factor 
		// by applying the appropriate rotation
		for (BSTNode<T>* cur_parent = cur_child->parent;
			cur_parent != NULL;
			cur_parent = cur_child->parent) {
			// For the original parent before any rotating
			// and the child that's gonna be under it
			BSTNode<T> *new_child, *original_parent;

			/*
				The balance factor hasn't been updated yet, so the deletion is taken into
				consideration in the if conditions below (it will increase or decrease by one)
			*/

			// If it's the right child
			if (cur_child == cur_parent->right) {
				if (cur_parent->balanceFactor > 0) {
					// Preserving the current parent as the original one
					// to connect it to the new child after rotation
					original_parent = cur_parent->parent;

					// Deciding whether to do single or double rotation
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
				else { // balanceFactor == 0
					cur_parent->balanceFactor = 1;
					// To proceed in the loop
					cur_child = cur_parent;
					continue;
				}
			}

			// If it's the left child
			else {
				if (cur_parent->balanceFactor < 0) {
					// Preserving the current parent as the original one
					// to connect it to the new child after rotation
					original_parent = cur_parent->parent;

					// Deciding whether to do single or double rotation
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
				else { // balanceFactor == 0
					cur_parent->balanceFactor = -1;
					// To proceed in the loop
					cur_child = cur_parent;
					continue;
				}
			}

			// This part will only be reached if a rotation is done
			// Otherwise it will just break or continue from the part above

			// Connect the original parent and the new child
			new_child->parent = original_parent;
			if (original_parent) {
				// If the old child was the original parent's left
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

	// Returns the new root after rotating the subtree
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

	// Returns the new root after rotating the subtree
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

	// Returns the new root after doubly rotating the subtree
	BSTNode<T>* rotateRightLeft(BSTNode<T>*& cur_node) {
		cur_node->right = rotateRight(cur_node->right);

		return rotateLeft(cur_node);
	}

	// Returns the new root after doubly rotating the subtree
	BSTNode<T>* rotateLeftRight(BSTNode<T>*& cur_node) {
		cur_node->left = rotateLeft(cur_node->left);

		return rotateRight(cur_node);
	}

	void deleteValue(const T& key) {
		BSTNode<T>* cur_node = search(key);
		if (cur_node)
			deleteNode(cur_node);
	}

	void deleteNode(BSTNode<T>*& cur_node) {
		// If it has both children or right child only
		// Get
		if (cur_node->right && cur_node->left || cur_node->right) {
			BSTNode<T>* successor = cur_node->right;
			while (successor->left)
				successor = successor->left;
			cur_node->key = successor->key;
			deleteNode(successor);
		}

		else if (cur_node->left) {
			BSTNode<T>* successor = cur_node->left;
			while (successor->right)
				successor = successor->right;
			cur_node->key = successor->key;
			deleteNode(successor);
		}

		else {
			balanceDeletion(cur_node);
			if (cur_node->parent->right == cur_node)
				cur_node->parent->right = NULL;
			else if (cur_node->parent->left == cur_node)
				cur_node->parent->left = NULL;
			delete cur_node;
		}
	}

	// Balance the tree after a node is deleted
	void balanceDeletion(BSTNode<T>* cur_child) {

		// We loop from cur_child up to the root
		// Fixing nodes with wrong balance factor 
		// by applying the appropriate rotation
		for (BSTNode<T>* cur_parent = cur_child->parent;
			cur_parent != NULL;
			cur_parent = cur_child->parent) {

			// For the original parent before any rotating
			// and the child that's gonna be under it
			BSTNode<T> *new_child, *original_parent, *other_side_child;
			/*
				other_side_child is because, unlike adding, we are on the lighter side of
				the tree, so to see if we're gonna do a signle or double rotation we
				need to know the balance factor of the child of the other side.

				The balance factor hasn't been updated yet, so the deletion is taken into
				consideration in the if conditions below (it will increase or decrease by one)
			*/

			// If it's the right child
			if (cur_child == cur_parent->right) {
				if (cur_parent->balanceFactor < 0) {
					// Preserving the current parent as the original one
					// to connect it to the new child after rotation
					original_parent = cur_parent->parent;

					// Deciding whether to do single or double rotation
					other_side_child = cur_parent->left;
					if (other_side_child->balanceFactor > 0)
						new_child = rotateLeftRight(cur_parent);
					else
						new_child = rotateRight(cur_parent);
				}
				else if (cur_parent->balanceFactor == 0) {
					cur_parent->balanceFactor = -1;
					break;
				}
				else { // balanceFactor < 0
					cur_parent->balanceFactor = 0;
					// To proceed in the loop
					cur_child = cur_parent;
					continue;
				}
			}

			// If it's the left child
			else {
				if (cur_parent->balanceFactor > 0) {
					// Preserving the current parent as the original one
					// to connect it to the new child after rotation
					original_parent = cur_parent->parent;

					// Deciding whether to do single or double rotation
					other_side_child = cur_parent->right;
					if (other_side_child->balanceFactor < 0)
						new_child = rotateRightLeft(cur_parent);
					else
						new_child = rotateLeft(cur_parent);
				}
				else if (cur_parent->balanceFactor == 0) {
					cur_parent->balanceFactor = 1;
					break;
				}
				else { // balanceFactor < 0
					cur_parent->balanceFactor = 0;
					// To proceed in the loop
					cur_child = cur_parent;
					continue;
				}
			}

			// This part will only be reached if a rotation is done
			// Otherwise it will just break or continue from the part above

			// Connect the original parent and the new child
			new_child->parent = original_parent;
			if (original_parent) {
				// If the old child was the original parent's left
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
};

int main() {
	BSTAVL<double> x;
	for (int i = 0; i < 7; i++)
		x.insert(i);
	x.insert(2.5);

	cout << "Inorder: "; x.printInorder();
	cout << "Preorder: "; x.printPreorder();
	cout << "Postorder: "; x.printPostorder();
	cout << endl;
	x.printInorder();
	x.deleteValue(6); cout << "Remove 6" << endl;
	x.deleteValue(4); cout << "Remove 4" << endl;
	x.printInorder();
	cin.get();
}
