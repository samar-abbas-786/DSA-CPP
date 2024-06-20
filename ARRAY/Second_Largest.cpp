#include <iostream>
using namespace std;

int largest(int a[], int n)
{
    int large = a[0];
    int i = 0;
    while (i < n)
    {
        if (a[i] > large)
        {
            large = a[i];
        }
        i++;
    }
    // int sec = -1;
    // while (i < n )
    // {
    //     if (a[i] > sec && a[i]!=large)
    //     {
    //         sec = a[i];
    //     }
    //     i++;
    // }

    return large;
}

int main()
{
    int a[] = {3, 2, 5, 3, 99,2, 66, 546, 4, 31};
    int n = sizeof(a) / sizeof(a[0]);
    cout << largest(a, n)<<endl;
    int x=largest(a,n);
    int sec=-1;
    for(int i=0;i<n;i++){
        if(a[i]>sec && a[i]!=x){
            sec=a[i];
        }
    }
  cout<<sec;
    return 0;
}