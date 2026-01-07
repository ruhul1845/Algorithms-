/*
    House Robber II (Circular Houses)
    Problem: Houses are arranged in a circle. First and last houses are adjacent.
             Find maximum money without robbing adjacent houses.
    
    Example: houses = [2, 3, 2] → Output: 3 (can't rob first and last together)
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<int> dp;
    
    int solve(vector<int>& nums, int start, int end) {
        if (end < start) return 0;
        
        dp.assign(end - start + 1, -1);
        return helper(nums, start, end, end);
    }
    
    int helper(vector<int>& nums, int start, int end, int idx) {
        if (idx < start) return 0;
        if (dp[idx - start] != -1) return dp[idx - start];
        
        int rob = nums[idx] + helper(nums, start, end, idx - 2);
        int skip = helper(nums, start, end, idx - 1);
        
        return dp[idx - start] = max(rob, skip);
    }
    
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        if (n == 1) return nums[0];
        
        // Case 1: Rob houses 0 to n-2 (exclude last)
        // Case 2: Rob houses 1 to n-1 (exclude first)
        return max(solve(nums, 0, n-2), solve(nums, 1, n-1));
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
private:
    int robLinear(vector<int>& nums, int start, int end) {
        if (end < start) return 0;
        if (end == start) return nums[start];
        
        int prev2 = nums[start];
        int prev1 = max(nums[start], nums[start + 1]);
        
        for (int i = start + 2; i <= end; i++) {
            int curr = max(prev1, nums[i] + prev2);
            prev2 = prev1;
            prev1 = curr;
        }
        
        return prev1;
    }
    
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        if (n == 1) return nums[0];
        
        return max(robLinear(nums, 0, n-2), robLinear(nums, 1, n-1));
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
    
    return 0;
}


















