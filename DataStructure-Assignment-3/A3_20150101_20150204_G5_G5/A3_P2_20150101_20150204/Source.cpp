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
		return *list.begin();
	}
	void push(const T& val) {
		list.push_front(val);
	}
	void pop() {
		list.pop_front();
	}
	int size() {
		return list.size();
	}
	bool empty() {
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
