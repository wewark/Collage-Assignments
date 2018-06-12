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

ostream& operator<<(ostream& out, printer& p) {
	out << "ID: " << p.id << endl;
	out << "Model: " << p.model << endl;
	out << "Description: " << p.description << endl;
	out << "Price: " << p.price << endl;
	return out;
}
istream& operator>>(istream& in, printer& p) {
	cout << "ID: "; in >> p.id;
	cout << "Model: "; in >> p.model;
	cout << "Description: "; in >> p.description;
	cout << "Price: "; in >> p.price;
	return in;
}

class Index
{
private:
	fstream data_file;
	const string data_path = "data.txt";

public:
	Index() {
		if (!exists(data_path)) {
			ofstream fout;
			fout.open(data_path, ios::app | ios::out | ios::binary);
			fout.close();
		}
		data_file.open(data_path, ios::in | ios::out);
		loadPI(), loadSIM(), loadSIP();
	}
	~Index() {
		data_file.close();
		savePI(), saveSIM(), saveSIP();
	}

	// Writes a record at file current position
	void writePrinter(printer& p) {
		short s = p.length();
		data_file.write((char*)&(s), sizeof(s));
		data_file << p.id << '|' << p.model << '|' << p.description << '|';
		data_file.write((char*)&p.price, sizeof(p.price));
		data_file << '|';
	}

	printer readPrinter() {
		printer p;
		short length;
		data_file.read((char*)&length, sizeof(length));
		data_file.getline(p.id, 30, '|');
		data_file.getline(p.model, 30, '|');
		data_file.getline(p.description, 50, '|');
		data_file.read((char*)&p.price, sizeof(p.price));
		data_file.seekg(1, ios::cur);
		return p;
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

	const string PIndex_path = "PI.txt";

	struct PIRecord
	{
		char PK[30]; // id
		int offset;
	};
	vector<PIRecord> PI;

	void loadPI() {
		if (!exists(PIndex_path)) {
			ofstream fout;
			fout.open(PIndex_path, ios::app | ios::out | ios::binary);
			fout.close();
			ReconstructPI();
		}
		else {
			ifstream fin(PIndex_path);
			PI.clear();
			while (fin.good())
			{
				char c;
				if (fin.get(c))fin.seekg(-1, ios::cur);
				else break;
				PIRecord temp;
				fin.read((char*)&temp, sizeof(temp));
				//cout << temp.PK << endl;
				PI.push_back(temp);
			}
			sort(PI.begin(), PI.end(), PIComp);
			fin.close();
		}

		// In case it exists but empty
		if (PI.empty())
			ReconstructPI();
	}

	void savePI() {
		fstream PIndex_file(PIndex_path, ios::out);
		PIndex_file.seekp(0);
		sort(PI.begin(), PI.end(), PIComp);
		for (int i = 0; i < PI.size(); i++)
			PIndex_file.write((char*)&PI[i], sizeof(PI[i]));
		PIndex_file.close();
	}

	void ReconstructPI() {
		data_file.clear();
		data_file.seekg(0);
		PI.clear();

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
			PI.push_back(temp);
		}

		sort(PI.begin(), PI.end(), PIComp);
		savePI();
	}

	// Adds the id of p to PI
	void addToPI(printer& p) {
		PIRecord temp;
		strcpy(temp.PK, p.id);
		temp.offset = data_file.tellp();
		PI.push_back(temp);
	}

	// Primary index compare function
	static bool PIComp(PIRecord& a, PIRecord& b) {
		return atoi(a.PK) < atoi(b.PK);
	}

