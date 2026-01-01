/*
    Minimum Subset Sum Difference
    Problem: Partition array into two subsets to minimize |sum(S1) - sum(S2)|
    
    Example: [1, 6, 11, 5] → Output: 1 (S1={1,5,6}=12, S2={11}=11)
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<vector<int>> dp;
    vector<int> arr;
    int totalSum;
    
    bool canMakeSum(int idx, int sum) {
        if (sum == 0) return true;
        if (idx < 0 || sum < 0) return false;
        if (dp[idx][sum] != -1) return dp[idx][sum];
        
        bool notTake = canMakeSum(idx - 1, sum);
        bool take = canMakeSum(idx - 1, sum - arr[idx]);
        
        return dp[idx][sum] = take || notTake;
    }
    
public:
    int minimumDifference(vector<int>& nums) {
        arr = nums;
        totalSum = accumulate(nums.begin(), nums.end(), 0);
        int n = nums.size();
        dp.assign(n, vector<int>(totalSum + 1, -1));
        
        int minDiff = totalSum;
        for (int s1 = 0; s1 <= totalSum / 2; s1++) {
            if (canMakeSum(n - 1, s1)) {
                int s2 = totalSum - s1;
                minDiff = min(minDiff, abs(s2 - s1));
            }
        }
        
        return minDiff;
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    int minimumDifference(vector<int>& nums) {
        int totalSum = accumulate(nums.begin(), nums.end(), 0);
        int n = nums.size();
        
        // Find all achievable subset sums
        vector<vector<bool>> dp(n + 1, vector<bool>(totalSum + 1, false));
        
        for (int i = 0; i <= n; i++) dp[i][0] = true;
        
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= totalSum; j++) {
                dp[i][j] = dp[i - 1][j];
                if (nums[i - 1] <= j) {
                    dp[i][j] = dp[i][j] || dp[i - 1][j - nums[i - 1]];
                }
            }
        }
        
        int minDiff = totalSum;
        for (int s1 = 0; s1 <= totalSum / 2; s1++) {
            if (dp[n][s1]) {
                minDiff = min(minDiff, totalSum - 2 * s1);
            }
        }
        
        return minDiff;
    }
    
    // Space Optimized
    int minimumDifferenceOptimized(vector<int>& nums) {
        int totalSum = accumulate(nums.begin(), nums.end(), 0);
        
        vector<bool> dp(totalSum + 1, false);
        dp[0] = true;
        
        for (int num : nums) {
            for (int j = totalSum; j >= num; j--) {
                dp[j] = dp[j] || dp[j - num];
            }
        }
        
        int minDiff = totalSum;
        for (int s1 = 0; s1 <= totalSum / 2; s1++) {
            if (dp[s1]) {
                minDiff = min(minDiff, totalSum - 2 * s1);
            }
        }
        
        return minDiff;
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
    cout << "Top-Down: " << td.minimumDifference(nums) << endl;
    cout << "Bottom-Up: " << bu.minimumDifference(nums) << endl;
    cout << "Bottom-Up Optimized: " << bu.minimumDifferenceOptimized(nums) << endl;
    
    return 0;
}







