#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

struct printer
{
	char id[30];
	char model[30];
	char description[50];
	double price;
	short length() {
		return strlen(id) + strlen(model) + strlen(description) + sizeof(price) + 4;
	}
};

//fstream data_file("data.txt", ios::in | ios::out);
//fstream PIndex_file;
class Index
{
private:
	fstream data_file;
	const string data_path = "data.txt";

public:
	Index() {
		data_file.open(data_path, ios::in | ios::out);
	}
	~Index() {
		data_file.close();
	}

	// Writes a record at file current position
	short writePrinter(printer& p) {
		short s = p.length();
		data_file.write((char*)&(s), sizeof(s));
		data_file << p.id << '|' << p.model << '|' << p.description << '|';
		data_file.write((char*)&p.price, sizeof(p.price));
		data_file << '|';
		return s;
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
		PIRecord temp;
		strcpy(temp.PK, p.id);
		temp.offset = data_file.tellp();
		PIndex.push_back(temp);

		writePrinter(p);
		sort(PIndex.begin(), PIndex.end(), PIComp);
	}

	void updatePrinter(char id[]) {
		int i = PIBinarySearch(id);
		if (i != -1) {
			printer p;
			cout << "ID :"; cin >> p.id;
			cout << "Model :"; cin >> p.model;
			cout << "Description :"; cin >> p.description;
			cout << "Price :"; cin >> p.price;
			short length;
			data_file.seekg(PIndex[i].offset);
			data_file.read((char*)&length, sizeof(length));
			cout << "length " << length << endl;
			if (length >= p.length())
			{
				cout << "fff";
				data_file.seekp(PIndex[i].offset + sizeof(length));
				data_file << p.id << '|' << p.model << '|' << p.description << '|';
				data_file.write((char*)&p.price, sizeof(p.price));
				data_file << '|';
				strcpy(PIndex[i].PK, p.id);
				sort(PIndex.begin(), PIndex.end(), PIComp);
			}
			else
			{
				data_file.seekp(PIndex[i].offset + sizeof(length));
				data_file << '*';
				PIndex.erase(PIndex.begin() + i);
				addPrinter(p);
				//deal with the indexes stuff
			}



		}
		else cout << "Not found!" << endl;
	}

	void deletePrinter(char id[]) {
		int i = PIBinarySearch(id);
		if (i != -1) {
			data_file.clear();
			data_file.seekp(PIndex[i].offset + 2);
			data_file << "*";
			//char c; data_file.seekg(PIndex[i].offset + 2); data_file.get(c);
			PIndex.erase(PIndex.begin() + i);
			// Point it to null
			// Don't erase it as the secondary key points here
			// it will point to next one instead
			//PIndex[i].offset = -1;  // WHY THIS WHEN I CAN SIMPLY ERASE IT
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
				// go to the beginning (readPrinter() reads length)
				data_file.seekg(-3, ios::cur);
				curRecord = readPrinter();
				records.push_back(curRecord);
			}
		}

		// Close then open the file in ios::out
		// mode only to clear it on opening
		data_file.close();
		data_file.open(data_path, ios::out);

		PIndex.clear();
		// Write all records in the vector to the new file
		for (int i = 0; i < records.size(); i++)
			addPrinter(records[i]);

