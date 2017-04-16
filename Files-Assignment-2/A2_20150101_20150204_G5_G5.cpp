#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

class Index
{
private:
	fstream data_file;
	fstream PIndex_file;
	fstream SIndex_file;
	char data_path[20] = "data.txt";
	char PIndex_path[20] = "primary.txt";
	char SIndex_path[20] = "secondary.txt";

	struct printer
	{
		char id[30];
		char model[30];
		char description[50];
		double price;
		char length() {
			return strlen(id) + strlen(model) + strlen(description) + sizeof(price) + 4;
		}
	};
	struct PIndexRecord
	{
		char PK[30]; // id
		int offset;
	};
	struct SIndexRecord
	{
		char SK[30]; // model
		int index; // index of record in PIndex vector
	};
	vector<PIndexRecord> PIndex;

public:
	Index() {
		data_file.open(data_path, ios::in | ios::out);
	}
	~Index() {
		data_file.close();
	}

	static const int MAX_BUFFER_SIZE = 50 + 30 + 30 + sizeof(double) + 4;
	// Writes a record at file current position
	int writePrinter(printer& p) {
		char buffer[MAX_BUFFER_SIZE];
		strcpy(buffer, p.id); strcat(buffer, "|");
		strcpy(buffer, p.model); strcat(buffer, "|");
		strcpy(buffer, p.description); strcat(buffer, "|");
		strcpy(buffer, (char*)&p.price); strcat(buffer, "|");

		short length = strlen(buffer);
		data_file.write((char*)&length, sizeof(length));
		data_file.write(buffer, length);

		delete[] buffer;
		return length;
	}

	printer readPrinter() {
		printer p;
		short length;
		data_file.read((char*)&length, sizeof(length));

		char *buffer = new char[length];
		data_file.read(buffer, length);
		istringstream stream(buffer);
		stream.getline(p.id, 30, '|');
		stream.getline(p.model, 30, '|');
		stream.getline(p.description, 50, '|');
		stream.getline((char*)&p.price, sizeof(p.price), '|');
		delete[] buffer;
		return p;
	}

	void addPrinter(printer& p) {
		data_file.clear();
		data_file.seekp(0, ios::end);

		// Updating primary index
		PIndexRecord temp;
		strcpy(temp.PK, p.id);
		temp.offset = data_file.tellp();
		PIndex.push_back(temp);

		writePrinter(p);
	}

	void updatePrinter(char id[]) {
		int i = PIndexBinarySearch(id);
		if (i != -1) {
			// TODO: Get data from user and update
		}
		else cout << "Not found!" << endl;
	}

	void deletePrinter(char id[]) {
		int i = PIndexBinarySearch(id);
		if (i != -1) {
			data_file.seekp(PIndex[i].offset + 2);
			data_file.write("*", 1);

			// Point it to null
			// Don't erase it as the secondary key points here
			// it will point to next one instead
			PIndex[i].offset = -1;
		}
		else cout << "Not found!" << endl;
	}

	void compactFile() {
		// Read all non-deleted records from the file in a vector
		vector<printer> records;
		data_file.clear();
		data_file.seekg(0);
		short recordLength;
		printer curRecord;

		// file.eof() wasn't working
		// Instead, it tries to read a single char
		char c;
		while (data_file.get(c)) {
			// If it was read successfully, go back to where you where
			data_file.seekg(-1, ios::cur);

			data_file.read((char*)&recordLength, sizeof(recordLength));

			// Check that it's not deleted
			data_file.get(c);
			if (c == '*') {
				// Jump to the first char of the next record
				// -1 because we already read the '*'
				data_file.seekg(recordLength - 1, ios::cur);
			}
			else {
				// Read record and push it to the vector
				// -1 to go back the byte we just read
				data_file.seekg(-1, ios::cur);
				curRecord = readPrinter();
				records.push_back(curRecord);
			}
		}

		// Close then open the file in ios::out
		// mode only to clear it on opening
		data_file.close();
		data_file.open("data.txt", ios::out);

		// Write all records in the vector to the new file
		for (int i = 0; i < records.size(); i++)
			addPrinter(records[i]);

		// Return the file back to in | out mode
		data_file.close();
		data_file.open("data.txt", ios::in | ios::out);
	}

	void visualizeFile() {
		data_file.clear();
		data_file.seekg(0);
		short recordLength;

		char c;
		while (data_file.get(c)) {
			// If it was read successfully, go back to where you where
			data_file.seekg(-1, ios::cur);

			data_file.read((char*)&recordLength, sizeof(recordLength));

			// Check that it's not deleted
			data_file.get(c);
			if (c == '*') cout << "*";
			else cout << "-";

			// Jump to the first char of the next record
			// -1 because we already read the '*'
			data_file.seekg(recordLength - 1, ios::cur);
		}
	}

	void savePIndex() {
		fstream PIndex_file(PIndex_path, ios::out);
		for (int i = 0; i < PIndex.size(); i++)
			PIndex_file.write((char*)&PIndex[i], sizeof(PIndex[i]));
		PIndex_file.close();
	}

	bool exists(char path[20]) {
		ifstream f(path);
		if (f.good()) {
			f.close();
			return true;
		}
		else {
			f.close();
			return false;
		}
	}

	void loadPIndex() {
		if (!exists(PIndex_path)) {
			ofstream fout;
			fout.open(PIndex_path, ios::app | ios::out | ios::binary);
			fout << 0;
			fout.close();
			ReconstructIndex();
		}
		else {
			ifstream fin(PIndex_path);
			PIndex.clear();
			while (true)
			{
				PIndexRecord temp;
				fin.read((char*)&temp, sizeof(temp));
				if (fin.eof()) break;
				PIndex.push_back(temp);
			}
			fin.close();
		}
	}

	void ReconstructIndex() {
		data_file.clear();
		data_file.seekg(0);
		PIndex.clear();

		while (true)
		{
			PIndexRecord temp;
			int offset = data_file.tellg();

			short len;
			data_file.read((char*)&len, sizeof(len));
			if (data_file.eof()) break;

			char *buffer = new char[len];
			data_file.read(buffer, len);
			if (buffer[0] == '*') continue;

			istringstream strbuf(buffer);
			strbuf.getline(temp.PK, 6, '|');
			temp.offset = offset;
			PIndex.push_back(temp);
		}

		sort(PIndex.begin(), PIndex.end(), PIndexComp);
		savePIndex();
	}

	// Primary index compare function
	static bool PIndexComp(PIndexRecord& a, PIndexRecord& b) {
		return atoi(a.PK) < atoi(b.PK);
	}

	// Returns index of record in PIndex vector
	int PIndexBinarySearch(char key[]) {
		int low = 0, high = PIndex.size() - 1, middle;
		while (low <= high)
		{
			middle = (low + high) / 2;
			if (strcmp(PIndex[middle].PK, key) == 0)
				return middle;
			else if (atoi(PIndex[middle].PK) < atoi(key))
				low = middle + 1;
			else
				high = middle - 1;
		}
		return -1;
	}
};

int main() {

}
