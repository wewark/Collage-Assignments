#include <iostream>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;

int avg1 = 0, avg2 = 0, avg3 = 0, avg4 = 0;
int multiplication(int key)
{
	double a = (sqrt(5) - 1) / 2;
	double ret = floor(997 * 1.0*fmod((key*1.0*a), (1.0)));
	return ret;
}

int foldshift(int key)
{
	int sum = 0;
	while (key)
	{
		sum += key % 1000;
		key /= 1000;
	}
	return sum % 997;
}

int midsquare(int key)
{
	int ret;
	long long sum = key*key;
	sum /= 100;
	ret = sum % 1000;
	return ret;
}

struct record
{
	int id;
	char name[51];
};

struct hashed {
	int id;
	int offset;
};

class method1 {
private:
	fstream file;
	fstream data;

public:
	method1()
	{
		file.open("hash1.txt", ios::in | ios::out);
		data.open("data1.txt", ios::in | ios::out);
	}
	void addrecord(record &r)
	{
		data.clear();
		file.clear();
		data.seekp(0, ios::end);   ///seek to the end of the main data file
		int of = data.tellp();      ///get the offset of where i will put the new record
		hashed h;
		h.id = r.id;
		h.offset = of;
		data.write((char*)&r, sizeof(r));       /// write the record in the data file
		int hashIndex = multiplication(r.id);    /// get the hashIndex from hash function
		while (true) {
			file.seekg(hashIndex * 16);              ///i will seek to the place of the hash index
			char c, c2;
			file.get(c);                           /// i will get the first char in the bucket
			file.seekg((hashIndex * 16) + 8);                /// then i get the first char in the second record in the bucket
			file.get(c2);
			if (c == '|' || c == '#') {                            /// if the first char in the bucket is empty i will put the record here
				file.seekp(hashIndex * 16);
				file.write((char*)&h, sizeof(h));   /// i will write the record here
				break;
			}
			else if (c2 == '|' || c == '#') {                          ///same but i will check for the second record in the bucket
				file.seekp((hashIndex * 16) + 8);
				file.write((char*)&h, sizeof(h));
				break;
			}
			else
			{
				while (true) {
					hashIndex++;     /// and i start to increment the hashindex until i find an empty place
					hashIndex = hashIndex % 997;
					file.seekg(hashIndex * 16);
					file.get(c);
					if (c == '|' || c == '#')break;
				}
			}
		}
	}

	int Search(int key)
	{
		data.clear();
		file.clear();
		int hashIndex = multiplication(key);
		char c, c2;
		int ret = -1;
		int i = 0;
		while (true)
		{
			avg1++;
			hashed h1, h2;
			h1.id = -1;
			h2.id = -1;
			file.seekg(hashIndex * 16);
			file.get(c);
			if (c != '|' || c != '#')
			{
				file.seekg(-1, ios::cur);
				file.read((char*)&h1, sizeof(h1));
			}
			file.seekg((hashIndex * 16) + 8);
			file.get(c2);
			if (c2 != '|' || c2 != '#')
			{
				file.seekg(-1, ios::cur);
				file.read((char*)&h2, sizeof(h2));
			}
			//   cout<<h1.id<<" "<<h2.id<<" "<<next<<endl;
			if (h1.id == key)
			{
				int of = h1.offset;
				data.seekg(of);
				record r;
				data.read((char*)&r, sizeof(r));
				cout << r.id << endl;
				cout << r.name << endl;
				cout << "---------------" << endl;
				ret = (hashIndex * 16);
				break;
			}
			else if (h2.id == key)
			{
				int of = h2.offset;
				data.seekg(of);
				record r;
				data.read((char*)&r, sizeof(r));
				cout << r.id << endl;
				cout << r.name << endl;
				cout << "---------------" << endl;
				ret = (hashIndex * 16) + 8;
				break;
			}
			else if ((c == '|'&&c2 == '|'))
			{
				cout << "Record with id " << key << " not found " << endl;
				break;
			}
			hashIndex++;
			hashIndex = hashIndex % 997;
			i++;
		}
		return ret;
	}

	void Delete(int key)
	{
		file.clear();
		data.clear();
		int HashOf = Search(key);
		int DataOf;
		if (HashOf != -1)
		{
			hashed h;
			file.seekg(HashOf);
			file.read((char*)&h, sizeof(h));
			DataOf = h.offset;
			file.seekp(HashOf);
			for (int i = 0; i < 8; i++)
				file << '#';
			data.seekp(DataOf);
			data << '*';
		}
	}

