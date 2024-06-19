#include <iostream>
using namespace std;

int main()
{
    int N;
    cout << "Enter the Size of The Array";
    cin >> N;
    cout << endl;
    int arr[N];

    cout << "Enter the Input Elements of an Array :";
    for (int i = 0; i < N; i++)
    {
        cin >> arr[i];
    }

    // Original array is
    cout << "The Reverse Array is : ";
    for (int i = 0; i < N; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;

    cout << "The Reverse Array is : ";
    for (int i = N - 1; i >= 0; i--)
    {
        cout << arr[i] << " ";
    }
    return 0;
}
