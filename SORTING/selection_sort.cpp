#include <iostream>
#include <algorithm> // For std::swap

using namespace std;

int main()
{
    cout << "Enter the size of the Array" << endl;
    int n;
    cin >> n;
    int arr[n];

    cout << "Enter the Elements of the Array" << endl;
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    cout << endl;

    for (int i = 0; i < n - 1; i++)
    {
        int MIN = i;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[MIN])
            {
                MIN = j;
            }
        }
        swap(arr[i], arr[MIN]);
    }
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }

    return 0;
}