	// Returns index of record in PI vector
	int PIBinarySearch(const char key[]) {
		int low = 0, high = PI.size() - 1, middle;
		while (low <= high)
		{
			middle = (low + high) / 2;
			if (strcmp(PI[middle].PK, key) == 0)
				return middle;
			else if (atoi(PI[middle].PK) < atoi(key))
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
			return;
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
		if (SIM.empty()) {
			ReconstructSIM();
			return;
		}
		// Do the same with SIMLabel
		if (!exists(SIMLabel_path)) {
			ofstream fout;
			fout.open(SIMLabel_path, ios::app | ios::out | ios::binary);
			fout.close();
			ReconstructSIM();
			return;
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
			if (p.id[0] != '*')
				addToSIM(p);
		}

		data_file.clear();
		sort(SIM.begin(), SIM.end(), SIMComp);
		saveSIM();
	}

	// Adds the model of p to SIM
	void addToSIM(printer& p) {
		bool found = false;
		for (int i = 0; i < SIM.size(); i++)
			if (strcmp(SIM[i].SK, p.model) == 0) {
				found = true;

				LabelRecord temp;
				strcpy(temp.PK, p.id);
				temp.next = SIM[i].labelIndex;
				SIM[i].labelIndex = SIMLabel.size();
				SIMLabel.push_back(temp);
				break;
			}

		if (!found) {
			SIMRecord simtemp;
			strcpy(simtemp.SK, p.model);
			simtemp.labelIndex = SIMLabel.size();

			LabelRecord labeltemp;
			strcpy(labeltemp.PK, p.id);
			labeltemp.next = -1;
			simtemp.labelIndex = SIMLabel.size();

			SIM.push_back(simtemp);
			SIMLabel.push_back(labeltemp);
		}
	}

	void removeFromSIM(printer& p) {
		for (int i = 0; i < SIM.size(); i++)
			if (strcmp(SIM[i].SK, p.model) == 0) {
				int cur = SIM[i].labelIndex, prv = -1;

				// Follow linked list until you find our printer
				while (strcmp(SIMLabel[cur].PK, p.id)) {
					prv = cur;
					cur = SIMLabel[cur].next;
				}

				// If it is the first one in the list
				if (prv == -1) {
					// If it was the ONLY one
					if (SIMLabel[cur].next == -1)
						SIM.erase(SIM.begin() + i);
					else
						SIM[i].labelIndex = SIMLabel[cur].next;
				}
				else
					SIMLabel[prv].next = SIMLabel[cur].next;
				break;
			}
	}

	// SIM compare function
	static bool SIMComp(SIMRecord& a, SIMRecord& b) {
		return strcmp(a.SK, b.SK) < 0;
	}

	// Returns index of a record in SIM
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
	vector<string> searchSIM(char key[]) {
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
			return;
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
		if (SIP.empty()) {
			ReconstructSIP();
			return;
		}
		// Do the same with SIPLabel
		if (!exists(SIPLabel_path)) {
			ofstream fout;
			fout.open(SIPLabel_path, ios::app | ios::out | ios::binary);
			fout.close();
			ReconstructSIP();
			return;
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
			if (p.id[0] != '*')
				addToSIP(p);
		}

		data_file.clear();
		sort(SIP.begin(), SIP.end(), SIPComp);
		saveSIP();
	}

	// Adds the price of p to SIP
	void addToSIP(printer& p) {
		bool found = false;
		for (int i = 0; i < SIP.size(); i++)
			if (SIP[i].SK == p.price) {
				found = true;

				LabelRecord temp;
				strcpy(temp.PK, p.id);
				temp.next = SIP[i].labelIndex;
				SIP[i].labelIndex = SIPLabel.size();
				SIPLabel.push_back(temp);
				break;
			}

		if (!found) {
			SIPRecord SIPtemp;
			SIPtemp.SK = p.price;
			SIPtemp.labelIndex = SIPLabel.size();

			LabelRecord labeltemp;
			strcpy(labeltemp.PK, p.id);
			labeltemp.next = -1;
			SIPtemp.labelIndex = SIPLabel.size();

			SIP.push_back(SIPtemp);
			SIPLabel.push_back(labeltemp);
		}
	}

	void removeFromSIP(printer& p) {
		for (int i = 0; i < SIP.size(); i++)
			if (SIP[i].SK == p.price) {
				int cur = SIP[i].labelIndex, prv = -1;

				// Follow linked list until you find our printer
				while (strcmp(SIPLabel[cur].PK, p.id)) {
					prv = cur;
					cur = SIPLabel[cur].next;
				}

				// If it is the first one in the list
				if (prv == -1) {
					// If it was the ONLY one
					if (SIPLabel[cur].next == -1)
						SIP.erase(SIP.begin() + i);
					else
						SIP[i].labelIndex = SIPLabel[cur].next;
				}
				else
					SIPLabel[prv].next = SIPLabel[cur].next;
				break;
			}
	}

	// SIP compare function
	static bool SIPComp(SIPRecord& a, SIPRecord& b) {
		return a.SK < b.SK;
	}

	// Returns index of a record in SIP
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
	vector<string> searchSIP(double key) {
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

	// *************** User Functions *************** //

	void addPrinter(printer& p) {
		data_file.clear();
		data_file.seekp(0, ios::end);

		// Update indexes
		addToPI(p), addToSIM(p), addToSIP(p);
		sort(PI.begin(), PI.end(), PIComp);
		sort(SIM.begin(), SIM.end(), SIMComp);
		sort(SIP.begin(), SIP.end(), SIPComp);

		writePrinter(p);
	}

	void updatePrinter(char id[]) {
		int i = PIBinarySearch(id);
		if (i == -1) {
			cout << "Not found!" << endl;
			return;
		}

		printer p, p_old; cin >> p;

		data_file.clear();
		data_file.seekg(PI[i].offset);
		p_old = readPrinter();

		if (p_old.length() == p.length()) {
			data_file.seekp(PI[i].offset);
			writePrinter(p);

			strcpy(PI[i].PK, p.id);

			removeFromSIM(p_old);
			removeFromSIP(p_old);
			addToSIM(p), addToSIP(p);

			sort(PI.begin(), PI.end(), PIComp);
			sort(SIM.begin(), SIM.end(), SIMComp);
			sort(SIP.begin(), SIP.end(), SIPComp);
		}
		else {
			deletePrinter(id);
			addPrinter(p);
		}
	}

	void deletePrinter(char id[]) {
		int i = PIBinarySearch(id);
		if (i == -1) {
			cout << "Not found!" << endl;
			return;
		}

		// Get the printer itself
		data_file.clear();
		data_file.seekg(PI[i].offset);
		printer p = readPrinter();

		data_file.clear();
		data_file.seekp(PI[i].offset + 2);
		data_file << "*";

		PI.erase(PI.begin() + i);
		removeFromSIM(p), removeFromSIP(p);
	}

	void searchByID() {
		char id[30];
		cout << "ID: "; cin >> id;
		int i = PIBinarySearch(id);
		if (i == -1) {
			cout << "Not found!" << endl;
			return;
		}

		data_file.clear();
		data_file.seekg(PI[i].offset);
		printer p = readPrinter();

		cout << p << endl;
	}

	void searchByModel() {
		char model[30];
		cout << "Model: "; cin >> model;

		vector<string> PKs = searchSIM(model);
		vector<int> offsets;
		for (auto i : PKs)
			offsets.push_back(PI[PIBinarySearch(i.c_str())].offset);

		// To reduce seeking
		sort(offsets.begin(), offsets.end());

		data_file.clear();
		cout << endl << offsets.size() << " printers found" << endl << endl;
		for (auto i : offsets) {
			data_file.seekg(i);
			printer p=readPrinter();
			cout << p << endl;
		}
	}

	void searchByModelAndPrice() {
		char model[30]; double price;
		cout << "Model: "; cin >> model;
		cout << "Price: "; cin >> price;

		vector<string> modelPKs = searchSIM(model);
		vector<string> pricePKs = searchSIP(price);

		// To binary search in it
		sort(pricePKs.begin(), pricePKs.end());
		vector<int> offsets;
		for (auto i : modelPKs)
			// If it is in the other one too
			if (binary_search(pricePKs.begin(), pricePKs.end(), i))
				offsets.push_back(PI[PIBinarySearch(i.c_str())].offset);

		// To reduce seeking
		sort(offsets.begin(), offsets.end());

		data_file.clear();
		cout << endl << offsets.size() << " printers found" << endl << endl;
		for (auto i : offsets) {
			data_file.seekg(i);
			printer p=readPrinter();
			cout << p << endl;
		}
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

		// Write all records in the vector to the new file
		for (int i = 0; i < records.size(); i++)
			addPrinter(records[i]);

		// Return the file back to in | out mode
		data_file.close();
		data_file.open(data_path, ios::in | ios::out);

		ReconstructPI(), ReconstructSIM(), ReconstructSIP();
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
} ind1;

int main() {
	while (true) {
		cout << "1) Add New printer" << endl;
		cout << "2) Update printer" << endl;
		cout << "3) Delete printer" << endl;
		cout << "4) Search using ID" << endl;
		cout << "5) Search using model" << endl;
		cout << "6) Search using certain model and certain price" << endl;
		cout << "7) Compact File" << endl;
		cout << "8) Visualize File" << endl;
		cout << "9) Exit" << endl << endl;
		cout << "Please Enter Your Choice:" << endl;
		int res; cin >> res;

		char id[30];
		switch (res)
		{
		case 1:
			printer p; cin >> p;
			ind1.addPrinter(p);
			break;
		case 2:
			cout << "ID: "; cin >> id;
			ind1.updatePrinter(id);
			break;
		case 3:
			cout << "ID: "; cin >> id;
			ind1.deletePrinter(id);
			break;
		case 4:
			ind1.searchByID();
			break;
		case 5:
			ind1.searchByModel();
			break;
		case 6:
			ind1.searchByModelAndPrice();
			break;
		case 7:
			ind1.compactFile();
			break;
		case 8:
			ind1.visualizeFile();
			break;
		case 9:
			return 0;
			break;
		default:
			cout << "Wrong choice" << endl;
			break;
		}
		system("PAUSE"), system("CLS");
	}
}
