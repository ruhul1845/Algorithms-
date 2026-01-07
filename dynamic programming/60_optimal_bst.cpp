/*
    Optimal Binary Search Tree
    Problem: Given keys and their search frequencies, construct BST
             that minimizes total search cost.
    
    Cost = sum of (depth + 1) * frequency for all keys
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<vector<int>> dp;
    vector<int> freq;
    vector<int> prefixSum;
    
    int sum(int i, int j) {
        return prefixSum[j + 1] - prefixSum[i];
    }
    
    int solve(int i, int j) {
        if (i > j) return 0;
        if (i == j) return freq[i];
        if (dp[i][j] != -1) return dp[i][j];
        
        int minCost = INT_MAX;
        
        // Try each key as root
        for (int r = i; r <= j; r++) {
            int cost = solve(i, r - 1) + solve(r + 1, j) + sum(i, j);
            minCost = min(minCost, cost);
        }
        
        return dp[i][j] = minCost;
    }
    
public:
    int optimalBST(vector<int>& keys, vector<int>& f) {
        freq = f;
        int n = keys.size();
        
        prefixSum.resize(n + 1, 0);
        for (int i = 0; i < n; i++) {
            prefixSum[i + 1] = prefixSum[i] + freq[i];
        }
        
        dp.assign(n, vector<int>(n, -1));
        return solve(0, n - 1);
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    int optimalBST(vector<int>& keys, vector<int>& freq) {
        int n = keys.size();
        
        // Prefix sum for range sum queries
        vector<int> prefixSum(n + 1, 0);
        for (int i = 0; i < n; i++) {
            prefixSum[i + 1] = prefixSum[i] + freq[i];
        }
        
        auto sum = [&](int i, int j) {
            return prefixSum[j + 1] - prefixSum[i];
        };
        
        vector<vector<int>> dp(n, vector<int>(n, 0));
        
        // Base case: single keys
        for (int i = 0; i < n; i++) {
            dp[i][i] = freq[i];
        }
        
        // Fill for increasing lengths
        for (int len = 2; len <= n; len++) {
            for (int i = 0; i <= n - len; i++) {
                int j = i + len - 1;
                dp[i][j] = INT_MAX;
                
                int freqSum = sum(i, j);
                
                for (int r = i; r <= j; r++) {
                    int left = (r > i) ? dp[i][r - 1] : 0;
                    int right = (r < j) ? dp[r + 1][j] : 0;
                    dp[i][j] = min(dp[i][j], left + right + freqSum);
                }
            }
        }
        
        return dp[0][n - 1];
    }
    
    // With Knuth's optimization O(n^2)
    int optimalBSTKnuth(vector<int>& keys, vector<int>& freq) {
        int n = keys.size();
        
        vector<int> prefixSum(n + 1, 0);
        for (int i = 0; i < n; i++) {
            prefixSum[i + 1] = prefixSum[i] + freq[i];
        }
        
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
        vector<vector<int>> root(n + 1, vector<int>(n + 1, 0));
        
        for (int i = 0; i < n; i++) {
            dp[i][i] = freq[i];
            root[i][i] = i;
        }
        
        for (int len = 2; len <= n; len++) {
            for (int i = 0; i <= n - len; i++) {
                int j = i + len - 1;
                dp[i][j] = INT_MAX;
                
                int freqSum = prefixSum[j + 1] - prefixSum[i];
                
                int lo = root[i][j - 1], hi = root[i + 1][j];
                if (j == i + 1) lo = hi = i;
                
                for (int r = lo; r <= hi && r <= j; r++) {
                    int left = (r > i) ? dp[i][r - 1] : 0;
                    int right = (r < j) ? dp[r + 1][j] : 0;
                    if (left + right + freqSum < dp[i][j]) {
                        dp[i][j] = left + right + freqSum;
                        root[i][j] = r;
                    }
                }
            }
        }
        
        return dp[0][n - 1];
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cout << "Enter number of keys: ";
    cin >> n;
    
    vector<int> keys(n), freq(n);
    cout << "Enter keys: ";
    for (int i = 0; i < n; i++) cin >> keys[i];
    cout << "Enter frequencies: ";
    for (int i = 0; i < n; i++) cin >> freq[i];
    
    TopDown td;
    BottomUp bu;
    
    cout << "\n--- Results ---" << endl;
    cout << "Top-Down: " << td.optimalBST(keys, freq) << endl;
    cout << "Bottom-Up: " << bu.optimalBST(keys, freq) << endl;
    cout << "Knuth Optimized: " << bu.optimalBSTKnuth(keys, freq) << endl;
    
    return 0;
}


















