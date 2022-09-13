#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
using namespace std;

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

int main()
{
   // istringstream in( "6 9    \n"
   //                   "1 2 2  \n"
   //                   "1 3 4  \n"
   //                   "2 3 1  \n"
   //                   "2 4 4  \n"
   //                   "2 5 2  \n"
   //                   "3 5 3  \n"
   //                   "4 6 2  \n"
   //                   "5 4 3  \n"
   //                   "5 6 2  \n"
   //                   "       \n"
   //                   "5 7    \n"
   //                   "1 2 10 \n"
   //                   "1 4 30 \n"
   //                   "1 5 100\n"
   //                   "2 3 50 \n"
   //                   "3 5 10 \n"
   //                   "4 3 20 \n"
   //                   "4 5 60 \n" );
   ifstream in infile("data.txt");
   Graph G(in), H(in);

   G.write( cout );
   cout << "\n\n";
   H.write( cout );
}