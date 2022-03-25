#include<iostream>
#include<algorithm>
#include <queue>
#include <set>

using namespace std;

int main(){
    auto timenow = chrono::system_clock::to_time_t(chrono::system_clock::now());
    for (int i = 0; i < 3; i++){
            cout<<i<<" ";

    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    cout << "Time spend: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;

}