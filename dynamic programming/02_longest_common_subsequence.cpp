/*
    Longest Common Subsequence (LCS)
    Problem: Given two strings, find the length of the longest subsequence
             present in both of them.
    
    Example: 
    s1 = "AGGTAB", s2 = "GXTXAYB"
    LCS = "GTAB", Length = 4
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<vector<int>> dp;
    string s1, s2;
    
    int solve(int i, int j) {
        // Base case: if either string is exhausted
        if (i < 0 || j < 0) return 0;
        
        if (dp[i][j] != -1) return dp[i][j];
        
        // If characters match, include in LCS
        if (s1[i] == s2[j]) {
            return dp[i][j] = 1 + solve(i - 1, j - 1);
        }
        
        // If not match, take maximum by excluding one character
        return dp[i][j] = max(solve(i - 1, j), solve(i, j - 1));
    }
    
public:
    int lcs(string& str1, string& str2) {
        s1 = str1;
        s2 = str2;
        int n = s1.length(), m = s2.length();
        dp.assign(n, vector<int>(m, -1));
        return solve(n - 1, m - 1);
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    int lcs(string& s1, string& s2) {
        int n = s1.length(), m = s2.length();
        
        // dp[i][j] = LCS of s1[0..i-1] and s2[0..j-1]
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
        
        return dp[n][m];
    }
    
    // Space Optimized - O(m) space
    int lcsOptimized(string& s1, string& s2) {
        int n = s1.length(), m = s2.length();
        
        vector<int> prev(m + 1, 0), curr(m + 1, 0);
        
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (s1[i - 1] == s2[j - 1]) {
                    curr[j] = 1 + prev[j - 1];
                } else {
                    curr[j] = max(prev[j], curr[j - 1]);
                }
            }
            prev = curr;
        }
        
        return prev[m];
    }
    
    // Print the LCS string
    string printLCS(string& s1, string& s2) {
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
        
        // Backtrack to find LCS string
        string lcs = "";
        int i = n, j = m;
        while (i > 0 && j > 0) {
            if (s1[i - 1] == s2[j - 1]) {
                lcs = s1[i - 1] + lcs;
                i--;
                j--;
            } else if (dp[i - 1][j] > dp[i][j - 1]) {
                i--;
            } else {
                j--;
            }
        }
        
        return lcs;
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
    cout << "Top-Down (Memoization): " << td.lcs(s1, s2) << endl;
    cout << "Bottom-Up (Tabulation): " << bu.lcs(s1, s2) << endl;
    cout << "Bottom-Up (Space Optimized): " << bu.lcsOptimized(s1, s2) << endl;
    cout << "LCS String: " << bu.printLCS(s1, s2) << endl;
    
    return 0;
}

/*
    Time Complexity: O(n * m)
    Space Complexity:
        - Top-Down: O(n * m) for memoization + O(n + m) recursion stack
        - Bottom-Up: O(n * m)
        - Bottom-Up Optimized: O(m)
*/

