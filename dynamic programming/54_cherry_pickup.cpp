/*
    Cherry Pickup
    Problem: Go from (0,0) to (n-1,n-1) and back. Collect max cherries.
             Each cell: 0=empty, 1=cherry, -1=blocked
    
    Trick: Two people going from (0,0) to (n-1,n-1) simultaneously.
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<vector<vector<int>>> dp;
    vector<vector<int>> grid;
    int n;
    
    int solve(int r1, int c1, int r2) {
        int c2 = r1 + c1 - r2;
        
        if (r1 >= n || c1 >= n || r2 >= n || c2 >= n) return INT_MIN;
        if (grid[r1][c1] == -1 || grid[r2][c2] == -1) return INT_MIN;
        if (r1 == n - 1 && c1 == n - 1) return grid[r1][c1];
        
        if (dp[r1][c1][r2] != INT_MIN) return dp[r1][c1][r2];
        
        int cherries = grid[r1][c1];
        if (r1 != r2) cherries += grid[r2][c2];
        
        int next = max({
            solve(r1 + 1, c1, r2 + 1), // both down
            solve(r1 + 1, c1, r2),     // 1 down, 2 right
            solve(r1, c1 + 1, r2 + 1), // 1 right, 2 down
            solve(r1, c1 + 1, r2)      // both right
        });
        
        if (next == INT_MIN) return dp[r1][c1][r2] = INT_MIN;
        return dp[r1][c1][r2] = cherries + next;
    }
    
public:
    int cherryPickup(vector<vector<int>>& g) {
        grid = g;
        n = grid.size();
        dp.assign(n, vector<vector<int>>(n, vector<int>(n, INT_MIN)));
        return max(0, solve(0, 0, 0));
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    int cherryPickup(vector<vector<int>>& grid) {
        int n = grid.size();
        
        // dp[r1][c1][r2] where c2 = r1 + c1 - r2
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(n, INT_MIN)));
        dp[0][0][0] = grid[0][0];
        
        for (int r1 = 0; r1 < n; r1++) {
            for (int c1 = 0; c1 < n; c1++) {
                for (int r2 = 0; r2 < n; r2++) {
                    int c2 = r1 + c1 - r2;
                    if (c2 < 0 || c2 >= n) continue;
                    if (grid[r1][c1] == -1 || grid[r2][c2] == -1) continue;
                    
                    int cherries = grid[r1][c1];
                    if (r1 != r2) cherries += grid[r2][c2];
                    
                    int prev = INT_MIN;
                    if (r1 > 0 && r2 > 0) prev = max(prev, dp[r1-1][c1][r2-1]);
                    if (r1 > 0 && c2 > 0) prev = max(prev, dp[r1-1][c1][r2]);
                    if (c1 > 0 && r2 > 0) prev = max(prev, dp[r1][c1-1][r2-1]);
                    if (c1 > 0 && c2 > 0) prev = max(prev, dp[r1][c1-1][r2]);
                    
                    if (r1 == 0 && c1 == 0) {
                        dp[r1][c1][r2] = cherries;
                    } else if (prev != INT_MIN) {
                        dp[r1][c1][r2] = prev + cherries;
                    }
                }
            }
        }
        
        return max(0, dp[n-1][n-1][n-1]);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cout << "Enter grid size: ";
    cin >> n;
    
    vector<vector<int>> grid(n, vector<int>(n));
    cout << "Enter grid (0=empty, 1=cherry, -1=blocked):" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
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

