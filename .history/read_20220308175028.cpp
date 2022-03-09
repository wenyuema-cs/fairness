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


class Graph
{
   int numVert, numEdge;
   vector< vector<int> > adj;

   struct Edge {
      int edge, start_node, end_node;
      double prob;
   };

   struct Node {
      int node, degree;
      bool act;
      vector<int> adjNode
   };

public:
   Graph();
   void write( ostream &out );
};
//======================================================================



struct adjNode {
    int val, cost;
    adjNode* next;
};


int main()
{
   Graph.Edge edge[16];
   Graph.Node node[6];

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