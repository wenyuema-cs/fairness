#include<iostream>
#include<algorithm>
#include <queue>
#include <set>
#include <vector>
#include <time.h>
#include <cmath>
// #include "log.h"
// #include "expect.h"
#include "strategies.h"

using namespace std;


void log(Graph g, values res, inPut in, string method){
    
    std::ofstream myfile;
    myfile.open ("log/"+in.dataset+"_"+method+".csv");
    myfile << "k;seed;inf;tim\n";
    for(int i = 0;i<in.BUDGET;i++){
        myfile << to_string(i)+";"+to_string(res.sed[i])+";"+to_string(res.inf[i])+";"+to_string(res.time[i])+"\n";
    }
    // myfile << "This is the first cell in the first column.\n";
    // myfile << "a,b,c,\n";
    // myfile << "c,s,v,\n";
    // myfile << "1,2,3.456\n";
    // myfile << "semi;colon";
    myfile.close();

}


int main(){
    int MCROUNDS =3;
    int BUDGET = 100;
    double EPSILON = 0.01;
    string method = "greedy";
    values res;
    // queue<int> s;

    InfGraph g = buildGraph("star");
    
    inPut in ={.BUDGET =BUDGET,.MCROUNDS= MCROUNDS, .EPSILON = EPSILON,.dataset = "star", .SAMPLE_ROUND= 100, .ALPHA = 0.1};
    res = greedy(g, BUDGET, MCROUNDS, EPSILON);

    log(g,res,in,method);

}