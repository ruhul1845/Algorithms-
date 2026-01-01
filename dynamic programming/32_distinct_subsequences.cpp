/*
    Distinct Subsequences
    Problem: Count distinct subsequences of s that equal t.
    
    Example: s = "rabbbit", t = "rabbit" → Output: 3
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<vector<int>> dp;
    string s, t;
    
    int solve(int i, int j) {
        if (j < 0) return 1;  // Found all chars of t
        if (i < 0) return 0;  // Exhausted s before t
        if (dp[i][j] != -1) return dp[i][j];
        
        int skip = solve(i - 1, j);
        int take = 0;
        if (s[i] == t[j]) {
            take = solve(i - 1, j - 1);
        }
        
        return dp[i][j] = skip + take;
    }
    
public:
    int numDistinct(string& str, string& target) {
        s = str;
        t = target;
        int n = s.length(), m = t.length();
        dp.assign(n, vector<int>(m, -1));
        return solve(n - 1, m - 1);
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    int numDistinct(string& s, string& t) {
        int n = s.length(), m = t.length();
        
        // dp[i][j] = count of t[0..j-1] in s[0..i-1]
        vector<vector<long long>> dp(n + 1, vector<long long>(m + 1, 0));
        
        // Empty t can be found in any prefix of s
        for (int i = 0; i <= n; i++) dp[i][0] = 1;
        
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                dp[i][j] = dp[i - 1][j];
                if (s[i - 1] == t[j - 1]) {
                    dp[i][j] += dp[i - 1][j - 1];
                }
            }
        }
        
        return dp[n][m];
    }
    
    // Space Optimized O(m)
    int numDistinctOptimized(string& s, string& t) {
        int n = s.length(), m = t.length();
        vector<long long> dp(m + 1, 0);
        dp[0] = 1;
        
        for (int i = 0; i < n; i++) {
            for (int j = m - 1; j >= 0; j--) {
                if (s[i] == t[j]) {
                    dp[j + 1] += dp[j];
                }
            }
        }
        
        return dp[m];
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s, t;
    cout << "Enter string s: ";
    cin >> s;
    cout << "Enter string t: ";
    cin >> t;
    
    TopDown td;
    BottomUp bu;
    
    cout << "\n--- Results ---" << endl;
    cout << "Top-Down: " << td.numDistinct(s, t) << endl;
    cout << "Bottom-Up: " << bu.numDistinct(s, t) << endl;
    cout << "Bottom-Up Optimized: " << bu.numDistinctOptimized(s, t) << endl;
    
    return 0;
}







