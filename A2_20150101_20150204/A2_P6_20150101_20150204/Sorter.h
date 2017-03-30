#pragma once
#include <vector>
using namespace std;

class Sorter
{
public:
	Sorter();
	~Sorter();
	virtual void sort(vector<int> &arr, int low, int high) = 0;
};

