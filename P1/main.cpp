#include <iostream>
#include <vector>
#include <stdlib.h>
#include <bits/stdc++.h>
using namespace std;

class student{
public:
string name;
int age;
double grade;
};



int main()
{
    vector<student>students;
    vector<string>names;
    double maxstudent=0;
    int index=0;
    cout<<"Welcome to Students Info.. program "<<endl;
    while(true)
    {
      cout<<"Enter your choice "<<endl;
      cout<<" 1) Add student "<<endl;
      cout<<" 2) Search student by name "<<endl;
      cout<<" 3) List students by alphabetical order "<<endl;
      cout<<" 4) update student's grade "<<endl;
      cout<<" 5) Find student ranked #1 "<<endl;
      cout<<" 6) Print all students "<<endl;
      cout<<" 7) Exit "<<endl;
      int choice;
      cin>>choice;
      system("CLS");
      if(choice==1)
      {
          student s;
          cout<<"Name :"; cin>>s.name;
          cout<<"Age  :"; cin>>s.age;
          cout<<"Grade:";cin>>s.grade;
          students.push_back(s);
          if(s.grade>maxstudent){
            maxstudent=s.grade;
            index=students.size()-1;
          }
          for (int i=0;i<s.name.size();i++)
            s.name[i]=tolower(s.name[i]);
          names.push_back(s.name);
      }
      else if(choice==2)
      {
          string name;
          cout<<"Enter the name of the student you want to search on : ";
          cin>>name;
          bool found=0;
          for(int i=0;i<students.size();i++)
          {
              if(students[i].name==name)
              {
                  found=1;
                  cout<<"Student found "<<endl;
                  cout<<"Name  :"<<students[i].name<<endl;
                  cout<<"Age   :"<<students[i].age<<endl;
                  cout<<"Grade :"<<students[i].grade<<endl;
                  break;
              }
          }
          if(!found) cout<<"Student with name : "<<name<<" Not found "<<endl;
      }
      else if(choice==3)
      {
          sort(names.begin(),names.end());
          for(int i=0;i<names.size();i++)
             cout<<i+1<<". "<<names[i]<<endl;
          cout<<"........................"<<endl;
      }
      else if(choice==4)
      {
          string name;
          cin>>name;
          cout<<"Enter the name of the student you want to update the grade : ";
          bool found=0;
          for(int i=0;i<students.size();i++)
          {
              if(students[i].name==name)
              {
                  found=1;
                  double g;
                  cout<<"Enter the new grade : ";cin>>g;
                  students[i].grade=g;
                  if(g>maxstudent){
                    maxstudent=g;
                    index=i;
                  }
                  break;
              }
          }
          if(!found) cout<<"there is no student with name "<<name<<" to update the grade "<<endl;

      }
      else if (choice==5)
      {
          cout<<"#1 ranked student "<<endl;
          cout<<"Name  :"<<students[index].name<<endl;
          cout<<"Age   :"<<students[index].age<<endl;
          cout<<"Grade :"<<students[index].grade<<endl;
      }
      else if (choice==6)
      {
          cout<<"There are "<<students.size()<<" here in the system "<<endl;
        for (int i=0;i<students.size();i++)
        {
            cout<<"Student #"<<i+1<<endl;
            cout<<"Name  :"<<students[i].name<<endl;
            cout<<"Age   :"<<students[i].age<<endl;
            cout<<"Grade :"<<students[i].grade<<endl;
            cout<<"..........................."<<endl;
        }
      }
      else if (choice==7)
      {
          cout<<"EXIT";
          return 0;
      }
      else
        cout <<"Unsupported Choice "<<endl;

       char c;
       cin.ignore();
          cout<<"Press any key to continue "<<endl;
          cin.get(c);
          system("CLS");
    }
    return 0;
}
