#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int start_index = 0;
    int max_sum = -1000;
    int last_index = 0;
    vector<int> v;
    v = {2, 8, -3, -4, -5, 6, -7, 8};

    for (int i = 0; i < v.size(); i++)
    {
        for (int j = i; j < v.size(); j++)
        {
            int curr_sum = 0;

            for (int k = i; k <= j; k++)
            {
                curr_sum += v[k];
                 }
                if (curr_sum >= max_sum){
                    max_sum=curr_sum;
                    start_index = i;
                last_index = j;
                }
        }
    }
    for (int h = start_index; h <= last_index; h++)
    {
        cout << v[h] << " ";
    }

    return 0;
}