/*
    Partition to K Equal Sum Subsets
    Problem: Partition array into k subsets with equal sum.
    
    Example: nums = [4,3,2,3,5,2,1], k = 4 → Output: true
             (partitions: [5], [4,1], [3,2], [3,2])
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<int> nums;
    int target;
    int k;
    unordered_map<int, bool> dp;
    
    bool solve(int mask, int currSum, int subsetsLeft) {
        if (subsetsLeft == 0) return mask == (1 << nums.size()) - 1;
        if (currSum == target) return solve(mask, 0, subsetsLeft - 1);
        
        if (dp.count(mask)) return dp[mask];
        
        for (int i = 0; i < nums.size(); i++) {
            if (mask & (1 << i)) continue;
            if (currSum + nums[i] > target) continue;
            
            if (solve(mask | (1 << i), currSum + nums[i], subsetsLeft)) {
                return dp[mask] = true;
            }
        }
        
        return dp[mask] = false;
    }
    
public:
    bool canPartitionKSubsets(vector<int>& n, int K) {
        nums = n;
        k = K;
        
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum % k != 0) return false;
        target = sum / k;
        
        // Sort descending for better pruning
        sort(nums.begin(), nums.end(), greater<int>());
        
        if (nums[0] > target) return false;
        
        dp.clear();
        return solve(0, 0, k);
    }
};

// ==================== BOTTOM-UP APPROACH (Bitmask DP) ====================
class BottomUp {
public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int n = nums.size();
        int sum = accumulate(nums.begin(), nums.end(), 0);
        
        if (sum % k != 0) return false;
        int target = sum / k;
        
        sort(nums.begin(), nums.end(), greater<int>());
        if (nums[0] > target) return false;
        
        // dp[mask] = sum of current subset mod target
        // -1 = invalid state
        vector<int> dp(1 << n, -1);
        dp[0] = 0;
        
        for (int mask = 0; mask < (1 << n); mask++) {
            if (dp[mask] == -1) continue;
            
            for (int i = 0; i < n; i++) {
                if (mask & (1 << i)) continue;
                
                int newMask = mask | (1 << i);
                int newSum = dp[mask] + nums[i];
                
                if (newSum <= target) {
                    dp[newMask] = newSum % target;
                }
            }
        }
        
        return dp[(1 << n) - 1] == 0;
    }
};

// ==================== BACKTRACKING APPROACH ====================
class Backtrack {
private:
    bool backtrack(vector<int>& nums, vector<int>& buckets, int idx, int target) {
        if (idx == nums.size()) {
            for (int b : buckets) {
                if (b != target) return false;
            }
            return true;
        }
        
        for (int i = 0; i < buckets.size(); i++) {
            if (buckets[i] + nums[idx] > target) continue;
            
            // Skip duplicate buckets
            if (i > 0 && buckets[i] == buckets[i-1]) continue;
            
            buckets[i] += nums[idx];
            if (backtrack(nums, buckets, idx + 1, target)) return true;
            buckets[i] -= nums[idx];
        }
        
        return false;
    }
    
public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum % k != 0) return false;
        int target = sum / k;
        
        sort(nums.begin(), nums.end(), greater<int>());
        if (nums[0] > target) return false;
        
        vector<int> buckets(k, 0);
        return backtrack(nums, buckets, 0, target);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k;
    cout << "Enter array size and k: ";
    cin >> n >> k;
    
    vector<int> nums(n);
    cout << "Enter array elements: ";
    for (int i = 0; i < n; i++) cin >> nums[i];
    
    TopDown td;
    BottomUp bu;
    Backtrack bt;
    
    cout << "\n--- Results ---" << endl;
    cout << "Top-Down: " << (td.canPartitionKSubsets(nums, k) ? "Yes" : "No") << endl;
    cout << "Bottom-Up: " << (bu.canPartitionKSubsets(nums, k) ? "Yes" : "No") << endl;
    cout << "Backtrack: " << (bt.canPartitionKSubsets(nums, k) ? "Yes" : "No") << endl;
    
    return 0;
}


