	void printall()
	{
		file.clear();
		data.clear();
		char c;
		for (int i = 0; i <= 997; i++)
		{
			hashed h1, h2;
			int next;
			h1.id = -1;
			h2.id = -1;
			file.seekg(i * 16);
			file.get(c);
			if (c != '|'&&c != '#')
			{
				file.seekg(-1, ios::cur);
				file.read((char*)&h1, sizeof(h1));
			}
			file.seekg((i * 16) + 8);
			file.get(c);
			if (c != '|'&&c != '#')
			{
				file.seekg(-1, ios::cur);
				file.read((char*)&h2, sizeof(h2));
			}
			if (h1.id != -1)
			{
				int of = h1.offset;
				data.seekg(of);
				record r;
				data.read((char*)&r, sizeof(r));
				cout << r.id << endl;
				cout << r.name << endl;
				cout << "---------------" << endl;
			}
			else if (h2.id != -1)
			{
				int of = h2.offset;
				data.seekg(of);
				record r;
				data.read((char*)&r, sizeof(r));
				cout << r.id << endl;
				cout << r.name << endl;
				cout << "---------------" << endl;
			}
		}
	}
};

class method2 {
private:
	fstream file;
	fstream data;

public:
	method2()
	{
		file.open("hash2.txt", ios::in | ios::out);
		data.open("data2.txt", ios::in | ios::out);
	}
	void addrecord(record &r)
	{
		data.clear();
		file.clear();
		data.seekp(0, ios::end);   ///seek to the end of the main data file
		int of = data.tellp();      ///get the offset of where i will put the new record
		hashed h;
		h.id = r.id;
		h.offset = of;
		data.write((char*)&r, sizeof(r));       /// write the record in the data file
		int hashIndex = multiplication(r.id);    /// get the hashIndex from hash function
		int i = 1;
		while (true) {
			file.seekg(hashIndex * 16);              ///i will seek to the place of the hash index
			char c, c2;
			file.get(c);                           /// i will get the first char in the bucket
			file.seekg((hashIndex * 16) + 8);                /// then i get the first char in the second record in the bucket
			file.get(c2);
			if (c == '|' || c == '#') {                            /// if the first char in the bucket is empty i will put the record here
				file.seekp(hashIndex * 16);
				file.write((char*)&h, sizeof(h));   /// i will write the record here
				break;
			}
			else if (c2 == '|' || c == '#') {                          ///same but i will check for the second record in the bucket
				file.seekp((hashIndex * 16) + 8);
				file.write((char*)&h, sizeof(h));
				break;
			}
			else
			{
				int intial = hashIndex;
				while (true) {
					hashIndex = intial + (i*i);     /// and i start to increment the hashindex until i find an empty place
					hashIndex = hashIndex % 997;
					file.seekg(hashIndex * 16);
					file.get(c);
					if (c == '|' || c == '#')break;
					i++;
				}
			}
		}
	}

	int Search(int key)
	{
		data.clear();
		file.clear();
		int hashIndex = multiplication(key);
		char c, c2;
		int ret = -1;
		int intial = hashIndex;
		int i = 1;
		while (true)
		{
			avg2++;
			hashed h1, h2;
			h1.id = -1;
			h2.id = -1;
			file.seekg(hashIndex * 16);
			file.get(c);
			if (c != '|' || c != '#')
			{
				file.seekg(-1, ios::cur);
				file.read((char*)&h1, sizeof(h1));
			}
			file.seekg((hashIndex * 16) + 8);
			file.get(c2);
			if (c2 != '|' || c2 != '#')
			{
				file.seekg(-1, ios::cur);
				file.read((char*)&h2, sizeof(h2));
			}
			//   cout<<h1.id<<" "<<h2.id<<" "<<next<<endl;
			if (h1.id == key)
			{
				int of = h1.offset;
				data.seekg(of);
				record r;
				data.read((char*)&r, sizeof(r));
				cout << r.id << endl;
				cout << r.name << endl;
				cout << "---------------" << endl;
				ret = (hashIndex * 16);
				break;
			}
			else if (h2.id == key)
			{
				int of = h2.offset;
				data.seekg(of);
				record r;
				data.read((char*)&r, sizeof(r));
				cout << r.id << endl;
				cout << r.name << endl;
				cout << "---------------" << endl;
				ret = (hashIndex * 16) + 8;
				break;
			}
			else if ((c == '|'&&c2 == '|'))
			{
				cout << "Record with id " << key << " not found " << endl;
				break;
			}
			hashIndex = intial + (i*i);
			hashIndex = hashIndex % 997;
			i++;
		}
		return ret;
	}

