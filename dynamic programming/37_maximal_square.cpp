/*
    Maximal Square
    Problem: Find largest square containing only 1s in binary matrix.
    
    Example: matrix = [["1","0","1","0","0"],["1","0","1","1","1"],
                       ["1","1","1","1","1"],["1","0","0","1","0"]]
             Output: 4 (2x2 square)
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<vector<int>> dp;
    vector<vector<char>> mat;
    int maxSide;
    
    int solve(int i, int j) {
        if (i < 0 || j < 0) return 0;
        if (dp[i][j] != -1) return dp[i][j];
        
        int left = solve(i, j - 1);
        int up = solve(i - 1, j);
        int diag = solve(i - 1, j - 1);
        
        if (mat[i][j] == '1') {
            dp[i][j] = 1 + min({left, up, diag});
            maxSide = max(maxSide, dp[i][j]);
        } else {
            dp[i][j] = 0;
        }
        
        return dp[i][j];
    }
    
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        mat = matrix;
        int m = matrix.size(), n = matrix[0].size();
        dp.assign(m, vector<int>(n, -1));
        maxSide = 0;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                solve(i, j);
            }
        }
        
        return maxSide * maxSide;
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        
        // dp[i][j] = side of largest square ending at (i,j)
        vector<vector<int>> dp(m, vector<int>(n, 0));
        int maxSide = 0;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == '1') {
                    if (i == 0 || j == 0) {
                        dp[i][j] = 1;
                    } else {
                        dp[i][j] = 1 + min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]});
                    }
                    maxSide = max(maxSide, dp[i][j]);
                }
            }
        }
        
        return maxSide * maxSide;
    }
    
    // Space Optimized O(n)
    int maximalSquareOptimized(vector<vector<char>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        
        vector<int> prev(n, 0), curr(n, 0);
        int maxSide = 0;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == '1') {
                    if (i == 0 || j == 0) {
                        curr[j] = 1;
                    } else {
                        curr[j] = 1 + min({prev[j], curr[j-1], prev[j-1]});
                    }
                    maxSide = max(maxSide, curr[j]);
                } else {
                    curr[j] = 0;
                }
            }
            swap(prev, curr);
        }
        
        return maxSide * maxSide;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int m, n;
    cout << "Enter matrix dimensions (m n): ";
    cin >> m >> n;
    
    vector<vector<char>> matrix(m, vector<char>(n));
    cout << "Enter matrix (0s and 1s):" << endl;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> matrix[i][j];
        }
    }
    
    TopDown td;
    BottomUp bu;
    
    cout << "\n--- Results ---" << endl;
    cout << "Top-Down: " << td.maximalSquare(matrix) << endl;
    cout << "Bottom-Up: " << bu.maximalSquare(matrix) << endl;
    cout << "Bottom-Up Optimized: " << bu.maximalSquareOptimized(matrix) << endl;
    
    return 0;
}







