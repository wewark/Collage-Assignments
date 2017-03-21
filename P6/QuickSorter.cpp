#include "QuickSorter.h"
#include <algorithm>
using namespace std;



QuickSorter::QuickSorter()
{
}


QuickSorter::~QuickSorter()
{
}

void QuickSorter::sort(vector<int> &arr, int low, int high)
{
	if (low < high) {
		int pivot = partition(arr, low, high);

		sort(arr, low, pivot - 1);
		sort(arr, pivot + 1, high);
	}
}

int QuickSorter::partition(vector<int> &arr, int low, int high)
{
	int pivot = arr[high];
	int i = low;

	for (int j = low; j <= high - 1; j++)
		if (arr[j] <= pivot)
		{
			swap(arr[i], arr[j]);
			i++;
		}

	// Put the pivot in the middle
	swap(arr[i], arr[high]);
	return i;
}
