/*
    Traveling Salesman Problem (TSP)
    - Find minimum cost Hamiltonian cycle
    - DP with bitmask
    - Time: O(2^n * n²), Space: O(2^n * n)
*/

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

class TSP {
public:
    int n;
    vector<vector<int>> dist;
    vector<vector<int>> dp;
    vector<vector<int>> parent;
    
    TSP(vector<vector<int>>& d) : n(d.size()), dist(d) {}
    
    // ==================== Basic TSP ====================
    int solve() {
        dp.assign(1 << n, vector<int>(n, INF));
        dp[1][0] = 0; // Start from node 0
        
        for (int mask = 1; mask < (1 << n); mask++) {
            for (int u = 0; u < n; u++) {
                if (!(mask & (1 << u)) || dp[mask][u] == INF) continue;
                
                for (int v = 0; v < n; v++) {
                    if (mask & (1 << v)) continue;
                    int newMask = mask | (1 << v);
                    dp[newMask][v] = min(dp[newMask][v], dp[mask][u] + dist[u][v]);
                }
            }
        }
        
        int fullMask = (1 << n) - 1;
        int ans = INF;
        for (int i = 1; i < n; i++) {
            if (dp[fullMask][i] != INF) {
                ans = min(ans, dp[fullMask][i] + dist[i][0]);
            }
        }
        return ans;
    }
    
    // ==================== TSP with Path ====================
    pair<int, vector<int>> solveWithPath() {
        dp.assign(1 << n, vector<int>(n, INF));
        parent.assign(1 << n, vector<int>(n, -1));
        dp[1][0] = 0;
        
        for (int mask = 1; mask < (1 << n); mask++) {
            for (int u = 0; u < n; u++) {
                if (!(mask & (1 << u)) || dp[mask][u] == INF) continue;
                
                for (int v = 0; v < n; v++) {
                    if (mask & (1 << v)) continue;
                    int newMask = mask | (1 << v);
                    if (dp[mask][u] + dist[u][v] < dp[newMask][v]) {
                        dp[newMask][v] = dp[mask][u] + dist[u][v];
                        parent[newMask][v] = u;
                    }
                }
            }
        }
        
        int fullMask = (1 << n) - 1;
        int ans = INF, lastNode = -1;
        
        for (int i = 1; i < n; i++) {
            if (dp[fullMask][i] != INF && dp[fullMask][i] + dist[i][0] < ans) {
                ans = dp[fullMask][i] + dist[i][0];
                lastNode = i;
            }
        }
        
        vector<int> path = {0};
        int mask = fullMask, curr = lastNode;
        
        while (curr != 0) {
            path.push_back(curr);
            int prev = parent[mask][curr];
            mask ^= (1 << curr);
            curr = prev;
        }
        reverse(path.begin(), path.end());
        path.push_back(0);
        
        return {ans, path};
    }
};

// ==================== Held-Karp Algorithm (same as above, cleaner) ====================
int heldKarp(vector<vector<int>>& dist) {
    int n = dist.size();
    vector<vector<int>> dp(1 << n, vector<int>(n, INF));
    dp[1][0] = 0;
    
    for (int mask = 1; mask < (1 << n); mask++) {
        if (!(mask & 1)) continue; // Must include start node
        
        for (int last = 0; last < n; last++) {
            if (!(mask & (1 << last)) || dp[mask][last] == INF) continue;
            
            for (int next = 0; next < n; next++) {
                if (mask & (1 << next)) continue;
                int newMask = mask | (1 << next);
                dp[newMask][next] = min(dp[newMask][next], dp[mask][last] + dist[last][next]);
            }
        }
    }
    
    int fullMask = (1 << n) - 1;
    int ans = INF;
    for (int i = 1; i < n; i++) {
        ans = min(ans, dp[fullMask][i] + dist[i][0]);
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cout << "=== Traveling Salesman Problem Demo ===" << endl;
    
    vector<vector<int>> dist = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };
    
    TSP tsp(dist);
    cout << "Minimum cost: " << tsp.solve() << endl;
    
    auto [cost, path] = tsp.solveWithPath();
    cout << "Optimal tour: ";
    for (int node : path) cout << node << " ";
    cout << "\nCost: " << cost << endl;
    
    cout << "\nHeld-Karp result: " << heldKarp(dist) << endl;
    
    return 0;
}









