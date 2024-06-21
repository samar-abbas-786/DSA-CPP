#include <iostream>
#include <vector>
using namespace std;
    // int removeElement(int nums[], int val) {
    //     int i=0;
    //     for(int j=0;j<nums.length();j++){
    //         if(nums[j]==val){
              
                
    //         }
    //         else{
    //             i++
    //         }
           
           
    //     }
    // }
    // return i;


int main()
{ int val=4;

    int a[] = {1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4};
    int n = sizeof(a) / sizeof(a[0]);
     int i=0;
        for(int j=0;j<n;j++){
            if(a[j]==val){
              
                
            }
            else{
                i++;
            }
           
           
        }
   cout<<i;
    return 0;
}