#include <iostream>
#include <vector>
#include <stdio.h>

#include "sfmt/SFMT.h"
using namespace std;
int sfmtSeed;

// std::vector<int> random_number;

void test(){
    cout<<"test on test"<<endl;
}

int main(){
    std::vector<double> random_number;

    sfmt_t sfmtSeed;
    int s;
    test();
    s = sfmt_genrand_uint32(&sfmtSeed);
    // for (int i = 0; i < 10; i++)
    // {
    //     random_number.push_back(  sfmt_genrand_uint32(&sfmtSeed) % 34);
    // }
    cout << "random number as "<< s<<endl;
}
 