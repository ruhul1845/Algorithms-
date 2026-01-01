/*
    Heavy-Light Decomposition
    - Decompose tree into heavy and light chains
    - Path queries/updates in O(log² n)
*/

#include <bits/stdc++.h>
using namespace std;

class HLD {
public:
    int n, timer;
    vector<vector<int>> adj;
    vector<int> parent, depth, heavy, head, pos, subtreeSize;
    vector<long long> segTree;
    
    HLD(int n) : n(n), timer(0), adj(n), parent(n), depth(n), 
                 heavy(n, -1), head(n), pos(n), subtreeSize(n), segTree(4 * n, 0) {}
    
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    int dfs(int v, int p = -1, int d = 0) {
        parent[v] = p;
        depth[v] = d;
        subtreeSize[v] = 1;
        int maxChildSize = 0;
        
        for (int child : adj[v]) {
            if (child != p) {
                subtreeSize[v] += dfs(child, v, d + 1);
                if (subtreeSize[child] > maxChildSize) {
                    maxChildSize = subtreeSize[child];
                    heavy[v] = child;
                }
            }
        }
        return subtreeSize[v];
    }
    
    void decompose(int v, int h, int p = -1) {
        head[v] = h;
        pos[v] = timer++;
        
        if (heavy[v] != -1) {
            decompose(heavy[v], h, v);
        }
        
        for (int child : adj[v]) {
            if (child != p && child != heavy[v]) {
                decompose(child, child, v);
            }
        }
    }
    
    void build(int root = 0) {
        dfs(root);
        decompose(root, root);
    }
    
    // Segment tree operations
    void update(int node, int start, int end, int idx, long long val) {
        if (start == end) {
            segTree[node] = val;
        } else {
            int mid = (start + end) / 2;
            if (idx <= mid) update(2*node, start, mid, idx, val);
            else update(2*node+1, mid+1, end, idx, val);
            segTree[node] = segTree[2*node] + segTree[2*node+1];
        }
    }
    
    long long query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) return 0;
        if (l <= start && end <= r) return segTree[node];
        int mid = (start + end) / 2;
        return query(2*node, start, mid, l, r) + query(2*node+1, mid+1, end, l, r);
    }
    
    // Update node value
    void updateNode(int v, long long val) {
        update(1, 0, n-1, pos[v], val);
    }
    
    // Query path from u to v
    long long queryPath(int u, int v) {
        long long result = 0;
        
        while (head[u] != head[v]) {
            if (depth[head[u]] < depth[head[v]]) swap(u, v);
            result += query(1, 0, n-1, pos[head[u]], pos[u]);
            u = parent[head[u]];
        }
        
        if (depth[u] > depth[v]) swap(u, v);
        result += query(1, 0, n-1, pos[u], pos[v]);
        
        return result;
    }
    
    // Query subtree
    long long querySubtree(int v) {
        return query(1, 0, n-1, pos[v], pos[v] + subtreeSize[v] - 1);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cout << "=== Heavy-Light Decomposition Demo ===" << endl;
    
    HLD hld(7);
    hld.addEdge(0, 1);
    hld.addEdge(0, 2);
    hld.addEdge(1, 3);
    hld.addEdge(1, 4);
    hld.addEdge(2, 5);
    hld.addEdge(2, 6);
    
    hld.build(0);
    
    // Set node values
    vector<int> values = {1, 2, 3, 4, 5, 6, 7};
    for (int i = 0; i < 7; i++) {
        hld.updateNode(i, values[i]);
    }
    
    cout << "Path sum (3 to 6): " << hld.queryPath(3, 6) << endl;
    cout << "Path sum (4 to 5): " << hld.queryPath(4, 5) << endl;
    cout << "Subtree sum at 1: " << hld.querySubtree(1) << endl;
    
    hld.updateNode(3, 10);
    cout << "\nAfter updating node 3 to 10:" << endl;
    cout << "Path sum (3 to 6): " << hld.queryPath(3, 6) << endl;
    
    return 0;
}







