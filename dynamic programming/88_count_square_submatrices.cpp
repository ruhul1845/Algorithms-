/*
    Count Square Submatrices with All Ones
    Problem: Count total square submatrices that contain only 1s.
    
    Example: [[0,1,1,1],[1,1,1,1],[0,1,1,1]] → Output: 15
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<vector<int>> dp;
    vector<vector<int>> matrix;
    int m, n;
    
    int solve(int i, int j) {
        if (i < 0 || j < 0 || matrix[i][j] == 0) return 0;
        if (dp[i][j] != -1) return dp[i][j];
        
        int left = solve(i, j - 1);
        int up = solve(i - 1, j);
        int diag = solve(i - 1, j - 1);
        
        return dp[i][j] = 1 + min({left, up, diag});
    }
    
public:
    int countSquares(vector<vector<int>>& mat) {
        matrix = mat;
        m = matrix.size();
        n = matrix[0].size();
        dp.assign(m, vector<int>(n, -1));
        
        int count = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                count += solve(i, j);
            }
        }
        
        return count;
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    int countSquares(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        
        // dp[i][j] = size of largest square ending at (i,j)
        vector<vector<int>> dp(m, vector<int>(n, 0));
        int count = 0;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == 1) {
                    if (i == 0 || j == 0) {
                        dp[i][j] = 1;
                    } else {
                        dp[i][j] = 1 + min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]});
                    }
                    count += dp[i][j]; // Each square of size k contributes k
                }
            }
        }
        
        return count;
    }
    
    // Space Optimized O(n)
    int countSquaresOptimized(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        
        vector<int> prev(n, 0), curr(n, 0);
        int count = 0;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == 1) {
                    if (i == 0 || j == 0) {
                        curr[j] = 1;
                    } else {
                        curr[j] = 1 + min({prev[j], curr[j-1], prev[j-1]});
                    }
                    count += curr[j];
                } else {
                    curr[j] = 0;
                }
            }
            swap(prev, curr);
        }
        
        return count;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int m, n;
    cout << "Enter matrix dimensions (m n): ";
    cin >> m >> n;
    
    vector<vector<int>> matrix(m, vector<int>(n));
    cout << "Enter matrix (0s and 1s):" << endl;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> matrix[i][j];
        }
    }
    
    TopDown td;
    BottomUp bu;
    
    cout << "\n--- Results ---" << endl;
    cout << "Top-Down: " << td.countSquares(matrix) << endl;
    cout << "Bottom-Up: " << bu.countSquares(matrix) << endl;
    cout << "Space Optimized: " << bu.countSquaresOptimized(matrix) << endl;
    
    return 0;
}

