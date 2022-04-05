#include "expect.h"

using namespace std;
using namespace std :: chrono;




values greedy(Graph g, int k, int mc, double epsilon){
   clock_t start_t, end_t;
   double duration;
   start_t = clock();
   // std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
   set<int> S, G;
   int sets [k];
   vector<double> maxinf, tim;
   for(int i=0; i<g.numVert;i++){
      G.insert(i);
   }
   cout<<endl;
   int node = -1;
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
      
      
      for (j = G.begin(); j != G.end(); j++) {
         queue<int> s=QueueS;
         s.push(*j);
         //cout<<"search max with node:"<<*j<<endl;
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
      end_t = clock();
      duration = (double)(end_t - start_t)/ CLOCKS_PER_SEC;

      maxinf.push_back(max_);
      tim.push_back(duration);
      //cout<<"maxx: "<<max_<<endl;
      G.erase(node);
      S.insert(node);
      sets[_] = node;
      
      //cout<<"slecting "<<node<< " with time: "<< duration<<endl;
      

   }
   // std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
   // if(outfile.is_open()){
      
   //    outfile << "Time spend: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
   //    outfile<<"Sorted selecting nodes: "<<endl;
   //    for(const auto& _ : sets){
   //       outfile<<_<<" ";
   //    }
   //    outfile<<endl;
     
   // }
   
   values res ={S,maxinf,tim};
   // res.sed = ;
   // res.inf = maxinf;
   // res.time = times;
   return res;
   //return make_pair(S,maxinf);
}



vector<int> RR(Graph g, int SAMPLE_SIZE){
   //cout<<"function RR ..."<<endl;
   vector<int> S;
   // S.push_back(vector<int>(0));
   queue<int> Q;
   double rand = g.numVert * randam();   
   int seed  = (int)rand;
   // cout<<"seed "<<seed<<" as the initial seed we selected."<<endl;
   Q.push(seed);
   S.push_back(seed);

   while((!Q.empty()) && S.size() < SAMPLE_SIZE){ //

      int u = Q.front();
      Q.pop();
      // cout<< u<<" been pop"<<endl;
      for(int w = 0; w < g.pre[u].size(); w++){

         if((g.pre_prob[u][w] <randam()) && (g.act[g.pre[u][w]]==0)){

            // cout<<"node "<< g.pre[u][w] <<" been activated"<<endl;
            g.act[g.pre[u][w]] = 1;
            Q.push(g.pre[u][w]);
            S.push_back(g.pre[u][w]);
         }

      }
      
   }

   return S;
}

vector<int> RRs(Graph g, int SAMPLE_SIZE, int SAMPLE_ROUND){
   vector<int> S;
   for(int i = 0; i < SAMPLE_ROUND; i++){
      vector<int> rr = RR(g ,SAMPLE_SIZE);
      for(const auto& i : rr){
         S.push_back(i);
      }
   }
   return S;
}



valuesRR rrSelect(Graph g, int SAMPLE_SIZE, int SAMPLE_ROUND, int k){

   clock_t start_t, end_t;
   double duration;
   start_t = clock();
   vector<double> tim;
   set<int> S;
   vector<int> Q;

   for(int i; i<k; i++){
      set<int> seed;
      int counter [g.numVert];
      int V [g.numVert];
      for (int i =0;i<g.numVert;i++){
         counter[i]=0;
         V[i] = i;
      }
      vector<int> rr = RRs(g ,SAMPLE_SIZE, SAMPLE_ROUND);
      for(const auto&_:rr){
         seed.insert(_);
      }
      for(const auto& i : rr){
         for(const auto& j : seed){
            if(i==j){
               counter[i]++;
            }
         }
      }
      // sorted by max -> min
      sort( V,V+g.numVert, [&](int i,int j){return counter[j]>counter[i];} );
      queue<int> candidate;
      // cout<< "after sorted"<<endl;
      for(const auto&_:V){
         // cout<<_<<" ";
         candidate.push(_);
      }
      // cout<<endl;  
      //int node = V[0];


      while((!candidate.empty()) ){
         int node = candidate.front();
         const bool is_in = S.find(node) != S.end();
         
         if(!is_in){
            S.insert(node);
            Q.push_back(node);
            // cout<<"has add node"<<node<<endl;
            
            break;

         }
         candidate.pop();
      }
      end_t = clock();
      duration = (double)(end_t - start_t); /// CLOCKS_PER_SEC;
      tim.push_back(duration);
   
   }

   valuesRR res ={S,Q,tim};
   return res;

}

