/*
    Integer Break
    Problem: Break n into sum of positive integers. Maximize product.
    
    Example: n = 10 → Output: 36 (3 + 3 + 4 = 10, 3*3*4 = 36)
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<int> dp;
    
    int solve(int n) {
        if (n <= 2) return 1;
        if (dp[n] != -1) return dp[n];
        
        int maxProd = 0;
        for (int i = 1; i < n; i++) {
            maxProd = max(maxProd, max(i * (n - i), i * solve(n - i)));
        }
        
        return dp[n] = maxProd;
    }
    
public:
    int integerBreak(int n) {
        dp.assign(n + 1, -1);
        return solve(n);
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    int integerBreak(int n) {
        vector<int> dp(n + 1, 0);
        dp[1] = 1;
        
        for (int i = 2; i <= n; i++) {
            for (int j = 1; j < i; j++) {
                dp[i] = max(dp[i], max(j * (i - j), j * dp[i - j]));
            }
        }
        
        return dp[n];
    }
    
    // Math: Use as many 3s as possible
    int integerBreakMath(int n) {
        if (n == 2) return 1;
        if (n == 3) return 2;
        
        int product = 1;
        while (n > 4) {
            product *= 3;
            n -= 3;
        }
        product *= n;
        
        return product;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cout << "Enter n: ";
    cin >> n;
    
    TopDown td;
    BottomUp bu;
    
    cout << "\n--- Results ---" << endl;
    cout << "Top-Down: " << td.integerBreak(n) << endl;
    cout << "Bottom-Up: " << bu.integerBreak(n) << endl;
    cout << "Math: " << bu.integerBreakMath(n) << endl;
    
    return 0;
}

