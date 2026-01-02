/*
    Paint Fence
    Problem: n posts, k colors. No more than 2 adjacent posts same color.
             Count number of ways to paint.
    
    Example: n = 3, k = 2 → Output: 6
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<vector<long long>> dp;
    int k;
    
    // sameCount = how many consecutive same colors so far
    long long solve(int idx, int sameCount) {
        if (idx == 0) return k; // first post: k choices
        if (dp[idx][sameCount] != -1) return dp[idx][sameCount];
        
        long long ways = 0;
        
        // Paint different color
        ways += solve(idx - 1, 0) * (k - 1);
        
        // Paint same color (only if sameCount < 1)
        if (sameCount < 1) {
            ways += solve(idx - 1, 1);
        }
        
        return dp[idx][sameCount] = ways;
    }
    
public:
    long long numWays(int n, int colors) {
        if (n == 0) return 0;
        k = colors;
        dp.assign(n, vector<long long>(2, -1));
        return solve(n - 1, 0);
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    long long numWays(int n, int k) {
        if (n == 0) return 0;
        if (n == 1) return k;
        
        // same[i] = ways to paint i posts where last 2 are same
        // diff[i] = ways to paint i posts where last 2 are different
        vector<long long> same(n + 1), diff(n + 1);
        
        same[1] = 0;
        diff[1] = k;
        
        for (int i = 2; i <= n; i++) {
            same[i] = diff[i - 1];
            diff[i] = (same[i - 1] + diff[i - 1]) * (k - 1);
        }
        
        return same[n] + diff[n];
    }
    
    // Space Optimized O(1)
    long long numWaysOptimized(int n, int k) {
        if (n == 0) return 0;
        if (n == 1) return k;
        
        long long same = 0, diff = k;
        
        for (int i = 2; i <= n; i++) {
            long long newSame = diff;
            long long newDiff = (same + diff) * (k - 1);
            same = newSame;
            diff = newDiff;
        }
        
        return same + diff;
    }
    
    // Alternative formula
    long long numWaysAlt(int n, int k) {
        if (n == 0) return 0;
        if (n == 1) return k;
        if (n == 2) return (long long)k * k;
        
        // f(n) = (k-1) * (f(n-1) + f(n-2))
        long long prev2 = k;
        long long prev1 = (long long)k * k;
        
        for (int i = 3; i <= n; i++) {
            long long curr = (k - 1) * (prev1 + prev2);
            prev2 = prev1;
            prev1 = curr;
        }
        
        return prev1;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k;
    cout << "Enter number of posts: ";
    cin >> n;
    cout << "Enter number of colors: ";
    cin >> k;
    
    TopDown td;
    BottomUp bu;
    
    cout << "\n--- Results ---" << endl;
    cout << "Top-Down: " << td.numWays(n, k) << endl;
    cout << "Bottom-Up: " << bu.numWays(n, k) << endl;
    cout << "Bottom-Up Optimized: " << bu.numWaysOptimized(n, k) << endl;
    cout << "Alternative Formula: " << bu.numWaysAlt(n, k) << endl;
    
    return 0;
}









