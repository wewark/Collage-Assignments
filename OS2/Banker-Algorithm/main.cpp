#include <iostream>
#include <vector>
#include <stdlib.h>
using namespace std;

int numProcess,numResources,x;
void print(vector<int>available,vector<vector<int>>allocated,vector<vector<int>>needed,vector<bool>visited)
{
    cout<<endl<<endl;
    cout<<"Available : ";
    for(int i=0;i<numResources;i++)
        cout<<available[i]<<" ";
    cout<<endl;
    cout<<"       ALLOCATION            NEED"<<endl;
    cout<<"-----------------------------------------"<<endl;
    for(int i=0;i<numProcess;i++)
    {
        if(!visited[i])
        {
            cout<<"P"<<i<<"          ";
            for(int j=0;j<numResources;j++)
                cout<<allocated[i][j]<<" ";
            cout<<"            ";
            for(int j=0;j<numResources;j++)
                cout<<needed[i][j]<<" ";
            cout<<endl;
        }
    }
    cout<<endl<<endl;
}
bool Banker(vector<int>available,vector<vector<int>>maximum,vector<vector<int>>allocated)
{
    vector<vector<int>>needed(numProcess);
    vector<bool>visited(numProcess,0);
    for(int i=0;i<numProcess;i++)
    {
        for(int j=0;j<numResources;j++) {
            needed[i].push_back( maximum[i][j] - allocated[i][j]);
            if(needed[i][j]<0)return false;
            if(available[j]<0)return false;
        }
    }
    int t=numProcess;
    bool ok=true;
    vector<int>order;
    while(t--)
    {
        bool release=0;
        int indx=-1;
        bool foundFree=0;
        print(available,allocated,needed,visited);
        for(int i=0;i<numProcess;i++)
        {
            if(!visited[i])
            {
                foundFree=1;
                bool allisgood=1;
                for(int j=0;j<numResources;j++)
                {
                    if(needed[i][j]>available[j])
                        allisgood=0;
                }
                if(allisgood)
                {
                    visited[i]=1;
                    release=1;
                    indx=i;
                    break;
                }
            }
        }
        if(release)
        {
            cout<<"Available : ";
            for(int i=0;i<numResources;i++)
                cout<<available[i]<<" ";
            cout<<endl;
            cout<<"P"<<indx<<" ok; releases : ";
            for(int i=0;i<numResources;i++){
                cout<<allocated[indx][i]<<" ";
                available[i]+=allocated[indx][i];
            }
            cout<<endl;
            order.push_back(indx);
        }
        else
        {
            if(foundFree)ok=false;
            break;
        }
    }
    cout<<endl;
    if(ok)
    {
        cout<<"The System is safe and the order is ";
        cout<<"< ";
        for(int i=0;i<numProcess;i++){
            cout<<"P"<<order[i];
            if(i!=numProcess-1)cout<<",";
            cout<<" ";
        }
        cout<<">"<<endl;
    }
    return ok;

}
int main() {

    cout<<"Enter the number of process: ";
    cin>>numProcess;
    cout<<"Enter the number of resources: ";
    cin>>numResources;
    vector<int>available(numResources);
    vector<vector<int>>maximum(numProcess);
    vector<vector<int>>allocated(numProcess);

    cout<<"Enter the "<<numResources<<" Available Resources"<<endl;
    for(int i=0;i<numResources;i++)
    {
        cin>>available[i];
    }
    cout<<"Enter the maximum demand of each process"<<endl;
    for(int i=0;i<numProcess;i++)
    {
        for(int j=0;j<numResources;j++)
        {
            cin>>x;
            maximum[i].push_back(x);
        }
    }
    cout<<"Enter the amount currently allocated for each process"<<endl;
    for(int i=0;i<numProcess;i++)
    {
        for(int j=0;j<numResources;j++)
        {
            cin>>x;
            allocated[i].push_back(x);
        }
    }

    Banker(available,maximum,allocated);
    cout<<endl;
    int choice;
    while(true)
    {
        cout<<"1:Request"<<endl;
        cout<<"2:Exit"<<endl;
        cin>>choice;
        if(choice==1)
        {
            cout<<"Enter the number of the process: ";
            cin>>choice;
            vector<int>request;
            if(choice>=0&&choice<numProcess)
            {
                cout<<"Enter your request: ";
                for(int i=0;i<numResources;i++)
                {
                    cin>>x;
                    request.push_back(x);
                }
                cout<<"P"<<choice<<" request (";
                for(int i=0;i<numResources;i++)
                {
                    cout<<request[i];
                    if(i!=numResources-1)cout<<",";
                }
                cout<<") ?"<<endl;
                cout<<"1:Yes    Otherwise:No"<<endl;
                cin>>x;
                if(x==1)
                {
                    for(int i=0;i<numResources;i++){
                        allocated[choice][i]+=request[i];
                        available[i]-=request[i];
                    }
                    bool check=Banker(available,maximum,allocated);
                    if(!check)
                    {
                        cout<<"Request Cannot be granted"<<endl;
                        for(int i=0;i<numResources;i++){
                            allocated[choice][i]-=request[i];
                            available[i]+=request[i];
                        }
                    }
                }
            }
            else cout<<"Invalid Number"<<endl;
        }
        else if(choice==2)break;
        else cout<<"Invalid choice"<<endl;
        char c;
        cout<<"Press any key to continue"<<endl;
        cin.ignore();
        cin.get(c);
        system("cls");
    }



    return 0;
}
