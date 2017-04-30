#include <iostream>

using namespace std;

void printPostOrder(string in,string pre)
{
   // The first element in pre is always root, search it
   // in in to find left and right subtrees
  // cout<<in<<" "<<pre<<" "<<endl;
   int root;
   for(int i=0;i<in.size();i++)
   {
       if(in[i]==pre[0])
       {
           root=i;
           break;
       }
   }
   // If left subtree is not empty, print left subtree
   if (root != 0)
      printPostOrder(in.substr(0,root),pre.substr(1,pre.size()-1));
   // If right subtree is not empty, print right subtree
   if (root != in.size()-1)
      printPostOrder(in.substr(root+1,in.size()-(root+1)),pre.substr(root+1,pre.size()-(root+1)));
   // Print root
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

    return 0;
}
