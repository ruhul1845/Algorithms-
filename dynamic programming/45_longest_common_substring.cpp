/*
    Longest Common Substring
    Problem: Find length of longest substring present in both strings.
    
    Example: s1 = "ABCDGH", s2 = "ACDGHR" → Output: 4 ("CDGH")
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<vector<int>> dp;
    string s1, s2;
    int maxLen;
    
    int solve(int i, int j) {
        if (i < 0 || j < 0) return 0;
        if (dp[i][j] != -1) return dp[i][j];
        
        // We need to compute all positions, not just return early
        solve(i - 1, j);
        solve(i, j - 1);
        
        if (s1[i] == s2[j]) {
            int prevLen = (i > 0 && j > 0) ? solve(i - 1, j - 1) : 0;
            dp[i][j] = 1 + prevLen;
            maxLen = max(maxLen, dp[i][j]);
        } else {
            dp[i][j] = 0;
        }
        
        return dp[i][j];
    }
    
public:
    int longestCommonSubstring(string& str1, string& str2) {
        s1 = str1; s2 = str2;
        int n = s1.length(), m = s2.length();
        dp.assign(n, vector<int>(m, -1));
        maxLen = 0;
        
        solve(n - 1, m - 1);
        
        return maxLen;
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    int longestCommonSubstring(string& s1, string& s2) {
        int n = s1.length(), m = s2.length();
        
        // dp[i][j] = length of LCS ending at s1[i-1] and s2[j-1]
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        int maxLen = 0;
        
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (s1[i - 1] == s2[j - 1]) {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                    maxLen = max(maxLen, dp[i][j]);
                }
                // else dp[i][j] = 0 (already initialized)
            }
        }
        
        return maxLen;
    }
    
    // Space Optimized O(m)
    int longestCommonSubstringOptimized(string& s1, string& s2) {
        int n = s1.length(), m = s2.length();
        
        vector<int> prev(m + 1, 0), curr(m + 1, 0);
        int maxLen = 0;
        
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (s1[i - 1] == s2[j - 1]) {
                    curr[j] = 1 + prev[j - 1];
                    maxLen = max(maxLen, curr[j]);
                } else {
                    curr[j] = 0;
                }
            }
            swap(prev, curr);
        }
        
        return maxLen;
    }
    
    // Print the substring
    string printLCSubstring(string& s1, string& s2) {
        int n = s1.length(), m = s2.length();
        
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        int maxLen = 0, endIdx = 0;
        
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (s1[i - 1] == s2[j - 1]) {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                    if (dp[i][j] > maxLen) {
                        maxLen = dp[i][j];
                        endIdx = i;
                    }
                }
            }
        }
        
        return s1.substr(endIdx - maxLen, maxLen);
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
    cout << "Top-Down: " << td.longestCommonSubstring(s1, s2) << endl;
    cout << "Bottom-Up: " << bu.longestCommonSubstring(s1, s2) << endl;
    cout << "Bottom-Up Optimized: " << bu.longestCommonSubstringOptimized(s1, s2) << endl;
    cout << "Substring: " << bu.printLCSubstring(s1, s2) << endl;
    
    return 0;
}