		// Return the file back to in | out mode
		data_file.close();
		data_file.open(data_path, ios::in | ios::out);
	}

	void visualizeFile() {
		data_file.clear();
			data_file.seekg(0);
		char c;
		while (data_file.good())
		{
			short len;
			data_file.read((char*)&len, sizeof(len));
			if (data_file.get(c))
			{
				if (c == '*') cout << "*";
				else cout << "-";
				data_file.seekg(len - 1, ios::cur);
			}
			else {
				data_file.clear();
				break;
			}
		}
		cout << endl;
	}

	bool exists(string path) {
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

	// ********************** Primary Index (PI) ********************** //

	const string PIndex_path = "primary.txt";

	struct PIRecord
	{
		char PK[30]; // id
		int offset;
	};
	vector<PIRecord> PIndex;

	void loadPI() {
		if (!exists(PIndex_path)) {
			ofstream fout;
			fout.open(PIndex_path, ios::app | ios::out | ios::binary);
			fout.close();
			ReconstructPI();
		}
		else {
			ifstream fin(PIndex_path);
			PIndex.clear();
			while (fin.good())
			{
				char c;
				if (fin.get(c))fin.seekg(-1, ios::cur);
				else break;
				PIRecord temp;
				fin.read((char*)&temp, sizeof(temp));
				//cout << temp.PK << endl;
				PIndex.push_back(temp);
			}
			sort(PIndex.begin(), PIndex.end(), PIComp);
			fin.close();
		}

		// In case it exists but empty
		if (PIndex.empty())
			ReconstructPI();
	}

	void savePI() {
		fstream PIndex_file(PIndex_path, ios::out);
		PIndex_file.seekp(0);
		sort(PIndex.begin(), PIndex.end(), PIComp);
		for (int i = 0; i < PIndex.size(); i++)
			PIndex_file.write((char*)&PIndex[i], sizeof(PIndex[i]));
		PIndex_file.close();
	}

	void ReconstructPI() {
		data_file.clear();
		data_file.seekg(0);
		PIndex.clear();

		while (true)
		{
			PIRecord temp;
			int offset = data_file.tellg();

			short len;
			data_file.read((char*)&len, sizeof(len));
			if (data_file.eof()) break;

			char *buffer = new char[len];
			data_file.read(buffer, len);
			if (buffer[0] == '*') continue;

			istringstream strbuf(buffer);
			strbuf.getline(temp.PK, 30, '|');   ///copy paste eh ... allah yanwar
			temp.offset = offset;
			PIndex.push_back(temp);
		}

		sort(PIndex.begin(), PIndex.end(), PIComp);
		savePI();
	}

	// Primary index compare function
	static bool PIComp(PIRecord& a, PIRecord& b) {
		return atoi(a.PK) < atoi(b.PK);
	}

	// Returns index of record in PIndex vector
	int PIBinarySearch(char key[]) {
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

	// *************** Secondary Index using Model (SIM) *************** //

	const string SIM_path = "SIM.txt";
	const string SIMLabel_path = "SIMLabel.txt";

	struct SIMRecord
	{
		char SK[30]; // model
		int labelIndex; // its index in Label ID list
	};
	struct LabelRecord
	{
		char PK[30]; // id
		int next;
	};
	vector<SIMRecord> SIM;
	vector<LabelRecord> SIMLabel;

	void loadSIM() {
		if (!exists(SIM_path)) {
			ofstream fout;
			fout.open(SIM_path, ios::app | ios::out | ios::binary);
			fout.close();
			ReconstructSIM();
		}
		else {
			ifstream fin(SIM_path);
			SIM.clear();
			while (fin.good())
			{
				if (fin.get()) fin.seekg(-1, ios::cur);
				else break;
				
				SIMRecord temp;
				fin.read((char*)&temp, sizeof(temp));
				SIM.push_back(temp);
			}
			sort(SIM.begin(), SIM.end(), SIMComp);
			fin.close();
		}

		// In case it exists but empty
		if (SIM.empty())
			ReconstructSIM();

		// Do the same with SIMLabel
		if (!exists(SIMLabel_path)) {
			ofstream fout;
			fout.open(SIMLabel_path, ios::app | ios::out | ios::binary);
			fout.close();
			ReconstructSIM();
		}
		else {
			ifstream fin(SIMLabel_path);
			SIMLabel.clear();
			while (fin.good())
			{
				if (fin.get()) fin.seekg(-1, ios::cur);
				else break;

				LabelRecord temp;
				fin.read((char*)&temp, sizeof(temp));
				SIMLabel.push_back(temp);
			}
			fin.close();
		}

		// In case it exists but empty
		if (SIMLabel.empty())
			ReconstructSIM();
	}

	void saveSIM() {
		ofstream fout(SIM_path);
		fout.seekp(0);
		sort(SIM.begin(), SIM.end(), SIMComp);
		for (int i = 0; i < SIM.size(); i++)
			fout.write((char*)&SIM[i], sizeof(SIM[i]));
		fout.close();

		fout.open(SIMLabel_path);
		fout.seekp(0);
		for (int i = 0; i < SIMLabel.size(); i++)
			fout.write((char*)&SIMLabel[i], sizeof(SIMLabel[i]));
		fout.close();
	}

	void ReconstructSIM() {
		data_file.clear();
		data_file.seekg(0);
		SIM.clear();
		SIMLabel.clear();

		while (true)
		{
			data_file.get();
			if (data_file.eof()) break;
			data_file.seekg(-1, ios::cur);

			printer p = readPrinter();
			bool found = false;
			for (int i = 0; i < SIM.size(); i++)
				if (SIM[i].SK == p.model) {
					found = true;

					LabelRecord temp;
					strcpy(temp.PK, p.id);
					temp.next = SIM[i].labelIndex;
					SIM[i].labelIndex = SIMLabel.size();
					SIMLabel.push_back(temp);
				}

			if (!found) {
				SIMRecord simtemp;
				strcpy(simtemp.SK, p.model);
				simtemp.labelIndex = SIMLabel.size();

				LabelRecord labeltemp;
				strcpy(labeltemp.PK, p.id);
				labeltemp.next = simtemp.labelIndex;
				simtemp.labelIndex = SIMLabel.size();

				SIM.push_back(simtemp);
				SIMLabel.push_back(labeltemp);
			}
		}

		data_file.clear();
		sort(SIM.begin(), SIM.end(), SIMComp);
		saveSIM();
	}

	// SIM compare function
	static bool SIMComp(SIMRecord& a, SIMRecord& b) {
		return strcmp(a.SK, b.SK) < 0;
	}

	// Returns index of a record in SIMLabel
	int SIMBinarySearch(char key[]) {
		int low = 0, high = SIM.size() - 1, middle;
		while (low <= high)
		{
			middle = (low + high) / 2;
			if (strcmp(SIM[middle].SK, key) == 0)
				return middle;
			else if (strcmp(SIM[middle].SK, key) < 0)
				low = middle + 1;
			else
				high = middle - 1;
		}
		return -1;
	}

	// Returns vector of PKs of found printers
	vector<string> searchByModel(char key[]) {
		int i = SIMBinarySearch(key);
		if (i != -1)
			i = SIM[i].labelIndex;

		vector<string> found;
		while (i != -1) {
			found.push_back(SIMLabel[i].PK);
			i = SIMLabel[i].next;
		}
		return found;
	}

	// *************** Secondary Index using Price (SIP) *************** //

	const string SIP_path = "SIP.txt";
	const string SIPLabel_path = "SIPLabel.txt";

	struct SIPRecord
	{
		double SK; // price
		int labelIndex; // its index in Label ID list
	};
	vector<SIPRecord> SIP;
	vector<LabelRecord> SIPLabel;

	void loadSIP() {
		if (!exists(SIP_path)) {
			ofstream fout;
			fout.open(SIP_path, ios::app | ios::out | ios::binary);
			fout.close();
			ReconstructSIP();
		}
		else {
			ifstream fin(SIP_path);
			SIP.clear();
			while (fin.good())
			{
				if (fin.get()) fin.seekg(-1, ios::cur);
				else break;

				SIPRecord temp;
				fin.read((char*)&temp, sizeof(temp));
				SIP.push_back(temp);
			}
			sort(SIP.begin(), SIP.end(), SIPComp);
			fin.close();
		}

		// In case it exists but empty
		if (SIP.empty())
			ReconstructSIP();

		// Do the same with SIPLabel
		if (!exists(SIPLabel_path)) {
			ofstream fout;
			fout.open(SIPLabel_path, ios::app | ios::out | ios::binary);
			fout.close();
			ReconstructSIP();
		}
		else {
			ifstream fin(SIPLabel_path);
			SIPLabel.clear();
			while (fin.good())
			{
				if (fin.get()) fin.seekg(-1, ios::cur);
				else break;

				LabelRecord temp;
				fin.read((char*)&temp, sizeof(temp));
				SIPLabel.push_back(temp);
			}
			fin.close();
		}

		// In case it exists but empty
		if (SIPLabel.empty())
			ReconstructSIP();
	}

	void saveSIP() {
		ofstream fout(SIP_path);
		fout.seekp(0);
		sort(SIP.begin(), SIP.end(), SIPComp);
		for (int i = 0; i < SIP.size(); i++)
			fout.write((char*)&SIP[i], sizeof(SIP[i]));
		fout.close();

		fout.open(SIPLabel_path);
		fout.seekp(0);
		for (int i = 0; i < SIPLabel.size(); i++)
			fout.write((char*)&SIPLabel[i], sizeof(SIPLabel[i]));
		fout.close();
	}

	void ReconstructSIP() {
		data_file.clear();
		data_file.seekg(0);
		SIP.clear();
		SIPLabel.clear();

		while (true)
		{
			data_file.get();
			if (data_file.eof()) break;
			data_file.seekg(-1, ios::cur);

			printer p = readPrinter();
			bool found = false;
			for (int i = 0; i < SIP.size(); i++)
				if (SIP[i].SK == p.price) {
					found = true;

					LabelRecord temp;
					strcpy(temp.PK, p.id);
					temp.next = SIP[i].labelIndex;
					SIP[i].labelIndex = SIPLabel.size();
					SIPLabel.push_back(temp);
				}

			if (!found) {
				SIPRecord SIPtemp;
				SIPtemp.SK = p.price;
				SIPtemp.labelIndex = SIPLabel.size();

				LabelRecord labeltemp;
				strcpy(labeltemp.PK, p.id);
				labeltemp.next = SIPtemp.labelIndex;
				SIPtemp.labelIndex = SIPLabel.size();

				SIP.push_back(SIPtemp);
				SIPLabel.push_back(labeltemp);
			}
		}

		data_file.clear();
		sort(SIP.begin(), SIP.end(), SIPComp);
		saveSIP();
	}

	// SIP compare function
	static bool SIPComp(SIPRecord& a, SIPRecord& b) {
		return a.SK < b.SK;
	}

	// Returns index of a record in SIPLabel
	int SIPBinarySearch(double key) {
		int low = 0, high = SIP.size() - 1, middle;
		while (low <= high)
		{
			middle = (low + high) / 2;
			if (SIP[middle].SK == key)
				return middle;
			else if (SIP[middle].SK < key)
				low = middle + 1;
			else
				high = middle - 1;
		}
		return -1;
	}

	// Returns vector of PKs of found printers
	vector<string> searchByPrice(double key) {
		int i = SIPBinarySearch(key);
		if (i != -1)
			i = SIP[i].labelIndex;

		vector<string> found;
		while (i != -1) {
			found.push_back(SIPLabel[i].PK);
			i = SIPLabel[i].next;
		}
		return found;
	}
};

int main() {
	Index ind1;
	printer p[] = {
		printer{"123","123","123",123},
		printer{"999","ahh","tmm",500},
		printer{"670","kmn","mra",800}
	};
	ind1.loadPI();
	ind1.loadSIM();
	ind1.loadSIP();

	//ind1.addPrinter(p[0]);
	//ind1.addPrinter(p[1]);
	//ind1.deletePrinter(p[1].id);
	//ind1.addPrinter(p[2]);
	//ind1.deletePrinter(p[2].id);
	//ind1.addPrinter(p[2]);

	ind1.visualizeFile();
	cout << "compacting..." << endl;
	ind1.compactFile();
	ind1.visualizeFile();
	//ind1.deletePrinter("60");
	//ind1.updatePrinter("70");
	//ind1.compactFile();

	ind1.savePI();
	ind1.saveSIM();
	ind1.saveSIP();
	cin.get();
}
