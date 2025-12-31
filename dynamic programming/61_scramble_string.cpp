/*
    Scramble String
    Problem: Check if s2 is a scrambled version of s1.
             A string can be scrambled by splitting and swapping children.
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    map<string, bool> dp;
    
    bool solve(string s1, string s2) {
        if (s1 == s2) return true;
        if (s1.length() != s2.length()) return false;
        
        int n = s1.length();
        if (n == 0) return true;
        
        string key = s1 + "_" + s2;
        if (dp.count(key)) return dp[key];
        
        // Check if characters match
        string t1 = s1, t2 = s2;
        sort(t1.begin(), t1.end());
        sort(t2.begin(), t2.end());
        if (t1 != t2) return dp[key] = false;
        
        for (int i = 1; i < n; i++) {
            // No swap
            if (solve(s1.substr(0, i), s2.substr(0, i)) &&
                solve(s1.substr(i), s2.substr(i))) {
                return dp[key] = true;
            }
            // With swap
            if (solve(s1.substr(0, i), s2.substr(n - i)) &&
                solve(s1.substr(i), s2.substr(0, n - i))) {
                return dp[key] = true;
            }
        }
        
        return dp[key] = false;
    }
    
public:
    bool isScramble(string s1, string s2) {
        dp.clear();
        return solve(s1, s2);
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    bool isScramble(string s1, string s2) {
        if (s1 == s2) return true;
        int n = s1.length();
        if (n != s2.length()) return false;
        
        // dp[len][i][j] = is s1[i..i+len-1] a scramble of s2[j..j+len-1]?
        vector<vector<vector<bool>>> dp(n + 1, 
            vector<vector<bool>>(n, vector<bool>(n, false)));
        
        // Base case: length 1
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                dp[1][i][j] = (s1[i] == s2[j]);
            }
        }
        
        // Fill for increasing lengths
        for (int len = 2; len <= n; len++) {
            for (int i = 0; i <= n - len; i++) {
                for (int j = 0; j <= n - len; j++) {
                    for (int k = 1; k < len && !dp[len][i][j]; k++) {
                        // No swap
                        dp[len][i][j] = dp[len][i][j] || 
                            (dp[k][i][j] && dp[len - k][i + k][j + k]);
                        // With swap
                        dp[len][i][j] = dp[len][i][j] || 
                            (dp[k][i][j + len - k] && dp[len - k][i + k][j]);
                    }
                }
            }
        }
        
        return dp[n][0][0];
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
    cout << "Top-Down: " << (td.isScramble(s1, s2) ? "Yes" : "No") << endl;
    cout << "Bottom-Up: " << (bu.isScramble(s1, s2) ? "Yes" : "No") << endl;
    
    return 0;
}



