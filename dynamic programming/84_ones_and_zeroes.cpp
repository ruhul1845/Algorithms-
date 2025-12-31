/*
    Ones and Zeroes
    Problem: Given strings of 0s and 1s, find max subset size with
             at most m 0s and n 1s total.
    
    Example: strs = ["10","0001","111001","1","0"], m = 5, n = 3
             Output: 4 ({"10","0001","1","0"})
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<vector<vector<int>>> dp;
    vector<pair<int, int>> counts; // {zeros, ones} for each string
    
    int solve(int idx, int m, int n) {
        if (idx < 0) return 0;
        if (dp[idx][m][n] != -1) return dp[idx][m][n];
        
        // Don't take
        int notTake = solve(idx - 1, m, n);
        
        // Take if possible
        int take = 0;
        if (counts[idx].first <= m && counts[idx].second <= n) {
            take = 1 + solve(idx - 1, m - counts[idx].first, n - counts[idx].second);
        }
        
        return dp[idx][m][n] = max(take, notTake);
    }
    
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        int sz = strs.size();
        counts.resize(sz);
        
        for (int i = 0; i < sz; i++) {
            int zeros = count(strs[i].begin(), strs[i].end(), '0');
            counts[i] = {zeros, (int)strs[i].length() - zeros};
        }
        
        dp.assign(sz, vector<vector<int>>(m + 1, vector<int>(n + 1, -1)));
        return solve(sz - 1, m, n);
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        int sz = strs.size();
        
        // dp[i][j] = max strings with i zeros and j ones
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        
        for (const string& s : strs) {
            int zeros = count(s.begin(), s.end(), '0');
            int ones = s.length() - zeros;
            
            // Traverse backwards (like 0/1 knapsack)
            for (int i = m; i >= zeros; i--) {
                for (int j = n; j >= ones; j--) {
                    dp[i][j] = max(dp[i][j], 1 + dp[i - zeros][j - ones]);
                }
            }
        }
        
        return dp[m][n];
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int numStrs, m, n;
    cout << "Enter number of strings, m, n: ";
    cin >> numStrs >> m >> n;
    
    vector<string> strs(numStrs);
    cout << "Enter strings: ";
    for (int i = 0; i < numStrs; i++) cin >> strs[i];
    
    TopDown td;
    BottomUp bu;
    
    cout << "\n--- Results ---" << endl;
    cout << "Top-Down: " << td.findMaxForm(strs, m, n) << endl;
    cout << "Bottom-Up: " << bu.findMaxForm(strs, m, n) << endl;
    
    return 0;
}



