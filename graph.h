#include <vector>
#include <csignal>
#include <math.h> 
#include <list>
// #include "continuous_rrset.h"
#include "iheap.h"
#include "sfmt/SFMT.h"

#ifdef HEAD_INFO
ofstream __HEAD_H_FOUT;
void setInfoFile(string s){__HEAD_H_FOUT.open(s.c_str()); }
#define ASSERT(v) {if (!(v)) {cerr<<"ASSERT FAIL @ "<<__FILE__<<":"<<__LINE__<<endl; exit(1);}}
#define INFO(...) do { ___debug( #__VA_ARGS__,  __VA_ARGS__,cout); cout<<endl; if(__HEAD_H_FOUT.is_open()){___debug( #__VA_ARGS__,  __VA_ARGS__,__HEAD_H_FOUT); __HEAD_H_FOUT<<endl;}  } while(0)
#define ASSERTT(v, ...) {if (!(v)) {cerr<<"ASSERT FAIL @ "<<__FILE__<<":"<<__LINE__<<endl; INFO(__VA_ARGS__); exit(1);}}
#else
#define ASSERTT(v, ...) ;
#define ASSERT(v ) ;
#define INFO(...) ;
#endif
#define INT_MAX 0x3f3f3f
using namespace std;
// const int INT_MAX = 0x3f3f3f;
typedef long long int64;

struct values
{
   vector<int> sed;
   vector<double> inf;
   vector<double> time;
};

static unsigned long int num = 1;
int randx(void) // RAND_MAX assumed to be 32767
{
   num = num * 1103515245 + 12345;
   return (unsigned int)(num/65536) % 32768;
}

void srandx(unsigned int seed)
{
    num = seed;
}


struct inPut{
   int BUDGET ;
   int MCROUNDS ;
   double EPSILON ;
   string dataset;
   int SAMPLE_ROUND;
   double ALPHA;
};


struct CompareBySecond {
	bool operator()(pair<int, int> a, pair<int, int> b)
	{
		return a.second < b.second;
	}
};

class Graph
{
   public:
   int numVert;
   int numEdge;
   
   vector<int> node, act;
   vector<vector<int> > pre, nxt;
   vector<vector<double> > pre_prob, nxt_prob;
   Graph(int nVert){
      //numVert = nVert;
      node = vector<int>(0);
      act = vector<int>(0);
      pre = vector<vector<int> >(0);
      nxt = vector<vector<int> >(0);
      pre_prob = vector<vector<double> >(0);
      nxt_prob = vector<vector<double> >(0);
      for (int i = 0; i < nVert; i++){
         addNode(i);
      }
   };
   Graph(){
      numVert = 0;
      node = vector<int>(0);
      pre = vector<vector<int> >(0);
      nxt = vector<vector<int> >(0);
      pre_prob = vector<vector<double> >(0);
      nxt_prob = vector<vector<double> >(0);      
   }
   void addNode(int u){
      numVert++;
      node.push_back(u);
      act.push_back(false);
      nxt.push_back(vector<int>(0));
      pre.push_back(vector<int>(0));
      nxt_prob.push_back(vector<double>(0));
      pre_prob.push_back(vector<double>(0));
   }
   void addEdge(int u, int v,double p){
      numEdge++;
      if (u>numVert-1 || v>numVert-1){
         cout<<"illegal node number: "<<u <<v <<endl;
         return;
      }
      nxt[u].push_back(v);
      pre[v].push_back(u);
      nxt_prob[u].push_back(p);
      pre_prob[v].push_back(p);                                                                                                                                                                                                                                                      
      return;
   }
   //void write( ostream &out );
};
//======================================================================


class InfGraph: public Graph
{
// private:
//    vector<bool> visit;
//    vector<int> visit_mark;
public:
   vector<vector<int>> hyperG;
   vector<vector<int>> hyperGT;
   //return the number of edges visited
   deque<int> q;
   sfmt_t sfmtSeed;
	vector<int> seedSet;
   vector<double> dist;
   vector<int> clean_helper;

   iHeap<double> iheap;
   
   vector<bool> visit;
   vector<int> visit_mark;

