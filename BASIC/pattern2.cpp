#include <iostream>

using namespace std;

int main()
{
    int n;
    cout << "Enter the value of n";
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if ((i == 1 || j == 1) || (i == n || j == n))
                cout << "#" << " ";
            else if (i == j)
            {
                cout << "S" << " ";
            }
            else if ((i + j) == n + 1)
            {
                cout << "A" << " ";
            }
            else if (i == n / 2 || j == n / 2)
            {
                cout << "M" << " ";
            }
            else
            {
                cout << " " << " ";
            }
        }

        cout << endl;
    }

    return 0;
}