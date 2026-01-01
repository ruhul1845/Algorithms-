/*
    Centroid Decomposition
    - Divide and conquer on trees
    - Time: O(n log n) for building
*/

#include <bits/stdc++.h>
using namespace std;

class CentroidDecomposition {
public:
    int n;
    vector<vector<int>> adj;
    vector<int> subtreeSize;
    vector<bool> removed;
    vector<int> centroidParent;
    
    CentroidDecomposition(int n) : n(n), adj(n), subtreeSize(n), 
                                   removed(n, false), centroidParent(n, -1) {}
    
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    // Calculate subtree sizes
    int getSize(int node, int parent) {
        subtreeSize[node] = 1;
        for (int child : adj[node]) {
            if (child != parent && !removed[child]) {
                subtreeSize[node] += getSize(child, node);
            }
        }
        return subtreeSize[node];
    }
    
    // Find centroid of subtree
    int getCentroid(int node, int parent, int treeSize) {
        for (int child : adj[node]) {
            if (child != parent && !removed[child]) {
                if (subtreeSize[child] > treeSize / 2) {
                    return getCentroid(child, node, treeSize);
                }
            }
        }
        return node;
    }
    
    // Build centroid decomposition
    int build(int node, int parent = -1) {
        int treeSize = getSize(node, -1);
        int centroid = getCentroid(node, -1, treeSize);
        
        removed[centroid] = true;
        centroidParent[centroid] = parent;
        
        for (int child : adj[centroid]) {
            if (!removed[child]) {
                build(child, centroid);
            }
        }
        
        return centroid;
    }
    
    // Get path to centroid root
    vector<int> getPathToCentroidRoot(int node) {
        vector<int> path;
        int curr = node;
        while (curr != -1) {
            path.push_back(curr);
            curr = centroidParent[curr];
        }
        return path;
    }
};

// ==================== Distance Query with Centroid Decomposition ====================
class TreeDistanceQuery {
public:
    int n;
    CentroidDecomposition cd;
    vector<vector<int>> adj;
    vector<map<int, int>> distFromCentroid; // distance to each centroid ancestor
    
    TreeDistanceQuery(int n) : n(n), cd(n), adj(n), distFromCentroid(n) {}
    
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
        cd.addEdge(u, v);
    }
    
    int bfsDistance(int start, int end) {
        if (start == end) return 0;
        vector<int> dist(n, -1);
        queue<int> q;
        q.push(start);
        dist[start] = 0;
        
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            
            for (int neighbor : adj[node]) {
                if (dist[neighbor] == -1) {
                    dist[neighbor] = dist[node] + 1;
                    if (neighbor == end) return dist[neighbor];
                    q.push(neighbor);
                }
            }
        }
        return -1;
    }
    
    void build() {
        cd.build(0);
        
        // Precompute distances to centroid ancestors
        for (int i = 0; i < n; i++) {
            int curr = i;
            while (curr != -1) {
                distFromCentroid[i][curr] = bfsDistance(i, curr);
                curr = cd.centroidParent[curr];
            }
        }
    }
    
    // Query distance using centroid decomposition
    int query(int u, int v) {
        int minDist = INT_MAX;
        int curr = u;
        
        while (curr != -1) {
            if (distFromCentroid[v].count(curr)) {
                minDist = min(minDist, distFromCentroid[u][curr] + distFromCentroid[v][curr]);
            }
            curr = cd.centroidParent[curr];
        }
        
        return minDist;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cout << "=== Centroid Decomposition Demo ===" << endl;
    
    CentroidDecomposition cd(7);
    cd.addEdge(0, 1);
    cd.addEdge(0, 2);
    cd.addEdge(1, 3);
    cd.addEdge(1, 4);
    cd.addEdge(2, 5);
    cd.addEdge(2, 6);
    
    int root = cd.build(0);
    cout << "Centroid decomposition root: " << root << endl;
    
    cout << "Centroid parents:" << endl;
    for (int i = 0; i < 7; i++) {
        cout << i << " -> " << cd.centroidParent[i] << endl;
    }
    
    // Distance queries
    cout << "\n=== Distance Queries ===" << endl;
    TreeDistanceQuery tdq(7);
    tdq.addEdge(0, 1);
    tdq.addEdge(0, 2);
    tdq.addEdge(1, 3);
    tdq.addEdge(1, 4);
    tdq.addEdge(2, 5);
    tdq.addEdge(2, 6);
    tdq.build();
    
    cout << "Distance(3, 6) = " << tdq.query(3, 6) << endl;
    cout << "Distance(4, 5) = " << tdq.query(4, 5) << endl;
    
    return 0;
}







