#include<iostream>

using namespace std;

int main{}{
    auto x = [](int a, int b){return a>b?a:b;};
    int a,b;
    cin >> a >> b;
    cout << x(a,b);
    return 0;
}