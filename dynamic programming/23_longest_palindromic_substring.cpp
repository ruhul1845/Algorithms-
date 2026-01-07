/*
    Longest Palindromic Substring
    Problem: Find the longest substring that is a palindrome.
    
    Example: s = "babad" → Output: "bab" or "aba"
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<vector<int>> dp;
    string s;
    
    bool isPalindrome(int i, int j) {
        if (i >= j) return true;
        if (dp[i][j] != -1) return dp[i][j];
        
        if (s[i] == s[j]) {
            return dp[i][j] = isPalindrome(i + 1, j - 1);
        }
        return dp[i][j] = false;
    }
    
public:
    string longestPalindrome(string& str) {
        s = str;
        int n = s.length();
        dp.assign(n, vector<int>(n, -1));
        
        int maxLen = 1, start = 0;
        
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                if (isPalindrome(i, j) && j - i + 1 > maxLen) {
                    maxLen = j - i + 1;
                    start = i;
                }
            }
        }
        
        return s.substr(start, maxLen);
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    string longestPalindrome(string& s) {
        int n = s.length();
        if (n == 0) return "";
        
        vector<vector<bool>> dp(n, vector<bool>(n, false));
        int start = 0, maxLen = 1;
        
        // All single characters are palindromes
        for (int i = 0; i < n; i++) dp[i][i] = true;
        
        // Check for length 2
        for (int i = 0; i < n - 1; i++) {
            if (s[i] == s[i + 1]) {
                dp[i][i + 1] = true;
                start = i;
                maxLen = 2;
            }
        }
        
        // Check for lengths > 2
        for (int len = 3; len <= n; len++) {
            for (int i = 0; i <= n - len; i++) {
                int j = i + len - 1;
                if (s[i] == s[j] && dp[i + 1][j - 1]) {
                    dp[i][j] = true;
                    start = i;
                    maxLen = len;
                }
            }
        }
        
        return s.substr(start, maxLen);
    }
    
    // Expand Around Center - O(n^2) time, O(1) space
    string longestPalindromeOptimized(string& s) {
        int n = s.length();
        if (n == 0) return "";
        
        int start = 0, maxLen = 1;
        
        for (int i = 0; i < n; i++) {
            // Odd length palindrome
            int l = i, r = i;
            while (l >= 0 && r < n && s[l] == s[r]) {
                if (r - l + 1 > maxLen) {
                    start = l;
                    maxLen = r - l + 1;
                }
                l--; r++;
            }
            
            // Even length palindrome
            l = i; r = i + 1;
            while (l >= 0 && r < n && s[l] == s[r]) {
                if (r - l + 1 > maxLen) {
                    start = l;
                    maxLen = r - l + 1;
                }
                l--; r++;
            }
        }
        
        return s.substr(start, maxLen);
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
    cout << "Top-Down: " << td.longestPalindrome(s) << endl;
    cout << "Bottom-Up: " << bu.longestPalindrome(s) << endl;
    cout << "Expand Around Center: " << bu.longestPalindromeOptimized(s) << endl;
    
    return 0;
}


















