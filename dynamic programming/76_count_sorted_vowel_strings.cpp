/*
    Count Sorted Vowel Strings
    Problem: Count strings of length n with vowels in sorted order.
    
    Example: n = 2 → Output: 15 (aa,ae,ai,ao,au,ee,ei,eo,eu,ii,io,iu,oo,ou,uu)
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<vector<int>> dp;
    
    int solve(int pos, int lastVowel, int n) {
        if (pos == n) return 1;
        if (dp[pos][lastVowel] != -1) return dp[pos][lastVowel];
        
        int count = 0;
        for (int v = lastVowel; v < 5; v++) {
            count += solve(pos + 1, v, n);
        }
        
        return dp[pos][lastVowel] = count;
    }
    
public:
    int countVowelStrings(int n) {
        dp.assign(n, vector<int>(5, -1));
        return solve(0, 0, n);
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    int countVowelStrings(int n) {
        // dp[i][j] = count of strings of length i starting with vowel j or higher
        vector<vector<int>> dp(n + 1, vector<int>(5, 0));
        
        // Base case: strings of length 1
        for (int v = 0; v < 5; v++) {
            dp[1][v] = 5 - v;
        }
        
        for (int len = 2; len <= n; len++) {
            dp[len][4] = 1; // Only 'u'
            for (int v = 3; v >= 0; v--) {
                dp[len][v] = dp[len][v + 1] + dp[len - 1][v];
            }
        }
        
        return dp[n][0];
    }
    
    // Combinatorics: C(n + 4, 4) = (n+4)! / (n! * 4!)
    int countVowelStringsMath(int n) {
        return (n + 1) * (n + 2) * (n + 3) * (n + 4) / 24;
    }
    
    // Simple O(n) solution
    int countVowelStringsSimple(int n) {
        int a = 1, e = 1, i = 1, o = 1, u = 1;
        
        for (int len = 2; len <= n; len++) {
            a = a + e + i + o + u;
            e = e + i + o + u;
            i = i + o + u;
            o = o + u;
            // u stays same
        }
        
        return a + e + i + o + u;
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
    cout << "Top-Down: " << td.countVowelStrings(n) << endl;
    cout << "Bottom-Up: " << bu.countVowelStrings(n) << endl;
    cout << "Simple O(n): " << bu.countVowelStringsSimple(n) << endl;
    cout << "Math (Combinatorics): " << bu.countVowelStringsMath(n) << endl;
    
    return 0;
}







