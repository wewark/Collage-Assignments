#include <algorithm>
#include <string>
#include <vector>
#include <typeinfo>
#include <bits/stdc++.h>
using namespace std;

template<class T>
class BSTFCI;

template<class T>
class BSTNode {
public:
	T key;
	BSTNode<T> *left, *right;
public:
	BSTNode() {
		left = right = NULL;
	}
	BSTNode(const T& ky, BSTNode<T> *l = NULL, BSTNode<T> *r = NULL) {
		key = ky;
		left = l, right = r;
	}
	BSTNode<T>* getLeft() { return left; }
	BSTNode<T>* getRight() { return right; }
	friend class BSTFCI<T>;

	// Print left, key, right
	void print() {
		if (left) left->print();
		cout << key << " ";
		if (right) right->print();
	}
};

template<class T>
class BSTFCI {
protected:
	BSTNode<T>* root;
public:
	BSTFCI() { root = NULL; }
	bool isEmpty() { return root == NULL; }

	void clear() { clear(root); }
	void clear(BSTNode<T>*& cur_node) {
		if (!cur_node) return;
		clear(cur_node->left);
		clear(cur_node->right);
		delete cur_node;
		cur_node = NULL;
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

	void insert(const T& key) { insert(key, root); }
	// Insert recursively
	BSTNode<T>* insert(const T& key, BSTNode<T>*& cur_node) {
		if (!cur_node)
			cur_node = new BSTNode<T>(key);
		// If it's a string use cpmStr, otherwise just compare
		else if (typeid(T) == typeid(string) && cmpStr(key, cur_node->key) ||
			typeid(T) != typeid(string) && key < cur_node->key)
			cur_node->left = insert(key, cur_node->left);
		else
			cur_node->right = insert(key, cur_node->right);
		return cur_node;
	}

	void printInOrder() {
		if (root) root->print();
		else cout << "[EMPTY BST]";
		cout << endl;
	}

	static string tolowerStr(string s) {
		for (int i = 0; i < s.length(); i++)
			s[i] = tolower(s[i]);
		return s;
	}
	static bool cmpStr(string a, string b) {
		a = tolowerStr(a), b = tolowerStr(b);
		return lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
	}

	bool isBalanced() { return isBalanced(root) != -1; }
	// If the subtree at that node is balanced it returns its height
	// otherwise it returns -1
	int isBalanced(BSTNode<T>*& cur_node) {
		if (!cur_node) return 0;

		int left_height = isBalanced(cur_node->left);
		int right_height = isBalanced(cur_node->right);

		if (left_height != -1 && right_height != -1 && abs(left_height - right_height) <= 1)
			return max(left_height, right_height) + 1;
		else
			return -1;
	}

	bool isSubTree(BSTFCI& t1, BSTFCI& t2) {
		BSTNode<T>* node1, node2;

		// Search for 2 in 1
		node1 = t1.search(t2.root), node2 = t2.root;
		if (compareSub(node1, node2))
			return true;

		// and for 1 in 2
		node1 = t1.root, node2 = t2.search(t1.root);
		if (compareSub(node1, node2))
			return true;

		return false;
	}
	// If subtrees at node1 and at node2 are identical
	bool compareSub(BSTNode<T>*& node1, BSTNode<T>*& node2) {
		return
			node1->key == node2->key &&
			// Left subtree in both is NULL or identical
			(!node1->left && !node2->left || !node1->left && !node2->left && compareSub(node1->left, node2->left)) &&
			// Right as well
			(!node1->right && !node2->right || !node1->right && !node2->right && compareSub(node1->right, node2->right));
	}

	void printRange(const T& low, const T& high) {
		if (!root)
			cout << "[EMPTY BST]";
		else
			printRange(low, high, root);
		cout << endl;
	}
	void printRange(const T& low, const T& high, BSTNode<T>*& cur_node) {
		if (!cur_node) return;

		// If cur key inside range
		if (cur_node->key >= low && cur_node->key <= high) {
			printRange(low, high, cur_node->left);
			cout << cur_node->key << " ";
			printRange(low, high, cur_node->right);
		}

		// Before range
		else if (cur_node->key < low)
			printRange(low, high, cur_node->right);

		// After range
		else if (cur_node->key > high)
			printRange(low, high, cur_node->left);
	}

	// Returns a vector containing all elements sorted
	vector<T> getAll() {
		vector<T> ret;
		getAll(root, ret);
		return ret;
	}
	void getAll(BSTNode<T>*& cur_node, vector<T>& ret) {
		if (!cur_node) return;
		getAll(cur_node->left, ret);
		ret.push_back(cur_node->key);
		getAll(cur_node->right, ret);
	}
};
