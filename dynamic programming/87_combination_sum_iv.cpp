/*
    Combination Sum IV
    Problem: Count permutations of nums that sum to target.
             (Order matters, unlike coin change)
    
    Example: nums = [1,2,3], target = 4 → Output: 7
             (1111, 112, 121, 211, 22, 13, 31)
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<int> dp;
    vector<int> nums;
    
    int solve(int target) {
        if (target == 0) return 1;
        if (target < 0) return 0;
        if (dp[target] != -1) return dp[target];
        
        int count = 0;
        for (int num : nums) {
            count += solve(target - num);
        }
        
        return dp[target] = count;
    }
    
public:
    int combinationSum4(vector<int>& n, int target) {
        nums = n;
        dp.assign(target + 1, -1);
        return solve(target);
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    int combinationSum4(vector<int>& nums, int target) {
        vector<unsigned int> dp(target + 1, 0);
        dp[0] = 1;
        
        for (int i = 1; i <= target; i++) {
            for (int num : nums) {
                if (i >= num) {
                    dp[i] += dp[i - num];
                }
            }
        }
        
        return dp[target];
    }
    
    // Follow-up: with negative numbers (need to limit combination length)
    int combinationSum4WithLength(vector<int>& nums, int target, int maxLen) {
        // dp[i][j] = ways to get sum j with at most i numbers
        vector<vector<int>> dp(maxLen + 1, vector<int>(target + 1, 0));
        
        for (int i = 0; i <= maxLen; i++) dp[i][0] = 1;
        
        for (int len = 1; len <= maxLen; len++) {
            for (int sum = 1; sum <= target; sum++) {
                for (int num : nums) {
                    if (sum >= num) {
                        dp[len][sum] += dp[len - 1][sum - num];
                    }
                }
            }
        }
        
        return dp[maxLen][target];
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, target;
    cout << "Enter array size and target: ";
    cin >> n >> target;
    
    vector<int> nums(n);
    cout << "Enter array elements: ";
    for (int i = 0; i < n; i++) cin >> nums[i];
    
    TopDown td;
    BottomUp bu;
    
    cout << "\n--- Results ---" << endl;
    cout << "Top-Down: " << td.combinationSum4(nums, target) << endl;
    cout << "Bottom-Up: " << bu.combinationSum4(nums, target) << endl;
    
    return 0;
}


















