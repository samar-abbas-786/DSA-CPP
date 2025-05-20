#include <iostream>
#include <stack>
using namespace std;

bool func(int n)
{
    stack<int> st;
    while (n > 0)
    {
        int a = n % 10;
        st.push(a);
        n = n / 10;
    }
    int ans = 0;

    //  int count =2;
    while (n > 0)
    {
        int x = st.top();
        st.pop();
        int y = st.top();
        st.pop();
        if (x != 1 && y != 0)
        {
            return false;
        }
        int p = 1;
        int z = st.top();
        st.pop();
        p *= z;
        ans = ans + p;
        p = p * 10;
    }
    if (ans < 2)
    {
        return false;
    }
    // n=1019
    //  st=1 0 1 9
    return true;
}

int main()
{
   bool x= func(1200);
  cout<<x;
    return 0;
}