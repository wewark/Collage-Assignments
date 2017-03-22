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
	void runExperiment(Sorter* sorter, int type, int minNum, int maxNum, int min_val, int max_val, int sets_num, int step);
private:
	inline int randBetween(int minNum, int maxNum);
};

