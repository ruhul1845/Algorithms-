/*
    Minimum Cost to Merge Stones
    Problem: Merge K consecutive piles into one. Cost = sum of stones.
             Find minimum cost to merge all into one pile.
    
    Example: stones = [3,2,4,1], K = 2 → Output: 20
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<vector<vector<int>>> dp;
    vector<int> prefix;
    int K;
    
    int sum(int i, int j) {
        return prefix[j + 1] - prefix[i];
    }
    
    int solve(int i, int j, int piles) {
        if (i == j) return piles == 1 ? 0 : INT_MAX;
        if (dp[i][j][piles] != -1) return dp[i][j][piles];
        
        if (piles == 1) {
            int merge = solve(i, j, K);
            return dp[i][j][piles] = (merge == INT_MAX) ? INT_MAX : merge + sum(i, j);
        }
        
        int minCost = INT_MAX;
        for (int mid = i; mid < j; mid += K - 1) {
            int left = solve(i, mid, 1);
            int right = solve(mid + 1, j, piles - 1);
            if (left != INT_MAX && right != INT_MAX) {
                minCost = min(minCost, left + right);
            }
        }
        
        return dp[i][j][piles] = minCost;
    }
    
public:
    int mergeStones(vector<int>& stones, int k) {
        int n = stones.size();
        if ((n - 1) % (k - 1) != 0) return -1;
        
        K = k;
        prefix.resize(n + 1, 0);
        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + stones[i];
        }
        
        dp.assign(n, vector<vector<int>>(n, vector<int>(k + 1, -1)));
        return solve(0, n - 1, 1);
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    int mergeStones(vector<int>& stones, int K) {
        int n = stones.size();
        if ((n - 1) % (K - 1) != 0) return -1;
        
        vector<int> prefix(n + 1, 0);
        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + stones[i];
        }
        
        // dp[i][j] = min cost to merge stones[i..j] into minimum piles
        vector<vector<int>> dp(n, vector<int>(n, 0));
        
        for (int len = K; len <= n; len++) {
            for (int i = 0; i + len - 1 < n; i++) {
                int j = i + len - 1;
                dp[i][j] = INT_MAX;
                
                for (int mid = i; mid < j; mid += K - 1) {
                    dp[i][j] = min(dp[i][j], dp[i][mid] + dp[mid + 1][j]);
                }
                
                if ((j - i) % (K - 1) == 0) {
                    dp[i][j] += prefix[j + 1] - prefix[i];
                }
            }
        }
        
        return dp[0][n - 1];
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, K;
    cout << "Enter number of piles and K: ";
    cin >> n >> K;
    
    vector<int> stones(n);
    cout << "Enter stone counts: ";
    for (int i = 0; i < n; i++) cin >> stones[i];
    
    TopDown td;
    BottomUp bu;
    
    cout << "\n--- Results ---" << endl;
    cout << "Top-Down: " << td.mergeStones(stones, K) << endl;
    cout << "Bottom-Up: " << bu.mergeStones(stones, K) << endl;
    
    return 0;
}







