/*
    Prim's Algorithm - Minimum Spanning Tree
    - Greedy algorithm
    - Grows MST from a starting vertex
    - Time: O((V + E) log V) with priority queue
    - Space: O(V + E)
*/

#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;

class Graph {
public:
    int V;
    vector<vector<pii>> adj; // {neighbor, weight}
    
    Graph(int v) : V(v), adj(v) {}
    
    void addEdge(int u, int v, int w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    
    // ==================== Basic Prim's ====================
    long long primMST() {
        vector<bool> inMST(V, false);
        priority_queue<pii, vector<pii>, greater<pii>> pq;
        
        long long totalWeight = 0;
        int edgesAdded = 0;
        
        pq.push({0, 0}); // {weight, vertex}
        
        while (!pq.empty() && edgesAdded < V) {
            auto [weight, u] = pq.top();
            pq.pop();
            
            if (inMST[u]) continue;
            
            inMST[u] = true;
            totalWeight += weight;
            edgesAdded++;
            
            for (auto& [v, w] : adj[u]) {
                if (!inMST[v]) {
                    pq.push({w, v});
                }
            }
        }
        
        return (edgesAdded == V) ? totalWeight : -1; // -1 if not connected
    }
    
    // ==================== Prim's with MST Edges ====================
    pair<long long, vector<pair<int, int>>> primMSTWithEdges() {
        vector<bool> inMST(V, false);
        vector<int> parent(V, -1);
        vector<int> key(V, INT_MAX);
        priority_queue<pii, vector<pii>, greater<pii>> pq;
        
        key[0] = 0;
        pq.push({0, 0});
        
        while (!pq.empty()) {
            auto [w, u] = pq.top();
            pq.pop();
            
            if (inMST[u]) continue;
            inMST[u] = true;
            
            for (auto& [v, weight] : adj[u]) {
                if (!inMST[v] && weight < key[v]) {
                    key[v] = weight;
                    parent[v] = u;
                    pq.push({weight, v});
                }
            }
        }
        
        long long totalWeight = 0;
        vector<pair<int, int>> mstEdges;
        
        for (int i = 1; i < V; i++) {
            if (parent[i] != -1) {
                mstEdges.push_back({parent[i], i});
                totalWeight += key[i];
            }
        }
        
        return {totalWeight, mstEdges};
    }
    
    // ==================== Dense Graph Prim's (O(V²)) ====================
    long long primDense() {
        vector<int> key(V, INT_MAX);
        vector<bool> inMST(V, false);
        
        key[0] = 0;
        long long totalWeight = 0;
        
        for (int count = 0; count < V; count++) {
            // Find minimum key vertex not in MST
            int u = -1;
            for (int v = 0; v < V; v++) {
                if (!inMST[v] && (u == -1 || key[v] < key[u])) {
                    u = v;
                }
            }
            
            if (key[u] == INT_MAX) return -1; // Not connected
            
            inMST[u] = true;
            totalWeight += key[u];
            
            // Update keys of adjacent vertices
            for (auto& [v, w] : adj[u]) {
                if (!inMST[v] && w < key[v]) {
                    key[v] = w;
                }
            }
        }
        
        return totalWeight;
    }
};

// ==================== Minimum Cost to Connect All Points ====================
class MinCostConnectPoints {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n = points.size();
        vector<bool> inMST(n, false);
        vector<int> minDist(n, INT_MAX);
        priority_queue<pii, vector<pii>, greater<pii>> pq;
        
        minDist[0] = 0;
        pq.push({0, 0});
        int totalCost = 0;
        int edgesAdded = 0;
        
        while (edgesAdded < n) {
            auto [dist, u] = pq.top();
            pq.pop();
            
            if (inMST[u]) continue;
            
            inMST[u] = true;
            totalCost += dist;
            edgesAdded++;
            
            for (int v = 0; v < n; v++) {
                if (!inMST[v]) {
                    int d = abs(points[u][0] - points[v][0]) + 
                            abs(points[u][1] - points[v][1]);
                    if (d < minDist[v]) {
                        minDist[v] = d;
                        pq.push({d, v});
                    }
                }
            }
        }
        
        return totalCost;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cout << "=== Prim's MST Algorithm Demo ===" << endl;
    
    Graph g(5);
    g.addEdge(0, 1, 2);
    g.addEdge(0, 3, 6);
    g.addEdge(1, 2, 3);
    g.addEdge(1, 3, 8);
    g.addEdge(1, 4, 5);
    g.addEdge(2, 4, 7);
    g.addEdge(3, 4, 9);
    
    // Basic Prim's
    cout << "MST Weight (Priority Queue): " << g.primMST() << endl;
    
    // Prim's with edges
    auto [weight, edges] = g.primMSTWithEdges();
    cout << "\nMST Weight: " << weight << endl;
    cout << "MST Edges:" << endl;
    for (auto& [u, v] : edges) {
        cout << u << " - " << v << endl;
    }
    
    // Dense graph Prim's
    cout << "\nMST Weight (O(V²)): " << g.primDense() << endl;
    
    // Min cost to connect points
    cout << "\n=== Min Cost to Connect Points ===" << endl;
    vector<vector<int>> points = {{0,0}, {2,2}, {3,10}, {5,2}, {7,0}};
    MinCostConnectPoints mccp;
    cout << "Minimum cost: " << mccp.minCostConnectPoints(points) << endl;
    
    return 0;
}


















