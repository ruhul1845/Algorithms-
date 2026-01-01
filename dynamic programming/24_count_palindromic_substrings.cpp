/*
    Count Palindromic Substrings
    Problem: Count all palindromic substrings in the given string.
    
    Example: s = "abc" → Output: 3 ("a", "b", "c")
    Example: s = "aaa" → Output: 6 ("a", "a", "a", "aa", "aa", "aaa")
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
    int countSubstrings(string& str) {
        s = str;
        int n = s.length();
        dp.assign(n, vector<int>(n, -1));
        
        int count = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                if (isPalindrome(i, j)) count++;
            }
        }
        
        return count;
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    int countSubstrings(string& s) {
        int n = s.length();
        vector<vector<bool>> dp(n, vector<bool>(n, false));
        int count = 0;
        
        // Single characters
        for (int i = 0; i < n; i++) {
            dp[i][i] = true;
            count++;
        }
        
        // Two characters
        for (int i = 0; i < n - 1; i++) {
            if (s[i] == s[i + 1]) {
                dp[i][i + 1] = true;
                count++;
            }
        }
        
        // Longer substrings
        for (int len = 3; len <= n; len++) {
            for (int i = 0; i <= n - len; i++) {
                int j = i + len - 1;
                if (s[i] == s[j] && dp[i + 1][j - 1]) {
                    dp[i][j] = true;
                    count++;
                }
            }
        }
        
        return count;
    }
    
    // Expand Around Center - O(n^2) time, O(1) space
    int countSubstringsOptimized(string& s) {
        int n = s.length();
        int count = 0;
        
        for (int i = 0; i < n; i++) {
            // Odd length
            int l = i, r = i;
            while (l >= 0 && r < n && s[l] == s[r]) {
                count++;
                l--; r++;
            }
            
            // Even length
            l = i; r = i + 1;
            while (l >= 0 && r < n && s[l] == s[r]) {
                count++;
                l--; r++;
            }
        }
        
        return count;
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
    cout << "Top-Down: " << td.countSubstrings(s) << endl;
    cout << "Bottom-Up: " << bu.countSubstrings(s) << endl;
    cout << "Expand Around Center: " << bu.countSubstringsOptimized(s) << endl;
    
    return 0;
}







