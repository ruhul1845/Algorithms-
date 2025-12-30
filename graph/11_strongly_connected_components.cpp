/*
    Strongly Connected Components (SCC)
    - Kosaraju's Algorithm
    - Tarjan's Algorithm
    - Time: O(V + E)
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== Kosaraju's Algorithm ====================
class KosarajuSCC {
public:
    int V;
    vector<vector<int>> adj, radj;
    
    KosarajuSCC(int v) : V(v), adj(v), radj(v) {}
    
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        radj[v].push_back(u);
    }
    
    vector<vector<int>> findSCCs() {
        vector<bool> visited(V, false);
        stack<int> order;
        
        // Step 1: Fill stack with finish order
        for (int i = 0; i < V; i++) {
            if (!visited[i]) dfs1(i, visited, order);
        }
        
        // Step 2: Process in reverse order on reversed graph
        fill(visited.begin(), visited.end(), false);
        vector<vector<int>> sccs;
        
        while (!order.empty()) {
            int node = order.top();
            order.pop();
            
            if (!visited[node]) {
                vector<int> scc;
                dfs2(node, visited, scc);
                sccs.push_back(scc);
            }
        }
        
        return sccs;
    }
    
    void dfs1(int node, vector<bool>& visited, stack<int>& order) {
        visited[node] = true;
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) dfs1(neighbor, visited, order);
        }
        order.push(node);
    }
    
    void dfs2(int node, vector<bool>& visited, vector<int>& scc) {
        visited[node] = true;
        scc.push_back(node);
        for (int neighbor : radj[node]) {
            if (!visited[neighbor]) dfs2(neighbor, visited, scc);
        }
    }
    
    int countSCCs() {
        return findSCCs().size();
    }
};

// ==================== Tarjan's Algorithm ====================
class TarjanSCC {
public:
    int V, timer;
    vector<vector<int>> adj;
    vector<int> disc, low, sccId;
    vector<bool> onStack;
    stack<int> st;
    vector<vector<int>> sccs;
    int sccCount;
    
    TarjanSCC(int v) : V(v), timer(0), adj(v), disc(v, -1), low(v, 0), 
                       sccId(v, -1), onStack(v, false), sccCount(0) {}
    
    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }
    
    vector<vector<int>> findSCCs() {
        for (int i = 0; i < V; i++) {
            if (disc[i] == -1) dfs(i);
        }
        return sccs;
    }
    
    void dfs(int node) {
        disc[node] = low[node] = timer++;
        st.push(node);
        onStack[node] = true;
        
        for (int neighbor : adj[node]) {
            if (disc[neighbor] == -1) {
                dfs(neighbor);
                low[node] = min(low[node], low[neighbor]);
            } else if (onStack[neighbor]) {
                low[node] = min(low[node], disc[neighbor]);
            }
        }
        
        // Node is root of SCC
        if (low[node] == disc[node]) {
            vector<int> scc;
            while (true) {
                int v = st.top();
                st.pop();
                onStack[v] = false;
                sccId[v] = sccCount;
                scc.push_back(v);
                if (v == node) break;
            }
            sccs.push_back(scc);
            sccCount++;
        }
    }
    
    // Build condensation graph (DAG of SCCs)
    vector<vector<int>> buildCondensation() {
        if (sccs.empty()) findSCCs();
        
        set<pair<int,int>> edges;
        for (int u = 0; u < V; u++) {
            for (int v : adj[u]) {
                if (sccId[u] != sccId[v]) {
                    edges.insert({sccId[u], sccId[v]});
                }
            }
        }
        
        vector<vector<int>> condensation(sccCount);
        for (auto& [u, v] : edges) {
            condensation[u].push_back(v);
        }
        return condensation;
    }
};

// ==================== 2-SAT using SCC ====================
class TwoSAT {
public:
    int n;
    TarjanSCC scc;
    
    TwoSAT(int variables) : n(variables), scc(2 * variables) {}
    
    // Add clause: a OR b
    // For negative variable i, use ~i or -i-1
    void addClause(int a, int b) {
        int notA = (a >= 0) ? (a + n) : (-a - 1);
        int notB = (b >= 0) ? (b + n) : (-b - 1);
        int posA = (a >= 0) ? a : (-a - 1 + n);
        int posB = (b >= 0) ? b : (-b - 1 + n);
        
        // NOT a => b and NOT b => a
        scc.addEdge(notA, posB);
        scc.addEdge(notB, posA);
    }
    
    pair<bool, vector<bool>> solve() {
        scc.findSCCs();
        
        vector<bool> assignment(n);
        
        for (int i = 0; i < n; i++) {
            if (scc.sccId[i] == scc.sccId[i + n]) {
                return {false, {}}; // No solution
            }
            assignment[i] = scc.sccId[i] > scc.sccId[i + n];
        }
        
        return {true, assignment};
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cout << "=== Strongly Connected Components Demo ===" << endl;
    
    // Kosaraju's Algorithm
    cout << "Kosaraju's Algorithm:" << endl;
    KosarajuSCC g1(8);
    g1.addEdge(0, 1);
    g1.addEdge(1, 2);
    g1.addEdge(2, 0);
    g1.addEdge(2, 3);
    g1.addEdge(3, 4);
    g1.addEdge(4, 5);
    g1.addEdge(5, 3);
    g1.addEdge(6, 5);
    g1.addEdge(6, 7);
    g1.addEdge(7, 6);
    
    auto sccs1 = g1.findSCCs();
    cout << "Number of SCCs: " << sccs1.size() << endl;
    for (int i = 0; i < sccs1.size(); i++) {
        cout << "SCC " << i + 1 << ": ";
        for (int node : sccs1[i]) cout << node << " ";
        cout << endl;
    }
    
    // Tarjan's Algorithm
    cout << "\nTarjan's Algorithm:" << endl;
    TarjanSCC g2(8);
    g2.addEdge(0, 1);
    g2.addEdge(1, 2);
    g2.addEdge(2, 0);
    g2.addEdge(2, 3);
    g2.addEdge(3, 4);
    g2.addEdge(4, 5);
    g2.addEdge(5, 3);
    g2.addEdge(6, 5);
    g2.addEdge(6, 7);
    g2.addEdge(7, 6);
    
    auto sccs2 = g2.findSCCs();
    cout << "Number of SCCs: " << sccs2.size() << endl;
    for (int i = 0; i < sccs2.size(); i++) {
        cout << "SCC " << i + 1 << ": ";
        for (int node : sccs2[i]) cout << node << " ";
        cout << endl;
    }
    
    // 2-SAT
    cout << "\n=== 2-SAT Problem ===" << endl;
    TwoSAT sat(3);
    sat.addClause(0, 1);      // x0 OR x1
    sat.addClause(-1, 2);     // NOT x0 OR x2
    sat.addClause(-2, -3);    // NOT x1 OR NOT x2
    
    auto [solvable, assignment] = sat.solve();
    if (solvable) {
        cout << "Solution: ";
        for (int i = 0; i < assignment.size(); i++) {
            cout << "x" << i << "=" << assignment[i] << " ";
        }
        cout << endl;
    } else {
        cout << "No solution" << endl;
    }
    
    return 0;
}

