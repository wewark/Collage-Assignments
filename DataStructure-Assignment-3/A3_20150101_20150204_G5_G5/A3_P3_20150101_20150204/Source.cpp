#include <iostream>
#include "LList.h"
using namespace std;

template <class T>
class Queue {
private:
	LList<T> list;
public:
	Queue() {}
	Queue(const T& val, int initial_size) {
		while (initial_size--)
			list.push_back(val);
	}
	~Queue() {
		while (!list.empty())
			list.pop_back();
	}

	T& front() const {
		if (!empty())
			return *list.begin();
		else throw "Trying to get front of empty queue";
	}
	void push(const T& val) {
		list.push_back(val);
	}
	void pop() {
		if (!empty())
			list.pop_front();
		else throw "Trying to pop empty queue";
	}
	int size() const {
		return list.size();
	}
	bool empty() const {
		return list.empty();
	}
};

int main() {
	Queue<int> q;
	for (int i = 0; i < 10; i++)
		q.push(i);
	while (!q.empty()) {
		cout << q.front() << " ";
		q.pop();
	}
	cout << endl;
	cin.get();
}
