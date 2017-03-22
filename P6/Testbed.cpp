#include "Testbed.h"
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <iostream>
#include <fstream>
using namespace std;

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

	sorter->sort(arr, 0, max(0, (int)arr.size() - 1));

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

void Testbed::runExperiment(Sorter* sorter, int type, int minNum, int maxNum, int min_val, int max_val, int sets_num, int step)
{
	fstream file("graph_data.csv", ios::out);

	vector<int> set;
	vector<double> average_time;
	double cur_average;
	cout << "Size\t\tAverage(ms)" << endl;
	file << "Size,Average(ms)" << endl;

	for (int set_size = min_val; set_size <= max_val; set_size += step) {
		set.push_back(set_size);
		cur_average = runAndAverage(sorter, type, minNum, maxNum, set_size, sets_num);
		average_time.push_back(cur_average);
		cout << set_size << "\t\t" << cur_average << endl;
		file << set_size << "," << cur_average << endl;
	}

	file.close();
}

inline int Testbed::randBetween(int minNum, int maxNum)
{
	return rand() % (maxNum - minNum + 1) + minNum;
}
