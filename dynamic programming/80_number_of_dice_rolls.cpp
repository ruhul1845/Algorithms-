/*
    Number of Dice Rolls With Target Sum
    Problem: n dice with k faces (1 to k). Count ways to get target sum.
    
    Example: n = 2, k = 6, target = 7 → Output: 6
             (1+6, 2+5, 3+4, 4+3, 5+2, 6+1)
*/

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<vector<int>> dp;
    int k;
    
    int solve(int dice, int target) {
        if (dice == 0) return target == 0 ? 1 : 0;
        if (target <= 0) return 0;
        if (dp[dice][target] != -1) return dp[dice][target];
        
        long long ways = 0;
        for (int face = 1; face <= k && face <= target; face++) {
            ways = (ways + solve(dice - 1, target - face)) % MOD;
        }
        
        return dp[dice][target] = ways;
    }
    
public:
    int numRollsToTarget(int n, int K, int target) {
        k = K;
        dp.assign(n + 1, vector<int>(target + 1, -1));
        return solve(n, target);
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    int numRollsToTarget(int n, int k, int target) {
        // dp[i][j] = ways to get sum j with i dice
        vector<vector<long long>> dp(n + 1, vector<long long>(target + 1, 0));
        dp[0][0] = 1;
        
        for (int dice = 1; dice <= n; dice++) {
            for (int sum = dice; sum <= min(target, dice * k); sum++) {
                for (int face = 1; face <= k && face <= sum; face++) {
                    dp[dice][sum] = (dp[dice][sum] + dp[dice - 1][sum - face]) % MOD;
                }
            }
        }
        
        return dp[n][target];
    }
    
    // Space Optimized O(target)
    int numRollsToTargetOptimized(int n, int k, int target) {
        vector<long long> prev(target + 1, 0), curr(target + 1, 0);
        prev[0] = 1;
        
        for (int dice = 1; dice <= n; dice++) {
            fill(curr.begin(), curr.end(), 0);
            
            for (int sum = dice; sum <= min(target, dice * k); sum++) {
                for (int face = 1; face <= k && face <= sum; face++) {
                    curr[sum] = (curr[sum] + prev[sum - face]) % MOD;
                }
            }
            
            swap(prev, curr);
        }
        
        return prev[target];
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k, target;
    cout << "Enter n (dice), k (faces), target: ";
    cin >> n >> k >> target;
    
    TopDown td;
    BottomUp bu;
    
    cout << "\n--- Results ---" << endl;
    cout << "Top-Down: " << td.numRollsToTarget(n, k, target) << endl;
    cout << "Bottom-Up: " << bu.numRollsToTarget(n, k, target) << endl;
    cout << "Space Optimized: " << bu.numRollsToTargetOptimized(n, k, target) << endl;
    
    return 0;
}







