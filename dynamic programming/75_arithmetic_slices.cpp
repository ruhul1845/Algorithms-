/*
    Arithmetic Slices
    Problem: Count arithmetic subarrays of length >= 3.
    
    Example: [1,2,3,4] → Output: 3 ([1,2,3], [2,3,4], [1,2,3,4])
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<int> dp;
    vector<int> nums;
    
    // dp[i] = count of arithmetic subarrays ending at i
    int solve(int i) {
        if (i < 2) return 0;
        if (dp[i] != -1) return dp[i];
        
        if (nums[i] - nums[i-1] == nums[i-1] - nums[i-2]) {
            return dp[i] = 1 + solve(i - 1);
        }
        return dp[i] = 0;
    }
    
public:
    int numberOfArithmeticSlices(vector<int>& n) {
        nums = n;
        int sz = nums.size();
        if (sz < 3) return 0;
        
        dp.assign(sz, -1);
        
        int total = 0;
        for (int i = 2; i < sz; i++) {
            total += solve(i);
        }
        
        return total;
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    int numberOfArithmeticSlices(vector<int>& nums) {
        int n = nums.size();
        if (n < 3) return 0;
        
        // dp[i] = arithmetic subarrays ending at i
        vector<int> dp(n, 0);
        int total = 0;
        
        for (int i = 2; i < n; i++) {
            if (nums[i] - nums[i-1] == nums[i-1] - nums[i-2]) {
                dp[i] = dp[i-1] + 1;
            }
            total += dp[i];
        }
        
        return total;
    }
    
    // Space Optimized O(1)
    int numberOfArithmeticSlicesOptimized(vector<int>& nums) {
        int n = nums.size();
        if (n < 3) return 0;
        
        int prev = 0, total = 0;
        
        for (int i = 2; i < n; i++) {
            if (nums[i] - nums[i-1] == nums[i-1] - nums[i-2]) {
                prev = prev + 1;
            } else {
                prev = 0;
            }
            total += prev;
        }
        
        return total;
    }
};

// ==================== Arithmetic Slices II - Subsequences ====================
class ArithmeticSlicesII {
public:
    // Count arithmetic subsequences of length >= 3
    int numberOfArithmeticSlices(vector<int>& nums) {
        int n = nums.size();
        if (n < 3) return 0;
        
        // dp[i][diff] = count of arithmetic subsequences ending at i with given diff
        vector<unordered_map<long long, int>> dp(n);
        int total = 0;
        
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                long long diff = (long long)nums[i] - nums[j];
                
                int count = dp[j].count(diff) ? dp[j][diff] : 0;
                dp[i][diff] += count + 1;
                total += count; // Only count if length >= 3
            }
        }
        
        return total;
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
    ArithmeticSlicesII as2;
    
    cout << "\n--- Results ---" << endl;
    cout << "Top-Down (Subarrays): " << td.numberOfArithmeticSlices(nums) << endl;
    cout << "Bottom-Up (Subarrays): " << bu.numberOfArithmeticSlices(nums) << endl;
    cout << "Space Optimized: " << bu.numberOfArithmeticSlicesOptimized(nums) << endl;
    cout << "Subsequences (length>=3): " << as2.numberOfArithmeticSlices(nums) << endl;
    
    return 0;
}


















