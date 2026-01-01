/*
    Wildcard Matching
    Problem: Check if pattern matches string. '?' matches any single char,
             '*' matches any sequence (including empty).
    
    Example: s = "adceb", p = "*a*b" → Output: true
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<vector<int>> dp;
    string s, p;
    
    bool solve(int i, int j) {
        if (j < 0) return i < 0;
        if (i < 0) {
            // Check if remaining pattern is all *
            for (int k = 0; k <= j; k++) {
                if (p[k] != '*') return false;
            }
            return true;
        }
        if (dp[i][j] != -1) return dp[i][j];
        
        if (p[j] == s[i] || p[j] == '?') {
            return dp[i][j] = solve(i - 1, j - 1);
        }
        
        if (p[j] == '*') {
            // * matches empty or * matches current char
            return dp[i][j] = solve(i, j - 1) || solve(i - 1, j);
        }
        
        return dp[i][j] = false;
    }
    
public:
    bool isMatch(string& str, string& pattern) {
        s = str;
        p = pattern;
        int n = s.length(), m = p.length();
        dp.assign(n, vector<int>(m, -1));
        return solve(n - 1, m - 1);
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    bool isMatch(string& s, string& p) {
        int n = s.length(), m = p.length();
        
        // dp[i][j] = does s[0..i-1] match p[0..j-1]?
        vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));
        dp[0][0] = true;
        
        // Pattern with * can match empty string
        for (int j = 1; j <= m; j++) {
            if (p[j - 1] == '*') dp[0][j] = dp[0][j - 1];
        }
        
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (p[j - 1] == s[i - 1] || p[j - 1] == '?') {
                    dp[i][j] = dp[i - 1][j - 1];
                } else if (p[j - 1] == '*') {
                    dp[i][j] = dp[i][j - 1] || dp[i - 1][j];
                }
            }
        }
        
        return dp[n][m];
    }
    
    // Space Optimized
    bool isMatchOptimized(string& s, string& p) {
        int n = s.length(), m = p.length();
        
        vector<bool> prev(m + 1, false), curr(m + 1, false);
        prev[0] = true;
        
        for (int j = 1; j <= m; j++) {
            if (p[j - 1] == '*') prev[j] = prev[j - 1];
        }
        
        for (int i = 1; i <= n; i++) {
            curr[0] = false;
            for (int j = 1; j <= m; j++) {
                if (p[j - 1] == s[i - 1] || p[j - 1] == '?') {
                    curr[j] = prev[j - 1];
                } else if (p[j - 1] == '*') {
                    curr[j] = curr[j - 1] || prev[j];
                } else {
                    curr[j] = false;
                }
            }
            swap(prev, curr);
        }
        
        return prev[m];
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s, p;
    cout << "Enter string: ";
    cin >> s;
    cout << "Enter pattern: ";
    cin >> p;
    
    TopDown td;
    BottomUp bu;
    
    cout << "\n--- Results ---" << endl;
    cout << "Top-Down: " << (td.isMatch(s, p) ? "Yes" : "No") << endl;
    cout << "Bottom-Up: " << (bu.isMatch(s, p) ? "Yes" : "No") << endl;
    cout << "Bottom-Up Optimized: " << (bu.isMatchOptimized(s, p) ? "Yes" : "No") << endl;
    
    return 0;
}







