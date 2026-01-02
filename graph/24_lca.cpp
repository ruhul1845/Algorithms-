/*
    Lowest Common Ancestor (LCA)
    - Binary Lifting
    - Euler Tour + RMQ
    - Time: O(log n) per query after O(n log n) preprocessing
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== Binary Lifting ====================
class LCA_BinaryLifting {
public:
    int n, LOG;
    vector<vector<int>> adj;
    vector<vector<int>> up; // up[i][j] = 2^j-th ancestor of i
    vector<int> depth;
    
    LCA_BinaryLifting(int n) : n(n), adj(n) {
        LOG = log2(n) + 1;
        up.assign(n, vector<int>(LOG, -1));
        depth.assign(n, 0);
    }
    
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    void preprocess(int root = 0) {
        dfs(root, -1);
    }
    
    void dfs(int node, int parent) {
        up[node][0] = parent;
        for (int j = 1; j < LOG; j++) {
            if (up[node][j-1] != -1) {
                up[node][j] = up[up[node][j-1]][j-1];
            }
        }
        
        for (int child : adj[node]) {
            if (child != parent) {
                depth[child] = depth[node] + 1;
                dfs(child, node);
            }
        }
    }
    
    int lca(int u, int v) {
        if (depth[u] < depth[v]) swap(u, v);
        
        int diff = depth[u] - depth[v];
        for (int j = 0; j < LOG; j++) {
            if ((diff >> j) & 1) {
                u = up[u][j];
            }
        }
        
        if (u == v) return u;
        
        for (int j = LOG - 1; j >= 0; j--) {
            if (up[u][j] != up[v][j]) {
                u = up[u][j];
                v = up[v][j];
            }
        }
        
        return up[u][0];
    }
    
    int distance(int u, int v) {
        return depth[u] + depth[v] - 2 * depth[lca(u, v)];
    }
    
    int kthAncestor(int node, int k) {
        for (int j = 0; j < LOG && node != -1; j++) {
            if ((k >> j) & 1) {
                node = up[node][j];
            }
        }
        return node;
    }
};

// ==================== Euler Tour + Sparse Table ====================
class LCA_SparseTable {
public:
    int n, LOG;
    vector<vector<int>> adj;
    vector<int> euler, first, depth;
    vector<vector<int>> sparse; // min depth in range
    vector<vector<int>> sparseIdx; // index of min
    
    LCA_SparseTable(int n) : n(n), adj(n), first(n, -1) {
        LOG = 20;
    }
    
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    void preprocess(int root = 0) {
        dfs(root, -1, 0);
        buildSparseTable();
    }
    
    void dfs(int node, int parent, int d) {
        first[node] = euler.size();
        euler.push_back(node);
        depth.push_back(d);
        
        for (int child : adj[node]) {
            if (child != parent) {
                dfs(child, node, d + 1);
                euler.push_back(node);
                depth.push_back(d);
            }
        }
    }
    
    void buildSparseTable() {
        int m = depth.size();
        sparse.assign(LOG, vector<int>(m));
        sparseIdx.assign(LOG, vector<int>(m));
        
        for (int i = 0; i < m; i++) {
            sparse[0][i] = depth[i];
            sparseIdx[0][i] = i;
        }
        
        for (int j = 1; j < LOG; j++) {
            for (int i = 0; i + (1 << j) <= m; i++) {
                if (sparse[j-1][i] < sparse[j-1][i + (1 << (j-1))]) {
                    sparse[j][i] = sparse[j-1][i];
                    sparseIdx[j][i] = sparseIdx[j-1][i];
                } else {
                    sparse[j][i] = sparse[j-1][i + (1 << (j-1))];
                    sparseIdx[j][i] = sparseIdx[j-1][i + (1 << (j-1))];
                }
            }
        }
    }
    
    int lca(int u, int v) {
        int l = first[u], r = first[v];
        if (l > r) swap(l, r);
        
        int len = r - l + 1;
        int k = log2(len);
        
        if (sparse[k][l] < sparse[k][r - (1 << k) + 1]) {
            return euler[sparseIdx[k][l]];
        }
        return euler[sparseIdx[k][r - (1 << k) + 1]];
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cout << "=== LCA Demo ===" << endl;
    
    // Binary Lifting
    LCA_BinaryLifting lca1(7);
    lca1.addEdge(0, 1);
    lca1.addEdge(0, 2);
    lca1.addEdge(1, 3);
    lca1.addEdge(1, 4);
    lca1.addEdge(2, 5);
    lca1.addEdge(2, 6);
    lca1.preprocess(0);
    
    cout << "Binary Lifting:" << endl;
    cout << "LCA(3, 4) = " << lca1.lca(3, 4) << endl;
    cout << "LCA(3, 6) = " << lca1.lca(3, 6) << endl;
    cout << "LCA(4, 5) = " << lca1.lca(4, 5) << endl;
    cout << "Distance(3, 6) = " << lca1.distance(3, 6) << endl;
    cout << "2nd ancestor of 3 = " << lca1.kthAncestor(3, 2) << endl;
    
    // Sparse Table
    LCA_SparseTable lca2(7);
    lca2.addEdge(0, 1);
    lca2.addEdge(0, 2);
    lca2.addEdge(1, 3);
    lca2.addEdge(1, 4);
    lca2.addEdge(2, 5);
    lca2.addEdge(2, 6);
    lca2.preprocess(0);
    
    cout << "\nSparse Table:" << endl;
    cout << "LCA(3, 4) = " << lca2.lca(3, 4) << endl;
    cout << "LCA(3, 6) = " << lca2.lca(3, 6) << endl;
    
    return 0;
}









