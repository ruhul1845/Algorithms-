/*
    Count Digit One (LeetCode 233)
    Problem: Count total occurrences of digit 1 in all numbers from 1 to n.
    
    Example: n = 13 → Output: 6 (1, 10, 11, 12, 13 → 1+1+2+1+1=6)
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Digit DP) ====================
class TopDown {
private:
    vector<int> digits;
    int dp[15][15][2]; // [pos][count][tight]
    
    int solve(int pos, int count, bool tight) {
        if (pos == digits.size()) return count;
        
        if (dp[pos][count][tight] != -1) return dp[pos][count][tight];
        
        int limit = tight ? digits[pos] : 9;
        int result = 0;
        
        for (int d = 0; d <= limit; d++) {
            result += solve(pos + 1, count + (d == 1), tight && (d == limit));
        }
        
        return dp[pos][count][tight] = result;
    }
    
public:
    int countDigitOne(int n) {
        if (n <= 0) return 0;
        digits.clear();
        
        int temp = n;
        while (temp > 0) {
            digits.push_back(temp % 10);
            temp /= 10;
        }
        reverse(digits.begin(), digits.end());
        
        memset(dp, -1, sizeof(dp));
        return solve(0, 0, true);
    }
};

// ==================== BOTTOM-UP APPROACH (Mathematical) ====================
class BottomUp {
public:
    int countDigitOne(int n) {
        if (n <= 0) return 0;
        
        long long count = 0;
        long long factor = 1;
        
        while (factor <= n) {
            long long higher = n / (factor * 10);
            long long curr = (n / factor) % 10;
            long long lower = n % factor;
            
            if (curr == 0) {
                count += higher * factor;
            } else if (curr == 1) {
                count += higher * factor + lower + 1;
            } else {
                count += (higher + 1) * factor;
            }
            
            factor *= 10;
        }
        
        return count;
    }
    
    // Generalized: count any digit d (0-9)
    long long countDigitD(long long n, int d) {
        if (n <= 0) return 0;
        
        long long count = 0;
        long long factor = 1;
        
        while (factor <= n) {
            long long higher = n / (factor * 10);
            long long curr = (n / factor) % 10;
            long long lower = n % factor;
            
            if (d == 0) {
                if (higher > 0) {
                    count += (higher - 1) * factor;
                    if (curr > d) count += factor;
                    else if (curr == d) count += lower + 1;
                }
            } else {
                if (curr < d) {
                    count += higher * factor;
                } else if (curr == d) {
                    count += higher * factor + lower + 1;
                } else {
                    count += (higher + 1) * factor;
                }
            }
            
            factor *= 10;
        }
        
        return count;
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
    cout << "Top-Down (Digit DP): " << td.countDigitOne(n) << endl;
    cout << "Bottom-Up (Math): " << bu.countDigitOne(n) << endl;
    
    cout << "\nCount of each digit 0-9:" << endl;
    for (int d = 0; d <= 9; d++) {
        cout << "Digit " << d << ": " << bu.countDigitD(n, d) << endl;
    }
    
    return 0;
}

