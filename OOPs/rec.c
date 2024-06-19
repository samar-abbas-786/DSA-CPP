#include <stdio.h>
void main()
{
    int arr[6] = {3, 5, 6, 3, 5, 6};

    while (i < j)
    {
        for (int i = 0; i < 6; i++)
        {
            arr[i] = arr[6 - 1 - i];
        }
    }
    for (int i = 0; i < 6; i++)
    {
        printf("%d", arr[6]);
    }
}