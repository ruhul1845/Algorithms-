/*
    Bipartite Matching - Hungarian Algorithm / Hopcroft-Karp
    - Maximum matching in bipartite graph
    - Time: O(E * sqrt(V)) Hopcroft-Karp
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== Hungarian Algorithm (Kuhn's) ====================
class HungarianMatching {
public:
    int n, m;
    vector<vector<int>> adj;
    vector<int> match;
    vector<bool> used;
    
    HungarianMatching(int left, int right) : n(left), m(right), adj(left), match(right, -1) {}
    
    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }
    
    bool dfs(int v) {
        for (int to : adj[v]) {
            if (used[to]) continue;
            used[to] = true;
            
            if (match[to] == -1 || dfs(match[to])) {
                match[to] = v;
                return true;
            }
        }
        return false;
    }
    
    int maxMatching() {
        int result = 0;
        for (int v = 0; v < n; v++) {
            used.assign(m, false);
            if (dfs(v)) result++;
        }
        return result;
    }
    
    vector<pair<int, int>> getMatching() {
        maxMatching();
        vector<pair<int, int>> edges;
        for (int i = 0; i < m; i++) {
            if (match[i] != -1) {
                edges.push_back({match[i], i});
            }
        }
        return edges;
    }
};

// ==================== Hopcroft-Karp Algorithm ====================
class HopcroftKarp {
public:
    int n, m;
    vector<vector<int>> adj;
    vector<int> matchL, matchR, dist;
    
    HopcroftKarp(int left, int right) : n(left), m(right), adj(left), 
                                         matchL(left, -1), matchR(right, -1), dist(left) {}
    
    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }
    
    bool bfs() {
        queue<int> q;
        for (int u = 0; u < n; u++) {
            if (matchL[u] == -1) {
                dist[u] = 0;
                q.push(u);
            } else {
                dist[u] = INT_MAX;
            }
        }
        
        bool found = false;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            
            for (int v : adj[u]) {
                if (matchR[v] == -1) {
                    found = true;
                } else if (dist[matchR[v]] == INT_MAX) {
                    dist[matchR[v]] = dist[u] + 1;
                    q.push(matchR[v]);
                }
            }
        }
        return found;
    }
    
    bool dfs(int u) {
        for (int v : adj[u]) {
            if (matchR[v] == -1 || (dist[matchR[v]] == dist[u] + 1 && dfs(matchR[v]))) {
                matchL[u] = v;
                matchR[v] = u;
                return true;
            }
        }
        dist[u] = INT_MAX;
        return false;
    }
    
    int maxMatching() {
        int result = 0;
        while (bfs()) {
            for (int u = 0; u < n; u++) {
                if (matchL[u] == -1 && dfs(u)) {
                    result++;
                }
            }
        }
        return result;
    }
};

// ==================== Minimum Vertex Cover ====================
// König's theorem: In bipartite graph, max matching = min vertex cover
class MinVertexCover {
public:
    vector<int> findMinVertexCover(int n, int m, vector<pair<int, int>>& edges) {
        HungarianMatching hm(n, m);
        vector<vector<int>> adj(n);
        
        for (auto& [u, v] : edges) {
            hm.addEdge(u, v);
            adj[u].push_back(v);
        }
        
        hm.maxMatching();
        
        // Find unmatched vertices on left
        vector<bool> matchedLeft(n, false);
        for (int i = 0; i < m; i++) {
            if (hm.match[i] != -1) matchedLeft[hm.match[i]] = true;
        }
        
        // BFS from unmatched left vertices
        vector<bool> reachableL(n, false), reachableR(m, false);
        queue<int> q;
        
        for (int i = 0; i < n; i++) {
            if (!matchedLeft[i]) {
                q.push(i);
                reachableL[i] = true;
            }
        }
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            
            for (int v : adj[u]) {
                if (!reachableR[v]) {
                    reachableR[v] = true;
                    if (hm.match[v] != -1 && !reachableL[hm.match[v]]) {
                        reachableL[hm.match[v]] = true;
                        q.push(hm.match[v]);
                    }
                }
            }
        }
        
        // Vertex cover: unreachable left + reachable right
        vector<int> cover;
        for (int i = 0; i < n; i++) {
            if (!reachableL[i]) cover.push_back(i);
        }
        for (int i = 0; i < m; i++) {
            if (reachableR[i]) cover.push_back(n + i);
        }
        
        return cover;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cout << "=== Bipartite Matching Demo ===" << endl;
    
    // Hungarian Algorithm
    HungarianMatching hm(4, 4);
    hm.addEdge(0, 0);
    hm.addEdge(0, 1);
    hm.addEdge(1, 0);
    hm.addEdge(2, 1);
    hm.addEdge(2, 2);
    hm.addEdge(3, 2);
    hm.addEdge(3, 3);
    
    cout << "Max Matching (Hungarian): " << hm.maxMatching() << endl;
    
    auto matching = hm.getMatching();
    cout << "Matching edges: ";
    for (auto& [u, v] : matching) {
        cout << "(" << u << "-" << v << ") ";
    }
    cout << endl;
    
    // Hopcroft-Karp
    HopcroftKarp hk(4, 4);
    hk.addEdge(0, 0);
    hk.addEdge(0, 1);
    hk.addEdge(1, 0);
    hk.addEdge(2, 1);
    hk.addEdge(2, 2);
    hk.addEdge(3, 2);
    hk.addEdge(3, 3);
    
    cout << "Max Matching (Hopcroft-Karp): " << hk.maxMatching() << endl;
    
    return 0;
}

