#include <iostream>
#include "BSTFCI.h"
using namespace std;

int main() {
	BSTFCI<int> b;
	for (int i = 0; i < 10; i++)
		b.insert(i);

	b.printInOrder();
	b.printRange(4, 8);
	b.clear();
	b.printInOrder();
	b.printRange(4, 8);
	cin.get();
}
