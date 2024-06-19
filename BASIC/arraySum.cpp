#include <iostream>
using namespace std;

int main()
{
    int n;
    cout << "Enter the size of Array" << endl;
    cin >> n;
    int array[n];

    for (int i = 0; i < n; i++)
    {
        cin >> array[i];
        cout << " ";
    }
    int min = array[0];

    for (int i = 0; i < n; i++)
    {
        if (array[i] < min)
        {
            min = array[i];
        }
    }
    cout << "The Minimum of the array is " << min << endl;
    return 0;
}