/*
    Union-Find (Disjoint Set Union)
    - Path compression + Union by rank
    - Time: O(α(n)) amortized per operation
*/

#include <bits/stdc++.h>
using namespace std;

class DSU {
public:
    vector<int> parent, rank_, size_;
    int components;
    
    DSU(int n) : parent(n), rank_(n, 0), size_(n, 1), components(n) {
        iota(parent.begin(), parent.end(), 0);
    }
    
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]); // Path compression
        }
        return parent[x];
    }
    
    bool unite(int x, int y) {
        int px = find(x), py = find(y);
        if (px == py) return false;
        
        // Union by rank
        if (rank_[px] < rank_[py]) swap(px, py);
        parent[py] = px;
        size_[px] += size_[py];
        if (rank_[px] == rank_[py]) rank_[px]++;
        components--;
        return true;
    }
    
    bool connected(int x, int y) { return find(x) == find(y); }
    int getSize(int x) { return size_[find(x)]; }
    int getComponents() { return components; }
};

// ==================== Weighted DSU ====================
class WeightedDSU {
public:
    vector<int> parent;
    vector<long long> weight; // weight[i] = weight from i to parent[i]
    
    WeightedDSU(int n) : parent(n), weight(n, 0) {
        iota(parent.begin(), parent.end(), 0);
    }
    
    pair<int, long long> find(int x) {
        if (parent[x] == x) return {x, 0};
        auto [root, w] = find(parent[x]);
        parent[x] = root;
        weight[x] += w;
        return {root, weight[x]};
    }
    
    // Set weight[y] - weight[x] = w
    bool unite(int x, int y, long long w) {
        auto [px, wx] = find(x);
        auto [py, wy] = find(y);
        if (px == py) return wx - wy == w;
        parent[px] = py;
        weight[px] = wy - wx + w;
        return true;
    }
};

// ==================== Number of Connected Components ====================
int countComponents(int n, vector<vector<int>>& edges) {
    DSU dsu(n);
    for (auto& e : edges) dsu.unite(e[0], e[1]);
    return dsu.getComponents();
}

// ==================== Redundant Connection ====================
vector<int> findRedundantConnection(vector<vector<int>>& edges) {
    int n = edges.size();
    DSU dsu(n + 1);
    for (auto& e : edges) {
        if (!dsu.unite(e[0], e[1])) return e;
    }
    return {};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cout << "=== Union-Find Demo ===" << endl;
    
    DSU dsu(6);
    dsu.unite(0, 1);
    dsu.unite(1, 2);
    dsu.unite(3, 4);
    
    cout << "Components: " << dsu.getComponents() << endl;
    cout << "0 and 2 connected: " << (dsu.connected(0, 2) ? "Yes" : "No") << endl;
    cout << "0 and 3 connected: " << (dsu.connected(0, 3) ? "Yes" : "No") << endl;
    cout << "Size of 0's component: " << dsu.getSize(0) << endl;
    
    dsu.unite(2, 3);
    cout << "\nAfter uniting 2 and 3:" << endl;
    cout << "Components: " << dsu.getComponents() << endl;
    cout << "0 and 4 connected: " << (dsu.connected(0, 4) ? "Yes" : "No") << endl;
    
    // Redundant Connection
    cout << "\n=== Redundant Connection ===" << endl;
    vector<vector<int>> edges = {{1,2},{1,3},{2,3}};
    auto redundant = findRedundantConnection(edges);
    cout << "Redundant: " << redundant[0] << " - " << redundant[1] << endl;
    
    return 0;
}

