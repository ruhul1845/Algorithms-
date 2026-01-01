/*
    Regular Expression Matching
    Problem: '.' matches any single character, '*' matches zero or more 
             of the preceding element.
    
    Example: s = "aab", p = "c*a*b" → Output: true
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
            // Pattern must be like a*b*c* to match empty string
            while (j >= 0 && p[j] == '*') j -= 2;
            return j < 0;
        }
        if (dp[i][j] != -1) return dp[i][j];
        
        if (p[j] == s[i] || p[j] == '.') {
            return dp[i][j] = solve(i - 1, j - 1);
        }
        
        if (p[j] == '*') {
            // Zero occurrences of preceding char
            bool zero = solve(i, j - 2);
            // One or more occurrences
            bool more = false;
            if (p[j - 1] == s[i] || p[j - 1] == '.') {
                more = solve(i - 1, j);
            }
            return dp[i][j] = zero || more;
        }
        
        return dp[i][j] = false;
    }
    
public:
    bool isMatch(string& str, string& pattern) {
        s = str;
        p = pattern;
        int n = s.length(), m = p.length();
        dp.assign(n + 1, vector<int>(m + 1, -1));
        return solve(n - 1, m - 1);
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    bool isMatch(string& s, string& p) {
        int n = s.length(), m = p.length();
        
        vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));
        dp[0][0] = true;
        
        // Handle patterns like a*b*c* that match empty string
        for (int j = 2; j <= m; j++) {
            if (p[j - 1] == '*') {
                dp[0][j] = dp[0][j - 2];
            }
        }
        
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (p[j - 1] == s[i - 1] || p[j - 1] == '.') {
                    dp[i][j] = dp[i - 1][j - 1];
                } else if (p[j - 1] == '*') {
                    // Zero occurrences
                    dp[i][j] = dp[i][j - 2];
                    // One or more
                    if (p[j - 2] == s[i - 1] || p[j - 2] == '.') {
                        dp[i][j] = dp[i][j] || dp[i - 1][j];
                    }
                }
            }
        }
        
        return dp[n][m];
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
    
    return 0;
}







