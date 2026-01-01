/*
    Minimum Falling Path Sum
    Problem: Find minimum sum path from top to bottom row.
             Can move to (row+1, col-1), (row+1, col), or (row+1, col+1).
    
    Example: [[2,1,3],[6,5,4],[7,8,9]] → Output: 13 (1→5→7)
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<vector<int>> dp;
    vector<vector<int>> matrix;
    int n;
    
    int solve(int row, int col) {
        if (col < 0 || col >= n) return INT_MAX;
        if (row == n - 1) return matrix[row][col];
        if (dp[row][col] != INT_MAX) return dp[row][col];
        
        int down = solve(row + 1, col);
        int left = solve(row + 1, col - 1);
        int right = solve(row + 1, col + 1);
        
        return dp[row][col] = matrix[row][col] + min({down, left, right});
    }
    
public:
    int minFallingPathSum(vector<vector<int>>& m) {
        matrix = m;
        n = matrix.size();
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
    int minFallingPathSum(vector<vector<int>>& matrix) {
        int n = matrix.size();
        vector<vector<int>> dp = matrix;
        
        for (int row = n - 2; row >= 0; row--) {
            for (int col = 0; col < n; col++) {
                int down = dp[row + 1][col];
                int left = (col > 0) ? dp[row + 1][col - 1] : INT_MAX;
                int right = (col < n - 1) ? dp[row + 1][col + 1] : INT_MAX;
                
                dp[row][col] += min({down, left, right});
            }
        }
        
        return *min_element(dp[0].begin(), dp[0].end());
    }
    
    // Space Optimized O(n)
    int minFallingPathSumOptimized(vector<vector<int>>& matrix) {
        int n = matrix.size();
        vector<int> prev = matrix[n - 1];
        
        for (int row = n - 2; row >= 0; row--) {
            vector<int> curr(n);
            for (int col = 0; col < n; col++) {
                int down = prev[col];
                int left = (col > 0) ? prev[col - 1] : INT_MAX;
                int right = (col < n - 1) ? prev[col + 1] : INT_MAX;
                
                curr[col] = matrix[row][col] + min({down, left, right});
            }
            prev = curr;
        }
        
        return *min_element(prev.begin(), prev.end());
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cout << "Enter matrix size: ";
    cin >> n;
    
    vector<vector<int>> matrix(n, vector<int>(n));
    cout << "Enter matrix:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> matrix[i][j];
        }
    }
    
    TopDown td;
    BottomUp bu;
    
    cout << "\n--- Results ---" << endl;
    cout << "Top-Down: " << td.minFallingPathSum(matrix) << endl;
    cout << "Bottom-Up: " << bu.minFallingPathSum(matrix) << endl;
    cout << "Space Optimized: " << bu.minFallingPathSumOptimized(matrix) << endl;
    
    return 0;
}







