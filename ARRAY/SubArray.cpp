#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<int> v;
    v = {1, 2, 3, 4, 5, 6, 7, 8};

    for (int i = 0; i < v.size(); i++)
    {
        for (int j = i; j < v.size(); j++)
        {
            for (int k = i; k < j; k++)
            {
                cout << v[k] << " ";
            }
            cout << endl;
        }
    }

    return 0;
}