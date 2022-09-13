#include<iostream>
#include<algorithm>

using namespace std;

int main(){
    int x[3]={1,2,3};
    cout << x <<endl;
    cout << *x <<endl;
    for (int i =0; i < 3; i++){
        cout << x+i << endl;
        cout << *(x+i) << endl;
        cout << x[i] << endl;
        cout << &x[i] << endl;
    }
    return 0;
}