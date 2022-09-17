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
    InfGraph g = buildGraph("star");
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
    int BUDGET = 109;
    double EPSILON = 0.01;
    int TEST = 10;
    string method = "myopic_python";
    inPut in ={.BUDGET =BUDGET,.MCROUNDS= MC, .EPSILON = EPSILON,.dataset = "star", .SAMPLE_ROUND= 100, .ALPHA = 0.1};
    vector <double> influence(BUDGET);
    // int *counter = (int*)malloc(sizeof(int)*g.numVert);
    queue<int> s;
    s.push(2);
    vector<int> star_seed = {17,5,22,25,44,45,59,65,66,71,82,83,87,88,89,93,99,102,106,107,76,86,81,2,100,50,75,104,27,60,48,55,95,84,7,58,35,12,101,68,61,79,56,36,13,54,108,41,39,98,72,63,77,53,29,43,62,52,78,97,90,28,34,6,49,74,33,19,37,9,23,92,32,69,18,96,40,105,3,30,1,85,94,109,46,42,47,51,16,80,10,21,24,38,91,26,15,73,103,8,57,20,67,31,70,11,0,64,4};
    vector<int> star1000_seed = {17, 59, 62,76, 82, 84, 86, 97, 95, 105, 2, 12, 35, 36, 53, 68, 78, 25, 71, 75, 87, 101, 56, 61, 79, 83, 102, 24, 43, 54, 108, 27, 32, 107, 65, 81, 98, 5, 39, 41, 72, 90, 100, 34, 80, 88, 106, 44, 47, 49, 28, 55, 60, 93, 46, 48, 69, 77, 7, 18, 99, 38, 9, 37, 42, 50, 58, 103, 19, 52, 94, 6, 13, 30, 74, 85, 92, 109, 15, 20, 45, 96, 104, 16, 40, 31, 89, 22, 51, 3, 10, 23, 67, 11, 66, 29, 26, 33, 57, 91, 73, 8, 0, 21, 1, 4, 63, 14, 64, 70};
    vector<int> seed_starwar_qu = {20, 1, 2, 47, 30, 81, 68, 72, 83, 89, 101, 8, 86, 108, 22, 38, 25, 78, 84, 103, 80, 57, 110, 43, 74, 10, 15, 56, 98, 41, 59, 85, 87, 6, 46, 49, 90, 62, 111, 100, 44, 39, 77, 5, 28, 79, 82, 65, 92, 50, 64, 48, 93, 37, 45, 91, 71, 107, 102, 16, 63, 61, 69, 35, 42, 9, 109, 52, 104, 51, 58, 40, 31, 105, 55, 96, 13, 18, 23, 88, 95, 21, 106, 19, 32, 54, 27, 75, 2, 97, 70, 26, 36, 76, 1, 29, 34, 12, 66, 33, 99, 4, 60, 94, 11, 53, 24, 14, 0, 67};
    vector<double> tim ={0};
    vector<double> maxinf;
    queue<int> myopic_py_select;


    // srandx(time(NULL));
    // srand (time(NULL));
    cout<<"random generation"<<endl;
    for(int i=0;i<100;i++){
        int name = randx();
        double fix = randam();
        printf("name is: %d ",name);
        printf( "fix is %f\n",fix);
    }
    
    double sprd;
    
    for(int i = 1;i<TEST;i++){
        for(int i=0;i<star1000_seed.size();i++){
            int node = star1000_seed[i];
            // cout<<seed[i]<<" ";
            // myopic_py_select.push(node);
            // pair<double,int> round =icExp_lazy(g, myopic_py_select, MC,EPSILON);
            // maxinf.push_back(round.first);
            myopic_py_select.push(node);
            float* counter = icExp_lazy(g, myopic_py_select, MC);
            // // printf("in budget %d",i);
            // for(int j =0;j<g.numVert;j++){
            //     // const auto& count = count/mc;
            //     if(counter[j] ==0){
            //         cout<<counter[j]<<" " << j << " ";

            //     }

            // }
            
            double min_expect = *min_element(counter+0, counter+g.numVert);
            min_expect = min_expect*1.0/MC;

            maxinf.push_back(min_expect);
            // printf("selecting node %d with %f influence\n", i, min_expect);
            // float* counter = icExp_hyperG(g, myopic_py_select, MC);
            // double min = *min_element(counter+0,counter+g.numVert);
            // maxinf.push_back(min);
        }
        for(int j = 0;j<BUDGET;j++){
            sprd = maxinf[j];
            // double clock = res.time[j];
            
            influence[j] += sprd;
            // time[j] += clock;
        }  
      printf("we've finished %d round test\n",i);


    }      
    for(int j = 0;j<BUDGET;j++){
        influence[j] = influence[j]*1.0/TEST;
        // time[j] = time[j]*1.0/TEST;
    }
    values res ={star1000_seed,influence,tim};
    logRec(g, res, in, method);
    /**/
    
}



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
    
