#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

string findLCS(const string &X, const string &Y)
{
    int m = X.length();
    int n = Y.length();

    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (X[i - 1] == Y[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else
            {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    int i = m, j = n;
    string lcs;

    while (i > 0 && j > 0)
    {
        if (X[i - 1] == Y[j - 1])
        {
            lcs.push_back(X[i - 1]); // Add character to LCS
            i--;
            j--;
        }
        else if (dp[i - 1][j] > dp[i][j - 1])
        {
            i--;
        }
        else
        {
            j--;
        }
    }

    reverse(lcs.begin(), lcs.end());

    return lcs;
}

int main()
{
    string X, Y;

    cout << "Enter first sequence: ";
    cin >> X;
    cout << "Enter second sequence: ";
    cin >> Y;

    string lcs = findLCS(X, Y);
    if (lcs.empty())
    {
        cout << "No Common Subsequence found!" << endl;
    }
    else
    {
        cout << "The Longest Common Subsequence is: " << lcs << endl;
    }

    return 0;
}
