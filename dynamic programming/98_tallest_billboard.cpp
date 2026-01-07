/*
    Tallest Billboard
    Problem: Build two supports of equal height using rods.
             Maximize height of supports.
    
    Example: rods = [1,2,3,6] → Output: 6 (supports: [6] and [1,2,3])
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    unordered_map<int, int> dp[21];
    vector<int> rods;
    
    // diff = left - right, maximize left
    int solve(int idx, int diff) {
        if (idx == rods.size()) {
            return diff == 0 ? 0 : INT_MIN;
        }
        
        if (dp[idx].count(diff)) return dp[idx][diff];
        
        // Skip rod
        int skip = solve(idx + 1, diff);
        
        // Add to left support
        int left = rods[idx] + solve(idx + 1, diff + rods[idx]);
        
        // Add to right support
        int right = solve(idx + 1, diff - rods[idx]);
        
        return dp[idx][diff] = max({skip, left, right});
    }
    
public:
    int tallestBillboard(vector<int>& r) {
        rods = r;
        for (int i = 0; i <= 20; i++) dp[i].clear();
        return max(0, solve(0, 0));
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    int tallestBillboard(vector<int>& rods) {
        int sum = accumulate(rods.begin(), rods.end(), 0);
        
        // dp[d] = max height of shorter support when difference is d
        vector<int> dp(sum + 1, -1);
        dp[0] = 0;
        
        for (int rod : rods) {
            vector<int> curr = dp;
            
            for (int d = 0; d <= sum - rod; d++) {
                if (dp[d] < 0) continue;
                
                // Add to taller support
                curr[d + rod] = max(curr[d + rod], dp[d]);
                
                // Add to shorter support
                int newDiff = abs(d - rod);
                int newShorter = dp[d] + min(d, rod);
                curr[newDiff] = max(curr[newDiff], newShorter);
            }
            
            dp = curr;
        }
        
        return dp[0];
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cout << "Enter number of rods: ";
    cin >> n;
    
    vector<int> rods(n);
    cout << "Enter rod lengths: ";
    for (int i = 0; i < n; i++) cin >> rods[i];
    
    TopDown td;
    BottomUp bu;
    
    cout << "\n--- Results ---" << endl;
    cout << "Top-Down: " << td.tallestBillboard(rods) << endl;
    cout << "Bottom-Up: " << bu.tallestBillboard(rods) << endl;
    
    return 0;
}


















