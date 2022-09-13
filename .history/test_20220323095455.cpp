#include<iostream>
#include<algorithm>
#include <queue>
#include <set>

using namespace std;

int main(){

    for (int i = 0; i < 3; i++){
            cout<<i<<" ";

    }
    cout << "Time spend: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;

}