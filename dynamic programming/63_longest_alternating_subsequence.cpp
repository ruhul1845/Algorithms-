/*
    Longest Alternating Subsequence
    Problem: Find longest subsequence where elements alternate between
             increasing and decreasing (zigzag pattern).
    
    Example: [1,5,4] → Output: 3 (alternates: up, down)
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<vector<int>> dp;
    vector<int> nums;
    
    // lastMove: 0 = can go any, 1 = last was up, -1 = last was down
    int solve(int idx, int lastMove) {
        if (idx == nums.size()) return 0;
        
        int dpIdx = lastMove + 1; // Convert to 0,1,2
        if (dp[idx][dpIdx] != -1) return dp[idx][dpIdx];
        
        int skip = solve(idx + 1, lastMove);
        int take = 0;
        
        if (lastMove == 0) {
            // First element, can start with up or down
            take = 1 + max(solve(idx + 1, 1), solve(idx + 1, -1));
        } else if (lastMove == 1) {
            // Need to go down
            take = 1 + solve(idx + 1, -1);
        } else {
            // Need to go up
            take = 1 + solve(idx + 1, 1);
        }
        
        return dp[idx][dpIdx] = max(skip, take);
    }
    
public:
    int longestAlternating(vector<int>& n) {
        nums = n;
        dp.assign(nums.size(), vector<int>(3, -1));
        return solve(0, 0);
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    int longestAlternating(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        
        // up[i] = length of longest alternating subseq ending at i with last move up
        // down[i] = length ending at i with last move down
        vector<int> up(n, 1), down(n, 1);
        
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (nums[i] > nums[j]) {
                    up[i] = max(up[i], down[j] + 1);
                } else if (nums[i] < nums[j]) {
                    down[i] = max(down[i], up[j] + 1);
                }
            }
        }
        
        int maxLen = 0;
        for (int i = 0; i < n; i++) {
            maxLen = max(maxLen, max(up[i], down[i]));
        }
        
        return maxLen;
    }
    
    // Optimized O(n) solution
    int longestAlternatingOptimized(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        
        int up = 1, down = 1;
        
        for (int i = 1; i < n; i++) {
            if (nums[i] > nums[i - 1]) {
                up = down + 1;
            } else if (nums[i] < nums[i - 1]) {
                down = up + 1;
            }
        }
        
        return max(up, down);
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
    cout << "Top-Down: " << td.longestAlternating(nums) << endl;
    cout << "Bottom-Up O(n²): " << bu.longestAlternating(nums) << endl;
    cout << "Bottom-Up O(n): " << bu.longestAlternatingOptimized(nums) << endl;
    
    return 0;
}

