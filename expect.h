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
   // vector<int> counter(g.numVert);
   // cout<<"Counter==="<<counter.size()<<endl;
   queue<int> origi;
   queue<int> ss;
   for(int i = 0; i<mc; i++){
      for (int i =0; i < g.numVert;i++){
         g.act[i]=0;
      }
      origi = s;
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

      ss=s;
      while(!ss.empty()){
         //cout<<"=========================================================="<<endl;
         int candi = ss.front(); 
         
         // "<<candi<<" here"<<endl;
         ss.pop();
         for (long unsigned int neighbor =0; neighbor < g.nxt[candi].size(); neighbor++){
            //cout<<"node "<<g.nxt[candi][neighbor]<<" may have chance be activate "<<endl;
            if((g.nxt_prob[candi][neighbor] > randam()) && (g.act[g.nxt[candi][neighbor]]==0)){
            // if((g.nxt_prob[candi][neighbor] > randx()) && (g.act[g.nxt[candi][neighbor]]==0)){
               g.act[g.nxt[candi][neighbor]] = 1;
               // cout<<"node active: "<< g.nxt[candi][neighbor]<<endl;
               ss.push(g.nxt[candi][neighbor]);
               counter[g.nxt[candi][neighbor]]++;
               //cout<<"is larger than node "<<g.nxt[candi][neighbor]<<" as probability"<< g.nxt_prob[candi][neighbor]<<endl;

               
            }
            
         }
         
      }
   }
   // cout<<"-------------Counter here-------------------------"<<endl;
   // for(int i =0;i<g.numVert;i++){
   //    cout<<counter[i]<<" ";
   // }
   // cout<<endl;
   // cout<<"-------------Counter end-------------------------"<<endl;
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


float* icExp_lazy(Graph g, queue<int> s,int mc){ //, double alpha

   srand (time(NULL));
   float *counter = (float*)malloc(sizeof(float)*g.numVert);
   // srand (time(NULL));

   for (int i =0;i<g.numVert;i++){
      counter[i]=0;
   }
   // vector<int> counter(g.numVert);
   // cout<<"Counter==="<<counter.size()<<endl;

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
         for (long unsigned int neighbor =0; neighbor < g.nxt[candi].size(); neighbor++){
            //cout<<"node "<<g.nxt[candi][neighbor]<<" may have chance be activate "<<endl;
            double rn = randam();
            if((g.nxt_prob[candi][neighbor] > rn) && (g.act[g.nxt[candi][neighbor]]==0)){
            // if((g.nxt_prob[candi][neighbor] > randx()) && (g.act[g.nxt[candi][neighbor]]==0)){
               // printf("random number: %f", rn);
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
   // int min_expect = *min_element(counter+0, counter+g.numVert);
   //cout << "min expected is "<<min_expect<<" in set" <<endl;
   // int num = 0;
   //cout<<"after mc:"<<endl;
   /*
   for(const auto& count : counter){
      const auto& count = count/mc;
      // cout<<count<<" ";

   }
   */
   // cout<<"counter in this mc process, with "<< sizeof(counter)<<" nodes: " <<endl;
   // for (int i =0;i<g.numVert;i++){
   //    // counter[i]= std::min<float>(counter[i]/mc, alpha);
   //    cout<<counter[i]<<" ";
   // }
   // cout << endl;
   // free(counter);
   return counter;
}

float* icExp_hyper(InfGraph g, queue<int> s, int mc){
   
   float *counter = (float*)malloc(sizeof(float)*g.numVert);

   for (int i =0;i<g.numVert;i++){
      counter[i]=0;
   }
   
   while(!s.empty()){
      int node = s.front();
      for(long unsigned int line=0;line<g.hyperGT.size();line++){
         counter[node]++;
         if (std::find(g.hyperGT[line].begin(), g.hyperGT[line].end(),node)!=g.hyperGT[line].end()){
           
            for(long unsigned int j=0;j<g.hyperGT[line].size();j++){
               counter[g.hyperGT[line][j]]++;
               
            }
            counter[node]--;

         }

      }
      s.pop();
   }
   // for(int i=0;i<g.numVert;i++){
   //    cout<<counter[i]<<" ";
   // }
   // cout<<endl;
   return counter;
}

float* icExp_hyperG(InfGraph g, queue<int> s, int mc){
   /*
   which recalculating counter, use node mark to set seedset selection. same intuition with TIm's hypergraph
   */
   // printf(" new term to occur this hyper function\n");
   
   float *counter = (float*)malloc(sizeof(float)*g.numVert);
   bool *nodeMark = (bool*)malloc(sizeof(bool)*g.numVert);


   for (int i =0;i<g.numVert;i++){
      counter[i]=0;
      nodeMark[i]=true;
   }
   // printf("original num is: ");
   // // int n = sizeof(counter) / sizeof(counter[0]);
   // // sort(counter, counter + g.numVert);
   // for(int i=0;i<g.numVert;i++){
   //    printf("%d[%f][%d] ",i,counter[i],nodeMark[i]);
   // }
   // cout<<endl;
   
   // for(int line=0;line<g.hyperGT.size();line++){
   //    printf("%d hypergraph: ",line);
   //    for(int j=0;j<g.hyperGT[line].size();j++){
   //       cout <<g.hyperGT[line][j]<< " ";

   //    }
   // }
   // cout<<endl;
   // printf("=======================================\n");
   // for(int line=0;line<g.hyperGT.size();line++){

   // }
   while(!s.empty()){
      int node = s.front();
      // printf("------------------------------------------\n");
      // printf("%d is the seed we are finding this time.\n",node);
      
      for(long unsigned int line=0;line<g.hyperGT.size();line++){
         
         counter[node]++;
         nodeMark[node]= false;
         if (std::find(g.hyperGT[line].begin(), g.hyperGT[line].end(),node)!=g.hyperGT[line].end()){
            // target node is find in certain hyper graph, update every number in counter.
            for(long unsigned int j=0;j<g.hyperGT[line].size();j++){
               // printf("checking, node [%d]\n",g.hyperGT[line][j]);
               if(nodeMark[g.hyperGT[line][j]]){
                  // if this node has been actived do not recalculate it's influence
                  // printf("we are true here, node [%d] is alredy in set\n",g.hyperGT[line][j]);
                  counter[g.hyperGT[line][j]]++;
               }
            }
         }
      }
      s.pop();

   }

   // printf("here is the counter itself: ");
   // // int n = sizeof(counter) / sizeof(counter[0]);
   // // // sort(counter, counter + g.numVert);
   // for(int i=0;i<g.numVert;i++){
   //    printf("%d[%f] ",i,counter[i]);
   // }
   // cout<<endl;

   return counter;
}
