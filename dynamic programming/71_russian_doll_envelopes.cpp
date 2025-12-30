/*
    Russian Doll Envelopes
    Problem: Find max envelopes you can nest inside each other.
             Envelope (w1,h1) fits in (w2,h2) if w1 < w2 and h1 < h2.
    
    Example: [[5,4],[6,4],[6,7],[2,3]] → Output: 3 ([2,3] → [5,4] → [6,7])
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== SOLUTION ====================
class Solution {
public:
    // O(n²) DP approach
    int maxEnvelopesDP(vector<vector<int>>& envelopes) {
        int n = envelopes.size();
        if (n == 0) return 0;
        
        // Sort by width ascending, then by height descending (for same width)
        sort(envelopes.begin(), envelopes.end(), [](auto& a, auto& b) {
            return a[0] == b[0] ? a[1] > b[1] : a[0] < b[0];
        });
        
        // LIS on heights
        vector<int> dp(n, 1);
        int maxLen = 1;
        
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (envelopes[j][0] < envelopes[i][0] && 
                    envelopes[j][1] < envelopes[i][1]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            maxLen = max(maxLen, dp[i]);
        }
        
        return maxLen;
    }
    
    // O(n log n) using LIS with binary search
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        int n = envelopes.size();
        if (n == 0) return 0;
        
        // Sort by width ascending, height descending for same width
        sort(envelopes.begin(), envelopes.end(), [](auto& a, auto& b) {
            return a[0] == b[0] ? a[1] > b[1] : a[0] < b[0];
        });
        
        // LIS on heights using binary search
        vector<int> tail;
        
        for (auto& env : envelopes) {
            int h = env[1];
            auto it = lower_bound(tail.begin(), tail.end(), h);
            if (it == tail.end()) {
                tail.push_back(h);
            } else {
                *it = h;
            }
        }
        
        return tail.size();
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cout << "Enter number of envelopes: ";
    cin >> n;
    
    vector<vector<int>> envelopes(n, vector<int>(2));
    cout << "Enter dimensions (width height) for each:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> envelopes[i][0] >> envelopes[i][1];
    }
    
    Solution sol;
    
    cout << "\n--- Results ---" << endl;
    cout << "O(n²) DP: " << sol.maxEnvelopesDP(envelopes) << endl;
    cout << "O(n log n): " << sol.maxEnvelopes(envelopes) << endl;
    
    return 0;
}

