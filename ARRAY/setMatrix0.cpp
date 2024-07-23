#include <iostream>
using namespace std;

int main()
{
    int m, n;
    cout << "Enter the value of m X n" << endl;
    cin >> m >> n;
    int arr[m][n];

    cout << "Enter the Elements of the Array" << endl;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> arr[i][j];
        }
    }

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }


    return 0;
}