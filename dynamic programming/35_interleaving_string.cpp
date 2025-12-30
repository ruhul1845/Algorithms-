/*
    Interleaving String
    Problem: Check if s3 is formed by interleaving s1 and s2.
    
    Example: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac" → Output: true
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<vector<int>> dp;
    string s1, s2, s3;
    
    bool solve(int i, int j) {
        int k = i + j;
        if (k == s3.length()) return true;
        if (dp[i][j] != -1) return dp[i][j];
        
        bool result = false;
        
        if (i < s1.length() && s1[i] == s3[k]) {
            result = solve(i + 1, j);
        }
        
        if (!result && j < s2.length() && s2[j] == s3[k]) {
            result = solve(i, j + 1);
        }
        
        return dp[i][j] = result;
    }
    
public:
    bool isInterleave(string& str1, string& str2, string& str3) {
        s1 = str1; s2 = str2; s3 = str3;
        if (s1.length() + s2.length() != s3.length()) return false;
        dp.assign(s1.length() + 1, vector<int>(s2.length() + 1, -1));
        return solve(0, 0);
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    bool isInterleave(string& s1, string& s2, string& s3) {
        int n = s1.length(), m = s2.length();
        if (n + m != s3.length()) return false;
        
        // dp[i][j] = can first i chars of s1 and first j chars of s2 form first i+j chars of s3?
        vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));
        
        dp[0][0] = true;
        
        // Fill first row (using only s2)
        for (int j = 1; j <= m; j++) {
            dp[0][j] = dp[0][j - 1] && (s2[j - 1] == s3[j - 1]);
        }
        
        // Fill first column (using only s1)
        for (int i = 1; i <= n; i++) {
            dp[i][0] = dp[i - 1][0] && (s1[i - 1] == s3[i - 1]);
        }
        
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                dp[i][j] = (dp[i - 1][j] && s1[i - 1] == s3[i + j - 1]) ||
                           (dp[i][j - 1] && s2[j - 1] == s3[i + j - 1]);
            }
        }
        
        return dp[n][m];
    }
    
    // Space Optimized O(m)
    bool isInterleaveOptimized(string& s1, string& s2, string& s3) {
        int n = s1.length(), m = s2.length();
        if (n + m != s3.length()) return false;
        
        vector<bool> dp(m + 1, false);
        
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= m; j++) {
                if (i == 0 && j == 0) {
                    dp[j] = true;
                } else if (i == 0) {
                    dp[j] = dp[j - 1] && s2[j - 1] == s3[j - 1];
                } else if (j == 0) {
                    dp[j] = dp[j] && s1[i - 1] == s3[i - 1];
                } else {
                    dp[j] = (dp[j] && s1[i - 1] == s3[i + j - 1]) ||
                            (dp[j - 1] && s2[j - 1] == s3[i + j - 1]);
                }
            }
        }
        
        return dp[m];
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s1, s2, s3;
    cout << "Enter s1: ";
    cin >> s1;
    cout << "Enter s2: ";
    cin >> s2;
    cout << "Enter s3: ";
    cin >> s3;
    
    TopDown td;
    BottomUp bu;
    
    cout << "\n--- Results ---" << endl;
    cout << "Top-Down: " << (td.isInterleave(s1, s2, s3) ? "Yes" : "No") << endl;
    cout << "Bottom-Up: " << (bu.isInterleave(s1, s2, s3) ? "Yes" : "No") << endl;
    cout << "Bottom-Up Optimized: " << (bu.isInterleaveOptimized(s1, s2, s3) ? "Yes" : "No") << endl;
    
    return 0;
}

