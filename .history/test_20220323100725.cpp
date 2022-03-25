#include<iostream>
#include<algorithm>
#include <queue>
#include <set>

using namespace std;
using namespace chrono;

int main(){
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    for (int i = 0; i < 3; i++){
            cout<<i<<" ";

    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
    cout << "Time spend: " << time << "[µs]" << std::endl;

    cout << "Time spend: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;

}