/*
    Tarjan's SCC with Applications
    - Strongly Connected Components
    - Condensation Graph
*/

#include <bits/stdc++.h>
using namespace std;

class TarjanSCC {
public:
    int n, timer, sccCount;
    vector<vector<int>> adj;
    vector<int> disc, low, sccId;
    vector<bool> onStack;
    stack<int> st;
    
    TarjanSCC(int n) : n(n), timer(0), sccCount(0), adj(n), disc(n, -1), 
                       low(n), sccId(n, -1), onStack(n, false) {}
    
    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }
    
    void dfs(int v) {
        disc[v] = low[v] = timer++;
        st.push(v);
        onStack[v] = true;
        
        for (int u : adj[v]) {
            if (disc[u] == -1) {
                dfs(u);
                low[v] = min(low[v], low[u]);
            } else if (onStack[u]) {
                low[v] = min(low[v], disc[u]);
            }
        }
        
        if (low[v] == disc[v]) {
            while (true) {
                int u = st.top();
                st.pop();
                onStack[u] = false;
                sccId[u] = sccCount;
                if (u == v) break;
            }
            sccCount++;
        }
    }
    
    void findSCCs() {
        for (int i = 0; i < n; i++) {
            if (disc[i] == -1) dfs(i);
        }
    }
    
    // Build condensation graph (DAG of SCCs)
    vector<vector<int>> buildCondensation() {
        findSCCs();
        
        set<pair<int, int>> edges;
        for (int u = 0; u < n; u++) {
            for (int v : adj[u]) {
                if (sccId[u] != sccId[v]) {
                    edges.insert({sccId[u], sccId[v]});
                }
            }
        }
        
        vector<vector<int>> cond(sccCount);
        for (auto& [u, v] : edges) {
            cond[u].push_back(v);
        }
        return cond;
    }
    
    // Get nodes in each SCC
    vector<vector<int>> getSCCs() {
        findSCCs();
        vector<vector<int>> sccs(sccCount);
        for (int i = 0; i < n; i++) {
            sccs[sccId[i]].push_back(i);
        }
        return sccs;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cout << "=== Tarjan's SCC Demo ===" << endl;
    
    TarjanSCC g(8);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    g.addEdge(4, 5);
    g.addEdge(5, 3);
    g.addEdge(6, 5);
    g.addEdge(6, 7);
    g.addEdge(7, 6);
    
    auto sccs = g.getSCCs();
    cout << "Number of SCCs: " << sccs.size() << endl;
    
    for (int i = 0; i < sccs.size(); i++) {
        cout << "SCC " << i << ": ";
        for (int v : sccs[i]) cout << v << " ";
        cout << endl;
    }
    
    auto cond = g.buildCondensation();
    cout << "\nCondensation graph edges:" << endl;
    for (int i = 0; i < cond.size(); i++) {
        for (int j : cond[i]) {
            cout << i << " -> " << j << endl;
        }
    }
    
    return 0;
}









