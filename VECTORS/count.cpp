#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    int n;
    cout << "Enter number" << endl;
    cin >> n;
    int ans = log(n) / log(10) + 1;
    cout << ans;
    return 0;
}