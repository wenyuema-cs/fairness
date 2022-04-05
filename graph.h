#include <vector>
using namespace std;

struct values
{
   set<int> sed;
   vector<double> inf;
   vector<double> time;
};

struct valuesRR
{
   set<int> sed;
   vector<int> seed;
   // vector<double> inf;
   vector<double> time;
};

struct inPut{
   int BUDGET ;
   int MCROUNDS ;
   double EPSILON ;

   int SAMPLE_SIZE;
   int SAMPLE_ROUND ;
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
Graph buildGraph(string dataset){
   int u,v, numV;
   double p;

   cout << "constructing....\n";
   Graph g;
   ifstream infile;
   if(dataset.compare("graph_ic") == 0){
       infile.open("networks/graph_ic.inf"); // with 15229 nodes
   }
   else if(dataset.compare("zachary") == 0){
       infile.open("networks/zachary"); // with 34 nodes
   }   
   else{
       
       string file_name = "networks/"+dataset+".txt" ;
       cout << "for fatemeh " << file_name << endl;
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
         //g.addEdge(v,u,p);
         //g2.addEdge(u-1,v-1,p);
         // edge[i].prob = ((double) rand() / (RAND_MAX));
      }
      
      
   }
   infile.close();
   cout <<"done"<<endl;
   return g;
}

Graph moveIso(Graph g){
    cout<<"going to remove edges"<<endl;
    int count = 0;
    cout<<"there are "<<g.numVert<<" nodes in this dataset"<<endl;
    for(int i=0; i<g.numVert; i++){
        if(g.pre[i].size()==0){
            if(i == 0){
                g.addEdge(i+1,i,0.01);
            }
            else{
                g.addEdge(i-1,i,0.01);
            }
            count++;
        }

    }
    cout<<"there are "<<count<<" nodes without indegree, has been add input edges"<<endl;
    return g;
}
