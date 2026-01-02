/*
    Tree Diameter and Related Problems
    - Diameter: longest path in tree
    - Tree Center
    - Time: O(n)
*/

#include <bits/stdc++.h>
using namespace std;

class Tree {
public:
    int n;
    vector<vector<pair<int, int>>> adj; // {neighbor, weight}
    
    Tree(int n) : n(n), adj(n) {}
    
    void addEdge(int u, int v, int w = 1) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    
    // ==================== BFS to find farthest node ====================
    pair<int, int> bfsFarthest(int start) {
        vector<int> dist(n, -1);
        queue<int> q;
        q.push(start);
        dist[start] = 0;
        
        int farthest = start, maxDist = 0;
        
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            
            for (auto& [neighbor, w] : adj[node]) {
                if (dist[neighbor] == -1) {
                    dist[neighbor] = dist[node] + w;
                    q.push(neighbor);
                    if (dist[neighbor] > maxDist) {
                        maxDist = dist[neighbor];
                        farthest = neighbor;
                    }
                }
            }
        }
        
        return {farthest, maxDist};
    }
    
    // ==================== Tree Diameter (2 BFS) ====================
    int diameter() {
        auto [node1, _] = bfsFarthest(0);
        auto [node2, diam] = bfsFarthest(node1);
        return diam;
    }
    
    // ==================== Diameter with Endpoints ====================
    tuple<int, int, int> diameterWithEndpoints() {
        auto [node1, _] = bfsFarthest(0);
        auto [node2, diam] = bfsFarthest(node1);
        return {diam, node1, node2};
    }
    
    // ==================== Tree Diameter (DFS) ====================
    int diameterDFS() {
        int maxDiam = 0;
        dfs(0, -1, maxDiam);
        return maxDiam;
    }
    
    int dfs(int node, int parent, int& maxDiam) {
        int max1 = 0, max2 = 0;
        
        for (auto& [child, w] : adj[node]) {
            if (child != parent) {
                int childDist = dfs(child, node, maxDiam) + w;
                if (childDist > max1) {
                    max2 = max1;
                    max1 = childDist;
                } else if (childDist > max2) {
                    max2 = childDist;
                }
            }
        }
        
        maxDiam = max(maxDiam, max1 + max2);
        return max1;
    }
    
    // ==================== Tree Center ====================
    vector<int> findCenter() {
        if (n == 1) return {0};
        
        vector<int> degree(n), dist(n, 0);
        queue<int> leaves;
        
        for (int i = 0; i < n; i++) {
            degree[i] = adj[i].size();
            if (degree[i] == 1) leaves.push(i);
        }
        
        int remaining = n;
        while (remaining > 2) {
            int leafCount = leaves.size();
            remaining -= leafCount;
            
            for (int i = 0; i < leafCount; i++) {
                int leaf = leaves.front();
                leaves.pop();
                
                for (auto& [neighbor, w] : adj[leaf]) {
                    if (--degree[neighbor] == 1) {
                        leaves.push(neighbor);
                    }
                }
            }
        }
        
        vector<int> centers;
        while (!leaves.empty()) {
            centers.push_back(leaves.front());
            leaves.pop();
        }
        return centers;
    }
    
    // ==================== All Distances from Node ====================
    vector<int> allDistances(int start) {
        vector<int> dist(n, -1);
        queue<int> q;
        q.push(start);
        dist[start] = 0;
        
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            
            for (auto& [neighbor, w] : adj[node]) {
                if (dist[neighbor] == -1) {
                    dist[neighbor] = dist[node] + w;
                    q.push(neighbor);
                }
            }
        }
        
        return dist;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cout << "=== Tree Diameter Demo ===" << endl;
    
    Tree t(7);
    t.addEdge(0, 1);
    t.addEdge(0, 2);
    t.addEdge(1, 3);
    t.addEdge(1, 4);
    t.addEdge(2, 5);
    t.addEdge(5, 6);
    
    cout << "Diameter (2 BFS): " << t.diameter() << endl;
    cout << "Diameter (DFS): " << t.diameterDFS() << endl;
    
    auto [diam, ep1, ep2] = t.diameterWithEndpoints();
    cout << "Diameter endpoints: " << ep1 << " and " << ep2 << endl;
    
    vector<int> centers = t.findCenter();
    cout << "Tree center(s): ";
    for (int c : centers) cout << c << " ";
    cout << endl;
    
    cout << "\nDistances from node 0: ";
    auto dist = t.allDistances(0);
    for (int i = 0; i < 7; i++) cout << dist[i] << " ";
    cout << endl;
    
    return 0;
}









