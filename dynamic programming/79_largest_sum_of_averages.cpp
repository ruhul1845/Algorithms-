/*
    Largest Sum of Averages
    Problem: Partition array into at most K groups. Maximize sum of averages.
    
    Example: nums = [9,1,2,3,9], K = 3 → Output: 20.0
             Partitions: [9], [1,2,3], [9] → 9 + 2 + 9 = 20
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<vector<double>> dp;
    vector<double> prefix;
    vector<int> nums;
    
    double avg(int i, int j) {
        return (prefix[j + 1] - prefix[i]) / (j - i + 1);
    }
    
    double solve(int idx, int k) {
        if (idx == nums.size()) return 0;
        if (k == 1) return avg(idx, nums.size() - 1);
        if (dp[idx][k] >= 0) return dp[idx][k];
        
        double maxSum = 0;
        for (int i = idx; i <= nums.size() - k; i++) {
            maxSum = max(maxSum, avg(idx, i) + solve(i + 1, k - 1));
        }
        
        return dp[idx][k] = maxSum;
    }
    
public:
    double largestSumOfAverages(vector<int>& n, int K) {
        nums = n;
        int sz = nums.size();
        
        prefix.resize(sz + 1, 0);
        for (int i = 0; i < sz; i++) {
            prefix[i + 1] = prefix[i] + nums[i];
        }
        
        dp.assign(sz, vector<double>(K + 1, -1));
        return solve(0, K);
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    double largestSumOfAverages(vector<int>& nums, int K) {
        int n = nums.size();
        
        vector<double> prefix(n + 1, 0);
        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + nums[i];
        }
        
        auto avg = [&](int i, int j) {
            return (prefix[j + 1] - prefix[i]) / (j - i + 1);
        };
        
        // dp[i][k] = max sum for nums[i..n-1] with k groups
        vector<vector<double>> dp(n + 1, vector<double>(K + 1, 0));
        
        // Base case: k = 1
        for (int i = 0; i < n; i++) {
            dp[i][1] = avg(i, n - 1);
        }
        
        for (int k = 2; k <= K; k++) {
            for (int i = 0; i <= n - k; i++) {
                for (int j = i; j <= n - k; j++) {
                    dp[i][k] = max(dp[i][k], avg(i, j) + dp[j + 1][k - 1]);
                }
            }
        }
        
        return dp[0][K];
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, K;
    cout << "Enter array size and K: ";
    cin >> n >> K;
    
    vector<int> nums(n);
    cout << "Enter array elements: ";
    for (int i = 0; i < n; i++) cin >> nums[i];
    
    TopDown td;
    BottomUp bu;
    
    cout << fixed << setprecision(5);
    cout << "\n--- Results ---" << endl;
    cout << "Top-Down: " << td.largestSumOfAverages(nums, K) << endl;
    cout << "Bottom-Up: " << bu.largestSumOfAverages(nums, K) << endl;
    
    return 0;
}









