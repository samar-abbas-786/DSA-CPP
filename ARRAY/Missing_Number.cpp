#include <iostream>
#include <vector>
using namespace std;
int findMissing(vector<int> &arr, int n)
{
    int sum = n * (n + 1) / 2;
    int s2 = 0;
    for (int i = 0; i < n; i++)
    {
        s2 =s2+ arr[i];
    }
    return (sum - s2);
}

int main()
{
    vector<int> a = {1, 2, 3, 4, 5, 6, 8};
    int n = sizeof(a) / sizeof(a[0]);
    int x = findMissing(a, n);
    cout << x;
    return 0;
}