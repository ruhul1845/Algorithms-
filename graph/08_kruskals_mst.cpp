/*
    Kruskal's Algorithm - Minimum Spanning Tree
    - Greedy algorithm using Union-Find
    - Sorts edges by weight
    - Time: O(E log E) or O(E log V)
    - Space: O(V + E)
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== Union-Find (Disjoint Set Union) ====================
class DSU {
public:
    vector<int> parent, rank_;
    
    DSU(int n) : parent(n), rank_(n, 0) {
        iota(parent.begin(), parent.end(), 0);
    }
    
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]); // Path compression
        }
        return parent[x];
    }
    
    bool unite(int x, int y) {
        int px = find(x), py = find(y);
        if (px == py) return false;
        
        // Union by rank
        if (rank_[px] < rank_[py]) swap(px, py);
        parent[py] = px;
        if (rank_[px] == rank_[py]) rank_[px]++;
        
        return true;
    }
    
    bool connected(int x, int y) {
        return find(x) == find(y);
    }
};

class Graph {
public:
    int V;
    vector<tuple<int, int, int>> edges; // {weight, u, v}
    
    Graph(int v) : V(v) {}
    
    void addEdge(int u, int v, int w) {
        edges.push_back({w, u, v});
    }
    
    // ==================== Basic Kruskal's ====================
    long long kruskalMST() {
        sort(edges.begin(), edges.end());
        DSU dsu(V);
        
        long long totalWeight = 0;
        int edgesAdded = 0;
        
        for (auto& [w, u, v] : edges) {
            if (dsu.unite(u, v)) {
                totalWeight += w;
                edgesAdded++;
                if (edgesAdded == V - 1) break;
            }
        }
        
        return (edgesAdded == V - 1) ? totalWeight : -1;
    }
    
    // ==================== Kruskal's with MST Edges ====================
    pair<long long, vector<tuple<int, int, int>>> kruskalMSTWithEdges() {
        sort(edges.begin(), edges.end());
        DSU dsu(V);
        
        long long totalWeight = 0;
        vector<tuple<int, int, int>> mstEdges;
        
        for (auto& [w, u, v] : edges) {
            if (dsu.unite(u, v)) {
                totalWeight += w;
                mstEdges.push_back({u, v, w});
                if (mstEdges.size() == V - 1) break;
            }
        }
        
        return {totalWeight, mstEdges};
    }
    
    // ==================== Second Best MST ====================
    long long secondBestMST() {
        sort(edges.begin(), edges.end());
        DSU dsu(V);
        
        vector<tuple<int, int, int>> mstEdges;
        vector<bool> inMST(edges.size(), false);
        
        // Find MST
        for (int i = 0; i < edges.size(); i++) {
            auto& [w, u, v] = edges[i];
            if (dsu.unite(u, v)) {
                mstEdges.push_back(edges[i]);
                inMST[i] = true;
                if (mstEdges.size() == V - 1) break;
            }
        }
        
        long long mstWeight = 0;
        for (auto& [w, u, v] : mstEdges) mstWeight += w;
        
        // Try removing each MST edge and find next best
        long long secondBest = LLONG_MAX;
        
        for (int skip = 0; skip < edges.size(); skip++) {
            if (!inMST[skip]) continue;
            
            DSU dsu2(V);
            long long weight = 0;
            int count = 0;
            
            for (int i = 0; i < edges.size(); i++) {
                if (i == skip) continue;
                auto& [w, u, v] = edges[i];
                if (dsu2.unite(u, v)) {
                    weight += w;
                    count++;
                    if (count == V - 1) break;
                }
            }
            
            if (count == V - 1) {
                secondBest = min(secondBest, weight);
            }
        }
        
        return secondBest;
    }
};

// ==================== Critical and Pseudo-Critical Edges ====================
class CriticalEdges {
public:
    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges) {
        int m = edges.size();
        
        // Add original index
        for (int i = 0; i < m; i++) {
            edges[i].push_back(i);
        }
        
        sort(edges.begin(), edges.end(), [](auto& a, auto& b) {
            return a[2] < b[2];
        });
        
        int mstWeight = getMSTWeight(n, edges, -1, -1);
        
        vector<int> critical, pseudoCritical;
        
        for (int i = 0; i < m; i++) {
            // Check if critical (removing increases MST)
            if (getMSTWeight(n, edges, i, -1) > mstWeight) {
                critical.push_back(edges[i][3]);
            }
            // Check if pseudo-critical (including doesn't increase MST)
            else if (getMSTWeight(n, edges, -1, i) == mstWeight) {
                pseudoCritical.push_back(edges[i][3]);
            }
        }
        
        return {critical, pseudoCritical};
    }
    
private:
    int getMSTWeight(int n, vector<vector<int>>& edges, int exclude, int include) {
        DSU dsu(n);
        int weight = 0;
        int count = 0;
        
        if (include != -1) {
            dsu.unite(edges[include][0], edges[include][1]);
            weight += edges[include][2];
            count++;
        }
        
        for (int i = 0; i < edges.size(); i++) {
            if (i == exclude) continue;
            if (dsu.unite(edges[i][0], edges[i][1])) {
                weight += edges[i][2];
                count++;
            }
        }
        
        return (count == n - 1) ? weight : INT_MAX;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cout << "=== Kruskal's MST Algorithm Demo ===" << endl;
    
    Graph g(5);
    g.addEdge(0, 1, 2);
    g.addEdge(0, 3, 6);
    g.addEdge(1, 2, 3);
    g.addEdge(1, 3, 8);
    g.addEdge(1, 4, 5);
    g.addEdge(2, 4, 7);
    g.addEdge(3, 4, 9);
    
    // Basic Kruskal's
    cout << "MST Weight: " << g.kruskalMST() << endl;
    
    // Kruskal's with edges
    auto [weight, mstEdges] = g.kruskalMSTWithEdges();
    cout << "\nMST Edges:" << endl;
    for (auto& [u, v, w] : mstEdges) {
        cout << u << " - " << v << " (weight: " << w << ")" << endl;
    }
    
    // Second best MST
    cout << "\nSecond Best MST Weight: " << g.secondBestMST() << endl;
    
    // Critical edges
    cout << "\n=== Critical and Pseudo-Critical Edges ===" << endl;
    vector<vector<int>> edges2 = {{0,1,1},{1,2,1},{2,3,2},{0,3,2},{0,2,2},{3,4,1}};
    CriticalEdges ce;
    auto result = ce.findCriticalAndPseudoCriticalEdges(5, edges2);
    
    cout << "Critical edges: ";
    for (int e : result[0]) cout << e << " ";
    cout << "\nPseudo-critical edges: ";
    for (int e : result[1]) cout << e << " ";
    cout << endl;
    
    return 0;
}


















