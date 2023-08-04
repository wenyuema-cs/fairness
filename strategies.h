#include "expect.h"
#include <numeric>

using namespace std;
using namespace std :: chrono;


double SELECTEDGES = 1/32;

void Median(float *a,int l,int r){
    if( l < r ){
        int i =l, j=r, x = a[l];
        while(i<j ){
            while(i<j && a[j]>=x){
                j--;
            }
            if(i<j){
                a[i] = a[j];
            }
            while(i<j && a[i]<x){
                i++;
            }
            if(i<j){
                a[j] = a[i];
            }
        }
        a[i] = x;
        Median(a,l,i-1);
        Median(a,i+1,r);
    }
}


float geoMean(float arr[], int n)
{
    // declare sum variable and
    // initialize it to 1.
    float sum = 0;
 
    // Compute the sum of all the
    // elements in the array.
    for (int i = 0; i < n; i++){
        if(arr[i]==0){
            return 0;
        }
        sum = sum + log(arr[i]);
        // printf("a[%d]:%d sum is %f\n",i,arr[i],sum);

    }
    // compute geometric mean through formula
    // antilog(((log(1) + log(2) + . . . + log(n))/n)
    // and return the value to main function.
    sum = sum/ n;
 
    return exp(sum);
}


values greedy(Graph g, int k, int mc, double epsilon, string model, string calcu){
   clock_t start_t, end_t;
   double duration;
   start_t = clock();

   set<int> S, G;
   vector<int> Q;
   vector<double> maxinf, tim;
   queue<int> s;
   // pair<double,int> res;
   summary res;
   for(int i=0; i<g.numVert;i++){
      G.insert(i);
   }
   // cout<<endl;
   int node = -1;
   int exp_j,set_j,sum_j,sum;
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
         if(model =="lt") 
            res = ltExpg(g,s,mc,epsilon);
         if(model == "ic")
            res = icExp(g, s, mc, epsilon);
         exp_j=res.min;
         set_j=res.node; // here is not node it's the number of nodes in thershold specifically  
         sum_j = res.sum;

         if(exp_j >max_){
            max_ = exp_j;
         }
         if(exp_j == max_){
            if(set_j<=min_){
               node = *j;
               sum = sum_j;
               min_ = set_j;
            }
         }
         
      }
      end_t = clock();
      duration = (double)(end_t - start_t)/ CLOCKS_PER_SEC;

      if(calcu == "min")
         maxinf.push_back(max_*1.0/mc);
      if(calcu == "sum")
         maxinf.push_back(sum*1.0/mc);
      tim.push_back(duration);
      G.erase(node);
      S.insert(node);
      Q.push_back(node);

   }
   
   vector<double> inf;
   inf = maxinf;
   values res_log ={Q,inf,tim};
   return res_log;
}


gpcpack gpc(Graph g, int mc, double cost, string model){
   cout<<"I'm in gpc";
   set<int> S, G;
   queue<int> s;
   int cost_mc = cost*mc*g.numVert;
   cout<<"cost_mc:"<<cost_mc<<endl;
   int* counter = (int*)malloc(sizeof(int));
   for(int i=0; i<g.numVert;i++){
      G.insert(i);
   }
   // cout<<endl;
   int node = -1;
   int min_expect,sum_inf;
   double gpc_summin=0;
   double max_ = 0;

   while(max_<cost_mc){
      max_ = 0;
      set<int, greater<int> >::iterator i;
      set<int, greater<int> >::iterator j;
      queue<int> QueueS;
      for (i = S.begin(); i != S.end(); i++){
         // G.erase(*i);
         
         QueueS.push(*i);
      }
      
      for (j = G.begin(); j != G.end(); j++) {
         gpc_summin=0;
         s=QueueS;
         s.push(*j);
         //cout<<"search max with node:"<<*j<<endl;
      
         if(model == "lt")
            counter = ltExp(g, s, mc);
         if(model == "ic")
            counter = icExp_lazyI(g, s, mc);
         // cout<<"mc: ";
         // for(const auto& count : counter){
         //    cout<<count<<" ";
         // }
         // cout<<endl;

         for(int i=0;i<g.numVert;i++){
            // cout<<gpc_summin<<" ";
            if(counter[i]<cost_mc){
               gpc_summin = gpc_summin+ counter[i];
            }
            else{
               gpc_summin = gpc_summin+ cost_mc;
            }
            
         }

         // cout<<endl;
         if(gpc_summin >=max_){
            node = *j;
            max_ = gpc_summin;
            
            min_expect = *min_element(counter+0, counter+g.numVert);
            sum_inf = std::accumulate(counter+0, counter+g.numVert,0);

         }
      }
      G.erase(node);
      S.insert(node);

   }
   // printf("finish selecting seed\n");
   free(counter);
   cout<<"budget size: "<<S.size()<<" min="<<min_expect<<endl;
   gpcpack result={S, max_/g.numVert ,min_expect ,sum_inf};
   return result;
}

