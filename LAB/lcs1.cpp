#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector<vector<int>> computeLCS(const string& seq1, const string& seq2) {
    int m = seq1.length();
    int n = seq2.length();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    // Fill DP table
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (seq1[i - 1] == seq2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    return dp;
}

void printIntermediateSteps(const vector<vector<int>>& dp, const string& seq1, const string& seq2) {
    int m = seq1.length();
    int n = seq2.length();

    cout << "    ";
    for (int j = 0; j < n; ++j) {
        cout << "  " << seq2[j] << " ";
    }
    cout << endl;

    for (int i = 0; i <= m; ++i) {
        if (i > 0) {
            cout << seq1[i - 1] << " ";
        } else {
            cout << "  ";
        }
        for (int j = 0; j <= n; ++j) {
            cout << dp[i][j] << "  ";
        }
        cout << endl;
    }
}

string backtrackLCS(const vector<vector<int>>& dp, const string& seq1, const string& seq2) {
    int i = seq1.length();
    int j = seq2.length();
    string lcs = "";

    cout << "Backtracking Steps:\n";
    while (i > 0 && j > 0) {
        if (seq1[i - 1] == seq2[j - 1]) {
            lcs = seq1[i - 1] + lcs; 
            cout << "Move ↖ from (" << i << "," << j << ")\n";
            i--;
            j--;
        } else if (dp[i - 1][j] >= dp[i][j - 1]) {
            cout << "Move ↑ from (" << i << "," << j << ")\n";
            i--;
        } else {
            cout << "Move ← from (" << i << "," << j << ")\n";
            j--;
        }
    }

    return lcs;
}

void visualBacktrack(const vector<vector<int>>& dp, const string& seq1, const string& seq2) {
    int i = seq1.length();
    int j = seq2.length();

    cout << "Visual Backtracking:\n";
    while (i > 0 && j > 0) {
        cout << "At position (" << i << "," << j << "): ";
        if (seq1[i - 1] == seq2[j - 1]) {
            cout << "Match '" << seq1[i - 1] << "', move ↖\n";
            i--;
            j--;
        } else if (dp[i - 1][j] >= dp[i][j - 1]) {
            cout << "Move ↑\n";
            i--;
        } else {
            cout << "Move ←\n";
            j--;
        }
    }
}

int main() {
    string seq1, seq2;
    
    // Input sequences
    cout << "Enter Sequence 1: ";
    cin >> seq1;
    
    cout << "Enter Sequence 2: ";
    cin >> seq2;

    // Compute LCS
    vector<vector<int>> dp = computeLCS(seq1, seq2);

    // Display intermediate DP table
    printIntermediateSteps(dp, seq1, seq2);

    // Backtrack and display LCS
    string lcs = backtrackLCS(dp, seq1, seq2);
    cout << "\nLCS: " << lcs << endl;

    // Visual backtracking via console
    visualBacktrack(dp, seq1, seq2);

    return 0;
}
