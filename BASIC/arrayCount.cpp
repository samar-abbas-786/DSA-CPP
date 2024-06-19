#include <iostream>
using namespace std;

int main()
{
    int n;
    cout << "Enter the size of th Arrays: ";
    cin >> n;

    int Arr[n];
    int target;
    cout << "Enter the Target Element";
    cin >> target;

    for (int i = 0; i < n; i++)
    {
        cin >> Arr[i];
    }
    cout << endl;

    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if (Arr[i] > target)
        {
            count++;
        }
    }
    cout << "The number of Elements greater than  " << target << "is :" << count << endl;
    return 0;
}