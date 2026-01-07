/*
    Min Cost Climbing Stairs
    Problem: Each step has a cost. You can start from step 0 or 1.
             Pay cost[i] to climb from step i. Find minimum cost to reach top.
    
    Example: cost = [10, 15, 20] → Output: 15 (start at index 1)
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<int> dp;
    vector<int> cost;
    
    int solve(int idx) {
        if (idx < 0) return 0;
        if (idx == 0 || idx == 1) return cost[idx];
        if (dp[idx] != -1) return dp[idx];
        
        return dp[idx] = cost[idx] + min(solve(idx-1), solve(idx-2));
    }
    
public:
    int minCostClimbingStairs(vector<int>& c) {
        cost = c;
        int n = cost.size();
        dp.assign(n, -1);
        return min(solve(n-1), solve(n-2));
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int n = cost.size();
        vector<int> dp(n);
        
        dp[0] = cost[0];
        dp[1] = cost[1];
        
        for (int i = 2; i < n; i++) {
            dp[i] = cost[i] + min(dp[i-1], dp[i-2]);
        }
        
        return min(dp[n-1], dp[n-2]);
    }
    
    // Space Optimized
    int minCostOptimized(vector<int>& cost) {
        int n = cost.size();
        int prev2 = cost[0];
        int prev1 = cost[1];
        
        for (int i = 2; i < n; i++) {
            int curr = cost[i] + min(prev1, prev2);
            prev2 = prev1;
            prev1 = curr;
        }
        
        return min(prev1, prev2);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cout << "Enter number of stairs: ";
    cin >> n;
    
    vector<int> cost(n);
    cout << "Enter cost of each stair: ";
    for (int i = 0; i < n; i++) cin >> cost[i];
    
    TopDown td;
    BottomUp bu;
    
    cout << "\n--- Results ---" << endl;
    cout << "Top-Down: " << td.minCostClimbingStairs(cost) << endl;
    cout << "Bottom-Up: " << bu.minCostClimbingStairs(cost) << endl;
    cout << "Bottom-Up Optimized: " << bu.minCostOptimized(cost) << endl;
    
    return 0;
}


















