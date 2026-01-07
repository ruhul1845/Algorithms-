/*
    Domino and Tromino Tiling
    Problem: Tile 2 x n board with dominoes and trominoes.
    
    Domino: 2x1, Tromino: L-shaped (3 cells)
*/

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<vector<long long>> dp;
    // state: 0 = both rows filled, 1 = top row extra, 2 = bottom row extra
    
    long long solve(int col, int state, int n) {
        if (col > n) return 0;
        if (col == n) return state == 0 ? 1 : 0;
        if (dp[col][state] != -1) return dp[col][state];
        
        long long ways = 0;
        
        if (state == 0) {
            // Both rows filled at col-1
            ways = (ways + solve(col + 1, 0, n)) % MOD;     // vertical domino
            ways = (ways + solve(col + 2, 0, n)) % MOD;     // two horizontal dominoes
            ways = (ways + solve(col + 2, 1, n)) % MOD;     // tromino (top extra)
            ways = (ways + solve(col + 2, 2, n)) % MOD;     // tromino (bottom extra)
        } else if (state == 1) {
            // Top row has extra cell
            ways = (ways + solve(col + 1, 0, n)) % MOD;     // horizontal domino bottom
            ways = (ways + solve(col + 1, 2, n)) % MOD;     // tromino extends
        } else {
            // Bottom row has extra cell
            ways = (ways + solve(col + 1, 0, n)) % MOD;     // horizontal domino top
            ways = (ways + solve(col + 1, 1, n)) % MOD;     // tromino extends
        }
        
        return dp[col][state] = ways;
    }
    
public:
    int numTilings(int n) {
        dp.assign(n + 1, vector<long long>(3, -1));
        return solve(0, 0, n);
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    int numTilings(int n) {
        if (n == 1) return 1;
        if (n == 2) return 2;
        
        // f(n) = 2*f(n-1) + f(n-3)
        // Or: f(n) = f(n-1) + f(n-2) + 2*(f(n-3) + f(n-4) + ... + f(0))
        
        vector<long long> dp(n + 1);
        dp[0] = 1;
        dp[1] = 1;
        dp[2] = 2;
        
        for (int i = 3; i <= n; i++) {
            dp[i] = (2 * dp[i - 1] + dp[i - 3]) % MOD;
        }
        
        return dp[n];
    }
    
    // Alternative formula with explicit states
    int numTilingsAlt(int n) {
        if (n == 1) return 1;
        
        // f = fully filled, p = partially filled (one extra cell)
        long long f_prev2 = 1, f_prev1 = 1;
        long long p_prev2 = 0, p_prev1 = 0;
        
        for (int i = 2; i <= n; i++) {
            long long f_curr = (f_prev1 + f_prev2 + 2 * p_prev1) % MOD;
            long long p_curr = (p_prev1 + f_prev2) % MOD;
            
            f_prev2 = f_prev1;
            f_prev1 = f_curr;
            p_prev2 = p_prev1;
            p_prev1 = p_curr;
        }
        
        return f_prev1;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cout << "Enter board width n: ";
    cin >> n;
    
    TopDown td;
    BottomUp bu;
    
    cout << "\n--- Results ---" << endl;
    cout << "Top-Down: " << td.numTilings(n) << endl;
    cout << "Bottom-Up: " << bu.numTilings(n) << endl;
    cout << "Bottom-Up Alt: " << bu.numTilingsAlt(n) << endl;
    
    return 0;
}


















