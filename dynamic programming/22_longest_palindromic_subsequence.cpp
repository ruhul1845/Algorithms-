/*
    Longest Palindromic Subsequence
    Problem: Find the length of longest palindromic subsequence.
    
    Example: s = "bbbab" → Output: 4 ("bbbb")
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
        if (i == j) return 1;
        if (dp[i][j] != -1) return dp[i][j];
        
        if (s[i] == s[j]) {
            return dp[i][j] = 2 + solve(i + 1, j - 1);
        }
        
        return dp[i][j] = max(solve(i + 1, j), solve(i, j - 1));
    }
    
public:
    int longestPalinSubseq(string& str) {
        s = str;
        int n = s.length();
        dp.assign(n, vector<int>(n, -1));
        return solve(0, n - 1);
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    int longestPalinSubseq(string& s) {
        int n = s.length();
        vector<vector<int>> dp(n, vector<int>(n, 0));
        
        // Single characters are palindromes of length 1
        for (int i = 0; i < n; i++) dp[i][i] = 1;
        
        // Build for lengths 2 to n
        for (int len = 2; len <= n; len++) {
            for (int i = 0; i <= n - len; i++) {
                int j = i + len - 1;
                if (s[i] == s[j]) {
                    dp[i][j] = 2 + dp[i+1][j-1];
                } else {
                    dp[i][j] = max(dp[i+1][j], dp[i][j-1]);
                }
            }
        }
        
        return dp[0][n-1];
    }
    
    // Using LCS approach: LPS(s) = LCS(s, reverse(s))
    int longestPalinSubseqLCS(string& s) {
        string rev = s;
        reverse(rev.begin(), rev.end());
        
        int n = s.length();
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
        
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (s[i-1] == rev[j-1]) {
                    dp[i][j] = 1 + dp[i-1][j-1];
                } else {
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                }
            }
        }
        
        return dp[n][n];
    }
    
    // Print the LPS
    string printLPS(string& s) {
        int n = s.length();
        vector<vector<int>> dp(n, vector<int>(n, 0));
        
        for (int i = 0; i < n; i++) dp[i][i] = 1;
        
        for (int len = 2; len <= n; len++) {
            for (int i = 0; i <= n - len; i++) {
                int j = i + len - 1;
                if (s[i] == s[j]) {
                    dp[i][j] = 2 + dp[i+1][j-1];
                } else {
                    dp[i][j] = max(dp[i+1][j], dp[i][j-1]);
                }
            }
        }
        
        // Reconstruct
        string result(dp[0][n-1], ' ');
        int left = 0, right = dp[0][n-1] - 1;
        int i = 0, j = n - 1;
        
        while (i <= j) {
            if (i == j) {
                result[left] = s[i];
                break;
            }
            if (s[i] == s[j]) {
                result[left++] = s[i];
                result[right--] = s[j];
                i++; j--;
            } else if (dp[i+1][j] > dp[i][j-1]) {
                i++;
            } else {
                j--;
            }
        }
        
        return result;
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
    cout << "Top-Down: " << td.longestPalinSubseq(s) << endl;
    cout << "Bottom-Up: " << bu.longestPalinSubseq(s) << endl;
    cout << "Using LCS: " << bu.longestPalinSubseqLCS(s) << endl;
    cout << "LPS String: " << bu.printLPS(s) << endl;
    
    return 0;
}







