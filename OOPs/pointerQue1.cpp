#include <iostream>
using namespace std;

void f(int *p, int *q)
{
    p = q;
    *q = 2;
    q = p;
    *q = 5;
    *p = *q;
}

int main()
{
    int i = 5, j = 10;
    f(&i, &j);
    printf("%d %d", i, j);
};
