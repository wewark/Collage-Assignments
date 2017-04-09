#include <iostream>
using namespace std;

template<class T>
struct node {
	T value;
	node<T>* next = NULL;
	node<T>* prev = NULL;
	node(const T& val) { value = val; }
};

template<class T>
class LList {
public:
	class iterator
	{
	private:
		node<T>* ptr;
	public:
		iterator() {
			ptr = NULL;
		}
		iterator(node<T>* new_ptr) {
			ptr = new_ptr;
		}
		~iterator() {}

		iterator operator ++ (int) {
			// TODO
		}
		iterator operator ++ () {
			// TODO
		}

		iterator operator -- (int) {
			// TODO
		}
		iterator operator -- () {
			// TODO
		}

		bool operator == (const iterator& other) {
			// TODO
		}
	};

private:
	node<T>* head;
	node<T>* tail;

public:
	LList() {
		node<T>* dummy = new node<T>(-1);
		head = tail = dummy;
	}
	LList(const T& val, int initial_size) {
		for (int i = 0; i < initial_size; i++)
			push_back(val);
	}
	~LList() {
		while (!empty())
			pop_back();
	}

	void push_front(const T& val) {
		node<T>* new_node = new node<T>(val);
		new_node->next = head;
		head->prev = new_node;
		head = new_node;
	}
	void push_back(const T& val) {
		node<T>* new_node = new node<T>(val);
		if (tail->prev) {
			tail->prev->next = new_node;
			new_node->prev = tail->prev;
		}
		else head = new_node;

		new_node->next = tail;
		tail->prev = new_node;
	}

	void pop_front() {
		if (!empty()) {
			node<T>* old_node = head;
			head = head->next;
			head->prev = NULL;
			delete old_node;
		}
		else throw "Poping from empty list";
	}
	void pop_back() {
		if (!empty()) {
			node<T>* old_node = tail->prev;
			if (tail->prev->prev) {
				node<T>* new_last = tail->prev->prev;
				new_last->next = tail;
				tail->prev = new_last;
			}
			else {
				head = tail;
				tail->prev = NULL;
			}
			delete old_node;
		}
		else throw "Poping from empty list";
	}

	void print() {
		node<T>* cur_node = head;
		while (cur_node->next) {
			cout << cur_node->value << " ";
			cur_node = cur_node->next;
		}
		cout << endl;
	}

	int size() {
		int cur_size = 0;
		node<T>* cur_node = head;
		while (cur_node->next) {
			cur_size++;
			cur_node = cur_node->next;
		}
		return cur_size;
	}

	bool empty() {
		return size() == 0;
	}

	void insert(const T& val, iterator positon) {
		// TODO
	}

	iterator erase(iterator position) {
		// TODO
	}

	LList<T>& operator = (LList<T> other) {
		// TODO
	}

	iterator begin() {
		// TODO
	}

	iterator end() {
		// TODO
	}
};

int main() {
	LList<int> list;
	//list.pop_front();
	for (int i = 0; i < 10; i++) {
		list.push_front(i);
	}
	list.print();
	list.pop_front();
	list.pop_front();
	list.print();
	cin.get();
}
