/*
    Frog Jump (LeetCode 403)
    Problem: Frog on stone 0 must reach last stone. If last jump was k,
             next jump must be k-1, k, or k+1. Can frog cross?
    
    Example: [0,1,3,5,6,8,12,17] → true
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== TOP-DOWN APPROACH (Memoization) ====================
class TopDown {
private:
    map<pair<int, int>, bool> dp;
    unordered_set<int> stoneSet;
    int lastStone;
    
    bool solve(int pos, int k) {
        if (pos == lastStone) return true;
        if (k <= 0) return false;
        
        auto key = make_pair(pos, k);
        if (dp.count(key)) return dp[key];
        
        for (int jump : {k - 1, k, k + 1}) {
            if (jump > 0 && stoneSet.count(pos + jump)) {
                if (solve(pos + jump, jump)) {
                    return dp[key] = true;
                }
            }
        }
        
        return dp[key] = false;
    }
    
public:
    bool canCross(vector<int>& stones) {
        if (stones[1] != 1) return false;
        
        for (int s : stones) stoneSet.insert(s);
        lastStone = stones.back();
        
        return solve(1, 1);
    }
};

// ==================== BOTTOM-UP APPROACH (Tabulation) ====================
class BottomUp {
public:
    bool canCross(vector<int>& stones) {
        int n = stones.size();
        if (stones[1] != 1) return false;
        
        unordered_map<int, int> stoneIdx;
        for (int i = 0; i < n; i++) {
            stoneIdx[stones[i]] = i;
        }
        
        // dp[i] = set of possible jump sizes to reach stone i
        vector<unordered_set<int>> dp(n);
        dp[0].insert(0);
        
        for (int i = 0; i < n; i++) {
            for (int k : dp[i]) {
                for (int jump : {k - 1, k, k + 1}) {
                    if (jump > 0) {
                        int nextPos = stones[i] + jump;
                        if (stoneIdx.count(nextPos)) {
                            dp[stoneIdx[nextPos]].insert(jump);
                        }
                    }
                }
            }
        }
        
        return !dp[n - 1].empty();
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cout << "Enter number of stones: ";
    cin >> n;
    
    vector<int> stones(n);
    cout << "Enter stone positions: ";
    for (int i = 0; i < n; i++) cin >> stones[i];
    
    TopDown td;
    BottomUp bu;
    
    cout << "\n--- Results ---" << endl;
    cout << "Top-Down: " << (td.canCross(stones) ? "Yes" : "No") << endl;
    cout << "Bottom-Up: " << (bu.canCross(stones) ? "Yes" : "No") << endl;
    
    return 0;
}


















