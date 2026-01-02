/*
    Cycle Detection in Graphs
    - Undirected Graph: DFS, Union-Find
    - Directed Graph: DFS with colors, Kahn's algorithm
    - Time: O(V + E)
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== Cycle in Undirected Graph (DFS) ====================
class UndirectedCycleDFS {
public:
    int V;
    vector<vector<int>> adj;
    
    UndirectedCycleDFS(int v) : V(v), adj(v) {}
    
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    bool hasCycle() {
        vector<bool> visited(V, false);
        
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                if (dfs(i, -1, visited)) return true;
            }
        }
        return false;
    }
    
    bool dfs(int node, int parent, vector<bool>& visited) {
        visited[node] = true;
        
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                if (dfs(neighbor, node, visited)) return true;
            } else if (neighbor != parent) {
                return true; // Cycle found
            }
        }
        return false;
    }
};

// ==================== Cycle in Undirected Graph (Union-Find) ====================
class UndirectedCycleUF {
public:
    vector<int> parent, rank_;
    
    UndirectedCycleUF(int n) : parent(n), rank_(n, 0) {
        iota(parent.begin(), parent.end(), 0);
    }
    
    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }
    
    bool unite(int x, int y) {
        int px = find(x), py = find(y);
        if (px == py) return false; // Cycle detected
        
        if (rank_[px] < rank_[py]) swap(px, py);
        parent[py] = px;
        if (rank_[px] == rank_[py]) rank_[px]++;
        return true;
    }
    
    bool hasCycle(vector<pair<int,int>>& edges) {
        for (auto& [u, v] : edges) {
            if (!unite(u, v)) return true;
        }
        return false;
    }
};

// ==================== Cycle in Directed Graph (DFS with Colors) ====================
class DirectedCycleDFS {
public:
    int V;
    vector<vector<int>> adj;
    
    DirectedCycleDFS(int v) : V(v), adj(v) {}
    
    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }
    
    // 0: white (unvisited), 1: gray (in recursion), 2: black (done)
    bool hasCycle() {
        vector<int> color(V, 0);
        
        for (int i = 0; i < V; i++) {
            if (color[i] == 0) {
                if (dfs(i, color)) return true;
            }
        }
        return false;
    }
    
    bool dfs(int node, vector<int>& color) {
        color[node] = 1;
        
        for (int neighbor : adj[node]) {
            if (color[neighbor] == 1) return true; // Back edge
            if (color[neighbor] == 0 && dfs(neighbor, color)) return true;
        }
        
        color[node] = 2;
        return false;
    }
    
    // Find the cycle
    vector<int> findCycle() {
        vector<int> color(V, 0);
        vector<int> parent(V, -1);
        int cycleStart = -1, cycleEnd = -1;
        
        for (int i = 0; i < V; i++) {
            if (color[i] == 0) {
                if (findCycleDFS(i, color, parent, cycleStart, cycleEnd)) break;
            }
        }
        
        vector<int> cycle;
        if (cycleStart == -1) return cycle;
        
        cycle.push_back(cycleStart);
        for (int v = cycleEnd; v != cycleStart; v = parent[v]) {
            cycle.push_back(v);
        }
        cycle.push_back(cycleStart);
        reverse(cycle.begin(), cycle.end());
        return cycle;
    }
    
    bool findCycleDFS(int node, vector<int>& color, vector<int>& parent, 
                      int& cycleStart, int& cycleEnd) {
        color[node] = 1;
        
        for (int neighbor : adj[node]) {
            if (color[neighbor] == 0) {
                parent[neighbor] = node;
                if (findCycleDFS(neighbor, color, parent, cycleStart, cycleEnd)) {
                    return true;
                }
            } else if (color[neighbor] == 1) {
                cycleEnd = node;
                cycleStart = neighbor;
                return true;
            }
        }
        
        color[node] = 2;
        return false;
    }
};

// ==================== Cycle in Directed Graph (Kahn's Algorithm) ====================
class DirectedCycleKahn {
public:
    int V;
    vector<vector<int>> adj;
    
    DirectedCycleKahn(int v) : V(v), adj(v) {}
    
    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }
    
    bool hasCycle() {
        vector<int> inDegree(V, 0);
        for (int u = 0; u < V; u++) {
            for (int v : adj[u]) inDegree[v]++;
        }
        
        queue<int> q;
        for (int i = 0; i < V; i++) {
            if (inDegree[i] == 0) q.push(i);
        }
        
        int count = 0;
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            count++;
            
            for (int neighbor : adj[node]) {
                if (--inDegree[neighbor] == 0) q.push(neighbor);
            }
        }
        
        return count != V;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cout << "=== Cycle Detection Demo ===" << endl;
    
    // Undirected graph with cycle
    cout << "Undirected Graph (DFS):" << endl;
    UndirectedCycleDFS g1(5);
    g1.addEdge(0, 1);
    g1.addEdge(1, 2);
    g1.addEdge(2, 0);
    g1.addEdge(2, 3);
    g1.addEdge(3, 4);
    cout << "Has cycle: " << (g1.hasCycle() ? "Yes" : "No") << endl;
    
    // Undirected graph without cycle
    UndirectedCycleDFS g2(4);
    g2.addEdge(0, 1);
    g2.addEdge(1, 2);
    g2.addEdge(2, 3);
    cout << "Has cycle (tree): " << (g2.hasCycle() ? "Yes" : "No") << endl;
    
    // Union-Find approach
    cout << "\nUndirected Graph (Union-Find):" << endl;
    vector<pair<int,int>> edges = {{0,1}, {1,2}, {2,0}, {2,3}};
    UndirectedCycleUF uf(5);
    cout << "Has cycle: " << (uf.hasCycle(edges) ? "Yes" : "No") << endl;
    
    // Directed graph with cycle
    cout << "\nDirected Graph (DFS):" << endl;
    DirectedCycleDFS g3(4);
    g3.addEdge(0, 1);
    g3.addEdge(1, 2);
    g3.addEdge(2, 3);
    g3.addEdge(3, 1);
    cout << "Has cycle: " << (g3.hasCycle() ? "Yes" : "No") << endl;
    
    vector<int> cycle = g3.findCycle();
    cout << "Cycle: ";
    for (int node : cycle) cout << node << " ";
    cout << endl;
    
    // Kahn's algorithm
    cout << "\nDirected Graph (Kahn's):" << endl;
    DirectedCycleKahn g4(4);
    g4.addEdge(0, 1);
    g4.addEdge(1, 2);
    g4.addEdge(2, 3);
    g4.addEdge(3, 1);
    cout << "Has cycle: " << (g4.hasCycle() ? "Yes" : "No") << endl;
    
    return 0;
}









