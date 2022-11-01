#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stack>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */ 
    stack<int> s1, s2;
    int num_operations;
    cin>>num_operations;
    int Q_operation, x;
    for(int i=0; i<num_operations; i++){
        cin>>Q_operation;
        if(Q_operation == 1){
            cin>>x;
            s1.push(x);
        }
        if(Q_operation == 2){
            if(!s2.empty()){
                s2.pop();
            }
            else{
                while(!s1.empty()){
                    s2.push(s1.top());
                    s1.pop();
                }
                s2.pop();
            }
        }
        if(Q_operation == 3){

            if(!s2.empty()){
            cout<<s2.top()<<endl;
            }
            else{
                while(!s1.empty()){
                    s2.push(s1.top());
                    s1.pop();
                }
                cout<<s2.top()<<endl;
            }
        }
    }
    
    return 0;
}