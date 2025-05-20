#include <iostream>
#include <bits/stdc++.h>
#include <vector>
using namespace std;

void printNUmber(int n)
{
    cout << n << " ";
    if (n > 0)
    {
        printNUmber(n - 1);
    }
}

int factorial(int n)
{
    if (n == 0 || n == 1)
    {

        return 1;
    }
    return n * factorial(n - 1);
}

bool isSorted(vector<int> &arr, int n)
{
    if (n == 0 || n == 1)

    {
        return true;
    }

    return arr[n - 1] >= arr[n - 2] && isSorted(arr, n - 1);
}

int fabonacci(int n)
{
    if (n == 1 || n == 0)
    {
        return n;
    }

    return fabonacci(n - 1) + fabonacci(n - 2);
}

int RecursiveBinarySearch(int l, int r, vector<int> &arr, int target)
{

    int mid = l + (r - l) / 2;
    if (arr[mid] == target)
    {
        return mid;
    }
    if (arr[mid] > target)
    {
        return RecursiveBinarySearch(0, mid - 1, arr, target);
    }
    return RecursiveBinarySearch(mid + 1, r, arr, target);
}

void printSubsets(vector<int> &arr, vector<int> &ans, int i)
{
    if (i == arr.size())
    {
        for (int val : ans)
        {
            cout << val << " ";
        }
        cout << endl;
        return;
    }
    // Include Elemets
    ans.push_back(arr[i]);
    printSubsets(arr, ans, i + 1);
    ans.pop_back(); // Backtracking step
    printSubsets(arr, ans, i + 1);
}
double myPow(int x, int n)
{
    if (n == 0)
    {
        return 1.00;
    }
    return float(x * myPow(x, n - 1));
}
int main()
{
    // int n;
    // cout << "Enter the Number" << endl;
    // cin >> n;
    // // printNUmber(n);
    // cout << fabonacci(n);
    // vector<int> arr = {1, 2, 3};
    // vector<int> ans;
    // printSubsets(arr, ans, 0);

    // cout << isSorted(arr, 5);
    // cout << RecursiveBinarySearch(0, arr.size(), arr, 9);
    cout << myPow(6.1, 3);
    return 0;
}