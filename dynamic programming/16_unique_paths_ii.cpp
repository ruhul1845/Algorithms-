/*
    Unique Paths II (With Obstacles)
    Problem: Grid has obstacles (1 = obstacle, 0 = empty).
             Count paths from top-left to bottom-right.
    
    Example: [[0,0,0],[0,1,0],[0,0,0]] → Output: 2
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<vector<int>> dp;
    vector<vector<int>> grid;
    int m, n;
    
    int solve(int i, int j) {
        if (i < 0 || j < 0 || grid[i][j] == 1) return 0;
        if (i == 0 && j == 0) return 1;
        if (dp[i][j] != -1) return dp[i][j];
        
        return dp[i][j] = solve(i-1, j) + solve(i, j-1);
    }
    
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        grid = obstacleGrid;
        m = grid.size();
        n = grid[0].size();
        if (grid[0][0] == 1 || grid[m-1][n-1] == 1) return 0;
        dp.assign(m, vector<int>(n, -1));
        return solve(m-1, n-1);
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        if (grid[0][0] == 1 || grid[m-1][n-1] == 1) return 0;
        
        vector<vector<long long>> dp(m, vector<long long>(n, 0));
        
        // Fill first row
        for (int j = 0; j < n && grid[0][j] == 0; j++) {
            dp[0][j] = 1;
        }
        
        // Fill first column
        for (int i = 0; i < m && grid[i][0] == 0; i++) {
            dp[i][0] = 1;
        }
        
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                if (grid[i][j] == 0) {
                    dp[i][j] = dp[i-1][j] + dp[i][j-1];
                }
            }
        }
        
        return dp[m-1][n-1];
    }
    
    // Space Optimized
    int uniquePathsOptimized(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        if (grid[0][0] == 1) return 0;
        
        vector<long long> dp(n, 0);
        dp[0] = 1;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    dp[j] = 0;
                } else if (j > 0) {
                    dp[j] += dp[j-1];
                }
            }
        }
        
        return dp[n-1];
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int m, n;
    cout << "Enter grid dimensions (m n): ";
    cin >> m >> n;
    
    vector<vector<int>> grid(m, vector<int>(n));
    cout << "Enter grid (0=empty, 1=obstacle):" << endl;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }
    
    TopDown td;
    BottomUp bu;
    
    cout << "\n--- Results ---" << endl;
    cout << "Top-Down: " << td.uniquePathsWithObstacles(grid) << endl;
    cout << "Bottom-Up: " << bu.uniquePathsWithObstacles(grid) << endl;
    cout << "Bottom-Up Optimized: " << bu.uniquePathsOptimized(grid) << endl;
    
    return 0;
}



