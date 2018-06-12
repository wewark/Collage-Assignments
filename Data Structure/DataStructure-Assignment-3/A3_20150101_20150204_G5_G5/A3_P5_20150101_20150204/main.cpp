#include <bits/stdc++.h>
using namespace std;

int main()
{
    string s;
    cin>>s;
    bool commented=false;
    stack<char>all;
    for(int i=0;i<s.size();i++)
    {
        if(!commented)
        {
            if(s[i]=='/'&&i+1!=s.size())
            {
                if(s[i+1]=='*'){
                    commented=true;
                    i++;
                }
            }
            else if(s[i]=='}'||s[i]==')'||s[i]==']'&&(!all.empty()))
            {
                if(all.top()=='{'&&s[i]=='}')
                    all.pop();
                else if(all.top()=='('&&s[i]==')')
                    all.pop();
                else if(all.top()=='['&&s[i]==']')
                    all.pop();
            }
            else
                all.push(s[i]);
        }
        if(commented)
        {
            if(s[i]=='*'&&i+1!=s.size())
            {
                if(s[i+1]=='/'){
                    commented=false;
                    i++;
                }
            }
        }

    }
    if(all.empty())cout<<"Valid";
    else cout<<"Not Valid";
    return 0;
}
