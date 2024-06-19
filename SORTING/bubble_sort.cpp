#include <iostream>
#include <Algorithm>
using namespace std;

void Bubble(int n, int a[])
{
    for (int i = n - 1; i >= 1; i--)
    {
        int didSwap = 0;
        for (int j = 0; j <= i - 1; j++)
        {
            if (a[j] > a[j + 1])
            {
                swap(a[j], a[j + 1]);
                didSwap = 1;
            }
        }
        if (didSwap == 0)
        {
            break;
        }
        cout << "Swapped " << endl;
    }
}

int main()
{
    int n;
    cout << "Enter the Size of the Array" << endl;
    cin >> n;
    int a[n];
    cout << "Enter the Elements of the Array" << endl;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    Bubble(n, a);
    cout << "The Sorted Array is" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }
    return 0;
}