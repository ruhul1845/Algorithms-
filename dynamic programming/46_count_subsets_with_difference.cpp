/*
    Count Subsets with Given Difference
    Problem: Count subsets where |sum(S1) - sum(S2)| = diff
    
    Let S1 - S2 = diff, S1 + S2 = totalSum
    Therefore S1 = (diff + totalSum) / 2
    Problem reduces to: count subsets with sum = S1
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<vector<int>> dp;
    vector<int> arr;
    
    int solve(int idx, int target) {
        if (target == 0) return 1;
        if (idx < 0) return 0;
        if (dp[idx][target] != -1) return dp[idx][target];
        
        int notTake = solve(idx - 1, target);
        int take = 0;
        if (arr[idx] <= target) {
            take = solve(idx - 1, target - arr[idx]);
        }
        
        return dp[idx][target] = take + notTake;
    }
    
public:
    int countSubsets(vector<int>& nums, int diff) {
        arr = nums;
        int totalSum = accumulate(nums.begin(), nums.end(), 0);
        
        // S1 = (diff + totalSum) / 2
        if ((diff + totalSum) % 2 != 0 || diff > totalSum) return 0;
        
        int target = (diff + totalSum) / 2;
        int n = nums.size();
        dp.assign(n, vector<int>(target + 1, -1));
        return solve(n - 1, target);
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    int countSubsets(vector<int>& nums, int diff) {
        int totalSum = accumulate(nums.begin(), nums.end(), 0);
        
        if ((diff + totalSum) % 2 != 0 || diff > totalSum) return 0;
        if (diff < 0 && -diff > totalSum) return 0;
        
        int target = (diff + totalSum) / 2;
        if (target < 0) return 0;
        
        int n = nums.size();
        vector<vector<int>> dp(n + 1, vector<int>(target + 1, 0));
        dp[0][0] = 1;
        
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= target; j++) {
                dp[i][j] = dp[i - 1][j];
                if (nums[i - 1] <= j) {
                    dp[i][j] += dp[i - 1][j - nums[i - 1]];
                }
            }
        }
        
        return dp[n][target];
    }
    
    // Space Optimized
    int countSubsetsOptimized(vector<int>& nums, int diff) {
        int totalSum = accumulate(nums.begin(), nums.end(), 0);
        
        if ((diff + totalSum) % 2 != 0 || abs(diff) > totalSum) return 0;
        
        int target = (diff + totalSum) / 2;
        if (target < 0) return 0;
        
        vector<int> dp(target + 1, 0);
        dp[0] = 1;
        
        for (int num : nums) {
            for (int j = target; j >= num; j--) {
                dp[j] += dp[j - num];
            }
        }
        
        return dp[target];
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, diff;
    cout << "Enter array size: ";
    cin >> n;
    cout << "Enter required difference: ";
    cin >> diff;
    
    vector<int> nums(n);
    cout << "Enter array elements: ";
    for (int i = 0; i < n; i++) cin >> nums[i];
    
    TopDown td;
    BottomUp bu;
    
    cout << "\n--- Results ---" << endl;
    cout << "Top-Down: " << td.countSubsets(nums, diff) << endl;
    cout << "Bottom-Up: " << bu.countSubsets(nums, diff) << endl;
    cout << "Bottom-Up Optimized: " << bu.countSubsetsOptimized(nums, diff) << endl;
    
    return 0;
}

