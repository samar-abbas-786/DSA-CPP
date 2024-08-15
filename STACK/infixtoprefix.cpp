#include <iostream>
#include <stack>
using namespace std;

int Priority(char s)
{

    // if((s[i]>='a' && s[i]<='z') || (s[i]>='0' && s[i]<='9') || ){
    //     return 1;
    // }
    if (s == '^')
    {
        return 3;
    }
    else if (s == '*' || s == '/')
    {
        return 2;
    }
    else if (s == '+' || s == '-')
    {
        return 1;
    }

    return -1;
}

string infixtopostfix(string s)
{

    string ans = "";
    // string s = "a+b*(c^d-e)";
    stack<char> st;

    int i = 0;
    int n = s.length();

    while (i < n)
    {
        if ((s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= 'a' && s[i] <= 'z') || (s[i] >= '0' && s[i] <= '9'))
        {
            ans += s[i];
        }
        else if (s[i] == '(')
        {
            st.push(s[i]);
        }
        else if (s[i] == ')')
        {

            while (!st.empty() && st.top() != '(')
            {
                ans += st.top();
                st.pop();
            }
            st.pop();
        }

        else
        {
            while (!st.empty() && (Priority(s[i]) <= Priority(st.top())))
            {
                ans += st.top();
                st.pop();
            }
            st.push(s[i]);
        }
        i++;
    }
    while (!st.empty())
    {
        ans += st.top();
        st.pop();
    }
    // cout << "Infix :" << s << "To :" << ans;
    return ans;
};
string reverse(string s)
{
    string reversed = "";
    for (int i = s.length() - 1; i >= 0; i--)
    {
        reversed += s[i];
    }
    return reversed;
}
int main()
{
    string s = "a+b*(c^d-e)";
    string str = reverse(s);

    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == '(')
        {
            str[i] = ')';
        }
        else if (str[i] == ')')
        {
            str[i] = '(';
        }
    }
    string new_str = infixtopostfix(str);
    cout << reverse(new_str);
    return 0;
}