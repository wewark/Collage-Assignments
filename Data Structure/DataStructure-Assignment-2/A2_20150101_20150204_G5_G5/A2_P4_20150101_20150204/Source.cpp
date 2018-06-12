#include <iostream>
#include <vector>
#include <time.h>
#include <fstream>
#include <algorithm>
using namespace std;

// Returns a vector of size n filled with rands
inline vector<int> randVector(int n) {
	vector<int> ret(n);
	for (int i = 0; i < n; i++)
		ret[i] = rand() % ((int)1e9 + 1);
	return ret;
}

int normalInsertionSort(vector<int> arr) {
	clock_t begin = clock();

	int cur, j;
	for (int i = 1; i < arr.size(); i++) {
		cur = arr[i];
		for (j = i; j > 0 && arr[j - 1] > cur; j--)
			arr[j] = arr[j - 1];
		arr[j] = cur;
	}

	clock_t end = clock();
	int elapsed_ms = end - begin;
	return elapsed_ms;
}

int doubleInsertionSort(vector<int> arr) {
	clock_t begin = clock();

	for (int i = 1; i < arr.size() - 1; i += 2) {
		// arr[i] and arr[i + 1] are to be inserted
		int mn = min(arr[i], arr[i + 1]);
		int mx = max(arr[i], arr[i + 1]);

		int j;
		// Keep shifting both while the max of them is smaller than the next element
		for (j = i; j > 0 && arr[j - 1] > mx; j--)
			arr[j + 1] = arr[j - 1];
		arr[j + 1] = mx;

		// Continue shifting the min of them normally
		for (; j > 0 && arr[j - 1] > mn; j--)
			arr[j] = arr[j - 1];
		arr[j] = mn;
	}
	// The last element may hasn't been inserted
	int last = arr.back(), j;
	for (j = arr.size() - 1; j > 0 && arr[j - 1] > last; j--)
		arr[j] = arr[j - 1];
	arr[j] = last;

	clock_t end = clock();
	int elapsed_ms = end - begin;
	return elapsed_ms;
}

int main() {
	srand(time(NULL));
	fstream file("graph_data.csv", ios::out);
	
	cout << "Size\t\tNormal(ms)\tDouble(ms)" << endl;
	file << "Size,Normal(ms),Double(ms)" << endl;
	for (int arr_size = 5000; arr_size <= 100000; arr_size += 5000) {
		vector<int> arr = randVector(arr_size);
		int normal_result = normalInsertionSort(arr);
		int double_res = doubleInsertionSort(arr);

		cout << arr_size << "\t\t" << normal_result << "\t\t" << double_res << endl;
		file << arr_size << "," << normal_result << "," << double_res << endl;
	}
	cin.ignore(), cin.get();
}