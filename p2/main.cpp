#include <bits/stdc++.h>
using namespace std;
bool cmp(string x,string y)
{
    if(x<y||x=="Untitled")
        return true;
    else return false;
}
void BaisedSort(vector<string>&x){
  sort(x.begin(),x.end(),cmp);
}
int main()
{
   int n;
   cin>>n;
   vector<string>songs(n);
   for(int i=0;i<n;i++)
       cin>>songs[i];
   BaisedSort(songs);
   cout<<endl;
   for(int i=0;i<songs.size();i++)
     cout<<songs[i]<<endl;
}
