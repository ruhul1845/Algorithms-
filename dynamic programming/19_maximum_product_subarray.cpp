/*
    Maximum Product Subarray
    Problem: Find the contiguous subarray with the largest product.
    
    Example: [2,3,-2,4] → Output: 6 (subarray [2,3])
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<pair<long long, long long>> dp; // {max, min} ending at index
    vector<int> arr;
    
    pair<long long, long long> solve(int idx) {
        if (idx == 0) return {arr[0], arr[0]};
        
        if (dp[idx].first != LLONG_MIN) return dp[idx];
        
        auto [prevMax, prevMin] = solve(idx - 1);
        
        long long currMax = max({(long long)arr[idx], prevMax * arr[idx], prevMin * arr[idx]});
        long long currMin = min({(long long)arr[idx], prevMax * arr[idx], prevMin * arr[idx]});
        
        return dp[idx] = {currMax, currMin};
    }
    
public:
    int maxProduct(vector<int>& nums) {
        arr = nums;
        int n = nums.size();
        dp.assign(n, {LLONG_MIN, LLONG_MAX});
        
        long long maxProd = LLONG_MIN;
        for (int i = 0; i < n; i++) {
            maxProd = max(maxProd, solve(i).first);
        }
        return maxProd;
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    int maxProduct(vector<int>& nums) {
        int n = nums.size();
        
        vector<long long> dpMax(n), dpMin(n);
        dpMax[0] = dpMin[0] = nums[0];
        long long result = nums[0];
        
        for (int i = 1; i < n; i++) {
            dpMax[i] = max({(long long)nums[i], dpMax[i-1] * nums[i], dpMin[i-1] * nums[i]});
            dpMin[i] = min({(long long)nums[i], dpMax[i-1] * nums[i], dpMin[i-1] * nums[i]});
            result = max(result, dpMax[i]);
        }
        
        return result;
    }
    
    // Space Optimized O(1)
    int maxProductOptimized(vector<int>& nums) {
        long long maxProd = nums[0];
        long long minProd = nums[0];
        long long result = nums[0];
        
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] < 0) swap(maxProd, minProd);
            
            maxProd = max((long long)nums[i], maxProd * nums[i]);
            minProd = min((long long)nums[i], minProd * nums[i]);
            
            result = max(result, maxProd);
        }
        
        return result;
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
    cout << "Top-Down: " << td.maxProduct(nums) << endl;
    cout << "Bottom-Up: " << bu.maxProduct(nums) << endl;
    cout << "Bottom-Up Optimized: " << bu.maxProductOptimized(nums) << endl;
    
    return 0;
}









