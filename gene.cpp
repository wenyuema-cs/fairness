
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main(){
    
    ifstream infile ("data/cit-patent/cit-patent.edges"); // with 34 nodes
    ofstream outfile ("data/cit-patent/cit-patent-ic.edges");
    int u,v;
    double p;
    if (infile.is_open())
    {
        while(not infile.eof()){
        infile >> u >> v ;
        g.addEdge(u,v,p);
      }
      cout <<"done"<<endl;
      
   }
   infile.close();
}