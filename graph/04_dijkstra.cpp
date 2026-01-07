/*
    Dijkstra's Algorithm - Shortest Path
    - Single source shortest path for non-negative weights
    - Time: O((V + E) log V) with priority queue
    - Space: O(V)
*/

#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;
typedef pair<long long, int> pli;

class Graph {
public:
    int V;
    vector<vector<pii>> adj; // {neighbor, weight}
    
    Graph(int v) : V(v), adj(v) {}
    
    void addEdge(int u, int v, int w, bool directed = false) {
        adj[u].push_back({v, w});
        if (!directed) adj[v].push_back({u, w});
    }
    
    // ==================== Basic Dijkstra ====================
    vector<int> dijkstra(int src) {
        vector<int> dist(V, INT_MAX);
        priority_queue<pii, vector<pii>, greater<pii>> pq;
        
        dist[src] = 0;
        pq.push({0, src});
        
        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            
            if (d > dist[u]) continue; // Skip outdated entries
            
            for (auto& [v, w] : adj[u]) {
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    pq.push({dist[v], v});
                }
            }
        }
        
        return dist;
    }
    
    // ==================== Dijkstra with Path ====================
    pair<vector<int>, vector<int>> dijkstraWithPath(int src) {
        vector<int> dist(V, INT_MAX);
        vector<int> parent(V, -1);
        priority_queue<pii, vector<pii>, greater<pii>> pq;
        
        dist[src] = 0;
        pq.push({0, src});
        
        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            
            if (d > dist[u]) continue;
            
            for (auto& [v, w] : adj[u]) {
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    parent[v] = u;
                    pq.push({dist[v], v});
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
    
    // ==================== Dijkstra with Set ====================
    vector<int> dijkstraSet(int src) {
        vector<int> dist(V, INT_MAX);
        set<pii> st;
        
        dist[src] = 0;
        st.insert({0, src});
        
        while (!st.empty()) {
            auto [d, u] = *st.begin();
            st.erase(st.begin());
            
            for (auto& [v, w] : adj[u]) {
                if (dist[u] + w < dist[v]) {
                    if (dist[v] != INT_MAX) {
                        st.erase({dist[v], v});
                    }
                    dist[v] = dist[u] + w;
                    st.insert({dist[v], v});
                }
            }
        }
        
        return dist;
    }
    
    // ==================== K Shortest Paths ====================
    vector<int> kShortestPaths(int src, int dest, int k) {
        vector<int> results;
        vector<int> count(V, 0);
        priority_queue<pii, vector<pii>, greater<pii>> pq;
        
        pq.push({0, src});
        
        while (!pq.empty() && count[dest] < k) {
            auto [d, u] = pq.top();
            pq.pop();
            
            count[u]++;
            
            if (u == dest) {
                results.push_back(d);
            }
            
            if (count[u] <= k) {
                for (auto& [v, w] : adj[u]) {
                    pq.push({d + w, v});
                }
            }
        }
        
        return results;
    }
};

// ==================== Dijkstra for Grid ====================
class GridDijkstra {
public:
    int rows, cols;
    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};
    
    GridDijkstra(int r, int c) : rows(r), cols(c) {}
    
    int shortestPath(vector<vector<int>>& grid, pair<int,int> src, pair<int,int> dest) {
        vector<vector<int>> dist(rows, vector<int>(cols, INT_MAX));
        priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, greater<>> pq;
        
        dist[src.first][src.second] = grid[src.first][src.second];
        pq.push({dist[src.first][src.second], src.first, src.second});
        
        while (!pq.empty()) {
            auto [d, r, c] = pq.top();
            pq.pop();
            
            if (r == dest.first && c == dest.second) return d;
            if (d > dist[r][c]) continue;
            
            for (int i = 0; i < 4; i++) {
                int nr = r + dr[i];
                int nc = c + dc[i];
                
                if (nr >= 0 && nr < rows && nc >= 0 && nc < cols) {
                    int newDist = dist[r][c] + grid[nr][nc];
                    if (newDist < dist[nr][nc]) {
                        dist[nr][nc] = newDist;
                        pq.push({newDist, nr, nc});
                    }
                }
            }
        }
        
        return dist[dest.first][dest.second];
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cout << "=== Dijkstra's Algorithm Demo ===" << endl;
    
    Graph g(6);
    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 2);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 3, 5);
    g.addEdge(2, 3, 8);
    g.addEdge(2, 4, 10);
    g.addEdge(3, 4, 2);
    g.addEdge(3, 5, 6);
    g.addEdge(4, 5, 3);
    
    // Basic Dijkstra
    cout << "Shortest distances from node 0:" << endl;
    vector<int> dist = g.dijkstra(0);
    for (int i = 0; i < 6; i++) {
        cout << "To " << i << ": " << dist[i] << endl;
    }
    
    // Dijkstra with path
    cout << "\nShortest path from 0 to 5:" << endl;
    auto [distances, parent] = g.dijkstraWithPath(0);
    vector<int> path = g.getPath(0, 5, parent);
    cout << "Path: ";
    for (int node : path) cout << node << " ";
    cout << "\nDistance: " << distances[5] << endl;
    
    // K shortest paths
    cout << "\n3 Shortest paths from 0 to 5:" << endl;
    vector<int> kPaths = g.kShortestPaths(0, 5, 3);
    for (int i = 0; i < kPaths.size(); i++) {
        cout << "Path " << i + 1 << ": " << kPaths[i] << endl;
    }
    
    // Grid Dijkstra
    cout << "\n=== Grid Dijkstra ===" << endl;
    vector<vector<int>> grid = {
        {1, 3, 1, 2},
        {2, 1, 1, 1},
        {5, 2, 1, 1}
    };
    GridDijkstra gdijk(3, 4);
    cout << "Shortest path cost (0,0) to (2,3): " 
         << gdijk.shortestPath(grid, {0,0}, {2,3}) << endl;
    
    return 0;
}


















