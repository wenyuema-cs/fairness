#include<iostream>
#include<algorithm>
#include <queue>

using namespace std;

int main(){
    queue<int> q;
    q.push(1);
    q.push(2);
    queue<int> p=q;
    p.pop();
    p.pop();
    cout << q.front() <<endl;

    return 0;
}