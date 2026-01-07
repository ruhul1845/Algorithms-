/*
    Jump Game
    Problem: Can you reach the last index? nums[i] = max jump length at i.
    
    Example: [2,3,1,1,4] → true, [3,2,1,0,4] → false
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<int> dp;
    vector<int> nums;
    
    bool solve(int idx) {
        if (idx >= nums.size() - 1) return true;
        if (dp[idx] != -1) return dp[idx];
        
        for (int jump = 1; jump <= nums[idx]; jump++) {
            if (solve(idx + jump)) {
                return dp[idx] = true;
            }
        }
        
        return dp[idx] = false;
    }
    
public:
    bool canJump(vector<int>& n) {
        nums = n;
        dp.assign(nums.size(), -1);
        return solve(0);
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        vector<bool> dp(n, false);
        dp[n - 1] = true;
        
        for (int i = n - 2; i >= 0; i--) {
            for (int jump = 1; jump <= nums[i] && i + jump < n; jump++) {
                if (dp[i + jump]) {
                    dp[i] = true;
                    break;
                }
            }
        }
        
        return dp[0];
    }
    
    // Greedy O(n) - track max reachable
    bool canJumpGreedy(vector<int>& nums) {
        int maxReach = 0;
        
        for (int i = 0; i < nums.size(); i++) {
            if (i > maxReach) return false;
            maxReach = max(maxReach, i + nums[i]);
        }
        
        return true;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cout << "Enter array size: ";
    cin >> n;
    
    vector<int> nums(n);
    cout << "Enter jump values: ";
    for (int i = 0; i < n; i++) cin >> nums[i];
    
    TopDown td;
    BottomUp bu;
    
    cout << "\n--- Results ---" << endl;
    cout << "Top-Down: " << (td.canJump(nums) ? "Yes" : "No") << endl;
    cout << "Bottom-Up: " << (bu.canJump(nums) ? "Yes" : "No") << endl;
    cout << "Greedy: " << (bu.canJumpGreedy(nums) ? "Yes" : "No") << endl;
    
    return 0;
}


















