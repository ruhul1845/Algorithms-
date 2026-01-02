/*
    Longest Increasing Subsequence (LIS)
    Problem: Given an array, find the length of the longest subsequence
             such that all elements are sorted in increasing order.
    
    Example:
    arr = [10, 9, 2, 5, 3, 7, 101, 18]
    LIS = [2, 3, 7, 101] or [2, 5, 7, 101], Length = 4
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<vector<int>> dp;
    vector<int> arr;
    
    // prev_idx is shifted by 1 (0 means -1, 1 means 0, etc.)
    int solve(int idx, int prev_idx) {
        if (idx == arr.size()) return 0;
        
        if (dp[idx][prev_idx + 1] != -1) return dp[idx][prev_idx + 1];
        
        // Don't take current element
        int notTake = solve(idx + 1, prev_idx);
        
        // Take current element if valid
        int take = 0;
        if (prev_idx == -1 || arr[idx] > arr[prev_idx]) {
            take = 1 + solve(idx + 1, idx);
        }
        
        return dp[idx][prev_idx + 1] = max(take, notTake);
    }
    
public:
    int lis(vector<int>& nums) {
        arr = nums;
        int n = nums.size();
        dp.assign(n, vector<int>(n + 1, -1));
        return solve(0, -1);
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    // O(n^2) approach
    int lis(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        
        // dp[i] = length of LIS ending at index i
        vector<int> dp(n, 1);
        int maxLen = 1;
        
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (nums[j] < nums[i]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            maxLen = max(maxLen, dp[i]);
        }
        
        return maxLen;
    }
    
    // O(n log n) approach using Binary Search
    int lisOptimized(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        
        vector<int> tail; // tail[i] = smallest ending element of LIS of length i+1
        
        for (int num : nums) {
            auto it = lower_bound(tail.begin(), tail.end(), num);
            if (it == tail.end()) {
                tail.push_back(num);
            } else {
                *it = num;
            }
        }
        
        return tail.size();
    }
    
    // Print one LIS
    vector<int> printLIS(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return {};
        
        vector<int> dp(n, 1);
        vector<int> parent(n, -1);
        int maxLen = 1, endIdx = 0;
        
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (nums[j] < nums[i] && dp[j] + 1 > dp[i]) {
                    dp[i] = dp[j] + 1;
                    parent[i] = j;
                }
            }
            if (dp[i] > maxLen) {
                maxLen = dp[i];
                endIdx = i;
            }
        }
        
        // Reconstruct LIS
        vector<int> lis;
        int curr = endIdx;
        while (curr != -1) {
            lis.push_back(nums[curr]);
            curr = parent[curr];
        }
        
        reverse(lis.begin(), lis.end());
        return lis;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cout << "Enter array size: ";
    cin >> n;
    
    vector<int> arr(n);
    cout << "Enter array elements: ";
    for (int i = 0; i < n; i++) cin >> arr[i];
    
    TopDown td;
    BottomUp bu;
    
    cout << "\n--- Results ---" << endl;
    cout << "Top-Down (Memoization): " << td.lis(arr) << endl;
    cout << "Bottom-Up O(n^2): " << bu.lis(arr) << endl;
    cout << "Bottom-Up O(n log n): " << bu.lisOptimized(arr) << endl;
    
    cout << "One LIS: ";
    vector<int> lis = bu.printLIS(arr);
    for (int x : lis) {
        cout << x << " ";
    }
    cout << endl;
    
    return 0;
}

/*
    Time Complexity:
        - Top-Down: O(n^2)
        - Bottom-Up O(n^2): O(n^2)
        - Bottom-Up Optimized: O(n log n)
    Space Complexity: O(n)
*/









