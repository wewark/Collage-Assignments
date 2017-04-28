#include <bits/stdc++.h>
using namespace std;
class TreeNode
{
    public:
        char data;
        TreeNode *left, *right;
        TreeNode(char d)
        {
            data = d;
            left = NULL;
            right = NULL;
        }
};
class StackNode
{
    public:
        TreeNode *treeNode;
        StackNode *next;
        StackNode(TreeNode *t)
        {
            treeNode = t;
            next = NULL;
        }
};
class ExpressionTree
{
    private:
        StackNode *top;
    public:
        ExpressionTree()
        {
            top = NULL;
        }
        void push(TreeNode *ptr)
        {
            if (top == NULL)
                top = new StackNode(ptr);
            else
            {
                StackNode *nptr = new StackNode(ptr);
                nptr->next = top;
                top = nptr;
            }
        }

        TreeNode *pop()
        {
            if (top == NULL)
            {
                cout<<"Empty"<<endl;
            }
            else
            {
                TreeNode *ptr = top->treeNode;
                top = top->next;
                return ptr;
            }
        }

        TreeNode *peek()
        {
            return top->treeNode;
        }

        void insert(char val)
        {
            if (val>='0'&&val<='9')
            {
                TreeNode *nptr = new TreeNode(val);
                push(nptr);
            }
            else if (val=='+'||val=='-'||val=='*'||val=='/')
            {
                TreeNode *nptr = new TreeNode(val);
                nptr->left = pop();
                nptr->right = pop();
                push(nptr);
            }
        }

        void buildTree(string eqn)
        {
            for(int i=eqn.size()-1;i>=0;i--)
                insert(eqn[i]);
        }

        double evaluate(TreeNode *ptr)
        {
            if (ptr->left == NULL && ptr->right == NULL)
                return ptr->data-'0';
            else
            {
                double result = 0.0;
                double left = evaluate(ptr->left);
                double right = evaluate(ptr->right);
                char op = ptr->data;
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

};

int main()
{
    string s;
    ExpressionTree tree1;
    cout<<"Expression: ";
    cin>>s;
    tree1.buildTree(s);
    cout<<"Evaluated Result : "<<tree1.evaluate(tree1.peek());
    return 0;
}