	void Delete(int key)
	{
		file.clear();
		data.clear();
		int HashOf = Search(key);
		int DataOf;
		if (HashOf != -1)
		{
			hashed h;
			file.seekg(HashOf);
			file.read((char*)&h, sizeof(h));
			DataOf = h.offset;
			file.seekp(HashOf);
			for (int i = 0; i < 8; i++)
				file << '#';
			data.seekp(DataOf);
			data << '*';
		}
	}

	void printall()
	{
		file.clear();
		data.clear();
		char c;
		for (int i = 0; i <= 997; i++)
		{
			hashed h1, h2;
			int next;
			h1.id = -1;
			h2.id = -1;
			file.seekg(i * 16);
			file.get(c);
			if (c != '|'&&c != '#')
			{
				file.seekg(-1, ios::cur);
				file.read((char*)&h1, sizeof(h1));
			}
			file.seekg((i * 16) + 8);
			file.get(c);
			if (c != '|'&&c != '#')
			{
				file.seekg(-1, ios::cur);
				file.read((char*)&h2, sizeof(h2));
			}
			if (h1.id != -1)
			{
				int of = h1.offset;
				data.seekg(of);
				record r;
				data.read((char*)&r, sizeof(r));
				cout << r.id << endl;
				cout << r.name << endl;
				cout << "---------------" << endl;
			}
			else if (h2.id != -1)
			{
				int of = h2.offset;
				data.seekg(of);
				record r;
				data.read((char*)&r, sizeof(r));
				cout << r.id << endl;
				cout << r.name << endl;
				cout << "---------------" << endl;
			}
		}
	}
};

class method3 {

private:
	fstream file;
	fstream data;


public:
	method3()
	{
		file.open("hash3.txt", ios::in | ios::out);
		data.open("data3.txt", ios::in | ios::out);
	}
	void addrecord(record &r)
	{
		data.clear();
		file.clear();
		data.seekp(0, ios::end);   ///seek to the end of the main data file
		int of = data.tellp();      ///get the offset of where i will put the new record
		hashed h;
		h.id = r.id;
		h.offset = of;
		data.write((char*)&r, sizeof(r));       /// write the record in the data file
		int hashIndex = foldshift(r.id);    /// get the hashIndex from hash function
		int i = 1;
		int step = midsquare(r.id);
		while (true) {
			file.seekg(hashIndex * 16);              ///i will seek to the place of the hash index
			char c, c2;
			file.get(c);                           /// i will get the first char in the bucket
			file.seekg((hashIndex * 16) + 8);                /// then i get the first char in the second record in the bucket
			file.get(c2);
			if (c == '|' || c == '#') {                            /// if the first char in the bucket is empty i will put the record here
				file.seekp(hashIndex * 16);
				file.write((char*)&h, sizeof(h));   /// i will write the record here
				break;
			}
			else if (c2 == '|' || c == '#') {                          ///same but i will check for the second record in the bucket
				file.seekp((hashIndex * 16) + 8);
				file.write((char*)&h, sizeof(h));
				break;
			}
			else
			{
				int intial = hashIndex;
				while (true) {
					hashIndex = intial + (i*step);     /// and i start to increment the hashindex until i find an empty place
					hashIndex = hashIndex % 997;
					file.seekg(hashIndex * 16);
					file.get(c);
					if (c == '|' || c == '#')break;
					i++;
				}
			}

		}
	}

