/*
    Cherry Pickup II
    Problem: Two robots start at (0,0) and (0,cols-1). Both move down.
             Collect max cherries. If both on same cell, count once.
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<vector<vector<int>>> dp;
    vector<vector<int>> grid;
    int rows, cols;
    
    int solve(int row, int c1, int c2) {
        if (row == rows) return 0;
        if (c1 < 0 || c1 >= cols || c2 < 0 || c2 >= cols) return INT_MIN;
        if (dp[row][c1][c2] != -1) return dp[row][c1][c2];
        
        int cherries = grid[row][c1];
        if (c1 != c2) cherries += grid[row][c2];
        
        int maxNext = INT_MIN;
        for (int dc1 = -1; dc1 <= 1; dc1++) {
            for (int dc2 = -1; dc2 <= 1; dc2++) {
                maxNext = max(maxNext, solve(row + 1, c1 + dc1, c2 + dc2));
            }
        }
        
        return dp[row][c1][c2] = cherries + maxNext;
    }
    
public:
    int cherryPickup(vector<vector<int>>& g) {
        grid = g;
        rows = grid.size();
        cols = grid[0].size();
        dp.assign(rows, vector<vector<int>>(cols, vector<int>(cols, -1)));
        return solve(0, 0, cols - 1);
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    int cherryPickup(vector<vector<int>>& grid) {
        int rows = grid.size(), cols = grid[0].size();
        
        vector<vector<vector<int>>> dp(rows, vector<vector<int>>(cols, vector<int>(cols, 0)));
        
        // Initialize last row
        for (int c1 = 0; c1 < cols; c1++) {
            for (int c2 = 0; c2 < cols; c2++) {
                dp[rows-1][c1][c2] = (c1 == c2) ? grid[rows-1][c1] : grid[rows-1][c1] + grid[rows-1][c2];
            }
        }
        
        // Fill bottom up
        for (int row = rows - 2; row >= 0; row--) {
            for (int c1 = 0; c1 < cols; c1++) {
                for (int c2 = 0; c2 < cols; c2++) {
                    int cherries = (c1 == c2) ? grid[row][c1] : grid[row][c1] + grid[row][c2];
                    
                    int maxNext = 0;
                    for (int dc1 = -1; dc1 <= 1; dc1++) {
                        for (int dc2 = -1; dc2 <= 1; dc2++) {
                            int nc1 = c1 + dc1, nc2 = c2 + dc2;
                            if (nc1 >= 0 && nc1 < cols && nc2 >= 0 && nc2 < cols) {
                                maxNext = max(maxNext, dp[row + 1][nc1][nc2]);
                            }
                        }
                    }
                    
                    dp[row][c1][c2] = cherries + maxNext;
                }
            }
        }
        
        return dp[0][0][cols - 1];
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int rows, cols;
    cout << "Enter grid dimensions (rows cols): ";
    cin >> rows >> cols;
    
    vector<vector<int>> grid(rows, vector<int>(cols));
    cout << "Enter grid values:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cin >> grid[i][j];
        }
    }
    
    TopDown td;
    BottomUp bu;
    
    cout << "\n--- Results ---" << endl;
    cout << "Top-Down: " << td.cherryPickup(grid) << endl;
    cout << "Bottom-Up: " << bu.cherryPickup(grid) << endl;
    
    return 0;
}









