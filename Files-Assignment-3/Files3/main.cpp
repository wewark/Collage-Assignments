#include <iostream>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;

<<<<<<< HEAD
int avg1=0,avg2=0,avg3=0,avg4=0,search1=0,search2=0,search3=0,search4=0,delete1=0,delete2=0,delete3=0,delete4=0,s1=0,s2=0,s3=0,s4=0;
=======
int avg1 = 0, avg2 = 0, avg3 = 0, avg4 = 0;
>>>>>>> origin/master
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
<<<<<<< HEAD
    int id;
    char name[51];
    int next;
=======
	int id;
	char name[51];
>>>>>>> origin/master
};

struct hashed {
	int id;
	int offset;
};

<<<<<<< HEAD
class method1{

private :
    fstream data;


public :
    method1()
    {
        data.open("data1.txt" , ios::in|ios::out);
    }
void addrecord(record &r )
{
    data.clear();
    int of=multiplication(r.id)*sizeof(r)*2;
    int newof=of;
    int id;
    do{
        for(int i=0;i<2;i++){
            data.seekg(newof);
            data.read((char*)&id,sizeof(id));
                if(id==-1||id==-2)
                {
                    data.seekp(newof);
                    data.write((char*)&r,sizeof(r));
                    return ;
                }
                else if(i!=1){
                    newof+=sizeof(r);
                }
        }
        newof=(newof+sizeof(r))%(997*2*sizeof(r));
    }
    while(newof!=of);

}

void Search(int key)
{
    data.clear();
    int of=multiplication(key)*sizeof(record)*2;
    int newof=of;
    int id;
    do{
        for(int i=0;i<2;i++){
            avg1++;
            s1++;
            data.seekg(newof);
            data.read((char*)&id,sizeof(id));
                if(id==key)
                {
                    record r;
                    data.seekg(newof);
                    data.read((char*)&r,sizeof(r));
                    cout<<r.id<<" "<<r.name<<endl;
                    return ;
                }
                else if(id==-1)
                {
                    cout<<key<<" record not found "<<endl;
                    return ;
                }
                else if(i!=1){

                    newof+=sizeof(record);
                }
        }
        newof=(newof+sizeof(record))%(997*2*sizeof(record));
    }
    while(newof!=of);
}

void Delete(int key)
{
    data.clear();
    int of=multiplication(key)*sizeof(record)*2;
    int newof=of;
    int id;
    do{
        for(int i=0;i<2;i++){
            avg1++;
            delete1++;
            data.seekg(newof);
            data.read((char*)&id,sizeof(id));
                if(id==key)
                {
                    record r;
                    r.id=-2;
                    data.seekp(newof);
                    data.write((char*)&r,sizeof(r));
                    return ;
                }
                else if(id==-1)
                {
                    cout<<key<<" record not found "<<endl;
                    return ;
                }
                else if(i!=1){

                    newof+=sizeof(record);
                }
        }
        newof=(newof+sizeof(record))%(997*2*sizeof(record));
    }
    while(newof!=of);
}

};


