/*
    Assignment Problem (Bitmask DP)
    Problem: n workers, n jobs. cost[i][j] = cost of worker i doing job j.
             Assign each job to exactly one worker. Minimize total cost.
    
    Also known as: Minimum Cost Assignment / Hungarian Problem
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<int> dp;
    vector<vector<int>> cost;
    int n;
    
    int solve(int worker, int mask) {
        if (worker == n) return 0;
        if (dp[mask] != -1) return dp[mask];
        
        int minCost = INT_MAX;
        
        for (int job = 0; job < n; job++) {
            if (!(mask & (1 << job))) {
                int newMask = mask | (1 << job);
                minCost = min(minCost, cost[worker][job] + solve(worker + 1, newMask));
            }
        }
        
        return dp[mask] = minCost;
    }
    
public:
    int minCostAssignment(vector<vector<int>>& c) {
        cost = c;
        n = cost.size();
        dp.assign(1 << n, -1);
        return solve(0, 0);
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    int minCostAssignment(vector<vector<int>>& cost) {
        int n = cost.size();
        
        // dp[mask] = min cost to assign jobs in mask
        vector<int> dp(1 << n, INT_MAX);
        dp[0] = 0;
        
        for (int mask = 0; mask < (1 << n); mask++) {
            if (dp[mask] == INT_MAX) continue;
            
            int worker = __builtin_popcount(mask);
            if (worker >= n) continue;
            
            for (int job = 0; job < n; job++) {
                if (!(mask & (1 << job))) {
                    int newMask = mask | (1 << job);
                    dp[newMask] = min(dp[newMask], dp[mask] + cost[worker][job]);
                }
            }
        }
        
        return dp[(1 << n) - 1];
    }
    
    // Get the assignment
    vector<int> getAssignment(vector<vector<int>>& cost) {
        int n = cost.size();
        
        vector<int> dp(1 << n, INT_MAX);
        vector<int> parent(1 << n, -1);
        dp[0] = 0;
        
        for (int mask = 0; mask < (1 << n); mask++) {
            if (dp[mask] == INT_MAX) continue;
            
            int worker = __builtin_popcount(mask);
            if (worker >= n) continue;
            
            for (int job = 0; job < n; job++) {
                if (!(mask & (1 << job))) {
                    int newMask = mask | (1 << job);
                    if (dp[mask] + cost[worker][job] < dp[newMask]) {
                        dp[newMask] = dp[mask] + cost[worker][job];
                        parent[newMask] = mask;
                    }
                }
            }
        }
        
        // Reconstruct assignment
        vector<int> assignment(n);
        int mask = (1 << n) - 1;
        for (int worker = n - 1; worker >= 0; worker--) {
            int prevMask = parent[mask];
            int job = __builtin_ctz(mask ^ prevMask); // Find which bit differs
            assignment[worker] = job;
            mask = prevMask;
        }
        
        return assignment;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cout << "Enter number of workers/jobs: ";
    cin >> n;
    
    vector<vector<int>> cost(n, vector<int>(n));
    cout << "Enter cost matrix:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> cost[i][j];
        }
    }
    
    TopDown td;
    BottomUp bu;
    
    cout << "\n--- Results ---" << endl;
    cout << "Top-Down: " << td.minCostAssignment(cost) << endl;
    cout << "Bottom-Up: " << bu.minCostAssignment(cost) << endl;
    
    cout << "Assignment (worker → job): ";
    vector<int> assignment = bu.getAssignment(cost);
    for (int i = 0; i < n; i++) {
        cout << i << "→" << assignment[i] << " ";
    }
    cout << endl;
    
    return 0;
}


















