/*
    Coin Change II - Count Ways
    Problem: Count number of combinations to make up amount using coins.
    
    Example: coins = [1, 2, 5], amount = 5 → Output: 4
             (5, 2+2+1, 2+1+1+1, 1+1+1+1+1)
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<vector<int>> dp;
    vector<int> coins;
    
    int solve(int idx, int amount) {
        if (amount == 0) return 1;
        if (idx < 0 || amount < 0) return 0;
        if (dp[idx][amount] != -1) return dp[idx][amount];
        
        int notTake = solve(idx - 1, amount);
        int take = 0;
        if (coins[idx] <= amount) {
            take = solve(idx, amount - coins[idx]); // same idx for unlimited
        }
        
        return dp[idx][amount] = take + notTake;
    }
    
public:
    int change(int amount, vector<int>& c) {
        coins = c;
        int n = coins.size();
        dp.assign(n, vector<int>(amount + 1, -1));
        return solve(n - 1, amount);
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    int change(int amount, vector<int>& coins) {
        int n = coins.size();
        vector<vector<int>> dp(n + 1, vector<int>(amount + 1, 0));
        
        for (int i = 0; i <= n; i++) dp[i][0] = 1;
        
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= amount; j++) {
                dp[i][j] = dp[i - 1][j];
                if (coins[i - 1] <= j) {
                    dp[i][j] += dp[i][j - coins[i - 1]];
                }
            }
        }
        
        return dp[n][amount];
    }
    
    // Space Optimized O(amount)
    int changeOptimized(int amount, vector<int>& coins) {
        vector<int> dp(amount + 1, 0);
        dp[0] = 1;
        
        for (int coin : coins) {
            for (int j = coin; j <= amount; j++) {
                dp[j] += dp[j - coin];
            }
        }
        
        return dp[amount];
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, amount;
    cout << "Enter number of coin types: ";
    cin >> n;
    cout << "Enter amount: ";
    cin >> amount;
    
    vector<int> coins(n);
    cout << "Enter coin denominations: ";
    for (int i = 0; i < n; i++) cin >> coins[i];
    
    TopDown td;
    BottomUp bu;
    
    cout << "\n--- Results ---" << endl;
    cout << "Top-Down: " << td.change(amount, coins) << endl;
    cout << "Bottom-Up: " << bu.change(amount, coins) << endl;
    cout << "Bottom-Up Optimized: " << bu.changeOptimized(amount, coins) << endl;
    
    return 0;
}

