#include<iostream>
#include<algorithm>
#include <queue>
#include <set>
#include <time.h>

using namespace std;


double count_time(){
    clock_t start_t, end_t, total_t;
    start_t = clock();
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    for (int i = 0; i < 3; i++){
            cout<<i<<" ";

    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("Total time taken by CPU: %d\n", total_t  );
    cout << "Time spend: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;

    return total_t;
}
int main(){
    double s = count_time();

}