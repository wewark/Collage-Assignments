#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

class Index
{
private:
	fstream data_file;
	fstream primary_file;
	fstream secondary_file;
	char data_file_path[20] = "data.txt";
	char primary_file_path[20] = "primary.txt";
	char secondary_file_path[20] = "secondary.txt";

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
		char PK[30];
		int offset;
	};
	static const int INDEX_SIZE = 100;
	PIndexRecord primary_index[INDEX_SIZE];

public:
	Index() {
		data_file.open(data_file_path, ios::in | ios::out);
	}
	~Index() {}

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
		writePrinter(p);
	}

	void updatePrinter() {
		// TODO
	}

	void deletePrinter() {
		// TODO
		//int offset = search()
		//file.seekp(offset + 2);
		//file.write("*", 1);
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
};

int main() {

}
