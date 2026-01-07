/*
    Best Time to Buy and Sell Stock IV (At Most K Transactions)
    Problem: Maximum profit with at most k transactions.
    
    Example: k = 2, prices = [3,2,6,5,0,3] → Output: 7
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<vector<vector<int>>> dp;
    vector<int> prices;
    int K;
    
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
    int maxProfit(int k, vector<int>& p) {
        prices = p;
        int n = prices.size();
        K = k;
        dp.assign(n, vector<vector<int>>(2, vector<int>(k + 1, -1)));
        return solve(0, 1, k);
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        if (n == 0 || k == 0) return 0;
        
        // If k >= n/2, we can make unlimited transactions
        if (k >= n / 2) {
            int profit = 0;
            for (int i = 1; i < n; i++) {
                if (prices[i] > prices[i - 1]) {
                    profit += prices[i] - prices[i - 1];
                }
            }
            return profit;
        }
        
        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(2, vector<int>(k + 1, 0)));
        
        for (int i = n - 1; i >= 0; i--) {
            for (int trans = 1; trans <= k; trans++) {
                dp[i][1][trans] = max(-prices[i] + dp[i + 1][0][trans], dp[i + 1][1][trans]);
                dp[i][0][trans] = max(prices[i] + dp[i + 1][1][trans - 1], dp[i + 1][0][trans]);
            }
        }
        
        return dp[0][1][k];
    }
    
    // Space Optimized O(k)
    int maxProfitOptimized(int k, vector<int>& prices) {
        int n = prices.size();
        if (n == 0 || k == 0) return 0;
        
        if (k >= n / 2) {
            int profit = 0;
            for (int i = 1; i < n; i++) {
                profit += max(0, prices[i] - prices[i - 1]);
            }
            return profit;
        }
        
        vector<int> buy(k + 1, INT_MIN);
        vector<int> sell(k + 1, 0);
        
        for (int price : prices) {
            for (int j = 1; j <= k; j++) {
                buy[j] = max(buy[j], sell[j - 1] - price);
                sell[j] = max(sell[j], buy[j] + price);
            }
        }
        
        return sell[k];
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k;
    cout << "Enter number of days: ";
    cin >> n;
    cout << "Enter max transactions k: ";
    cin >> k;
    
    vector<int> prices(n);
    cout << "Enter prices: ";
    for (int i = 0; i < n; i++) cin >> prices[i];
    
    TopDown td;
    BottomUp bu;
    
    cout << "\n--- Results ---" << endl;
    cout << "Top-Down: " << td.maxProfit(k, prices) << endl;
    cout << "Bottom-Up: " << bu.maxProfit(k, prices) << endl;
    cout << "Bottom-Up Optimized: " << bu.maxProfitOptimized(k, prices) << endl;
    
    return 0;
}


