class method2{


private :
    fstream data;


public :
    method2()
    {
        data.open("data2.txt" , ios::in|ios::out);
    }
void addrecord(record &r )
{
    data.clear();
    int intial=multiplication(r.id);
    int of=intial*sizeof(r)*2;
    int j=1;
    int newof=of;
    int id;
    do{
        for(int i=0;i<2;i++){
            data.seekg(newof);
            data.read((char*)&id,sizeof(id));
                if(id==-1||id==-2)
                {
                    data.seekp(newof);
                    data.write((char*)&r,sizeof(r));
                    return ;
                }
                else {
                    newof+=sizeof(r);
                }
        }
        newof=((intial+(j*j))%997)*sizeof(r)*2;
        j++;
    }
    while(newof!=of);
}

void Search(int key)
{
    data.clear();
    int intial=multiplication(key);
    int of=intial*sizeof(record)*2;
    int j=1;
    int newof=of;
    int id;
    do{
        for(int i=0;i<2;i++){
            avg2++;
            s2++;
            data.seekg(newof);
            data.read((char*)&id,sizeof(id));
                if(id==key)
                {
                    record r;
                    data.seekg(newof);
                    data.read((char*)&r,sizeof(r));
                    cout<<r.id<<" "<<r.name<<endl;
                    return ;
                }
                else if(id==-1)
                {
                    cout<<key<<" record not found "<<endl;
                    return ;
                }
                else {

                    newof+=sizeof(record);
                }
        }
        newof=((intial+(j*j))%997)*sizeof(record)*2;
        j++;
    }
    while(newof!=of);
}

void Delete(int key)
{
    data.clear();
    int intial=multiplication(key);
    int of=intial*sizeof(record)*2;
    int j=1;
    int newof=of;
    int id;
    do{
        for(int i=0;i<2;i++){
            avg2++;
            delete2++;
            data.seekg(newof);
            data.read((char*)&id,sizeof(id));
                if(id==key)
                {
                    record r;
                    r.id=-2;
                    data.seekp(newof);
                    data.write((char*)&r,sizeof(r));
                    return ;
                }
                else if(id==-1)
                {
                    cout<<key<<" record not found "<<endl;
                    return ;
                }
                else {

                    newof+=sizeof(record);
                }
        }
         newof=((intial+(j*j))%997)*sizeof(record)*2;
        j++;
    }
    while(newof!=of);
}


};


class method3{

private :
    fstream data;


public :
    method3()
    {
        data.open("data3.txt" , ios::in|ios::out);
    }
void addrecord(record &r )
{
    data.clear();
    int intial=foldshift(r.id);
    int step=midsquare(r.id);
    int of=intial*sizeof(r)*2;
    int j=1;
    int newof=of;
    int id;
    do{
        for(int i=0;i<2;i++){
            data.seekg(newof);
            data.read((char*)&id,sizeof(id));
                if(id==-1||id==-2)
                {
                    data.seekp(newof);
                    data.write((char*)&r,sizeof(r));
                    return ;
                }
                else {
                    newof+=sizeof(r);
                }
        }
        newof=((intial+(j*step))%997)*sizeof(r)*2;
        j++;
    }
    while(newof!=of);
}

void Search(int key)
{
    data.clear();
    int intial=foldshift(key);
    int step=midsquare(key);
    int of=intial*sizeof(record)*2;
    int j=1;
    int newof=of;
    int id;
    do{
        for(int i=0;i<2;i++){
            avg3++;
            s3++;
            data.seekg(newof);
            data.read((char*)&id,sizeof(id));
                if(id==key)
                {
                    record r;
                    data.seekg(newof);
                    data.read((char*)&r,sizeof(r));
                    cout<<r.id<<" "<<r.name<<endl;
                    return ;
                }
                else if(id==-1)
                {
                    cout<<key<<" record not found "<<endl;
                    return ;
                }
                else {

                    newof+=sizeof(record);
                }
        }
        newof=((intial+(j*step))%997)*sizeof(record)*2;
        j++;
    }
    while(newof!=of);
}

void Delete(int key)
{
    data.clear();
    int intial=foldshift(key);
    int step=midsquare(key);
    int of=intial*sizeof(record)*2;
    int j=1;
    int newof=of;
    int id;
    do{
        for(int i=0;i<2;i++){
            avg3++;
            delete3++;
            data.seekg(newof);
            data.read((char*)&id,sizeof(id));
                if(id==key)
                {
                    record r;
                    r.id=-2;
                    data.seekp(newof);
                    data.write((char*)&r,sizeof(r));
                    return ;
                }
                else if(id==-1)
                {
                    cout<<key<<" record not found "<<endl;
                    return ;
                }
                else {

                    newof+=sizeof(record);
                }
        }
         newof=((intial+(j*step))%997)*sizeof(record)*2;
        j++;
    }
    while(newof!=of);
}

};


class method4{
private :
    fstream data;
    fstream over;

public :
    method4()
    {
        data.open("data4.txt" , ios::in|ios::out);
        over.open("overflow.txt",ios::in|ios::out);
    }