values saturate(Graph g, int mc, int k_total, string model, string calcu){
   clock_t start_t, end_t;
   double duration;

   vector<int> Q;
   vector<double> inf, tim;
   double cost ;
   // = 1/g.numVert;

   int inf_min,inf_sum;
   gpcpack selection;
   set<int> seed,s;
   double max;
   int k=10;
   cout<<"I'm in saturate"<<endl;
   
   while(k <= k_total)
   {
      
      cout<< "Now k = "<<k<<endl;
      start_t = clock();
      double c_max = 1;
      double c_min = 0;
      while ((c_max - c_min) >= 1.0/g.numVert)
      {
         cout<<"thershold,c_max,c_min:"<<(c_max - c_min)<<" "<< c_max<<" "<< c_min<<" "<<cost<<endl;
         cost = (c_max + c_min) / 2;
         selection = gpc(g, mc, cost, model);
         s = selection.seed;
         cout<<"selected size: "<<s.size()<<" ";
         if(s.size() >  k){
            c_max = cost;
         }else{
            c_min = cost;
            seed = s;
            inf_min = selection.min;
            inf_sum = selection.sum;
         }
      }
      cout<<endl;
   
      end_t = clock();
      duration = (double)(end_t - start_t)/ CLOCKS_PER_SEC;

      int* counter = (int*)malloc(sizeof(int));
      queue<int> QueueS;
      set<int, greater<int> >::iterator i;
      for (i = seed.begin(); i != seed.end(); i++){
         QueueS.push(*i);
      }

      if(model == "lt")
         counter = ltExp(g, QueueS, mc*100);
      if(model == "ic")
         counter = icExp_lazyI(g, QueueS, mc*100);
      if(calcu == "min"){
         inf_min = *min_element(counter+0, counter+g.numVert);
         cout<<"min expect in gpc: "<<(inf_min)*1.0/(mc*100)<<" with "<<s.size()<<endl;
         inf.push_back(inf_min*1.0/(mc*100));
      }
      if(calcu == "sum"){
         inf_sum = std::accumulate(counter+0, counter+g.numVert,0); 
         cout<<"sum expect in gpc: "<<(inf_sum*1.0)/(mc*100)<<" with "<<s.size()<<endl;
         inf.push_back(inf_sum*1.0/(mc*100));
      }
      free(counter);
      while (!QueueS.empty())
      {
         QueueS.pop();
      }
      tim.push_back(duration);
      k += 10;
      cout<<"=========================="<<endl;
      cout<<"while k = "<<k<<", min = "<<inf_min*1.0/mc<<endl;
   }
   cout<<endl;
   values res_log ={Q,inf,tim};
   return res_log;
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
      summary influence = icExp(g, lazy_select, mc, epsilon);
      inf.push_back(influence.min);
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
      summary influence = icExp(g, count_select, mc, epsilon);
      inf.push_back(influence.min);
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
         summary res = icExp(g, s, mc, epsilon);
         double exp_j=res.min;
         int set_j=res.node;
      

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


values myOpic(InfGraph g, int k, int MCROUNDS, double epsilon,string model, string calcu){
   clock_t start_t, end_t;
   double duration;
   start_t = clock();

   set<int> S, G;
   vector<double> inf;
   vector<int> Q;
   vector<double> maxinf, tim;
   queue<int> s;
   // int add = {5};
   int* counter = (int*)malloc(sizeof(int));
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
   double sum_inf = 0;
   for(int _ =0; _<k-1;_++){
      // double min_ = 0x3f3f3f;
      set<int, greater<int> >::iterator i;
      // set<int, greater<int> >::iterator j;
      queue<int> QueueS;
      // printf("who is in seed set: ");
      for (i = S.begin(); i != S.end(); i++){
         // G.erase(*i);
         // cout<<*i<<" ";
         QueueS.push(*i);
      }
      // cout<<endl;
      if(model == "lt")
         counter = ltExp(g, QueueS, MCROUNDS);
      if(model == "ic")
         counter = icExp_lazyI(g, QueueS, MCROUNDS);
      // if(model == "icc")
      //    counter = icExp_lazycon(g, QueueS, MCROUNDS);
      double min_expect = *min_element(counter+0, counter+g.numVert);
      for(int i=0;i<g.numVert;i++){ //n is the size of array a[]
         if(counter[i]==min_expect){
            // if( S.find(V[i]) !=S.end() ){
            node = i;
            // }
            
         } 
      }

      // printf("min element is node %d, with %f\n",node,min_expect);

      // for (j = G.begin(); j != G.end(); j++) {
      //    s=QueueS;
      //    s.push(*j);
      //    //cout<<"search max with node:"<<*j<<endl;
      //    pair<double,int> res = icExp(g, s, mc, epsilon);
      //    double exp_j=res.first;
      

      //    if(exp_j < min_){
      //       min_ =exp_j;
      //       node = *j;
      //    }
         
      // }
      end_t = clock();
      duration = (double)(end_t - start_t)/ CLOCKS_PER_SEC;
      tim.push_back(duration);
      //cout<<"maxx: "<<max_<<endl;
      G.erase(node);
      S.insert(node);
      Q.push_back(node);

      if(calcu == "min"){
         inf.push_back(min_expect*1.0/MCROUNDS);
      }

      if(calcu == "sum"){
         sum_inf = std::accumulate(counter+0, counter+g.numVert,0);
         inf.push_back(sum_inf/MCROUNDS);
      }

      
      //cout<<"slecting "<<node<< " with time: "<< duration<<endl;
      

   }

   // vector<double> maxinf;
   // queue<int> myopic_select;
   // for(long unsigned int i=0;i<Q.size();i++){
   //    int node = Q[i];
      // cout<<Q[i]<<" ";
      // myopic_select.push(node);
      // cout <<"now we propogate adding node:" << i <<endl;
      // pair<double,int> influence = icExp(g, myopic_select, mc, epsilon);
      // inf.push_back(influence.first);

      // if(model == "lt")
      //    counter = ltExp(g, myopic_select, mc);
      // if(model == "ic")
      //    counter = icExp_lazyI(g, myopic_select, mc);


      // find GeoMean
      // for(int m=0;m<g.numVert;m++){
      //    counter[m] = counter[m]*1.0/mc;  
      // }
      // float mean_expect = geoMean(counter,g.numVert);


      // find Median
      // Median(counter,0,g.numVert-1);
      // float med_expect = counter[g.numVert/2]*1.0/mc;

      // find min_probability
      // double min_expect = *min_element(counter+0, counter+g.numVert);
      // if (i == Q.size()-1){
      //    cout<<min_expect<<endl;
      // }

      // min_expect = min_expect/mc;

      // maxinf.push_back(min_expect);
      
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
         float* counter = icExp_hyperG(g, s, mc);
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
   // cout<<"sorted selected"<<endl;
   g.init_hyper_graph();
   g.build_hyper_graph_r(mc);
   for(int i=0;i<k;i++){
      // int node = Q[i];
      // cout<<Q[i]<<" ";
      myopic_select.push(Q[i]);
      // cout <<"now we propogate adding node:" << i <<endl;
      float* counter = icExp_hyperG(g, myopic_select, mc);
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
         for(long unsigned int neighbor = 0; neighbor<g.pre[candi].size();neighbor++){
            // no initialize? why it workds???
            if( (g.act[g.pre[candi][neighbor]] == 0) && ( Qset.find(candi) !=Qset.end() )){
               g.act[g.pre[candi][neighbor]] = 1;
               Q.push(g.pre[candi][neighbor]);
               B.push_back(g.pre[candi][neighbor]);
               Qset.insert(g.pre[candi][neighbor]);

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
   
   // int reachNum = 0;
   // // cout<<"----------------------"<<endl;
   // // cout<<"V after sorted:"<<endl;
   // for (int i =0;i<g.numVert;i++){
   //    if(counter[i]>0){
   //       reachNum++;
   //    }
   //    // cout<<V[i]<<"("<<counter[V[i]]<<") ";
   // }
   // // cout<<endl;
   // printf("there are %d nodes in reachable set",reachNum);
   
   free(counter);

   return V;
}

int* bsfReach(Graph g, bool* t, bool*s){
   // queue<int> s;
   int *V = (int*)malloc(sizeof(int)*g.numVert);
   int *counter = (int*)malloc(sizeof(int)*g.numVert);
   bool *spread = (bool*)malloc(sizeof(bool)*g.numVert);
   queue<int> oneSpread;

   for(int i=0;i<g.numVert;i++){
      V[i] = 0;
      counter[i] = 0;
   }

   
   for (int i=0;i<g.numVert;i++)
   {
      if(t[i] == true){
         oneSpread.push(i);
         for(int j=0;j<g.numVert;j++){
            spread[j] = false;
         }
         while(!oneSpread.empty()){
            int node = oneSpread.front();
            oneSpread.pop();
            for(long unsigned int w = 0; w<g.pre[node].size();w++){

               // counter one spread without repeating
               if((spread[w] == false) && (s[i] == false )){
                  spread[w] =true;
                  counter[w]++;
                  oneSpread.push(w);
               }
            }
         }
      }
      else{
         continue;
      }
      

   }

   for (int i =0;i<g.numVert;i++){
      V[i] = i;
   }

   // sorted by max->min 
   sort( V,V+g.numVert, [&](int i,int j){return counter[j]<counter[i];} );
   /**/
   // int reachNum = 0;
   // for(int i=0;i<g.numVert;i++){
   //    if(counter[i]>0){
   //       reachNum++;
   //    }
   // }
   // printf("there are %d nodes in reachable set\n",reachNum);
   
   return V;
   


}

values rbfsSelect(InfGraph g, int k, int MCROUNDS, double EPSILON){
   bool *S = (bool*)malloc(sizeof(bool)*g.numVert);
   bool *T = (bool*)malloc(sizeof(bool)*g.numVert);
   clock_t start_t, end_t;
   double duration;
   start_t = clock();
   // set<int> S;

   vector<int> Q;
   vector<double> inf;
   vector<double>  tim;
   queue<int> targets,s;

   for(int i = 0; i<g.numVert;i++){
      // targets.push(i);
      S[i] = false;
      T[i] = true;
   }

   for(int budget = 0; budget<k; budget++){
      int targetNum = 0;
      int* V  = bsfReach(g, T, S);

      int node;
      for (int i=0;i<g.numVert;i++){
         if(S[V[i]]==true){
            continue;
         }
         else{
            node = V[i];
            printf("node %d can be selected\n",node);
            break;
         }
      }
      
      S[node] = true;
      s.push(node);
      Q.push_back(node);
      end_t = clock();
      duration = (double)(end_t -start_t)/CLOCKS_PER_SEC;
      tim.push_back(duration);

      // cout<<"node selected by far";
      // for(int i=0;i<g.numVert;i++){
      //    if(S[i]==true){
      //       cout<<i<<" ";
      //    }
      // }
      // cout<<endl;

      int* counter = icExp_lazyI(g,s,MCROUNDS);

      while(!targets.empty()){
         targets.pop();
      }
      for(int i=0; i<g.numVert;i++){
         T[i]=false;
      }
      targetNum = 0;

      int min_expect = *min_element(counter+0, counter+g.numVert);

      // int select;
      for(int i=0; i<g.numVert;i++){
         if(counter[i]<= min_expect+EPSILON){
            T[i]=true;
            targetNum ++;
         }
      }
      // printf("round %d: there are %d nodes in target set\n",budget,targetNum);
   }
   queue<int> RR_selet;
   //  min_expect;
   for(int i=0;i<k;i++){
      RR_selet.push(Q[i]);
      int* counter =icExp_lazyI(g,RR_selet,MCROUNDS);
      // cout<<"counter in this mc process, with "<< sizeof(counter)<<" nodes: " <<endl;
      // for (int i =0;i<g.numVert;i++){
      //    // counter[i]= std::min<float>(counter[i]/mc, alpha);
      //    cout<<counter[i]<<" ";
      // }
      // cout << endl;
      double min_expect = *min_element(counter+0,counter+g.numVert);
      min_expect = min_expect*1.0/MCROUNDS;
      // printf("%d rounds influence spread as: %f\n",i,min_expect);
      inf.push_back(min_expect);
   }
   values res ={Q,inf,tim};
   return res;
}



int* onehopReach(InfGraph g, bool* t, bool* S){
   
   // queue<int> s;
   int *V = (int*)malloc(sizeof(int)*g.numVert);
   int *counter = (int*)malloc(sizeof(int)*g.numVert);

   for(int i=0;i<g.numVert;i++){

      counter[i] =0;
   //    if(S[i]==true){
   //       s.push(i);
   //    }
   }

   for(int node =0; node<g.numVert; node++){
      
      if(t[node] ==true){
         counter[node]++;
         for(long unsigned int w=0; w < g.pre[node].size(); w++){

            if(S[node] == false){
               counter[g.pre[node][w]]++;
            }

         }
      }
      else{
         continue;
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
   /**/

   // int reachNum = 0;
   // for(int i=0;i<g.numVert;i++){
   //    if(counter[i]>0){
   //       reachNum++;
   //    }
   // }
   // printf("there are %d nodes in reachable set\n",reachNum);
   // cout<<"V after sorted:"<<endl;
   // for (int i =0;i<g.numVert;i++){
   //    cout<<V[i]<<" ";
   // }
   // cout<<endl;
   free(counter);
   return V;
}

values rSelect(InfGraph g, int k, int MCROUNDS, double EPSILON, string model, string calcu){
   bool *S = (bool*)malloc(sizeof(bool)*g.numVert);
   bool *T = (bool*)malloc(sizeof(bool)*g.numVert);
   clock_t start_t, end_t;
   double duration;
   start_t = clock();
   // set<int> S;

   int* counter = (int*)malloc(sizeof(int));
   vector<int> Q;
   vector<double> inf;
   vector<double>  tim;
   queue<int> targets,s;

   for(int i = 0; i<g.numVert;i++){
      // targets.push(i);
      S[i] = false;
      T[i] = true;
   }

   for(int budget = 0; budget<k; budget++){
      int targetNum = 0;
      int* V  = onehopReach(g, T, S);
      

      int node;
      for (int i=0;i<g.numVert;i++){
         if(S[V[i]]==true){
            continue;
         }
         else{
            node = V[i];
            // printf("node %d can be selected\n",node);
            break;
         }
      }
      
      S[node] = true;
      s.push(node);
      Q.push_back(node);
      end_t = clock();
      duration = (double)(end_t -start_t)/CLOCKS_PER_SEC;
      tim.push_back(duration);

      // for(int i=0;i<g.numVert;i++){
      //    if(S[i]==true){
      //       s.push(i);
      //    }
      // }

      if(model == "lt")
         counter = ltExp(g, s, MCROUNDS);
      if(model == "ic")
         counter = icExp_lazyI(g, s, MCROUNDS);

      while(!targets.empty()){
         targets.pop();
      }
      for(int i=0; i<g.numVert;i++){
         T[i]=false;
      }
      targetNum = 0;

      int min_expect = *min_element(counter+0, counter+g.numVert);

      // int select;
      for(int i=0; i<g.numVert;i++){
         if(counter[i]<= min_expect+EPSILON){
            T[i]=true;
            targetNum ++;
         }
      }
      // printf("round %d: there are %d nodes in target set\n",budget,targetNum);
   }
   queue<int> RR_selet;
   //  min_expect;
   double sum_inf=0;
   for(int i=0;i<k;i++){
      RR_selet.push(Q[i]);
      if(model == "lt")
         counter = ltExp(g, RR_selet, MCROUNDS);
      if(model == "ic")
         counter = icExp_lazyI(g, RR_selet, MCROUNDS);
      // cout<<"counter in this mc process, with "<< sizeof(counter)<<" nodes: " <<endl;
      // for (int i =0;i<g.numVert;i++){
      //    // counter[i]= std::min<float>(counter[i]/mc, alpha);
      //    cout<<counter[i]<<" ";
      // }
      // cout << endl;
      double min_expect = *min_element(counter+0,counter+g.numVert);
      min_expect = min_expect*1.0/MCROUNDS;
      // printf("%d rounds influence spread as: %f\n",i,min_expect);
      
      if(calcu == "min"){
         inf.push_back(min_expect);
      }
      if(calcu == "sum"){
         sum_inf = std::accumulate(counter+0, counter+g.numVert,0);
         inf.push_back(sum_inf/MCROUNDS);
      }
      
   }
   values res ={Q,inf,tim};
   return res;
}


int* tieReach(InfGraph g, bool* t, bool* S,double *probC){
   
   // queue<int> s;
   // int wholePro =0;
   int *V = (int*)malloc(sizeof(int)*g.numVert);
   int *counter = (int*)malloc(sizeof(int)*g.numVert);
   // double *probC = (double*)malloc(sizeof(double)*g.numVert);

   for(int i=0;i<g.numVert;i++){

      counter[i] =0;
   //    if(S[i]==true){
   //       s.push(i);
   //    }
   }

   for(int node =0; node<g.numVert; node++){
      
      if(t[node] ==true){
         counter[node]++;
         // wholePro++;
         for(long unsigned int w=0; w < g.pre[node].size(); w++){

            if(S[node] == false){
               counter[g.pre[node][w]]++;
               // wholePro++;
            }


         }
      }
      else{
         continue;
      }

   }

   
   for (int i =0;i<g.numVert;i++){
      V[i] = i;
   }

   // sorted by max->min 
   // tie should change from min-max!!
   sort( V,V+g.numVert, [&](int i,int j){return (counter[j]<counter[i]) || (counter[j]<counter[i]) && (probC[i]<probC[j]);} );
   // /**/
   // int reachNum = 0;
   // for(int i=0;i<g.numVert;i++){
   //    if(counter[i]>0){
   //       reachNum++;
   //    }
   // }
   // printf("there are %d nodes in reachable set\n",reachNum);
   free(counter);
   return V;
}

values rtieSelect(InfGraph g, int k, int MCROUNDS, double EPSILON, string model, string calcu){
   bool *S = (bool*)malloc(sizeof(bool)*g.numVert);
   bool *T = (bool*)malloc(sizeof(bool)*g.numVert);
   int* counter = (int*)malloc(sizeof(int));
   // record p(u,s)
   double *probC = (double*)malloc(sizeof(double)*g.numVert);
   clock_t start_t, end_t;
   double duration;
   start_t = clock();
   // set<int> S;

   vector<int> Q;
   vector<double> inf;
   vector<double>  tim;
   queue<int> targets,s;

   for(int i = 0; i<g.numVert;i++){
      // targets.push(i);
      S[i] = false;
      T[i] = true;
      probC[i] = 0;
   }

   for(int budget = 0; budget<k; budget++){
      int targetNum = 0;
      int* V  = tieReach(g, T, S, probC);
      // free(probC)
      

      int node;
      for (int i=0;i<g.numVert;i++){
         if(S[V[i]]==true){
            continue;
         }
         else{
            node = V[i];
            // printf("node %d can be selected\n",node);
            break;
         }
      }
      
      S[node] = true;
      s.push(node);
      Q.push_back(node);
      end_t = clock();
      duration = (double)(end_t -start_t)/CLOCKS_PER_SEC;
      tim.push_back(duration);

      // for(int i=0;i<g.numVert;i++){
      //    if(S[i]==true){
      //       s.push(i);
      //    }
      // }
      int wholeProb = 0;
      if(model == "lt")
         counter = ltExp(g, s, MCROUNDS);
      if(model == "ic")
         counter = icExp_lazyI(g, s, MCROUNDS);

      while(!targets.empty()){
         targets.pop();
      }
      for(int i=0; i<g.numVert;i++){
         T[i]=false;
         wholeProb += counter[i];
      }
      targetNum = 0;

      int min_expect = *min_element(counter+0, counter+g.numVert);

      // int select;
      for(int i=0; i<g.numVert;i++){
         probC[i] = counter[i]*1.0/wholeProb;
         if(counter[i]<= min_expect+EPSILON){
            T[i]=true;
            targetNum ++;
         }
      }
      // printf("round %d: there are %d nodes in target set\n",budget,targetNum);
   }
   queue<int> RR_selet;
   //  min_expect;
   double sum_inf=0;
   for(int i=0;i<k;i++){
      RR_selet.push(Q[i]);
      if(model == "lt")
         counter = ltExp(g, RR_selet, MCROUNDS);
      if(model == "ic")
         counter = icExp_lazyI(g, RR_selet, MCROUNDS);
      // cout<<"counter in this mc process, with "<< sizeof(counter)<<" nodes: " <<endl;
      // for (int i =0;i<g.numVert;i++){
      //    // counter[i]= std::min<float>(counter[i]/mc, alpha);
      //    cout<<counter[i]<<" ";
      // }
      // cout << endl;
      double min_expect = *min_element(counter+0,counter+g.numVert);
      min_expect = min_expect*1.0/MCROUNDS;
      // printf("%d rounds influence spread as: %f\n",i,min_expect);
      // inf.push_back(min_expect);
      if(calcu == "min"){
         inf.push_back(min_expect);
      }
      if(calcu == "sum"){
         sum_inf = std::accumulate(counter+0, counter+g.numVert,0);
         inf.push_back(sum_inf/MCROUNDS);
      }
   }
   values res ={Q,inf,tim};
   return res;
}


int* probReach(InfGraph g, bool* t, bool* S){
   
   // queue<int> s;
   int wholePro =0;
   int *V = (int*)malloc(sizeof(int)*g.numVert);
   int *counter = (int*)malloc(sizeof(int)*g.numVert);
   double *probC = (double*)malloc(sizeof(double)*g.numVert);

   for(int i=0;i<g.numVert;i++){

      counter[i] =0;
      probC[i]=0;
   //    if(S[i]==true){
   //       s.push(i);
   //    }
   }

   for(int node =0; node<g.numVert; node++){
      
      if(t[node] ==true){
         counter[node]++;
         wholePro++;
         for(long unsigned int w=0; w < g.pre[node].size(); w++){

            if(S[node] == false){
               counter[g.pre[node][w]]++;
               wholePro++;
            }


         }
      }
      else{
         continue;
      }

   }
   double prob;
   // (1-p(u,s))*C(u,s))
   for(int i = 0;i<g.numVert;i++){
      prob = counter[i]*1.0/wholePro;
      probC[i] = (1-prob)*counter[i];
   }


   
   for (int i =0;i<g.numVert;i++){
      V[i] = i;
   }

   // sorted by max->min 
   sort( V,V+g.numVert, [&](int i,int j){return probC[j]<probC[i];} );
   /**/

   // int reachNum = 0;
   // for(int i=0;i<g.numVert;i++){
   //    if(counter[i]>0){
   //       reachNum++;
   //    }
   // }
   // printf("there are %d nodes in reachable set\n",reachNum);
   free(counter);
   return V;
}


values rpSelect(InfGraph g, int k, int MCROUNDS, double EPSILON){
   bool *S = (bool*)malloc(sizeof(bool)*g.numVert);
   bool *T = (bool*)malloc(sizeof(bool)*g.numVert);
   clock_t start_t, end_t;
   double duration;
   start_t = clock();
   // set<int> S;

   vector<int> Q;
   vector<double> inf;
   vector<double>  tim;
   queue<int> targets,s;

   for(int i = 0; i<g.numVert;i++){
      // targets.push(i);
      S[i] = false;
      T[i] = true;
   }

   for(int budget = 0; budget<k; budget++){
      // int reachNum = 0;
      int targetNum = 0;
      int* V  = probReach(g, T, S);
      
      // printf("round %d: there are %d nodes in reachable set\n",budget,reachNum);
      int node;
      for (int i=0;i<g.numVert;i++){
         if(S[V[i]]==true){
            continue;
         }
         else{
            node = V[i];
            // printf("node %d can be selected\n",node);
            break;
         }
      }
      
      S[node] = true;
      s.push(node);
      Q.push_back(node);
      end_t = clock();
      duration = (double)(end_t -start_t)/CLOCKS_PER_SEC;
      tim.push_back(duration);

      // for(int i=0;i<g.numVert;i++){
      //    if(S[i]==true){
      //       s.push(i);
      //    }
      // }

      int* counter = icExp_lazyI(g,s,MCROUNDS);

      while(!targets.empty()){
         targets.pop();
      }
      for(int i=0; i<g.numVert;i++){
         T[i]=false;
      }
      targetNum = 0;

      int min_expect = *min_element(counter+0, counter+g.numVert);

      // int select;
      for(int i=0; i<g.numVert;i++){
         if(counter[i]<= min_expect+EPSILON){
            T[i]=true;
            targetNum ++;
         }
      }
      // printf("round %d: there are %d nodes in target set\n",budget,targetNum);
   }
   queue<int> RR_selet;
   //  min_expect;
   for(int i=0;i<k;i++){
      RR_selet.push(Q[i]);
      int* counter =icExp_lazyI(g,RR_selet,MCROUNDS);
      // cout<<"counter in this mc process, with "<< sizeof(counter)<<" nodes: " <<endl;
      // for (int i =0;i<g.numVert;i++){
      //    // counter[i]= std::min<float>(counter[i]/mc, alpha);
      //    cout<<counter[i]<<" ";
      // }
      // cout << endl;
      double min_expect = *min_element(counter+0,counter+g.numVert);
      min_expect = min_expect*1.0/MCROUNDS;
      // printf("%d rounds influence spread as: %f\n",i,min_expect);
      inf.push_back(min_expect);
      
   }
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
   g.init_hyper_graph();
   g.build_hyper_graph_r(MCROUNDS);
   // cout<<"sorted selected"<<endl;
   for(int i=0;i<k;i++){
      // cout<<Q[i]<<" ";
      RR_select.push(Q[i]);
      // cout <<"now we propogate adding node:" << i <<endl;
      // pair<double,int> influence = icExp(g, RR_select, MCROUNDS, EPSILON);
      // inf.push_back(influence.first);

      // float* counter = icExp_hyperG(g, RR_select, MCROUNDS);
      float* counter = icExp_lazy(g, RR_select, MCROUNDS);

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
      summary influence = icExp(g, RR_select, MCROUNDS, EPSILON);
      inf.push_back(influence.min);
   }
   // cout<<endl;
   
   values res ={Q,inf,tim};
   return res;   

}


values super(InfGraph g, int k, int mc, double epsilon){

   clock_t start_t, end_t;
   double duration;
   start_t = clock();

   set<int> S, G;
   vector<double> inf;
   vector<int> Q;
   vector<double> maxinf, tim;
   queue<int> s;
   queue<int> T;

   int RRselectCount = 0;
   int myselectCount = 0;

   for(int i=0; i<g.numVert;i++){
      G.insert(i);
      // T.push(i);
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

   // G.erase(fir_node);
   S.insert(fir_node);
   Q.push_back(fir_node); 
   s.push(fir_node);  
   int my_node;
   int RR_node;
   int my_pre = 0;
   // int my_range;
   for(int j=0;j<k-1;j++){
      int* counter = icExp_lazyI(g,s,mc);
      int min_expect = *min_element(counter+0,counter+g.numVert);

      // cout<<"what in Set: ";
      // // set<int, greater<int> >::iterator k;
      // for (const auto k:S) {
      //    cout<<k<<" ";
      // }
      // cout<<endl;

      // find node from myopic, and Target nodes in RR as well.
      for(int i=0;i<g.numVert;i++){
         if(S.find(i) != S.end()){
            continue;
         }
         else{
            if(counter[i]==min_expect){
               my_node = i;
            }
            if(counter[i]<=min_expect+epsilon){
               T.push(i);
               // my_range = i;
            }
         }
      }


      int my_expect = 0;
      int my_sum;
      int my_count = 0;




      int* V = RSet(g,T,S);
      for(int i = 0;i<g.numVert;i++){
         if(S.find( V[i]) != S.end()){
            continue;
         }
         else{
            RR_node = V[i];
            break;
         }
      }


      int RR_count = 0;
      int RR_select =0;
      queue<int> my_s;
      queue<int> RR_s;
      RR_s = s;
      RR_s.push(RR_node);
      counter = icExp_lazyI(g,RR_s,mc);
      int RR_expect = *min_element(counter+0,counter+g.numVert);

      for(int i=0; i<g.numVert;i++){
         if(counter[i]==RR_expect){
            RR_select = i;
         }
      }

      // printf("RR_expect %d with node %d",RR_expect,RR_select);
      for(int i=0;i<g.numVert;i++){
         if(counter[i]<=RR_expect+epsilon*mc){
            RR_count++;
         }
      }
      // s.pop();


      // if myopic find repeat node as previous round, use RR selected node.
      if(my_pre == my_node){
         // node = -1;
         printf("round %d using RR's set\n",j);
         // cout<<"pick node "<<RR_node<<endl;
         s.push(RR_node);
         Q.push_back(RR_node);  
         S.insert(RR_node);
         maxinf.push_back(RR_expect*1.0/mc); 
         RRselectCount++;
         // cout<<"same with previous node selection in myopic."<<endl;
         continue;
      }
      else{
         RR_s = s;
         RR_s.push(my_node);
         //???
         counter = icExp_lazyI(g,RR_s,mc);
         my_expect = *min_element(counter+0,counter+g.numVert);
         my_sum = std::accumulate(counter+0,counter+g.numVert,0);
         for(int i=0;i<g.numVert;i++){
            if(counter[i]<=my_expect+epsilon*mc){
               my_count++;
            }
         }
         // s.pop();
      }

      // printf("==========================================\n");
      // printf("myopic selection is %d, RR selection is %d ", my_node,RR_node);

      if(my_expect>RR_expect){
         // printf("round %d using myopic's set\n",j);
         // cout<<"pick node "<<my_node<<endl;
         s.push(my_node);
         Q.push_back(my_node); 
         S.insert(my_node);
         my_pre = my_node;
         maxinf.push_back(my_expect*1.0/mc);
         myselectCount++;
      }
      else if(my_expect==RR_expect){
         if(my_count>=RR_count){
            // cout<<"using myopic's set: ";
            // cout<<"pick node "<<my_node<<endl;
            s.push(my_node);
            Q.push_back(my_node); 
            S.insert(my_node);
            my_pre = my_node;
            maxinf.push_back(my_expect*1.0/mc);
            myselectCount++;
            // break;
         }
         else{
            printf("round %d using RR's set\n",j);
            // cout<<"pick node "<<RR_node<<endl;
            s.push(RR_node);
            Q.push_back(RR_node);  
            S.insert(RR_node);
            maxinf.push_back(RR_expect*1.0/mc);  
            RRselectCount++;        
         }
      }
      else{
         printf("round %d using RR's set\n",j);
         // cout<<"pick node "<<RR_node<<endl;
         s.push(RR_node);
         Q.push_back(RR_node); 
         S.insert(RR_node);
         maxinf.push_back(RR_expect*1.0/mc);
         RRselectCount++;
      }
      // break;

      end_t = clock();
      duration = (double)(end_t-start_t)/CLOCKS_PER_SEC;
      tim.push_back(duration);

   }
   values res ={Q,maxinf,tim};
   // res.sed = ;
   // res.inf = maxinf;
   // res.time = times;
   printf("Myopic using %d times, RR using %d times\n",myselectCount,RRselectCount);
   return res;

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

      int targetNum = 0;
      // cout<<"trying to do rrSelection here"<<endl;
      int* V = RSet(g, T, S);
      int node;
      // cout<<"what's wrong here????????"<<endl;
      // printf("%d\n",g.numVert);
      for(int i =0;i<g.numVert;i++){
         // printf("%d %d\n",i,V[i]);
         if( S.find(V[i]) !=S.end() ){
            // printf("node %d is here", V[i]);
            continue;
         }
         else{
            node = V[i];
            // printf("choosing nodes %d here",node);
            break;
         }
      }
      
      // printf("round %d: there are %d nodes in reachable set\n",j,reachNum);
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
            targetNum++;
         }
      }
      // printf("round %d: there are %d nodes in target set\n",j,targetNum);
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
      float* counter = icExp_lazy(g, RR_select, MCROUNDS);

      // find GeoMean
      // for(int m =0;m<g.numVert;m++){
      //    counter[m] = counter[m]*1.0/MCROUNDS;
      // }
      // float mean_expect = geoMean(counter,g.numVert);

      // find Median
      // Median(counter,0,g.numVert-1);
      // float med_expect = counter[g.numVert/2]*1.0/MCROUNDS;

      //find minimial
      double min_expect = *min_element(counter+0, counter+g.numVert);
      // cout<< "min_expect in budget "<<i<<": "<<min_expect <<endl;
      min_expect = min_expect*1.0/MCROUNDS;
      inf.push_back(min_expect);
      // pair<double,int> influence = icExp(g, RR_select, MCROUNDS, EPSILON);
      // double mininf = influence.first;
      // inf.push_back(mininf);
   }
   // cout<<endl;
   
   values res ={Q,inf,tim};
   return res;   

}

/**/
values sSuper(InfGraph g, int k, int MCROUNDS, double epsilon, string model,string calcu){

   clock_t start_t, end_t;
   double duration;
   start_t = clock();

   bool *S = (bool*)malloc(sizeof(bool)*g.numVert);
   bool *T = (bool*)malloc(sizeof(bool)*g.numVert);
   int* counter = (int*)malloc(sizeof(int));
   set<int> G;
   vector<double> inf;
   vector<int> Q;
   vector<double> maxinf, tim;
   queue<int> s;


   for(int i = 0; i<g.numVert;i++){
      // targets.push(i);
      S[i] = false;
   }

   int RRselectCount = 0;
   int myselectCount = 0;

   int my_node;
   int RR_node;
   int my_pre = 0;
   // int my_range;
   for(int j=0;j<k-1;j++){
      if(model == "lt")
         counter = ltExp(g, s, MCROUNDS);
      if(model == "ic")
         counter = icExp_lazyI(g, s, MCROUNDS);
      int min_expect = *min_element(counter+0,counter+g.numVert);

      // cout<<"what in Set: ";
      // // set<int, greater<int> >::iterator k;
      // for (const auto k:S) {
      //    cout<<k<<" ";
      // }
      // cout<<endl;
      for(int i = 0; i<g.numVert;i++){
         // targets.push(i);
         T[i] = false;
      }
      // find node from myopic, and Target nodes in RR as well.
      for(int i=0;i<g.numVert;i++){
         if(S[i] ==true){
            continue;
         }
         else{
            if(counter[i]==min_expect){
               my_node = i;
            }
            if(counter[i]<=min_expect+epsilon){
               T[i] = true;
               // my_range = i;
            }
         }
      }


      int my_expect = 0;
      int my_sum;
      int my_count = 0;




      int* V = onehopReach(g,T,S);
      for(int i = 0;i<g.numVert;i++){
         if(S[V[i]] == true){
            continue;
         }
         else{
            RR_node = V[i];
            break;
         }
      }


      int RR_count = 0;
      int RR_select =0;
      queue<int> my_s;
      queue<int> RR_s;

      // RR expectation
      RR_s = s;
      RR_s.push(RR_node);
      if(model == "lt")
         counter = ltExp(g, s, MCROUNDS);
      if(model == "ic")
         counter = icExp_lazyI(g, s, MCROUNDS);
      int RR_expect = *min_element(counter+0,counter+g.numVert);
      int RR_sum = std::accumulate(counter+0, counter+g.numVert,0);

      for(int i=0; i<g.numVert;i++){
         if(counter[i]==my_expect){
            RR_select = i;
         }
      }

      // printf("RR_expect %d with node %d",RR_expect,RR_select);
      for(int i=0;i<g.numVert;i++){
         if(counter[i]<=my_expect+epsilon*MCROUNDS){
            RR_count++;
         }
      }
      // s.pop();


      // if myopic find repeat node as previous round, use RR selected node.
      if(my_pre == my_node){
         // node = -1;
         printf("round %d using RR's set\n",j);
         // cout<<"pick node "<<RR_node<<endl;
         s.push(RR_node);
         Q.push_back(RR_node);  
         S[RR_node] = true;
         if(calcu == "min"){
            maxinf.push_back(RR_expect*1.0/MCROUNDS);
         }
         if(calcu == "sum"){
            maxinf.push_back(RR_sum*1.0/MCROUNDS);
         }
         RRselectCount++;
         // cout<<"same with previous node selection in myopic."<<endl;
         continue;
      }
      else{
         my_s = s;
         my_s.push(my_node);
         // are we using s but not RR_s here? answer: should be RR_s? really?
      if(model == "lt")
         counter = ltExp(g, s, MCROUNDS);
      if(model == "ic"){
         counter = icExp_lazyI(g, s, MCROUNDS);
         my_expect = *min_element(counter+0,counter+g.numVert);

         my_sum = std::accumulate(counter+0,counter+g.numVert,0);
         for(int i=0;i<g.numVert;i++){
            if(counter[i]<=my_expect+epsilon*MCROUNDS){
               my_count++;
            }
         }
      }

         // s.pop();
      }

      // printf("==========================================\n");
      // printf("myopic selection is %d, RR selection is %d ", my_node,RR_node);

      if(my_expect>RR_expect){
         // printf("round %d using myopic's set\n",j);
         // cout<<"pick node "<<my_node<<endl;
         s.push(my_node);
         Q.push_back(my_node); 
         S[my_node] = true;
         my_pre = my_node;
         if(calcu == "min"){
            maxinf.push_back(my_expect*1.0/MCROUNDS);
         }
         if(calcu == "sum"){
            maxinf.push_back(my_sum*1.0/MCROUNDS);
         }
         myselectCount++;
      }
      else if(my_expect==RR_expect){
         if(my_count>=RR_count){
            // cout<<"using myopic's set: ";
            // cout<<"pick node "<<my_node<<endl;
            s.push(my_node);
            Q.push_back(my_node);  
            S[my_node] = true;
            my_pre = my_node;
            if(calcu == "min"){
               maxinf.push_back(my_expect*1.0/MCROUNDS);
            }
            if(calcu == "sum"){
               maxinf.push_back(my_sum*1.0/MCROUNDS);
            }
            myselectCount++;
            // break;
         }
         else{
            printf("round %d using RR's set\n",j);
            // cout<<"pick node "<<RR_node<<endl;
            s.push(RR_node);
            Q.push_back(RR_node);  
            S[RR_node] = true;
            if(calcu == "min"){
               maxinf.push_back(RR_expect*1.0/MCROUNDS);
            }
            if(calcu == "sum"){
               maxinf.push_back(RR_sum*1.0/MCROUNDS);
            }
            RRselectCount++;        
         }
      }
      else{
         printf("round %d using RR's set\n",j);
         // cout<<"pick node "<<RR_node<<endl;
         s.push(RR_node);
         Q.push_back(RR_node); 
         S[RR_node] = true;
         if(calcu == "min"){
            maxinf.push_back(RR_expect*1.0/MCROUNDS);
         }
         if(calcu == "sum"){
            maxinf.push_back(RR_sum*1.0/MCROUNDS);
         }
         RRselectCount++;
      }
      // break;

      end_t = clock();
      duration = (double)(end_t-start_t)/CLOCKS_PER_SEC;
      tim.push_back(duration);

   }
   values res ={Q,maxinf,tim};
   // res.sed = ;
   // res.inf = maxinf;
   // res.time = times;
   printf("Myopic using %d times, RR using %d times\n",myselectCount,RRselectCount);
   return res;

}


values tSuper(InfGraph g, int k, int MCROUNDS, double epsilon, string model, string calcu){

   clock_t start_t, end_t;
   double duration;
   start_t = clock();

   bool *S = (bool*)malloc(sizeof(bool)*g.numVert);
   bool *T = (bool*)malloc(sizeof(bool)*g.numVert);
   int* counter = (int*)malloc(sizeof(int));

   double *probC = (double*)malloc(sizeof(double)*g.numVert);
   set<int> G;
   vector<double> inf;
   vector<int> Q;
   vector<double> maxinf, tim;
   queue<int> s;


   for(int i = 0; i<g.numVert;i++){
      // targets.push(i);
      S[i] = false;
   }

   int RRselectCount = 0;
   int myselectCount = 0;
   int wholeProb;
   int my_node;
   int RR_node;
   int my_sum,RR_sum;
   int my_pre = 0;
   // int my_range;
   for(int j=0;j<k-1;j++){
      wholeProb = 0;
      if(model == "lt")
         counter = ltExp(g, s, MCROUNDS);
      if(model == "ic")
         counter = icExp_lazyI(g, s, MCROUNDS);
      int min_expect = *min_element(counter+0,counter+g.numVert);

      // cout<<"what in Set: ";
      // // set<int, greater<int> >::iterator k;
      // for (const auto k:S) {
      //    cout<<k<<" ";
      // }
      // cout<<endl;
      for(int i = 0; i<g.numVert;i++){
         // targets.push(i);
         T[i] = false;
         wholeProb += counter[i];
      }
      // find node from myopic, and Target nodes in RR as well.
      for(int i=0;i<g.numVert;i++){
         probC[i] = counter[i]*1.0/wholeProb;
         if(S[i] ==true){
            continue;
         }
         else{
            if(counter[i]==min_expect){
               my_node = i;
            }
            if(counter[i]<=min_expect+epsilon){
               T[i] = true;
               // my_range = i;
            }
         }
      }


      int my_expect = 0;
      int my_count = 0;




      int* V = tieReach(g,T,S,probC);
      for(int i = 0;i<g.numVert;i++){
         if(S[V[i]] == true){
            continue;
         }
         else{
            RR_node = V[i];
            break;
         }
      }


      int RR_count = 0;
      int RR_select =0;
      queue<int> my_s;
      queue<int> RR_s;

      // RR expectation
      RR_s = s;
      RR_s.push(RR_node);
      if(model == "lt")
         counter = ltExp(g, s, MCROUNDS);
      if(model == "ic")
         counter = icExp_lazyI(g, s, MCROUNDS);
      int RR_expect = *min_element(counter+0,counter+g.numVert);
      RR_sum = std::accumulate(counter+0,counter+g.numVert,0);
      for(int i=0; i<g.numVert;i++){
         if(counter[i]==my_expect){
            RR_select = i;
         }
      }

      // printf("RR_expect %d with node %d",RR_expect,RR_select);
      for(int i=0;i<g.numVert;i++){
         if(counter[i]<=my_expect+epsilon*MCROUNDS){
            RR_count++;
         }
      }
      // s.pop();


      // if myopic find repeat node as previous round, use RR selected node.
      if(my_pre == my_node){
         // node = -1;
         // printf("round %d using RR's set\n",j);
         // cout<<"pick node "<<RR_node<<endl;
         s.push(RR_node);
         Q.push_back(RR_node);  
         S[RR_node] = true;
         if(calcu == "min"){
            maxinf.push_back(RR_expect*1.0/MCROUNDS);
         }
         if(calcu == "sum"){
            maxinf.push_back(RR_sum*1.0/MCROUNDS);
         }
         RRselectCount++;
         // cout<<"same with previous node selection in myopic."<<endl;
         continue;
      }
      else{
         my_s = s;
         my_s.push(my_node);
         // are we using s but not RR_s here? answer: should be RR_s? really?
      if(model == "lt")
         counter = ltExp(g, s, MCROUNDS);
      if(model == "ic")
         counter = icExp_lazyI(g, s, MCROUNDS);
      my_expect = *min_element(counter+0,counter+g.numVert);
      my_sum = std::accumulate(counter+0,counter+g.numVert,0);
         for(int i=0;i<g.numVert;i++){
            if(counter[i]<=my_expect+epsilon*MCROUNDS){
               my_count++;
            }
         }
         // s.pop();
      }

      // printf("==========================================\n");
      // printf("myopic selection is %d, RR selection is %d ", my_node,RR_node);

      if(my_expect>RR_expect){
         // printf("round %d using myopic's set\n",j);
         // cout<<"pick node "<<my_node<<endl;
         s.push(my_node);
         Q.push_back(my_node); 
         S[my_node] = true;
         my_pre = my_node;
         if(calcu == "min"){
            maxinf.push_back(my_expect*1.0/MCROUNDS);
         }
         if(calcu == "sum"){
            maxinf.push_back(my_sum*1.0/MCROUNDS);
         }
         myselectCount++;
      }
      else if(my_expect==RR_expect){
         if(my_count>=RR_count){
            // cout<<"using myopic's set: ";
            // cout<<"pick node "<<my_node<<endl;
            s.push(my_node);
            Q.push_back(my_node);  
            S[my_node] = true;
            my_pre = my_node;
            if(calcu == "min"){
               maxinf.push_back(my_expect*1.0/MCROUNDS);
            }
            if(calcu == "sum"){
               maxinf.push_back(my_sum*1.0/MCROUNDS);
            }
            myselectCount++;
            // break;
         }
         else{
            // printf("round %d using RR's set\n",j);
            // cout<<"pick node "<<RR_node<<endl;
            s.push(RR_node);
            Q.push_back(RR_node);  
            S[RR_node] = true;
            if(calcu == "min"){
               maxinf.push_back(RR_expect*1.0/MCROUNDS);
            }
            if(calcu == "sum"){
               maxinf.push_back(RR_sum*1.0/MCROUNDS);
            }
            RRselectCount++;        
         }
      }
      else{
         // printf("round %d using RR's set\n",j);
         // cout<<"pick node "<<RR_node<<endl;
         s.push(RR_node);
         Q.push_back(RR_node); 
         S[RR_node] = true;
         if(calcu == "min"){
            maxinf.push_back(RR_expect*1.0/MCROUNDS);
         }
         if(calcu == "sum"){
            maxinf.push_back(RR_sum*1.0/MCROUNDS);
         }

         RRselectCount++;
      }
      // break;

      end_t = clock();
      duration = (double)(end_t-start_t)/CLOCKS_PER_SEC;
      tim.push_back(duration);

   }
   values res ={Q,maxinf,tim};
   // res.sed = ;
   // res.inf = maxinf;
   // res.time = times;
   // printf("Myopic using %d times, RR using %d times\n",myselectCount,RRselectCount);
   return res;

}

pair<int,int> lsGreedy(InfGraph g, int MCROUNDS, set<int> s, string model){
   set<int> redSet;
   queue<int> qReduce;
   int* counter = (int*)malloc(sizeof(int));
   set<int, greater<int> >::iterator i;
   set<int, greater<int>>::iterator j;
   int min_expect,remove_node;
   // orgSet = s;
   int node;
   int max = 0;
   // printf("we are in reducing node!!!!!\n");
   // printf("min_expectation is :\n", min_expect);
   // cout<<endl;
   for(i = s.begin(); i!=s.end(); i++){

      redSet = s;
      // printf("if we remove node %d\n",*i);
      remove_node = *i;
      redSet.erase(remove_node);
      while(!qReduce.empty()){
         qReduce.pop();
      }
      for(j = redSet.begin();j!=redSet.end();j++){
         qReduce.push(*j);
      }
      if(model == "lt")
         counter = ltExp(g, qReduce, MCROUNDS);
      if(model == "ic")
         counter = icExp_lazyI(g, qReduce, MCROUNDS);
      
      min_expect = *min_element(counter+0,counter+g.numVert);
      
      // printf("%d ", min_expect);
      if (min_expect>=max){
         node = *i;
         max = min_expect;
         // cout << "max "<<max<< ", ";
      }
      // cout<<endl;

      // orgSet.insert(remove_node);
   }
   printf("we are removing node %d, with  %d expectation \n", node, max);
   return make_pair(node,max);
}


pair<int,int> addGreedy_old(InfGraph g, int MCROUNDS, set<int> s, string model){
   set<int> restSet,G;
   queue<int> qAdd;
   int* counter;
   set<int, greater<int> >::iterator i;
   set<int, greater<int>>::iterator j;
   int min_expect,add_node;
   // orgSet = s;
   int node;
   int max = 0;


   for(int nodes=0; nodes<g.numVert; nodes++){
      G.insert(nodes);
   }
   
   // printf("seed set as :");
   // for(i = s.begin(); i!=s.end(); i++){
   //    // cout<< *i<< " ";
   // }
   // cout<<endl;

   set_difference(G.begin(),G.end(),s.begin(),s.end(),inserter(restSet,restSet.begin()));

   // printf("rest node as :");
   // for(i = restSet.begin(); i!=restSet.end(); i++){
   //    cout<< *i<< " ";
   // }
   // cout<<endl;

   for(i = restSet.begin(); i!=restSet.end(); i++){
      // if(*i%20==0){
      //    printf("%d",*i);
      // }
      add_node = *i;
      s.insert(add_node);

      for(j = s.begin();j!=s.end();j++){
         qAdd.push(*j);
      }
      if(model == "lt")
         counter = ltExp(g, qAdd, MCROUNDS);
      if(model == "ic")
         counter = icExp_lazyI(g, qAdd, MCROUNDS);
      // qAdd.pop();
      min_expect = *min_element(counter+0,counter+g.numVert);
      // printf("%d ", min_expect);
      while(!qAdd.empty()){
         qAdd.pop();
      }
      if (min_expect>=max){
         node = *i;
         max = min_expect;
      }
      free(counter);
      s.erase(add_node);

      // orgSet.insert(remove_node);
   }
   printf("we are adding node %d, with %d min expectation\n", node, max);
   return make_pair(node,max);
}

summary addGreedy(InfGraph g, int MCROUNDS, set<int> s, string model){
   set<int> restSet,G;
   queue<int> qAdd;
   int* counter;
   set<int, greater<int> >::iterator i;
   set<int, greater<int>>::iterator j;
   int add_node, min_expect, sum_inf, max;
   // double min_expect;
   // orgSet = s;
   int node;
   // double max = 0;


   for(int nodes=0; nodes<g.numVert; nodes++){
      G.insert(nodes);
   }
   
   // printf("seed set as :");
   // for(i = s.begin(); i!=s.end(); i++){
   //    // cout<< *i<< " ";
   // }
   // cout<<endl;

   set_difference(G.begin(),G.end(),s.begin(),s.end(),inserter(restSet,restSet.begin()));

   // printf("rest node as :");
   // for(i = restSet.begin(); i!=restSet.end(); i++){
   //    cout<< *i<< " ";
   // }
   // cout<<endl;
   for(i = restSet.begin(); i!=restSet.end(); i++){
      // if(*i%20==0){
      //    printf("%d",*i);
      // }
      add_node = *i;
      s.insert(add_node);

      for(j = s.begin();j!=s.end();j++){
         qAdd.push(*j);
      }
      if(model == "lt")
         counter = ltExp(g, qAdd, MCROUNDS);
      if(model == "ic")
         counter = icExp_lazyI(g, qAdd, MCROUNDS);
      // qAdd.pop();
      min_expect = *min_element(counter+0,counter+g.numVert);
      // printf("%d ", min_expect);
      while(!qAdd.empty()){
         qAdd.pop();
      }
      if (min_expect>=max){
         node = *i;
         max = min_expect;
         sum_inf = std::accumulate(counter+0, counter+g.numVert,0);
      }
      // free(counter);
      s.erase(add_node);

      // orgSet.insert(remove_node);
   }
   printf("we are adding node %d, with %d min expectation\n", node, max);
   summary res ={node, max, sum_inf};
   // make_pair(node,max);
   return res;
}

values rselectLs(InfGraph g, int k, int MCROUNDS, double EPSILON, string model,int step){
   bool *S = (bool*)malloc(sizeof(bool)*g.numVert);
   bool *T = (bool*)malloc(sizeof(bool)*g.numVert);
   bool *remove = (bool*)malloc(sizeof(bool)*g.numVert);
   clock_t start_t, end_t;
   double duration;
   start_t = clock();
   // set<int> S;

   int* counter = (int*)malloc(sizeof(int));
   vector<int> Q;
   vector<double> inf;
   vector<double>  tim;
   queue<int> targets,s;
   int replace_node, previous_node, min_expect;
   set<int> sets;
   pair<int,int> ls_candi;
   double loop_size;

   for(int i = 0; i<g.numVert;i++){
      // targets.push(i);
      S[i] = false;
      T[i] = true;
      remove[i]=false;
   }

   for(int budget = 0; budget<k; budget++){
      int targetNum = 0;
      int* V  = onehopReach(g, T, S);
      

      int node;
      for (int i=0;i<g.numVert;i++){
         if((S[V[i]]==true) || (remove[V[i]]==true)){
            continue;
         }
         else{
            node = V[i];
            // printf("node %d can be selected\n",node);
            break;
         }
      }
      
      S[node] = true;
      sets.insert(node);

      if( budget%step == 0 ){
         replace_node = -1;
         previous_node = -1;
         printf("we are in sepcial budget %d !!!!!!!",budget);
         loop_size = 1;
         double threshold =0.3*step;

         // local search on budget = 5
         while((replace_node != node) && (previous_node != node )&&(loop_size<=threshold)){
            loop_size++;
            ls_candi = lsGreedy(g, MCROUNDS, sets, model);
            replace_node = ls_candi.first;
            remove[replace_node]=true;

            sets.erase(replace_node);
            S[replace_node] = false;

            //target node re-selection
            while(!targets.empty()){
               targets.pop();
            }
            for(int i=0; i<g.numVert;i++){
               T[i]=false;
            }
            // targetNum = 0;

            min_expect = ls_candi.second;

            for(int i=0; i<g.numVert;i++){
               if(counter[i]<= min_expect+EPSILON){
                  T[i]=true;
                  // targetNum ++;
               }
            }
               
            int* V  = onehopReach(g, T, S);

            for (int i=0;i<g.numVert;i++){
               if((S[V[i]]==true) || (remove[V[i]]==true)){
                  continue;
               }
               else{
                  previous_node = node;
                  node = V[i];
                  // printf("node %d can be selected\n",node);
                  break;
               }
            }

            sets.insert(node);
            S[node] = true;
            

            printf("%d %d %d\n", replace_node, node, previous_node);

            // printf("abandon node %d ",replace_node);
            // printf("add node %d\n",node);

         }         
         
      }
      Q.push_back(node);
      end_t = clock();
      duration = (double)(end_t -start_t)/CLOCKS_PER_SEC;
      tim.push_back(duration);

      // for(int i=0;i<g.numVert;i++){
      //    if(S[i]==true){
      //       s.push(i);
      //    }
      // }


      while(!s.empty()){
         s.pop();
      }

      for(int i=0; i<g.numVert;i++){
         if(S[i]==true){
            s.push(i);
         }
         
      }

      if(model == "lt")
         counter = ltExp(g, s, MCROUNDS);
      if(model == "ic")
         counter = icExp_lazyI(g, s, MCROUNDS);

      while(!targets.empty()){
         targets.pop();
      }
      for(int i=0; i<g.numVert;i++){
         T[i]=false;
      }
      targetNum = 0;

      min_expect = *min_element(counter+0, counter+g.numVert);

      // int select;
      for(int i=0; i<g.numVert;i++){
         if(counter[i]<= min_expect+EPSILON){
            T[i]=true;
            targetNum ++;
         }
      }
      free(V);
      // printf("round %d: there are %d nodes in target set\n",budget,targetNum);
   }
   free(S);
   free(T);
   free(remove);
   queue<int> RR_selet;
   //  min_expect;
   for(int i=0;i<k;i++){
      RR_selet.push(Q[i]);
      if(model == "lt")
         counter = ltExp(g, RR_selet, MCROUNDS);
      if(model == "ic")
         counter = icExp_lazyI(g, RR_selet, MCROUNDS);
      // cout<<"counter in this mc process, with "<< sizeof(counter)<<" nodes: " <<endl;
      // for (int i =0;i<g.numVert;i++){
      //    // counter[i]= std::min<float>(counter[i]/mc, alpha);
      //    cout<<counter[i]<<" ";
      // }
      // cout << endl;
      double min_expect = *min_element(counter+0,counter+g.numVert);
      min_expect = min_expect*1.0/MCROUNDS;
      // printf("%d rounds influence spread as: %f\n",i,min_expect);
      inf.push_back(min_expect);
   }
   free(counter);
   values res ={Q,inf,tim};
   return res;
}


values rgselectLs(InfGraph g, int k, int MCROUNDS, double EPSILON, string model,int step){
   bool *S = (bool*)malloc(sizeof(bool)*g.numVert);
   bool *T = (bool*)malloc(sizeof(bool)*g.numVert);
   // bool *remove = (bool*)malloc(sizeof(bool)*g.numVert);
   clock_t start_t, end_t;
   double duration;
   start_t = clock();
   // set<int> S;

   int* counter = (int*)malloc(sizeof(int));
   vector<int> Q;
   vector<double> inf;
   vector<double>  tim;
   queue<int> targets,s;
   int replace_node, add_node, min_expect, add_expect; //,previous_node
   set<int> sets;
   pair<int,int> ls_candi,lg_candi;
   double loop_size;

   for(int i = 0; i<g.numVert;i++){
      // targets.push(i);
      S[i] = false;
      T[i] = true;
      // remove[i]=false;
   }

   for(int budget = 0; budget<k; budget++){
      int targetNum = 0;
      int* V  = onehopReach(g, T, S);
      

      int node;
      for (int i=0;i<g.numVert;i++){
         if(S[V[i]]==true){
            continue;
         }
         else{
            node = V[i];
            // printf("node %d can be selected\n",node);
            break;
         }
      }
      
      S[node] = true;
      sets.insert(node);
   
      while(!s.empty()){
         s.pop();
      }

      for(int i=0; i<g.numVert;i++){
         if(S[i]==true){
            s.push(i);
         }
         
      }

      if(model == "lt")
         counter = ltExp(g, s, MCROUNDS);
      if(model == "ic")
         counter = icExp_lazyI(g, s, MCROUNDS);

      while(!targets.empty()){
         targets.pop();
      }
      for(int i=0; i<g.numVert;i++){
         T[i]=false;
      }
      // targetNum = 0;

      min_expect = *min_element(counter+0, counter+g.numVert);
      // printf("min expectation before LS %d\n",min_expect);

      if (budget % step ==0){
      // if( (budget%step == 0) && (budget!=0) ){
         replace_node = -1;
         // previous_node = -1;
         printf("we are in sepcial budget %d: \n",budget);
         // loop_size = 1;
         // double threshold = 0.3*10;

         // local search on budget = 5
         // while((replace_node != node) && (previous_node != node )&&(loop_size<=threshold)){
         loop_size++;
         ls_candi = lsGreedy(g, MCROUNDS, sets, model);
         replace_node = ls_candi.first;
         // remove[replace_node]=true;

         sets.erase(replace_node);
         S[replace_node] = false;


         lg_candi = addGreedy_old(g, MCROUNDS, sets, model);
         add_node = lg_candi.first;
         add_expect = lg_candi.second;

         if(add_expect>min_expect){
            printf("%d is larger than %d, node %d has been add\n",add_expect, min_expect,add_node);
            node = add_node;
         }
         else{
            printf("keep previous node\n");
            node = replace_node;
         }

         

         printf("%d %d\n", replace_node, node);

            // printf("abandon node %d ",replace_node);
            // printf("add node %d\n",node);

         // }         
         
      }

      sets.insert(node);
      S[node] = true;
      Q.push_back(node);

      end_t = clock();
      duration = (double)(end_t -start_t)/CLOCKS_PER_SEC;
      tim.push_back(duration);

      // int select;
      for(int i=0; i<g.numVert;i++){
         if(counter[i]<= min_expect+EPSILON){
            T[i]=true;
            targetNum ++;
         }
      }
      // printf("round %d: there are %d nodes in target set\n",budget,targetNum);
   }
   free(S);
   free(T);
   queue<int> RR_selet;
   //  min_expect;
   for(int i=0;i<k;i++){
      RR_selet.push(Q[i]);
      if(model == "lt")
         counter = ltExp(g, RR_selet, MCROUNDS);
      if(model == "ic")
         counter = icExp_lazyI(g, RR_selet, MCROUNDS);
      // cout<<"counter in this mc process, with "<< sizeof(counter)<<" nodes: " <<endl;
      // for (int i =0;i<g.numVert;i++){
      //    // counter[i]= std::min<float>(counter[i]/mc, alpha);
      //    cout<<counter[i]<<" ";
      // }
      // cout << endl;
      double expect = *min_element(counter+0,counter+g.numVert);
      expect = expect*1.0/MCROUNDS;
      // printf("%d rounds influence spread as: %f\n",i,min_expect);
      inf.push_back(expect);
   }
   values res ={Q,inf,tim};
   return res;
}


summary replaceGreedy(InfGraph g, queue<int> s,int MCROUNDS,string model){
   set<int> sets;
   int seed;
   pair<int,int> ls_candi;//,lg_candi;
   summary lg_candi;
   int min_expect,replace_node,add_node,add_expect,node,expect,sum_inf;
   int* counter;
   int ls_times;
	MCROUNDS = MCROUNDS * 10;

   node = s.front();
   if(model == "lt")
      counter = ltExp(g, s, MCROUNDS);
   if(model == "ic")
      counter = icExp_lazyI(g, s, MCROUNDS);
   min_expect = *min_element(counter+0,counter+g.numVert);

   while(!s.empty()){
      seed = s.front();
      sets.insert(seed);
      s.pop();
   }
   printf("expectation before is %d\n",min_expect);
   expect = min_expect;
   sum_inf = std::accumulate(counter+0,counter+g.numVert,0);
   free(counter);
/*   */
   ls_times = 0;
   do{
      ls_times++;
      printf("we are in %d LS:\n",ls_times);
      ls_candi = lsGreedy(g, MCROUNDS, sets, model);
      replace_node = ls_candi.first;

      // if(remove[replace_node] == true){
      //    break;
      // }
      sets.erase(replace_node);

      lg_candi = addGreedy(g, MCROUNDS, sets, model);
      add_node = lg_candi.node;
      add_expect = lg_candi.min;

      if(add_expect>expect){
         printf("%d is larger than %d, node %d has been add\n",add_expect, expect,add_node);
         node = add_node;
         sets.insert(add_node);
         expect = add_expect;
         sum_inf = lg_candi.sum;
      }
      else{
         printf("keep previous node\n");
         node = replace_node;
         sets.insert(replace_node);
      }

   }while(node!=replace_node);

   printf("add node %d with expect %d\n",node,expect);
   summary res = {node, expect, sum_inf};
   // make_pair(node, expect)
   return res;
}

values lSelect(InfGraph g, int k, int MCROUNDS, double EPSILON, string model,string calcu){
   bool *S = (bool*)malloc(sizeof(bool)*g.numVert);
   bool *T = (bool*)malloc(sizeof(bool)*g.numVert);
   clock_t start_t, end_t;
   double duration;
   start_t = clock();
   // set<int> S;

   int* counter;
   vector<int> Q;
   vector<double> inf;
   vector<double>  tim;
   queue<int> targets,s;
   double min_expect;

   for(int i = 0; i<g.numVert;i++){
      // targets.push(i);
      S[i] = false;
      T[i] = true;
   }

   for(int budget = 0; budget<k; budget++){
      int targetNum = 0;
      int* V  = onehopReach(g, T, S);
      

      int node;
      for (int i=0;i<g.numVert;i++){
         if(S[V[i]]==true){
            continue;
         }
         else{
            node = V[i];
            // printf("node %d can be selected\n",node);
            break;
         }
      }
      
      S[node] = true;
      s.push(node);
      Q.push_back(node);
      end_t = clock();
      duration = (double)(end_t -start_t)/CLOCKS_PER_SEC;
      tim.push_back(duration);

      // for(int i=0;i<g.numVert;i++){
      //    if(S[i]==true){
      //       s.push(i);
      //    }
      // }

      if(model == "lt")
         counter = ltExp(g, s, MCROUNDS);
      if(model == "ic")
         counter = icExp_lazyI(g, s, MCROUNDS);

      while(!targets.empty()){
         targets.pop();
      }
      for(int i=0; i<g.numVert;i++){
         T[i]=false;
      }
      targetNum = 0;

      min_expect = *min_element(counter+0, counter+g.numVert);

      // int select;
      for(int i=0; i<g.numVert;i++){
         if(counter[i]<= min_expect+EPSILON){
            T[i]=true;
            targetNum ++;
         }
      }
      // printf("round %d: there are %d nodes in target set\n",budget,targetNum);
   }
   free(counter);
   free(S);
   free(T);
   queue<int> RR_selet;
   vector<int> seed;
   vector<double> timevec;
   // pair<int,int> lsres;
   summary lsres;
   printf("finish RR selection\n");
   int sum_inf;
   for(int i=0;i<k;i++){
      RR_selet.push(Q[i]);
      if(i%10 == 0){
         start_t = clock();
         printf("\nwe are in sepcial budget %d: \n",i);
         lsres = replaceGreedy(g, RR_selet, MCROUNDS,model);
         // double expect = lsres.min;
         min_expect = lsres.min*0.1/MCROUNDS;
         sum_inf = lsres.sum;
         // printf("min expectation is %f\n",min_expect);

         end_t = clock();
         duration = (double)(end_t -start_t)/CLOCKS_PER_SEC;
         
         seed.push_back(lsres.node);
         if(calcu == "min"){
            inf.push_back(min_expect);
         }
         if(calcu == "sum"){
            inf.push_back(sum_inf*0.1/MCROUNDS);
         }
         timevec.push_back(tim[i]+duration);
      }
      else{
         seed.push_back(0);
         inf.push_back(0);
         timevec.push_back(0);
         continue;
      }
      // cout<<"counter in this mc process, with "<< sizeof(counter)<<" nodes: " <<endl;
      // for (int i =0;i<g.numVert;i++){
      //    // counter[i]= std::min<float>(counter[i]/mc, alpha);
      //    cout<<counter[i]<<" ";
      // }
      // cout << endl;
      // double min_expect = *min_element(counter+0,counter+g.numVert);

   }
   values res = {seed,inf,timevec};
   return res;
}