	int Search(int key)
	{
		data.clear();
		file.clear();
		int hashIndex = foldshift(key);
		char c, c2;
		int ret = -1;
		int intial = hashIndex;
		int i = 1;
		int step = midsquare(key);
		while (true)
		{
			avg3++;
			hashed h1, h2;
			h1.id = -1;
			h2.id = -1;
			file.seekg(hashIndex * 16);
			file.get(c);
			if (c != '|' || c != '#')
			{
				file.seekg(-1, ios::cur);
				file.read((char*)&h1, sizeof(h1));
			}
			file.seekg((hashIndex * 16) + 8);
			file.get(c2);
			if (c2 != '|' || c2 != '#')
			{
				file.seekg(-1, ios::cur);
				file.read((char*)&h2, sizeof(h2));
			}
			//   cout<<h1.id<<" "<<h2.id<<" "<<next<<endl;
			if (h1.id == key)
			{
				int of = h1.offset;
				data.seekg(of);
				record r;
				data.read((char*)&r, sizeof(r));
				cout << r.id << endl;
				cout << r.name << endl;
				cout << "---------------" << endl;
				ret = (hashIndex * 16);
				break;
			}
			else if (h2.id == key)
			{
				int of = h2.offset;
				data.seekg(of);
				record r;
				data.read((char*)&r, sizeof(r));
				cout << r.id << endl;
				cout << r.name << endl;
				cout << "---------------" << endl;
				ret = (hashIndex * 16) + 8;
				break;
			}
			else if ((c == '|'&&c2 == '|'))
			{
				cout << "Record with id " << key << " not found " << endl;
				break;
			}
			hashIndex = intial + (i*step);
			hashIndex = hashIndex % 997;
			i++;
		}
		return ret;
	}

	void Delete(int key)
	{
		file.clear();
		data.clear();
		int HashOf = Search(key);
		int DataOf;
		if (HashOf != -1)
		{
			hashed h;
			file.seekg(HashOf);
			file.read((char*)&h, sizeof(h));
			DataOf = h.offset;
			file.seekp(HashOf);
			for (int i = 0; i < 8; i++)
				file << '#';
			data.seekp(DataOf);
			data << '*';
		}
	}

	void printall()
	{
		file.clear();
		data.clear();
		char c;
		for (int i = 0; i <= 997; i++)
		{
			hashed h1, h2;
			int next;
			h1.id = -1;
			h2.id = -1;
			file.seekg(i * 16);
			file.get(c);
			if (c != '|'&&c != '#')
			{
				file.seekg(-1, ios::cur);
				file.read((char*)&h1, sizeof(h1));
			}
			file.seekg((i * 16) + 8);
			file.get(c);
			if (c != '|'&&c != '#')
			{
				file.seekg(-1, ios::cur);
				file.read((char*)&h2, sizeof(h2));
			}
			if (h1.id != -1)
			{
				int of = h1.offset;
				data.seekg(of);
				record r;
				data.read((char*)&r, sizeof(r));
				cout << r.id << endl;
				cout << r.name << endl;
				cout << "---------------" << endl;
			}
			else if (h2.id != -1)
			{
				int of = h2.offset;
				data.seekg(of);
				record r;
				data.read((char*)&r, sizeof(r));
				cout << r.id << endl;
				cout << r.name << endl;
				cout << "---------------" << endl;
			}
		}
	}
};


class method4 {

private:
	fstream file;
	fstream data;
	fstream over;

public:
	method4()
	{
		file.open("hash.txt", ios::in | ios::out);
		data.open("data.txt", ios::in | ios::out);
		over.open("overflow.txt", ios::in | ios::out);
	}
	void addrecord(record &r)
	{
		data.clear();
		file.clear();
		over.clear();
		data.seekp(0, ios::end);   ///seek to the end of the main data file
		int of = data.tellp();      ///get the offset of where i will put the new record
		hashed h;
		h.id = r.id;
		h.offset = of;
		data.write((char*)&r, sizeof(r));       /// write the record in the data file
		int hashIndex = multiplication(r.id);    /// get the hashIndex from hash function
		int before = -1;                         /// initially i will say make the before = -1 as i came from no where
		int next;
		while (true) {
			file.seekg(hashIndex * 20);              ///i will seek to the place of the hash index
			char c, c2;
			file.get(c);                           /// i will get the first char in the bucket
			file.seekg(7, ios::cur);                /// then i get the first char in the second record in the bucket
			file.get(c2);
			if (c == '|' || c == '#') {                            /// if the first char in the bucket is empty i will put the record here
				file.seekp(hashIndex * 20);
				file.write((char*)&h, sizeof(h));   /// i will write the record here
				break;
			}
			else if (c2 == '|' || c == '#') {                          ///same but i will check for the second record in the bucket
				file.seekp((hashIndex * 20) + 8);
				file.write((char*)&h, sizeof(h));
				break;
			}
			else
			{
				file.seekg((hashIndex * 20) + 16);                 ///if both of the two records are full
				file.read((char*)&next, sizeof(next));          /// then i read the next of the bucket
				if (next == -1) {                  /// if the next == -1 means that bucket has no next
					over.seekp(0, ios::end);
					int place = (over.tellp() / 20);
					file.seekp((hashIndex * 20) + 16);
					file.write((char*)&place, sizeof(place));
					over.write((char*)&h, sizeof(h));
					break;
				}
				else
				{
					while (true)
					{

						over.seekg((next * 20) + 8);
						char c;
						over.get(c);
						if (c == '|' || c == '#')
						{
							over.seekp((next * 20) + 8);
							over.write((char*)&h, sizeof(h));
							break;
						}
						before = next;
						over.seekg((next * 20) + 16);
						over.read((char*)&next, sizeof(next));
						if (next == -1) {
							over.seekp(0, ios::end);
							int place = (over.tellp() / 20);
							over.write((char*)&h, sizeof(h));
							over.seekp((before * 20) + 16);
							over.write((char*)&place, sizeof(place));
							break;
						}
					}
					break;
				}
			}
		}
	}

