#include<iostream>
using namespace std;
int sum(int n){
    int s=0;
    if(n==0) return s;
    s=n+sum(n-1);
    return s;
}
int main(){
    cout<<sum(2000);
    return 0;
}