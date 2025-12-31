/*
    Network Flow - Ford-Fulkerson Algorithm
    - Maximum flow in a flow network
    - Uses BFS (Edmonds-Karp) for finding augmenting paths
    - Time: O(V * E²)
*/

#include <bits/stdc++.h>
using namespace std;

class MaxFlow {
public:
    int V;
    vector<vector<int>> capacity;
    vector<vector<int>> adj;
    
    MaxFlow(int v) : V(v), capacity(v, vector<int>(v, 0)), adj(v) {}
    
    void addEdge(int u, int v, int cap) {
        capacity[u][v] += cap;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    // ==================== BFS to find augmenting path ====================
    int bfs(int source, int sink, vector<int>& parent) {
        fill(parent.begin(), parent.end(), -1);
        parent[source] = source;
        
        queue<pair<int, int>> q;
        q.push({source, INT_MAX});
        
        while (!q.empty()) {
            auto [node, flow] = q.front();
            q.pop();
            
            for (int next : adj[node]) {
                if (parent[next] == -1 && capacity[node][next] > 0) {
                    parent[next] = node;
                    int newFlow = min(flow, capacity[node][next]);
                    if (next == sink) return newFlow;
                    q.push({next, newFlow});
                }
            }
        }
        
        return 0;
    }
    
    // ==================== Ford-Fulkerson (Edmonds-Karp) ====================
    int maxflow(int source, int sink) {
        int flow = 0;
        vector<int> parent(V);
        int newFlow;
        
        while ((newFlow = bfs(source, sink, parent)) > 0) {
            flow += newFlow;
            int curr = sink;
            
            while (curr != source) {
                int prev = parent[curr];
                capacity[prev][curr] -= newFlow;
                capacity[curr][prev] += newFlow;
                curr = prev;
            }
        }
        
        return flow;
    }
    
    // ==================== Get Min Cut ====================
    vector<pair<int, int>> getMinCut(int source, int sink) {
        maxflow(source, sink);
        
        // BFS from source to find reachable vertices
        vector<bool> reachable(V, false);
        queue<int> q;
        q.push(source);
        reachable[source] = true;
        
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            
            for (int next : adj[node]) {
                if (!reachable[next] && capacity[node][next] > 0) {
                    reachable[next] = true;
                    q.push(next);
                }
            }
        }
        
        // Find cut edges
        vector<pair<int, int>> cutEdges;
        for (int u = 0; u < V; u++) {
            if (reachable[u]) {
                for (int v : adj[u]) {
                    if (!reachable[v]) {
                        cutEdges.push_back({u, v});
                    }
                }
            }
        }
        
        return cutEdges;
    }
};

// ==================== Bipartite Matching using Max Flow ====================
class BipartiteMatching {
public:
    int maxMatching(int n, int m, vector<pair<int, int>>& edges) {
        // n: left vertices, m: right vertices
        // Source = 0, Left = 1 to n, Right = n+1 to n+m, Sink = n+m+1
        int source = 0, sink = n + m + 1;
        MaxFlow mf(n + m + 2);
        
        // Source to left vertices
        for (int i = 1; i <= n; i++) {
            mf.addEdge(source, i, 1);
        }
        
        // Right vertices to sink
        for (int i = 1; i <= m; i++) {
            mf.addEdge(n + i, sink, 1);
        }
        
        // Edges between left and right
        for (auto& [u, v] : edges) {
            mf.addEdge(u, n + v, 1);
        }
        
        return mf.maxflow(source, sink);
    }
};

// ==================== Maximum Students Taking Exam ====================
class MaxStudents {
public:
    int maxStudents(vector<vector<char>>& seats) {
        int m = seats.size(), n = seats[0].size();
        int total = 0;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (seats[i][j] == '.') total++;
            }
        }
        
        // Create bipartite graph: odd columns vs even columns
        int source = m * n, sink = m * n + 1;
        MaxFlow mf(m * n + 2);
        
        auto getId = [&](int i, int j) { return i * n + j; };
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (seats[i][j] == '#') continue;
                
                if (j % 2 == 0) { // Even column (left partition)
                    mf.addEdge(source, getId(i, j), 1);
                    
                    // Check adjacent seats in odd columns
                    int dirs[][2] = {{-1, 1}, {0, 1}, {1, 1}, {-1, -1}, {0, -1}, {1, -1}};
                    for (auto& [di, dj] : dirs) {
                        int ni = i + di, nj = j + dj;
                        if (ni >= 0 && ni < m && nj >= 0 && nj < n && 
                            seats[ni][nj] == '.' && nj % 2 == 1) {
                            mf.addEdge(getId(i, j), getId(ni, nj), 1);
                        }
                    }
                } else { // Odd column (right partition)
                    mf.addEdge(getId(i, j), sink, 1);
                }
            }
        }
        
        return total - mf.maxflow(source, sink);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cout << "=== Network Flow (Ford-Fulkerson) Demo ===" << endl;
    
    MaxFlow mf(6);
    mf.addEdge(0, 1, 16);
    mf.addEdge(0, 2, 13);
    mf.addEdge(1, 2, 10);
    mf.addEdge(1, 3, 12);
    mf.addEdge(2, 1, 4);
    mf.addEdge(2, 4, 14);
    mf.addEdge(3, 2, 9);
    mf.addEdge(3, 5, 20);
    mf.addEdge(4, 3, 7);
    mf.addEdge(4, 5, 4);
    
    cout << "Maximum Flow: " << mf.maxflow(0, 5) << endl;
    
    // Bipartite Matching
    cout << "\n=== Bipartite Matching ===" << endl;
    vector<pair<int, int>> edges = {{1, 1}, {1, 2}, {2, 1}, {3, 2}, {3, 3}};
    BipartiteMatching bm;
    cout << "Maximum Matching: " << bm.maxMatching(3, 3, edges) << endl;
    
    return 0;
}



