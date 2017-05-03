#include <iostream>
#include "BSTFCI.h"
using namespace std;
void mirror(BSTNode<int>*node)
{
  if (node==NULL)
    return;
  else
  {
    BSTNode<int>* temp;
    mirror(node->left);
    mirror(node->right);
    temp        = node->left;
    node->left  = node->right;
    node->right = temp;
  }
}
int main()
{
    BSTNode <int> *root  = new BSTNode<int>(1);
    root->left           = new BSTNode<int>(2);
    root->right          = new BSTNode<int>(3);
    root->left->left     = new BSTNode<int>(4);
    root->left->right    = new BSTNode<int>(5);
    cout<<"Original Tree: ";
    root->print();
    cout<<endl;
    mirror(root);
    cout<<"Mirrored Tree: ";
    root->print();
    return 0;
}
