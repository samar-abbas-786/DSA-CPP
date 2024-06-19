#include <iostream>
using namespace std;

int main()
{

    cout << "Enter the Size of Array" << endl;
    int n;
    cin >> n;
    int arr[n];
    cout << "Enter the Elements" << endl;
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    int largest = arr[0];
    for (int i = 0; i < n; i++)
    {
        if (largest < arr[i])
        {
            largest = arr[i];
        }
    }
    cout << "The Largest Element is " << largest << endl;

    int secondMax = arr[0];

    for (int i = 0; i < n; i++)
    {
        if (arr[i] != largest)
        {
            if (secondMax < arr[i])
            {
                secondMax = arr[i];
            }
        }
    }
    cout << "The Second Largest Element is " << secondMax << endl;

    return 0;
}