#pragma once
#include "Sorter.h"
#include <vector>
using namespace std;

class QuickSorter :
	public Sorter
{
public:
	QuickSorter();
	~QuickSorter();
	void sort(vector<int> &arr, int low, int high);
private:
	int partition(vector<int> &arr, int low, int high);
};

