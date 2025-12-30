/*
    0/1 Knapsack Problem
    Problem: Given n items with weights and values, and a knapsack of capacity W,
             find the maximum value that can be put in the knapsack.
             Each item can be either included or excluded (0/1).
    
    Example:
    weights = [1, 2, 3], values = [10, 15, 40], capacity = 6
    Output: 65 (items with weight 2 and 3)
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<vector<int>> dp;
    vector<int> wt, val;
    
    int solve(int idx, int capacity) {
        // Base case: no items left or no capacity
        if (idx < 0 || capacity == 0) return 0;
        
        if (dp[idx][capacity] != -1) return dp[idx][capacity];
        
        // Don't take current item
        int notTake = solve(idx - 1, capacity);
        
        // Take current item (if possible)
        int take = 0;
        if (wt[idx] <= capacity) {
            take = val[idx] + solve(idx - 1, capacity - wt[idx]);
        }
        
        return dp[idx][capacity] = max(take, notTake);
    }
    
public:
    int knapsack(vector<int>& weights, vector<int>& values, int W) {
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
    int knapsack(vector<int>& wt, vector<int>& val, int W) {
        int n = wt.size();
        
        // dp[i][j] = max value using first i items with capacity j
        vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));
        
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= W; j++) {
                // Don't take item i-1
                dp[i][j] = dp[i - 1][j];
                
                // Take item i-1 if possible
                if (wt[i - 1] <= j) {
                    dp[i][j] = max(dp[i][j], val[i - 1] + dp[i - 1][j - wt[i - 1]]);
                }
            }
        }
        
        return dp[n][W];
    }
    
    // Space Optimized - O(W) space
    int knapsackOptimized(vector<int>& wt, vector<int>& val, int W) {
        int n = wt.size();
        vector<int> dp(W + 1, 0);
        
        for (int i = 0; i < n; i++) {
            // Traverse from right to left to avoid using updated values
            for (int j = W; j >= wt[i]; j--) {
                dp[j] = max(dp[j], val[i] + dp[j - wt[i]]);
            }
        }
        
        return dp[W];
    }
    
    // Print selected items
    vector<int> getSelectedItems(vector<int>& wt, vector<int>& val, int W) {
        int n = wt.size();
        vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));
        
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= W; j++) {
                dp[i][j] = dp[i - 1][j];
                if (wt[i - 1] <= j) {
                    dp[i][j] = max(dp[i][j], val[i - 1] + dp[i - 1][j - wt[i - 1]]);
                }
            }
        }
        
        // Backtrack to find selected items
        vector<int> selected;
        int i = n, j = W;
        while (i > 0 && j > 0) {
            if (dp[i][j] != dp[i - 1][j]) {
                selected.push_back(i - 1); // Item index
                j -= wt[i - 1];
            }
            i--;
        }
        
        reverse(selected.begin(), selected.end());
        return selected;
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
    cout << "Top-Down (Memoization): " << td.knapsack(weights, values, W) << endl;
    cout << "Bottom-Up (Tabulation): " << bu.knapsack(weights, values, W) << endl;
    cout << "Bottom-Up (Space Optimized): " << bu.knapsackOptimized(weights, values, W) << endl;
    
    cout << "Selected items (indices): ";
    vector<int> selected = bu.getSelectedItems(weights, values, W);
    for (int idx : selected) {
        cout << idx << " ";
    }
    cout << endl;
    
    return 0;
}

/*
    Time Complexity: O(n * W)
    Space Complexity:
        - Top-Down: O(n * W) for memoization + O(n) recursion stack
        - Bottom-Up: O(n * W)
        - Bottom-Up Optimized: O(W)
*/

