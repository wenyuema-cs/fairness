#include <vector>
#include <iostream>

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
   // in >> numVert >> nedge;
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