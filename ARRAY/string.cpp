#include <iostream>
#include <stack>
#include <vector>

using namespace std;

int main()
{
    stack<char> st;
    vector<char> str;
    string s1 = "AAABBBCCD";
    string s2 = "AB";
    for (int i = 0; i < s1.size(); i++)
    {
        st.push(s1[i]);
    }
    for (int i = 0; i < s2.size(); i++)
    {   
        // if (s2[i] == st.top())
        // {
        //     st.pop();
        // }
        while(s2[i]==st.top()){
            st.pop();
        }
        
      
    }
    cout << "The Resultant String is:";
    for (int i = 0; i < st.size(); i++)
    {
        cout << st.top();
        st.pop();
    }

    return 0;
}
