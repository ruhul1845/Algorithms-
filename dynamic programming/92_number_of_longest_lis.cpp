/*
    Number of Longest Increasing Subsequences
    Problem: Find count of LIS with maximum length.
    
    Example: [1,3,5,4,7] → Output: 2 ([1,3,5,7] and [1,3,4,7])
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== DP APPROACH ====================
class Solution {
public:
    int findNumberOfLIS(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        
        vector<int> length(n, 1); // length[i] = length of LIS ending at i
        vector<int> count(n, 1);  // count[i] = number of LIS ending at i
        int maxLen = 1;
        
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (nums[j] < nums[i]) {
                    if (length[j] + 1 > length[i]) {
                        length[i] = length[j] + 1;
                        count[i] = count[j];
                    } else if (length[j] + 1 == length[i]) {
                        count[i] += count[j];
                    }
                }
            }
            maxLen = max(maxLen, length[i]);
        }
        
        int result = 0;
        for (int i = 0; i < n; i++) {
            if (length[i] == maxLen) {
                result += count[i];
            }
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
    cout << "Number of LIS: " << sol.findNumberOfLIS(nums) << endl;
    
    return 0;
}

