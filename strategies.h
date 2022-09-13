#include "expect.h"

using namespace std;
using namespace std :: chrono;


double SELECTEDGES = 1/32;

values greedy(Graph g, int k, int mc, double epsilon){
   clock_t start_t, end_t;
   double duration;
   start_t = clock();

   set<int> S, G;
   vector<int> Q;
   vector<double> maxinf, tim;
   queue<int> s;
   for(int i=0; i<g.numVert;i++){
      G.insert(i);
   }
   cout<<endl;
   int node = -1;
   for(int _ =0; _<k;_++){
      double max_ = 0;
      double min_ = 0x3f3f3f;
      set<int, greater<int> >::iterator i;
      set<int, greater<int> >::iterator j;
      queue<int> QueueS;
      for (i = S.begin(); i != S.end(); i++){
         // G.erase(*i);
         
         QueueS.push(*i);
      }
      
      
      for (j = G.begin(); j != G.end(); j++) {
         s=QueueS;
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
      Q.push_back(node);


      
      //cout<<"slecting "<<node<< " with time: "<< duration<<endl;
      

   }
   
/*
   
   queue<int> greedy_select;
   cout<<"sorted selected"<<endl;
   for(int i=0;i<Q.size();i++){
      int node = Q[i];
      cout<<Q[i]<<" ";
      greedy_select.push(node);
      // cout <<"now we propogate adding node:" << i <<endl;
      pair<double,int> influence = icExp(g, greedy_select, mc, epsilon);
      inf.push_back(influence.first);
   }
   cout<<endl;
   */
   // }
   vector<double> inf;
   inf = maxinf;
   values res ={Q,inf,tim};
   // res.sed = ;
   
   // res.time = times;
   return res;
   //return make_pair(S,maxinf);
}

values greedy_hyper(InfGraph g, int k, int mc, double epsilon){
   clock_t start_t, end_t;
   double duration;
   start_t = clock();

   set<int> S, G;
   vector<int> Q;
   vector<double> maxinf, tim;
   queue<int> s;
   for(int i=0; i<g.numVert;i++){
      G.insert(i);
   }
   cout<<endl;
   int node = -1;
   for(int _ =0; _<k;_++){
      double max_ = 0;
      double min_ = 0x3f3f3f;
      set<int, greater<int> >::iterator i;
      set<int, greater<int> >::iterator j;
      queue<int> QueueS;
      for (i = S.begin(); i != S.end(); i++){
         // G.erase(*i);
         
         QueueS.push(*i);
      }
      
      
      for (j = G.begin(); j != G.end(); j++) {
         s=QueueS;
         s.push(*j);
         //cout<<"search max with node:"<<*j<<endl;
         float* counter = icExp_hyper(g, s, mc);

         int set_j = 0;
         int min = *min_element(counter+0, counter+g.numVert);
         for(int t = 0;t<g.numVert;t++){
            // cout<<count<<" ";
            if(counter[t] <= min + epsilon){
               //cout<< count <<" ";
               set_j++;
            }
         }        
         double exp_j = min*1.0/mc;
      

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
      Q.push_back(node);


      
      //cout<<"slecting "<<node<< " with time: "<< duration<<endl;
      

   }
   
/*
   
   queue<int> greedy_select;
   cout<<"sorted selected"<<endl;
   for(int i=0;i<Q.size();i++){
      int node = Q[i];
      cout<<Q[i]<<" ";
      greedy_select.push(node);
      // cout <<"now we propogate adding node:" << i <<endl;
      pair<double,int> influence = icExp(g, greedy_select, mc, epsilon);
      inf.push_back(influence.first);
   }
   cout<<endl;
   */
   // }
   vector<double> inf;
   inf = maxinf;
   values res ={Q,inf,tim};
   // res.sed = ;
   
   // res.time = times;
   return res;
   //return make_pair(S,maxinf);
}


set<int> oneHop(Graph g, set<int> S){
   for(const auto& node: S){
      for(long unsigned int w=0; w < g.pre[node].size(); w++){

         S.insert(g.pre[node][w]);

      }
   }
   return S;
}


int* rGs(Graph g, int SAMPLE_ROUND ){
   
   
   int *V = (int*)malloc(sizeof(int)*g.numVert);
   int *counter = (int*)malloc(sizeof(int)*g.numVert);

   for (int node=0; node<g.numVert; node++) {
      set<int> neighbor;
      neighbor.insert(node);

      for(int j=0; j < SAMPLE_ROUND;j++){ 
         neighbor = oneHop(g, neighbor);
    
      }
      for(const auto& node: neighbor){
         counter[node]++;
      }     


   }  
   /*
   cout<<"what is inside couter:"<<endl;
   for(int i = 0;i<g.numVert;i++){
      cout<<counter[i]<<" ";
   }
   cout<<endl;
   */
   for (int i =0;i<g.numVert;i++){
      V[i] = i;
   }

   // sorted by max->min 
   sort( V,V+g.numVert, [&](int i,int j){return counter[j]<counter[i];} );
   free(counter);
   /*
   cout<<"V after sorted:"<<endl;
   for (int i =0;i<g.numVert;i++){
      cout<<V[i]<<" ";
   }
   cout<<endl;
   */
   return V;
}

values rSelect(Graph g, int k, int SAMPLE_ROUND, int MCROUNDS, double EPSILON){
   clock_t start_t, end_t;
   double duration;
   start_t = clock();
   set<int> S;
   vector<int> Q;
   vector<double> inf;
   vector<double>  tim;
   queue<int> candidate;
   queue<int> rr_select;

   int* V  = rGs(g, SAMPLE_ROUND);
   cout<< "after sorted"<<endl;
   cout<<"sorted max appared nodes"<<endl;
   for (int i=0;i<g.numVert;i++){
      candidate.push(V[i]);
      cout<<V[i]<<" ";
   }
   free(V);

   cout<<endl<<"start to select nodes"<<endl;
   // int i = 0;
   for(int i = 0; i<k; i++){
   // while(!candidate.empty()){
      int node = candidate.front();
      printf(" waht is the front node in this V session: %d \n",node);
      // const bool is_in = S.find(node) != S.end();
      
      // if(!is_in){
         // cout<<"using budget: "<<i<<endl; 
         // cout<<"has add node "<<node<<endl;
      S.insert(node);
      Q.push_back(node);
      end_t = clock();
      duration = (double)(end_t - start_t); /// CLOCKS_PER_SEC;
      tim.push_back(duration);
         // i++;
         
      // }
      candidate.pop();
   }


   cout<<"sorted selected"<<endl;
   for(long unsigned int i=0;i<Q.size();i++){
      int node = Q[i];
      cout<<Q[i]<<" ";
      rr_select.push(node);
      // cout <<"now we propogate adding node:" << i <<endl;
      pair<double,int> influence = icExp(g, rr_select, MCROUNDS, EPSILON);
      inf.push_back(influence.first);
   }
   cout<<endl;
   values res ={Q,inf,tim};
   return res;
}


values lazyGreedy(Graph g, int k, int mc, double epsilon, double alpha){
   clock_t start_t, end_t;
   double duration;
   start_t = clock();

   set<int> S, G;
   vector<int> Q;
   float pre_sum_min = 0;
   float sum_min = 0;
   vector<double> maxinf, tim;
   vector<double> margininf(g.numVert,0);
   // float* margininf = (float*)malloc(g.numVert*sizeof(0));
   for(int i=0; i<g.numVert;i++){
      G.insert(i);
   }
   cout<<endl;
   int node = -1;

   for(int _ =0; _<k; _++){ 
      // cout<<"======================================== "<<endl;
      // double max_ = 0;
      set<int, greater<int> >:: iterator i;
      set<int, greater<int> >:: iterator v;
      queue<int> QueueS;
      queue<int> s;
      bool first = true;

      for (i = S.begin(); i != S.end(); i++){
         // G.erase(*i);
         QueueS.push(*i);
      }

      for (v = G.begin(); v != G.end(); v++) {
         s = QueueS;
         s.push(*v);

         if(not first){
            if(margininf[*v]!=0){
               if(margininf[*v] < margininf[node]*0.6 ){
                  continue;
               }
            }
         }

         margininf[*v] = 0;
         float sum_min_each = 0 ;
         // queue<int> temp;
         // temp = s;
         // cout<<"what is in the set:";
         // while(!temp.empty()){
         //    cout << temp.front() << " ";
         //    temp.pop();
         // }
         // cout<<endl;
         float* counter = icExp_lazy(g, s, mc);
         // cout<<"print type counter[i] "<<typeid(counter[1]).name()<< " with "<< counter[1]<<endl;
         for (int i = 0;i<g.numVert;i++){
            sum_min_each += std::min<float>(counter[i]*1.0/mc, alpha);
            //min(counter[i], alpha);
         }
         
         //cout<<"there are some thing called sum of min: "<<sum_min_<<endl;
         margininf[*v] = sum_min_each - pre_sum_min;
         // cout<<"sum min in this turn "<<sum_min_each<<" sum min in last round"<<pre_sum_min<<endl;

         if(first){
            first = false;
            // cout<<"selecting "<<*v<<" now"<<endl;
            node = *v;
            sum_min = sum_min_each;
            continue;
         }

         if(margininf[*v]>=margininf[node]){
            node = *v;
            // cout<<"selecting antoher branch selecting "<<*v<<"now"<<endl;
            sum_min = sum_min_each;
         }


         
      }
      // cout<<"margininf here, with lenth "<<g.numVert<<endl;
      // for(int i=0;i<g.numVert;i++){
      //    cout<< std::setprecision(10)<<margininf[i]<<" ";
      // }
      // cout<<endl;

      end_t = clock();
      duration = (double)(end_t - start_t)/ CLOCKS_PER_SEC;     
      tim.push_back(duration);
      
      G.erase(node);
      S.insert(node);
      pre_sum_min = sum_min;
      // cout<<"largest marginal gain this round: "<<pre_sum_min<<endl;
      // cout<<"what in Selecting S: ";
      // for(const auto& i: S){
      //    cout<<i;
      // }
      // cout<<endl;
      Q.push_back(node);

   }

   vector<double> inf;
   queue<int> lazy_select;
   // cout<<"sorted selected"<<endl;
   for(long unsigned int i=0;i<Q.size();i++){
      int node = Q[i];
      // cout<<Q[i]<<" ";
      lazy_select.push(node);
      // cout <<"now we propogate adding node:" << i <<endl;
      pair<double,int> influence = icExp(g, lazy_select, mc, epsilon);
      inf.push_back(influence.first);
   }
   // cout<<endl;


   values res ={Q,inf,tim};
   return res;
}

values lazy_hyper(InfGraph g, int k, int mc, double epsilon, double alpha){
   clock_t start_t, end_t;
   double duration;
   start_t = clock();

   set<int> S, G;
   vector<int> Q;
   float pre_sum_min = 0;
   float sum_min=0;
   vector<double> maxinf, tim;
   vector<double> margininf(g.numVert,0);
   // float* margininf = (float*)malloc(g.numVert*sizeof(0));
   for(int i=0; i<g.numVert;i++){
      G.insert(i);
   }
   // cout<<endl;
   int node = -1;

   for(int _ =0; _<k; _++){ 
      // cout<<"======================================== "<<endl;
      // double max_ = 0;
      set<int, greater<int> >:: iterator i;
      set<int, greater<int> >:: iterator v;
      queue<int> QueueS;
      queue<int> s;
      bool first = true;

      for (i = S.begin(); i != S.end(); i++){
         // G.erase(*i);
         QueueS.push(*i);
      }

      for (v = G.begin(); v != G.end(); v++) {
         s = QueueS;
         s.push(*v);

         if(not first){
            if(margininf[*v]!=0){
               if(margininf[*v] < margininf[node]*0.6 ){
                  continue;
               }
            }
         }

         margininf[*v] = 0;
         float sum_min_each = 0 ;
         // queue<int> temp;
         // temp = s;
         // cout<<"what is in the set:";
         // while(!temp.empty()){
         //    cout << temp.front() << " ";
         //    temp.pop();
         // }
         // cout<<endl;
         float* counter = icExp_hyper(g, s, mc);
         // cout<<"print type counter[i] "<<typeid(counter[1]).name()<< " with "<< counter[1]<<endl;
         for (int i = 0;i<g.numVert;i++){
            sum_min_each += std::min<float>(counter[i]*1.0/mc, alpha);
            //min(counter[i], alpha);
         }
         
         //cout<<"there are some thing called sum of min: "<<sum_min_<<endl;
         margininf[*v] = sum_min_each - pre_sum_min;
         //cout<<"sum min in this turn "<<sum_min_each<<" sum min in last round"<<pre_sum_min<<endl;

         if(first){
            first = false;
            // cout<<"selecting "<<*v<<" now"<<endl;
            node = *v;
            sum_min = sum_min_each;
            continue;
         }

         if(margininf[*v]>=margininf[node]){
            node = *v;
            // cout<<"selecting antoher branch selecting "<<*v<<"now"<<endl;
            sum_min = sum_min_each;
         }


         
      }
      // cout<<"margininf here, with lenth "<<g.numVert<<endl;
      // for(int i=0;i<g.numVert;i++){
      //    cout<< std::setprecision(10)<<margininf[i]<<" ";
      // }
      // cout<<endl;

      end_t = clock();
      duration = (double)(end_t - start_t)/ CLOCKS_PER_SEC;     
      tim.push_back(duration);
      
      G.erase(node);
      S.insert(node);
      pre_sum_min = sum_min;
      // cout<<"largest marginal gain this round: "<<pre_sum_min<<endl;
      // cout<<"what in Selecting S: ";
      // for(const auto& i: S){
      //    cout<<i;
      // }
      // cout<<endl;
      Q.push_back(node);

   }

   vector<double> inf;
   queue<int> lazy_select;
   // cout<<"sorted selected"<<endl;
   for(long unsigned int i=0;i<Q.size();i++){
      int node = Q[i];
      // cout<<Q[i]<<" ";
      lazy_select.push(node);
      // cout <<"now we propogate adding node:" << i <<endl;
      float* counter = icExp_hyper(g, lazy_select, mc);
      double min_expect = *min_element(counter+0, counter+g.numVert);
      inf.push_back(min_expect*1.0/mc);
   }
   // cout<<endl;


   values res ={Q,inf,tim};
   return res;
}


values count(Graph g, int k, int mc, double epsilon, double alpha){
   clock_t start_t, end_t;
   double duration;
   start_t = clock();

   set<int> S, G;
   vector<int> Q;
   vector<double> maxinf, tim;
   queue<int> s;
   for(int i=0; i<g.numVert;i++){
      G.insert(i);
   }
   cout<<endl;
   int node = -1;
   for(int _ =0; _<k;_++){
      double count_max_ = 0;
      set<int, greater<int> >::iterator i;
      set<int, greater<int> >::iterator j;
      queue<int> QueueS;
      
      for (i = S.begin(); i != S.end(); i++){
         // G.erase(*i);
         
         QueueS.push(*i);
      }
      
      
      for (j = G.begin(); j != G.end(); j++) {
         int count = 0;
         s=QueueS;
         s.push(*j);
         //cout<<"search max with node:"<<*j<<endl;
         
         float* counter = icExp_lazy(g, s, mc);
         for(int i = 0; i<g.numVert;i++){
            counter[i] = counter[i]*1.0/mc;
         }
         // cout<<"print type counter[i] "<<typeid(counter[1]).name()<< " with "<< counter[1]<<endl;
         for (int i =0;i<g.numVert;i++){
            
            if(counter[i]>alpha){
               // cout<<"if someone are larger"<<endl;
               count++;
            }
         }
         // cout<<"what is count given by: "<<count<<endl;

         if(count > count_max_){
            // cout<<"i'm selecting "<<*j<<endl;
            node = *j;
            count_max_ = count;
         }
         // cout<<"count_max_ become: "<<count_max_<<endl;
         
      }
      // break;
      end_t = clock();
      duration = (double)(end_t - start_t)/ CLOCKS_PER_SEC;

      tim.push_back(duration);
      //cout<<"maxx: "<<max_<<endl;
      G.erase(node);
      S.insert(node);
      Q.push_back(node);

      
      //cout<<"slecting "<<node<< " with time: "<< duration<<endl;
      

   }

   vector<double> inf;
   queue<int> count_select;
   cout<<"sorted selected"<<endl;
   for(long unsigned int i=0;i<Q.size();i++){
      int node = Q[i];
      cout<<Q[i]<<" ";
      count_select.push(node);
      // cout <<"now we propogate adding node:" << i <<endl;
      pair<double,int> influence = icExp(g, count_select, mc, epsilon);
      inf.push_back(influence.first);
   }
   cout<<endl;
     
   // }
   
   values res ={Q,inf,tim};
   // res.sed = ;
   // res.inf = maxinf;
   // res.time = times;
   return res;
   //return make_pair(S,maxinf);
}

values myOpic_trick(Graph g, int k, int mc, double epsilon){
   clock_t start_t, end_t;
   double duration;
   start_t = clock();

   set<int> S, G;
   vector<int> Q;
   vector<double> maxinf, tim;
   queue<int> s;
   for(int i=0; i<g.numVert;i++){
      G.insert(i);
   }
   long unsigned int max_degree = 0;
   int fir_node = -1;
   for(int i=0; i<g.numVert;i++){
      if(g.nxt[i].size()>max_degree){
         max_degree = g.nxt[i].size();//g.pre[i].size()
         fir_node = i;
      }
        
   }
   end_t = clock();
   duration = (double)(end_t - start_t)/ CLOCKS_PER_SEC;

   tim.push_back(duration);
      //cout<<"maxx: "<<max_<<endl;
   G.erase(fir_node);
   S.insert(fir_node);
   Q.push_back(fir_node);   
   int node = -1;
   for(int _ =0; _<k-1;_++){
      double max_ = 0;
      double min_ = 0x3f3f3f;
      set<int, greater<int> >::iterator i;
      set<int, greater<int> >::iterator j;
      queue<int> QueueS;
      for (i = S.begin(); i != S.end(); i++){
         // G.erase(*i);
         
         QueueS.push(*i);
      }
      
      
      for (j = G.begin(); j != G.end(); j++) {
         s=QueueS;
         s.push(*j);
         //cout<<"search max with node:"<<*j<<endl;
         pair<double,int> res = icExp(g, s, mc, epsilon);
         double exp_j=res.first;
         int set_j=res.second;
      

         if(exp_j > max_){
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
      Q.push_back(node);


      
      //cout<<"slecting "<<node<< " with time: "<< duration<<endl;
      

   }
/*
 this is for 
   vector<double> inf;
   queue<int> greedy_select;
   cout<<"sorted selected"<<endl;
   for(int i=0;i<Q.size();i++){
      int node = Q[i];
      cout<<Q[i]<<" ";
      greedy_select.push(node);
      // cout <<"now we propogate adding node:" << i <<endl;
      pair<double,int> influence = icExp(g, greedy_select, mc, epsilon);
      inf.push_back(influence.first);
   }
   cout<<endl;
 */    
   // }
   
   values res ={Q,maxinf,tim};
   // res.sed = ;
   // res.inf = maxinf;
   // res.time = times;
   return res;
   //return make_pair(S,maxinf);   
}

values myOpic(InfGraph g, int k, int mc, double epsilon){
   clock_t start_t, end_t;
   double duration;
   start_t = clock();

   set<int> S, G;
   vector<int> Q;
   vector<double> maxinf, tim;
   queue<int> s;
   for(int i=0; i<g.numVert;i++){
      G.insert(i);
   }
   long unsigned int max_degree = 0;
   int fir_node = -1;
   for(int i=0; i<g.numVert;i++){
      if(g.nxt[i].size()>max_degree){
         max_degree = g.nxt[i].size();//g.pre[i].size()
         fir_node = i;
      }
        
   }
   end_t = clock();
   duration = (double)(end_t - start_t)/ CLOCKS_PER_SEC;

   tim.push_back(duration);
      //cout<<"maxx: "<<max_<<endl;
   G.erase(fir_node);
   S.insert(fir_node);
   Q.push_back(fir_node);   
   int node = -1;
   for(int _ =0; _<k-1;_++){
      double min_ = 0x3f3f3f;
      set<int, greater<int> >::iterator i;
      set<int, greater<int> >::iterator j;
      queue<int> QueueS;
      for (i = S.begin(); i != S.end(); i++){
         // G.erase(*i);
         
         QueueS.push(*i);
      }
      
      
      for (j = G.begin(); j != G.end(); j++) {
         s=QueueS;
         s.push(*j);
         //cout<<"search max with node:"<<*j<<endl;
         pair<double,int> res = icExp(g, s, mc, epsilon);
         double exp_j=res.first;
      

         if(exp_j < min_){
            min_ =exp_j;
            node = *j;
         }
         
      }
      end_t = clock();
      duration = (double)(end_t - start_t)/ CLOCKS_PER_SEC;
      tim.push_back(duration);
      //cout<<"maxx: "<<max_<<endl;
      G.erase(node);
      S.insert(node);
      Q.push_back(node);


      
      //cout<<"slecting "<<node<< " with time: "<< duration<<endl;
      

   }

   vector<double> inf;
   queue<int> greedy_select;
   cout<<"sorted selected"<<endl;
   for(long unsigned int i=0;i<Q.size();i++){
      int node = Q[i];
      cout<<Q[i]<<" ";
      greedy_select.push(node);
      // cout <<"now we propogate adding node:" << i <<endl;
      pair<double,int> influence = icExp(g, greedy_select, mc, epsilon);
      inf.push_back(influence.first);
   }
   cout<<endl;
     
   // }
   
   values res ={Q,inf,tim};
   // res.sed = ;
   // res.inf = maxinf;
   // res.time = times;
   return res;
   //return make_pair(S,maxinf);   
}


values myOpic_hyper(InfGraph g, int k, int mc){
   clock_t start_t, end_t;
   double duration;
   start_t = clock();

   set<int> S, G;
   vector<int> Q;
   vector<double> inf;
   vector<double> maxinf, tim;
   queue<int> s;
   for(int i=0; i<g.numVert;i++){
      G.insert(i);
   }
   long unsigned int max_degree = 0;
   int fir_node = -1;
   for(int i=0; i<g.numVert;i++){
      if(g.nxt[i].size()>max_degree){
         max_degree = g.nxt[i].size();//g.pre[i].size()
         fir_node = i;
      }
        
   }
   end_t = clock();
   duration = (double)(end_t - start_t)/ CLOCKS_PER_SEC;

   tim.push_back(duration);
      //cout<<"maxx: "<<max_<<endl;
   G.erase(fir_node);
   S.insert(fir_node);
   Q.push_back(fir_node);   
   int node = -1;
   for(int _ =0; _<k-1;_++){
      double min_ = 0x3f3f3f;
      set<int, greater<int> >::iterator i;
      set<int, greater<int> >::iterator j;
      queue<int> QueueS;
      for (i = S.begin(); i != S.end(); i++){
         // G.erase(*i);
         
         QueueS.push(*i);
      }
      
      
      for (j = G.begin(); j != G.end(); j++) {
         s=QueueS;
         s.push(*j);
         //cout<<"search max with node:"<<*j<<endl;
         float* counter = icExp_hyper(g, s, mc);
         int min = *min_element(counter+0,counter+g.numVert);

         double exp_j;

         if(min ==0){
            exp_j = 0;
         }else{
            exp_j=min*1.0/mc;
         }
         
         // printf("%d ",min);

         if(exp_j < min_){
            min_ = exp_j;
            node = *j;
         }
         
      }
      end_t = clock();
      duration = (double)(end_t - start_t)/ CLOCKS_PER_SEC;
      
      // printf("picking for node %d, it's expectation is %f",node,min_);
      tim.push_back(duration);
      inf.push_back(min_);
      //cout<<"maxx: "<<max_<<endl;
      G.erase(node);
      S.insert(node);
      Q.push_back(node);


      
      //cout<<"slecting "<<node<< " with time: "<< duration<<endl;
      

   }
/**/ 
   queue<int> myopic_select;
   cout<<"sorted selected"<<endl;
   for(long unsigned int i=0;i<Q.size();i++){
      int node = Q[i];
      cout<<Q[i]<<" ";
      myopic_select.push(node);
      // cout <<"now we propogate adding node:" << i <<endl;
      float* counter = icExp_lazy(g, myopic_select, mc);
      int min = *min_element(counter+0,counter+g.numVert);
      maxinf.push_back(min*1.0/mc);
      // printf("spread as %f",min*1.0/mc);
   }
   cout<<endl;
    
   // }
   
   values res ={Q,maxinf,tim};
   // res.sed = ;
   // res.inf = maxinf;
   // res.time = times;
   return res;
   //return make_pair(S,maxinf);   
}

int* RSet(Graph g, queue<int> t, set<int> s){
   // cout<<"in Rset"<<endl;
   
   int *V = (int*)malloc(sizeof(int)*g.numVert);
   int *counter = (int*)malloc(sizeof(int)*g.numVert);
   for(int i =0;i<g.numVert;i++){
      V[i]=0;
      counter[i]=0;
   }
   // int *V = calloc(sizeof(int)*g.numVert);
   // int *counter = calloc(sizeof(int)*g.numVert);
   queue<int> Q;
   set<int> Qset;
   
   for(const auto& make:s){
      g.act[make] = 1;
      counter[make]++;
   }

   while(!t.empty()){
      int v = t.front();
      Q.push(v);
      Qset.insert(v);
      t.pop();
      vector<int> B;
      while(!Q.empty()){
         int candi = Q.front();
         Q.pop();
         B.push_back(candi);
         for(long unsigned int neighbor = 0; neighbor<g.nxt[candi].size();neighbor++){

            if( (g.act[g.nxt[candi][neighbor]] == 0) && ( Qset.find(candi) !=Qset.end() )){
               g.act[g.nxt[candi][neighbor]] = 1;
               Q.push(g.nxt[candi][neighbor]);
               B.push_back(g.nxt[candi][neighbor]);
               Qset.insert(g.nxt[candi][neighbor]);

            }
         }
         
      }
      for(const auto& node: B){
         counter[node]++;
      }
      
   }
   
   // cout<<"----------------------"<<endl;
   // cout<<"what is inside couter:"<<endl;
   // for(int i = 0;i<g.numVert;i++){
   //    cout<<counter[i]<<" ";
   // }
   // cout<<endl;

   for (int i =0;i<g.numVert;i++){
      V[i] = i;
   }

   // sorted by max->min 
   sort( V,V+g.numVert, [&](int i,int j){return counter[j]<counter[i];} );
   // free(counter);
   // cout<<"----------------------"<<endl;
   // cout<<"V after sorted:"<<endl;
   // for (int i =0;i<g.numVert;i++){
   //    cout<<V[i]<<" ";
   // }
   // cout<<endl;
   return V;
}

values rrSelect(InfGraph g, int k, int MCROUNDS, double EPSILON){
   
   clock_t start_t, end_t;
   double duration;
   start_t = clock();
   vector<double> tim;
   set<int> S;
   queue<int> Sque;
   queue<int> T;
   vector<int> Q;

   for(int i = 0; i<g.numVert;i++){
      T.push(i);
   }

   for(int j = 0; j<k; j++){
      // cout<<"trying to do rrSelection here"<<endl;
      int* V = RSet(g, T, S);
      int node;
      for(int i =0;i<g.numVert;i++){
         if( S.find(V[i]) !=S.end() ){
            continue;
         }
         else{
            node = V[i];
            break;
         }
      }
      // printf("what is node %d been selected \n",node);
      S.insert(node);
      Q.push_back(node);
      for(const auto& i: S){
         Sque.push(i);
      }
      float* counter = icExp_lazy(g, Sque, MCROUNDS);

      while(!T.empty()){
         T.pop();
      } 
      
      double min_expect = *min_element(counter+0, counter+g.numVert);
      //cout << "min expected is "<<min_expect<<" in set" <<endl;
      // printf("node that been seleceted \n");
      // cout<< typeid(counter[0]).name()<< counter[0] <<" ";
      int select;
      for(int i = 0; i<g.numVert; i++){
         if(counter[i] <= min_expect + EPSILON){
            select = i;
            // cout<< typeid(counter[i]).name() <<" "<< counter[i]<< " "<< typeid(select).name()<< select<<endl;
            T.push(select);
         }
      }
      


      

      end_t = clock();
      duration = (double)(end_t - start_t) / CLOCKS_PER_SEC;
      tim.push_back(duration);
   
   }

   vector<double> inf;
   queue<int> RR_select;
   // cout<<"sorted selected"<<endl;
   for(int i=0;i<k;i++){
      // cout<<Q[i]<<" ";
      RR_select.push(Q[i]);
      // cout <<"now we propogate adding node:" << i <<endl;
      pair<double,int> influence = icExp(g, RR_select, MCROUNDS, EPSILON);
      inf.push_back(influence.first);
   }
   // cout<<endl;
   
   values res ={Q,inf,tim};
   return res;   

}

values rrSelect_hyper(InfGraph g, int k, int MCROUNDS, double EPSILON){
   
   clock_t start_t, end_t;
   double duration;
   start_t = clock();
   vector<double> tim;
   set<int> S;
   queue<int> Sque;
   queue<int> T;
   vector<int> Q;

   for(int i = 0; i<g.numVert;i++){
      T.push(i);
   }

   for(int j = 0; j<k; j++){
      // cout<<"trying to do rrSelection here"<<endl;
      int* V = RSet(g, T, S);
      int node;
      for(int i =0;i<g.numVert;i++){
         if( S.find(V[i]) !=S.end() ){
            continue;
         }
         else{
            node = V[i];
            break;
         }
      }
      // printf("what is node %d been selected \n",node);
      S.insert(node);
      Q.push_back(node);
      for(const auto& i: S){
         Sque.push(i);
      }
      float* counter = icExp_hyperG(g, Sque, MCROUNDS);

      while(!T.empty()){
         T.pop();
      } 
      
      double min_expect = *min_element(counter+0, counter+g.numVert);
      //cout << "min expected is "<<min_expect<<" in set" <<endl;
      // printf("node that been seleceted \n");
      // cout<< typeid(counter[0]).name()<< counter[0] <<" ";
      int select;
      for(int i = 0; i<g.numVert; i++){
         if(counter[i] <= min_expect + EPSILON){
            select = i;
            // cout<< typeid(counter[i]).name() <<" "<< counter[i]<< " "<< typeid(select).name()<< select<<endl;
            T.push(select);
         }
      }
      


      

      end_t = clock();
      duration = (double)(end_t - start_t) / CLOCKS_PER_SEC;
      tim.push_back(duration);
   
   }

   vector<double> inf;
   queue<int> RR_select;
   // g.init_hyper_graph();
   // g.build_hyper_graph_r(MCROUNDS);
   // cout<<"sorted selected"<<endl;
   for(int i=0;i<k;i++){
      // cout<<Q[i]<<" ";
      RR_select.push(Q[i]);
      // cout <<"now we propogate adding node:" << i <<endl;
      // pair<double,int> influence = icExp(g, RR_select, MCROUNDS, EPSILON);
      // inf.push_back(influence.first);
      float* counter = icExp_hyperG(g, RR_select, MCROUNDS);
      double min = *min_element(counter+0,counter+g.numVert);
      min = min /MCROUNDS;
      inf.push_back(min);
   }
   // cout<<endl;
   
   values res ={Q,inf,tim};
   return res;   

}


int* RSet_mysel(Graph g, queue<int> t, set<int> s){
   // cout<<"in Rset"<<endl;
   
   int *V = (int*)malloc(sizeof(int)*g.numVert);
   int *counter = (int*)malloc(sizeof(int)*g.numVert);
   for(int i =0;i<g.numVert;i++){
      V[i]=0;
      counter[i]=0;
   }
   // int *V = calloc(sizeof(int)*g.numVert);
   // int *counter = calloc(sizeof(int)*g.numVert);
   queue<int> Q;
   set<int> Qset;
   
   for(const auto& make:s){
      g.act[make] = 1;
      counter[make]++;
   }

   while(!t.empty()){
      int v = t.front();
      Q.push(v);
      Qset.insert(v);
      t.pop();
      vector<int> B;
      while(!Q.empty()){
         int candi = Q.front();
         Q.pop();
         B.push_back(candi);
         for(long unsigned int neighbor = 0; neighbor<g.nxt[candi].size();neighbor++){

            if( (g.act[g.nxt[candi][neighbor]] == 0) && ( Qset.find(candi) !=Qset.end() )){
               if(g.nxt_prob[candi][neighbor] >= SELECTEDGES){
                  g.act[g.nxt[candi][neighbor]] = 1;
                  Q.push(g.nxt[candi][neighbor]);
                  B.push_back(g.nxt[candi][neighbor]);
                  Qset.insert(g.nxt[candi][neighbor]);
               }

            }
         }
         
      }
      for(const auto& node: B){
         counter[node]++;
      }
      
   }
   
   // cout<<"----------------------"<<endl;
   // cout<<"what is inside couter:"<<endl;
   // for(int i = 0;i<g.numVert;i++){
   //    cout<<counter[i]<<" ";
   // }
   // cout<<endl;

   for (int i =0;i<g.numVert;i++){
      V[i] = i;
   }

   // sorted by max->min 
   sort( V,V+g.numVert, [&](int i,int j){return counter[j]<counter[i];} );
   // free(counter);
   // cout<<"----------------------"<<endl;
   // cout<<"V after sorted:"<<endl;
   // for (int i =0;i<g.numVert;i++){
   //    cout<<V[i]<<" ";
   // }
   // cout<<endl;
   return V;
}

values rrSelect_mysel_hyper(InfGraph g, int k, int MCROUNDS, double EPSILON){
   
   clock_t start_t, end_t;
   double duration;
   start_t = clock();
   vector<double> tim;
   set<int> S;
   queue<int> Sque;
   queue<int> T;
   vector<int> Q;

   for(int i = 0; i<g.numVert;i++){
      T.push(i);
   }

   for(int j = 0; j<k; j++){
      // cout<<"trying to do rrSelection here"<<endl;
      int* V = RSet_mysel(g, T, S);
      int node;
      for(int i =0;i<g.numVert;i++){
         if( S.find(V[i]) !=S.end() ){
            continue;
         }
         else{
            node = V[i];
            break;
         }
      }
      // printf("what is node %d been selected \n",node);
      S.insert(node);
      Q.push_back(node);
      for(const auto& i: S){
         Sque.push(i);
      }
      float* counter = icExp_hyper(g, Sque, MCROUNDS);

      while(!T.empty()){
         T.pop();
      } 
      
      double min_expect = *min_element(counter+0, counter+g.numVert);
      //cout << "min expected is "<<min_expect<<" in set" <<endl;
      // printf("node that been seleceted \n");
      // cout<< typeid(counter[0]).name()<< counter[0] <<" ";
      int select;
      for(int i = 0; i<g.numVert; i++){
         if(counter[i] <= min_expect + EPSILON){
            select = i;
            // cout<< typeid(counter[i]).name() <<" "<< counter[i]<< " "<< typeid(select).name()<< select<<endl;
            T.push(select);
         }
      }
      


      

      end_t = clock();
      duration = (double)(end_t - start_t) / CLOCKS_PER_SEC;
      tim.push_back(duration);
   
   }

   vector<double> inf;
   queue<int> RR_select;
   // cout<<"sorted selected"<<endl;
   for(int i=0;i<k;i++){
      // cout<<Q[i]<<" ";
      RR_select.push(Q[i]);
      // cout <<"now we propogate adding node:" << i <<endl;
      pair<double,int> influence = icExp(g, RR_select, MCROUNDS, EPSILON);
      inf.push_back(influence.first);
   }
   // cout<<endl;
   
   values res ={Q,inf,tim};
   return res;   

}