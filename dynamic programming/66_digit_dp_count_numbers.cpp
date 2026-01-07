/*
    Digit DP - Count Numbers with Property
    Problem: Count numbers from 1 to N that satisfy certain digit conditions.
    
    Example: Count numbers where sum of digits equals K
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== Count numbers with digit sum = K ====================
class DigitSumK {
private:
    vector<int> digits;
    int K;
    int dp[20][200][2]; // [pos][sum][tight]
    
    int solve(int pos, int sum, bool tight) {
        if (sum > K) return 0;
        if (pos == digits.size()) return (sum == K) ? 1 : 0;
        
        if (dp[pos][sum][tight] != -1) return dp[pos][sum][tight];
        
        int limit = tight ? digits[pos] : 9;
        int count = 0;
        
        for (int d = 0; d <= limit; d++) {
            count += solve(pos + 1, sum + d, tight && (d == limit));
        }
        
        return dp[pos][sum][tight] = count;
    }
    
public:
    int countWithDigitSum(long long N, int k) {
        if (N <= 0) return 0;
        K = k;
        digits.clear();
        
        while (N > 0) {
            digits.push_back(N % 10);
            N /= 10;
        }
        reverse(digits.begin(), digits.end());
        
        memset(dp, -1, sizeof(dp));
        return solve(0, 0, true);
    }
};

// ==================== Count numbers without consecutive 1s ====================
class NoConsecutiveOnes {
private:
    vector<int> digits;
    int dp[65][2][2]; // [pos][lastBit][tight]
    
    int solve(int pos, int lastBit, bool tight) {
        if (pos == digits.size()) return 1;
        
        if (dp[pos][lastBit][tight] != -1) return dp[pos][lastBit][tight];
        
        int limit = tight ? digits[pos] : 1;
        int count = 0;
        
        for (int d = 0; d <= limit; d++) {
            if (d == 1 && lastBit == 1) continue; // Skip consecutive 1s
            count += solve(pos + 1, d, tight && (d == limit));
        }
        
        return dp[pos][lastBit][tight] = count;
    }
    
public:
    int countWithoutConsecutiveOnes(long long N) {
        if (N <= 0) return 0;
        digits.clear();
        
        while (N > 0) {
            digits.push_back(N & 1);
            N >>= 1;
        }
        reverse(digits.begin(), digits.end());
        
        memset(dp, -1, sizeof(dp));
        return solve(0, 0, true);
    }
};

// ==================== Count numbers with digit d appearing exactly k times ====================
class DigitCountK {
private:
    vector<int> digits;
    int targetDigit, targetCount;
    int dp[20][20][2];
    
    int solve(int pos, int count, bool tight) {
        if (pos == digits.size()) return (count == targetCount) ? 1 : 0;
        
        if (dp[pos][count][tight] != -1) return dp[pos][count][tight];
        
        int limit = tight ? digits[pos] : 9;
        int result = 0;
        
        for (int d = 0; d <= limit; d++) {
            int newCount = count + (d == targetDigit ? 1 : 0);
            result += solve(pos + 1, newCount, tight && (d == limit));
        }
        
        return dp[pos][count][tight] = result;
    }
    
public:
    int countWithDigitOccurrence(long long N, int digit, int k) {
        if (N <= 0) return 0;
        targetDigit = digit;
        targetCount = k;
        digits.clear();
        
        while (N > 0) {
            digits.push_back(N % 10);
            N /= 10;
        }
        reverse(digits.begin(), digits.end());
        
        memset(dp, -1, sizeof(dp));
        return solve(0, 0, true);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long N;
    int k;
    
    cout << "=== Digit Sum Problem ===" << endl;
    cout << "Enter N and target sum K: ";
    cin >> N >> k;
    
    DigitSumK ds;
    cout << "Numbers from 1 to " << N << " with digit sum " << k << ": " 
         << ds.countWithDigitSum(N, k) << endl;
    
    cout << "\n=== No Consecutive 1s in Binary ===" << endl;
    cout << "Enter N: ";
    cin >> N;
    
    NoConsecutiveOnes nc;
    cout << "Numbers from 1 to " << N << " without consecutive 1s: " 
         << nc.countWithoutConsecutiveOnes(N) << endl;
    
    cout << "\n=== Digit Occurrence Count ===" << endl;
    cout << "Enter N, digit, and count: ";
    int d;
    cin >> N >> d >> k;
    
    DigitCountK dc;
    cout << "Numbers with digit " << d << " appearing " << k << " times: "
         << dc.countWithDigitOccurrence(N, d, k) << endl;
    
    return 0;
}


















