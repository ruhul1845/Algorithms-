/*
    Target Sum
    Problem: Assign + or - to each number. Count ways to reach target sum.
    
    Example: nums = [1,1,1,1,1], target = 3 → Output: 5
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    map<pair<int, int>, int> dp;
    vector<int> arr;
    
    int solve(int idx, int sum) {
        if (idx < 0) {
            return sum == 0 ? 1 : 0;
        }
        
        auto key = make_pair(idx, sum);
        if (dp.count(key)) return dp[key];
        
        int add = solve(idx - 1, sum - arr[idx]);
        int sub = solve(idx - 1, sum + arr[idx]);
        
        return dp[key] = add + sub;
    }
    
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        arr = nums;
        dp.clear();
        return solve(nums.size() - 1, target);
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        
        // Let P = sum of positive, N = sum of negative
        // P - N = target, P + N = sum
        // 2P = target + sum, P = (target + sum) / 2
        
        if ((target + sum) % 2 != 0 || abs(target) > sum) return 0;
        
        int subsetSum = (target + sum) / 2;
        int n = nums.size();
        
        vector<vector<int>> dp(n + 1, vector<int>(subsetSum + 1, 0));
        dp[0][0] = 1;
        
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= subsetSum; j++) {
                dp[i][j] = dp[i - 1][j];
                if (nums[i - 1] <= j) {
                    dp[i][j] += dp[i - 1][j - nums[i - 1]];
                }
            }
        }
        
        return dp[n][subsetSum];
    }
    
    // Space Optimized
    int findTargetSumWaysOptimized(vector<int>& nums, int target) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        
        if ((target + sum) % 2 != 0 || abs(target) > sum) return 0;
        
        int subsetSum = (target + sum) / 2;
        vector<int> dp(subsetSum + 1, 0);
        dp[0] = 1;
        
        for (int num : nums) {
            for (int j = subsetSum; j >= num; j--) {
                dp[j] += dp[j - num];
            }
        }
        
        return dp[subsetSum];
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, target;
    cout << "Enter array size: ";
    cin >> n;
    cout << "Enter target: ";
    cin >> target;
    
    vector<int> nums(n);
    cout << "Enter array elements: ";
    for (int i = 0; i < n; i++) cin >> nums[i];
    
    TopDown td;
    BottomUp bu;
    
    cout << "\n--- Results ---" << endl;
    cout << "Top-Down: " << td.findTargetSumWays(nums, target) << endl;
    cout << "Bottom-Up: " << bu.findTargetSumWays(nums, target) << endl;
    cout << "Bottom-Up Optimized: " << bu.findTargetSumWaysOptimized(nums, target) << endl;
    
    return 0;
}


















