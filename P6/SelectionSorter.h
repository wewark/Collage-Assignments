#pragma once
#include "Sorter.h"
#include <vector>
using namespace std;

class SelectionSorter :
	public Sorter
{
public:
	SelectionSorter();
	~SelectionSorter();
	void sort(vector<int> &arr, int low, int high);
};

