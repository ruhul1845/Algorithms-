/*
    Number of Ways to Stay in the Same Place After Some Steps
    Problem: Array of length arrLen. Start at index 0.
             Can stay, go left, or go right. After steps, be at index 0.
             Count number of ways.
*/

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<vector<int>> dp;
    int maxPos;
    
    int solve(int pos, int steps) {
        if (pos < 0 || pos > maxPos) return 0;
        if (steps == 0) return pos == 0 ? 1 : 0;
        if (dp[pos][steps] != -1) return dp[pos][steps];
        
        long long ways = 0;
        ways += solve(pos, steps - 1);     // Stay
        ways += solve(pos - 1, steps - 1); // Left
        ways += solve(pos + 1, steps - 1); // Right
        
        return dp[pos][steps] = ways % MOD;
    }
    
public:
    int numWays(int steps, int arrLen) {
        maxPos = min(arrLen - 1, steps);
        dp.assign(maxPos + 1, vector<int>(steps + 1, -1));
        return solve(0, steps);
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    int numWays(int steps, int arrLen) {
        int maxPos = min(arrLen - 1, steps);
        
        // dp[i][j] = ways to be at position j after i steps
        vector<vector<long long>> dp(steps + 1, vector<long long>(maxPos + 1, 0));
        dp[0][0] = 1;
        
        for (int s = 1; s <= steps; s++) {
            for (int pos = 0; pos <= maxPos; pos++) {
                dp[s][pos] = dp[s - 1][pos];
                if (pos > 0) dp[s][pos] += dp[s - 1][pos - 1];
                if (pos < maxPos) dp[s][pos] += dp[s - 1][pos + 1];
                dp[s][pos] %= MOD;
            }
        }
        
        return dp[steps][0];
    }
    
    // Space Optimized O(arrLen)
    int numWaysOptimized(int steps, int arrLen) {
        int maxPos = min(arrLen - 1, steps);
        
        vector<long long> prev(maxPos + 1, 0), curr(maxPos + 1, 0);
        prev[0] = 1;
        
        for (int s = 1; s <= steps; s++) {
            for (int pos = 0; pos <= maxPos; pos++) {
                curr[pos] = prev[pos];
                if (pos > 0) curr[pos] += prev[pos - 1];
                if (pos < maxPos) curr[pos] += prev[pos + 1];
                curr[pos] %= MOD;
            }
            swap(prev, curr);
        }
        
        return prev[0];
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int steps, arrLen;
    cout << "Enter steps and array length: ";
    cin >> steps >> arrLen;
    
    TopDown td;
    BottomUp bu;
    
    cout << "\n--- Results ---" << endl;
    cout << "Top-Down: " << td.numWays(steps, arrLen) << endl;
    cout << "Bottom-Up: " << bu.numWays(steps, arrLen) << endl;
    cout << "Space Optimized: " << bu.numWaysOptimized(steps, arrLen) << endl;
    
    return 0;
}

