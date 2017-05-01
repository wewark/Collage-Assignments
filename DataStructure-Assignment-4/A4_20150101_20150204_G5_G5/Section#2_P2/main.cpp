#include <iostream>
using namespace std;
void printPostOrder(string in,string pre)
{
   int root;
   for(int i=0;i<in.size();i++)
   {
       if(in[i]==pre[0])
       {
           root=i;
           break;
       }
   }
   if (root != 0)
      printPostOrder(in.substr(0,root),pre.substr(1,pre.size()-1));
   if (root != in.size()-1)
      printPostOrder(in.substr(root+1,in.size()-(root+1)),pre.substr(root+1,pre.size()-(root+1)));
   cout << pre[0];
}
int main()
{
    string preorder,inorder;
    cout<<"InOrder: ";
    cin>>inorder;
    cout<<"PreOrder: ";
    cin>>preorder;
    cout<<"PostOrder: ";
    printPostOrder(inorder,preorder);

    /*
     InOrder | PreOrder | PostOrder
     ------- | -------- | ---------
     1)FBGAC |  ABFGC   |  FGBCA
     2)A     |  A       |  A
     3)BAC   |  ABC     |  BCA
     4)FBI   |  IBF     |  FBI
     5)FBGI  |  IBFG    |  FGBI

    */
    return 0;
}
