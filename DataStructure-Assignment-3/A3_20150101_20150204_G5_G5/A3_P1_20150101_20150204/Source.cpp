#include <iostream>
#include "LList.h"
using namespace std;

int main() {
	LList<int> list;
	for (int i = 0; i < 10; i++)
		list.push_front(i);
	list.print();
	cout << list.size() << endl;
	LList<int>::iterator itr = list.end();
	cout << *--itr << endl;
	list.erase(list.begin() + 3);
	list.erase(itr);
	list.print();

	cout << endl << "List of lists:" << endl;
	LList<LList<int>> list2d;
	for (int i = 0; i < 10; i++)
		list2d.push_front(list);
	for (LList<LList<int>>::iterator i = list2d.begin(); i != list2d.end(); i++) {
		for (LList<int>::iterator j = i->begin(); j != i->end(); j++)
			cout << *j << " ";
		cout << endl;
	}

	cin.get();
}
