/*
    Minimum Insertions to Make Palindrome
    Problem: Find minimum insertions needed to make string a palindrome.
    
    Example: s = "abcd" → Output: 3 ("dcbabcd")
    Formula: n - LPS(s) where LPS = Longest Palindromic Subsequence
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<vector<int>> dp;
    string s;
    
    int lps(int i, int j) {
        if (i > j) return 0;
        if (i == j) return 1;
        if (dp[i][j] != -1) return dp[i][j];
        
        if (s[i] == s[j]) {
            return dp[i][j] = 2 + lps(i + 1, j - 1);
        }
        return dp[i][j] = max(lps(i + 1, j), lps(i, j - 1));
    }
    
public:
    int minInsertions(string& str) {
        s = str;
        int n = s.length();
        dp.assign(n, vector<int>(n, -1));
        return n - lps(0, n - 1);
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    int minInsertions(string& s) {
        int n = s.length();
        
        // Find LPS length
        vector<vector<int>> dp(n, vector<int>(n, 0));
        
        for (int i = 0; i < n; i++) dp[i][i] = 1;
        
        for (int len = 2; len <= n; len++) {
            for (int i = 0; i <= n - len; i++) {
                int j = i + len - 1;
                if (s[i] == s[j]) {
                    dp[i][j] = 2 + dp[i + 1][j - 1];
                } else {
                    dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
                }
            }
        }
        
        return n - dp[0][n - 1];
    }
    
    // Direct approach: minimum insertions
    int minInsertionsDirect(string& s) {
        int n = s.length();
        // dp[i][j] = min insertions to make s[i..j] palindrome
        vector<vector<int>> dp(n, vector<int>(n, 0));
        
        for (int len = 2; len <= n; len++) {
            for (int i = 0; i <= n - len; i++) {
                int j = i + len - 1;
                if (s[i] == s[j]) {
                    dp[i][j] = dp[i + 1][j - 1];
                } else {
                    dp[i][j] = 1 + min(dp[i + 1][j], dp[i][j - 1]);
                }
            }
        }
        
        return dp[0][n - 1];
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s;
    cout << "Enter string: ";
    cin >> s;
    
    TopDown td;
    BottomUp bu;
    
    cout << "\n--- Results ---" << endl;
    cout << "Top-Down: " << td.minInsertions(s) << endl;
    cout << "Bottom-Up (LPS): " << bu.minInsertions(s) << endl;
    cout << "Bottom-Up (Direct): " << bu.minInsertionsDirect(s) << endl;
    
    return 0;
}







