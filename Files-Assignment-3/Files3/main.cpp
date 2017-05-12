#include <iostream>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;

int avg1=0,avg2=0,avg3=0,avg4=0,search1=0,search2=0,search3=0,search4=0,delete1=0,delete2=0,delete3=0,delete4=0,s1=0,s2=0,s3=0,s4=0;
int multiplication(int key)
{
    double a = (sqrt(5)-1)/2;
    double ret = floor(997*1.0*fmod((key*1.0*a),(1.0)));
    return ret;
}

int foldshift(int key)
{
    int sum=0;
    while(key)
    {
       sum+=key%1000;
       key/=1000;
    }
    return sum%997;
}

int midsquare(int key)
{
    int ret;
    long long sum=key*key;
    sum/=100;
    ret=sum%1000;
    return ret;
}

struct record
{
    int id;
    char name[51];
    int next;
};

struct hashed{
   int id;
   int offset;
};

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



};

void setall()
{
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






    return 0;
}

