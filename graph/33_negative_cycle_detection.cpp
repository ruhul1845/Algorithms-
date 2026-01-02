/*
    Negative Cycle Detection
    - Bellman-Ford based
    - SPFA based
*/

#include <bits/stdc++.h>
using namespace std;

class NegativeCycle {
public:
    int n;
    vector<tuple<int, int, long long>> edges;
    vector<vector<pair<int, long long>>> adj;
    
    NegativeCycle(int n) : n(n), adj(n) {}
    
    void addEdge(int u, int v, long long w) {
        edges.push_back({u, v, w});
        adj[u].push_back({v, w});
    }
    
    // ==================== Bellman-Ford Detection ====================
    bool hasNegativeCycleBF() {
        vector<long long> dist(n, 0);
        
        for (int i = 0; i < n; i++) {
            for (auto& [u, v, w] : edges) {
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                }
            }
        }
        
        // Check for negative cycle
        for (auto& [u, v, w] : edges) {
            if (dist[u] + w < dist[v]) return true;
        }
        return false;
    }
    
    // ==================== Find Negative Cycle ====================
    vector<int> findNegativeCycle() {
        vector<long long> dist(n, 0);
        vector<int> parent(n, -1);
        int cycleNode = -1;
        
        for (int i = 0; i < n; i++) {
            cycleNode = -1;
            for (auto& [u, v, w] : edges) {
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    parent[v] = u;
                    cycleNode = v;
                }
            }
        }
        
        if (cycleNode == -1) return {};
        
        // Find a node in the cycle
        for (int i = 0; i < n; i++) {
            cycleNode = parent[cycleNode];
        }
        
        // Extract cycle
        vector<int> cycle;
        int curr = cycleNode;
        do {
            cycle.push_back(curr);
            curr = parent[curr];
        } while (curr != cycleNode);
        cycle.push_back(cycleNode);
        
        reverse(cycle.begin(), cycle.end());
        return cycle;
    }
    
    // ==================== SPFA Detection ====================
    bool hasNegativeCycleSPFA(int src = 0) {
        vector<long long> dist(n, LLONG_MAX);
        vector<int> count(n, 0);
        vector<bool> inQueue(n, false);
        queue<int> q;
        
        dist[src] = 0;
        q.push(src);
        inQueue[src] = true;
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            inQueue[u] = false;
            
            for (auto& [v, w] : adj[u]) {
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    if (!inQueue[v]) {
                        q.push(v);
                        inQueue[v] = true;
                        count[v]++;
                        if (count[v] >= n) return true;
                    }
                }
            }
        }
        return false;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cout << "=== Negative Cycle Detection Demo ===" << endl;
    
    // Graph with negative cycle
    NegativeCycle g1(4);
    g1.addEdge(0, 1, 1);
    g1.addEdge(1, 2, -1);
    g1.addEdge(2, 3, -1);
    g1.addEdge(3, 1, -1);
    
    cout << "Has negative cycle (BF): " << (g1.hasNegativeCycleBF() ? "Yes" : "No") << endl;
    cout << "Has negative cycle (SPFA): " << (g1.hasNegativeCycleSPFA() ? "Yes" : "No") << endl;
    
    auto cycle = g1.findNegativeCycle();
    cout << "Negative cycle: ";
    for (int v : cycle) cout << v << " ";
    cout << endl;
    
    // Graph without negative cycle
    cout << "\nGraph without negative cycle:" << endl;
    NegativeCycle g2(3);
    g2.addEdge(0, 1, -1);
    g2.addEdge(1, 2, 2);
    g2.addEdge(0, 2, 3);
    
    cout << "Has negative cycle: " << (g2.hasNegativeCycleBF() ? "Yes" : "No") << endl;
    
    return 0;
}









