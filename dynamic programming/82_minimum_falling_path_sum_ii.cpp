/*
    Minimum Falling Path Sum II
    Problem: Non-zero shift falling path. Next row's column must be different.
    
    Optimization: Track min and second min to achieve O(n²) instead of O(n³)
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<vector<int>> dp;
    vector<vector<int>> grid;
    int n;
    
    int solve(int row, int col) {
        if (row == n - 1) return grid[row][col];
        if (dp[row][col] != INT_MAX) return dp[row][col];
        
        int minNext = INT_MAX;
        for (int nextCol = 0; nextCol < n; nextCol++) {
            if (nextCol != col) {
                minNext = min(minNext, solve(row + 1, nextCol));
            }
        }
        
        return dp[row][col] = grid[row][col] + minNext;
    }
    
public:
    int minFallingPathSum(vector<vector<int>>& g) {
        grid = g;
        n = grid.size();
        dp.assign(n, vector<int>(n, INT_MAX));
        
        int minSum = INT_MAX;
        for (int col = 0; col < n; col++) {
            minSum = min(minSum, solve(0, col));
        }
        
        return minSum;
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    // O(n²) optimized
    int minFallingPathSum(vector<vector<int>>& grid) {
        int n = grid.size();
        if (n == 1) return grid[0][0];
        
        // Track min and second min for each row
        int min1 = 0, min2 = 0, minIdx = -1;
        
        for (int row = 0; row < n; row++) {
            int newMin1 = INT_MAX, newMin2 = INT_MAX, newMinIdx = -1;
            
            for (int col = 0; col < n; col++) {
                int val;
                if (col != minIdx) {
                    val = grid[row][col] + min1;
                } else {
                    val = grid[row][col] + min2;
                }
                
                if (val < newMin1) {
                    newMin2 = newMin1;
                    newMin1 = val;
                    newMinIdx = col;
                } else if (val < newMin2) {
                    newMin2 = val;
                }
            }
            
            min1 = newMin1;
            min2 = newMin2;
            minIdx = newMinIdx;
        }
        
        return min1;
    }
    
    // O(n³) naive approach
    int minFallingPathSumNaive(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<vector<int>> dp = grid;
        
        for (int row = n - 2; row >= 0; row--) {
            for (int col = 0; col < n; col++) {
                int minNext = INT_MAX;
                for (int nextCol = 0; nextCol < n; nextCol++) {
                    if (nextCol != col) {
                        minNext = min(minNext, dp[row + 1][nextCol]);
                    }
                }
                dp[row][col] += minNext;
            }
        }
        
        return *min_element(dp[0].begin(), dp[0].end());
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cout << "Enter grid size: ";
    cin >> n;
    
    vector<vector<int>> grid(n, vector<int>(n));
    cout << "Enter grid:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }
    
    TopDown td;
    BottomUp bu;
    
    cout << "\n--- Results ---" << endl;
    cout << "Top-Down: " << td.minFallingPathSum(grid) << endl;
    cout << "Bottom-Up O(n²): " << bu.minFallingPathSum(grid) << endl;
    cout << "Bottom-Up O(n³): " << bu.minFallingPathSumNaive(grid) << endl;
    
    return 0;
}









