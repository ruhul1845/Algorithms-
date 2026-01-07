/*
    Burst Balloons
    Problem: Burst all balloons to maximize coins.
             Coins for bursting i = nums[left] * nums[i] * nums[right]
    
    Example: [3,1,5,8] → Output: 167
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<vector<int>> dp;
    vector<int> nums;
    
    int solve(int left, int right) {
        if (left > right) return 0;
        if (dp[left][right] != -1) return dp[left][right];
        
        int maxCoins = 0;
        for (int k = left; k <= right; k++) {
            // k is the LAST balloon to burst in range [left, right]
            int coins = nums[left - 1] * nums[k] * nums[right + 1];
            coins += solve(left, k - 1) + solve(k + 1, right);
            maxCoins = max(maxCoins, coins);
        }
        
        return dp[left][right] = maxCoins;
    }
    
public:
    int maxCoins(vector<int>& n) {
        int sz = n.size();
        nums.resize(sz + 2);
        nums[0] = nums[sz + 1] = 1;
        for (int i = 0; i < sz; i++) nums[i + 1] = n[i];
        
        dp.assign(sz + 2, vector<int>(sz + 2, -1));
        return solve(1, sz);
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    int maxCoins(vector<int>& n) {
        int sz = n.size();
        vector<int> nums(sz + 2);
        nums[0] = nums[sz + 1] = 1;
        for (int i = 0; i < sz; i++) nums[i + 1] = n[i];
        
        vector<vector<int>> dp(sz + 2, vector<int>(sz + 2, 0));
        
        for (int len = 1; len <= sz; len++) {
            for (int left = 1; left <= sz - len + 1; left++) {
                int right = left + len - 1;
                
                for (int k = left; k <= right; k++) {
                    int coins = nums[left - 1] * nums[k] * nums[right + 1];
                    coins += dp[left][k - 1] + dp[k + 1][right];
                    dp[left][right] = max(dp[left][right], coins);
                }
            }
        }
        
        return dp[1][sz];
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cout << "Enter number of balloons: ";
    cin >> n;
    
    vector<int> nums(n);
    cout << "Enter balloon values: ";
    for (int i = 0; i < n; i++) cin >> nums[i];
    
    TopDown td;
    BottomUp bu;
    
    cout << "\n--- Results ---" << endl;
    cout << "Top-Down: " << td.maxCoins(nums) << endl;
    cout << "Bottom-Up: " << bu.maxCoins(nums) << endl;
    
    return 0;
}


















