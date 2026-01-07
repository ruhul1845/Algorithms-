/*
    Unique Paths
    Problem: Count paths from top-left to bottom-right in m x n grid.
             Can only move right or down.
    
    Example: m = 3, n = 7 → Output: 28
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<vector<int>> dp;
    
    int solve(int i, int j) {
        if (i == 0 && j == 0) return 1;
        if (i < 0 || j < 0) return 0;
        if (dp[i][j] != -1) return dp[i][j];
        
        return dp[i][j] = solve(i-1, j) + solve(i, j-1);
    }
    
public:
    int uniquePaths(int m, int n) {
        dp.assign(m, vector<int>(n, -1));
        return solve(m-1, n-1);
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> dp(m, vector<int>(n, 1));
        
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                dp[i][j] = dp[i-1][j] + dp[i][j-1];
            }
        }
        
        return dp[m-1][n-1];
    }
    
    // Space Optimized O(n)
    int uniquePathsOptimized(int m, int n) {
        vector<int> dp(n, 1);
        
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                dp[j] += dp[j-1];
            }
        }
        
        return dp[n-1];
    }
    
    // Using Combinatorics: C(m+n-2, m-1)
    long long uniquePathsMath(int m, int n) {
        long long result = 1;
        for (int i = 0; i < min(m-1, n-1); i++) {
            result = result * (m + n - 2 - i) / (i + 1);
        }
        return result;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int m, n;
    cout << "Enter grid dimensions (m n): ";
    cin >> m >> n;
    
    TopDown td;
    BottomUp bu;
    
    cout << "\n--- Results ---" << endl;
    cout << "Top-Down: " << td.uniquePaths(m, n) << endl;
    cout << "Bottom-Up: " << bu.uniquePaths(m, n) << endl;
    cout << "Bottom-Up Optimized: " << bu.uniquePathsOptimized(m, n) << endl;
    cout << "Math (Combinatorics): " << bu.uniquePathsMath(m, n) << endl;
    
    return 0;
}


















