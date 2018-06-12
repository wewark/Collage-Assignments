#include <iostream>
#include "LList.h"
using namespace std;

template <class T>
class Stack {
private:
	LList<T> list;
public:
	Stack() {}
	Stack(const T& val, int initial_size) {
		while (initial_size--)
			list.push_back(val);
	}
	~Stack() {
		while (!list.empty())
			list.pop_back();
	}

	T& top() const {
		if (!empty())
			return *list.begin();
		else throw "Trying to get top of empty stack";
	}
	void push(const T& val) {
		list.push_front(val);
	}
	void pop() {
		if (!empty())
			list.pop_front();
		else throw "Trying to pop empty queue";
	}
	int size() {
		return list.size();
	}
	bool empty() const {
		return list.empty();
	}
};

int main() {
	Stack<int> st;
	for (int i = 0; i < 10; i++)
		st.push(i);
	while (!st.empty()) {
		cout << st.top() << " ";
		st.pop();
	}
	cout << endl;
	cin.get();
}
