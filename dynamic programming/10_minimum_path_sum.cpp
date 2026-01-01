/*
    Minimum Path Sum
    Problem: Given an m x n grid filled with non-negative numbers,
             find a path from top-left to bottom-right that minimizes
             the sum of all numbers along the path.
             You can only move right or down at any point.
    
    Example:
    grid = [[1, 3, 1],
            [1, 5, 1],
            [4, 2, 1]]
    Output: 7 (path: 1→3→1→1→1)
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
        // Base case: reached destination
        if (i == m - 1 && j == n - 1) return grid[i][j];
        
        // Out of bounds
        if (i >= m || j >= n) return INT_MAX;
        
        if (dp[i][j] != -1) return dp[i][j];
        
        // Move right or down
        int right = solve(i, j + 1);
        int down = solve(i + 1, j);
        
        return dp[i][j] = grid[i][j] + min(right, down);
    }
    
public:
    int minPathSum(vector<vector<int>>& g) {
        grid = g;
        m = g.size();
        n = g[0].size();
        dp.assign(m, vector<int>(n, -1));
        return solve(0, 0);
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        
        // dp[i][j] = minimum path sum to reach (i, j)
        vector<vector<int>> dp(m, vector<int>(n, 0));
        
        dp[0][0] = grid[0][0];
        
        // Fill first row
        for (int j = 1; j < n; j++) {
            dp[0][j] = dp[0][j - 1] + grid[0][j];
        }
        
        // Fill first column
        for (int i = 1; i < m; i++) {
            dp[i][0] = dp[i - 1][0] + grid[i][0];
        }
        
        // Fill rest of the grid
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                dp[i][j] = grid[i][j] + min(dp[i - 1][j], dp[i][j - 1]);
            }
        }
        
        return dp[m - 1][n - 1];
    }
    
    // Space Optimized - O(n) space
    int minPathSumOptimized(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<int> dp(n, 0);
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (i == 0 && j == 0) {
                    dp[j] = grid[i][j];
                } else if (i == 0) {
                    dp[j] = dp[j - 1] + grid[i][j];
                } else if (j == 0) {
                    dp[j] = dp[j] + grid[i][j];
                } else {
                    dp[j] = grid[i][j] + min(dp[j], dp[j - 1]);
                }
            }
        }
        
        return dp[n - 1];
    }
    
    // In-place modification - O(1) extra space
    int minPathSumInPlace(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (i == 0 && j == 0) continue;
                else if (i == 0) grid[i][j] += grid[i][j - 1];
                else if (j == 0) grid[i][j] += grid[i - 1][j];
                else grid[i][j] += min(grid[i - 1][j], grid[i][j - 1]);
            }
        }
        
        return grid[m - 1][n - 1];
    }
    
    // Print the path
    vector<pair<int, int>> getPath(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> dp(m, vector<int>(n, 0));
        
        dp[0][0] = grid[0][0];
        for (int j = 1; j < n; j++) dp[0][j] = dp[0][j - 1] + grid[0][j];
        for (int i = 1; i < m; i++) dp[i][0] = dp[i - 1][0] + grid[i][0];
        
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                dp[i][j] = grid[i][j] + min(dp[i - 1][j], dp[i][j - 1]);
            }
        }
        
        // Backtrack to find path
        vector<pair<int, int>> path;
        int i = m - 1, j = n - 1;
        path.push_back({i, j});
        
        while (i > 0 || j > 0) {
            if (i == 0) {
                j--;
            } else if (j == 0) {
                i--;
            } else if (dp[i - 1][j] < dp[i][j - 1]) {
                i--;
            } else {
                j--;
            }
            path.push_back({i, j});
        }
        
        reverse(path.begin(), path.end());
        return path;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int m, n;
    cout << "Enter grid dimensions (m n): ";
    cin >> m >> n;
    
    vector<vector<int>> grid(m, vector<int>(n));
    cout << "Enter grid values:" << endl;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }
    
    // Make copies for different methods
    vector<vector<int>> grid2 = grid;
    
    TopDown td;
    BottomUp bu;
    
    cout << "\n--- Results ---" << endl;
    cout << "Top-Down (Memoization): " << td.minPathSum(grid) << endl;
    cout << "Bottom-Up (Tabulation): " << bu.minPathSum(grid) << endl;
    cout << "Bottom-Up (Space Optimized): " << bu.minPathSumOptimized(grid) << endl;
    
    cout << "Path: ";
    vector<pair<int, int>> path = bu.getPath(grid);
    for (auto& p : path) {
        cout << "(" << p.first << "," << p.second << ") ";
    }
    cout << endl;
    
    cout << "Path values: ";
    for (auto& p : path) {
        cout << grid[p.first][p.second] << " ";
    }
    cout << endl;
    
    return 0;
}

/*
    Time Complexity: O(m * n)
    Space Complexity:
        - Top-Down: O(m * n) for memoization + O(m + n) recursion stack
        - Bottom-Up: O(m * n)
        - Bottom-Up Optimized: O(n)
        - In-place: O(1) extra space (modifies input)
*/







