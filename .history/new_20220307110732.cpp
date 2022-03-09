#include<iostream>
#include <fstream>

using namespace std;

int main() {
  ifstream infile("data.txt");
  int n,m;
  int a,b,c;
  int cost[100][100];
  for(int i=0;i<n;++i) {
    for(int j=0;j<n;++j) {
      cost[i][j]=0;
    }
  }
  if (infile>>n>>m) {
    while (infile>>a>>b>>c) {
      for(int i=0;i<n;++i) {
        for(int j=0;j<n;++j) {
          cost[a-1][b-1]=c;
        }
      }
    }
  }
  for(int i=0;i<n;++i) {
    for(int j=0;j<n;++j) {
      cout<<cost[i][j]<<" ";
    }
    cout<<endl;
  }
  infile.close();
}