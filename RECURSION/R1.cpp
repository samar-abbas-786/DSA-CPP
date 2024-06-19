#include <iostream>
#include <vector>
using namespace std;

int main()
{

    vector<int> v;

    // for loop
    for (int i = 0; i < 5; i++)
    {
        int elements;
        cin >> elements;
        v.push_back(elements);
    }
    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i] << ' ';
    }
    cout << endl;
    // for each loop

    for (int ele : v)
    {
        cout << ele << " ";
    }
    cout << endl;
    // While Loop
    int idx = 0;
    while (idx < v.size())
    {
        cout << v[idx++] << " ";
    }
    return 0;
}