/*
    Minimum Cost Tree From Leaf Values
    Problem: Build binary tree from array (leaves in inorder).
             Non-leaf value = max of subtree leaves.
             Minimize sum of non-leaf values.
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<vector<int>> dp;
    vector<vector<int>> maxVal;
    vector<int> arr;
    
    int solve(int i, int j) {
        if (i >= j) return 0;
        if (dp[i][j] != -1) return dp[i][j];
        
        int minCost = INT_MAX;
        for (int k = i; k < j; k++) {
            int cost = maxVal[i][k] * maxVal[k + 1][j] + solve(i, k) + solve(k + 1, j);
            minCost = min(minCost, cost);
        }
        
        return dp[i][j] = minCost;
    }
    
public:
    int mctFromLeafValues(vector<int>& a) {
        arr = a;
        int n = arr.size();
        
        // Precompute max values
        maxVal.assign(n, vector<int>(n, 0));
        for (int i = 0; i < n; i++) {
            maxVal[i][i] = arr[i];
            for (int j = i + 1; j < n; j++) {
                maxVal[i][j] = max(maxVal[i][j - 1], arr[j]);
            }
        }
        
        dp.assign(n, vector<int>(n, -1));
        return solve(0, n - 1);
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    int mctFromLeafValues(vector<int>& arr) {
        int n = arr.size();
        
        // Precompute max values
        vector<vector<int>> maxVal(n, vector<int>(n, 0));
        for (int i = 0; i < n; i++) {
            maxVal[i][i] = arr[i];
            for (int j = i + 1; j < n; j++) {
                maxVal[i][j] = max(maxVal[i][j - 1], arr[j]);
            }
        }
        
        vector<vector<int>> dp(n, vector<int>(n, 0));
        
        for (int len = 2; len <= n; len++) {
            for (int i = 0; i + len - 1 < n; i++) {
                int j = i + len - 1;
                dp[i][j] = INT_MAX;
                
                for (int k = i; k < j; k++) {
                    dp[i][j] = min(dp[i][j], 
                        maxVal[i][k] * maxVal[k + 1][j] + dp[i][k] + dp[k + 1][j]);
                }
            }
        }
        
        return dp[0][n - 1];
    }
    
    // Greedy using stack - O(n)
    int mctFromLeafValuesGreedy(vector<int>& arr) {
        int cost = 0;
        stack<int> st;
        st.push(INT_MAX);
        
        for (int a : arr) {
            while (st.top() <= a) {
                int mid = st.top();
                st.pop();
                cost += mid * min(st.top(), a);
            }
            st.push(a);
        }
        
        while (st.size() > 2) {
            int top = st.top();
            st.pop();
            cost += top * st.top();
        }
        
        return cost;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cout << "Enter array size: ";
    cin >> n;
    
    vector<int> arr(n);
    cout << "Enter leaf values: ";
    for (int i = 0; i < n; i++) cin >> arr[i];
    
    TopDown td;
    BottomUp bu;
    
    cout << "\n--- Results ---" << endl;
    cout << "Top-Down: " << td.mctFromLeafValues(arr) << endl;
    cout << "Bottom-Up: " << bu.mctFromLeafValues(arr) << endl;
    cout << "Greedy (Stack): " << bu.mctFromLeafValuesGreedy(arr) << endl;
    
    return 0;
}









