#include <algorithm>
#include <iostream>
#include <iomanip>
#include <iterator>
#include <fstream>
#include <string>
#include <sstream>
#include <typeinfo>
#include <vector>

using namespace std;

/*struct Edge {
      int edge, start_node, end_node;
      double prob;
   };

struct Node {
      int node, degree;
      bool act;
      vector<int> adjNode;
   };*/

class Graph
{
   public:
   int numVert;
   vector<int> node;
   vector<vector<int>> pre, nxt;
   vector<vector<double>> pre_prob, nxt_prob;
   Graph(int nVert){
      numVert = nVert;
      node = vector<int>(0);
      pre = vector<vector<int>>(0);
      nxt = vector<vector<int>>(0);
      pre_prob = vector<vector<double>>(0);
      nxt_prob = vector<vector<double>>(0);
      for (int i = 0; i < nVert; i++){
         addNode(i);
      }
   };
   Graph(){
      numVert = 0;
      node = vector<int>(0);
      pre = vector<vector<int>>(0);
      nxt = vector<vector<int>>(0);
      pre_prob = vector<vector<double>>(0);
      nxt_prob = vector<vector<double>>(0);      
   }
   void addNode(int u){
      numVert++;
      node.push_back(u);
      nxt.push_back(vector<int>);
      pre.push_back(vector<int>);
   }
   void addEdge(int u, int v){
      if (u>numVert-1 || v>numVert-1){
         cout<<"illegal node number"<<endl;
         return;
      }
      nxt[u].push_back(v);
      pre[v].push_back(u);
      return;
   }
   //void write( ostream &out );
};
//======================================================================



struct adjNode {
    int val, cost;
    adjNode* next;
};


int main()
{
   Graph g1(16),g2;


   ifstream infile ("data.txt");
   
   if (infile.is_open())
   {
      
      for(int i=0; i < 16; i++){
         infile >> edge[i].start_node >> edge[i].end_node >> edge[i].prob;

         // edge[i].prob = ((double) rand() / (RAND_MAX));
         
         adj[edge[i].start_node-1][enedge[i].end_noded-1] = edge[i].prob;
         
         cout << edge[i].start_node << " " << edge[i].end_node << " " << edge[i].prob << endl;
      }
      
   }
   infile.close();

  return 0;

}