#pragma once
#include <vector>
#include "Sorter.h"
using namespace std;

class Testbed
{
public:
	Testbed();
	~Testbed();
	vector<int> generateRandomList(int minNum, int maxNum, int arrSize);
	vector<int> generateReverseOrderedList(int minNum, int maxNum, int arrSize);
	int runOnce(Sorter* sorter, vector<int> &arr);
	double runAndAverage(Sorter* sorter, int type, int minNum, int maxNum, int arrSize, int setsNum);
private:
	inline int randBetween(int minNum, int maxNum);
};

