#include <algorithm>
#include <iostream>
#include <iomanip>
#include <iterator>
#include <fstream>
#include <numeric>
#include <string>
#include <sstream>
#include <queue>
#include <typeinfo>
#include <utility> 
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
      //numVert = nVert;
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

vector<int> sort_indexes(const vector<int> &v) {
  // initialize original index locations
  vector<int> idx(v.size());  
  iota(idx.begin(), idx.end(), 0);
  //cout <<"before sorted"<<endl;
  for(const auto& i: v){
     cout<<i<<" ";
  }
  cout <<endl;

  // sort indexes based on comparing values in v
  // using std::stable_sort instead of std::sort
  // to avoid unnecessary index re-orderings
  // when v contains elements of equal values 
  auto comp=[&v](int i1, int i2){ return v[i1]<v[i2];};
  stable_sort(idx.begin(), idx.end(), comp);
  //stable_sort(idx.begin(), idx.end(), myfunction);

//   cout<<"after sort as:"<<endl;
//   for(const auto& i: idx){
//      cout<<i<<" ";
//   }
//   cout <<endl;
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
               cout<<typeid(counter).name()<<endl;
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

pair<int,int> icExpq(Graph g, queue<int> s,int mc,double epsilon){
   //int counter [6] = {};
   epsilon = epsilon*mc;
   vector<int> counter(g.numVert);
   //cout<<"Counter==="<<counter.size()<<endl;
   for(int i = 0; i<mc; i++){
      while(!s.empty()){
         //cout<<"=========================================================="<<endl;
         int candi = s.front();
         queue<int> origi = s;
         while(!origi.empty()){
            int make = origi.front();
            g.act[make] = 1;
            origi.pop();
         }  
         //cout<<"pop "<<candi<<" here"<<endl;
         int check = 1;
         s.pop();
         for (int neighbor =0; neighbor < g.nxt[candi].size(); neighbor++){
            //cout<<"node "<<g.nxt[candi][neighbor]<<" may have chance be activate "<<endl;
            if((g.nxt_prob[candi][neighbor] < randam()) && (g.act[g.nxt[candi][neighbor]]==0)){
               g.act[g.nxt[candi][neighbor]] = 1;
               //cout<<"node active: "<< g.nxt[candi][neighbor]<<endl;
               s.push(g.nxt[candi][neighbor]);
               counter[g.nxt[candi][neighbor]]++;
               //cout<<"is larger than node "<<g.nxt[candi][neighbor]<<" as probability"<< g.nxt_prob[candi][neighbor]<<endl;
               
               
            }
            
         }
         
      }
   }
   //cout<<"--------------------------------------"<<endl;
   int min_expect = *min_element(counter.begin(), counter.end());
   int num = 0;
   for(const auto& count : counter){
      cout<<count<<" ";
      if(count < min_expect + epsilon){
         num++;
      }
   }
   cout << endl;
   //vector<int> sort_counter = sort_indexes(counter);
   return make_pair(min_expect, num);
}


int main()
{
   srand (20220315);
   cout << "constructing....";
   Graph g;
   cout << "done" <<endl;

   ifstream infile ("networks/graph_ic.inf");
   int u,v;
   double p;
   if (infile.is_open())
   {
      cout << "adding nodes to g2....";
      for (int i = 0; i < 15229; i++){
         g.addNode(i);
      }
      cout <<"done"<<endl;
      while(not infile.eof()){
         infile >> u >> v >> p;
         g.addEdge(u-1,v-1,p);
         //g2.addEdge(u-1,v-1,p);
         // edge[i].prob = ((double) rand() / (RAND_MAX));
      }
      
   }
   infile.close();
   
   // int n = g1.node.size();
   // cout << n << endl;

   // for (int i = 0; i < g.node.size();i++){
   //    cout << g.node[i] << "with size "<< g.nxt[i].size()<<": ";
   //    for (int j =0; j < g.nxt[i].size();j++){
   //       cout << "(" << g.nxt[i][j] << "," << g.nxt_prob[i][j]<<"), ";
   //    }
   //    cout << endl;
   // }

   vector<int> select;
   select.push_back(3);
   select.push_back(2);

   queue<int> selectq;
   selectq.push(3);
   selectq.push(2); 
   select = sort_indexes(select);
   //Model ic;
   pair<int,int> res=icExpq(g,selectq,10000,0.3);
   cout << res.first << " " << res.second << endl;
  return 0;

}