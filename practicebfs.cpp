#include<iostream>
#include<vector>
#include<vector>
#include<queue>
#include<omp.h>
#include<bits/stdc++.h>
using namespace std;
queue<int>q;

void dfs(int start,int* arr,int n ,int visit[])
{

for(int i=0;i<n;i++)
{
  

    if((*(arr+(start*n)+i)==1) && (!visit[i]))
    {
        visit[i]=1;
cout<<i<<" ";
dfs(i,(int*)arr,n,visit);

    }
}
}
int main()
{
    cout<<"enter the vertex";
    int n;
    cin>>n;
     int arr[n][n]={0};
    
    cout<<"enter the edge";
    int edge;
    cin>>edge;

    for(int j=0;j<edge;j++)
    {
        int a, b;
        cout<<"enter the 2edge";
        cin>>a>>b;
        arr[a][b]=1;
        arr[b][a]=1;

    }
    int visit[n]={0};
     cout<<"enter the start";
     int start;
     cin>>start;

     clock_t strt=clock();
      visit[start]=1;
      cout<<start<<" ";
      q.push(start);
       
       dfs(start,(int*)arr,n,visit);

       clock_t stop=clock();

       cout<<"time"<<(double)(stop-strt)<<"ms"<<endl;
return 0;
}


