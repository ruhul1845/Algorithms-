/*
    Hamiltonian Path and Cycle
    - Path that visits every vertex exactly once
    - NP-complete problem
    - Time: O(n! * n) brute force, O(2^n * n²) DP
*/

#include <bits/stdc++.h>
using namespace std;

class HamiltonianPath {
public:
    int V;
    vector<vector<int>> adj;
    
    HamiltonianPath(int v) : V(v), adj(v) {}
    
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    // ==================== Backtracking Solution ====================
    bool hasHamiltonianPath() {
        vector<bool> visited(V, false);
        
        for (int start = 0; start < V; start++) {
            if (findPath(start, 1, visited)) return true;
        }
        return false;
    }
    
    bool findPath(int node, int count, vector<bool>& visited) {
        if (count == V) return true;
        
        visited[node] = true;
        
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                if (findPath(neighbor, count + 1, visited)) return true;
            }
        }
        
        visited[node] = false;
        return false;
    }
    
    // ==================== Get Hamiltonian Path ====================
    vector<int> getHamiltonianPath() {
        vector<bool> visited(V, false);
        vector<int> path;
        
        for (int start = 0; start < V; start++) {
            path.clear();
            if (findPathWithPath(start, visited, path)) return path;
        }
        return {};
    }
    
    bool findPathWithPath(int node, vector<bool>& visited, vector<int>& path) {
        visited[node] = true;
        path.push_back(node);
        
        if (path.size() == V) return true;
        
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                if (findPathWithPath(neighbor, visited, path)) return true;
            }
        }
        
        visited[node] = false;
        path.pop_back();
        return false;
    }
    
    // ==================== Hamiltonian Cycle ====================
    bool hasHamiltonianCycle() {
        vector<bool> visited(V, false);
        return findCycle(0, 1, visited);
    }
    
    bool findCycle(int node, int count, vector<bool>& visited) {
        if (count == V) {
            // Check if there's edge back to start (node 0)
            for (int neighbor : adj[node]) {
                if (neighbor == 0) return true;
            }
            return false;
        }
        
        visited[node] = true;
        
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                if (findCycle(neighbor, count + 1, visited)) return true;
            }
        }
        
        visited[node] = false;
        return false;
    }
    
    // ==================== DP with Bitmask ====================
    bool hasHamiltonianPathDP() {
        // dp[mask][i] = can reach node i with visited nodes as mask
        vector<vector<bool>> dp(1 << V, vector<bool>(V, false));
        
        for (int i = 0; i < V; i++) {
            dp[1 << i][i] = true;
        }
        
        for (int mask = 1; mask < (1 << V); mask++) {
            for (int u = 0; u < V; u++) {
                if (!(mask & (1 << u)) || !dp[mask][u]) continue;
                
                for (int v : adj[u]) {
                    if (!(mask & (1 << v))) {
                        dp[mask | (1 << v)][v] = true;
                    }
                }
            }
        }
        
        int fullMask = (1 << V) - 1;
        for (int i = 0; i < V; i++) {
            if (dp[fullMask][i]) return true;
        }
        return false;
    }
};

// ==================== Shortest Hamiltonian Path (TSP variant) ====================
class ShortestHamiltonianPath {
public:
    int solve(vector<vector<int>>& dist) {
        int n = dist.size();
        vector<vector<int>> dp(1 << n, vector<int>(n, INT_MAX));
        
        for (int i = 0; i < n; i++) {
            dp[1 << i][i] = 0;
        }
        
        for (int mask = 1; mask < (1 << n); mask++) {
            for (int u = 0; u < n; u++) {
                if (!(mask & (1 << u)) || dp[mask][u] == INT_MAX) continue;
                
                for (int v = 0; v < n; v++) {
                    if (mask & (1 << v)) continue;
                    int newMask = mask | (1 << v);
                    dp[newMask][v] = min(dp[newMask][v], dp[mask][u] + dist[u][v]);
                }
            }
        }
        
        int fullMask = (1 << n) - 1;
        int ans = INT_MAX;
        for (int i = 0; i < n; i++) {
            ans = min(ans, dp[fullMask][i]);
        }
        return ans;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cout << "=== Hamiltonian Path Demo ===" << endl;
    
    HamiltonianPath g(5);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    g.addEdge(4, 0);
    g.addEdge(0, 2);
    
    cout << "Has Hamiltonian Path: " << (g.hasHamiltonianPath() ? "Yes" : "No") << endl;
    cout << "Has Hamiltonian Cycle: " << (g.hasHamiltonianCycle() ? "Yes" : "No") << endl;
    cout << "Has Hamiltonian Path (DP): " << (g.hasHamiltonianPathDP() ? "Yes" : "No") << endl;
    
    auto path = g.getHamiltonianPath();
    cout << "Hamiltonian Path: ";
    for (int node : path) cout << node << " ";
    cout << endl;
    
    // Shortest Hamiltonian Path
    cout << "\n=== Shortest Hamiltonian Path ===" << endl;
    vector<vector<int>> dist = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };
    ShortestHamiltonianPath shp;
    cout << "Shortest path: " << shp.solve(dist) << endl;
    
    return 0;
}



