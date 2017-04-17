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

fstream data_file("data.txt",ios::in|ios::out);
fstream PIndex_file("primary.txt",ios::in|ios::out);
class Index
{
private:
//	fstream data_file;
//	fstream PIndex_file;
	fstream SIndex_file;
	string data_path = "data.txt";
	string PIndex_path = "primary.txt";
	string SIndex_path = "secondary.txt";


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
	//	data_file.open(data_path, ios::in | ios::out);
	//	PIndex_file.open(PIndex_path , ios::in | ios::out);
	}
	~Index() {
		data_file.close();
		PIndex_file.close();
	}

	static const int MAX_BUFFER_SIZE = 50 + 30 + 30 + sizeof(double) + 4 + 1 ; //for null char :)
	// Writes a record at file current position
	short writePrinter(printer& p) {
		short s=p.length();
        data_file.write((char*)&(s),sizeof(s));
        data_file<<p.id<<'|'<<p.model<<'|'<<p.description<<'|';
        data_file.write((char*)&p.price,sizeof(p.price));
        data_file<<'|';
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
		PIndexRecord temp;
		strcpy(temp.PK, p.id);
		temp.offset = data_file.tellp();
		PIndex.push_back(temp);

		writePrinter(p);
		sort(PIndex.begin(),PIndex.end(),PIndexComp);
	}

	void updatePrinter(char id[]) {
		int i = PIndexBinarySearch(id);
		if (i != -1) {
			printer p;
			cout<<"ID :"; cin>>p.id;
			cout<<"Model :"; cin>>p.model;
			cout<<"Description :"; cin>>p.description;
			cout<<"Price :"; cin>>p.price;
			short length;
			data_file.seekg(PIndex[i].offset);
			data_file.read((char*)&length,sizeof(length));
			cout<<"length "<<length<<endl;
			if(length>=p.length())
            {
                cout<<"fff";
                data_file.seekp(PIndex[i].offset+sizeof(length));
                data_file<<p.id<<'|'<<p.model<<'|'<<p.description<<'|';
                data_file.write((char*)&p.price,sizeof(p.price));
                data_file<<'|';
                strcpy(PIndex[i].PK,p.id);
                sort(PIndex.begin(),PIndex.end(),PIndexComp);
            }
            else
            {
                data_file.seekp(PIndex[i].offset+sizeof(length));
                data_file<<'*';
                PIndex.erase(PIndex.begin()+i);
                addPrinter(p);
                //deal with the indexes stuff
            }



		}
		else cout << "Not found!" << endl;
	}

	void deletePrinter(char id[]) {
		int i = PIndexBinarySearch(id);
		if (i != -1) {
			data_file.seekp(PIndex[i].offset + 2);
			data_file.write("*", 1);
            PIndex.erase(PIndex.begin()+i);
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
	char c;
	while(data_file.good())
	{
		short len;
		data_file.read((char*)&len,sizeof(len));
		if(data_file.get(c))
		{
			if(c == '*') cout << "*";
			else cout <<"-";
			data_file.seekg(len-1,ios::cur);
		}
		else break;
	}
	cout << endl;
}

	void savePIndex() {
		fstream PIndex_file(PIndex_path, ios::out);
		PIndex_file.seekp(0);
		sort(PIndex.begin(),PIndex.end(),PIndexComp);
		for (int i = 0; i < PIndex.size(); i++)
			PIndex_file.write((char*)&PIndex[i], sizeof(PIndex[i]));
		PIndex_file.close();
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

	void loadPIndex() {
		if (!exists(PIndex_path)) {
			ofstream fout;
			fout.open(PIndex_path, ios::app | ios::out | ios::binary);
			fout.close();
			ReconstructIndex();
		}
		else {
			ifstream fin(PIndex_path);
			PIndex.clear();
			while (fin.good())
			{
			    char c;
	            if(fin.get(c))fin.seekg(-1,ios::cur);
	            else break;
				PIndexRecord temp;
				fin.read((char*)&temp, sizeof(temp));
				cout<<temp.PK<<endl;
				PIndex.push_back(temp);
			}
            sort(PIndex.begin(),PIndex.end(),PIndexComp);
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
			strbuf.getline(temp.PK,30, '|');   ///copy paste eh ... allah yanwar
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
    Index ind1;
    ind1.loadPIndex();
   printer p,p2;
    cin>>p.id>>p.model>>p.description>>p.price;
//    cin>>p2.id>>p2.model>>p2.description>>p2.price;
////    short s=p.length();
//    f.write((char*)&(s),sizeof(s));
//    f<<p.id<<'|'<<p.model<<'|'<<p.description<<'|';
//    f.write((char*)&p.price,sizeof(p.price));
//    f<<'|';
//    s=p2.length();
//     f.write((char*)&s,sizeof(s));
//    f<<p2.id<<'|'<<p2.model<<'|'<<p2.description<<'|';
//    f.write((char*)&p2.price,sizeof(p2.price));
//    f<<'|';
//
    ind1.addPrinter(p);
//    ind1.addPrinter(p2);
    //  ind1.deletePrinter("20150204");
   // ind1.deletePrinter("60");
   //ind1.updatePrinter("70");
 // ind1.compactFile();

   ind1.visualizeFile();
    ind1.savePIndex();

}
