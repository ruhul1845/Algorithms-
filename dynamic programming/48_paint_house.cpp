/*
    Paint House
    Problem: n houses, 3 colors (R,G,B). Adjacent houses can't have same color.
             costs[i][j] = cost of painting house i with color j.
    
    Example: costs = [[17,2,17],[16,16,5],[14,3,19]] → Output: 10
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<vector<int>> dp;
    vector<vector<int>> costs;
    
    int solve(int idx, int lastColor) {
        if (idx == costs.size()) return 0;
        if (dp[idx][lastColor] != -1) return dp[idx][lastColor];
        
        int minCost = INT_MAX;
        for (int color = 0; color < 3; color++) {
            if (color != lastColor) {
                minCost = min(minCost, costs[idx][color] + solve(idx + 1, color));
            }
        }
        
        return dp[idx][lastColor] = minCost;
    }
    
public:
    int minCost(vector<vector<int>>& c) {
        costs = c;
        int n = costs.size();
        dp.assign(n, vector<int>(4, -1)); // 3 = no previous color
        return solve(0, 3);
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    int minCost(vector<vector<int>>& costs) {
        int n = costs.size();
        if (n == 0) return 0;
        
        // dp[i][j] = min cost to paint houses 0..i with house i having color j
        vector<vector<int>> dp(n, vector<int>(3));
        
        dp[0][0] = costs[0][0];
        dp[0][1] = costs[0][1];
        dp[0][2] = costs[0][2];
        
        for (int i = 1; i < n; i++) {
            dp[i][0] = costs[i][0] + min(dp[i-1][1], dp[i-1][2]);
            dp[i][1] = costs[i][1] + min(dp[i-1][0], dp[i-1][2]);
            dp[i][2] = costs[i][2] + min(dp[i-1][0], dp[i-1][1]);
        }
        
        return min({dp[n-1][0], dp[n-1][1], dp[n-1][2]});
    }
    
    // Space Optimized O(1)
    int minCostOptimized(vector<vector<int>>& costs) {
        int n = costs.size();
        if (n == 0) return 0;
        
        int r = costs[0][0], g = costs[0][1], b = costs[0][2];
        
        for (int i = 1; i < n; i++) {
            int newR = costs[i][0] + min(g, b);
            int newG = costs[i][1] + min(r, b);
            int newB = costs[i][2] + min(r, g);
            r = newR; g = newG; b = newB;
        }
        
        return min({r, g, b});
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cout << "Enter number of houses: ";
    cin >> n;
    
    vector<vector<int>> costs(n, vector<int>(3));
    cout << "Enter costs (R G B for each house):" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> costs[i][j];
        }
    }
    
    TopDown td;
    BottomUp bu;
    
    cout << "\n--- Results ---" << endl;
    cout << "Top-Down: " << td.minCost(costs) << endl;
    cout << "Bottom-Up: " << bu.minCost(costs) << endl;
    cout << "Bottom-Up Optimized: " << bu.minCostOptimized(costs) << endl;
    
    return 0;
}


















