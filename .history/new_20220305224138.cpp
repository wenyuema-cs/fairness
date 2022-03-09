#include<iostream>
using namespace std;
int a(int b){
    int k = b;
    k+=2;
    k--;
    return k;
}

int main()
{
    int n = 10;
    for (int i=0;i<n;i+=2){
        n=a(n);
    }
    cout << n << endl;
    cout << "Hello World" << endl;
    return 0;

}