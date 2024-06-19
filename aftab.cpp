#include <iostream>
using namespace std;

int main()
{
    int a, b, c;
    cout << "Enter Three Numbers a, b, c" << endl;
    cin >> a >> b >> c;
    cout << endl;

    if (a == b && b == c)
    {
        cout << "All numbers are equal: " << a + b + c << endl;
    }
    else
    {
        if (a != b && b != c && a != c)
        {
            if (a < b && b < c)
            {
                cout << "The difference between the smallest and middle number is: " << b - a << endl;
            }
            else if (b < a && a < c)
            {
                cout << "The difference between the smallest and middle number is: " << a - b << endl;
            }
            else if (c < b && b < a)
            {
                cout << "The difference between the smallest and middle number is: " << b - c << endl;
            }
            else if (a < c && c < b)
            {
                cout << "The difference between the smallest and middle number is: " << c - a << endl;
            }
            else if (c < a && a < b)
            {
                cout << "The difference between the smallest and middle number is: " << a - c << endl;
            }
            else if (b < c && c < a)
            {
                cout << "The difference between the smallest and middle number is: " << c - b << endl;
            }
        }
        else
        {
            if (a == b || b == c)
            {
                cout << "The sum between the smallest and higher number is: " << a + c << endl;
            }
            else if (a == c)
            {
                cout << "The sum between the smallest and higher number is: " << b + c << endl;
            }
            else if (b == c)
            {
                cout << "The sum between the smallest and higher number is: " << a + b << endl;
            }
        }
    }

    return 0;
}
