/*
    Perfect Squares
    Problem: Find minimum number of perfect square numbers that sum to n.
    
    Example: n = 12 → Output: 3 (4 + 4 + 4)
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<int> dp;
    
    int solve(int n) {
        if (n == 0) return 0;
        if (dp[n] != -1) return dp[n];
        
        int minSquares = n; // worst case: all 1s
        
        for (int i = 1; i * i <= n; i++) {
            minSquares = min(minSquares, 1 + solve(n - i * i));
        }
        
        return dp[n] = minSquares;
    }
    
public:
    int numSquares(int n) {
        dp.assign(n + 1, -1);
        return solve(n);
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    int numSquares(int n) {
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;
        
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j * j <= i; j++) {
                dp[i] = min(dp[i], 1 + dp[i - j * j]);
            }
        }
        
        return dp[n];
    }
    
    // BFS Approach
    int numSquaresBFS(int n) {
        vector<int> squares;
        for (int i = 1; i * i <= n; i++) {
            squares.push_back(i * i);
        }
        
        queue<pair<int, int>> q;
        vector<bool> visited(n + 1, false);
        q.push({n, 0});
        visited[n] = true;
        
        while (!q.empty()) {
            auto [remaining, steps] = q.front();
            q.pop();
            
            for (int sq : squares) {
                int next = remaining - sq;
                if (next == 0) return steps + 1;
                if (next > 0 && !visited[next]) {
                    visited[next] = true;
                    q.push({next, steps + 1});
                }
            }
        }
        
        return n;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cout << "Enter n: ";
    cin >> n;
    
    TopDown td;
    BottomUp bu;
    
    cout << "\n--- Results ---" << endl;
    cout << "Top-Down: " << td.numSquares(n) << endl;
    cout << "Bottom-Up: " << bu.numSquares(n) << endl;
    cout << "BFS: " << bu.numSquaresBFS(n) << endl;
    
    return 0;
}







