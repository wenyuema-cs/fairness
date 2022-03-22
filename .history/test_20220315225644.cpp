#include<iostream>
#include<algorithm>
#include <queue>
#include <set>

using namespace std;

int main(){
   set<int> S, G;
   S.insert(3);
   for(int i; i<=6;i++){
       G.insert(i);
   }
   set<int, greater<int> >::iterator i;
   set<int, greater<int> >::iterator j;
   
    for (j = S.begin(); j != S.end(); j++){
        G.erase(j);
    }
    for(i = G.begin(); i!=G.end();i++){
        cout<<*i<<" ";
    }
    
    cout << endl;

    return 0;
}