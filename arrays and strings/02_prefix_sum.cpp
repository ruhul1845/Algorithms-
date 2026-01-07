/*
 * Prefix Sum and Difference Array Techniques
 * Efficient range query and update operations
 */

#include <bits/stdc++.h>
using namespace std;

// 1. Basic Prefix Sum
class PrefixSum {
    vector<int> prefix;
public:
    PrefixSum(vector<int>& arr) {
        int n = arr.size();
        prefix.resize(n + 1, 0);
        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + arr[i];
        }
    }
    
    // Range sum query [l, r] - O(1)
    int rangeSum(int l, int r) {
        return prefix[r + 1] - prefix[l];
    }
};

// 2. 2D Prefix Sum
class PrefixSum2D {
    vector<vector<int>> prefix;
public:
    PrefixSum2D(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        prefix.resize(m + 1, vector<int>(n + 1, 0));
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                prefix[i][j] = matrix[i-1][j-1] 
                             + prefix[i-1][j] 
                             + prefix[i][j-1] 
                             - prefix[i-1][j-1];
            }
        }
    }
    
    // Sum of rectangle (r1,c1) to (r2,c2) - O(1)
    int sumRegion(int r1, int c1, int r2, int c2) {
        return prefix[r2+1][c2+1] 
             - prefix[r1][c2+1] 
             - prefix[r2+1][c1] 
             + prefix[r1][c1];
    }
};

// 3. Subarray Sum Equals K
int subarraySum(vector<int>& arr, int k) {
    unordered_map<int, int> prefixCount;
    prefixCount[0] = 1;
    int sum = 0, count = 0;
    
    for (int num : arr) {
        sum += num;
        if (prefixCount.find(sum - k) != prefixCount.end()) {
            count += prefixCount[sum - k];
        }
        prefixCount[sum]++;
    }
    return count;
}

// 4. Product of Array Except Self
vector<int> productExceptSelf(vector<int>& nums) {
    int n = nums.size();
    vector<int> result(n, 1);
    
    // Left products
    int left = 1;
    for (int i = 0; i < n; i++) {
        result[i] = left;
        left *= nums[i];
    }
    
    // Right products
    int right = 1;
    for (int i = n - 1; i >= 0; i--) {
        result[i] *= right;
        right *= nums[i];
    }
    
    return result;
}

// 5. Difference Array for Range Updates
class DifferenceArray {
    vector<int> diff;
    int n;
public:
    DifferenceArray(int size) : n(size) {
        diff.resize(n + 1, 0);
    }
    
    // Add value in range [l, r] - O(1)
    void rangeUpdate(int l, int r, int val) {
        diff[l] += val;
        diff[r + 1] -= val;
    }
    
    // Get final array after all updates - O(n)
    vector<int> getArray() {
        vector<int> result(n);
        result[0] = diff[0];
        for (int i = 1; i < n; i++) {
            result[i] = result[i-1] + diff[i];
        }
        return result;
    }
};

// 6. Maximum Subarray Sum (Kadane's Algorithm)
int maxSubArray(vector<int>& arr) {
    int maxSum = arr[0];
    int currentSum = arr[0];
    
    for (int i = 1; i < arr.size(); i++) {
        currentSum = max(arr[i], currentSum + arr[i]);
        maxSum = max(maxSum, currentSum);
    }
    return maxSum;
}

int main() {
    // Test Prefix Sum
    vector<int> arr = {1, 2, 3, 4, 5};
    PrefixSum ps(arr);
    cout << "Sum from index 1 to 3: " << ps.rangeSum(1, 3) << endl;
    
    // Test 2D Prefix Sum
    vector<vector<int>> matrix = {{3, 0, 1, 4}, {5, 6, 3, 2}, {1, 2, 0, 1}};
    PrefixSum2D ps2d(matrix);
    cout << "Sum of region (1,1) to (2,2): " << ps2d.sumRegion(1, 1, 2, 2) << endl;
    
    // Test Kadane's Algorithm
    vector<int> arr2 = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    cout << "Maximum Subarray Sum: " << maxSubArray(arr2) << endl;
    
    return 0;
}










