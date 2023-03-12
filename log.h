#include <chrono>
#include <iostream>
#include"strategies.h"
#include <fstream>

using namespace std;
using namespace std :: chrono;


void logRec(Graph g, values res, inPut in, string method, string calcu){
// void logRec(Graph g, values res, inPut in, string method){
   ofstream outfile ("log/log_"+method+".txt",ios::app);
   auto timenow = chrono::system_clock::to_time_t(chrono::system_clock::now());
   string distribution;
   if(in.dataset == "zachary_01"){
      distribution = "0.1";
   }else{
      distribution = "normal";
   }

   if(outfile.is_open()){
      outfile <<"======================================================================"<<endl;
      outfile<< ctime(&timenow);
      outfile<<"Dataset: "<<in.dataset<<endl;
      outfile<<"Graph with "<<g.numVert<<" nodes, "<< g.numEdge<<" edges."<<endl;
      outfile<<"Algorithm: initial "<<method<<" | Budget: "<< in.BUDGET<<endl;
      outfile<< "MC rounds = "<<in.MCROUNDS<<"| Possibility of influence = "<<distribution <<" | Epsilon = "<< in.EPSILON <<endl;
      if(method.compare("RR")==0){
          outfile<<""<<in.SAMPLE_ROUND<<endl;
      }

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

   char sp = 'spa';
   int step = 20;
   // char tw = 'twitter';
   // char fb = 'facebook';
   // char bitcoin = 'bitcoin';

   string logfile = "log/"+in.CAL+"/"+to_string(in.EPSILON)+"/";
   cout<<"output file: "<< logfile<<endl;
   std::ofstream myfile;
   if((method.compare("lgRR")==0) || (method.compare("lsRR")==0)){
      myfile.open (logfile+in.MODEL+"_"+in.dataset+"_"+method+"_"+to_string(step)+".csv");      
   }
   else{
      myfile.open (logfile+in.MODEL+"_"+in.dataset+"_"+method+".csv");
   }
   myfile << "k;seed;inf;tim\n";
   if ((in.dataset.find(sp) != string::npos ))
   {
   //   cout<<"Yes, string contains the character - "<< endl;
   for(int i = 0;i<in.BUDGET;i++){
      if(i%10==0){
         myfile << to_string(i)+";"+to_string(res.sed[i])+";"+to_string(res.inf[i])+";"+to_string(res.time[i])+"\n";
      }
      
   } 
   
   }
   else
   {
      for(int i = 0;i<in.BUDGET;i++){
         if(i%10==0){
            myfile << to_string(i)+";"+to_string(res.sed[i])+";"+to_string(res.inf[i])+";"+to_string(res.time[i])+"\n";
         }
         
      } 
   }
   myfile.close();
}
   
