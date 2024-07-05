#include <iostream>
#include <vector>
using namespace std;
class Solution
{
public:
    int removeDuplicates(vector<int> &nums)
    {

        for (int i = 1; i < nums.size() - 1; i++)
        {
            if (nums[i - 1] == nums[i] && nums[i] == nums[i + 1])
            {
                nums.pop_back();
            }
        }
        return -1;
    }
};
int main()
{
    vector<int> v;
    v = {1, 2, 2, 2, 4, 4, 4, 4, 5, 5, 5};
    vector<int> result = removeDuplicates(v);

    return 0;
}