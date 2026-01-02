/*
    Delete and Earn
    Problem: Delete num[i] to earn num[i] points. Must also delete all num[i]-1 and num[i]+1.
             Find maximum points.
    
    Example: [3,4,2] → Output: 6 (delete 4s → earn 4, then delete 2 → earn 2)
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<int> dp;
    vector<int> sum;
    
    int solve(int num) {
        if (num < 0) return 0;
        if (num == 0) return sum[0];
        if (dp[num] != -1) return dp[num];
        
        int take = sum[num] + solve(num - 2);
        int skip = solve(num - 1);
        
        return dp[num] = max(take, skip);
    }
    
public:
    int deleteAndEarn(vector<int>& nums) {
        int maxNum = *max_element(nums.begin(), nums.end());
        sum.assign(maxNum + 1, 0);
        
        for (int num : nums) {
            sum[num] += num;
        }
        
        dp.assign(maxNum + 1, -1);
        return solve(maxNum);
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    int deleteAndEarn(vector<int>& nums) {
        int maxNum = *max_element(nums.begin(), nums.end());
        vector<int> sum(maxNum + 1, 0);
        
        for (int num : nums) {
            sum[num] += num;
        }
        
        // Now it's house robber problem
        vector<int> dp(maxNum + 1, 0);
        dp[0] = sum[0];
        dp[1] = max(sum[0], sum[1]);
        
        for (int i = 2; i <= maxNum; i++) {
            dp[i] = max(dp[i-1], dp[i-2] + sum[i]);
        }
        
        return dp[maxNum];
    }
    
    // Space Optimized
    int deleteAndEarnOptimized(vector<int>& nums) {
        int maxNum = *max_element(nums.begin(), nums.end());
        vector<int> sum(maxNum + 1, 0);
        
        for (int num : nums) {
            sum[num] += num;
        }
        
        int prev2 = sum[0];
        int prev1 = max(sum[0], sum[1]);
        
        for (int i = 2; i <= maxNum; i++) {
            int curr = max(prev1, prev2 + sum[i]);
            prev2 = prev1;
            prev1 = curr;
        }
        
        return prev1;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cout << "Enter array size: ";
    cin >> n;
    
    vector<int> nums(n);
    cout << "Enter numbers: ";
    for (int i = 0; i < n; i++) cin >> nums[i];
    
    TopDown td;
    BottomUp bu;
    
    cout << "\n--- Results ---" << endl;
    cout << "Top-Down: " << td.deleteAndEarn(nums) << endl;
    cout << "Bottom-Up: " << bu.deleteAndEarn(nums) << endl;
    cout << "Bottom-Up Optimized: " << bu.deleteAndEarnOptimized(nums) << endl;
    
    return 0;
}









