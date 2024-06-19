#include <iostream>
using namespace std;

int twoSum(int arr[5], int target)
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = i; j < 5; j++)
        {
            if (arr[i] + arr[j] == target)
            {
                cout << "[" << i << "," << j << "]" << endl;
            }
        }
    }
    return -1;
};
int main()
{
    int arr[] = {1, 2, 3, 4, 5};
    twoSum(arr, 5);
    return 0;
}