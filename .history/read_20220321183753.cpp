#include <algorithm>
#include <iostream>
#include <iomanip>
#include <iterator>
#include <fstream>
#include <numeric>
#include <set>
#include <string>
#include <sstream>
#include <queue>
#include <typeinfo>
#include <utility> 
#include <vector>
 

using namespace std;

int SAMPLE_SIZE = 50;

double randam(){
   double r = (rand()*1.0 / RAND_MAX) ;
   //cout << rand() << endl;
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

void ic(Graph g, vector<int> s,int mc,double epsilon){
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
               // cout<<"is larger than"<<"node "<<g.nxt[candi][neighbor]<<" as probability"<< g.nxt_prob[candi][neighbor]<<endl;
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

pair<double,int> icExp(Graph g, queue<int> s,int mc,double epsilon){
   int counter [g.numVert];
   for (int i =0;i<g.numVert;i++){
      counter[i]=0;
   }
   epsilon = epsilon*mc;
   //vector<int> counter(g.numVert);
   //cout<<"Counter==="<<counter.size()<<endl;

   for(int i = 0; i<mc; i++){
      for (int i =0; i < g.numVert;i++){
         g.act[i]=0;
      }
      queue<int> origi = s;
      while(!origi.empty()){
            int make = origi.front();
            g.act[make] = 1;
            counter[make]++;
            origi.pop();
      }       
      cout<<"before mc:"<<endl;
      for (const auto& count : counter){
         cout<< count<<" ";
      }
      cout<<endl;    

      queue<int> ss=s;
      while(!ss.empty()){
         //cout<<"=========================================================="<<endl;
         int candi = ss.front();
         
         //cout<<"pop "<<candi<<" here"<<endl;
         ss.pop();
         for (int neighbor =0; neighbor < g.nxt[candi].size(); neighbor++){
            cout<<"node "<<g.nxt[candi][neighbor]<<" may have chance be activate "<<endl;
            if((g.nxt_prob[candi][neighbor] < randam()) && (g.act[g.nxt[candi][neighbor]]==0)){
               g.act[g.nxt[candi][neighbor]] = 1;
               //cout<<"node active: "<< g.nxt[candi][neighbor]<<endl;
               ss.push(g.nxt[candi][neighbor]);
               counter[g.nxt[candi][neighbor]]++;
               //cout<<"is larger than node "<<g.nxt[candi][neighbor]<<" as probability"<< g.nxt_prob[candi][neighbor]<<endl;

               
            }
            
         }
         
      }
   }
   //cout<<"--------------------------------------"<<endl;
   int min_expect = *min_element(counter+0, counter+g.numVert);
   cout << "min expected is "<<min_expect<<" in set" <<endl;
   int num = 0;
   cout<<"after mc:"<<endl;
   for(const auto& count : counter){
      // cout<<count<<" ";
      if(count <= min_expect + epsilon){
         cout<< count <<" ";
         num++;
      }
   }
   // cout << endl;
   //vector<int> sort_counter = sort_indexes(counter);
   
   cout<<min_expect<<endl;
   return make_pair(min_expect/mc, num);
}

pair<set<int>,vector<double>> greedy(Graph g, int k, int mc, double epsilon){
   cout<<"Active greedy function"<<endl;
   set<int> S, G;
   vector<double> maxinf;
   for(int i; i<g.numVert;i++){
      //cout<<i<<endl;
      G.insert(i);
   }

   for(int _ =0; _<k;_++){
      double max_ = 0;
      int min_ = 0x3f3f3f;
      set<int, greater<int> >::iterator i;
      set<int, greater<int> >::iterator j;
      queue<int> QueueS;
      for (i = S.begin(); i != S.end(); i++){
         // G.erase(*i);
         
         QueueS.push(*i);
      }
      
      int node = -1;
      for (j = G.begin(); j != G.end(); j++) {
         queue<int> s=QueueS;
         s.push(*j);
         cout<<"search max with node:"<<*j<<endl;
         pair<double,int> res = icExp(g, s, mc, epsilon);
         double exp_j=res.first;
         int set_j=res.second;
      

         if(exp_j >max_){
            max_ =exp_j;
         }
         if(exp_j == max_){
            if(set_j<=min_){
               node = *j;
               min_ = set_j;
            }
         }
         
      }
      maxinf.push_back(max_);
      G.erase(node);
      S.insert(node);
      cout<<"S insert: "<<node<<endl;


   }
   return make_pair(S,maxinf);



}

void RR(Graph g, int SAMPLE_SIZE, int threshold, int budget){
   set<int> S, G, rS;
   vector<int> sG;
   
   vector<double> maxinf;
   queue<int> Q;
   for(int i; i<g.numVert;i++){
      G.insert(i);
      vector<int> rr_list;
      int sample_number = 1;
      if((randam() < 0.5) && sample_number < SAMPLE_SIZE){
         sG.push_back(i);
         Q.push(i);
         g.act[i] = 1;
      }
       
   }
   while(!Q.empty()){
      int u = Q.front();
      Q.pop();
      for(int w = 0; w < g.pre[u].size(); w++){
         if((g.pre_prob[u][w] <randam()) && (g.act[g.pre[u][w]]==0)){
            g.act[g.pre[u][w]] = 1;
            Q.push(g.pre[u][w]);
            sG.push_back(g.pre[u][w]);

         }

      }


   }

}


int main()
{
   srand (time(NULL));
   cout << "constructing....";
   Graph g;
   cout << "done" <<endl;

   //ifstream infile ("networks/graph_ic.inf"); // with node 15229
   //ifstream infile ("networks/data.txt");
   ifstream infile ("networks/zachary");
   int u,v;
   double p;
   if (infile.is_open())
   {
      cout << "adding nodes to....";
      for (int i = 0; i < 34; i++){
         g.addNode(i);
      }
      
      while(not infile.eof()){
         infile >> u >> v >> p;
         g.addEdge(u-1,v-1,p);
         //g2.addEdge(u-1,v-1,p);
         // edge[i].prob = ((double) rand() / (RAND_MAX));
      }
      cout <<"done"<<endl;
      
   }
   infile.close();
   
   // int n = g.node.size();
   // cout << n << endl;

   // for (int i = 0; i < 4/*g.node.size()*/;i++){
   //    for (int j =0; j < g.nxt[i].size();j++){
   //       if ((1-g.nxt_prob[i][j])<0.00001){
   //          cout << "("<<i<<"," << g.nxt[i][j] << "," << g.nxt_prob[i][j]<<")"<<endl;
   //       }
   //    }
   // }
   
   /*
   // test of icExp

   queue<int> select;
   select.push(3);
   select.push(2); 

   select = sort_indexes(select);
   Model ic;
   pair<int,int> res=icExp(g,select,100,0);
   */

   /* */
   // test of greedy
   pair<set<int>,vector<double>> res = greedy(g, 33,100,0.05);
   cout<<"Selecting nodes: "<<endl;
   for (set<int, greater<int> >::iterator i =res.first.begin();i != res.first.end();i++){
      cout<<*i<<" ";
   }
   cout<<endl;
   cout<<"The maxmin influence:"<<endl;
   for (int i =0;i<res.second.size();i++){
      cout<<res.second[i]<<" ";
   }
   cout<<endl;
   

  return 0;

}