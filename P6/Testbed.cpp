#include "Testbed.h"
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <chrono>

Testbed::Testbed()
{
}


Testbed::~Testbed()
{
}

vector<int> Testbed::generateRandomList(int minNum, int maxNum, int arrSize)
{
	vector<int> arr(arrSize);
	for (int i = 0; i < arrSize; i++)
		arr[i] = randBetween(minNum, maxNum);
	return arr;
}

vector<int> Testbed::generateReverseOrderedList(int minNum, int maxNum, int arrSize)
{
	vector<int> arr(arrSize);
	for (int i = 0; i < arrSize; i++)
		arr[i] = randBetween(minNum, maxNum);
	sort(arr.rbegin(), arr.rend());
	return arr;
}

int Testbed::runOnce(Sorter* sorter, vector<int>& arr)
{
	clock_t begin = clock();

	sorter->sort(arr, 0, arr.size() - 1);

	clock_t end = clock();
	int elapsed_ms = end - begin;
	return elapsed_ms;
}

double Testbed::runAndAverage(Sorter * sorter, int type, int minNum, int maxNum, int arrSize, int setsNum)
{
	int sum = 0;
	vector<int> arr;

	if (type == 1) // Random
		for (int i = 0; i < setsNum; i++) {
			arr = generateRandomList(minNum, maxNum, arrSize);
			sum += runOnce(sorter, arr);
		}
	else if (type == 2) // Reversed
		for (int i = 0; i < setsNum; i++) {
			arr = generateReverseOrderedList(minNum, maxNum, arrSize);
			sum += runOnce(sorter, arr);
		}

	return sum / (double)setsNum;
}

inline int Testbed::randBetween(int minNum, int maxNum)
{
	srand(time(NULL));
	return rand() % (maxNum - minNum + 1) + minNum;
}