	void Search(int key, int x) /// 0 to just search , 1 to search and delete
	{
		data.clear();
		file.clear();
		over.clear();
		int hashIndex = multiplication(key);
		char c, c2;
		avg4++;
		hashed h1, h2;
		int next;
		h1.id = -1;
		h2.id = -1;
		file.seekg(hashIndex * 20);
		file.get(c);
		if (c != '|'&&c != '#')
		{
			file.seekg(-1, ios::cur);
			file.read((char*)&h1, sizeof(h1));
		}
		file.seekg((hashIndex * 20) + 8);
		file.get(c2);
		if (c2 != '|'&&c2 != '#')
		{
			file.seekg(-1, ios::cur);
			file.read((char*)&h2, sizeof(h2));
		}
		file.seekg((hashIndex * 20) + 16);
		file.read((char*)&next, sizeof(next));
		//   cout<<h1.id<<" "<<h2.id<<" "<<next<<endl;
		if (h1.id == key&&x == 0)
		{
			int of = h1.offset;
			data.seekg(of);
			record r;
			data.read((char*)&r, sizeof(r));
			cout << r.id << endl;
			cout << r.name << endl;
			cout << "---------------" << endl;
		}
		else if (h1.id == key&&x == 1)
		{
			int of = h1.offset;
			data.seekp(of);
			data << '*';
			file.seekp((hashIndex * 20));
			for (int i = 0; i < 8; i++)
				file << '#';

		}
		else if (h2.id == key&&x == 0)
		{
			int of = h2.offset;
			data.seekg(of);
			record r;
			data.read((char*)&r, sizeof(r));
			cout << r.id << endl;
			cout << r.name << endl;
			cout << "---------------" << endl;
		}
		else if (h2.id == key&&x == 1)
		{
			int of = h2.offset;
			data.seekp(of);
			data << '*';
			file.seekp((hashIndex * 20) + 8);
			for (int i = 0; i < 8; i++)
				file << '#';
		}
		else if (next == -1)
		{
			cout << "Record with id " << key << " not found " << endl;
		}
		else
		{
			hashIndex = next;
			while (true)
			{
				avg4++;
				if (hashIndex == -1)
				{
					cout << "Record with id " << key << " not found " << endl;
					break;
				}
				else {
					over.seekg(hashIndex * 20);
					h1.id = -1;
					h2.id = -1;
					over.get(c);
					if (c != '|'&&c != '#')
					{
						over.seekg(-1, ios::cur);
						over.read((char*)&h1, sizeof(h1));
					}
					over.seekg((hashIndex * 20) + 8);
					over.get(c);
					if (c != '|'&&c != '#')
					{
						over.seekg(-1, ios::cur);
						over.read((char*)&h2, sizeof(h2));
					}
					over.seekg((hashIndex * 20) + 16);
					over.read((char*)&next, sizeof(next));

					if (h1.id == key&&x == 0)
					{
						int of = h1.offset;
						data.seekg(of);
						record r;
						data.read((char*)&r, sizeof(r));
						cout << r.id << endl;
						cout << r.name << endl;
						cout << "---------------" << endl;
					}
					else if (h1.id == key&&x == 1)
					{
						int of = h1.offset;
						data.seekp(of);
						data << '*';
						over.seekp((hashIndex * 20));
						for (int i = 0; i < 8; i++)
							over << '#';
					}
					else if (h2.id == key&&x == 0)
					{
						int of = h2.offset;
						data.seekg(of);
						record r;
						data.read((char*)&r, sizeof(r));
						cout << r.id << endl;
						cout << r.name << endl;
						cout << "---------------" << endl;
					}
					else if (h2.id == key&&x == 1)
					{
						int of = h2.offset;
						data.seekp(of);
						data << '*';
						over.seekp((hashIndex * 20) + 8);
						for (int i = 0; i < 8; i++)
							over << '#';
					}

					hashIndex = next;
				}

			}

		}

	}

