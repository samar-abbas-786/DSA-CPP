#include <iostream>
using namespace std;

void merge(int a[], int low, int mid, int high)
{
    int i, j, k;
    int n1 = mid - low + 1; // size of  Left Array
    int n2 = high - mid;    // Size of right Array

    int L[n1];
    int R[n2];
    for (int i = 0; i < n1; i++)
    {
        L[i] = a[low + i]; // Copy into Array
    }
    for (int i = 0; i < n2; i++)
    {
        R[i] = a[mid + 1 + i]; // Copy into Array
    }
    i = low;
    j = mid + 1;
    k = low;
    while (n1 > i && n2 > j)
    {

        if (L[i] <= R[j])
        {
            a[k] = L[i];
            i++;
        }
        else if (R[j] <= L[i])
        {
            a[k] = R[j];
            j++;
        }
        k++;
        while (i < n1)
        {
            a[k] = L[i];
            i++;
            k++;
        }
        while (j < n2)
        {
            a[k] = R[j];
            j++;
            k++;
        }
    }
}

void merge_sort(int a[], int low, int high)
{
    if (low < high)
    {
        int mid = (low + high) / 2;
        if (low == mid)
            return;
        merge_sort(a, low, mid);
        merge_sort(a, mid + 1, high);
        merge(a, low, mid, high);
    }
}
int main()
{
    int a[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    merge_sort(a, 0, 9);
    for (int i = 0; i < 10; i++)
    {
        cout << a[i] << " ";
    }
    return 0;
}
