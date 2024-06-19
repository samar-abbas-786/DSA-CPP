#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int QS_Partition(int a[], int low, int high)
{
    int pivot = a[low];
    int i = low;
    int j = high;
    while (i < j)
    {
        while (a[i] <= pivot && i <= high )
        {
            i++;
        }
        while(a[j] > pivot && j > low )
        {
            j--;
        }
        if (i < j)
        {
            swap(a[i], a[j]);
        }
    }
    swap(a[low], a[j]);

    return j;
}

void QS(int a[], int low, int high)
{
    if (low < high)
    {
        int partition_index = QS_Partition(a, low, high);
        QS(a, low, partition_index - 1);
        QS(a, partition_index + 1, high);
    }
}
int main()
{
    int a[] = {3, 1, 4, 6, 9, 1, 4, 8, 11, 21};
    int n = sizeof(a) / sizeof(a[0]);
    QS(a, 0, n-1);
    for (int i = 0; i < 10; i++)
    {
        cout << a[i] << " ";
    }
    return 0;
}