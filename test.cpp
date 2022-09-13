#include<iostream>
#include<algorithm>
#include <queue>
#include <set>
#include <vector>
#include <time.h>
#include <cmath>
#include "log.h"

using namespace std;


double count_time(){
    clock_t start_t, end_t;
    double duration;
    start_t = clock();
    cout<<start_t<<endl;
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	for(int i=0; i<100000; i++)
	{
		float y = log(pow(i,5));
	}
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    end_t = clock();
    cout<<end_t<<endl;
    duration = (double)(end_t - start_t) ;
    cout << "Total time taken by CPU: "<<duration <<endl;
    cout << "Time spend: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;

    return duration;
}



// int randx(void) // RAND_MAX assumed to be 32767
// {
//     static unsigned long int num = 1;
//     num = num * 1103515245 + 12345;
//     return (unsigned int)(num/65536) % 32768;
// }

// void srandx(unsigned int seed)
// {
//     static unsigned long int num = 1;

//     num = seed;
// }

int main(){
    /*   
    int zero = 0;
    double name;
    if(zero == 0){
        name = 0;
    }else{
        name = zero*1.0 /10000;
    }
    
    printf("%f is in loop\n",name);
    */
    InfGraph g = buildGraph("starwar_qu");
    // double epsilon_prime = arg.epsilon * sqrt(2);
    // int64 ci = (2+2/3 * epsilon_prime)* ( log(g.numVert) + Math::logcnk(g.numVert, arg.k) + log(Math::log2(g.numVert))) * pow(2.0, x) / (epsilon_prime* epsilon_prime);
    printf("there are %d nodes\n",g.numVert);
    // vector<int> see;
    // see = vector<bool> (10);
    // for (int i = 0; i < see.size(); i++)
    // {         
    //     see[i] = i;         
    // } 
    // printf("does is exist? %d",see[1]);
    int MC = 1000;
    int BUDGET = 111;
    double EPSILON = 0.01;
    int TEST = 5;
    string method = "myopic";
    inPut in ={.BUDGET =BUDGET,.MCROUNDS= MC, .EPSILON = EPSILON,.dataset = "starwar_qu", .SAMPLE_ROUND= 100, .ALPHA = 0.1};
    vector <double> influence(BUDGET);
    // int *counter = (int*)malloc(sizeof(int)*g.numVert);
    queue<int> s;
    s.push(2);

    vector<int> seed = {20, 1, 2, 47, 30, 81, 68, 72, 83, 89, 101, 8, 86, 108, 22, 38, 25, 78, 84, 103, 80, 57, 110, 43, 74, 10, 15, 56, 98, 41, 59, 85, 87, 6, 46, 49, 90, 62, 111, 100, 44, 39, 77, 5, 28, 82, 65, 92, 50, 64, 48, 93, 37, 45, 91, 71, 107, 102, 16, 63, 61, 69, 35, 42, 9, 109, 52, 104, 51, 58, 40, 31, 105, 55, 96, 13, 18, 23, 88, 95, 21, 106, 19, 32, 54, 27, 75, 2, 97, 70, 26, 36, 76, 1, 29, 34, 12, 66, 33, 99, 4, 60, 94, 11, 53, 24, 14, 0, 67, 73};
    vector<double> tim ={0};
    vector<double> maxinf;
    queue<int> myopic_py_select;


    srandx(45);
    cout<<"random generation"<<endl;
    for(int i=0;i<3;i++){
        int name = randx();
        printf("name is: %d",name);
    }
    
    double sprd;
    for(int test = 1; test<=TEST; test++){
        for(int i=0;i<BUDGET;i++){
            int node = seed[i];
            // cout<<seed[i]<<" ";
            myopic_py_select.push(node);
            pair<double,int> round =icExp(g, myopic_py_select, MC,EPSILON);
            maxinf.push_back(round.first);
            printf("selecting node %d with %f influence", i, round.first);
            // float* counter = icExp_hyperG(g, myopic_py_select, MC);
            // double min = *min_element(counter+0,counter+g.numVert);
            // maxinf.push_back(min);
        }
        for(int budget = 0;budget<BUDGET;budget++){
            sprd = maxinf[budget];
            influence[budget] += sprd;
        }  
        printf("we've finished %d round test\n", test);
    }
    for(int budget = 0;budget<BUDGET;budget++){
        influence[budget] = influence[budget]*1.0/TEST;
    }
    values res ={seed,influence,tim};
    logRec(g, res, in, method);
    /*
    for(int i = 0;i<TEST;i++){
        values res = greedy(g, BUDGET, MC, EPSILON);
        for(int j = 0;j<BUDGET;j++){
            double spread = res.inf[j];
            influence[j] += spread;
            cout<<influence[j]<<" ";
        }
        cout<<endl;
    }
    for(int j = 0;j<BUDGET;j++){
        influence[j] = influence[j]*1.0/TEST;
        cout<<influence[j]<<" ";
    }
    cout<<endl;

    

    
    g.init_hyper_graph();
    
    g.build_hyper_graph_r(MC);

    

    printf("what is hyperGT %ld\n",g.hyperGT.size());

    
    //check the hyperG here
    for(int line;line<g.hyperGT.size();line++){
        printf("there are %ld element in %dth hyperGT\n",g.hyperGT[line].size(),line);

        for(const auto& element:g.hyperGT[line]){
            printf("%d ",element);
        }
        cout<<endl;
    }
    
    int node = 5;
    int count = 0;
    for(int line;line<g.hyperGT.size();line++){
        if (std::find(g.hyperGT[line].begin(), g.hyperGT[line].end(),node)!=g.hyperGT[line].end()){
            count++;
        }
    }
    printf("the possibility of node %d exist %f",node,count*1.0/MC);

    */
    
}