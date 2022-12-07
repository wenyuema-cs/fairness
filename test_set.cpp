#include "log.h"

int main(){
    set<int> s;
    for(int i;i<10;i++){
        s.insert(i);
    }
    set<int, greater<int> >::iterator i;   
    for(i = s.begin(); i != s.end(); i++){
        // G.erase(*i);
        
        printf("this is node %d\n",*i);
    }    
}