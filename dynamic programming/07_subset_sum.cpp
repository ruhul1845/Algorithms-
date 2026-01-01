/*
    Subset Sum Problem
    Problem: Given a set of non-negative integers and a target sum,
             determine if there is a subset that sums up to the target.
    
    Example:
    arr = [3, 34, 4, 12, 5, 2], target = 9
    Output: true (subset {4, 5} sums to 9)
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<vector<int>> dp;
    vector<int> arr;
    
    bool solve(int idx, int target) {
        // Base cases
        if (target == 0) return true;
        if (idx < 0 || target < 0) return false;
        
        if (dp[idx][target] != -1) return dp[idx][target];
        
        // Don't take current element
        bool notTake = solve(idx - 1, target);
        
        // Take current element
        bool take = false;
        if (arr[idx] <= target) {
            take = solve(idx - 1, target - arr[idx]);
        }
        
        return dp[idx][target] = take || notTake;
    }
    
public:
    bool subsetSum(vector<int>& nums, int target) {
        arr = nums;
        int n = nums.size();
        dp.assign(n, vector<int>(target + 1, -1));
        return solve(n - 1, target);
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    bool subsetSum(vector<int>& nums, int target) {
        int n = nums.size();
        
        // dp[i][j] = can we make sum j using first i elements?
        vector<vector<bool>> dp(n + 1, vector<bool>(target + 1, false));
        
        // Base case: sum 0 is always possible (empty subset)
        for (int i = 0; i <= n; i++) {
            dp[i][0] = true;
        }
        
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= target; j++) {
                // Don't take element i-1
                dp[i][j] = dp[i - 1][j];
                
                // Take element i-1 if possible
                if (nums[i - 1] <= j) {
                    dp[i][j] = dp[i][j] || dp[i - 1][j - nums[i - 1]];
                }
            }
        }
        
        return dp[n][target];
    }
    
    // Space Optimized - O(target) space
    bool subsetSumOptimized(vector<int>& nums, int target) {
        int n = nums.size();
        vector<bool> dp(target + 1, false);
        dp[0] = true;
        
        for (int i = 0; i < n; i++) {
            // Traverse from right to left
            for (int j = target; j >= nums[i]; j--) {
                dp[j] = dp[j] || dp[j - nums[i]];
            }
        }
        
        return dp[target];
    }
    
    // Print subset that sums to target
    vector<int> getSubset(vector<int>& nums, int target) {
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
        
        vector<int> subset;
        if (!dp[n][target]) return subset;
        
        // Backtrack to find subset
        int i = n, j = target;
        while (i > 0 && j > 0) {
            if (dp[i][j] && !dp[i - 1][j]) {
                subset.push_back(nums[i - 1]);
                j -= nums[i - 1];
            }
            i--;
        }
        
        return subset;
    }
    
    // Count number of subsets with given sum
    int countSubsets(vector<int>& nums, int target) {
        int n = nums.size();
        vector<vector<int>> dp(n + 1, vector<int>(target + 1, 0));
        
        for (int i = 0; i <= n; i++) dp[i][0] = 1;
        
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
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, target;
    cout << "Enter array size: ";
    cin >> n;
    cout << "Enter target sum: ";
    cin >> target;
    
    vector<int> arr(n);
    cout << "Enter array elements: ";
    for (int i = 0; i < n; i++) cin >> arr[i];
    
    TopDown td;
    BottomUp bu;
    
    cout << "\n--- Results ---" << endl;
    cout << "Top-Down (Memoization): " << (td.subsetSum(arr, target) ? "Yes" : "No") << endl;
    cout << "Bottom-Up (Tabulation): " << (bu.subsetSum(arr, target) ? "Yes" : "No") << endl;
    cout << "Bottom-Up (Space Optimized): " << (bu.subsetSumOptimized(arr, target) ? "Yes" : "No") << endl;
    cout << "Number of subsets: " << bu.countSubsets(arr, target) << endl;
    
    cout << "One subset: ";
    vector<int> subset = bu.getSubset(arr, target);
    if (subset.empty()) {
        cout << "No subset found";
    } else {
        for (int x : subset) cout << x << " ";
    }
    cout << endl;
    
    return 0;
}

/*
    Time Complexity: O(n * target)
    Space Complexity:
        - Top-Down: O(n * target) for memoization + O(n) recursion stack
        - Bottom-Up: O(n * target)
        - Bottom-Up Optimized: O(target)
*/







