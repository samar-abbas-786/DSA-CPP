#include <iostream>

using namespace std;

int func(char s, int n)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cout << s << "  ";
        }
        cout << endl;
    }
}

int main()
{
    int n;
    char s;

    cin >> n;
    cin >> s;
    func(s, n);
    cout << "My Name is Samar Abbas" << endl;
    func('#', n);

    return 0;
}