/*
    Triangle - Minimum Path Sum
    Problem: Given a triangle, find minimum path sum from top to bottom.
             Each step you may move to adjacent numbers on the row below.
    
    Example: [[2],[3,4],[6,5,7],[4,1,8,3]] → Output: 11 (2+3+5+1)
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<vector<int>> dp;
    vector<vector<int>> tri;
    
    int solve(int i, int j) {
        if (i == tri.size() - 1) return tri[i][j];
        if (dp[i][j] != -1) return dp[i][j];
        
        int down = solve(i + 1, j);
        int diag = solve(i + 1, j + 1);
        
        return dp[i][j] = tri[i][j] + min(down, diag);
    }
    
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        tri = triangle;
        int n = triangle.size();
        dp.assign(n, vector<int>(n, -1));
        return solve(0, 0);
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int n = triangle.size();
        vector<vector<int>> dp = triangle;
        
        // Start from second last row
        for (int i = n - 2; i >= 0; i--) {
            for (int j = 0; j <= i; j++) {
                dp[i][j] += min(dp[i+1][j], dp[i+1][j+1]);
            }
        }
        
        return dp[0][0];
    }
    
    // Space Optimized O(n)
    int minimumTotalOptimized(vector<vector<int>>& triangle) {
        int n = triangle.size();
        vector<int> dp = triangle[n - 1];
        
        for (int i = n - 2; i >= 0; i--) {
            for (int j = 0; j <= i; j++) {
                dp[j] = triangle[i][j] + min(dp[j], dp[j+1]);
            }
        }
        
        return dp[0];
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cout << "Enter number of rows: ";
    cin >> n;
    
    vector<vector<int>> triangle(n);
    cout << "Enter triangle values:" << endl;
    for (int i = 0; i < n; i++) {
        triangle[i].resize(i + 1);
        for (int j = 0; j <= i; j++) {
            cin >> triangle[i][j];
        }
    }
    
    TopDown td;
    BottomUp bu;
    
    cout << "\n--- Results ---" << endl;
    cout << "Top-Down: " << td.minimumTotal(triangle) << endl;
    cout << "Bottom-Up: " << bu.minimumTotal(triangle) << endl;
    cout << "Bottom-Up Optimized: " << bu.minimumTotalOptimized(triangle) << endl;
    
    return 0;
}









