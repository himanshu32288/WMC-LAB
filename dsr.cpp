#include <bits/stdc++.h>
using namespace std;

int main() {
    unordered_map<int,vector<int>>adj;
    int n,m;
    cout<<"Enter Number of nodes and edges:";
    cin>>n>>m; 
    cout<<"source destination\n";
    for(int i = 0;i < m;i++){
        int u,v;
        cin>>u>>v;
        u--,v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int s,d; 
    cout<<"Enter source hope and destination hope:";
    cin>>s>>d;
    s--,d--;
    map<int,string>mp;
    vector<vector<int>>table(n,vector<int>(4,0));
    for(int i = 0;i < n;i++){
        table[i][2] = INT_MAX;
        table[i][0] = s + 1;
        table[i][1] = d + 1;
    }
    mp[s] = "1";
    table[s][2] = 0;
    // table[s][1] = d + 1;
    queue<pair<int,int>>pq;
    pq.push({0,s});
    while(!pq.empty()){
        int curr = pq.front().second;
        pq.pop();
        for(auto &nbr : adj[curr]){
        if(table[nbr][2] > table[curr][2] + 1){
            table[nbr][2] = table[curr][2] + 1;
            mp[nbr] = mp[curr] + "->" + to_string(nbr + 1); 
            pq.push({table[nbr][2],nbr});
        }
        }
    }
    int temp = d;
    int curr = temp;
    while(true){
        for(auto nbr : adj[temp]){
        if(table[nbr][2] < table[curr][2]){
            curr = nbr;
        }
        }
        temp = curr;
        mp[curr] = mp[d];
        if(curr == s)break;
    }
    for(int i = 0;i < n;i++){
        cout<<"For Node :"<<i + 1<<endl<<endl;
        cout<<"Source_ID : "<<table[i][0]<<endl;
        cout<<"Dest_ID   : "<<table[i][1]<<endl;
        cout<<"Path      : "<<mp[i]<<endl; 
        cout<<endl<<endl;
   }
}