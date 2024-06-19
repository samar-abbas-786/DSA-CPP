#include <iostream>
using namespace std;

void merge_sort(int a[], int low, int high)
{

    int mid = (high + low) / 2;
    if (low >= mid)
        return;
    merge_sort(a, low, mid);
    merge_sort(a, mid + 1, high);
    merge(a, low, mid, high);
}
int main()
{
    return 0;
}