    void addrecord(record &r)
    {
        data.clear();
        over.clear();
        int of=multiplication(r.id)*sizeof(record)*2;
        int id;
        int next;
        for(int i=0;i<2;i++){
            data.seekg(of);
            data.read((char*)&id,sizeof(id));
            if(id==-1||id==-2)
            {
                data.seekp(of);
                data.write((char*)&r,sizeof(r));
                return ;
            }
            else if(i!=1)
            {
                of+=sizeof(record);
            }
            else if(i==1)
            {
                of+=(sizeof(record)-sizeof(int));
                data.seekg(of);
                data.read((char*)&next,sizeof(next));
            }
        }
        if(next==-1)
        {
            over.seekp(0,ios::end);
            int pos=over.tellp()/(2*sizeof(record));
            over.write((char*)&r,sizeof(r));
            data.seekp(of);
            data.write((char*)&pos,sizeof(pos));
            return ;
        }

        else {
            int before=-1;
            while(true)
            {
                if(next==-1)
                {
                    over.seekp(0,ios::end);
                    int pos=over.tellp()/(2*sizeof(record));
                    over.write((char*)&r,sizeof(r));
                    over.seekp(before);
                    over.write((char*)&pos,sizeof(pos));
                    return ;
                }
                of=next*sizeof(record)*2;
                for(int i=0;i<2;i++)
                {
                    over.seekg(of);
                    over.read((char*)&id,sizeof(id));
                    if(id==-1||id==-2)
                    {
                        over.seekp(of);
                        over.write((char*)&r,sizeof(r));
                        return ;
                    }
                    else if(i!=1)
                    {
                        of+=sizeof(r);
                    }
                    else if(i==1)
                    {
                        of+=(sizeof(r)-sizeof(int));
                        over.seekg(of);
                        over.read((char*)&next,sizeof(next));
                        before=of;
                    }
                }
            }
        }
    }

    void Search(int key)
    {
        int of=multiplication(key)*sizeof(record)*2;
        int id;
        int next;
        for(int i=0;i<2;i++){
            avg4++;
            s4++;
            data.seekg(of);
            data.read((char*)&id,sizeof(id));
            if(id==key)
            {
                record r;
                data.seekg(of);
                data.read((char*)&r,sizeof(r));
                cout<<r.id<<" "<<r.name<<endl;
                return ;
            }
            else if(i!=1)
            {
                of+=sizeof(record);
            }
            else if(i==1)
            {
                of+=(sizeof(record)-sizeof(int));
                data.seekg(of);
                data.read((char*)&next,sizeof(next));
            }
        }
        if(next==-1)
        {
            cout<<"Record not found"<<endl;
            return ;
        }
        else {
            while(true)
            {
                if(next==-1)
                {
                    cout<<"Record not found"<<endl;
                    return ;
                }
                of=next*sizeof(record)*2;
                for(int i=0;i<2;i++)
                {
                    avg4++;
                    s4++;
                    over.seekg(of);
                    over.read((char*)&id,sizeof(id));
                    if(id==key)
                    {
                        record r;
                        over.seekg(of);
                        over.read((char*)&r,sizeof(r));
                        cout<<r.id<<" "<<r.name<<endl;
                        return ;
                    }
                    else if(i!=1)
                    {
                        of+=sizeof(record);
                    }
                    else if(i==1)
                    {
                        of+=(sizeof(record)-sizeof(int));
                        over.seekg(of);
                        over.read((char*)&next,sizeof(next));
                    }
                }
            }
        }
    }

