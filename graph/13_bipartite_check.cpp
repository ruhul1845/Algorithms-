/*
    Bipartite Graph Check
    - Two-coloring problem
    - BFS and DFS approaches
    - Time: O(V + E)
*/

#include <bits/stdc++.h>
using namespace std;

class Graph {
public:
    int V;
    vector<vector<int>> adj;
    
    Graph(int v) : V(v), adj(v) {}
    
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    // ==================== BFS Bipartite Check ====================
    bool isBipartiteBFS() {
        vector<int> color(V, -1);
        
        for (int i = 0; i < V; i++) {
            if (color[i] == -1) {
                if (!bfs(i, color)) return false;
            }
        }
        return true;
    }
    
    bool bfs(int start, vector<int>& color) {
        queue<int> q;
        q.push(start);
        color[start] = 0;
        
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            
            for (int neighbor : adj[node]) {
                if (color[neighbor] == -1) {
                    color[neighbor] = 1 - color[node];
                    q.push(neighbor);
                } else if (color[neighbor] == color[node]) {
                    return false;
                }
            }
        }
        return true;
    }
    
    // ==================== DFS Bipartite Check ====================
    bool isBipartiteDFS() {
        vector<int> color(V, -1);
        
        for (int i = 0; i < V; i++) {
            if (color[i] == -1) {
                if (!dfs(i, 0, color)) return false;
            }
        }
        return true;
    }
    
    bool dfs(int node, int c, vector<int>& color) {
        color[node] = c;
        
        for (int neighbor : adj[node]) {
            if (color[neighbor] == -1) {
                if (!dfs(neighbor, 1 - c, color)) return false;
            } else if (color[neighbor] == c) {
                return false;
            }
        }
        return true;
    }
    
    // ==================== Get Bipartition ====================
    pair<vector<int>, vector<int>> getBipartition() {
        vector<int> color(V, -1);
        vector<int> setA, setB;
        
        for (int i = 0; i < V; i++) {
            if (color[i] == -1) {
                queue<int> q;
                q.push(i);
                color[i] = 0;
                
                while (!q.empty()) {
                    int node = q.front();
                    q.pop();
                    
                    if (color[node] == 0) setA.push_back(node);
                    else setB.push_back(node);
                    
                    for (int neighbor : adj[node]) {
                        if (color[neighbor] == -1) {
                            color[neighbor] = 1 - color[node];
                            q.push(neighbor);
                        }
                    }
                }
            }
        }
        
        return {setA, setB};
    }
    
    // ==================== Find Odd Cycle (if not bipartite) ====================
    vector<int> findOddCycle() {
        vector<int> color(V, -1);
        vector<int> parent(V, -1);
        
        for (int i = 0; i < V; i++) {
            if (color[i] == -1) {
                queue<int> q;
                q.push(i);
                color[i] = 0;
                
                while (!q.empty()) {
                    int node = q.front();
                    q.pop();
                    
                    for (int neighbor : adj[node]) {
                        if (color[neighbor] == -1) {
                            color[neighbor] = 1 - color[node];
                            parent[neighbor] = node;
                            q.push(neighbor);
                        } else if (color[neighbor] == color[node]) {
                            // Found odd cycle
                            vector<int> cycle;
                            int u = node, v = neighbor;
                            while (u != v) {
                                cycle.push_back(u);
                                u = parent[u];
                            }
                            cycle.push_back(v);
                            
                            vector<int> pathFromV;
                            int curr = neighbor;
                            while (curr != -1 && curr != u) {
                                pathFromV.push_back(curr);
                                curr = parent[curr];
                            }
                            
                            return cycle;
                        }
                    }
                }
            }
        }
        
        return {}; // Bipartite, no odd cycle
    }
};

// ==================== Possible Bipartition (LeetCode 886) ====================
class PossibleBipartition {
public:
    bool possibleBipartition(int n, vector<vector<int>>& dislikes) {
        vector<vector<int>> adj(n + 1);
        for (auto& d : dislikes) {
            adj[d[0]].push_back(d[1]);
            adj[d[1]].push_back(d[0]);
        }
        
        vector<int> color(n + 1, -1);
        
        for (int i = 1; i <= n; i++) {
            if (color[i] == -1) {
                queue<int> q;
                q.push(i);
                color[i] = 0;
                
                while (!q.empty()) {
                    int node = q.front();
                    q.pop();
                    
                    for (int neighbor : adj[node]) {
                        if (color[neighbor] == -1) {
                            color[neighbor] = 1 - color[node];
                            q.push(neighbor);
                        } else if (color[neighbor] == color[node]) {
                            return false;
                        }
                    }
                }
            }
        }
        
        return true;
    }
};

// ==================== Is Graph Bipartite (LeetCode 785) ====================
class IsGraphBipartite {
public:
    bool isBipartite(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<int> color(n, -1);
        
        for (int i = 0; i < n; i++) {
            if (color[i] == -1) {
                queue<int> q;
                q.push(i);
                color[i] = 0;
                
                while (!q.empty()) {
                    int node = q.front();
                    q.pop();
                    
                    for (int neighbor : graph[node]) {
                        if (color[neighbor] == -1) {
                            color[neighbor] = 1 - color[node];
                            q.push(neighbor);
                        } else if (color[neighbor] == color[node]) {
                            return false;
                        }
                    }
                }
            }
        }
        
        return true;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cout << "=== Bipartite Graph Check Demo ===" << endl;
    
    // Bipartite graph
    Graph g1(6);
    g1.addEdge(0, 1);
    g1.addEdge(0, 3);
    g1.addEdge(1, 2);
    g1.addEdge(2, 3);
    g1.addEdge(3, 4);
    g1.addEdge(4, 5);
    
    cout << "Graph 1 is bipartite (BFS): " << (g1.isBipartiteBFS() ? "Yes" : "No") << endl;
    cout << "Graph 1 is bipartite (DFS): " << (g1.isBipartiteDFS() ? "Yes" : "No") << endl;
    
    auto [setA, setB] = g1.getBipartition();
    cout << "Set A: ";
    for (int v : setA) cout << v << " ";
    cout << "\nSet B: ";
    for (int v : setB) cout << v << " ";
    cout << endl;
    
    // Non-bipartite graph (odd cycle)
    cout << "\n";
    Graph g2(5);
    g2.addEdge(0, 1);
    g2.addEdge(1, 2);
    g2.addEdge(2, 0); // Triangle
    g2.addEdge(2, 3);
    g2.addEdge(3, 4);
    
    cout << "Graph 2 is bipartite: " << (g2.isBipartiteBFS() ? "Yes" : "No") << endl;
    
    // Possible Bipartition
    cout << "\n=== Possible Bipartition ===" << endl;
    vector<vector<int>> dislikes = {{1,2},{1,3},{2,4}};
    PossibleBipartition pb;
    cout << "Can bipartition: " << (pb.possibleBipartition(4, dislikes) ? "Yes" : "No") << endl;
    
    return 0;
}

