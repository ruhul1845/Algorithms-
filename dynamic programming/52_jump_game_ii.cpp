/*
    Jump Game II
    Problem: Minimum number of jumps to reach last index.
    
    Example: [2,3,1,1,4] → Output: 2 (0→1→4)
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<int> dp;
    vector<int> nums;
    
    int solve(int idx) {
        if (idx >= nums.size() - 1) return 0;
        if (dp[idx] != -1) return dp[idx];
        
        int minJumps = INT_MAX;
        for (int jump = 1; jump <= nums[idx]; jump++) {
            int next = solve(idx + jump);
            if (next != INT_MAX) {
                minJumps = min(minJumps, 1 + next);
            }
        }
        
        return dp[idx] = minJumps;
    }
    
public:
    int jump(vector<int>& n) {
        nums = n;
        dp.assign(nums.size(), -1);
        return solve(0);
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    int jump(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n, INT_MAX);
        dp[n - 1] = 0;
        
        for (int i = n - 2; i >= 0; i--) {
            for (int jump = 1; jump <= nums[i] && i + jump < n; jump++) {
                if (dp[i + jump] != INT_MAX) {
                    dp[i] = min(dp[i], 1 + dp[i + jump]);
                }
            }
        }
        
        return dp[0];
    }
    
    // Greedy O(n)
    int jumpGreedy(vector<int>& nums) {
        int n = nums.size();
        if (n <= 1) return 0;
        
        int jumps = 0;
        int currEnd = 0, farthest = 0;
        
        for (int i = 0; i < n - 1; i++) {
            farthest = max(farthest, i + nums[i]);
            
            if (i == currEnd) {
                jumps++;
                currEnd = farthest;
            }
        }
        
        return jumps;
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
    cout << "Top-Down: " << td.jump(nums) << endl;
    cout << "Bottom-Up: " << bu.jump(nums) << endl;
    cout << "Greedy: " << bu.jumpGreedy(nums) << endl;
    
    return 0;
}

