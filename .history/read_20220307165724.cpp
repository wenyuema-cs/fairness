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

struct graphEdge {
    int start_ver, end_ver;
    double prob;
};



int main()
{
   graphEdge edge[16];
   ifstream infile ("data.txt");
   
   if (infile.is_open())
   {
      for(int i=0; i < 16; i++){
         infile >> edge[i].start_ver >> edge[i].end_ver >> edge[i].prob;
         //edge[i].prob = ((double) rand() / (RAND_MAX));
         cout << edge[i].start_ver << " " << edge[i].end_ver << " " << edge[i].prob << endl;
      }
   }
   infile.close();

  return 0;

}