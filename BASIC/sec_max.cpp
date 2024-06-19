#include <bits/stdc++.h>
using namespace std;
#define max(a,b) ((a) > (b) ? (a) : (b))

int main() {     
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        int a[n];
        for(int i=0;i<n;i++){
            cin>>a[i];
        }
        int MAX=0;
        for(int i=0;i<n;i++){
            MAX=max(a[i],MAX);
        }
        int sec_MAX=0;
        for(int i=0;i<n;i++){
            while(a[i]!=MAX){
                sec_MAX=max(a[i],sec_MAX);
            }
        }
        cout<<(MAX+sec_MAX)<<endl;
    }
    
	

}