    void Delete(int key)
    {
        int of=multiplication(key)*sizeof(record)*2;
        int id;
        int next;
        for(int i=0;i<2;i++){
            avg4++;
            delete4++;
            data.seekg(of);
            data.read((char*)&id,sizeof(id));
            if(id==key)
            {
                record r;
                r.id=-2;
                data.seekp(of);
                data.write((char*)&r,sizeof(r));
                return ;
            }
            else if(i!=1)
            {
                of+=sizeof(record);
            }
            else if(i==1)
            {
                of+=(sizeof(record)-sizeof(int));
                data.seekg(of);
                data.read((char*)&next,sizeof(next));
            }
        }
        if(next==-1)
        {
            cout<<"Record not found"<<endl;
            return ;
        }
        else {
            while(true)
            {
                if(next==-1)
                {
                    cout<<"Record not found"<<endl;
                    return ;
                }
                of=next*sizeof(record)*2;
                for(int i=0;i<2;i++)
                {
                    avg4++;
                    delete4++;
                    over.seekg(of);
                    over.read((char*)&id,sizeof(id));
                    if(id==key)
                    {
                        record r;
                        r.id=-2;
                        over.seekp(of);
                        over.write((char*)&r,sizeof(r));
                        return ;
                    }
                    else if(i!=1)
                    {
                        of+=sizeof(record);
                    }
                    else if(i==1)
                    {
                        of+=(sizeof(record)-sizeof(int));
                        over.seekg(of);
                        over.read((char*)&next,sizeof(next));
                    }
                }
            }
        }
    }



=======
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
>>>>>>> origin/master
};

void setall()
{
<<<<<<< HEAD
    fstream file1("data1.txt",ios::out);
    fstream file2("data2.txt",ios::out);
    fstream file3("data3.txt",ios::out);
    fstream file4("data4.txt",ios::out);
    fstream over("overflow.txt",ios::out);
    record r;
    r.id=-1;
    r.next=-1;
    for(int i=0;i<2000;i++)
    {
        file1.write((char*)&r,sizeof(r));
        file2.write((char*)&r,sizeof(r));
        file3.write((char*)&r,sizeof(r));
        file4.write((char*)&r,sizeof(r));
    }

=======
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
>>>>>>> origin/master
}

<<<<<<< HEAD
setall();



set<int> randomIDs;
set<int>::iterator it;
method1 m1;
method2 m2;
method3 m3;
method4 m4;

while(randomIDs.size()<500)
{
    int ID = 10000+rand()%1000;
    randomIDs.insert(ID);
}
char name[51]="refaie";
it=randomIDs.begin();
for(;it!=randomIDs.end();it++)
{
    record r;
    strcpy(r.name,name);
    r.id=*it;
    m1.addrecord(r);
    m2.addrecord(r);
    m3.addrecord(r);
   // m4.addrecord(r);
}

it=randomIDs.begin();
for(;it!=randomIDs.end();it++)
{
    //cout<<*it<<endl;
    m1.Search(*it);
    m2.Search(*it);
    m3.Search(*it);
 //   m4.Search(*it);
}
search1=s1;
search2=s2;
search3=s3;
search4=s4;

s1=0;
s2=0;
s3=0;
s4=0;

int  i = 0;
for (it = randomIDs.begin(); it!=randomIDs.end();) {
        m1.Delete(*it);
        m2.Delete(*it);
        m3.Delete(*it);
        randomIDs.erase(it++);
        if(i == 49)
            break;
        i++;
}

it=randomIDs.begin();
for(;it!=randomIDs.end();it++)
{
    m1.Search(*it);
    m2.Search(*it);
   m3.Search(*it);
  // m4.Search(*it,0);
}

cout<<endl;
cout<<"METHOD       |   METHOD 1    |   METHOD 2   |   METHOD 3   |  METHOD 4"<<endl;
cout<<"-------------------------------------------------------------------------"<<endl;
cout<<"1st Search   |   "<<search1*1.0/500.0<<"      |   "<<search2*1.0/500.0<<"     |   "<<search3*1.0/500.0<<"      |  "<<search4*1.0/500.0<<endl;
cout<<"Delete       |   "<<delete1*1.0/50.0<<"       |   "<<delete2*1.0/50.0<<"      |   "<<delete3*1.0/50.0<<"      |  "<<delete4*1.0/50.0<<endl;
cout<<"2nd Search   |   "<<s1*1.0/450.0<<"     |   "<<s2*1.0/450.0<<"    |   "<<s3*1.0/450.0<<"    |  "<<s4*1.0/450.0<<endl;
cout<<"Average      |   "<<(avg1*1.0)/(1000.0)<<"      |   "<<(avg2*1.0)/1000.0<<"     |   "<<avg3*1.0/1000<<"      |  "<<avg4*1.0/1000<<endl;





=======
int main()
{
>>>>>>> origin/master

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

