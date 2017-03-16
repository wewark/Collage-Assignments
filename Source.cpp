#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstring>
using namespace std;

struct device
{
	char id[20];
	char name[30];
	char brand[30];
	double price;
	char length() {
		return strlen(id) + strlen(name) + strlen(brand) + sizeof(price) + 4;
	}
};

// The start byte of the first item in the list
int availList = -1;
// The first byte to be used in the file will be
// the 5th byte as the first 4 bytes are for the availList
const int FIRST_BYTE_IN_FILE = 4;

// Writes availList in the first 4 byte of the file
void setAvailList(fstream &file) {
	file.seekp(0);
	file.write((char*)&availList, sizeof(availList));
}

// Sets availList to the value written in the file
void getAvailList(fstream &file) {
	file.seekg(0);
	file.read((char*)&availList, sizeof(availList));
}

void addToAvailList(int startByte, fstream &file) {
	file.seekp(startByte + 2);
	// OK I will point at what availList points at
	file.write((char*)&(availList), sizeof(availList));

	// Now availList points at me
	availList = startByte;
}

void removeFromAvailList(int cur, int prev, int next, fstream &file) {
	// If first element in the list
	if (prev == -1)
		availList = next;

	else {
		// Go to prev start byte
		// Skip 1 byte for its length and 1 for the '*'
		file.seekp(prev + 2);
		// Make your prev point to your next
		file << next;
	}
}

// Writes record starting at a certain byte
void writeRecord(device rec, int startByte, fstream &file) {
	// If startByte is -1 add record at the end
	if (startByte == -1)
		file.seekp(0, ios::end);
	else
		file.seekp(startByte);

	file << rec.length();
	file << rec.id << '#';
	file << rec.name << '#';
	file << rec.brand << '#';
	file.write((char*)&rec.price, sizeof(rec.price));
	file << '#';
}

void addRecord(device rec, fstream &file) {
	// If the availList is empty add record at the end of the file
	if (availList == -1) {
		writeRecord(rec, -1, file);
		return;
	}

	// Start byte of the prev, cur and next elements in availList
	int prev = -1, cur = availList, next = -1;
	char length;
	while (true) {
		file.seekg(cur);
		file >> length;
		file.seekg(1, ios::cur);
		file.read((char*)&next, sizeof(next));

		if (length >= rec.length()) {
			// Remove the element from availList
			removeFromAvailList(cur, prev, next, file);

			// Write the record in that place
			writeRecord(rec, cur, file);

			// Go to first char of the extra space
			file.seekp(cur + rec.length());

			// fill the rest with '#'
			for (int i = 0; i < length - rec.length(); i++)
				file << '#';
			break;
		}
		// If end of list reached, add record at the end of the file
		else if (next == -1) {
			writeRecord(rec, -1, file);
			break;
		}
		// Else, Go to next element
		else
			prev = cur, cur = next;
	}
}

int search(char* id, fstream &file) {
	file.clear();
	file.seekg(FIRST_BYTE_IN_FILE);
	char recordLength, curId[20];
	bool recordFound = false;

	// file.eof() wasn't working
	// Instead, it tries to read a single char
	while (file.get(curId[0])) {
		// If it was read successfully, go back to where you where
		file.seekg(-1, ios::cur);

		file >> recordLength;

		// Check that it's not deleted
		char c;
		file.get(c);
		if (c != '*') {
			// Go back the 1 char you just read
			file.seekg(-1, ios::cur);

			// Read id from file
			file.getline(curId, 20, '#');

			// If ids match
			if (strcmp(curId, id) == 0) {
				recordFound = true;
				break;
			}

			// Jump to the first char of the next record
			file.seekg(recordLength - strlen(curId) - 1, ios::cur);
		}
		else {
			// Jump to the first char of the next record
			file.seekg(recordLength - 1, ios::cur);
		}
	}

	if (recordFound)
		// Return the offset of the starting byte
		// But before the curId and the '#'
		return (int)file.tellg() - strlen(curId) - 1;

	// Record not found
	else
		return -1;
}

device readRecord(int startByte, fstream &file) {
	// If deleted
	if (startByte == -1) {
		return device{ "*", "", "", 0 };
	}

	file.seekg(startByte);
	device rec;
	file.getline(rec.id, 20, '#');
	file.getline(rec.name, 30, '#');
	file.getline(rec.brand, 30, '#');
	file.read((char*)&rec.price, sizeof(rec.price));
	return rec;
}

void printRecord(int startByte, fstream &file) {
	device rec = readRecord(startByte, file);
	cout << "Record found" << endl;
	cout << "ID: " << rec.id << endl;
	cout << "Name: " << rec.name << endl;
	cout << "Brand: " << rec.brand << endl;
	cout << "Price: " << rec.price << endl;
}

void printRecord(char* id, fstream &file) {
	device rec = readRecord(search(id, file), file);
	// If not found
	if (strcmp(rec.id, "*") == 0)
		cout << "Record not found!" << endl;
	else {
		cout << "Record found" << endl;
		cout << "ID: " << rec.id << endl;
		cout << "Name: " << rec.name << endl;
		cout << "Brand: " << rec.brand << endl;
		cout << "Price: " << rec.price << endl;
	}
}

// Deleted records are like that:
// [length(1 byte)]['*'(1 byte)][next element in the list(4 bytes)]
void deleteRecord(char* id, fstream &file) {
	int startByte = search(id, file);

	// If record was found
	if (startByte != -1) {
		file.seekp(startByte);
		// The star to show that it's deleted and will be ignored when searching
		file << '*';

		// To make availList point at the length, not the first char of the id
		addToAvailList(startByte - 1, file);
	}
}

void updateRecord(char* id, fstream&file) {
	device d1;
	cout << "ID: "; cin >> d1.id;
	cout << "Name: "; cin >> d1.name;
	cout << "Brand: "; cin >> d1.brand;
	cout << "Price: "; cin >> d1.price;

	int startByte = search(id, file);
	int length;
	file.seekp(startByte);
	file >> length;
	if (length >= d1.length()) {
		writeRecord(d1, startByte, file);
		file.seekp(startByte + d1.length());
		for (int i = 0; i < length - d1.length(); i++)
			file << '#';
	}
	else {
		deleteRecord(id, file);
		addRecord(d1, file);
	}
}

void compactFile() {
	// TODO
}

int main() {
	fstream file("data.txt", ios::in | ios::out);
	//setAvailList(file);
	device dev[] = {
		{ "12", "cable", "acer", 15.5 },
		{ "28", "laptop", "dell", 15000 },
		{ "19", "cellphone", "samsung", 15000 }
	};
	//for (int i = 0; i < 3; i++)
	//addRecord(dev[i], file);
	getAvailList(file);
	printRecord("20", file);
	printRecord("28", file);
	//deleteRecord("28", file);
	//printRecord("28", file);
	addRecord(device{ "20", "lap", "del", 15 }, file);
	setAvailList(file);
	//cin.ignore(), cin.get();
}