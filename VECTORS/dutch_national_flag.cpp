#include <iostream>
#include <vector>
using namespace std;

void helper(vector<int> &nums, int l, int h)
{
    int mid = l;

    while (mid <= h)
    {

        if (nums[mid] == 0)
        {
            swap(nums[l], nums[mid]);
            l++;
            mid++;
        }

        else if (nums[mid] == 2)
        {
            swap(nums[h], nums[mid]);
            h--;
        }
        else
        {
            mid++;
        }
    }
}

int main()
{
    vector<int> nums = {0, 1, 1, 2, 0, 1, 0, 0, 2, 2, 0, 1};
    int low = 0;
    int high = nums.size() - 1;
    helper(nums, low, high);

    for (int i = 0; i < nums.size(); i++)
    {
        cout << nums[i] << " ";
    }

    return 0;
}