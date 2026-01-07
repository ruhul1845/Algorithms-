/*
    Articulation Points and Bridges
    - Cut vertices and cut edges
    - Tarjan's algorithm
    - Time: O(V + E)
*/

#include <bits/stdc++.h>
using namespace std;

class Graph {
public:
    int V, timer;
    vector<vector<int>> adj;
    vector<int> disc, low;
    vector<bool> visited, isArticulation;
    vector<pair<int, int>> bridges;
    
    Graph(int v) : V(v), timer(0), adj(v), disc(v), low(v), 
                   visited(v, false), isArticulation(v, false) {}
    
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    // ==================== Find Articulation Points ====================
    vector<int> findArticulationPoints() {
        fill(visited.begin(), visited.end(), false);
        fill(isArticulation.begin(), isArticulation.end(), false);
        timer = 0;
        
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                dfsArticulation(i, -1);
            }
        }
        
        vector<int> result;
        for (int i = 0; i < V; i++) {
            if (isArticulation[i]) result.push_back(i);
        }
        return result;
    }
    
    void dfsArticulation(int node, int parent) {
        visited[node] = true;
        disc[node] = low[node] = timer++;
        int children = 0;
        
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                children++;
                dfsArticulation(neighbor, node);
                low[node] = min(low[node], low[neighbor]);
                
                // Articulation point conditions
                if (parent == -1 && children > 1) {
                    isArticulation[node] = true;
                }
                if (parent != -1 && low[neighbor] >= disc[node]) {
                    isArticulation[node] = true;
                }
            } else if (neighbor != parent) {
                low[node] = min(low[node], disc[neighbor]);
            }
        }
    }
    
    // ==================== Find Bridges ====================
    vector<pair<int, int>> findBridges() {
        fill(visited.begin(), visited.end(), false);
        bridges.clear();
        timer = 0;
        
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                dfsBridges(i, -1);
            }
        }
        
        return bridges;
    }
    
    void dfsBridges(int node, int parent) {
        visited[node] = true;
        disc[node] = low[node] = timer++;
        
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                dfsBridges(neighbor, node);
                low[node] = min(low[node], low[neighbor]);
                
                // Bridge condition
                if (low[neighbor] > disc[node]) {
                    bridges.push_back({node, neighbor});
                }
            } else if (neighbor != parent) {
                low[node] = min(low[node], disc[neighbor]);
            }
        }
    }
    
    // ==================== Find Biconnected Components ====================
    vector<vector<pair<int, int>>> findBiconnectedComponents() {
        fill(visited.begin(), visited.end(), false);
        timer = 0;
        
        vector<vector<pair<int, int>>> bccs;
        stack<pair<int, int>> edgeStack;
        
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                dfsBCC(i, -1, edgeStack, bccs);
            }
        }
        
        return bccs;
    }
    
    void dfsBCC(int node, int parent, stack<pair<int, int>>& edgeStack,
                vector<vector<pair<int, int>>>& bccs) {
        visited[node] = true;
        disc[node] = low[node] = timer++;
        
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                edgeStack.push({node, neighbor});
                dfsBCC(neighbor, node, edgeStack, bccs);
                low[node] = min(low[node], low[neighbor]);
                
                if (low[neighbor] >= disc[node]) {
                    vector<pair<int, int>> bcc;
                    while (!edgeStack.empty()) {
                        auto edge = edgeStack.top();
                        edgeStack.pop();
                        bcc.push_back(edge);
                        if (edge.first == node && edge.second == neighbor) break;
                    }
                    bccs.push_back(bcc);
                }
            } else if (neighbor != parent && disc[neighbor] < disc[node]) {
                edgeStack.push({node, neighbor});
                low[node] = min(low[node], disc[neighbor]);
            }
        }
    }
};

// ==================== Critical Connections (LeetCode 1192) ====================
class CriticalConnections {
public:
    int timer = 0;
    
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        vector<vector<int>> adj(n);
        for (auto& conn : connections) {
            adj[conn[0]].push_back(conn[1]);
            adj[conn[1]].push_back(conn[0]);
        }
        
        vector<int> disc(n, -1), low(n);
        vector<vector<int>> result;
        
        dfs(0, -1, adj, disc, low, result);
        return result;
    }
    
    void dfs(int node, int parent, vector<vector<int>>& adj,
             vector<int>& disc, vector<int>& low, vector<vector<int>>& result) {
        disc[node] = low[node] = timer++;
        
        for (int neighbor : adj[node]) {
            if (disc[neighbor] == -1) {
                dfs(neighbor, node, adj, disc, low, result);
                low[node] = min(low[node], low[neighbor]);
                
                if (low[neighbor] > disc[node]) {
                    result.push_back({node, neighbor});
                }
            } else if (neighbor != parent) {
                low[node] = min(low[node], disc[neighbor]);
            }
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cout << "=== Articulation Points & Bridges Demo ===" << endl;
    
    Graph g(7);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(1, 3);
    g.addEdge(3, 4);
    g.addEdge(4, 5);
    g.addEdge(5, 3);
    g.addEdge(4, 6);
    
    // Articulation Points
    cout << "Articulation Points: ";
    vector<int> artPoints = g.findArticulationPoints();
    for (int p : artPoints) cout << p << " ";
    cout << endl;
    
    // Bridges
    cout << "Bridges: ";
    auto bridges = g.findBridges();
    for (auto& [u, v] : bridges) {
        cout << "(" << u << "-" << v << ") ";
    }
    cout << endl;
    
    // Biconnected Components
    cout << "\nBiconnected Components:" << endl;
    auto bccs = g.findBiconnectedComponents();
    for (int i = 0; i < bccs.size(); i++) {
        cout << "BCC " << i + 1 << ": ";
        for (auto& [u, v] : bccs[i]) {
            cout << "(" << u << "-" << v << ") ";
        }
        cout << endl;
    }
    
    // Critical Connections
    cout << "\n=== Critical Connections ===" << endl;
    vector<vector<int>> conn = {{0,1},{1,2},{2,0},{1,3}};
    CriticalConnections cc;
    auto critConn = cc.criticalConnections(4, conn);
    cout << "Critical Connections: ";
    for (auto& c : critConn) {
        cout << "(" << c[0] << "-" << c[1] << ") ";
    }
    cout << endl;
    
    return 0;
}


















