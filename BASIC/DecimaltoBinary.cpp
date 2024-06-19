#include <iostream>
#include <stack>
using namespace std;

int main()
{
    cout << "Enter the decimal Number :";
    int n;
    cin >> n;
    

    stack<int> binaryNumbers;
    if (n == 0)
    {
        cout << "0";
        return 0;
    }

    while (n > 0)
    {
       
        int remainder = n % 2;
        binaryNumbers.push(remainder);
        n = n / 2;
    }
    while (!binaryNumbers.empty())
    {
        cout << binaryNumbers.top();
        binaryNumbers.pop();
    }
    return 0;
}