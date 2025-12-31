/*
    Game Theory DP - Stone Game
    Problem: Two players take stones from ends of array.
             Find if first player can win (both play optimally).
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<vector<int>> dp;
    vector<int> piles;
    
    // Returns score difference (player1 - player2)
    int solve(int i, int j) {
        if (i > j) return 0;
        if (dp[i][j] != INT_MIN) return dp[i][j];
        
        // Current player takes left or right
        int takeLeft = piles[i] - solve(i + 1, j);
        int takeRight = piles[j] - solve(i, j - 1);
        
        return dp[i][j] = max(takeLeft, takeRight);
    }
    
public:
    bool stoneGame(vector<int>& p) {
        piles = p;
        int n = piles.size();
        dp.assign(n, vector<int>(n, INT_MIN));
        return solve(0, n - 1) > 0;
    }
    
    int scoreDifference(vector<int>& p) {
        piles = p;
        int n = piles.size();
        dp.assign(n, vector<int>(n, INT_MIN));
        return solve(0, n - 1);
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    bool stoneGame(vector<int>& piles) {
        int n = piles.size();
        
        // dp[i][j] = max score difference for subarray [i,j]
        vector<vector<int>> dp(n, vector<int>(n, 0));
        
        // Single pile: current player takes it
        for (int i = 0; i < n; i++) {
            dp[i][i] = piles[i];
        }
        
        // Fill for increasing lengths
        for (int len = 2; len <= n; len++) {
            for (int i = 0; i <= n - len; i++) {
                int j = i + len - 1;
                dp[i][j] = max(piles[i] - dp[i + 1][j], piles[j] - dp[i][j - 1]);
            }
        }
        
        return dp[0][n - 1] > 0;
    }
    
    // Space optimized
    bool stoneGameOptimized(vector<int>& piles) {
        int n = piles.size();
        vector<int> dp = piles;
        
        for (int len = 2; len <= n; len++) {
            for (int i = 0; i <= n - len; i++) {
                dp[i] = max(piles[i] - dp[i + 1], piles[i + len - 1] - dp[i]);
            }
        }
        
        return dp[0] > 0;
    }
};

// ==================== Predict the Winner ====================
class PredictWinner {
public:
    bool predictTheWinner(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));
        
        for (int i = 0; i < n; i++) dp[i][i] = nums[i];
        
        for (int len = 2; len <= n; len++) {
            for (int i = 0; i <= n - len; i++) {
                int j = i + len - 1;
                dp[i][j] = max(nums[i] - dp[i + 1][j], nums[j] - dp[i][j - 1]);
            }
        }
        
        return dp[0][n - 1] >= 0;
    }
};

// ==================== Nim Game ====================
class NimGame {
public:
    // Classic Nim: XOR of all piles = 0 means second player wins
    bool canWinNim(vector<int>& piles) {
        int xorSum = 0;
        for (int p : piles) xorSum ^= p;
        return xorSum != 0;
    }
    
    // Simple Nim: remove 1-3 stones from single pile of n stones
    bool canWinSimpleNim(int n) {
        return n % 4 != 0;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cout << "Enter number of piles: ";
    cin >> n;
    
    vector<int> piles(n);
    cout << "Enter pile values: ";
    for (int i = 0; i < n; i++) cin >> piles[i];
    
    TopDown td;
    BottomUp bu;
    PredictWinner pw;
    NimGame ng;
    
    cout << "\n--- Results ---" << endl;
    cout << "Stone Game - Player 1 wins: " << (td.stoneGame(piles) ? "Yes" : "No") << endl;
    cout << "Score Difference: " << td.scoreDifference(piles) << endl;
    cout << "Bottom-Up: " << (bu.stoneGame(piles) ? "Yes" : "No") << endl;
    cout << "Predict Winner: " << (pw.predictTheWinner(piles) ? "Player 1" : "Player 2") << endl;
    cout << "Nim Game (XOR): " << (ng.canWinNim(piles) ? "First player wins" : "Second player wins") << endl;
    
    return 0;
}



