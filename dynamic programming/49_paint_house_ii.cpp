/*
    Paint House II (k colors)
    Problem: n houses, k colors. Adjacent houses can't have same color.
             Find minimum cost.
    
    Optimization: Track min and second min to achieve O(nk) instead of O(nk²)
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<vector<int>> dp;
    vector<vector<int>> costs;
    int k;
    
    int solve(int idx, int lastColor) {
        if (idx == costs.size()) return 0;
        if (lastColor != -1 && dp[idx][lastColor] != -1) return dp[idx][lastColor];
        
        int minCost = INT_MAX;
        for (int color = 0; color < k; color++) {
            if (color != lastColor) {
                minCost = min(minCost, costs[idx][color] + solve(idx + 1, color));
            }
        }
        
        if (lastColor != -1) dp[idx][lastColor] = minCost;
        return minCost;
    }
    
public:
    int minCost(vector<vector<int>>& c) {
        costs = c;
        int n = costs.size();
        if (n == 0) return 0;
        k = costs[0].size();
        dp.assign(n, vector<int>(k, -1));
        return solve(0, -1);
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    int minCost(vector<vector<int>>& costs) {
        int n = costs.size();
        if (n == 0) return 0;
        int k = costs[0].size();
        
        // Track min, second min and min index
        int min1 = 0, min2 = 0, minIdx = -1;
        
        for (int i = 0; i < n; i++) {
            int newMin1 = INT_MAX, newMin2 = INT_MAX, newMinIdx = -1;
            
            for (int j = 0; j < k; j++) {
                int cost;
                if (j != minIdx) {
                    cost = costs[i][j] + min1;
                } else {
                    cost = costs[i][j] + min2;
                }
                
                if (cost < newMin1) {
                    newMin2 = newMin1;
                    newMin1 = cost;
                    newMinIdx = j;
                } else if (cost < newMin2) {
                    newMin2 = cost;
                }
            }
            
            min1 = newMin1;
            min2 = newMin2;
            minIdx = newMinIdx;
        }
        
        return min1;
    }
    
    // Standard O(nk²) approach
    int minCostNaive(vector<vector<int>>& costs) {
        int n = costs.size();
        if (n == 0) return 0;
        int k = costs[0].size();
        
        vector<vector<int>> dp = costs;
        
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < k; j++) {
                int minPrev = INT_MAX;
                for (int p = 0; p < k; p++) {
                    if (p != j) {
                        minPrev = min(minPrev, dp[i-1][p]);
                    }
                }
                dp[i][j] = costs[i][j] + minPrev;
            }
        }
        
        return *min_element(dp[n-1].begin(), dp[n-1].end());
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k;
    cout << "Enter number of houses and colors: ";
    cin >> n >> k;
    
    vector<vector<int>> costs(n, vector<int>(k));
    cout << "Enter costs matrix:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++) {
            cin >> costs[i][j];
        }
    }
    
    TopDown td;
    BottomUp bu;
    
    cout << "\n--- Results ---" << endl;
    cout << "Top-Down: " << td.minCost(costs) << endl;
    cout << "Bottom-Up O(nk): " << bu.minCost(costs) << endl;
    cout << "Bottom-Up O(nk²): " << bu.minCostNaive(costs) << endl;
    
    return 0;
}



