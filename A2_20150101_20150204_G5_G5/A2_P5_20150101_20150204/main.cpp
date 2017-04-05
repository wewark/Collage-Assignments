#include <bits/stdc++.h>
using namespace std;
void InsertionWithBinary(vector<int>x)
{
    clock_t begin = clock();
    for(int i=1;i<x.size();i++)
    {
        int element=x[i];
        int start=0,End=i-1,mid,fnd;
        while(start<=End)
        {
            mid=(start+End)/2;
            if(x[mid]>element){
                fnd=mid;
                End=mid-1;
            }
            else if(x[mid]<element){
               start=mid+1;
               fnd=mid+1;
               }
            else if (x[mid]==element){
                fnd=mid;
                break;
                }
        }
        for(int j=i;j>mid;j--)
            x[j]=x[j-1];
        x[fnd]=element;
    }

    clock_t end = clock();
    int elapsed_ms = end - begin;
    cout<<"time of sort with binary search is "<<elapsed_ms<<endl<<endl;
}

void InsertionSort(vector<int>x)
{
    clock_t begin = clock();
    for(int i=1;i<x.size();i++)
    {
        int element=x[i];
        int j=i;
        while(j>0&&x[j-1]>element)
        {
            x[j]=x[j-1];
            j--;
        }
        x[j]=element;
    }
    clock_t end = clock();
    int elapsed_ms = end - begin;
    cout<<"time of normal insertion sort is "<<elapsed_ms<<endl;
    cout<<endl;
}
int main()
{
  for(int i=5000;i<=100000;i+=5000)
  {
      cout<<endl;
      cout<<i<<endl;
      vector<int>nums(i);
      for(int j=i;j>0;j--)
          nums[i-j]=j;
      InsertionWithBinary(nums);
      InsertionSort(nums);
  }
    return 0;
}
