/*
    Longest Turbulent Subarray
    Problem: Subarray where comparisons alternate: a < b > c < d > e...
    
    Example: [9,4,2,10,7,8,8,1,9] → Output: 5 ([4,2,10,7,8])
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<vector<int>> dp;
    vector<int> arr;
    
    // dir: 1 = prev was increasing, -1 = prev was decreasing
    int solve(int idx, int dir) {
        if (idx == arr.size()) return 0;
        if (dp[idx][dir + 1] != -1) return dp[idx][dir + 1];
        
        int len = 0;
        if (dir == 0) {
            // Start of subarray
            if (idx + 1 < arr.size()) {
                if (arr[idx] < arr[idx + 1]) {
                    len = max(len, 1 + solve(idx + 1, 1));
                } else if (arr[idx] > arr[idx + 1]) {
                    len = max(len, 1 + solve(idx + 1, -1));
                }
            }
        } else {
            // Continue turbulent pattern
            if (idx + 1 < arr.size()) {
                if (dir == 1 && arr[idx] > arr[idx + 1]) {
                    len = 1 + solve(idx + 1, -1);
                } else if (dir == -1 && arr[idx] < arr[idx + 1]) {
                    len = 1 + solve(idx + 1, 1);
                }
            }
        }
        
        return dp[idx][dir + 1] = len;
    }
    
public:
    int maxTurbulenceSize(vector<int>& a) {
        arr = a;
        int n = arr.size();
        if (n == 1) return 1;
        
        dp.assign(n, vector<int>(3, -1));
        
        int maxLen = 1;
        for (int i = 0; i < n; i++) {
            maxLen = max(maxLen, 1 + solve(i, 0));
        }
        
        return maxLen;
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    int maxTurbulenceSize(vector<int>& arr) {
        int n = arr.size();
        if (n == 1) return 1;
        
        // inc[i] = length of turbulent subarray ending at i with arr[i-1] < arr[i]
        // dec[i] = length of turbulent subarray ending at i with arr[i-1] > arr[i]
        vector<int> inc(n, 1), dec(n, 1);
        int maxLen = 1;
        
        for (int i = 1; i < n; i++) {
            if (arr[i] > arr[i - 1]) {
                inc[i] = dec[i - 1] + 1;
                dec[i] = 1;
            } else if (arr[i] < arr[i - 1]) {
                dec[i] = inc[i - 1] + 1;
                inc[i] = 1;
            }
            maxLen = max(maxLen, max(inc[i], dec[i]));
        }
        
        return maxLen;
    }
    
    // Space Optimized O(1)
    int maxTurbulenceSizeOptimized(vector<int>& arr) {
        int n = arr.size();
        if (n == 1) return 1;
        
        int inc = 1, dec = 1, maxLen = 1;
        
        for (int i = 1; i < n; i++) {
            if (arr[i] > arr[i - 1]) {
                inc = dec + 1;
                dec = 1;
            } else if (arr[i] < arr[i - 1]) {
                dec = inc + 1;
                inc = 1;
            } else {
                inc = dec = 1;
            }
            maxLen = max(maxLen, max(inc, dec));
        }
        
        return maxLen;
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
    cout << "Top-Down: " << td.maxTurbulenceSize(arr) << endl;
    cout << "Bottom-Up: " << bu.maxTurbulenceSize(arr) << endl;
    cout << "Space Optimized: " << bu.maxTurbulenceSizeOptimized(arr) << endl;
    
    return 0;
}


















