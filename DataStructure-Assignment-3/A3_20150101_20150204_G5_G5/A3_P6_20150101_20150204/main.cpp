#include <bits/stdc++.h>
using namespace std;
class Stack
{
public:
    queue<int>q1;
    int top()
    {
        if(q1.empty())
        {
            cout<<"The Stack is empty";
            return -1;
        }
        else return q1.front();
    }
    void pop()
    {
        if(q1.empty())
        {
            cout<<"The Stack is empty";
            return;
        }
        else q1.pop();
    }
    void push(int v)
    {
        int s=q1.size();
        q1.push(v);
         for (int i=0;i<s;i++)
        {
            q1.push(q1.front());
            q1.pop();
        }
    }


};
int main()
{
    Stack s;
    s.push(10);
    s.push(20);
    cout<<s.top()<<endl;
    s.pop();
    cout << s.top() << endl;

    return 0;
}
