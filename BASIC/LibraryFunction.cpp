#include <bits/stdc++.h>
#include <cmath>
#include <iostream>
using namespace std;

// void swap(int &x, int &y)
// {
//     cout << &x;
//     x = x + y;
//     y = x - y;
//     x = x - y;
//     // cout << x << " " << y << endl;

//     return;
// }

int main()
{
    priority_queue<int> pq;
    pq.push(1);
    pq.push(4);
    pq.push(3);
    cout << pq.size() << endl;
    for (int i = 0; i < pq.size(); i++)
    {
        cout << pq.top() << " ";
        pq.pop();
    }
    unordered_set<int> ust;
    ust.insert(1);
    ust.insert(2);
    ust.insert(3);
    ust.insert(4);
    ust.find(1);

    //     // cout << "Enter the Number; " << endl;
    //     // int n;
    //     // cin >> n;
    //     // cout << sqrt(n) << endl;
    //     // cout << cbrt(n) << endl;

    //     // cout << pow(n, 2) << endl;

    //     int a = 15;
    //     int b = 25;
    //     cout << &a;

    //     cout << a << " " << b << endl;
    //     swap(a, b);

    //     cout << a << " " << b << endl;

    return 0;
}