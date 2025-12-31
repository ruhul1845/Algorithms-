/*
    Bellman-Ford Algorithm
    - Single source shortest path
    - Works with negative weights
    - Detects negative cycles
    - Time: O(V * E), Space: O(V)
*/

#include <bits/stdc++.h>
using namespace std;

class Graph {
public:
    int V;
    vector<tuple<int, int, int>> edges; // {u, v, weight}
    vector<vector<pair<int, int>>> adj;
    
    Graph(int v) : V(v), adj(v) {}
    
    void addEdge(int u, int v, int w, bool directed = true) {
        edges.push_back({u, v, w});
        adj[u].push_back({v, w});
        if (!directed) {
            edges.push_back({v, u, w});
            adj[v].push_back({u, w});
        }
    }
    
    // ==================== Basic Bellman-Ford ====================
    pair<vector<long long>, bool> bellmanFord(int src) {
        vector<long long> dist(V, LLONG_MAX);
        dist[src] = 0;
        
        // Relax all edges V-1 times
        for (int i = 0; i < V - 1; i++) {
            for (auto& [u, v, w] : edges) {
                if (dist[u] != LLONG_MAX && dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                }
            }
        }
        
        // Check for negative cycle
        bool hasNegativeCycle = false;
        for (auto& [u, v, w] : edges) {
            if (dist[u] != LLONG_MAX && dist[u] + w < dist[v]) {
                hasNegativeCycle = true;
                break;
            }
        }
        
        return {dist, hasNegativeCycle};
    }
    
    // ==================== Bellman-Ford with Path ====================
    tuple<vector<long long>, vector<int>, bool> bellmanFordWithPath(int src) {
        vector<long long> dist(V, LLONG_MAX);
        vector<int> parent(V, -1);
        dist[src] = 0;
        
        for (int i = 0; i < V - 1; i++) {
            for (auto& [u, v, w] : edges) {
                if (dist[u] != LLONG_MAX && dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    parent[v] = u;
                }
            }
        }
        
        bool hasNegativeCycle = false;
        for (auto& [u, v, w] : edges) {
            if (dist[u] != LLONG_MAX && dist[u] + w < dist[v]) {
                hasNegativeCycle = true;
                break;
            }
        }
        
        return {dist, parent, hasNegativeCycle};
    }
    
    vector<int> getPath(int src, int dest, vector<int>& parent) {
        vector<int> path;
        if (parent[dest] == -1 && dest != src) return path;
        
        for (int curr = dest; curr != -1; curr = parent[curr]) {
            path.push_back(curr);
        }
        reverse(path.begin(), path.end());
        return path;
    }
    
    // ==================== Find Negative Cycle ====================
    vector<int> findNegativeCycle() {
        vector<long long> dist(V, 0); // Start with 0 to find any cycle
        vector<int> parent(V, -1);
        int cycleNode = -1;
        
        for (int i = 0; i < V; i++) {
            cycleNode = -1;
            for (auto& [u, v, w] : edges) {
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    parent[v] = u;
                    cycleNode = v;
                }
            }
        }
        
        vector<int> cycle;
        if (cycleNode == -1) return cycle;
        
        // Find a node in the cycle
        for (int i = 0; i < V; i++) {
            cycleNode = parent[cycleNode];
        }
        
        // Extract the cycle
        int curr = cycleNode;
        do {
            cycle.push_back(curr);
            curr = parent[curr];
        } while (curr != cycleNode);
        cycle.push_back(cycleNode);
        
        reverse(cycle.begin(), cycle.end());
        return cycle;
    }
    
    // ==================== SPFA (Shortest Path Faster Algorithm) ====================
    pair<vector<long long>, bool> spfa(int src) {
        vector<long long> dist(V, LLONG_MAX);
        vector<bool> inQueue(V, false);
        vector<int> count(V, 0);
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
                        
                        if (count[v] >= V) {
                            return {dist, true}; // Negative cycle
                        }
                    }
                }
            }
        }
        
        return {dist, false};
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cout << "=== Bellman-Ford Algorithm Demo ===" << endl;
    
    // Graph without negative cycle
    Graph g1(5);
    g1.addEdge(0, 1, -1);
    g1.addEdge(0, 2, 4);
    g1.addEdge(1, 2, 3);
    g1.addEdge(1, 3, 2);
    g1.addEdge(1, 4, 2);
    g1.addEdge(3, 2, 5);
    g1.addEdge(3, 1, 1);
    g1.addEdge(4, 3, -3);
    
    cout << "Graph without negative cycle:" << endl;
    auto [dist1, hasNeg1] = g1.bellmanFord(0);
    
    if (hasNeg1) {
        cout << "Negative cycle detected!" << endl;
    } else {
        cout << "Shortest distances from node 0:" << endl;
        for (int i = 0; i < 5; i++) {
            cout << "To " << i << ": " << dist1[i] << endl;
        }
    }
    
    // With path
    cout << "\nShortest path from 0 to 4:" << endl;
    auto [dist2, parent, hasNeg2] = g1.bellmanFordWithPath(0);
    vector<int> path = g1.getPath(0, 4, parent);
    cout << "Path: ";
    for (int node : path) cout << node << " ";
    cout << endl;
    
    // Graph with negative cycle
    cout << "\n=== Graph with Negative Cycle ===" << endl;
    Graph g2(4);
    g2.addEdge(0, 1, 1);
    g2.addEdge(1, 2, -1);
    g2.addEdge(2, 3, -1);
    g2.addEdge(3, 1, -1);
    
    auto [dist3, hasNeg3] = g2.bellmanFord(0);
    if (hasNeg3) {
        cout << "Negative cycle detected!" << endl;
        vector<int> cycle = g2.findNegativeCycle();
        cout << "Cycle: ";
        for (int node : cycle) cout << node << " ";
        cout << endl;
    }
    
    // SPFA
    cout << "\n=== SPFA (without negative cycle) ===" << endl;
    auto [dist4, hasNeg4] = g1.spfa(0);
    cout << "Shortest distances from node 0:" << endl;
    for (int i = 0; i < 5; i++) {
        cout << "To " << i << ": " << dist4[i] << endl;
    }
    
    return 0;
}



