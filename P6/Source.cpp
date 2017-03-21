#include <iostream>
#include "QuickSorter.h"
#include "SelectionSorter.h"
#include "Testbed.h"
#include <vector>
using namespace std;

int main() {
	vector<int> arr = { 5,6,8,1,9,85,45 };
	QuickSorter x;
	//x.sort(arr, 7, 0, 6);
	SelectionSorter y;
	Testbed z;
	cout << z.runAndAverage(&x, 1, 0, 1e9, 1000, 1000) << endl;
	cout << z.runAndAverage(&y, 1, 0, 1e9, 1000, 1000) << endl;
	cin.ignore(), cin.get();
}
