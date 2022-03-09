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

struct Edge {
      int edge, start_node, end_node;
      double prob;
   };

struct Node {
      int node, degree;
      bool act;
      vector<int> adjNode;
   };

class Graph
{
   public:
   int numVert;
   vector<int> node;
   vector<vector<int> > pre, nxt;
   vector<vector<double> > pre_prob, nxt_prob;
   Graph(int nVert){
      numVert = nVert;
      node = vector<int>(0);
      pre = vector<vector<int> >(0);
      nxt = vector<vector<int> >(0);
      pre_prob = vector<vector<double> >(0);
      nxt_prob = vector<vector<double> >(0);
      for (int i = 0; i < nVert; i++){
         addNode(i);
      }
   };
   Graph(){
      numVert = 0;
      node = vector<int>(0);
      pre = vector<vector<int> >(0);
      nxt = vector<vector<int> >(0);
      pre_prob = vector<vector<double> >(0);
      nxt_prob = vector<vector<double> >(0);      
   }
   void addNode(int u){
      numVert++;
      node.push_back(u);
      nxt.push_back(vector<int>(0));
      pre.push_back(vector<int>(0));
      nxt_prob.push_back(vector<double>(0));
      pre_prob.push_back(vector<double>(0));
   }
   void addEdge(int u, int v,double p){
      if (u>numVert-1 || v>numVert-1){
         cout<<"illegal node number"<<endl;
         return;
      }
      nxt[u].push_back(v);
      pre[v].push_back(u);
      nxt_prob[u].push_back(p);
      pre_prob[v].push_back(p);
      return;
   }
   //void write( ostream &out );
};
//======================================================================

class Model
{
   void icExp(Graph g,vector<Node > s, t, epsilon)
}


struct adjNode {
    int val, cost;
    adjNode* next;
};


int main()
{
   cout << "constructing....";
   Graph g1(6),g2;
   cout << "done" <<endl;

   ifstream infile ("data.txt");
   int u,v;
   double p;
   if (infile.is_open())
   {
      cout << "adding nodes to g2....";
      for (int i = 0; i < 6; i++){
         g2.addNode(i);
      }
      cout <<"done"<<endl;
      for(int i=0; i < 16; i++){
         infile >> u >> v >> p;
         g1.addEdge(u-1,v-1,p);
         g2.addEdge(u-1,v-1,p);
         // edge[i].prob = ((double) rand() / (RAND_MAX));
      }
      
   }
   infile.close();
   int n = g1.node.size();
   cout << n << endl;
   cout << g1.node[0] << endl;
   for (int i = 0; i < g1.node.size();i++){
      cout << g1.node[i] << ": ";
      for (int j =0; j < g1.pre[i].size();j++){
         cout << "(" << g1.pre[i][j] << "," << g1.pre_prob[i][j]<<"), ";
      }
      cout << endl;
   }
  return 0;

}