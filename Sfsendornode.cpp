#include<bits/stdc++.h>
using namespace std;
void shortest_distance(vector<vector<int>>&matrix){
        int INF = INT_MAX;
        int n = matrix.size();
        for(int i = 0; i < n; i++){
        	for(int j = 0; j < n; j++){
            	if(matrix[i][j] == -1)
                	matrix[i][j] = INF;
        	}
        }
        for (int k = 0; k < n; ++k) {
        	for (int i = 0; i < n; ++i) {
            	for (int j = 0; j < n; ++j) {
                	if (matrix[i][k] < INF && matrix[k][j] < INF and matrix[i][k] + matrix[k][j] < INF)
                    	matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);
            	}
        	}
        }
        for(int i= 0; i< n; i++){
        	for(int j = 0; j < n; j++){
            	if(matrix[i][j] >= INF)
                	matrix[i][j] = -1;
        	}
        }
    }
 
int main() {
    int n;
    cout<<"Enter Number of nodes:";
    cin>>n;
    vector<vector<int>> matrix(n, vector<int> (n, -1));  
    cout<<"Enter Distance\n";
    for(int i=0; i< n; i++) {
        for(int j=0; j< n; j++) { 
            cout<<i<<"->"<<j<<":";
        	cin>>matrix[i][j];
        }
    }
    shortest_distance(matrix);
    for(int i=0; i< n; i++) {
        for(int j=0; j< n; j++) {
        	cout<<matrix[i][j]<<" ";
        }
        cout<<endl;
    }
    return 0;
}