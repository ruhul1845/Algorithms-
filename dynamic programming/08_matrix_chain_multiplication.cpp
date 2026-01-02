/*
    Matrix Chain Multiplication
    Problem: Given dimensions of n matrices, find the most efficient way
             to multiply these matrices (minimum number of scalar multiplications).
    
    Example:
    dimensions = [10, 20, 30, 40, 30]
    Matrices: A(10x20), B(20x30), C(30x40), D(40x30)
    Output: Minimum cost to multiply all matrices
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<vector<int>> dp;
    vector<int> dims;
    
    int solve(int i, int j) {
        // Base case: single matrix, no multiplication needed
        if (i == j) return 0;
        
        if (dp[i][j] != -1) return dp[i][j];
        
        int minCost = INT_MAX;
        
        // Try all possible positions to split
        for (int k = i; k < j; k++) {
            // Cost = left part + right part + multiplication cost
            int cost = solve(i, k) + solve(k + 1, j) + 
                       dims[i - 1] * dims[k] * dims[j];
            minCost = min(minCost, cost);
        }
        
        return dp[i][j] = minCost;
    }
    
public:
    int mcm(vector<int>& dimensions) {
        dims = dimensions;
        int n = dimensions.size();
        dp.assign(n, vector<int>(n, -1));
        return solve(1, n - 1);
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    int mcm(vector<int>& dims) {
        int n = dims.size();
        
        // dp[i][j] = minimum cost to multiply matrices from i to j
        vector<vector<int>> dp(n, vector<int>(n, 0));
        
        // l is chain length
        for (int l = 2; l < n; l++) {
            for (int i = 1; i < n - l + 1; i++) {
                int j = i + l - 1;
                dp[i][j] = INT_MAX;
                
                for (int k = i; k < j; k++) {
                    int cost = dp[i][k] + dp[k + 1][j] + 
                               dims[i - 1] * dims[k] * dims[j];
                    dp[i][j] = min(dp[i][j], cost);
                }
            }
        }
        
        return dp[1][n - 1];
    }
    
    // Print optimal parenthesization
    string printOptimalParens(vector<int>& dims) {
        int n = dims.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));
        vector<vector<int>> split(n, vector<int>(n, 0));
        
        for (int l = 2; l < n; l++) {
            for (int i = 1; i < n - l + 1; i++) {
                int j = i + l - 1;
                dp[i][j] = INT_MAX;
                
                for (int k = i; k < j; k++) {
                    int cost = dp[i][k] + dp[k + 1][j] + 
                               dims[i - 1] * dims[k] * dims[j];
                    if (cost < dp[i][j]) {
                        dp[i][j] = cost;
                        split[i][j] = k;
                    }
                }
            }
        }
        
        return buildParens(split, 1, n - 1);
    }
    
private:
    string buildParens(vector<vector<int>>& split, int i, int j) {
        if (i == j) {
            return "M" + to_string(i);
        }
        return "(" + buildParens(split, i, split[i][j]) + " x " +
               buildParens(split, split[i][j] + 1, j) + ")";
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cout << "Enter number of matrices: ";
    cin >> n;
    
    vector<int> dims(n + 1);
    cout << "Enter dimensions (n+1 values for n matrices):" << endl;
    cout << "For matrices A1(d0xd1), A2(d1xd2), ..., An(d(n-1)xdn)" << endl;
    for (int i = 0; i <= n; i++) {
        cin >> dims[i];
    }
    
    TopDown td;
    BottomUp bu;
    
    cout << "\n--- Results ---" << endl;
    cout << "Top-Down (Memoization): " << td.mcm(dims) << endl;
    cout << "Bottom-Up (Tabulation): " << bu.mcm(dims) << endl;
    cout << "Optimal Parenthesization: " << bu.printOptimalParens(dims) << endl;
    
    return 0;
}

/*
    Time Complexity: O(n^3)
    Space Complexity: O(n^2)
    
    Note: This is a classic example of "partition DP" or "interval DP"
          where we try all possible ways to partition the problem.
*/









