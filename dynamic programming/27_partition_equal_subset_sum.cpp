/*
    Partition Equal Subset Sum
    Problem: Determine if array can be partitioned into two subsets with equal sum.
    
    Example: [1, 5, 11, 5] → Output: true ([1,5,5] and [11])
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<vector<int>> dp;
    vector<int> arr;
    
    bool solve(int idx, int target) {
        if (target == 0) return true;
        if (idx < 0 || target < 0) return false;
        if (dp[idx][target] != -1) return dp[idx][target];
        
        bool notTake = solve(idx - 1, target);
        bool take = solve(idx - 1, target - arr[idx]);
        
        return dp[idx][target] = take || notTake;
    }
    
public:
    bool canPartition(vector<int>& nums) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum % 2 != 0) return false;
        
        arr = nums;
        int target = sum / 2;
        int n = nums.size();
        dp.assign(n, vector<int>(target + 1, -1));
        return solve(n - 1, target);
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    bool canPartition(vector<int>& nums) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum % 2 != 0) return false;
        
        int target = sum / 2;
        int n = nums.size();
        
        vector<vector<bool>> dp(n + 1, vector<bool>(target + 1, false));
        
        for (int i = 0; i <= n; i++) dp[i][0] = true;
        
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= target; j++) {
                dp[i][j] = dp[i - 1][j];
                if (nums[i - 1] <= j) {
                    dp[i][j] = dp[i][j] || dp[i - 1][j - nums[i - 1]];
                }
            }
        }
        
        return dp[n][target];
    }
    
    // Space Optimized O(target)
    bool canPartitionOptimized(vector<int>& nums) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum % 2 != 0) return false;
        
        int target = sum / 2;
        vector<bool> dp(target + 1, false);
        dp[0] = true;
        
        for (int num : nums) {
            for (int j = target; j >= num; j--) {
                dp[j] = dp[j] || dp[j - num];
            }
        }
        
        return dp[target];
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cout << "Enter array size: ";
    cin >> n;
    
    vector<int> nums(n);
    cout << "Enter array elements: ";
    for (int i = 0; i < n; i++) cin >> nums[i];
    
    TopDown td;
    BottomUp bu;
    
    cout << "\n--- Results ---" << endl;
    cout << "Top-Down: " << (td.canPartition(nums) ? "Yes" : "No") << endl;
    cout << "Bottom-Up: " << (bu.canPartition(nums) ? "Yes" : "No") << endl;
    cout << "Bottom-Up Optimized: " << (bu.canPartitionOptimized(nums) ? "Yes" : "No") << endl;
    
    return 0;
}



