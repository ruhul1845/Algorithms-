/*
    Super Egg Drop
    Problem: k eggs, n floors. Find minimum moves to determine critical floor.
             Critical floor = lowest floor where egg breaks.
    
    Example: k = 2, n = 6 → Output: 3
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<vector<int>> dp;
    
    int solve(int k, int n) {
        if (n <= 1) return n;
        if (k == 1) return n;
        if (dp[k][n] != -1) return dp[k][n];
        
        // Binary search optimization
        int lo = 1, hi = n, result = n;
        
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            int breaks = solve(k - 1, mid - 1); // egg breaks
            int survives = solve(k, n - mid);   // egg survives
            
            int worst = 1 + max(breaks, survives);
            result = min(result, worst);
            
            if (breaks > survives) {
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }
        
        return dp[k][n] = result;
    }
    
public:
    int superEggDrop(int k, int n) {
        dp.assign(k + 1, vector<int>(n + 1, -1));
        return solve(k, n);
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    // O(k * n * log n) with binary search
    int superEggDrop(int k, int n) {
        vector<vector<int>> dp(k + 1, vector<int>(n + 1, 0));
        
        // Base cases
        for (int i = 1; i <= n; i++) dp[1][i] = i;
        for (int i = 1; i <= k; i++) dp[i][1] = 1;
        
        for (int eggs = 2; eggs <= k; eggs++) {
            for (int floors = 2; floors <= n; floors++) {
                dp[eggs][floors] = floors;
                
                int lo = 1, hi = floors;
                while (lo <= hi) {
                    int mid = (lo + hi) / 2;
                    int breaks = dp[eggs - 1][mid - 1];
                    int survives = dp[eggs][floors - mid];
                    
                    int worst = 1 + max(breaks, survives);
                    dp[eggs][floors] = min(dp[eggs][floors], worst);
                    
                    if (breaks > survives) hi = mid - 1;
                    else lo = mid + 1;
                }
            }
        }
        
        return dp[k][n];
    }
    
    // Alternative: dp[moves][eggs] = max floors
    int superEggDropAlt(int k, int n) {
        // dp[m][k] = max floors we can check with m moves and k eggs
        vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));
        
        int m = 0;
        while (dp[m][k] < n) {
            m++;
            for (int eggs = 1; eggs <= k; eggs++) {
                dp[m][eggs] = dp[m-1][eggs-1] + dp[m-1][eggs] + 1;
            }
        }
        
        return m;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int k, n;
    cout << "Enter number of eggs: ";
    cin >> k;
    cout << "Enter number of floors: ";
    cin >> n;
    
    TopDown td;
    BottomUp bu;
    
    cout << "\n--- Results ---" << endl;
    cout << "Top-Down: " << td.superEggDrop(k, n) << endl;
    cout << "Bottom-Up: " << bu.superEggDrop(k, n) << endl;
    cout << "Alternative: " << bu.superEggDropAlt(k, n) << endl;
    
    return 0;
}

