#include <iostream>
#include <unordered_map>
using namespace std;
int main()
{
    unordered_map<int, int> mpp;
    int arr[] = {1, 1, 2, 4, 4, 3, 3, 2, 2};

    for (int i = 0; i < 9; i++)
    {
        mpp[arr[i]]++;
    }
    for (auto it : mpp)
    {
        cout << it.first << "->" << it.second << endl;
    }
   
    return 0;
}