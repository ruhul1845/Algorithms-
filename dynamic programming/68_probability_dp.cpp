/*
    Probability DP - Knight Probability in Chessboard
    Problem: Knight on NxN board at (r,c). After K moves, probability of staying on board.
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    int N;
    vector<vector<vector<double>>> dp;
    int dr[8] = {-2, -2, -1, -1, 1, 1, 2, 2};
    int dc[8] = {-1, 1, -2, 2, -2, 2, -1, 1};
    
    double solve(int r, int c, int k) {
        if (r < 0 || r >= N || c < 0 || c >= N) return 0.0;
        if (k == 0) return 1.0;
        if (dp[r][c][k] >= 0) return dp[r][c][k];
        
        double prob = 0.0;
        for (int i = 0; i < 8; i++) {
            prob += solve(r + dr[i], c + dc[i], k - 1) / 8.0;
        }
        
        return dp[r][c][k] = prob;
    }
    
public:
    double knightProbability(int n, int k, int row, int col) {
        N = n;
        dp.assign(n, vector<vector<double>>(n, vector<double>(k + 1, -1)));
        return solve(row, col, k);
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    double knightProbability(int n, int k, int row, int col) {
        int dr[8] = {-2, -2, -1, -1, 1, 1, 2, 2};
        int dc[8] = {-1, 1, -2, 2, -2, 2, -1, 1};
        
        vector<vector<double>> curr(n, vector<double>(n, 0));
        vector<vector<double>> prev(n, vector<double>(n, 0));
        
        prev[row][col] = 1.0;
        
        for (int move = 0; move < k; move++) {
            fill(curr.begin(), curr.end(), vector<double>(n, 0));
            
            for (int r = 0; r < n; r++) {
                for (int c = 0; c < n; c++) {
                    if (prev[r][c] > 0) {
                        for (int i = 0; i < 8; i++) {
                            int nr = r + dr[i];
                            int nc = c + dc[i];
                            if (nr >= 0 && nr < n && nc >= 0 && nc < n) {
                                curr[nr][nc] += prev[r][c] / 8.0;
                            }
                        }
                    }
                }
            }
            
            swap(prev, curr);
        }
        
        double totalProb = 0.0;
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < n; c++) {
                totalProb += prev[r][c];
            }
        }
        
        return totalProb;
    }
};

// ==================== Dice Roll Sum Probability ====================
class DiceRollSum {
public:
    // Probability of getting exactly target sum with n dice (each 1-6)
    double diceSum(int n, int target) {
        if (target < n || target > 6 * n) return 0.0;
        
        // dp[i][j] = probability of getting sum j with i dice
        vector<vector<double>> dp(n + 1, vector<double>(target + 1, 0));
        dp[0][0] = 1.0;
        
        for (int dice = 1; dice <= n; dice++) {
            for (int sum = dice; sum <= min(target, 6 * dice); sum++) {
                for (int face = 1; face <= 6 && face <= sum; face++) {
                    dp[dice][sum] += dp[dice - 1][sum - face] / 6.0;
                }
            }
        }
        
        return dp[n][target];
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cout << "=== Knight Probability ===" << endl;
    int n, k, r, c;
    cout << "Enter board size N, moves K, start row and col: ";
    cin >> n >> k >> r >> c;
    
    TopDown td;
    BottomUp bu;
    
    cout << fixed << setprecision(6);
    cout << "Top-Down: " << td.knightProbability(n, k, r, c) << endl;
    cout << "Bottom-Up: " << bu.knightProbability(n, k, r, c) << endl;
    
    cout << "\n=== Dice Roll Sum ===" << endl;
    int numDice, target;
    cout << "Enter number of dice and target sum: ";
    cin >> numDice >> target;
    
    DiceRollSum drs;
    cout << "Probability: " << drs.diceSum(numDice, target) << endl;
    
    return 0;
}

