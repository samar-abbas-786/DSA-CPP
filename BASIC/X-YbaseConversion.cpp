#include <iostream>
#include <stack>
using namespace std;

int main()
{
    cout << "Enter the decimal Number :";
    int n;
    cin >> n;
    cout << "Enter the base Number :";
    int x;
    cin >> x;

    stack<char> binaryNumbers;
    if (n == 0)
    {
        cout << "0";
        return 0;
    }

    while (n > 0)
    {

        int remainder = n % x;
        if (remainder >= 10)
        {
            remainder = char('A' + (remainder - 10));
        }
        else
        {
            remainder = ('0' + remainder);
        }
        binaryNumbers.push(remainder);
        n = n / x;
    }
    while (!binaryNumbers.empty())
    {
        cout << binaryNumbers.top();
        binaryNumbers.pop();
    }
    return 0;
}