	void Delete(int key)
	{
		file.clear();
		data.clear();
		over.clear();
		Search(key, 1);
	}

	void printall()
	{
		file.clear();
		data.clear();
		char c;
		for (int i = 0; i <= 997; i++)
		{
			hashed h1, h2;
			int next;
			h1.id = -1;
			h2.id = -1;
			file.seekg(i * 20);
			file.get(c);
			if (c != '|'&&c != '#')
			{
				file.seekg(-1, ios::cur);
				file.read((char*)&h1, sizeof(h1));
			}
			file.seekg((i * 20) + 8);
			file.get(c);
			if (c != '|'&&c != '#')
			{
				file.seekg(-1, ios::cur);
				file.read((char*)&h2, sizeof(h2));
			}
			file.seekg((i * 20) + 16);
			file.read((char*)&next, sizeof(next));
			if (h1.id != -1)
			{
				int of = h1.offset;
				data.seekg(of);
				record r;
				data.read((char*)&r, sizeof(r));
				cout << r.id << endl;
				cout << r.name << endl;
				cout << "---------------" << endl;
			}
			else if (h2.id != -1)
			{
				int of = h2.offset;
				data.seekg(of);
				record r;
				data.read((char*)&r, sizeof(r));
				cout << r.id << endl;
				cout << r.name << endl;
				cout << "---------------" << endl;
			}
			while (next != -1)
			{
				h1.id = -1;
				h2.id = -1;
				over.seekg(next * 20);
				over.get(c);
				if (c != '|'&&c != '#')
				{
					over.seekg(-1, ios::cur);
					over.read((char*)&h1, sizeof(h1));
				}
				over.seekg((i * 20) + 8);
				over.get(c);
				if (c != '|'&&c != '#')
				{
					over.seekg(-1, ios::cur);
					over.read((char*)&h2, sizeof(h2));
				}
				over.seekg((i * 20) + 16);
				over.read((char*)&next, sizeof(next));
				if (h1.id != -1)
				{
					int of = h1.offset;
					data.seekg(of);
					record r;
					data.read((char*)&r, sizeof(r));
					cout << r.id << endl;
					cout << r.name << endl;
					cout << "---------------" << endl;
				}
				else if (h2.id != -1)
				{
					int of = h2.offset;
					data.seekg(of);
					record r;
					data.read((char*)&r, sizeof(r));
					cout << r.id << endl;
					cout << r.name << endl;
					cout << "---------------" << endl;
				}
			}
		}
	}
};

void setall()
{
	fstream file1("hash1.txt", ios::out);
	fstream file2("hash2.txt", ios::out);
	fstream file3("hash3.txt", ios::out);
	fstream file4("hash.txt", ios::out);
	fstream over("overflow.txt", ios::out);
	for (int i = 0; i < 16000; i++)
	{
		file1 << '|';
		file2 << '|';
		file3 << '|';
	}
	for (int i = 0; i < 1000; i++)
	{
		int x = -1;
		for (int j = 0; j < 16; j++)
		{
			file4 << '|';
			over << '|';
		}
		file4.write((char*)&x, sizeof(x));
		over.write((char*)&x, sizeof(x));
	}
}

int main()
{

	setall();

	set<int> randomIDs;
	set<int>::iterator it;
	method1 m1;
	method2 m2;
	method3 m3;
	method4 m4;
	while (randomIDs.size() < 500)
	{
		int ID = 10000 + rand() % 1000000;
		randomIDs.insert(ID);
	}
	char name[51] = "refaie";
	it = randomIDs.begin();
	for (; it != randomIDs.end(); it++)
	{
		record r;
		strcpy(r.name, name);
		r.id = *it;
		m1.addrecord(r);
		m2.addrecord(r);
		m3.addrecord(r);
		m4.addrecord(r);
	}

	it = randomIDs.begin();
	for (; it != randomIDs.end(); it++)
	{
		//cout<<*it<<endl;
		m1.Search(*it);
		m2.Search(*it);
		m3.Search(*it);
		// m4.Search(*it,0);
	}
	cout << avg1 / 500 << " " << avg2 / 500 << " " << avg3 / 500 << " " << avg4 / 500 << endl;







	return 0;
}
