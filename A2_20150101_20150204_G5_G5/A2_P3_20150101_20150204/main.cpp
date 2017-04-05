#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin>>n;
    bool check=false;
    vector<int>sides(n);
    for(int i=0;i<n;i++)
        cin>>sides[i];
    sort(sides.begin(),sides.end());
    for(int i=0;i<n-2;i++){
        if((sides[i]+sides[i+1])>sides[i+2]&&sides[i+1]+sides[i+2]>sides[i]&&sides[i+2]+sides[i]>sides[i+1]){
           check=true;
           break;
        }
    }
    if(check)cout<<"Can construct at least one degenerate triangle "<<endl;
    else cout<<"Cannot construct at least one degenerate triangle "<<endl;
}
