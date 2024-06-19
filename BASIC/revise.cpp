#include <iostream>

using namespace std;

// int func1(int n)
// {
//     if (n == 0)
//     {
//         return 1;
//     }

//     else
//     {
//         return n * func1(n - 1);
//     }
// };

int prime(int x, int y, int sum = 0)
{
    if (x < y)
    {
        if (x % 2 == 0)
            // cout << x << " ";
            sum += x;
        x++;

        return prime(x, y, sum);
    }

    if (x > y)
    {
        if (x % 2 == 0)
            cout << x << " ";
        x--;
        return prime(x, y);
    }
}
int main()
{
    // int a;
    // cout << "Enter the value, you want to find factorial";
    // cin >> a;
    // int result = func1(a);
    // cout << result << endl;

    int a, b;
    cout << "Enter the lower value of a" << endl;
    cin >> a;

    cout << "Enter the lower value of b" << endl;
    cin >> b;
    // if (a < b)
    // {
    prime(a, b);

    // cout << result;
    // }
    // else
    // {
    //     cout << "Lower limit is higer than Upper Limit" << endl;
    // }
    return 0;
}