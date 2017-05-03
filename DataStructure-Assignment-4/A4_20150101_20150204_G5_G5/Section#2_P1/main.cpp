#include <bits/stdc++.h>
#include "BSTFCI.h"
using namespace std;
double evaluate(BSTNode<char>*ptr)
{
    if (ptr->left == NULL && ptr->right == NULL)
        return ptr->key-'0';
    else
    {
        double result = 0.0;
        double left = evaluate(ptr->left);
        double right = evaluate(ptr->right);
        char op = ptr->key;
        if (op=='+')
        result = left + right;
        else if(op=='-')
        result = left - right;
        else if(op=='*')
        result = left * right;
        else if(op=='/')
        result = left / right;
        return result;
    }
}
void evaluate(string s)
{
    stack<BSTNode<char>*>sta;
    for(int i=s.size()-1;i>=0;i--)
    {
        char val=s[i];
        if (val>='0'&&val<='9')
            {
                BSTNode<char>*n = new BSTNode<char>(val);
                sta.push(n);
            }
            else if (val=='+'||val=='-'||val=='*'||val=='/')
            {
                BSTNode<char>*n = new BSTNode<char>(val);
                n->left=sta.top();
                sta.pop();
                n->right=sta.top();
                sta.pop();
                sta.push(n);
            }
    }
    double result=evaluate(sta.top());
    cout<<result;
}

int main()
{
    string s;
    cout<<"Expression: ";
    cin>>s;
    cout<<"Evaluation: ";
    evaluate(s);

    /*
       +3*4/82  = 19
       +11 = 2
       -11 = 0
       /12 = 0.5
       +1*23 = 7
    */
    return 0;
}
