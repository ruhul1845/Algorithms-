/*
    Maximum Subarray (Kadane's Algorithm)
    Problem: Find the contiguous subarray with the largest sum.
    
    Example: [-2,1,-3,4,-1,2,1,-5,4] → Output: 6 (subarray [4,-1,2,1])
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<int> dp;
    vector<int> arr;
    
    // dp[i] = maximum subarray sum ending at index i
    int solve(int idx) {
        if (idx < 0) return 0;
        if (dp[idx] != INT_MIN) return dp[idx];
        
        int prev = solve(idx - 1);
        return dp[idx] = max(arr[idx], prev + arr[idx]);
    }
    
public:
    int maxSubArray(vector<int>& nums) {
        arr = nums;
        int n = nums.size();
        dp.assign(n, INT_MIN);
        
        int maxSum = INT_MIN;
        for (int i = 0; i < n; i++) {
            maxSum = max(maxSum, solve(i));
        }
        return maxSum;
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    // Kadane's Algorithm
    int maxSubArray(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n);
        dp[0] = nums[0];
        int maxSum = dp[0];
        
        for (int i = 1; i < n; i++) {
            dp[i] = max(nums[i], dp[i-1] + nums[i]);
            maxSum = max(maxSum, dp[i]);
        }
        
        return maxSum;
    }
    
    // Space Optimized O(1)
    int maxSubArrayOptimized(vector<int>& nums) {
        int currSum = nums[0];
        int maxSum = nums[0];
        
        for (int i = 1; i < nums.size(); i++) {
            currSum = max(nums[i], currSum + nums[i]);
            maxSum = max(maxSum, currSum);
        }
        
        return maxSum;
    }
    
    // Get the subarray
    pair<int, pair<int, int>> maxSubArrayWithIndices(vector<int>& nums) {
        int n = nums.size();
        int currSum = nums[0], maxSum = nums[0];
        int start = 0, end = 0, tempStart = 0;
        
        for (int i = 1; i < n; i++) {
            if (nums[i] > currSum + nums[i]) {
                currSum = nums[i];
                tempStart = i;
            } else {
                currSum = currSum + nums[i];
            }
            
            if (currSum > maxSum) {
                maxSum = currSum;
                start = tempStart;
                end = i;
            }
        }
        
        return {maxSum, {start, end}};
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
    cout << "Top-Down: " << td.maxSubArray(nums) << endl;
    cout << "Bottom-Up: " << bu.maxSubArray(nums) << endl;
    cout << "Bottom-Up Optimized: " << bu.maxSubArrayOptimized(nums) << endl;
    
    auto result = bu.maxSubArrayWithIndices(nums);
    cout << "Max Sum: " << result.first << " (indices " << result.second.first 
         << " to " << result.second.second << ")" << endl;
    
    return 0;
}

