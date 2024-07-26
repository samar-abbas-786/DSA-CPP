#include <iostream>
#include <vector>
using namespace std;

void push(vector<int> &arr, int val)
{
    int top=-1;
    
    // for (int i = 0; i < arr.size(); i++)
    // {
    //     if (arr[i] == -1)
    //     {
    //         arr[i] = val;
    //         break;
    //     }
    // }
}
int pop(vector<int> &arr)
{
    for (int i = 0; i < arr.size() - 1; i++)
    {
        if (arr[i] != -1 && arr[i + 1] == -1)
        {
            return arr[i];
        }
    }
}
void print(vector<int> &arr)
{
    for (int i = 0; i < arr.size(); i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main()
{
    vector<int> arr = {-1, -1, -1, -1, -1, -1};
    cout << endl;
    print(arr);
    push(arr, 8);
    print(arr);
    push(arr, 9);
        push(arr, 11);
    print(arr);

   cout<< pop(arr);

    return 0;
}