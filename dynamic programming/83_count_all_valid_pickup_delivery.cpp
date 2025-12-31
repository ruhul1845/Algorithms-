/*
    Count All Valid Pickup and Delivery Options
    Problem: n orders, each with pickup (Pi) and delivery (Di).
             Pickup must happen before delivery. Count valid sequences.
    
    Example: n = 2 → Output: 6 (P1P2D1D2, P1P2D2D1, P1D1P2D2, etc.)
*/

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<vector<long long>> dp;
    
    // unpicked = orders not yet picked, undelivered = picked but not delivered
    long long solve(int unpicked, int undelivered) {
        if (unpicked == 0 && undelivered == 0) return 1;
        if (unpicked < 0 || undelivered < 0) return 0;
        if (dp[unpicked][undelivered] != -1) return dp[unpicked][undelivered];
        
        long long ways = 0;
        
        // Pick up an order
        if (unpicked > 0) {
            ways = (ways + unpicked * solve(unpicked - 1, undelivered + 1)) % MOD;
        }
        
        // Deliver an order
        if (undelivered > 0) {
            ways = (ways + undelivered * solve(unpicked, undelivered - 1)) % MOD;
        }
        
        return dp[unpicked][undelivered] = ways;
    }
    
public:
    int countOrders(int n) {
        dp.assign(n + 1, vector<long long>(n + 1, -1));
        return solve(n, 0);
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    int countOrders(int n) {
        // For n orders, we have 2n positions
        // Formula: For each new order, we have (2*i - 1) * i ways to insert
        // Result: product of (2*i - 1) * i for i = 1 to n
        
        long long result = 1;
        for (int i = 1; i <= n; i++) {
            // Insert pickup and delivery for order i
            // Pickup can go in 2*(i-1)+1 positions
            // Delivery can go in 2*(i-1)+2 positions after pickup
            // But we count pairs, so: (2i-1) * (2i) / 2 = (2i-1) * i
            result = (result * (2 * i - 1) % MOD * i) % MOD;
        }
        
        return result;
    }
    
    // Using factorial: n! * (2n-1)!!
    int countOrdersFactorial(int n) {
        // Result = n! * (2n-1)!! = (2n)! / 2^n
        long long result = 1;
        for (int i = 1; i <= 2 * n; i++) {
            result = (result * i) % MOD;
            if (i % 2 == 0) {
                // Divide by 2 using modular inverse
                result = (result * 500000004) % MOD; // 2^(-1) mod 10^9+7
            }
        }
        return result;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cout << "Enter number of orders: ";
    cin >> n;
    
    TopDown td;
    BottomUp bu;
    
    cout << "\n--- Results ---" << endl;
    cout << "Top-Down: " << td.countOrders(n) << endl;
    cout << "Bottom-Up: " << bu.countOrders(n) << endl;
    cout << "Factorial: " << bu.countOrdersFactorial(n) << endl;
    
    return 0;
}



