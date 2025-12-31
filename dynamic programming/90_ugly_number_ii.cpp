/*
    Ugly Number II
    Problem: Find nth ugly number. Ugly numbers have only 2, 3, 5 as prime factors.
    
    Sequence: 1, 2, 3, 4, 5, 6, 8, 9, 10, 12, 15, ...
    Example: n = 10 → Output: 12
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== DP APPROACH ====================
class Solution {
public:
    int nthUglyNumber(int n) {
        vector<int> ugly(n);
        ugly[0] = 1;
        
        int i2 = 0, i3 = 0, i5 = 0;
        
        for (int i = 1; i < n; i++) {
            int next2 = ugly[i2] * 2;
            int next3 = ugly[i3] * 3;
            int next5 = ugly[i5] * 5;
            
            ugly[i] = min({next2, next3, next5});
            
            if (ugly[i] == next2) i2++;
            if (ugly[i] == next3) i3++;
            if (ugly[i] == next5) i5++;
        }
        
        return ugly[n - 1];
    }
    
    // Using priority queue
    int nthUglyNumberPQ(int n) {
        priority_queue<long, vector<long>, greater<long>> pq;
        unordered_set<long> seen;
        
        pq.push(1);
        seen.insert(1);
        
        long ugly = 1;
        vector<int> primes = {2, 3, 5};
        
        for (int i = 0; i < n; i++) {
            ugly = pq.top();
            pq.pop();
            
            for (int p : primes) {
                long next = ugly * p;
                if (!seen.count(next)) {
                    seen.insert(next);
                    pq.push(next);
                }
            }
        }
        
        return ugly;
    }
};

// ==================== Super Ugly Number ====================
class SuperUglyNumber {
public:
    // primes = [2,7,13,19], n = 12 → 32
    int nthSuperUglyNumber(int n, vector<int>& primes) {
        int k = primes.size();
        vector<int> ugly(n);
        ugly[0] = 1;
        
        vector<int> indices(k, 0);
        vector<long> nextMultiples(k);
        
        for (int i = 0; i < k; i++) {
            nextMultiples[i] = primes[i];
        }
        
        for (int i = 1; i < n; i++) {
            long minVal = *min_element(nextMultiples.begin(), nextMultiples.end());
            ugly[i] = minVal;
            
            for (int j = 0; j < k; j++) {
                if (nextMultiples[j] == minVal) {
                    indices[j]++;
                    nextMultiples[j] = (long)ugly[indices[j]] * primes[j];
                }
            }
        }
        
        return ugly[n - 1];
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cout << "Enter n for nth ugly number: ";
    cin >> n;
    
    Solution sol;
    
    cout << "\n--- Results ---" << endl;
    cout << "DP Approach: " << sol.nthUglyNumber(n) << endl;
    cout << "Priority Queue: " << sol.nthUglyNumberPQ(n) << endl;
    
    cout << "\nFirst 20 ugly numbers: ";
    for (int i = 1; i <= 20; i++) {
        cout << sol.nthUglyNumber(i) << " ";
    }
    cout << endl;
    
    return 0;
}



