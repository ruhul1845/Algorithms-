/*
    Profitable Schemes
    Problem: n members, minProfit required. Each crime needs group[i] members
             and gives profit[i]. Count schemes with at least minProfit.
*/

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    vector<vector<vector<int>>> dp;
    vector<int> group, profit;
    int minProfit;
    
    int solve(int idx, int members, int currProfit) {
        if (idx == group.size()) {
            return currProfit >= minProfit ? 1 : 0;
        }
        
        int profitIdx = min(currProfit, minProfit);
        if (dp[idx][members][profitIdx] != -1) {
            return dp[idx][members][profitIdx];
        }
        
        // Skip crime
        long long ways = solve(idx + 1, members, currProfit);
        
        // Do crime if enough members
        if (members >= group[idx]) {
            ways += solve(idx + 1, members - group[idx], 
                         min(minProfit, currProfit + profit[idx]));
        }
        
        return dp[idx][members][profitIdx] = ways % MOD;
    }
    
public:
    int profitableSchemes(int n, int mp, vector<int>& g, vector<int>& p) {
        group = g;
        profit = p;
        minProfit = mp;
        
        dp.assign(g.size(), vector<vector<int>>(n + 1, vector<int>(mp + 1, -1)));
        return solve(0, n, 0);
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    int profitableSchemes(int n, int minProfit, vector<int>& group, vector<int>& profit) {
        int numCrimes = group.size();
        
        // dp[j][k] = schemes with j members and at least k profit
        vector<vector<int>> dp(n + 1, vector<int>(minProfit + 1, 0));
        
        // Base case: 0 crimes, 0 members, 0 profit = 1 way
        for (int j = 0; j <= n; j++) {
            dp[j][0] = 1;
        }
        
        for (int i = 0; i < numCrimes; i++) {
            int g = group[i], p = profit[i];
            
            for (int j = n; j >= g; j--) {
                for (int k = minProfit; k >= 0; k--) {
                    int newProfit = min(minProfit, k + p);
                    dp[j][newProfit] = (dp[j][newProfit] + dp[j - g][k]) % MOD;
                }
            }
        }
        
        return dp[n][minProfit];
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, minProfit, numCrimes;
    cout << "Enter n (members), minProfit, number of crimes: ";
    cin >> n >> minProfit >> numCrimes;
    
    vector<int> group(numCrimes), profit(numCrimes);
    cout << "Enter group sizes: ";
    for (int i = 0; i < numCrimes; i++) cin >> group[i];
    cout << "Enter profits: ";
    for (int i = 0; i < numCrimes; i++) cin >> profit[i];
    
    TopDown td;
    BottomUp bu;
    
    cout << "\n--- Results ---" << endl;
    cout << "Top-Down: " << td.profitableSchemes(n, minProfit, group, profit) << endl;
    cout << "Bottom-Up: " << bu.profitableSchemes(n, minProfit, group, profit) << endl;
    
    return 0;
}







