#include <iostream>
#include <vector>
using namespace std;

void push(vector<int> &arr, int val)
{
    // int left = -1;
    int end = -1;
    // if (left == -1 && end == -1)
    // {
    //     left = 0;
    // }
    end++;
    arr[end] = val;
}
void print(vector<int> &arr)
{
    for (int i = 0; i < arr.size(); i++)
    {
        cout << arr[i] << " ";
    }
    // cout << endl;
}

int main()
{
    vector<int> arr = {1,2};
    push(arr, 8);
    push(arr, 5);
    push(arr, 2);
    push(arr, 1);

    print(arr);

    return 0;
}