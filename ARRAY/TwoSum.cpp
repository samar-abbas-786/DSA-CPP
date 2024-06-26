#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> twoSum(vector<int> &nums, int target)
{
    vector<pair<int,int>> temp;
    for(int i=0;i<nums.size();i++){
        temp.push_back({nums[i],i});
    }
    
    sort(temp.begin(), temp.end());

    int left = 0;
    int right = temp.size() - 1;
    while (left < right)
    {
        if ((temp[left].first + temp[right].first) == target)
           return {temp[left].second,temp[right].second};

        else if ((temp[left].first + temp[right].first) < target)
        {
            left++;
        }
        else
        {
            right--;
        }
    }
    
   
    return {-1,-1};
}

int main()
{

    vector<int> v;
    v = {1,2,3,4,5};
    vector<int> result = twoSum(v, 5);
    cout<<"{";
    for (int i = 0; i < result.size(); i++)
    {
        cout << result[i] << ",";
    }
    cout<<"}";
    return 0;
}