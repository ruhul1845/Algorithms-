/*
    Best Time to Buy and Sell Stock with Transaction Fee
    Problem: Pay fee for each transaction. Unlimited transactions allowed.
    
    Example: prices = [1,3,2,8,4,9], fee = 2 → Output: 8
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<vector<int>> dp;
    vector<int> prices;
    int fee;
    
    int solve(int idx, int canBuy) {
        if (idx == prices.size()) return 0;
        if (dp[idx][canBuy] != -1) return dp[idx][canBuy];
        
        if (canBuy) {
            int buy = -prices[idx] + solve(idx + 1, 0);
            int skip = solve(idx + 1, 1);
            return dp[idx][canBuy] = max(buy, skip);
        } else {
            int sell = prices[idx] - fee + solve(idx + 1, 1);
            int skip = solve(idx + 1, 0);
            return dp[idx][canBuy] = max(sell, skip);
        }
    }
    
public:
    int maxProfit(vector<int>& p, int f) {
        prices = p;
        fee = f;
        int n = prices.size();
        dp.assign(n, vector<int>(2, -1));
        return solve(0, 1);
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    int maxProfit(vector<int>& prices, int fee) {
        int n = prices.size();
        
        vector<vector<int>> dp(n + 1, vector<int>(2, 0));
        
        for (int i = n - 1; i >= 0; i--) {
            dp[i][1] = max(-prices[i] + dp[i + 1][0], dp[i + 1][1]);
            dp[i][0] = max(prices[i] - fee + dp[i + 1][1], dp[i + 1][0]);
        }
        
        return dp[0][1];
    }
    
    // Space Optimized
    int maxProfitOptimized(vector<int>& prices, int fee) {
        int n = prices.size();
        
        int aheadBuy = 0, aheadSell = 0;
        
        for (int i = n - 1; i >= 0; i--) {
            int currBuy = max(-prices[i] + aheadSell, aheadBuy);
            int currSell = max(prices[i] - fee + aheadBuy, aheadSell);
            aheadBuy = currBuy;
            aheadSell = currSell;
        }
        
        return aheadBuy;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, fee;
    cout << "Enter number of days: ";
    cin >> n;
    cout << "Enter transaction fee: ";
    cin >> fee;
    
    vector<int> prices(n);
    cout << "Enter prices: ";
    for (int i = 0; i < n; i++) cin >> prices[i];
    
    TopDown td;
    BottomUp bu;
    
    cout << "\n--- Results ---" << endl;
    cout << "Top-Down: " << td.maxProfit(prices, fee) << endl;
    cout << "Bottom-Up: " << bu.maxProfit(prices, fee) << endl;
    cout << "Bottom-Up Optimized: " << bu.maxProfitOptimized(prices, fee) << endl;
    
    return 0;
}







