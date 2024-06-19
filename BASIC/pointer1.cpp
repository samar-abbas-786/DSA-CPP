#include <iostream>
using namespace std;

int main()
{

    int x;
    int *ptr;
    ptr = &x;
    x = 4;
    cout << &x << endl;
    cout << ptr << endl;
    cout << x << endl;
    cout << *ptr << endl;
    return 0;
}