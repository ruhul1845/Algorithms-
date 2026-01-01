/*
    Decode Ways
    Problem: A message encoded as digits. 'A'=1, 'B'=2, ..., 'Z'=26.
             Count the number of ways to decode the message.
    
    Example: s = "12" → Output: 2 ("AB" or "L")
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<int> dp;
    string s;
    
    int solve(int idx) {
        if (idx == s.length()) return 1;
        if (s[idx] == '0') return 0;
        if (dp[idx] != -1) return dp[idx];
        
        // Take one digit
        int ways = solve(idx + 1);
        
        // Take two digits
        if (idx + 1 < s.length()) {
            int twoDigit = (s[idx] - '0') * 10 + (s[idx + 1] - '0');
            if (twoDigit <= 26) {
                ways += solve(idx + 2);
            }
        }
        
        return dp[idx] = ways;
    }
    
public:
    int numDecodings(string& str) {
        s = str;
        if (s.empty() || s[0] == '0') return 0;
        dp.assign(s.length(), -1);
        return solve(0);
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    int numDecodings(string& s) {
        int n = s.length();
        if (n == 0 || s[0] == '0') return 0;
        
        vector<int> dp(n + 1, 0);
        dp[0] = 1;
        dp[1] = 1;
        
        for (int i = 2; i <= n; i++) {
            // Single digit
            if (s[i - 1] != '0') {
                dp[i] += dp[i - 1];
            }
            
            // Two digits
            int twoDigit = (s[i - 2] - '0') * 10 + (s[i - 1] - '0');
            if (twoDigit >= 10 && twoDigit <= 26) {
                dp[i] += dp[i - 2];
            }
        }
        
        return dp[n];
    }
    
    // Space Optimized O(1)
    int numDecodingsOptimized(string& s) {
        int n = s.length();
        if (n == 0 || s[0] == '0') return 0;
        
        int prev2 = 1, prev1 = 1;
        
        for (int i = 2; i <= n; i++) {
            int curr = 0;
            
            if (s[i - 1] != '0') {
                curr += prev1;
            }
            
            int twoDigit = (s[i - 2] - '0') * 10 + (s[i - 1] - '0');
            if (twoDigit >= 10 && twoDigit <= 26) {
                curr += prev2;
            }
            
            prev2 = prev1;
            prev1 = curr;
        }
        
        return prev1;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s;
    cout << "Enter encoded string: ";
    cin >> s;
    
    TopDown td;
    BottomUp bu;
    
    cout << "\n--- Results ---" << endl;
    cout << "Top-Down: " << td.numDecodings(s) << endl;
    cout << "Bottom-Up: " << bu.numDecodings(s) << endl;
    cout << "Bottom-Up Optimized: " << bu.numDecodingsOptimized(s) << endl;
    
    return 0;
}







