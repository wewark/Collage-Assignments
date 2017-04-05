#include <iostream>
#include "QuickSorter.h"
#include "SelectionSorter.h"
#include "Testbed.h"
#include <vector>
#include <time.h>
#include <fstream>
using namespace std;

int main() {
	srand(time(NULL));
	QuickSorter qs;
	SelectionSorter ss;
	Testbed tb;
	const int
		min_num = 0,
		max_num = 1e9,
		min_size = 5000,
		max_size = 100000,
		sets_num = 10,
		step = 5000;
	vector<double> qs_rand, qs_rev, ss_rand, ss_rev;

	// Quick sort random
	cout << "Quick sort random" << endl;
	qs_rand = tb.runExperiment(&qs, 0, min_num, max_num, min_size, max_size, sets_num, step);
	// Selection sort random
	cout << "Selection sort random" << endl;
	ss_rand = tb.runExperiment(&ss, 0, min_num, max_num, min_size, max_size, sets_num, step);
	// Quick sort reversed
	cout << "Quick sort reversed" << endl;
	qs_rev = tb.runExperiment(&qs, 1, min_num, max_num, min_size, max_size, sets_num, step);
	// Selection sort reversed
	cout << "Selection sort reversed" << endl;
	ss_rev = tb.runExperiment(&ss, 1, min_num, max_num, min_size, max_size, sets_num, step);

	// Write everything to file
	fstream file("graph_data.csv", ios::out);
	file << "Size,Quick sort random,Selection sort random,";
	file << "Quick sort reversed, Selection sort reversed" << endl;
	for (int set_size = min_size, i = 0; set_size <= max_size; set_size += step, i++) {
		file << set_size << ",";
		file << qs_rand[i] << ",";
		file << ss_rand[i] << ",";
		file << qs_rev[i] << ",";
		file << ss_rev[i] << endl;
	}

	cin.ignore(), cin.get();
}
