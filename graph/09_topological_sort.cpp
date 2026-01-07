/*
    Topological Sort
    - Linear ordering of vertices in DAG
    - For every directed edge (u, v), u comes before v
    - DFS-based (Tarjan's) and BFS-based (Kahn's)
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
    }
    
    // ==================== DFS-based (Tarjan's Algorithm) ====================
    vector<int> topologicalSortDFS() {
        vector<bool> visited(V, false);
        stack<int> st;
        
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                dfsUtil(i, visited, st);
            }
        }
        
        vector<int> result;
        while (!st.empty()) {
            result.push_back(st.top());
            st.pop();
        }
        
        return result;
    }
    
    void dfsUtil(int node, vector<bool>& visited, stack<int>& st) {
        visited[node] = true;
        
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                dfsUtil(neighbor, visited, st);
            }
        }
        
        st.push(node);
    }
    
    // ==================== BFS-based (Kahn's Algorithm) ====================
    vector<int> topologicalSortBFS() {
        vector<int> inDegree(V, 0);
        
        for (int u = 0; u < V; u++) {
            for (int v : adj[u]) {
                inDegree[v]++;
            }
        }
        
        queue<int> q;
        for (int i = 0; i < V; i++) {
            if (inDegree[i] == 0) {
                q.push(i);
            }
        }
        
        vector<int> result;
        
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            result.push_back(node);
            
            for (int neighbor : adj[node]) {
                inDegree[neighbor]--;
                if (inDegree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }
        
        // Check if valid (no cycle)
        if (result.size() != V) {
            return {}; // Cycle detected
        }
        
        return result;
    }
    
    // ==================== All Topological Sorts ====================
    void allTopologicalSorts() {
        vector<bool> visited(V, false);
        vector<int> inDegree(V, 0);
        
        for (int u = 0; u < V; u++) {
            for (int v : adj[u]) {
                inDegree[v]++;
            }
        }
        
        vector<int> current;
        cout << "All topological sorts:" << endl;
        allTopoUtil(visited, inDegree, current);
    }
    
    void allTopoUtil(vector<bool>& visited, vector<int>& inDegree, vector<int>& current) {
        bool found = false;
        
        for (int i = 0; i < V; i++) {
            if (!visited[i] && inDegree[i] == 0) {
                visited[i] = true;
                current.push_back(i);
                
                for (int neighbor : adj[i]) {
                    inDegree[neighbor]--;
                }
                
                allTopoUtil(visited, inDegree, current);
                
                // Backtrack
                visited[i] = false;
                current.pop_back();
                for (int neighbor : adj[i]) {
                    inDegree[neighbor]++;
                }
                
                found = true;
            }
        }
        
        if (!found && current.size() == V) {
            for (int node : current) cout << node << " ";
            cout << endl;
        }
    }
    
    // ==================== Check if Topological Sort Exists ====================
    bool hasValidTopologicalSort() {
        return !topologicalSortBFS().empty();
    }
    
    // ==================== Lexicographically Smallest Topological Sort ====================
    vector<int> lexSmallestTopoSort() {
        vector<int> inDegree(V, 0);
        
        for (int u = 0; u < V; u++) {
            for (int v : adj[u]) {
                inDegree[v]++;
            }
        }
        
        priority_queue<int, vector<int>, greater<int>> pq;
        for (int i = 0; i < V; i++) {
            if (inDegree[i] == 0) {
                pq.push(i);
            }
        }
        
        vector<int> result;
        
        while (!pq.empty()) {
            int node = pq.top();
            pq.pop();
            result.push_back(node);
            
            for (int neighbor : adj[node]) {
                inDegree[neighbor]--;
                if (inDegree[neighbor] == 0) {
                    pq.push(neighbor);
                }
            }
        }
        
        return (result.size() == V) ? result : vector<int>();
    }
};

// ==================== Course Schedule ====================
class CourseSchedule {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> adj(numCourses);
        vector<int> inDegree(numCourses, 0);
        
        for (auto& pre : prerequisites) {
            adj[pre[1]].push_back(pre[0]);
            inDegree[pre[0]]++;
        }
        
        queue<int> q;
        for (int i = 0; i < numCourses; i++) {
            if (inDegree[i] == 0) q.push(i);
        }
        
        int count = 0;
        while (!q.empty()) {
            int course = q.front();
            q.pop();
            count++;
            
            for (int next : adj[course]) {
                if (--inDegree[next] == 0) {
                    q.push(next);
                }
            }
        }
        
        return count == numCourses;
    }
    
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> adj(numCourses);
        vector<int> inDegree(numCourses, 0);
        
        for (auto& pre : prerequisites) {
            adj[pre[1]].push_back(pre[0]);
            inDegree[pre[0]]++;
        }
        
        queue<int> q;
        for (int i = 0; i < numCourses; i++) {
            if (inDegree[i] == 0) q.push(i);
        }
        
        vector<int> order;
        while (!q.empty()) {
            int course = q.front();
            q.pop();
            order.push_back(course);
            
            for (int next : adj[course]) {
                if (--inDegree[next] == 0) {
                    q.push(next);
                }
            }
        }
        
        return (order.size() == numCourses) ? order : vector<int>();
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cout << "=== Topological Sort Demo ===" << endl;
    
    Graph g(6);
    g.addEdge(5, 2);
    g.addEdge(5, 0);
    g.addEdge(4, 0);
    g.addEdge(4, 1);
    g.addEdge(2, 3);
    g.addEdge(3, 1);
    
    // DFS-based
    cout << "Topological Sort (DFS): ";
    vector<int> order1 = g.topologicalSortDFS();
    for (int node : order1) cout << node << " ";
    cout << endl;
    
    // BFS-based (Kahn's)
    cout << "Topological Sort (BFS): ";
    vector<int> order2 = g.topologicalSortBFS();
    for (int node : order2) cout << node << " ";
    cout << endl;
    
    // Lexicographically smallest
    cout << "Lex Smallest Topo Sort: ";
    vector<int> order3 = g.lexSmallestTopoSort();
    for (int node : order3) cout << node << " ";
    cout << endl;
    
    // All topological sorts (small graph)
    cout << "\n";
    Graph g2(4);
    g2.addEdge(0, 1);
    g2.addEdge(0, 2);
    g2.addEdge(1, 3);
    g2.addEdge(2, 3);
    g2.allTopologicalSorts();
    
    // Course schedule
    cout << "\n=== Course Schedule ===" << endl;
    vector<vector<int>> prereqs = {{1,0}, {2,0}, {3,1}, {3,2}};
    CourseSchedule cs;
    cout << "Can finish: " << (cs.canFinish(4, prereqs) ? "Yes" : "No") << endl;
    cout << "Order: ";
    vector<int> courseOrder = cs.findOrder(4, prereqs);
    for (int c : courseOrder) cout << c << " ";
    cout << endl;
    
    return 0;
}


















