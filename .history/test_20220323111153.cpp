#include<iostream>
#include<algorithm>
#include <queue>
#include <set>
#include <time.h>
#include <cmath>

using namespace std;


double count_time(){
    clock_t start_t, end_t, total_t;
    start_t = clock();
    cout<<start_t<<endl;
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	for(int i=0; i<100000; i++)
	{
		floart y = log(pow(i,5));
	}
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    end_t = clock();
    cout<<end_t<<endl;
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    cout << "Total time taken by CPU: "<<total_t <<endl;
    cout << "Time spend: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;

    return total_t;
}
int main(){
    double s = count_time();

}