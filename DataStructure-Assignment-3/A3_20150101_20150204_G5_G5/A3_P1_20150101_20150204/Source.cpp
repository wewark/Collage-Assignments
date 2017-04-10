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
			if (ptr->next) {
				iterator temp(ptr);
				ptr = ptr->next;
				return temp;
			}
			throw "ptr->next is NULL";
		}
		iterator operator ++ () {
			if (ptr->next) {
				ptr = ptr->next;
				return *this;
			}
			throw "ptr->next is NULL";
		}

		iterator operator -- (int) {
			if (ptr->prev) {
				iterator temp(ptr);
				ptr = ptr->prev;
				return temp;
			}
			throw "ptr->prev is NULL";
		}
		iterator operator -- () {
			if (ptr->prev) {
				ptr = ptr->prev;
				return *this;
			}
			throw "ptr->prev is NULL";
		}

		bool operator == (const iterator& other) {
			return &*ptr == &*other.ptr;
		}
		bool operator != (const iterator& other) {
			return &*ptr != &*other.ptr;
		}

		T& operator * () {
			return ptr->value;
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
		delete tail;
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
		for (LList<T>::iterator itr = begin(); itr != end(); itr++)
			cout << *itr << " ";
		cout << endl;
	}

	int size() {
		int cur_size = 0;
		for (LList<T>::iterator itr = begin(); itr != end(); itr++)
			cur_size++;
		return cur_size;
	}

	bool empty() {
		return begin() == end();
	}

	void insert(const T& val, iterator positon) {
		// TODO
	}

	iterator erase(iterator position) {
		// TODO
	}

	LList<T>& operator = (LList<T> other) {
		while (!empty())
			pop_back();
		for (LList<T>::iterator itr = other.begin(); itr != other.end(); itr++)
			push_back(*itr);
		return *this;
	}

	iterator begin() {
		return iterator(head);
	}

	iterator end() {
		return iterator(tail);
	}
};

int main() {
	LList<int> list;
	//list.pop_front();
	for (int i = 0; i < 10; i++)
		list.push_front(i);
	list.print();
	LList<int>::iterator itr = list.end();
	cout << *--itr << endl;
	LList<int> list2;
	list2.push_back(15);
	list2 = list;
	list2.print();
	cin.get();
}
