#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <typeinfo>
#include <string>
#include <string>
#include <sstream>
#include <iterator>
#include <vector>
#include <algorithm>
using namespace std;

//======================================================================
class Graph
{
   int numVert;
   vector< vector<int> > adj;

public:
   Graph( istream &in  );
   void write( ostream &out );
};

Graph::Graph( istream &in )
{
   int nedge, a, b, cost;
   in >> numVert >> nedge;
   adj = vector< vector<int> >( numVert, vector<int>( numVert, 0 ) );
   for ( int i = 0; i < nedge; i++ )
   {
      in >> a >> b >> cost;
      adj[a-1][b-1] = cost;
//    adj[b-1][a-1] = cost;            // need this as well if graph is undirected
   }
}

void Graph::write( ostream &out )
{
   for ( int i = 0; i < numVert; i++ )
   {
      for ( int j = 0; j < numVert; j++ ) out << setw( 2 ) << adj[i][j] << ' ';
      out << '\n';
   }
}

//======================================================================

struct graphEdge {
    int start_ver, end_ver, weight;
};

void tokenize(string s, string del = " ")
{
    int start = 0;
    int end = s.find(del);
    while (end != -1) {
        cout << s.substr(start, end - start) << endl;
        start = end + del.size();
        end = s.find(del, start);
    }
    // cout << s.substr(start, end - start);
   //return s;
}

int main()
{
   graphEdge edge;
   ifstream infile ("data.txt");
   
   if (infile.is_open())
   {
      for(int i=0; i < 16; i++){
         infile >> edge.start_ver >> edge.end_ver >> edge.weight;
         cout << edge.start_ver << " " << edge.end_ver << " " << edge.weight << endl;
      }
      cout<<edge<<endl
   }
   infile.close();
  //

  // else cout << "Unable to open file"; 

  return 0;
   
   // Graph G(in), H(in);

   // G.write( cout );
   // cout << "\n\n";
   // H.write( cout );
}