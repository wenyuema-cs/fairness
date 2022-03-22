#include <algorithm>
#include <iostream>
#include <iomanip>
#include <iterator>
#include <fstream>
#include <numeric>
#include <string>
#include <sstream>
#include <typeinfo>
#include <vector>

using namespace std;

double randam(){
   double r = ((double) rand() / (RAND_MAX)) ;
   //cout<<r;
   return r;
};

struct Edge {
   int edge, start_node, end_node;
   double prob;
};

struct Node {
   int node, degree;
   bool act;
   vector<double> pre_prob;
   vector<double> nxt_prob;
};

struct adjNode {
    int val, cost;
    adjNode* next;
};

class Graph
{
   public:
   int numVert;
   
   vector<int> node, act;
   vector<vector<int> > pre, nxt;
   vector<vector<double> > pre_prob, nxt_prob;
   Graph(int nVert){
      numVert = nVert;
      node = vector<int>(0);
      act = vector<int>(0);
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
      act.push_back(false);
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
bool myfunction (int i,int j) { return (i<j); } 

vector<int> sort_indexes(const vector<int> &v) {
  // initialize original index locations
  vector<int> idx(v.size());  
  iota(idx.begin(), idx.end(), 0);


  // sort indexes based on comparing values in v
  // using std::stable_sort instead of std::sort
  // to avoid unnecessary index re-orderings
  // when v contains elements of equal values 
  stable_sort(idx.begin(), idx.end(), &v(int i1, int i2){ return v[i1]<v[i2];});
  //stable_sort(idx.begin(), idx.end(), myfunction);

  cout<<"idx"<<endl;
  for(const auto& i: idx){
     cout<<i<<endl;
  }
  return idx;
}

void icExp(Graph g, vector<int> s,int mc,double epsilon){
   //int counter [6] = {};
   vector<int> counter(g.numVert);
   for(int i = 0; i<mc; i++){
      for(const auto& candi : s){
         int check = 1;
         cout<<"who's nex nodes lenth "<< g.nxt[candi].size() << endl;
         for (int neighbor =0; neighbor < g.nxt[candi].size(); neighbor++){
            cout<<"node "<<g.nxt[candi][neighbor]<<" may have chance be activate "<<endl;
            if(g.nxt_prob[candi][neighbor] < randam()){
               g.act[g.nxt[candi][neighbor]]=1;
               s.push_back(g.nxt_prob[candi][neighbor]);
               counter[g.nxt[candi][neighbor]]++;
               cout<<"is larger than"<<"node "<<g.nxt[candi][neighbor]<<" as probability"<< g.nxt_prob[candi][neighbor]<<endl;
               for(const auto& count : counter){
                  cout<<count;
               }
               cout<<endl;
               vector<int> sort_counter = sort_indexes(counter);
               // for (auto i: sort_indexes(counter)) {
               //    cout << "after sorted: "<<counter[i]<<endl
               // }
            }
            for(int k; k<g.act.size(); k++){
               check = g.act[k]&check;
               }
            }
         if(check == 1){
            break;
         }
         
      }

   }
}



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

   for (int i = 0; i < g1.node.size();i++){
      cout << g1.node[i] << "with size "<< g1.nxt[i].size()<<": ";
      for (int j =0; j < g1.nxt[i].size();j++){
         cout << "(" << g1.nxt[i][j] << "," << g1.nxt_prob[i][j]<<"), ";
      }
      cout << endl;
   }

   vector<int> select;
   select.push_back(3);
   select.push_back(2);  
   select = sort_indexes(select);
   //Model ic;
   icExp(g1,select,3,0.3);
  return 0;

}