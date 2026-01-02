/*
    Best Time to Buy and Sell Stock (One Transaction)
    Problem: Find maximum profit with at most one buy and one sell.
    
    Example: prices = [7,1,5,3,6,4] → Output: 5 (buy at 1, sell at 6)
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<vector<int>> dp;
    vector<int> prices;
    
    // bought: 0 = can buy, 1 = already bought
    int solve(int idx, int bought) {
        if (idx == prices.size()) return 0;
        if (dp[idx][bought] != -1) return dp[idx][bought];
        
        if (bought == 0) {
            int buy = -prices[idx] + solve(idx + 1, 1);
            int skip = solve(idx + 1, 0);
            return dp[idx][bought] = max(buy, skip);
        } else {
            int sell = prices[idx]; // Only one transaction, so stop
            int skip = solve(idx + 1, 1);
            return dp[idx][bought] = max(sell, skip);
        }
    }
    
public:
    int maxProfit(vector<int>& p) {
        prices = p;
        int n = prices.size();
        dp.assign(n, vector<int>(2, -1));
        return solve(0, 0);
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if (n == 0) return 0;
        
        int minPrice = prices[0];
        int maxProfit = 0;
        
        for (int i = 1; i < n; i++) {
            maxProfit = max(maxProfit, prices[i] - minPrice);
            minPrice = min(minPrice, prices[i]);
        }
        
        return maxProfit;
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
    
    return 0;
}









