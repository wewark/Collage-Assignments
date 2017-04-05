#include "SelectionSorter.h"
#include <algorithm>
using namespace std;


SelectionSorter::SelectionSorter()
{
}


SelectionSorter::~SelectionSorter()
{
}

void SelectionSorter::sort(vector<int> &arr, int low, int high)
{
	for (int i = 0; i < arr.size(); i++) {
		int minIndex = i;
		for (int j = i + 1; j < arr.size(); j++)
			if (arr[j] < arr[minIndex])
				minIndex = j;
		swap(arr[i], arr[minIndex]);
	}
}
