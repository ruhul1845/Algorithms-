/*
    Breadth-First Search (BFS)
    - Level order traversal
    - Shortest path in unweighted graph
    - Time: O(V + E), Space: O(V)
*/

#include <bits/stdc++.h>
using namespace std;

class Graph {
public:
    int V;
    vector<vector<int>> adj;
    
    Graph(int v) : V(v), adj(v) {}
    
    void addEdge(int u, int v, bool directed = false) {
        adj[u].push_back(v);
        if (!directed) adj[v].push_back(u);
    }
    
    // ==================== Basic BFS ====================
    void bfs(int start) {
        vector<bool> visited(V, false);
        queue<int> q;
        
        visited[start] = true;
        q.push(start);
        
        cout << "BFS traversal from " << start << ": ";
        
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            cout << node << " ";
            
            for (int neighbor : adj[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        cout << endl;
    }
    
    // ==================== BFS with Level ====================
    void bfsWithLevel(int start) {
        vector<bool> visited(V, false);
        vector<int> level(V, -1);
        queue<int> q;
        
        visited[start] = true;
        level[start] = 0;
        q.push(start);
        
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            
            for (int neighbor : adj[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    level[neighbor] = level[node] + 1;
                    q.push(neighbor);
                }
            }
        }
        
        cout << "Node levels from " << start << ":" << endl;
        for (int i = 0; i < V; i++) {
            cout << "Node " << i << ": Level " << level[i] << endl;
        }
    }
    
    // ==================== Shortest Path (Unweighted) ====================
    vector<int> shortestPath(int start, int end) {
        vector<bool> visited(V, false);
        vector<int> parent(V, -1);
        queue<int> q;
        
        visited[start] = true;
        q.push(start);
        
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            
            if (node == end) break;
            
            for (int neighbor : adj[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    parent[neighbor] = node;
                    q.push(neighbor);
                }
            }
        }
        
        // Reconstruct path
        vector<int> path;
        if (!visited[end]) return path; // No path
        
        for (int curr = end; curr != -1; curr = parent[curr]) {
            path.push_back(curr);
        }
        reverse(path.begin(), path.end());
        return path;
    }
    
    // ==================== BFS for All Components ====================
    void bfsAllComponents() {
        vector<bool> visited(V, false);
        int componentCount = 0;
        
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                componentCount++;
                cout << "Component " << componentCount << ": ";
                
                queue<int> q;
                visited[i] = true;
                q.push(i);
                
                while (!q.empty()) {
                    int node = q.front();
                    q.pop();
                    cout << node << " ";
                    
                    for (int neighbor : adj[node]) {
                        if (!visited[neighbor]) {
                            visited[neighbor] = true;
                            q.push(neighbor);
                        }
                    }
                }
                cout << endl;
            }
        }
        cout << "Total components: " << componentCount << endl;
    }
    
    // ==================== Multi-source BFS ====================
    vector<int> multiSourceBFS(vector<int>& sources) {
        vector<int> dist(V, INT_MAX);
        queue<int> q;
        
        for (int src : sources) {
            dist[src] = 0;
            q.push(src);
        }
        
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            
            for (int neighbor : adj[node]) {
                if (dist[neighbor] > dist[node] + 1) {
                    dist[neighbor] = dist[node] + 1;
                    q.push(neighbor);
                }
            }
        }
        
        return dist;
    }
};

// ==================== 0-1 BFS (Deque) ====================
class Graph01BFS {
public:
    int V;
    vector<vector<pair<int, int>>> adj; // {neighbor, weight (0 or 1)}
    
    Graph01BFS(int v) : V(v), adj(v) {}
    
    void addEdge(int u, int v, int w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    
    vector<int> shortestPath(int start) {
        vector<int> dist(V, INT_MAX);
        deque<int> dq;
        
        dist[start] = 0;
        dq.push_front(start);
        
        while (!dq.empty()) {
            int node = dq.front();
            dq.pop_front();
            
            for (auto& [neighbor, weight] : adj[node]) {
                if (dist[node] + weight < dist[neighbor]) {
                    dist[neighbor] = dist[node] + weight;
                    if (weight == 0) {
                        dq.push_front(neighbor);
                    } else {
                        dq.push_back(neighbor);
                    }
                }
            }
        }
        
        return dist;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cout << "=== BFS Demo ===" << endl;
    
    Graph g(6);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    g.addEdge(4, 5);
    
    // Basic BFS
    g.bfs(0);
    
    // BFS with levels
    cout << endl;
    g.bfsWithLevel(0);
    
    // Shortest path
    cout << "\nShortest path from 0 to 5: ";
    vector<int> path = g.shortestPath(0, 5);
    for (int node : path) cout << node << " ";
    cout << "(length: " << path.size() - 1 << ")" << endl;
    
    // Disconnected graph
    cout << "\n=== Disconnected Graph ===" << endl;
    Graph g2(7);
    g2.addEdge(0, 1);
    g2.addEdge(1, 2);
    g2.addEdge(3, 4);
    g2.addEdge(5, 6);
    g2.bfsAllComponents();
    
    // 0-1 BFS
    cout << "\n=== 0-1 BFS ===" << endl;
    Graph01BFS g3(5);
    g3.addEdge(0, 1, 0);
    g3.addEdge(1, 2, 1);
    g3.addEdge(0, 3, 1);
    g3.addEdge(3, 4, 0);
    g3.addEdge(2, 4, 0);
    
    vector<int> dist = g3.shortestPath(0);
    cout << "Distances from node 0:" << endl;
    for (int i = 0; i < 5; i++) {
        cout << "To " << i << ": " << dist[i] << endl;
    }
    
    return 0;
}



