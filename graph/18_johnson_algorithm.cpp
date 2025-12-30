/*
    Johnson's Algorithm
    - All pairs shortest path
    - Works with negative weights (no negative cycles)
    - Combines Bellman-Ford and Dijkstra
    - Time: O(V * E + V² log V)
*/

#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;
typedef pair<long long, int> pli;

class Johnson {
public:
    int V;
    vector<tuple<int, int, long long>> edges; // {u, v, weight}
    vector<vector<pair<int, long long>>> adj;
    
    Johnson(int v) : V(v), adj(v) {}
    
    void addEdge(int u, int v, long long w) {
        edges.push_back({u, v, w});
        adj[u].push_back({v, w});
    }
    
    // ==================== Bellman-Ford for reweighting ====================
    pair<vector<long long>, bool> bellmanFord(int src, int n, 
                                               vector<tuple<int, int, long long>>& edges) {
        vector<long long> dist(n, INF);
        dist[src] = 0;
        
        for (int i = 0; i < n - 1; i++) {
            for (auto& [u, v, w] : edges) {
                if (dist[u] != INF && dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                }
            }
        }
        
        // Check for negative cycle
        for (auto& [u, v, w] : edges) {
            if (dist[u] != INF && dist[u] + w < dist[v]) {
                return {dist, true};
            }
        }
        
        return {dist, false};
    }
    
    // ==================== Dijkstra ====================
    vector<long long> dijkstra(int src, vector<vector<pair<int, long long>>>& adjList) {
        int n = adjList.size();
        vector<long long> dist(n, INF);
        priority_queue<pli, vector<pli>, greater<pli>> pq;
        
        dist[src] = 0;
        pq.push({0, src});
        
        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            
            if (d > dist[u]) continue;
            
            for (auto& [v, w] : adjList[u]) {
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    pq.push({dist[v], v});
                }
            }
        }
        
        return dist;
    }
    
    // ==================== Johnson's Algorithm ====================
    pair<vector<vector<long long>>, bool> allPairsShortestPath() {
        // Add new vertex connected to all vertices with 0 weight
        int newV = V;
        vector<tuple<int, int, long long>> newEdges = edges;
        for (int i = 0; i < V; i++) {
            newEdges.push_back({newV, i, 0});
        }
        
        // Run Bellman-Ford from new vertex
        auto [h, hasNegCycle] = bellmanFord(newV, V + 1, newEdges);
        
        if (hasNegCycle) {
            return {{}, true};
        }
        
        // Reweight edges
        vector<vector<pair<int, long long>>> reweightedAdj(V);
        for (auto& [u, v, w] : edges) {
            reweightedAdj[u].push_back({v, w + h[u] - h[v]});
        }
        
        // Run Dijkstra from each vertex
        vector<vector<long long>> dist(V);
        for (int i = 0; i < V; i++) {
            dist[i] = dijkstra(i, reweightedAdj);
            
            // Convert back to original weights
            for (int j = 0; j < V; j++) {
                if (dist[i][j] != INF) {
                    dist[i][j] = dist[i][j] - h[i] + h[j];
                }
            }
        }
        
        return {dist, false};
    }
    
    // ==================== Print Distance Matrix ====================
    void printDistances(vector<vector<long long>>& dist) {
        cout << "Distance Matrix:" << endl;
        cout << "    ";
        for (int i = 0; i < V; i++) cout << setw(6) << i;
        cout << endl;
        
        for (int i = 0; i < V; i++) {
            cout << setw(3) << i << " ";
            for (int j = 0; j < V; j++) {
                if (dist[i][j] == INF) {
                    cout << setw(6) << "INF";
                } else {
                    cout << setw(6) << dist[i][j];
                }
            }
            cout << endl;
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cout << "=== Johnson's Algorithm Demo ===" << endl;
    
    // Graph with negative edges but no negative cycle
    Johnson g1(4);
    g1.addEdge(0, 1, -5);
    g1.addEdge(0, 2, 2);
    g1.addEdge(1, 2, 4);
    g1.addEdge(1, 3, 3);
    g1.addEdge(2, 3, 1);
    g1.addEdge(3, 0, 6);
    
    cout << "Graph with negative edges:" << endl;
    auto [dist1, hasNeg1] = g1.allPairsShortestPath();
    
    if (hasNeg1) {
        cout << "Negative cycle detected!" << endl;
    } else {
        g1.printDistances(dist1);
    }
    
    // Graph with negative cycle
    cout << "\n=== Graph with Negative Cycle ===" << endl;
    Johnson g2(3);
    g2.addEdge(0, 1, 1);
    g2.addEdge(1, 2, -3);
    g2.addEdge(2, 0, 1);
    
    auto [dist2, hasNeg2] = g2.allPairsShortestPath();
    
    if (hasNeg2) {
        cout << "Negative cycle detected!" << endl;
    } else {
        g2.printDistances(dist2);
    }
    
    return 0;
}

