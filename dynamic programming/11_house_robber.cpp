/*
    House Robber
    Problem: Given an array representing money in each house,
             find maximum money you can rob without robbing adjacent houses.
    
    Example: houses = [2, 7, 9, 3, 1] → Output: 12 (rob houses 0, 2, 4)
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<int> dp;
    vector<int> nums;
    
    int solve(int idx) {
        if (idx < 0) return 0;
        if (dp[idx] != -1) return dp[idx];
        
        int rob = nums[idx] + solve(idx - 2);
        int skip = solve(idx - 1);
        
        return dp[idx] = max(rob, skip);
    }
    
public:
    int rob(vector<int>& houses) {
        nums = houses;
        int n = houses.size();
        if (n == 0) return 0;
        dp.assign(n, -1);
        return solve(n - 1);
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        if (n == 1) return nums[0];
        
        vector<int> dp(n);
        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]);
        
        for (int i = 2; i < n; i++) {
            dp[i] = max(dp[i-1], nums[i] + dp[i-2]);
        }
        
        return dp[n-1];
    }
    
    // Space Optimized O(1)
    int robOptimized(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        if (n == 1) return nums[0];
        
        int prev2 = nums[0];
        int prev1 = max(nums[0], nums[1]);
        
        for (int i = 2; i < n; i++) {
            int curr = max(prev1, nums[i] + prev2);
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
    cout << "Enter number of houses: ";
    cin >> n;
    
    vector<int> houses(n);
    cout << "Enter money in each house: ";
    for (int i = 0; i < n; i++) cin >> houses[i];
    
    TopDown td;
    BottomUp bu;
    
    cout << "\n--- Results ---" << endl;
    cout << "Top-Down: " << td.rob(houses) << endl;
    cout << "Bottom-Up: " << bu.rob(houses) << endl;
    cout << "Bottom-Up Optimized: " << bu.robOptimized(houses) << endl;
    
    return 0;
}

