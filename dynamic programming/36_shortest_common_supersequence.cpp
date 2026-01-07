/*
    Shortest Common Supersequence
    Problem: Find shortest string that has both s1 and s2 as subsequences.
    
    Example: s1 = "abac", s2 = "cab" → Output: "cabac" (length 5)
    Formula: len(SCS) = len(s1) + len(s2) - len(LCS)
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<vector<int>> dp;
    string s1, s2;
    
    int lcs(int i, int j) {
        if (i < 0 || j < 0) return 0;
        if (dp[i][j] != -1) return dp[i][j];
        
        if (s1[i] == s2[j]) {
            return dp[i][j] = 1 + lcs(i - 1, j - 1);
        }
        return dp[i][j] = max(lcs(i - 1, j), lcs(i, j - 1));
    }
    
public:
    int shortestLength(string& str1, string& str2) {
        s1 = str1; s2 = str2;
        int n = s1.length(), m = s2.length();
        dp.assign(n, vector<int>(m, -1));
        return n + m - lcs(n - 1, m - 1);
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    int shortestLength(string& s1, string& s2) {
        int n = s1.length(), m = s2.length();
        
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (s1[i - 1] == s2[j - 1]) {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        
        return n + m - dp[n][m];
    }
    
    // Print the SCS
    string printSCS(string& s1, string& s2) {
        int n = s1.length(), m = s2.length();
        
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (s1[i - 1] == s2[j - 1]) {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        
        // Build SCS by backtracking
        string scs = "";
        int i = n, j = m;
        
        while (i > 0 && j > 0) {
            if (s1[i - 1] == s2[j - 1]) {
                scs = s1[i - 1] + scs;
                i--; j--;
            } else if (dp[i - 1][j] > dp[i][j - 1]) {
                scs = s1[i - 1] + scs;
                i--;
            } else {
                scs = s2[j - 1] + scs;
                j--;
            }
        }
        
        while (i > 0) {
            scs = s1[i - 1] + scs;
            i--;
        }
        while (j > 0) {
            scs = s2[j - 1] + scs;
            j--;
        }
        
        return scs;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s1, s2;
    cout << "Enter first string: ";
    cin >> s1;
    cout << "Enter second string: ";
    cin >> s2;
    
    TopDown td;
    BottomUp bu;
    
    cout << "\n--- Results ---" << endl;
    cout << "Top-Down Length: " << td.shortestLength(s1, s2) << endl;
    cout << "Bottom-Up Length: " << bu.shortestLength(s1, s2) << endl;
    cout << "SCS String: " << bu.printSCS(s1, s2) << endl;
    
    return 0;
}


















