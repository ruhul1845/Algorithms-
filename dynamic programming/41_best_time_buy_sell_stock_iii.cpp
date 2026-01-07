/*
    Best Time to Buy and Sell Stock III (At Most 2 Transactions)
    Problem: Maximum profit with at most 2 transactions.
    
    Example: prices = [3,3,5,0,0,3,1,4] → Output: 6 (buy@0,sell@3 + buy@1,sell@4)
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<vector<vector<int>>> dp;
    vector<int> prices;
    
    int solve(int idx, int canBuy, int trans) {
        if (idx == prices.size() || trans == 0) return 0;
        if (dp[idx][canBuy][trans] != -1) return dp[idx][canBuy][trans];
        
        if (canBuy) {
            int buy = -prices[idx] + solve(idx + 1, 0, trans);
            int skip = solve(idx + 1, 1, trans);
            return dp[idx][canBuy][trans] = max(buy, skip);
        } else {
            int sell = prices[idx] + solve(idx + 1, 1, trans - 1);
            int skip = solve(idx + 1, 0, trans);
            return dp[idx][canBuy][trans] = max(sell, skip);
        }
    }
    
public:
    int maxProfit(vector<int>& p) {
        prices = p;
        int n = prices.size();
        dp.assign(n, vector<vector<int>>(2, vector<int>(3, -1)));
        return solve(0, 1, 2);
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if (n == 0) return 0;
        
        // dp[i][j][k] = max profit at day i, j=canBuy, k=transactions left
        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(2, vector<int>(3, 0)));
        
        for (int i = n - 1; i >= 0; i--) {
            for (int trans = 1; trans <= 2; trans++) {
                // Can buy
                dp[i][1][trans] = max(-prices[i] + dp[i + 1][0][trans], dp[i + 1][1][trans]);
                // Must sell
                dp[i][0][trans] = max(prices[i] + dp[i + 1][1][trans - 1], dp[i + 1][0][trans]);
            }
        }
        
        return dp[0][1][2];
    }
    
    // Space Optimized
    int maxProfitOptimized(vector<int>& prices) {
        int buy1 = INT_MIN, sell1 = 0;
        int buy2 = INT_MIN, sell2 = 0;
        
        for (int price : prices) {
            buy1 = max(buy1, -price);
            sell1 = max(sell1, buy1 + price);
            buy2 = max(buy2, sell1 - price);
            sell2 = max(sell2, buy2 + price);
        }
        
        return sell2;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cout << "Enter number of days: ";
    cin >> n;
    
    vector<int> prices(n);
    cout << "Enter prices: ";
    for (int i = 0; i < n; i++) cin >> prices[i];
    
    TopDown td;
    BottomUp bu;
    
    cout << "\n--- Results ---" << endl;
    cout << "Top-Down: " << td.maxProfit(prices) << endl;
    cout << "Bottom-Up: " << bu.maxProfit(prices) << endl;
    cout << "Bottom-Up Optimized: " << bu.maxProfitOptimized(prices) << endl;
    
    return 0;
}


















