
#include "log.h"

using namespace std;
using namespace std :: chrono;



// inPut in ={in.BUDGET =BUDGET,in.MCROUNDS= 100, in.EPSILON = 0.0001, in.SAMPLE_SIZE =13, in.SAMPLE_ROUND = 100};


int main(int argc, char *argv[])
{
   string method = argv[1];
   int BUDGET = atoi(argv[2]);
   int MCROUNDS = atoi(argv[3]);
   double EPSILON = atof(argv[4]);
   string dataset =argv[5];


   inPut in ={in.BUDGET =BUDGET,in.MCROUNDS= MCROUNDS, in.EPSILON = EPSILON};
   cout<<BUDGET<<" "<<MCROUNDS<<" " <<EPSILON <<" "<< dataset<<" " <<method<<endl;

   
   Graph og = buildGraph(dataset);

   /* */
   // test of abnormal nodes
   Graph g = moveIso(og);
   
   
   /*
   // test of icExp

   queue<int> select;
   select.push(3);
   select.push(2); 
   
   pair<int,int> res=icExp(g,select,100,0);
   */

   /* */
   // test of greedy
   if(method.compare("greedy")==0){
      values res = greedy(g, in.BUDGET, in.MCROUNDS, in.EPSILON);
      logRec(g,res, in, method);
   }

   
   


   // test of RR

   // if(method.compare("RR")==0){
   //    valuesRR res = rrSelect(g ,SAMPLE_SIZE, SAMPLE_ROUND, BUDGET);

   //    queue<int> rr_select;
   //    vector<double> inf;
   //    for(const auto&i:res.seed){
   //       rr_select.push(i);
   //       cout <<"now we are adding node:" << i <<endl;
   //       pair<double,int> influence = icExp(g, rr_select, MCROUNDS, EPSILON);
   //       inf.push_back(influence.first);
   //    }

   //    logRec(g, res, in, method);
   // }

   
   

   // for (const auto&i:res.seed){

   //    rr_select.push(i);
   //    cout <<"now we are adding node:" << i <<endl;
   //    pair<double,int> influence = icExp(g, rr_select, MCROUNDS, EPSILON);
   //    inf.push_back(influence.first);
   // }   
   

   /*   
   ofstream outfile ("log/log_RR.txt",ios::app);
   auto timenow = chrono::system_clock::to_time_t(chrono::system_clock::now());
   if(outfile.is_open()){
      outfile <<"======================================================================"<<endl;
      outfile<< ctime(&timenow);
      outfile<<"Graph with "<<g.numVert<<" nodes, "<< g.numEdge<<" edges."<<endl;
      outfile<<"Algorithm: initial RR | Budget: "<< BUDGET<<endl;
      outfile<< "MC rounds = "<<MCROUNDS<<"| Possibility of influence = normal | Epsilon = "<< EPSILON <<endl;

      outfile<<"Selecting nodes: "<<endl;
      // for (set<int, greater<double> >::iterator i = res.first.begin();i != res.first.end();i++){
      //    outfile<<*i<<" ";
      // }
      for (const auto&i:res.sed){
         outfile<<i<<" ";
      }
      outfile<<endl;

      outfile<<"The maxmin influence:"<<endl;
      for (const auto&i:inf){
         outfile<<i<<" ";
      }
      outfile<<endl;

      outfile<<"The time spend:"<<endl;
      for (const auto&i:res.time){
         outfile<<i<<", ";
      }
      outfile<<endl;
   }

   outfile.close();   
 */
   


   /*
   // test of sort_indexes
   vector<int> counter;
   counter.push_back(3);
   counter.push_back(2); 
   vector<int> after_s = sort_indexes(counter);
   */




   /* 
   // test of dual binary-search
   double local_threshold = EPSILON;

   values res = greedy(g, BUDGET, MCROUNDS, local_threshold);
   double max = 0;
   cout<<"The maxmin influence:"<<endl;
   for (const auto&i:res.inf){
      if(max<i){
         max = i;
      }
   }
   cout<<"what is max one"<<max<<endl;

   while( (max < local_threshold*0.95) || (max > local_threshold*1.05 ) ){

      local_threshold = (max + local_threshold)/2;

      values res = greedy(g, BUDGET, MCROUNDS, local_threshold);
      cout<<"The maxmin influence:"<<endl;
      for (const auto&i:res.inf){
         if(max<i){
            max = i;
         }
      }
      cout<<"what is max one"<<max<<endl;

   }
   

   
   ofstream outfile ("log/log_dualbin.txt",ios::app);
   auto timenow = chrono::system_clock::to_time_t(chrono::system_clock::now());
   if(outfile.is_open()){
      outfile <<"======================================================================"<<endl;
      outfile<< ctime(&timenow);
      outfile<<"Graph with "<<g.numVert<<" nodes, "<< g.numEdge<<" edges."<<endl;
      outfile<<"Algorithm: initial greedy | Budget: "<< BUDGET<<endl;
      outfile<< "MC rounds = "<<MCROUNDS<<"| Possibility of influence = normal | Epsilon = "<< EPSILON <<endl;

      outfile<<"Selecting nodes: "<<endl;
      // for (set<int, greater<double> >::iterator i = res.first.begin();i != res.first.end();i++){
      //    outfile<<*i<<" ";
      // }
      for (const auto&i:res.sed){
         outfile<<i<<" ";
      }
      outfile<<endl;

      outfile<<"The maxmin influence:"<<endl;
      for (const auto&i:res.inf){
         outfile<<i<<" ";
      }
      outfile<<endl;

      outfile<<"The time spend:"<<endl;
      for (const auto&i:res.time){
         outfile<<i<<" ";
      }
      outfile<<endl;
   }

   outfile.close();
   */
   

return 0;

}