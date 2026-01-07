/*
    Palindrome Partitioning - Minimum Cuts
    Problem: Find minimum cuts needed to partition string into palindromes.
    
    Example: s = "aab" → Output: 1 (partitions: "aa", "b")
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<int> dp;
    vector<vector<bool>> isPalin;
    string s;
    
    void precompute() {
        int n = s.length();
        isPalin.assign(n, vector<bool>(n, false));
        
        for (int i = n - 1; i >= 0; i--) {
            for (int j = i; j < n; j++) {
                if (s[i] == s[j] && (j - i <= 2 || isPalin[i+1][j-1])) {
                    isPalin[i][j] = true;
                }
            }
        }
    }
    
    int solve(int idx) {
        if (idx == s.length()) return 0;
        if (dp[idx] != -1) return dp[idx];
        
        int minCuts = INT_MAX;
        for (int j = idx; j < s.length(); j++) {
            if (isPalin[idx][j]) {
                minCuts = min(minCuts, 1 + solve(j + 1));
            }
        }
        
        return dp[idx] = minCuts;
    }
    
public:
    int minCut(string& str) {
        s = str;
        int n = s.length();
        dp.assign(n, -1);
        precompute();
        return solve(0) - 1; // -1 because we count partitions, not cuts
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    int minCut(string& s) {
        int n = s.length();
        
        // Precompute palindrome table
        vector<vector<bool>> isPalin(n, vector<bool>(n, false));
        for (int i = n - 1; i >= 0; i--) {
            for (int j = i; j < n; j++) {
                if (s[i] == s[j] && (j - i <= 2 || isPalin[i+1][j-1])) {
                    isPalin[i][j] = true;
                }
            }
        }
        
        // dp[i] = minimum cuts for s[0..i]
        vector<int> dp(n, 0);
        
        for (int i = 0; i < n; i++) {
            if (isPalin[0][i]) {
                dp[i] = 0;
            } else {
                dp[i] = i; // max cuts
                for (int j = 0; j < i; j++) {
                    if (isPalin[j+1][i]) {
                        dp[i] = min(dp[i], dp[j] + 1);
                    }
                }
            }
        }
        
        return dp[n - 1];
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
    cout << "Top-Down: " << td.minCut(s) << endl;
    cout << "Bottom-Up: " << bu.minCut(s) << endl;
    
    return 0;
}


















