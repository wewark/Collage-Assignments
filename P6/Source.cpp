#include <iostream>
#include "QuickSorter.h"
#include "SelectionSorter.h"
#include "Testbed.h"
#include <vector>
#include <time.h>
using namespace std;

int main() {
	srand(time(NULL));
	vector<int> arr = { 5,6,8,1,9,85,45 };
	QuickSorter x;
	//x.sort(arr, 0, 6);
	SelectionSorter y;
	Testbed z;
	//cout << z.runAndAverage(&x, 1, 0, 1e9, 1000, 1000) << endl;
	//cout << z.runAndAverage(&y, 1, 0, 1e9, 1000, 1000) << endl;
	z.runExperiment(&x, 1, 0, 1e9, 0, 100000, 100, 5000);
	cin.ignore(), cin.get();
}
