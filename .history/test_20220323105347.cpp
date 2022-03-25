#include<iostream>
#include<algorithm>
#include <queue>
#include <set>
#include <time.h>

using namespace std;


int count_time(){
    clock_t start_t, end_t, total_t;
    start_t = clock();
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    for (int i = 0; i < 3; i++){
            cout<<i<<" ";

    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    end_t = clock();
    int time = duration_cast<std::chrono::microseconds>(end - begin).count();
    cout << "Time spend: " << time << "[µs]" << std::endl;

    cout << "Time spend: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;

    return time;
}
int main(){
    s = count_time();

}