/*
    Count Vowel Permutation
    Problem: Count strings of length n where each character follows rules:
             'a' can be followed by 'e'
             'e' can be followed by 'a' or 'i'
             'i' can be followed by any vowel except 'i'
             'o' can be followed by 'i' or 'u'
             'u' can be followed by 'a'
*/

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<vector<long long>> dp;
    // 0=a, 1=e, 2=i, 3=o, 4=u
    
    long long solve(int pos, int lastVowel, int n) {
        if (pos == n) return 1;
        if (dp[pos][lastVowel] != -1) return dp[pos][lastVowel];
        
        long long count = 0;
        
        if (lastVowel == 0) { // a -> e
            count = solve(pos + 1, 1, n);
        } else if (lastVowel == 1) { // e -> a, i
            count = (solve(pos + 1, 0, n) + solve(pos + 1, 2, n)) % MOD;
        } else if (lastVowel == 2) { // i -> a, e, o, u
            count = (solve(pos + 1, 0, n) + solve(pos + 1, 1, n) + 
                    solve(pos + 1, 3, n) + solve(pos + 1, 4, n)) % MOD;
        } else if (lastVowel == 3) { // o -> i, u
            count = (solve(pos + 1, 2, n) + solve(pos + 1, 4, n)) % MOD;
        } else { // u -> a
            count = solve(pos + 1, 0, n);
        }
        
        return dp[pos][lastVowel] = count;
    }
    
public:
    int countVowelPermutation(int n) {
        dp.assign(n, vector<long long>(5, -1));
        
        long long total = 0;
        for (int v = 0; v < 5; v++) {
            total = (total + solve(1, v, n)) % MOD;
        }
        
        return total;
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    int countVowelPermutation(int n) {
        // dp[v] = count of strings ending with vowel v
        vector<long long> dp(5, 1); // Start: one of each vowel
        
        for (int i = 2; i <= n; i++) {
            vector<long long> newDp(5, 0);
            
            // What can precede each vowel?
            newDp[0] = (dp[1] + dp[2] + dp[4]) % MOD; // a <- e, i, u
            newDp[1] = (dp[0] + dp[2]) % MOD;          // e <- a, i
            newDp[2] = (dp[1] + dp[3]) % MOD;          // i <- e, o
            newDp[3] = dp[2];                           // o <- i
            newDp[4] = (dp[2] + dp[3]) % MOD;          // u <- i, o
            
            dp = newDp;
        }
        
        long long total = 0;
        for (int v = 0; v < 5; v++) {
            total = (total + dp[v]) % MOD;
        }
        
        return total;
    }
    
    // Matrix Exponentiation for O(log n)
    int countVowelPermutationFast(int n) {
        // Transition matrix based on rules
        vector<vector<long long>> M = {
            {0, 1, 1, 0, 1}, // a <- e, i, u
            {1, 0, 1, 0, 0}, // e <- a, i
            {0, 1, 0, 1, 0}, // i <- e, o
            {0, 0, 1, 0, 0}, // o <- i
            {0, 0, 1, 1, 0}  // u <- i, o
        };
        
        auto result = matrixPow(M, n - 1);
        
        long long total = 0;
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                total = (total + result[i][j]) % MOD;
            }
        }
        
        return total;
    }
    
private:
    vector<vector<long long>> matrixMult(vector<vector<long long>>& A, vector<vector<long long>>& B) {
        int n = 5;
        vector<vector<long long>> C(n, vector<long long>(n, 0));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
                }
            }
        }
        return C;
    }
    
    vector<vector<long long>> matrixPow(vector<vector<long long>>& M, int p) {
        int n = 5;
        vector<vector<long long>> result(n, vector<long long>(n, 0));
        for (int i = 0; i < n; i++) result[i][i] = 1;
        
        while (p > 0) {
            if (p & 1) result = matrixMult(result, M);
            M = matrixMult(M, M);
            p >>= 1;
        }
        
        return result;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cout << "Enter string length: ";
    cin >> n;
    
    TopDown td;
    BottomUp bu;
    
    cout << "\n--- Results ---" << endl;
    cout << "Top-Down: " << td.countVowelPermutation(n) << endl;
    cout << "Bottom-Up: " << bu.countVowelPermutation(n) << endl;
    cout << "Matrix Exp: " << bu.countVowelPermutationFast(n) << endl;
    
    return 0;
}


















