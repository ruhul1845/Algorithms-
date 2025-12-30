/*
    Dungeon Game
    Problem: Knight starts at (0,0), princess at (n-1,m-1).
             Each cell changes HP. Find minimum initial HP to rescue princess.
             HP must always be >= 1.
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<vector<int>> dp;
    vector<vector<int>> dungeon;
    int m, n;
    
    int solve(int i, int j) {
        if (i == m - 1 && j == n - 1) {
            return max(1, 1 - dungeon[i][j]);
        }
        if (i >= m || j >= n) return INT_MAX;
        if (dp[i][j] != -1) return dp[i][j];
        
        int right = solve(i, j + 1);
        int down = solve(i + 1, j);
        
        int minNext = min(right, down);
        int needed = minNext - dungeon[i][j];
        
        return dp[i][j] = max(1, needed);
    }
    
public:
    int calculateMinimumHP(vector<vector<int>>& d) {
        dungeon = d;
        m = dungeon.size();
        n = dungeon[0].size();
        dp.assign(m, vector<int>(n, -1));
        return solve(0, 0);
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        int m = dungeon.size(), n = dungeon[0].size();
        
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, INT_MAX));
        dp[m][n - 1] = dp[m - 1][n] = 1;
        
        for (int i = m - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                int minNext = min(dp[i + 1][j], dp[i][j + 1]);
                dp[i][j] = max(1, minNext - dungeon[i][j]);
            }
        }
        
        return dp[0][0];
    }
    
    // Space Optimized
    int calculateMinimumHPOptimized(vector<vector<int>>& dungeon) {
        int m = dungeon.size(), n = dungeon[0].size();
        
        vector<int> dp(n + 1, INT_MAX);
        dp[n - 1] = 1;
        
        for (int i = m - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                int minNext = min(dp[j], dp[j + 1]);
                dp[j] = max(1, minNext - dungeon[i][j]);
            }
            dp[n] = INT_MAX;
        }
        
        return dp[0];
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int m, n;
    cout << "Enter dungeon dimensions (m n): ";
    cin >> m >> n;
    
    vector<vector<int>> dungeon(m, vector<int>(n));
    cout << "Enter dungeon values:" << endl;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> dungeon[i][j];
        }
    }
    
    TopDown td;
    BottomUp bu;
    
    cout << "\n--- Results ---" << endl;
    cout << "Top-Down: " << td.calculateMinimumHP(dungeon) << endl;
    cout << "Bottom-Up: " << bu.calculateMinimumHP(dungeon) << endl;
    cout << "Bottom-Up Optimized: " << bu.calculateMinimumHPOptimized(dungeon) << endl;
    
    return 0;
}

