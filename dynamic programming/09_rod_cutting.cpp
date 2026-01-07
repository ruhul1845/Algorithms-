/*
    Rod Cutting Problem
    Problem: Given a rod of length n and prices for each length,
             find the maximum revenue obtainable by cutting the rod
             and selling the pieces.
    
    Example:
    length = 8, prices = [1, 5, 8, 9, 10, 17, 17, 20]
    (prices[i] = price of rod of length i+1)
    Output: Maximum revenue
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<int> dp;
    vector<int> prices;
    
    int solve(int n) {
        // Base case: no rod left
        if (n <= 0) return 0;
        
        if (dp[n] != -1) return dp[n];
        
        int maxRevenue = 0;
        
        // Try all possible first cuts
        for (int i = 1; i <= n; i++) {
            maxRevenue = max(maxRevenue, prices[i - 1] + solve(n - i));
        }
        
        return dp[n] = maxRevenue;
    }
    
public:
    int rodCutting(vector<int>& price, int n) {
        prices = price;
        dp.assign(n + 1, -1);
        return solve(n);
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    int rodCutting(vector<int>& prices, int n) {
        // dp[i] = maximum revenue for rod of length i
        vector<int> dp(n + 1, 0);
        
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= i; j++) {
                dp[i] = max(dp[i], prices[j - 1] + dp[i - j]);
            }
        }
        
        return dp[n];
    }
    
    // Alternative: Using unbounded knapsack approach
    int rodCuttingKnapsack(vector<int>& prices, int n) {
        vector<int> dp(n + 1, 0);
        
        for (int i = 0; i < n; i++) {  // For each piece length
            for (int j = i + 1; j <= n; j++) {  // For each rod length
                dp[j] = max(dp[j], dp[j - (i + 1)] + prices[i]);
            }
        }
        
        return dp[n];
    }
    
    // Get the cuts to make
    vector<int> getCuts(vector<int>& prices, int n) {
        vector<int> dp(n + 1, 0);
        vector<int> cut(n + 1, 0);  // cut[i] = length of first piece for rod of length i
        
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= i; j++) {
                if (prices[j - 1] + dp[i - j] > dp[i]) {
                    dp[i] = prices[j - 1] + dp[i - j];
                    cut[i] = j;
                }
            }
        }
        
        // Reconstruct the cuts
        vector<int> cuts;
        int remaining = n;
        while (remaining > 0) {
            cuts.push_back(cut[remaining]);
            remaining -= cut[remaining];
        }
        
        return cuts;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cout << "Enter rod length: ";
    cin >> n;
    
    vector<int> prices(n);
    cout << "Enter prices for lengths 1 to " << n << ": ";
    for (int i = 0; i < n; i++) {
        cin >> prices[i];
    }
    
    TopDown td;
    BottomUp bu;
    
    cout << "\n--- Results ---" << endl;
    cout << "Top-Down (Memoization): " << td.rodCutting(prices, n) << endl;
    cout << "Bottom-Up (Tabulation): " << bu.rodCutting(prices, n) << endl;
    cout << "Bottom-Up (Knapsack style): " << bu.rodCuttingKnapsack(prices, n) << endl;
    
    cout << "Cuts to make: ";
    vector<int> cuts = bu.getCuts(prices, n);
    for (int c : cuts) {
        cout << c << " ";
    }
    cout << endl;
    
    return 0;
}

/*
    Time Complexity: O(n^2)
    Space Complexity: O(n)
    
    Note: This is similar to unbounded knapsack where we can use
          each piece length unlimited times.
*/


















