/*
    Coin Change Problem
    Problem: Given coins of different denominations and a total amount,
             find the minimum number of coins needed to make up that amount.
             If not possible, return -1.
    
    Example:
    coins = [1, 2, 5], amount = 11
    Output: 3 (5 + 5 + 1)
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<int> dp;
    vector<int> coins;
    
    int solve(int amount) {
        // Base case
        if (amount == 0) return 0;
        if (amount < 0) return INT_MAX;
        
        if (dp[amount] != -1) return dp[amount];
        
        int minCoins = INT_MAX;
        for (int coin : coins) {
            if (coin <= amount) {
                int result = solve(amount - coin);
                if (result != INT_MAX) {
                    minCoins = min(minCoins, 1 + result);
                }
            }
        }
        
        return dp[amount] = minCoins;
    }
    
public:
    int coinChange(vector<int>& c, int amount) {
        coins = c;
        dp.assign(amount + 1, -1);
        int result = solve(amount);
        return (result == INT_MAX) ? -1 : result;
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    int coinChange(vector<int>& coins, int amount) {
        // dp[i] = minimum coins needed to make amount i
        vector<int> dp(amount + 1, INT_MAX);
        dp[0] = 0;
        
        for (int i = 1; i <= amount; i++) {
            for (int coin : coins) {
                if (coin <= i && dp[i - coin] != INT_MAX) {
                    dp[i] = min(dp[i], 1 + dp[i - coin]);
                }
            }
        }
        
        return (dp[amount] == INT_MAX) ? -1 : dp[amount];
    }
    
    // Count number of ways to make change
    int countWays(vector<int>& coins, int amount) {
        vector<long long> dp(amount + 1, 0);
        dp[0] = 1;
        
        // For each coin, update all amounts that can use it
        for (int coin : coins) {
            for (int i = coin; i <= amount; i++) {
                dp[i] += dp[i - coin];
            }
        }
        
        return dp[amount];
    }
    
    // Print one solution (which coins to use)
    vector<int> getCoins(vector<int>& coins, int amount) {
        vector<int> dp(amount + 1, INT_MAX);
        vector<int> parent(amount + 1, -1);
        dp[0] = 0;
        
        for (int i = 1; i <= amount; i++) {
            for (int coin : coins) {
                if (coin <= i && dp[i - coin] != INT_MAX) {
                    if (1 + dp[i - coin] < dp[i]) {
                        dp[i] = 1 + dp[i - coin];
                        parent[i] = coin;
                    }
                }
            }
        }
        
        vector<int> result;
        if (dp[amount] == INT_MAX) return result;
        
        int curr = amount;
        while (curr > 0) {
            result.push_back(parent[curr]);
            curr -= parent[curr];
        }
        
        return result;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, amount;
    cout << "Enter number of coin types: ";
    cin >> n;
    cout << "Enter target amount: ";
    cin >> amount;
    
    vector<int> coins(n);
    cout << "Enter coin denominations: ";
    for (int i = 0; i < n; i++) cin >> coins[i];
    
    TopDown td;
    BottomUp bu;
    
    cout << "\n--- Results ---" << endl;
    cout << "Top-Down (Memoization): " << td.coinChange(coins, amount) << endl;
    cout << "Bottom-Up (Tabulation): " << bu.coinChange(coins, amount) << endl;
    cout << "Number of ways: " << bu.countWays(coins, amount) << endl;
    
    cout << "Coins used: ";
    vector<int> coinsUsed = bu.getCoins(coins, amount);
    for (int c : coinsUsed) {
        cout << c << " ";
    }
    cout << endl;
    
    return 0;
}

/*
    Time Complexity: O(amount * n) where n is number of coin types
    Space Complexity: O(amount)
*/







