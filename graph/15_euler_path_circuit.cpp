/*
    Eulerian Path and Circuit
    - Eulerian Path: visits every edge exactly once
    - Eulerian Circuit: Eulerian path that starts and ends at same vertex
    - Hierholzer's Algorithm
    - Time: O(E)
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== Undirected Graph ====================
class UndirectedEuler {
public:
    int V;
    vector<multiset<int>> adj;
    
    UndirectedEuler(int v) : V(v), adj(v) {}
    
    void addEdge(int u, int v) {
        adj[u].insert(v);
        adj[v].insert(u);
    }
    
    // Check if Eulerian path/circuit exists
    // 0: No Eulerian path, 1: Eulerian path, 2: Eulerian circuit
    int hasEuler() {
        // Check connectivity (ignoring isolated vertices)
        int start = -1;
        for (int i = 0; i < V; i++) {
            if (!adj[i].empty()) {
                start = i;
                break;
            }
        }
        if (start == -1) return 2; // Empty graph
        
        vector<bool> visited(V, false);
        dfs(start, visited);
        
        for (int i = 0; i < V; i++) {
            if (!adj[i].empty() && !visited[i]) return 0;
        }
        
        // Count odd degree vertices
        int oddCount = 0;
        for (int i = 0; i < V; i++) {
            if (adj[i].size() % 2 == 1) oddCount++;
        }
        
        if (oddCount == 0) return 2; // Eulerian circuit
        if (oddCount == 2) return 1; // Eulerian path
        return 0;
    }
    
    void dfs(int node, vector<bool>& visited) {
        visited[node] = true;
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) dfs(neighbor, visited);
        }
    }
    
    // Find Eulerian path/circuit using Hierholzer's algorithm
    vector<int> findEulerPath() {
        int eulerType = hasEuler();
        if (eulerType == 0) return {};
        
        // Find starting vertex
        int start = 0;
        if (eulerType == 1) {
            for (int i = 0; i < V; i++) {
                if (adj[i].size() % 2 == 1) {
                    start = i;
                    break;
                }
            }
        } else {
            for (int i = 0; i < V; i++) {
                if (!adj[i].empty()) {
                    start = i;
                    break;
                }
            }
        }
        
        vector<int> path;
        stack<int> st;
        st.push(start);
        
        while (!st.empty()) {
            int node = st.top();
            if (adj[node].empty()) {
                path.push_back(node);
                st.pop();
            } else {
                int next = *adj[node].begin();
                adj[node].erase(adj[node].find(next));
                adj[next].erase(adj[next].find(node));
                st.push(next);
            }
        }
        
        reverse(path.begin(), path.end());
        return path;
    }
};

// ==================== Directed Graph ====================
class DirectedEuler {
public:
    int V;
    vector<multiset<int>> adj;
    vector<int> inDegree, outDegree;
    
    DirectedEuler(int v) : V(v), adj(v), inDegree(v, 0), outDegree(v, 0) {}
    
    void addEdge(int u, int v) {
        adj[u].insert(v);
        outDegree[u]++;
        inDegree[v]++;
    }
    
    // Check if Eulerian path/circuit exists
    // 0: No Eulerian path, 1: Eulerian path, 2: Eulerian circuit
    int hasEuler() {
        // Check connectivity
        int start = -1;
        for (int i = 0; i < V; i++) {
            if (outDegree[i] > 0) {
                start = i;
                break;
            }
        }
        if (start == -1) return 2;
        
        // Check degree conditions
        int startNodes = 0, endNodes = 0;
        for (int i = 0; i < V; i++) {
            int diff = outDegree[i] - inDegree[i];
            if (diff > 1 || diff < -1) return 0;
            if (diff == 1) startNodes++;
            if (diff == -1) endNodes++;
        }
        
        if (startNodes == 0 && endNodes == 0) return 2; // Circuit
        if (startNodes == 1 && endNodes == 1) return 1; // Path
        return 0;
    }
    
    // Find Eulerian path/circuit using Hierholzer's algorithm
    vector<int> findEulerPath() {
        int eulerType = hasEuler();
        if (eulerType == 0) return {};
        
        // Find starting vertex
        int start = 0;
        if (eulerType == 1) {
            for (int i = 0; i < V; i++) {
                if (outDegree[i] - inDegree[i] == 1) {
                    start = i;
                    break;
                }
            }
        } else {
            for (int i = 0; i < V; i++) {
                if (outDegree[i] > 0) {
                    start = i;
                    break;
                }
            }
        }
        
        vector<int> path;
        stack<int> st;
        st.push(start);
        
        while (!st.empty()) {
            int node = st.top();
            if (adj[node].empty()) {
                path.push_back(node);
                st.pop();
            } else {
                int next = *adj[node].begin();
                adj[node].erase(adj[node].find(next));
                st.push(next);
            }
        }
        
        reverse(path.begin(), path.end());
        return path;
    }
};

// ==================== Reconstruct Itinerary (LeetCode 332) ====================
class ReconstructItinerary {
public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        map<string, multiset<string>> adj;
        for (auto& ticket : tickets) {
            adj[ticket[0]].insert(ticket[1]);
        }
        
        vector<string> path;
        stack<string> st;
        st.push("JFK");
        
        while (!st.empty()) {
            string node = st.top();
            if (adj[node].empty()) {
                path.push_back(node);
                st.pop();
            } else {
                string next = *adj[node].begin();
                adj[node].erase(adj[node].begin());
                st.push(next);
            }
        }
        
        reverse(path.begin(), path.end());
        return path;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cout << "=== Eulerian Path & Circuit Demo ===" << endl;
    
    // Undirected graph with Eulerian circuit
    cout << "Undirected Graph (Eulerian Circuit):" << endl;
    UndirectedEuler g1(5);
    g1.addEdge(0, 1);
    g1.addEdge(1, 2);
    g1.addEdge(2, 0);
    g1.addEdge(0, 3);
    g1.addEdge(3, 4);
    g1.addEdge(4, 0);
    
    int type1 = g1.hasEuler();
    cout << "Euler type: " << (type1 == 2 ? "Circuit" : (type1 == 1 ? "Path" : "None")) << endl;
    
    vector<int> path1 = g1.findEulerPath();
    cout << "Euler path: ";
    for (int node : path1) cout << node << " ";
    cout << endl;
    
    // Undirected graph with Eulerian path
    cout << "\nUndirected Graph (Eulerian Path):" << endl;
    UndirectedEuler g2(4);
    g2.addEdge(0, 1);
    g2.addEdge(1, 2);
    g2.addEdge(2, 3);
    
    int type2 = g2.hasEuler();
    cout << "Euler type: " << (type2 == 2 ? "Circuit" : (type2 == 1 ? "Path" : "None")) << endl;
    
    vector<int> path2 = g2.findEulerPath();
    cout << "Euler path: ";
    for (int node : path2) cout << node << " ";
    cout << endl;
    
    // Directed graph with Eulerian circuit
    cout << "\nDirected Graph (Eulerian Circuit):" << endl;
    DirectedEuler g3(3);
    g3.addEdge(0, 1);
    g3.addEdge(1, 2);
    g3.addEdge(2, 0);
    
    int type3 = g3.hasEuler();
    cout << "Euler type: " << (type3 == 2 ? "Circuit" : (type3 == 1 ? "Path" : "None")) << endl;
    
    vector<int> path3 = g3.findEulerPath();
    cout << "Euler path: ";
    for (int node : path3) cout << node << " ";
    cout << endl;
    
    // Reconstruct Itinerary
    cout << "\n=== Reconstruct Itinerary ===" << endl;
    vector<vector<string>> tickets = {{"JFK","SFO"},{"JFK","ATL"},{"SFO","ATL"},{"ATL","JFK"},{"ATL","SFO"}};
    ReconstructItinerary ri;
    vector<string> itinerary = ri.findItinerary(tickets);
    cout << "Itinerary: ";
    for (auto& city : itinerary) cout << city << " ";
    cout << endl;
    
    return 0;
}



