#include<iostream>
#include<algorithm>
#include <queue>
#include <set>

using namespace std;

int main(){
   set<int> S, G;
   for(int i; i<6;i++){
       G.insert(i);
   }
   for (itr = G.begin(); itr != G.end(); itr++) {
        cout << *itr << " ";
    }
    cout << endl;

    return 0;
}