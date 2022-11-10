#include<bits/stdc++.h>
using namespace std; 
/* 
On demand distance vector routting protocol 
1.node->(_id,table->(dest,prev,next)) 
2.working 
    if destination is already prsent route 
    else do bfs and updatin reverse 
    5->4->3
*/  
class Node{ 
    int id;
    unordered_map<int,pair<int,int>> table;
    public:
    Node(int _id){
        id=_id;
    }  
    int get_id(){
        return id;
    } 
    void setNexthop(int dest,int _id){
        table[dest].first=_id;
    }
    void setPrevhop(int src,int _id){
        table[src].second=_id;
    }
    bool hasEntry(int dest){
        if(table.find(dest)==table.end())
        return false;
        return true;
    } 
    int next_hop(int dest){
        return table[dest].first;
    }
    int prev_hop(int dest){
        return table[dest].second;
    } 
    void printTable(){ 
        cout<<"Dest    | Previous Hop | Next Hop\n";
        for(auto x:table){
            cout<<x.first<<"        "<<x.second.second<<"               "<<x.second.first<<"\n";
        }
    }
};  

class AODV{
    unordered_map<int,vector<int>> g;
    unordered_map<int,Node*> id_node;
    public:
    void create_node(int _id){
        Node* current=new Node(_id); 
        g[_id]={};
    }
    void add_edge(int src_id,int dest_id){ 
        if(g.find(src_id)==g.end()){
            Node* new_node=new Node(src_id);  
            id_node[src_id]=new_node;
            g[src_id]={};
        }
        if(g.find(dest_id)==g.end()){
            Node* new_node=new Node(dest_id);  
            id_node[dest_id]=new_node;
            g[dest_id]={};
        }
        (g[src_id]).push_back(dest_id); 
        (g[dest_id]).push_back(src_id);
    }    
    bool BFS(int src, int dest,unordered_map<int,int> &pred){
        queue<int> q;
        unordered_map<int,bool> visited; 
        visited[src] = true;
        q.push(src);

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int i = 0; i < g[u].size(); i++) {
                if (visited.find(g[u][i]) == visited.end()) {
                    visited[g[u][i]] = true;
                    pred[g[u][i]] = u;
                    q.push(g[u][i]);
                    if (g[u][i] == dest)
                        return true;
                }
            }
        }
        return false;
}
 
    void RREQ(int src,int dest){
          unordered_map<int,int> pred;  
          //RREQ
          BFS(src,dest,pred); 
          //updating table
          Node* towords_dest=id_node[dest];
          Node* towords_src=id_node[dest]; 
          int temp=dest; 
          int next=-1; 
          /* RREP*/ 
          bool found=false;
          while(temp!=src){ 
            towords_dest->setNexthop(dest,next);
            towords_dest->setPrevhop(dest,pred[temp]);
            towords_src->setNexthop(src,pred[temp]);
            towords_src->setPrevhop(src,next); 
            towords_dest=towords_src=id_node[pred[temp]]; 
            next=temp;    
            temp=pred[temp]; 
          }  
            towords_dest->setNexthop(dest,next);
            towords_dest->setPrevhop(dest,-1);
            towords_src->setNexthop(src,-1);
            towords_src->setPrevhop(src,next); 

    } 
    void get_path(int src_id,int dest_id){
         if(g.find(src_id)==g.end()||g.find(dest_id)==g.end()){
            cout<<"node is not part of network\n";
            return;
         }
         Node *src=id_node[src_id];
         if(!(src->hasEntry(dest_id))){
            RREQ(src_id,dest_id);  
         }  
         while(src->next_hop(dest_id)!=dest_id){
               cout<<src->get_id()<<"->"; 
               src=id_node[src->next_hop(dest_id)];
         } 
         cout<<dest_id<<"\n";
    } 
    void get_route_table(int id){
         if(id_node.find(id)==id_node.end()){
            cout<<"Not part of network";
            return;
         }
        Node* node_=id_node[id];
        node_->printTable();
    } 
};
int main(){
    char ch='8'; 
    AODV network;
    while(ch!='4'){
        cout<<"1.Add adges\n2.Find path\n3.See route table\n4.Exit\n";
        cin>>ch; 
        if(ch=='1'){ 
            cout<<"Enter Number of edge to add:";
            int n;
            cin>>n;
            cout<<"Enter source id and dest id:\n"; 
            while(n--){
            int src,dest;
            cin>>src>>dest;
            network.add_edge(src,dest); 
            } 
        } 
        if(ch=='2'){
            cout<<"Enter source id and dest id:"; 
            int src,dest;
            cin>>src>>dest; 
            network.get_path(src,dest); 
        }if(ch=='3'){
            cout<<"Enter router id:";
            int id;
            cin>>id;
            network.get_route_table(id);
        }
    }
}