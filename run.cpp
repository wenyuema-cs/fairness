
#include "log.h"
using namespace std;
using namespace std :: chrono;



// inPut in ={in.BUDGET =BUDGET,in.MCROUNDS= 100, in.EPSILON = 0.0001, in.SAMPLE_SIZE =13, in.SAMPLE_ROUND = 100};

/*
input parameters of argv ./read 
----------
test_method: string
    RR, greedy
mcrounds_num: int 
   number, usually set as 1000
epsilon_selection: float 
   number 0.1
dataset: string
   ba_tp, ba_ep, vk_rp, vk_tp, zachary, zachary_01 
sample_round: int 
   sample round in IM calculation

*/


int main(int argc, char *argv[])
{
   string method ;
   method = argv[1];
   int BUDGET = atoi(argv[2]);
   int MCROUNDS = atoi(argv[3]);
   double EPSILON = atof(argv[4]);
   string dataset =argv[5];
   int SAMPLE_ROUND = atoi(argv[6]);
   double ALPHA = atof(argv[7]);
   int TEST = atoi(argv[8]);
   string model = argv[9];
   string calcu = argv[10];
   int step = 20 ;

   //inPut in ={in.BUDGET =BUDGET,in.MCROUNDS= MCROUNDS, in.EPSILON = EPSILON,in.dataset = dataset, in.SAMPLE_ROUND= SAMPLE_ROUND};
   inPut in ={.BUDGET =BUDGET,.MCROUNDS= MCROUNDS, .EPSILON = EPSILON,.dataset = dataset, .SAMPLE_ROUND= SAMPLE_ROUND, .ALPHA = ALPHA, .TEST =TEST, .MODEL = model, .CAL = calcu};
   cout<<"Method: "<<method<<" Objective: "<< calcu<<endl;
   cout<<"Budget: "<<BUDGET<<" "<<MCROUNDS<<" " <<EPSILON <<" "<< dataset<<" "  <<SAMPLE_ROUND<<" " <<endl;
   cout<<"influence model: "<< model<<endl;
   cout<<"internal step: "<<to_string(step)<<endl;
   
   InfGraph g = buildGraph(dataset);

   vector <double> influence(BUDGET);
   vector <double> time(BUDGET);
   values res;


   for(int test = 1;test<=TEST;test++){
      /* */
      // test of abnormal nodes
      // Graph g = moveIso(og);
      
      
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
         res = greedy(g, in.BUDGET, in.MCROUNDS, in.EPSILON,in.MODEL,in.CAL);
         // res = greedy_hyper(g,  in.BUDGET, in.MCROUNDS, in.EPSILON);

         // logRec(g,res, in, method);
      }

      // test of RR
      if(method.compare("RR")==0){
         res = rrSelect(g , BUDGET,MCROUNDS, EPSILON);
         // res = rbfsSelect(g , BUDGET,MCROUNDS, EPSILON);
         
      }

      if(method.compare("sRR")==0){
         res = rSelect(g, BUDGET,MCROUNDS, EPSILON, in.MODEL,in.CAL);
      }
      if(method.compare("pRR")==0){
         res = rpSelect(g, BUDGET,MCROUNDS, EPSILON);
      }
      if(method.compare("tRR")==0){
         res = rtieSelect(g, BUDGET, MCROUNDS, EPSILON, in.MODEL,in.CAL);
      }

      if(method.compare("lsRR")==0){
         res = rselectLs(g, BUDGET, MCROUNDS, EPSILON, in.MODEL,step);
      }

      if(method.compare("lgRR")==0){
         res = rgselectLs(g, BUDGET, MCROUNDS, EPSILON, in.MODEL,step);
      }

      if(method.compare("lRR")==0){
         res = lSelect(g, BUDGET, MCROUNDS, EPSILON, in.MODEL,in.CAL);
      }

      if(method.compare("supers")==0){
         res = sSuper(g, in.BUDGET, in.MCROUNDS, in.EPSILON, in.MODEL,in.CAL);
      }
      // if(method.compare("superp")==0){
      //    res = pSuper(g, in.BUDGET, in.MCROUNDS, in.EPSILON);
      // }
      if(method.compare("supert")==0){
         res = tSuper(g, in.BUDGET, in.MCROUNDS, in.EPSILON, in.MODEL,in.CAL);
      }

      if(method.compare("RR_hyper")==0){
         g.init_hyper_graph();
         g.build_hyper_graph_r(MCROUNDS);
         res = rrSelect_hyper(g , BUDGET,MCROUNDS, EPSILON); 
      }

      // test of lazygreedy
      if(method.compare("lazygreedy")==0){
         // res = lazyGreedy(g, in.BUDGET, in.MCROUNDS, in.EPSILON, in.ALPHA);
         res = lazy_hyper(g, in.BUDGET, in.MCROUNDS, in.EPSILON, in.ALPHA);
         // logRec(g, res, in, method);
      }
      
      // test of count
      if(method.compare("count")==0){
         res = count(g, in.BUDGET, in.MCROUNDS, in.EPSILON, in.ALPHA);
         // logRec(g, res, in, method);
      }   
      
      if(method.compare("myopic")==0){
         res = myOpic(g, in.BUDGET, in.MCROUNDS, in.EPSILON, in.MODEL, in.CAL);
         // res = myOpic_trick(g, in.BUDGET, in.MCROUNDS, in.EPSILON);
         // res = myOpic_hyper(g, in.BUDGET, in.MCROUNDS);
         // logRec(g, res, in, method);
      }

      if(method.compare("myopic_hyper")==0){
         g.init_hyper_graph();
         g.build_hyper_graph_r(MCROUNDS);
         res = myOpic_hyper(g, in.BUDGET, in.MCROUNDS);
      }      
      if(method.compare("superR")==0){
         res = super(g, in.BUDGET, in.MCROUNDS, in.EPSILON);
      }



      for(int j = 0;j<BUDGET;j++){
         double spread = res.inf[j];
         double clock = res.time[j];
         
         influence[j] += spread;
         time[j] += clock;
      }  
      printf("we've finished %d round test\n",test);
   }
   for(int j = 0;j<BUDGET;j++){
      influence[j] = influence[j]*1.0/TEST;
      time[j] = time[j]*1.0/TEST;
   }
   values avg_res = {res.sed,influence,time};
   logRec(g,avg_res, in, method, calcu);
   

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