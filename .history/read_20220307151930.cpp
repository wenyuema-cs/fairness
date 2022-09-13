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
    string start_ver, end_ver, weight;
};

int main()
{
   string line;
   stringstream sstream(line);
   string space_char = " ";
   vector<string> edge;
   graphEdge edges;
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
   ifstream infile ("data.txt");
   
   if (infile.is_open())
   {
      while (getline (infile,line) )
      {
         line.erase(remove_if(line.begin(), line.end(),::isspace),line.end());
         //edge.push_back(line);
         edges.start_ver
         cout << typeid(edge).name() << '\n';
         for (const auto &str : edge){
         cout << str <<endl;
         }
         
         // size_t pos = 0;
         // while((pos = line.find(space_delimiter) != string :: npos)){
         //    words.push_back(line.substr(0,pos));
         //    text.erase(0,pos + space_delimiter.length());
      }
       // edges[infile] = {line}
      
       
   }
    infile.close();
  

  // else cout << "Unable to open file"; 

  return 0;
   
   // Graph G(in), H(in);

   // G.write( cout );
   // cout << "\n\n";
   // H.write( cout );
}