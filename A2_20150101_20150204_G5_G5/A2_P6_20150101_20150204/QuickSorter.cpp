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
	if (high == 0) return;

	int part = partition(arr, low, high);

	if (low < part - 1)
		sort(arr, low, part - 1);
	if (part + 1 < high)
		sort(arr, part + 1, high);
}

int QuickSorter::partition(vector<int>& arr, int low, int high)
{
	int mid = (low + high) / 2;
	int pivot = arr[mid];
	swap(arr[mid], arr[low]);
	int i = low + 1, j = high;

	while (i <= j) {
		while (i <= j && arr[i] < pivot)
			i++;
		while (i <= j && arr[j] >= pivot)
			j--;

		if (i < j)
			swap(arr[i], arr[j]);
	}
	swap(arr[i - 1], arr[low]);
	return i - 1;
}
