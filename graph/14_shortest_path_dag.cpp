/*
    Shortest Path in DAG
    - Using topological sort
    - Works with negative weights
    - Time: O(V + E)
*/

#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;

class DAG {
public:
    int V;
    vector<vector<pair<int, int>>> adj; // {neighbor, weight}
    
    DAG(int v) : V(v), adj(v) {}
    
    void addEdge(int u, int v, int w) {
        adj[u].push_back({v, w});
    }
    
    // ==================== Topological Sort ====================
    vector<int> topologicalSort() {
        vector<int> inDegree(V, 0);
        for (int u = 0; u < V; u++) {
            for (auto& [v, w] : adj[u]) {
                inDegree[v]++;
            }
        }
        
        queue<int> q;
        for (int i = 0; i < V; i++) {
            if (inDegree[i] == 0) q.push(i);
        }
        
        vector<int> order;
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            order.push_back(node);
            
            for (auto& [neighbor, w] : adj[node]) {
                if (--inDegree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }
        
        return order;
    }
    
    // ==================== Shortest Path ====================
    vector<long long> shortestPath(int src) {
        vector<long long> dist(V, INF);
        vector<int> order = topologicalSort();
        
        dist[src] = 0;
        
        for (int node : order) {
            if (dist[node] != INF) {
                for (auto& [neighbor, w] : adj[node]) {
                    dist[neighbor] = min(dist[neighbor], dist[node] + w);
                }
            }
        }
        
        return dist;
    }
    
    // ==================== Shortest Path with Path Reconstruction ====================
    pair<vector<long long>, vector<int>> shortestPathWithPath(int src) {
        vector<long long> dist(V, INF);
        vector<int> parent(V, -1);
        vector<int> order = topologicalSort();
        
        dist[src] = 0;
        
        for (int node : order) {
            if (dist[node] != INF) {
                for (auto& [neighbor, w] : adj[node]) {
                    if (dist[node] + w < dist[neighbor]) {
                        dist[neighbor] = dist[node] + w;
                        parent[neighbor] = node;
                    }
                }
            }
        }
        
        return {dist, parent};
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
    
    // ==================== Longest Path ====================
    vector<long long> longestPath(int src) {
        vector<long long> dist(V, LLONG_MIN);
        vector<int> order = topologicalSort();
        
        dist[src] = 0;
        
        for (int node : order) {
            if (dist[node] != LLONG_MIN) {
                for (auto& [neighbor, w] : adj[node]) {
                    dist[neighbor] = max(dist[neighbor], dist[node] + w);
                }
            }
        }
        
        return dist;
    }
    
    // ==================== Count Paths ====================
    vector<long long> countPaths(int src) {
        vector<long long> paths(V, 0);
        vector<int> order = topologicalSort();
        
        paths[src] = 1;
        
        for (int node : order) {
            for (auto& [neighbor, w] : adj[node]) {
                paths[neighbor] += paths[node];
            }
        }
        
        return paths;
    }
    
    // ==================== Shortest Paths Count ====================
    pair<vector<long long>, vector<long long>> shortestPathsCount(int src) {
        vector<long long> dist(V, INF);
        vector<long long> count(V, 0);
        vector<int> order = topologicalSort();
        
        dist[src] = 0;
        count[src] = 1;
        
        for (int node : order) {
            if (dist[node] != INF) {
                for (auto& [neighbor, w] : adj[node]) {
                    if (dist[node] + w < dist[neighbor]) {
                        dist[neighbor] = dist[node] + w;
                        count[neighbor] = count[node];
                    } else if (dist[node] + w == dist[neighbor]) {
                        count[neighbor] += count[node];
                    }
                }
            }
        }
        
        return {dist, count};
    }
};

// ==================== Longest Increasing Path in Matrix ====================
class LongestIncreasingPath {
public:
    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};
    
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        vector<vector<int>> dp(m, vector<int>(n, 0));
        
        int maxLen = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                maxLen = max(maxLen, dfs(matrix, dp, i, j));
            }
        }
        
        return maxLen;
    }
    
    int dfs(vector<vector<int>>& matrix, vector<vector<int>>& dp, int r, int c) {
        if (dp[r][c] != 0) return dp[r][c];
        
        int m = matrix.size(), n = matrix[0].size();
        dp[r][c] = 1;
        
        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d], nc = c + dc[d];
            if (nr >= 0 && nr < m && nc >= 0 && nc < n && 
                matrix[nr][nc] > matrix[r][c]) {
                dp[r][c] = max(dp[r][c], 1 + dfs(matrix, dp, nr, nc));
            }
        }
        
        return dp[r][c];
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cout << "=== Shortest Path in DAG Demo ===" << endl;
    
    DAG g(6);
    g.addEdge(0, 1, 2);
    g.addEdge(0, 4, 1);
    g.addEdge(1, 2, 3);
    g.addEdge(2, 3, 6);
    g.addEdge(4, 2, 2);
    g.addEdge(4, 5, 4);
    g.addEdge(5, 3, 1);
    
    // Shortest path
    cout << "Shortest distances from node 0:" << endl;
    auto dist = g.shortestPath(0);
    for (int i = 0; i < 6; i++) {
        cout << "To " << i << ": " << (dist[i] == INF ? -1 : dist[i]) << endl;
    }
    
    // Shortest path with reconstruction
    cout << "\nShortest path from 0 to 3:" << endl;
    auto [dist2, parent] = g.shortestPathWithPath(0);
    vector<int> path = g.getPath(0, 3, parent);
    cout << "Path: ";
    for (int node : path) cout << node << " ";
    cout << "\nDistance: " << dist2[3] << endl;
    
    // Longest path
    cout << "\nLongest distances from node 0:" << endl;
    auto longest = g.longestPath(0);
    for (int i = 0; i < 6; i++) {
        cout << "To " << i << ": " << (longest[i] == LLONG_MIN ? -1 : longest[i]) << endl;
    }
    
    // Count paths
    cout << "\nNumber of paths from node 0:" << endl;
    auto paths = g.countPaths(0);
    for (int i = 0; i < 6; i++) {
        cout << "To " << i << ": " << paths[i] << endl;
    }
    
    // Longest increasing path in matrix
    cout << "\n=== Longest Increasing Path in Matrix ===" << endl;
    vector<vector<int>> matrix = {
        {9, 9, 4},
        {6, 6, 8},
        {2, 1, 1}
    };
    LongestIncreasingPath lip;
    cout << "Longest increasing path: " << lip.longestIncreasingPath(matrix) << endl;
    
    return 0;
}







