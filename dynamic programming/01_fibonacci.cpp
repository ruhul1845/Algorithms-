/*
    Fibonacci Sequence
    Problem: Find the nth Fibonacci number
    F(n) = F(n-1) + F(n-2), where F(0) = 0, F(1) = 1
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<long long> dp;
    
    long long solve(int n) {
        if (n <= 1) return n;
        if (dp[n] != -1) return dp[n];
        return dp[n] = solve(n - 1) + solve(n - 2);
    }
    
public:
    long long fibonacci(int n) {
        dp.assign(n + 1, -1);
        return solve(n);
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    long long fibonacci(int n) {
        if (n <= 1) return n;
        
        vector<long long> dp(n + 1);
        dp[0] = 0;
        dp[1] = 1;
        
        for (int i = 2; i <= n; i++) {
            dp[i] = dp[i - 1] + dp[i - 2];
        }
        
        return dp[n];
    }
    
    // Space Optimized Bottom-Up O(1) space
    long long fibonacciOptimized(int n) {
        if (n <= 1) return n;
        
        long long prev2 = 0, prev1 = 1;
        
        for (int i = 2; i <= n; i++) {
            long long curr = prev1 + prev2;
            prev2 = prev1;
            prev1 = curr;
        }
        
        return prev1;
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
    cout << "Top-Down (Memoization): " << td.fibonacci(n) << endl;
    cout << "Bottom-Up (Tabulation): " << bu.fibonacci(n) << endl;
    cout << "Bottom-Up (Space Optimized): " << bu.fibonacciOptimized(n) << endl;
    
    return 0;
}

/*
    Time Complexity: O(n)
    Space Complexity: 
        - Top-Down: O(n) for memoization + O(n) recursion stack
        - Bottom-Up: O(n) for dp array
        - Bottom-Up Optimized: O(1)
*/

