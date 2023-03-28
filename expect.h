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
#include<omp.h>

using namespace std;
using namespace std :: chrono;


double randam(){
   double r = (rand()*1.0 / RAND_MAX) ;
   //cout << rand() << endl;
   //cout<<r;
   return r;
};



summary icExp(Graph g, queue<int> s,int mc,double epsilon){
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
   int sum_inf = std::accumulate(counter+0, counter+g.numVert,0);
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
   // double min = min_expect*1.0/mc;
   //cout<<"min: "<<min<<endl;
   summary res ={num, min_expect, sum_inf};
   return res;
}

summary ltExpg(Graph g, queue<int> s,int mc,double epsilon){

   int *counter = (int*)malloc(sizeof(int)*g.numVert);
   // srand (time(NULL));

   for (int i =0;i<g.numVert;i++){
      counter[i]=0;
   }
   
   for(int i = 0; i<mc; i++){
      for (int i =0; i < g.numVert;i++){
         g.act[i]=0;
      }
      queue<int> origi = s;

      // cout<<"before mc:";
      while(!origi.empty()){
            int make = origi.front();
            g.act[make] = 1;
            counter[make]++;
            // printf("%d[%d] ", make,counter[make]);
            origi.pop();
      }        
      // cout<<endl;
      // printf("does node 499 been activate: %d", g.act[499]);
      queue<int> ss=s;
      // double sum;
      while(!ss.empty()){
         //cout<<"=========================================================="<<endl;
         int candi = ss.front(); 
         
         // cout<<"pop node"<<candi<<" here"<<endl;
         ss.pop();
         double rn = randam();
         if(g.pre[candi].size() == 0 )
            continue;
         for (long unsigned int neighbor =0; neighbor < g.pre[candi].size(); neighbor++){
            //cout<<"node "<<g.nxt[candi][neighbor]<<" may have chance be activate "<<endl;
            // sum += g.pre_prob[candi][neighbor];
            rn -= g.pre_prob[candi][neighbor];
            if((rn<=0) && (g.act[g.pre[candi][neighbor]]==0)){
            // if((g.nxt_prob[candi][neighbor] > randx()) && (g.act[g.nxt[candi][neighbor]]==0)){
               // printf("random number: %f", rn);
               // printf("rn as: %f\n", rn);
               g.act[g.pre[candi][neighbor]] = 1;
               // cout<<"node active: "<< g.nxt[candi][neighbor]<<endl;
               ss.push(g.pre[candi][neighbor]);
               counter[g.pre[candi][neighbor]]++;
               break;
               //cout<<"is larger than node "<<g.nxt[candi][neighbor]<<" as probability"<< g.nxt_prob[candi][neighbor]<<endl;

               
            }
            
         }
         
      }
   }

   int min_expect = *min_element(counter+0, counter+g.numVert);
   int sum_inf = std::accumulate(counter+0, counter+g.numVert,0);

   int num=0;

   for(int count = 0; count<g.numVert;count++){
      if(counter[count] <=min_expect+epsilon){
         num++;
      }
   }
   free(counter);
   // printf("counter this time:");
   // for (int i =0;i<g.numVert;i++){
   //    printf("%d[%d]",i,counter[i]);
   // }
   // cout<<endl;

   double min = min_expect*1.0/mc;
   summary res = {num, min_expect, sum_inf};
   return res;
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

int* icExp_lazyI(Graph g, queue<int> s,int mc){ //, double alpha

   srand (time(NULL));
   int *counter = (int*)malloc(sizeof(int)*g.numVert);
   // srand (time(NULL));

   for (int i =0;i<g.numVert;i++){
      counter[i]=0;
   }
   // vector<int> counter(g.numVert);
   // cout<<"Counter==="<<counter.size()<<endl;
   // #pragma omp parallel for reduction(m10x1Add: S)
   for(int i = 0; i<mc; i++){
      for (int i =0; i < g.numVert;i++){
         g.act[i]=0;
      }
      queue<int> origi = s;

      // cout<<"before mc:"<<endl;
      while(!origi.empty()){
            int make = origi.front();
            g.act[make] = 1;
            counter[make]++;
            // printf("%d[%d] ", make,counter[make]);
            origi.pop();
      }       
      // cout<<"before mc:"<<endl;
      // for (int count =0; count<g.numVert;count++){
      //    // cout<< <<counter[count]<<" ";
      //    printf("%d[%d] ", count,counter[count]);
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

int* ltExp(Graph g, queue<int> s,int mc){ //, double alpha

   srand (time(NULL));
   int *counter = (int*)malloc(sizeof(int)*g.numVert);
   // srand (time(NULL));

   for (int i =0;i<g.numVert;i++){
      counter[i]=0;
   }
   
   for(int i = 0; i<mc; i++){
      for (int i =0; i < g.numVert;i++){
         g.act[i]=0;
      }
      queue<int> origi = s;

      // cout<<"before mc:";
      while(!origi.empty()){
            int make = origi.front();
            g.act[make] = 1;
            counter[make]++;
            // printf("%d[%d] ", make,counter[make]);
            origi.pop();
      }        
      // cout<<endl;
      // printf("does node 499 been activate: %d", g.act[499]);
      queue<int> ss=s;
      // double sum;
      while(!ss.empty()){
         //cout<<"=========================================================="<<endl;
         int candi = ss.front(); 
         
         // cout<<"pop node"<<candi<<" here"<<endl;
         ss.pop();
         double rn = randam();
         if(g.pre[candi].size() == 0 )
            continue;
         for (long unsigned int neighbor =0; neighbor < g.pre[candi].size(); neighbor++){
            //cout<<"node "<<g.nxt[candi][neighbor]<<" may have chance be activate "<<endl;
            // sum += g.pre_prob[candi][neighbor];
            rn -= g.pre_prob[candi][neighbor];
            if((rn<=0) && (g.act[g.pre[candi][neighbor]]==0)){
            // if((g.nxt_prob[candi][neighbor] > randx()) && (g.act[g.nxt[candi][neighbor]]==0)){
               // printf("random number: %f", rn);
               // printf("rn as: %f\n", rn);
               g.act[g.pre[candi][neighbor]] = 1;
               // cout<<"node active: "<< g.nxt[candi][neighbor]<<endl;
               ss.push(g.pre[candi][neighbor]);
               counter[g.pre[candi][neighbor]]++;
               break;
               //cout<<"is larger than node "<<g.nxt[candi][neighbor]<<" as probability"<< g.nxt_prob[candi][neighbor]<<endl;

               
            }
            
         }
         
      }
   }
   // printf("counter this time:");
   // for (int i =0;i<g.numVert;i++){
   //    printf("%d[%d]",i,counter[i]);
   // }
   // cout<<endl;
   return counter;
}


/*
// for paralla program
int* icExp_lazycon(Graph g, queue<int> s,int mc){ //, double alpha

   srand (time(NULL));
   int *counter = (int*)malloc(sizeof(int)*g.numVert);
   // srand (time(NULL));

   for (int i =0;i<g.numVert;i++){
      counter[i]=0;
   }
   // vector<int> counter(g.numVert);
   // cout<<"Counter==="<<counter.size()<<endl;
   int myArray[g.numVert] = {};
   #pragma omp parallel for firstprivate(mc,g,s) num_threads(10) reduction(+:myArray) schedule(dynamic,50) default(none)
      //#pragma omp for 
      for(int i = 0; i<mc; i++){
         // for (int j =0; j < g.numVert;j++){
         //    g.act[j]=0;
         // }

         bool *S = (bool*)malloc(sizeof(bool)*g.numVert);
         queue<int> origi = s;
         // cout<<"before mc:"<<endl;
         while(!origi.empty()){
               int make = origi.front();
               S[make] = true;
               myArray[make]++;
               // printf("%d[%d] ", make,counter[make]);
               origi.pop();
         }      
         // cout<<"before mc:"<<endl;
         // for (int count =0; count<g.numVert;count++){
         //    // cout<< <<counter[count]<<" ";
         //    printf("%d[%d] ", count,counter[count]);
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
               if((g.nxt_prob[candi][neighbor] > rn) && (!S[g.nxt[candi][neighbor]])){
               // if((g.nxt_prob[candi][neighbor] > randx()) && (g.act[g.nxt[candi][neighbor]]==0)){
                  // printf("random number: %f", rn);
                  S[g.nxt[candi][neighbor]] = true;
                  // cout<<"node active: "<< g.nxt[candi][neighbor]<<endl;
                  ss.push(g.nxt[candi][neighbor]);
                  myArray[g.nxt[candi][neighbor]]++;
                  //cout<<"is larger than node "<<g.nxt[candi][neighbor]<<" as probability"<< g.nxt_prob[candi][neighbor]<<endl;

                  
               }
               
            }
            
         }
      }
   
   int max = 0;
   for (int i=0;i<g.numVert;i++){
      counter[i] = myArray[i];
      if (max<myArray[i])
         max = myArray[i];
   }
   // cout<<"max counter of seed:"<<max<<endl;
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
   //return counter;
//}




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
