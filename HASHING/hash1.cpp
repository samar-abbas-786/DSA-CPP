#include <iostream>
#include <algorithm>
#include <limits.h>
using namespace std;
int main()
{
    int a[] = {1, 2, 3, 4, 5, 6, 7};
    int max_value = 0;
    int n = sizeof(a) / sizeof(a[0]);
    for (int i = 0; i < n; i++)
    {
        max_value = max(max_value, a[i]);
    }

    int hash[max_value] = {0};
    for (int i = 0; i < max_value; i++)
    {
        hash[a[i]] += 1;
    }

    for (int i = 0; i < max_value; i++)
    {
        cout << hash[i] << " ";
    }
    return 0;
}