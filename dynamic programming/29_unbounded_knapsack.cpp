/*
    Unbounded Knapsack
    Problem: Items can be selected unlimited times. Maximize value within capacity.
    
    Example: weights = [1, 3, 4], values = [15, 50, 60], capacity = 8
             Output: 120 (using weight 4 twice)
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<vector<int>> dp;
    vector<int> wt, val;
    
    int solve(int idx, int capacity) {
        if (idx < 0 || capacity == 0) return 0;
        if (dp[idx][capacity] != -1) return dp[idx][capacity];
        
        int notTake = solve(idx - 1, capacity);
        int take = 0;
        if (wt[idx] <= capacity) {
            take = val[idx] + solve(idx, capacity - wt[idx]); // same idx!
        }
        
        return dp[idx][capacity] = max(take, notTake);
    }
    
public:
    int unboundedKnapsack(vector<int>& weights, vector<int>& values, int W) {
        wt = weights;
        val = values;
        int n = weights.size();
        dp.assign(n, vector<int>(W + 1, -1));
        return solve(n - 1, W);
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    int unboundedKnapsack(vector<int>& wt, vector<int>& val, int W) {
        int n = wt.size();
        vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));
        
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= W; j++) {
                dp[i][j] = dp[i - 1][j];
                if (wt[i - 1] <= j) {
                    dp[i][j] = max(dp[i][j], val[i - 1] + dp[i][j - wt[i - 1]]);
                }
            }
        }
        
        return dp[n][W];
    }
    
    // Space Optimized O(W)
    int unboundedKnapsackOptimized(vector<int>& wt, vector<int>& val, int W) {
        int n = wt.size();
        vector<int> dp(W + 1, 0);
        
        for (int i = 0; i < n; i++) {
            for (int j = wt[i]; j <= W; j++) { // left to right!
                dp[j] = max(dp[j], val[i] + dp[j - wt[i]]);
            }
        }
        
        return dp[W];
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, W;
    cout << "Enter number of items: ";
    cin >> n;
    cout << "Enter knapsack capacity: ";
    cin >> W;
    
    vector<int> weights(n), values(n);
    cout << "Enter weights: ";
    for (int i = 0; i < n; i++) cin >> weights[i];
    cout << "Enter values: ";
    for (int i = 0; i < n; i++) cin >> values[i];
    
    TopDown td;
    BottomUp bu;
    
    cout << "\n--- Results ---" << endl;
    cout << "Top-Down: " << td.unboundedKnapsack(weights, values, W) << endl;
    cout << "Bottom-Up: " << bu.unboundedKnapsack(weights, values, W) << endl;
    cout << "Bottom-Up Optimized: " << bu.unboundedKnapsackOptimized(weights, values, W) << endl;
    
    return 0;
}







