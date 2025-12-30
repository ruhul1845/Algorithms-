/*
    Best Time to Buy and Sell Stock with Cooldown
    Problem: After selling, you must wait one day before buying again.
    
    Example: prices = [1,2,3,0,2] → Output: 3 (buy@1,sell@3,cooldown,buy@0,sell@2)
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<vector<int>> dp;
    vector<int> prices;
    
    int solve(int idx, int canBuy) {
        if (idx >= prices.size()) return 0;
        if (dp[idx][canBuy] != -1) return dp[idx][canBuy];
        
        if (canBuy) {
            int buy = -prices[idx] + solve(idx + 1, 0);
            int skip = solve(idx + 1, 1);
            return dp[idx][canBuy] = max(buy, skip);
        } else {
            int sell = prices[idx] + solve(idx + 2, 1); // cooldown: idx + 2
            int skip = solve(idx + 1, 0);
            return dp[idx][canBuy] = max(sell, skip);
        }
    }
    
public:
    int maxProfit(vector<int>& p) {
        prices = p;
        int n = prices.size();
        dp.assign(n, vector<int>(2, -1));
        return solve(0, 1);
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if (n <= 1) return 0;
        
        vector<vector<int>> dp(n + 2, vector<int>(2, 0));
        
        for (int i = n - 1; i >= 0; i--) {
            dp[i][1] = max(-prices[i] + dp[i + 1][0], dp[i + 1][1]);
            dp[i][0] = max(prices[i] + dp[i + 2][1], dp[i + 1][0]);
        }
        
        return dp[0][1];
    }
    
    // Space Optimized
    int maxProfitOptimized(vector<int>& prices) {
        int n = prices.size();
        if (n <= 1) return 0;
        
        int ahead2Buy = 0;
        int aheadBuy = 0, aheadSell = 0;
        
        for (int i = n - 1; i >= 0; i--) {
            int currBuy = max(-prices[i] + aheadSell, aheadBuy);
            int currSell = max(prices[i] + ahead2Buy, aheadSell);
            
            ahead2Buy = aheadBuy;
            aheadBuy = currBuy;
            aheadSell = currSell;
        }
        
        return aheadBuy;
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

