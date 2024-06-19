#include <iostream>
#include <vector>
using namespace std;

void dupl(vector<int> v)
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (v[i] == v[j])
            {
                v.erase(v.end() - j);
            }
        }
    }
};
int main()
{
    vector<int> v = {1, 2, 3, 4, 1};
    dupl(v);
    for (int num : v)
    {
        cout << num << " ";
    }
    return 0;
}