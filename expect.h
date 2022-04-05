#include <algorithm>
#include <chrono>
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
#include"graph.h"

using namespace std;
using namespace std :: chrono;


double randam(){
   double r = (rand()*1.0 / RAND_MAX) ;
   //cout << rand() << endl;
   //cout<<r;
   return r;
};


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
      // cout<<"before mc:"<<endl;
      // for (const auto& count : counter){
      //    cout<< count<<" ";
      // }
      // cout<<endl;    

      queue<int> ss=s;
      while(!ss.empty()){
         //cout<<"=========================================================="<<endl;
         int candi = ss.front();
         
         // "<<candi<<" here"<<endl;
         ss.pop();
         for (int neighbor =0; neighbor < g.nxt[candi].size(); neighbor++){
            //cout<<"node "<<g.nxt[candi][neighbor]<<" may have chance be activate "<<endl;
            if((g.nxt_prob[candi][neighbor] < randam()) && (g.act[g.nxt[candi][neighbor]]==0)){
               g.act[g.nxt[candi][neighbor]] = 1;
               // cout<<"node active: "<< g.nxt[candi][neighbor]<<endl;
               ss.push(g.nxt[candi][neighbor]);
               counter[g.nxt[candi][neighbor]]++;
               //cout<<"is larger than node "<<g.nxt[candi][neighbor]<<" as probability"<< g.nxt_prob[candi][neighbor]<<endl;

               
            }
            
         }
         
      }
   }
   //cout<<"--------------------------------------"<<endl;
   int min_expect = *min_element(counter+0, counter+g.numVert);
   //cout << "min expected is "<<min_expect<<" in set" <<endl;
   int num = 0;
   //cout<<"after mc:"<<endl;
   for(const auto& count : counter){
      // cout<<count<<" ";
      if(count <= min_expect + epsilon){
         //cout<< count <<" ";
         num++;
      }
   }
   // cout << endl;
   //vector<int> sort_counter = sort_indexes(counter);
   double min = min_expect*1.0/mc;
   //cout<<"min: "<<min<<endl;
   return make_pair(min, num);
}