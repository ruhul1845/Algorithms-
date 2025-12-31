/*
    Edit Distance (Levenshtein Distance)
    Problem: Given two strings, find the minimum number of operations
             required to convert string1 to string2.
             Operations: Insert, Delete, Replace
    
    Example:
    s1 = "horse", s2 = "ros"
    Output: 3 (horse -> rorse -> rose -> ros)
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<vector<int>> dp;
    string s1, s2;
    
    int solve(int i, int j) {
        // Base cases
        if (i < 0) return j + 1;  // Insert remaining chars of s2
        if (j < 0) return i + 1;  // Delete remaining chars of s1
        
        if (dp[i][j] != -1) return dp[i][j];
        
        // If characters match, no operation needed
        if (s1[i] == s2[j]) {
            return dp[i][j] = solve(i - 1, j - 1);
        }
        
        // Try all three operations and take minimum
        int insert = 1 + solve(i, j - 1);      // Insert s2[j] into s1
        int del = 1 + solve(i - 1, j);         // Delete s1[i]
        int replace = 1 + solve(i - 1, j - 1); // Replace s1[i] with s2[j]
        
        return dp[i][j] = min({insert, del, replace});
    }
    
public:
    int editDistance(string& str1, string& str2) {
        s1 = str1;
        s2 = str2;
        int n = s1.length(), m = s2.length();
        dp.assign(n, vector<int>(m, -1));
        return solve(n - 1, m - 1);
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    int editDistance(string& s1, string& s2) {
        int n = s1.length(), m = s2.length();
        
        // dp[i][j] = edit distance between s1[0..i-1] and s2[0..j-1]
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        
        // Base cases
        for (int i = 0; i <= n; i++) dp[i][0] = i;  // Delete all chars
        for (int j = 0; j <= m; j++) dp[0][j] = j;  // Insert all chars
        
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (s1[i - 1] == s2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = 1 + min({
                        dp[i][j - 1],     // Insert
                        dp[i - 1][j],     // Delete
                        dp[i - 1][j - 1]  // Replace
                    });
                }
            }
        }
        
        return dp[n][m];
    }
    
    // Space Optimized - O(m) space
    int editDistanceOptimized(string& s1, string& s2) {
        int n = s1.length(), m = s2.length();
        
        vector<int> prev(m + 1), curr(m + 1);
        
        for (int j = 0; j <= m; j++) prev[j] = j;
        
        for (int i = 1; i <= n; i++) {
            curr[0] = i;
            for (int j = 1; j <= m; j++) {
                if (s1[i - 1] == s2[j - 1]) {
                    curr[j] = prev[j - 1];
                } else {
                    curr[j] = 1 + min({curr[j - 1], prev[j], prev[j - 1]});
                }
            }
            swap(prev, curr);
        }
        
        return prev[m];
    }
    
    // Print the sequence of operations
    void printOperations(string& s1, string& s2) {
        int n = s1.length(), m = s2.length();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        
        for (int i = 0; i <= n; i++) dp[i][0] = i;
        for (int j = 0; j <= m; j++) dp[0][j] = j;
        
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (s1[i - 1] == s2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = 1 + min({dp[i][j - 1], dp[i - 1][j], dp[i - 1][j - 1]});
                }
            }
        }
        
        // Backtrack to find operations
        vector<string> operations;
        int i = n, j = m;
        
        while (i > 0 || j > 0) {
            if (i > 0 && j > 0 && s1[i - 1] == s2[j - 1]) {
                i--; j--;
            } else if (j > 0 && (i == 0 || dp[i][j - 1] <= dp[i - 1][j] && dp[i][j - 1] <= dp[i - 1][j - 1])) {
                operations.push_back("Insert '" + string(1, s2[j - 1]) + "' at position " + to_string(i));
                j--;
            } else if (i > 0 && (j == 0 || dp[i - 1][j] <= dp[i][j - 1] && dp[i - 1][j] <= dp[i - 1][j - 1])) {
                operations.push_back("Delete '" + string(1, s1[i - 1]) + "' at position " + to_string(i - 1));
                i--;
            } else {
                operations.push_back("Replace '" + string(1, s1[i - 1]) + "' with '" + string(1, s2[j - 1]) + "' at position " + to_string(i - 1));
                i--; j--;
            }
        }
        
        reverse(operations.begin(), operations.end());
        cout << "Operations:" << endl;
        for (const string& op : operations) {
            cout << "  " << op << endl;
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s1, s2;
    cout << "Enter first string: ";
    cin >> s1;
    cout << "Enter second string: ";
    cin >> s2;
    
    TopDown td;
    BottomUp bu;
    
    cout << "\n--- Results ---" << endl;
    cout << "Top-Down (Memoization): " << td.editDistance(s1, s2) << endl;
    cout << "Bottom-Up (Tabulation): " << bu.editDistance(s1, s2) << endl;
    cout << "Bottom-Up (Space Optimized): " << bu.editDistanceOptimized(s1, s2) << endl;
    
    bu.printOperations(s1, s2);
    
    return 0;
}

/*
    Time Complexity: O(n * m)
    Space Complexity:
        - Top-Down: O(n * m) for memoization + O(n + m) recursion stack
        - Bottom-Up: O(n * m)
        - Bottom-Up Optimized: O(m)
*/



