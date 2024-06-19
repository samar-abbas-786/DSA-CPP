#include <iostream>
using namespace std;

int main()
{
    char a[] = "gate2011";

    printf("\n%c", a[3] + 3);
    printf("%s", a + a[3] - a[1]);
    printf("\n%c", a[3] + 3);
    printf("\n%d", a[3] + 3);
    printf("\n%s", "gate2011");
    printf("\n%s", a);
    // printf("\n%s",1000); 1000 is base address
}
