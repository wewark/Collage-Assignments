#include <bits/stdc++.h>

using namespace std;

int main()
{
    list<int>l1;
    list<int>::iterator it;
    list<int>::iterator it2;
    l1.push_back(6);
    l1.push_back(9);
    l1.push_back(11);
    l1.push_back(13);
    cout<<"First List: ";
    for(it=l1.begin();it!=l1.end();it++)
        cout<<*it<<" ";
    cout<<endl;
    list<int>l2;
    l2.push_back(5);
    l2.push_back(7);
    l2.push_back(8);
    l2.push_back(9);
    l2.push_back(9);
    l2.push_back(10);
    l2.push_back(12);
    l2.push_back(13);
    l2.push_back(14);
    l2.push_back(15);
    l2.push_back(16);
    l2.push_back(17);
    cout<<"Second List: ";
    for(it2=l2.begin();it2!=l2.end();it2++)
        cout<<*it2<<" ";
    cout<<endl;

    ///merging
     it=l1.begin();
     it2=l2.begin();
	  while (it!=l1.end()&&it2!=l2.end()){
	    if (*it2<*it)
	          l1.insert(it,*it2++);
	    else if(*it2>*it)
             it++;
        else if(*it2==*it)
            it2++;
	  }
	  while (it2!=l2.end()){
         l1.push_back(*it2);
         it2++;
	  }

///another way of merging
//  l1.merge(l2);
//erasing the duplicates
//    int val=-1;
//    for(it=l1.begin();it!=l1.end();){
//        if(*it==val)
//           l1.erase(it++);
//        else{
//        val=*it;
//        ++it;
//        }
//    }

    cout<<"Merged List: ";
    for(it=l1.begin();it!=l1.end();it++)
        cout<<*it<<" ";

    return 0;
}
