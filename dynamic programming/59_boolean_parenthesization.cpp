/*
    Boolean Parenthesization
    Problem: Count ways to parenthesize boolean expression to get True.
             Operands: T, F. Operators: &, |, ^
    
    Example: "T|T&F^T" → Output: 4
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    map<tuple<int, int, bool>, long long> dp;
    string expr;
    
    long long solve(int i, int j, bool isTrue) {
        if (i > j) return 0;
        if (i == j) {
            if (isTrue) return expr[i] == 'T';
            return expr[i] == 'F';
        }
        
        auto key = make_tuple(i, j, isTrue);
        if (dp.count(key)) return dp[key];
        
        long long ways = 0;
        
        for (int k = i + 1; k < j; k += 2) {
            char op = expr[k];
            
            long long lt = solve(i, k - 1, true);
            long long lf = solve(i, k - 1, false);
            long long rt = solve(k + 1, j, true);
            long long rf = solve(k + 1, j, false);
            
            if (op == '&') {
                if (isTrue) ways += lt * rt;
                else ways += lt * rf + lf * rt + lf * rf;
            } else if (op == '|') {
                if (isTrue) ways += lt * rt + lt * rf + lf * rt;
                else ways += lf * rf;
            } else { // XOR
                if (isTrue) ways += lt * rf + lf * rt;
                else ways += lt * rt + lf * rf;
            }
        }
        
        return dp[key] = ways;
    }
    
public:
    long long countWays(string& s) {
        expr = s;
        dp.clear();
        return solve(0, s.length() - 1, true);
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    long long countWays(string& s) {
        int n = s.length();
        
        // dpT[i][j] = ways to get True for s[i..j]
        // dpF[i][j] = ways to get False for s[i..j]
        vector<vector<long long>> dpT(n, vector<long long>(n, 0));
        vector<vector<long long>> dpF(n, vector<long long>(n, 0));
        
        // Base case: single operands
        for (int i = 0; i < n; i += 2) {
            dpT[i][i] = (s[i] == 'T');
            dpF[i][i] = (s[i] == 'F');
        }
        
        // Fill for increasing lengths
        for (int len = 3; len <= n; len += 2) {
            for (int i = 0; i + len - 1 < n; i += 2) {
                int j = i + len - 1;
                
                for (int k = i + 1; k < j; k += 2) {
                    char op = s[k];
                    
                    long long lt = dpT[i][k - 1];
                    long long lf = dpF[i][k - 1];
                    long long rt = dpT[k + 1][j];
                    long long rf = dpF[k + 1][j];
                    
                    if (op == '&') {
                        dpT[i][j] += lt * rt;
                        dpF[i][j] += lt * rf + lf * rt + lf * rf;
                    } else if (op == '|') {
                        dpT[i][j] += lt * rt + lt * rf + lf * rt;
                        dpF[i][j] += lf * rf;
                    } else { // XOR
                        dpT[i][j] += lt * rf + lf * rt;
                        dpF[i][j] += lt * rt + lf * rf;
                    }
                }
            }
        }
        
        return dpT[0][n - 1];
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string expr;
    cout << "Enter boolean expression (e.g., T|T&F^T): ";
    cin >> expr;
    
    TopDown td;
    BottomUp bu;
    
    cout << "\n--- Results ---" << endl;
    cout << "Top-Down: " << td.countWays(expr) << endl;
    cout << "Bottom-Up: " << bu.countWays(expr) << endl;
    
    return 0;
}


















