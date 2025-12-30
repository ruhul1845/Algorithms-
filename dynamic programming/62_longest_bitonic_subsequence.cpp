/*
    Longest Bitonic Subsequence
    Problem: Find longest subsequence that first increases then decreases.
    
    Example: [1,11,2,10,4,5,2,1] → Output: 6 ([1,2,10,4,2,1])
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== SOLUTION ====================
class Solution {
public:
    int longestBitonicSubsequence(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        
        // LIS ending at each index (from left)
        vector<int> lis(n, 1);
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (nums[j] < nums[i]) {
                    lis[i] = max(lis[i], lis[j] + 1);
                }
            }
        }
        
        // LDS starting at each index (from right)
        vector<int> lds(n, 1);
        for (int i = n - 2; i >= 0; i--) {
            for (int j = n - 1; j > i; j--) {
                if (nums[i] > nums[j]) {
                    lds[i] = max(lds[i], lds[j] + 1);
                }
            }
        }
        
        // Combine: bitonic[i] = lis[i] + lds[i] - 1
        int maxLen = 0;
        for (int i = 0; i < n; i++) {
            maxLen = max(maxLen, lis[i] + lds[i] - 1);
        }
        
        return maxLen;
    }
    
    // Print the subsequence
    vector<int> getBitonicSubseq(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return {};
        
        vector<int> lis(n, 1), lds(n, 1);
        vector<int> lisParent(n, -1), ldsParent(n, -1);
        
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (nums[j] < nums[i] && lis[j] + 1 > lis[i]) {
                    lis[i] = lis[j] + 1;
                    lisParent[i] = j;
                }
            }
        }
        
        for (int i = n - 2; i >= 0; i--) {
            for (int j = n - 1; j > i; j--) {
                if (nums[i] > nums[j] && lds[j] + 1 > lds[i]) {
                    lds[i] = lds[j] + 1;
                    ldsParent[i] = j;
                }
            }
        }
        
        int maxLen = 0, peakIdx = 0;
        for (int i = 0; i < n; i++) {
            if (lis[i] + lds[i] - 1 > maxLen) {
                maxLen = lis[i] + lds[i] - 1;
                peakIdx = i;
            }
        }
        
        // Build increasing part
        vector<int> result;
        stack<int> incPart;
        int idx = peakIdx;
        while (idx != -1) {
            incPart.push(nums[idx]);
            idx = lisParent[idx];
        }
        while (!incPart.empty()) {
            result.push_back(incPart.top());
            incPart.pop();
        }
        
        // Build decreasing part (skip peak as it's already added)
        idx = ldsParent[peakIdx];
        while (idx != -1) {
            result.push_back(nums[idx]);
            idx = ldsParent[idx];
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
    
    Solution sol;
    
    cout << "\n--- Results ---" << endl;
    cout << "Length: " << sol.longestBitonicSubsequence(nums) << endl;
    
    cout << "Subsequence: ";
    vector<int> subseq = sol.getBitonicSubseq(nums);
    for (int x : subseq) cout << x << " ";
    cout << endl;
    
    return 0;
}

