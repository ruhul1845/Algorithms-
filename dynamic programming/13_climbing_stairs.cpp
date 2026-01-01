/*
    Climbing Stairs
    Problem: You can climb 1 or 2 steps at a time. 
             Find number of distinct ways to reach the top (n steps).
    
    Example: n = 3 → Output: 3 (1+1+1, 1+2, 2+1)
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<int> dp;
    
    int solve(int n) {
        if (n <= 1) return 1;
        if (dp[n] != -1) return dp[n];
        return dp[n] = solve(n-1) + solve(n-2);
    }
    
public:
    int climbStairs(int n) {
        dp.assign(n + 1, -1);
        return solve(n);
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    int climbStairs(int n) {
        if (n <= 1) return 1;
        
        vector<int> dp(n + 1);
        dp[0] = dp[1] = 1;
        
        for (int i = 2; i <= n; i++) {
            dp[i] = dp[i-1] + dp[i-2];
        }
        
        return dp[n];
    }
    
    // Space Optimized
    int climbStairsOptimized(int n) {
        if (n <= 1) return 1;
        
        int prev2 = 1, prev1 = 1;
        
        for (int i = 2; i <= n; i++) {
            int curr = prev1 + prev2;
            prev2 = prev1;
            prev1 = curr;
        }
        
        return prev1;
    }
    
    // Generalized: k steps at a time
    int climbStairsK(int n, int k) {
        vector<int> dp(n + 1, 0);
        dp[0] = 1;
        
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= k && j <= i; j++) {
                dp[i] += dp[i - j];
            }
        }
        
        return dp[n];
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cout << "Enter number of stairs: ";
    cin >> n;
    
    TopDown td;
    BottomUp bu;
    
    cout << "\n--- Results ---" << endl;
    cout << "Top-Down: " << td.climbStairs(n) << endl;
    cout << "Bottom-Up: " << bu.climbStairs(n) << endl;
    cout << "Bottom-Up Optimized: " << bu.climbStairsOptimized(n) << endl;
    cout << "With k=3 steps: " << bu.climbStairsK(n, 3) << endl;
    
    return 0;
}







