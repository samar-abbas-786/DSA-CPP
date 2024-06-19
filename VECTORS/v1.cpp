#include <iostream>
#include <vector>
using namespace std;

 vector<int> twoSum(vector<int>& nums, int target) {
        for(int i=0;i<nums.size();i++){
            for (int j=0;j<nums.size();j++){
              if({nums[i]+nums[j]}==target){
                cout<< i+j;
              }
            }
        }
        
    }

int main()
{
    vector<int> v;
    // cout << v.size() << endl;
    // cout << v.capacity() << endl;
    // v.push_back(234);
    // // cout << v << endl;
    // cout << v.size() << endl;
    // // cout << v.begin() << endl;
    for (int i = 0; i < 5; i++)
    {
        int element;
        cin >> element;
        v.push_back(element);
    }
    cout << endl;
    // for (int i = 0; i < v.size(); i++)
    // {

    //     cout << v[i] << " ";
    // }
    for (int ele : v)
    {
        cout << ele << " ";
    }

    return 0;
}