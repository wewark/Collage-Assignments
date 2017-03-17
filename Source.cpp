#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstring>
#include <vector>
#include <stdlib.h>
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
	file.clear();
	file.seekp(0);
	file.write((char*)&availList, sizeof(availList));
}

// Sets availList to the value written in the file
void getAvailList(fstream &file) {
	file.clear();
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
	file.clear();
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
	else {
		file.clear();
		return -1;
	}
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
	// Skip the last '#'
	file.seekg(1, ios::cur);
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
		file.clear();
		file.seekp(startByte);
		// The star to show that it's deleted and will be ignored when searching
		file << '*';

		// To make availList point at the length, not the first char of the id
		addToAvailList(startByte - 1, file);
		cout << "Record with ID " << id << " deleted" << endl;

		// The availList has been changed, so write it the file
		setAvailList(file);
	}
	else
		cout << "Record not found!" << endl;

}

void updateRecord(char* id, fstream&file) {
	int startByte = search(id, file);
	// check if the record is not exist
	if (startByte == -1) {
		cout << "Cannot update un-existed record " << endl;
		return;
	}
	//entering the data of the new device
	device d1;
	cout << "Enter the new data of the record " << endl;
	cout << "ID: "; cin >> d1.id;
	cout << "Name: "; cin >> d1.name;
	cout << "Brand: "; cin >> d1.brand;
	cout << "Price: "; cin >> d1.price;


	int length;
	file.seekp(startByte);
	file >> length;  // get the length of the record that ought to be updated
	 // check if the length of the updated record can be fitted in the old one
	if (length >= d1.length()) {   //if yes
		writeRecord(d1, startByte, file);   //write the record in that place
		file.seekp(startByte + d1.length());
		for (int i = 0; i < length - d1.length(); i++)  //filling the rest by hashes
			file << '#';
	}
	else {   //if it can't fit in that length
		deleteRecord(id, file);  //delete the old record
		addRecord(d1, file);    //add it somewhere it can fit
	}
}

void compactFile(fstream &file) {
	// Read all non-deleted records from the file in a vector
	vector<device> records;
	file.clear();
	file.seekg(FIRST_BYTE_IN_FILE);
	char recordLength;
	device curRecord;

	// file.eof() wasn't working
	// Instead, it tries to read a single char
	char c;
	while (file.get(c)) {
		// If it was read successfully, go back to where you where
		file.seekg(-1, ios::cur);

		file.get(recordLength);

		// Check that it's not deleted
		file.get(c);
		if (c == '*') {
			// Jump to the first char of the next record
			// -2 because we already read the '*'
			file.seekg(recordLength - 1, ios::cur);
			continue;
		}

		// Read record and push it to the vector
		// -1 to go back the byte we just read
		curRecord = readRecord((int)file.tellg() - 1, file);
		records.push_back(curRecord);

		// Skip all the '#'s after the record
		while (file.get(c) && c == '#');
		file.seekg(-1, ios::cur);
	}

	// Close then open the file in ios::out
	// mode only to clear it on opening
	file.close();
	file.open("data.txt", ios::out);

	// Clear availList and write it to the new file
	availList = -1;
	setAvailList(file);

	// Write all records in the vector to the new file
	for (int i = 0; i < records.size(); i++)
		addRecord(records[i], file);

	// Return the file back to in | out mode
	file.close();
	file.open("data.txt", ios::in | ios::out);
}

int main() {
	fstream file("data.txt", ios::in | ios::out);
	//setAvailList(file);    //set the avilList by -1
	getAvailList(file);    //get the avilList value
	cout << "                Welcome to store management system" << endl << endl;
	while (true) {

		cout << "1) Add new device" << endl;
		cout << "2) Update device" << endl;
		cout << "3) Delete device" << endl;
		cout << "4) Search for a device by ID" << endl;
		cout << "5) Compact file" << endl;
		cout << "6) Exit" << endl;
		cout << "Enter your choice : ";
		int choice;
		cin >> choice;
		if (choice == 1) {
			device d1;
			system("CLS");
			//Entering the data of the new device
			cout << "ID: "; cin >> d1.id;
			cout << "Name: "; cin >> d1.name;
			cout << "Brand: "; cin >> d1.brand;
			cout << "Price: "; cin >> d1.price;
			addRecord(d1, file);
			cout << "Press any key to continue " << endl;
			char c;
			cin.ignore();
			cin.get(c);  // to get all characters including '\n'
			system("CLS");
		}
		else if (choice == 2) {
			system("CLS");
			char id[30];
			cout << "Enter the ID of the record you want to update : ";
			cin >> id;
			updateRecord(id, file);
			cout << "Press any key to continue " << endl;
			char c;
			cin.ignore();
			cin.get(c);
			system("ClS");
		}
		else if (choice == 3) {
			system("CLS");
			char id[30];
			cout << "Enter the ID of the record you want to delete : ";
			cin >> id;
			deleteRecord(id, file);
			cout << "Press any key to continue " << endl;
			char c;
			cin.ignore();
			cin.get(c);
			system("CLS");
		}
		else if (choice == 4) {
			system("CLS");
			char id[30];
			cout << "Enter the ID of the record you want to Search : ";
			cin >> id;
			printRecord(id, file);
			cout << "Press any key to continue " << endl;
			char c;
			cin.ignore();
			cin.get(c);
			system("ClS");
		}
		else if (choice == 5) {
			compactFile(file);
			///..........just visual effects.......///
			string x = "Compacting";
			for (int k = 0; k < 8; k++) {
				for (int i = 0; i < 5; i++) {
					cout << x;
					for (int j = 0; j < i; j++)
						cout << ".";
					system("CLS");
				}
			}
			cout << "Compacting file done " << endl;
			cout << "Press any key to continue " << endl;
			char c;
			cin.ignore();
			cin.get(c);
			system("CLS");
			///....................................///
		}
		else if (choice == 6) {
			cout << endl;
			cout << "EXIT" << endl;
			break;
		}
		else {
			cout << "un-supported choice please choose from the list " << endl;
			cout << "Press any key to continue " << endl;
			char c;
			cin.ignore();
			cin.get(c);
			system("CLS");
		}

	}

	cin.ignore(), cin.get();
}