   void init_hyper_graph(){
      hyperG.clear();
      for (int i = 0; i < numVert; i++)
         hyperG.push_back(vector<int>());
      hyperGT.clear();
      
      visit = vector<bool> (numVert);
      visit_mark = vector<int> (numVert);
   }
   void build_hyper_graph_r(int64 R)
   {
      // cout<<"now we are build hyper-graph"<<endl;
      if( R > INT_MAX ){
         cout<<"Error:R too large"<<endl;
         exit(1);
      }
      //INFO("build_hyper_graph_r", R);

      

      int prevSize = hyperGT.size();
      while ((int)hyperGT.size() <= R)
         hyperGT.push_back( vector<int>() );



      vector<int> random_number;
      for (int i = 0; i < R; i++)
      {
         random_number.push_back( randx()% numVert);
         random_number.push_back(  sfmt_genrand_uint32(&sfmtSeed) % numVert);
      }

      //trying BFS start from same node
      

      for (int i = prevSize; i < R; i++)
      {
         this->InfGraph::BuildHypergraphNode(random_number[i], i );
      }


      int totAddedElement = 0;
      for (int i = prevSize; i < R; i++)
      {
         for (int t : hyperGT[i])
         {
               hyperG[t].push_back(i);
               //hyperG.addElement(t, i);
               totAddedElement++;
         }
      }
   cout<<"nearly out of hyper graph."<<endl;
   }
/*
	double build_seedset(int k)
	{

		priority_queue<pair<int, int>, vector<pair<int, int>>, CompareBySecond>heap;
		vector<int>coverage(n, 0);

		for (int i = 0; i < n; i++)
		{
			pair<int, int>tep(make_pair(i, (int)hyperG[i].size()));
			heap.push(tep);
			coverage[i] = (int)hyperG[i].size();
		}

		int maxInd;

		long long influence = 0;
		long long numEdge = hyperGT.size();

		// check if an edge is removed
		vector<bool> edgeMark(numEdge, false);
		// check if an node is remained in the heap
		vector<bool> nodeMark(n + 1, true);

		seedSet.clear();
		while ((int)seedSet.size()<k)
		{
			pair<int, int>ele = heap.top();
			heap.pop();
			if (ele.second > coverage[ele.first])
			{
				ele.second = coverage[ele.first];
				heap.push(ele);
				continue;
			}

			maxInd = ele.first;
			vector<int>e = hyperG[maxInd];  
			influence += coverage[maxInd];
			seedSet.push_back(maxInd);
			nodeMark[maxInd] = false;

			for (unsigned int j = 0; j < e.size(); ++j){
				if (edgeMark[e[j]])continue;

				vector<int>nList = hyperGT[e[j]];
				for (unsigned int l = 0; l < nList.size(); ++l){
					if (nodeMark[nList[l]])coverage[nList[l]]--;
				}
				edgeMark[e[j]] = true;
			}
		}
		return 1.0*influence / hyperGT.size();
	}
   */

/*
 * BFS starting from one node
 */

   int BuildHypergraphNode(int uStart, int hyperiiid)
   {
      int n_visit_edge = 1;
         ASSERT((int)this->hyperGT.size() > hyperiiid);
         this->hyperGT[hyperiiid].push_back(uStart);

      int n_visit_mark = 0;
      
      this->q.clear();
      this->q.push_back(uStart);   

      // int expand = this->q.front();
      // printf("assert of %d see n_visit_mark%d see numVert%d", n_visit_mark < this->numVert,n_visit_mark,this->numVert)
      ASSERT(n_visit_mark < this->numVert);
      this->visit_mark[n_visit_mark++] = uStart;

      this->visit[uStart] = true;
      while (!this->q.empty())
      {
         int expand = this->q.front();
         this->q.pop_front();

         int i = expand;
         for (int j = 0; j < (int)this->nxt[i].size(); j++)
         {
            //int u=expand;
            int v = nxt[i][j];
            n_visit_edge++;
            double randDouble = sfmt_genrand_real1(&sfmtSeed);
            if (randDouble > this->nxt_prob[i][j])
               continue;
            if (this->visit[v])
               continue;
            if (!this->visit[v])
            {
               ASSERT(n_visit_mark < n);
               this->visit_mark[n_visit_mark++] = v;
               this->visit[v] = true;
            }
            this->q.push_back(v);
               ASSERT((int)this->hyperGT.size() > hyperiiid);
               this->hyperGT[hyperiiid].push_back(v);
         }
         

      }
      for (int i = 0; i < n_visit_mark; i++)
         this->visit[this->visit_mark[i]] = false;
      // printf("%d is n_visit_edge here\n",n_visit_edge);
      return n_visit_edge;
   }


};


InfGraph buildGraph(string dataset){
   int u,v, numV;
   double p;

   cout << "constructing....\n";
   InfGraph g;
   ifstream infile;
   if(dataset.compare("graph_ic") == 0){
       infile.open("networks/graph_ic.inf"); // with 15229 nodes
   }
   else if(dataset.compare("zachary") == 0){
       infile.open("networks/zachary"); // with 34 nodes
   }
   else if(dataset.compare("zachary_01") == 0){
       infile.open("networks/zachary_01"); // with 34 nodes
   }    
   else{
       
       string file_name = "networks/"+dataset+".txt" ;
       infile.open(file_name); // with 2039 nodes
   }
   

   if (infile.is_open())
   {
      infile >> numV;
      cout<<"add node: "<<numV<<endl;
      for (int i = 0; i < numV; i++){ 
         g.addNode(i);
        //  cout<<"add node: "<<i<<endl;
      }
      
      while(not infile.eof()){
         infile >> u >> v >> p;
         g.addEdge(u,v,p);
         g.addEdge(v,u,p);
         //g2.addEdge(u-1,v-1,p);
         // edge[i].prob = ((double) rand() / (RAND_MAX));
      }
      
      
   }
   infile.close();
   cout <<"done"<<endl;
   return g;
}

InfGraph moveIso(InfGraph g){
    cout<<"going to remove edges"<<endl;
    int count = 0;
    cout<<"there are "<<g.numVert<<" nodes in this dataset"<<endl;
    for(int i=0; i<g.numVert; i++){
        if(g.pre[i].size()==0){
            g.addEdge(g.nxt[i][0],i,0.01);
            count++;
        }

    }
    cout<<"there are "<<count<<" nodes without indegree, has been add input edges"<<endl;
    return g;
}