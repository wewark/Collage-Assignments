#include <iostream>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;
fstream file("hash.txt",ios::in|ios::out);
fstream data("data.txt",ios::in|ios::out);

int multiplication(int key)
{
    double a = (sqrt(5)-1)/2;
    double ret = floor(997*1.0*fmod((key*1.0*a),(1.0)));
    return ret;
}

struct record
{
    int id;
    char name[51];
};

struct hashed{
   int id;
   int offset;
};

void addrecord(record &r )
{
    data.clear();
    file.clear();

    data.seekp(0,ios::end);   ///seek to the end of the main data file
    int of=data.tellp();      ///get the offset of where i will put the new record
    hashed h;
    h.id=r.id;
    h.offset=of;
    data.write((char*)&r,sizeof(r));       /// write the record in the data file
    int hashIndex=multiplication(r.id);    /// get the hashIndex from hash function
    int before=-1;                         /// initially i will say make the before = -1 as i came from no where
    int next;
    while(true){
    file.seekg(hashIndex*20);              ///i will seek to the place of the hash index
    char c,c2;
    file.get(c);                           /// i will get the first char in the bucket
    file.seekg(7,ios::cur);                /// then i get the first char in the second record in the bucket
    file.get(c2);
    if(c=='|'){                            /// if the first char in the bucket is empty i will put the record here
        file.seekp(hashIndex*20);
        file.write((char*)&h,sizeof(h));   /// i will write the record here
        if(before!=-1)                    /// check if i came from another bucket
        {
            file.seekp((before*20)+16);                        /// if i came from another bucket i will put the next of the before my place
            file.write((char*)&hashIndex,sizeof(hashIndex));
        }
        break;
    }
    else if(c2=='|') {                          ///same but i will check for the second record in the bucket
        file.seekp((hashIndex*20)+8);
        file.write((char*)&h,sizeof(h));
        if(before!=-1)
        {
            file.seekp((before*20)+16);
            file.write((char*)&hashIndex,sizeof(hashIndex));
        }
        break;
    }
    else
    {
         file.seekg((hashIndex*20)+16);                 ///if both of the two records are full
         file.read((char*)&next,sizeof(next));          /// then i read the next of the bucket
         if(next==-1){                                 /// if the next == -1 means that bucket has no next
            before=hashIndex;                         /// so i will make the before as my place
            while (true){
            hashIndex++;                             /// and i start to increment the hashindex until i find an empty place
            file.seekg(hashIndex*20);
            file.get(c);
            if(c=='|')break;
            }
         }
         else
         {
             before=hashIndex;
             hashIndex=next;
         }
    }
    }

}

int main()
{

// un comment this in the first time you use the program
//    for(int i=0;i<1000;i++)
//        {
//            int next=-1;
//            for(int j=0;j<16;j++)
//                file<<'|';
//            file.write((char*)&next,sizeof(next));
//        }


record r;
cin>>r.id;
cin>>r.name;

addrecord(r);


    return 0;
}
