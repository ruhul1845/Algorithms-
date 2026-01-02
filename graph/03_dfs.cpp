/*
    Depth-First Search (DFS)
    - Recursive and Iterative implementations
    - Discovery and finish times
    - Path finding
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
    
    // ==================== Recursive DFS ====================
    void dfsRecursive(int start) {
        vector<bool> visited(V, false);
        cout << "DFS (Recursive) from " << start << ": ";
        dfsUtil(start, visited);
        cout << endl;
    }
    
    void dfsUtil(int node, vector<bool>& visited) {
        visited[node] = true;
        cout << node << " ";
        
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                dfsUtil(neighbor, visited);
            }
        }
    }
    
    // ==================== Iterative DFS ====================
    void dfsIterative(int start) {
        vector<bool> visited(V, false);
        stack<int> st;
        
        st.push(start);
        cout << "DFS (Iterative) from " << start << ": ";
        
        while (!st.empty()) {
            int node = st.top();
            st.pop();
            
            if (visited[node]) continue;
            
            visited[node] = true;
            cout << node << " ";
            
            // Push neighbors in reverse order for same order as recursive
            for (int i = adj[node].size() - 1; i >= 0; i--) {
                if (!visited[adj[node][i]]) {
                    st.push(adj[node][i]);
                }
            }
        }
        cout << endl;
    }
    
    // ==================== DFS with Discovery/Finish Times ====================
    int timer = 0;
    
    void dfsWithTimes(int start) {
        vector<bool> visited(V, false);
        vector<int> discovery(V, -1);
        vector<int> finish(V, -1);
        timer = 0;
        
        dfsTimesUtil(start, visited, discovery, finish);
        
        cout << "Discovery and Finish Times:" << endl;
        for (int i = 0; i < V; i++) {
            if (discovery[i] != -1) {
                cout << "Node " << i << ": d=" << discovery[i] 
                     << ", f=" << finish[i] << endl;
            }
        }
    }
    
    void dfsTimesUtil(int node, vector<bool>& visited, 
                      vector<int>& discovery, vector<int>& finish) {
        visited[node] = true;
        discovery[node] = ++timer;
        
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                dfsTimesUtil(neighbor, visited, discovery, finish);
            }
        }
        
        finish[node] = ++timer;
    }
    
    // ==================== DFS for All Components ====================
    void dfsAllComponents() {
        vector<bool> visited(V, false);
        int componentCount = 0;
        
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                componentCount++;
                cout << "Component " << componentCount << ": ";
                dfsComponentUtil(i, visited);
                cout << endl;
            }
        }
        cout << "Total components: " << componentCount << endl;
    }
    
    void dfsComponentUtil(int node, vector<bool>& visited) {
        visited[node] = true;
        cout << node << " ";
        
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                dfsComponentUtil(neighbor, visited);
            }
        }
    }
    
    // ==================== Path Finding ====================
    bool findPath(int start, int end, vector<int>& path) {
        vector<bool> visited(V, false);
        return findPathUtil(start, end, visited, path);
    }
    
    bool findPathUtil(int node, int end, vector<bool>& visited, vector<int>& path) {
        visited[node] = true;
        path.push_back(node);
        
        if (node == end) return true;
        
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                if (findPathUtil(neighbor, end, visited, path)) {
                    return true;
                }
            }
        }
        
        path.pop_back();
        return false;
    }
    
    // ==================== Find All Paths ====================
    void findAllPaths(int start, int end) {
        vector<bool> visited(V, false);
        vector<int> path;
        cout << "All paths from " << start << " to " << end << ":" << endl;
        findAllPathsUtil(start, end, visited, path);
    }
    
    void findAllPathsUtil(int node, int end, vector<bool>& visited, vector<int>& path) {
        visited[node] = true;
        path.push_back(node);
        
        if (node == end) {
            for (int n : path) cout << n << " ";
            cout << endl;
        } else {
            for (int neighbor : adj[node]) {
                if (!visited[neighbor]) {
                    findAllPathsUtil(neighbor, end, visited, path);
                }
            }
        }
        
        path.pop_back();
        visited[node] = false;
    }
    
    // ==================== Count Nodes in Connected Component ====================
    int countNodesInComponent(int start) {
        vector<bool> visited(V, false);
        return countNodesUtil(start, visited);
    }
    
    int countNodesUtil(int node, vector<bool>& visited) {
        visited[node] = true;
        int count = 1;
        
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                count += countNodesUtil(neighbor, visited);
            }
        }
        
        return count;
    }
};

// ==================== DFS on Grid ====================
class GridDFS {
public:
    int rows, cols;
    vector<vector<int>> grid;
    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};
    
    GridDFS(vector<vector<int>>& g) : grid(g) {
        rows = g.size();
        cols = g[0].size();
    }
    
    // Count islands (connected 1s)
    int countIslands() {
        vector<vector<bool>> visited(rows, vector<bool>(cols, false));
        int islands = 0;
        
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (grid[i][j] == 1 && !visited[i][j]) {
                    islands++;
                    dfsGrid(i, j, visited);
                }
            }
        }
        
        return islands;
    }
    
    void dfsGrid(int r, int c, vector<vector<bool>>& visited) {
        if (r < 0 || r >= rows || c < 0 || c >= cols) return;
        if (visited[r][c] || grid[r][c] == 0) return;
        
        visited[r][c] = true;
        
        for (int d = 0; d < 4; d++) {
            dfsGrid(r + dr[d], c + dc[d], visited);
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cout << "=== DFS Demo ===" << endl;
    
    Graph g(6);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    g.addEdge(4, 5);
    
    // Recursive DFS
    g.dfsRecursive(0);
    
    // Iterative DFS
    g.dfsIterative(0);
    
    // DFS with times
    cout << endl;
    g.dfsWithTimes(0);
    
    // Path finding
    cout << "\nPath from 0 to 5: ";
    vector<int> path;
    if (g.findPath(0, 5, path)) {
        for (int node : path) cout << node << " ";
    } else {
        cout << "No path found";
    }
    cout << endl;
    
    // All paths
    cout << endl;
    Graph g2(4);
    g2.addEdge(0, 1);
    g2.addEdge(0, 2);
    g2.addEdge(1, 3);
    g2.addEdge(2, 3);
    g2.findAllPaths(0, 3);
    
    // Grid DFS - Count Islands
    cout << "\n=== Grid DFS (Count Islands) ===" << endl;
    vector<vector<int>> grid = {
        {1, 1, 0, 0, 0},
        {1, 1, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 1, 1}
    };
    GridDFS gdfs(grid);
    cout << "Number of islands: " << gdfs.countIslands() << endl;
    
    return 0;
}









