#include <iostream>
#include <vector>
#include <map>
using namespace std;

int main() {
    vector<int> nums = {123, 456, 789}; // Example input
    map<int, int> mpp;
    
    for (int i = 0; i < nums.size(); i++) {
        int a = nums[i] % 10;
        mpp[a] = nums[i]; // Insert key-value pair into the map
    }
    
    // Print the map to verify the result
    for (const auto& pair : mpp) {
        cout << pair.first << " -> " << pair.second << endl;
    }

    return 0;
}
