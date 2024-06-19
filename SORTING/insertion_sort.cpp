#include <iostream>
#include <Algorithm>
using namespace std;

void insertion(int a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        int j = i;

        while (j > 0 && a[j - 1] > a[j])
        {
            swap(a[j-1], a[j]);
            j--;
        }
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
    insertion(a, n);
    cout << "The Sorted Array is" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }
    return 0;
}