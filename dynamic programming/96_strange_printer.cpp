/*
    Strange Printer
    Problem: Printer prints same character sequence, then overwrites.
             Find minimum turns to print string.
    
    Example: "aaabbb" → Output: 2 ("aaa" then "bbb")
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<vector<int>> dp;
    string s;
    
    int solve(int i, int j) {
        if (i > j) return 0;
        if (dp[i][j] != -1) return dp[i][j];
        
        // Print s[i] and extend as far as possible
        int result = 1 + solve(i + 1, j);
        
        // Try to combine printing s[i] with later same characters
        for (int k = i + 1; k <= j; k++) {
            if (s[k] == s[i]) {
                result = min(result, solve(i, k - 1) + solve(k + 1, j));
            }
        }
        
        return dp[i][j] = result;
    }
    
public:
    int strangePrinter(string str) {
        s = str;
        int n = s.length();
        if (n == 0) return 0;
        
        dp.assign(n, vector<int>(n, -1));
        return solve(0, n - 1);
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    int strangePrinter(string s) {
        int n = s.length();
        if (n == 0) return 0;
        
        vector<vector<int>> dp(n, vector<int>(n, 0));
        
        // Single character
        for (int i = 0; i < n; i++) {
            dp[i][i] = 1;
        }
        
        for (int len = 2; len <= n; len++) {
            for (int i = 0; i + len - 1 < n; i++) {
                int j = i + len - 1;
                dp[i][j] = dp[i + 1][j] + 1;
                
                for (int k = i + 1; k <= j; k++) {
                    if (s[k] == s[i]) {
                        int left = (k > i + 1) ? dp[i][k - 1] : 0;
                        int right = (k < j) ? dp[k + 1][j] : 0;
                        dp[i][j] = min(dp[i][j], left + right + 1);
                    }
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
    cout << "Top-Down: " << td.strangePrinter(s) << endl;
    cout << "Bottom-Up: " << bu.strangePrinter(s) << endl;
    
    return 0;
}









