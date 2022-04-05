#include <chrono>
#include <iostream>
#include"strategies.h"

using namespace std;
using namespace std :: chrono;

void logRec(Graph g, values res, inPut in, string method){
   ofstream outfile ("log/log_"+method+".txt",ios::app);
   auto timenow = chrono::system_clock::to_time_t(chrono::system_clock::now());
   if(outfile.is_open()){
      outfile <<"======================================================================"<<endl;
      outfile<< ctime(&timenow);
      outfile<<"Graph with "<<g.numVert<<" nodes, "<< g.numEdge<<" edges."<<endl;
      outfile<<"Algorithm: initial "<<method<<" | Budget: "<< in.BUDGET<<endl;
      outfile<< "MC rounds = "<<in.MCROUNDS<<"| Possibility of influence = normal | Epsilon = "<< in.EPSILON <<endl;

      outfile<<"Selecting nodes: "<<endl;
      // for (set<int, greater<double> >::iterator i = res.first.begin();i != res.first.end();i++){
      //    outfile<<*i<<" ";
      // }
      for (const auto&i:res.sed){
         outfile<<i<<", ";
      }
      outfile<<endl;

      outfile<<"The maxmin influence:"<<endl;
      for (const auto&i:res.inf){
         outfile<<i<<", ";
      }
      outfile<<endl;

      outfile<<"The time spend:"<<endl;
      for (const auto&i:res.time){
         outfile<<i<<", ";
      }
      outfile<<endl;
   }

   outfile.close();
}
   
