/*
    Floyd-Warshall Algorithm
    - All pairs shortest path
    - Works with negative weights (but no negative cycles)
    - Time: O(V³), Space: O(V²)
*/

#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;

class FloydWarshall {
public:
    int V;
    vector<vector<long long>> dist;
    vector<vector<int>> next; // For path reconstruction
    
    FloydWarshall(int v) : V(v), dist(v, vector<long long>(v, INF)), 
                           next(v, vector<int>(v, -1)) {
        for (int i = 0; i < V; i++) {
            dist[i][i] = 0;
        }
    }
    
    void addEdge(int u, int v, long long w, bool directed = true) {
        dist[u][v] = min(dist[u][v], w);
        next[u][v] = v;
        if (!directed) {
            dist[v][u] = min(dist[v][u], w);
            next[v][u] = u;
        }
    }
    
    // ==================== Basic Floyd-Warshall ====================
    bool compute() {
        for (int k = 0; k < V; k++) {
            for (int i = 0; i < V; i++) {
                for (int j = 0; j < V; j++) {
                    if (dist[i][k] < INF && dist[k][j] < INF) {
                        if (dist[i][k] + dist[k][j] < dist[i][j]) {
                            dist[i][j] = dist[i][k] + dist[k][j];
                            next[i][j] = next[i][k];
                        }
                    }
                }
            }
        }
        
        // Check for negative cycles
        for (int i = 0; i < V; i++) {
            if (dist[i][i] < 0) return false;
        }
        return true;
    }
    
    // ==================== Get Shortest Distance ====================
    long long getDistance(int u, int v) {
        return dist[u][v];
    }
    
    // ==================== Get Shortest Path ====================
    vector<int> getPath(int u, int v) {
        vector<int> path;
        if (dist[u][v] == INF) return path;
        
        path.push_back(u);
        while (u != v) {
            u = next[u][v];
            path.push_back(u);
        }
        return path;
    }
    
    // ==================== Print Distance Matrix ====================
    void printDistances() {
        cout << "Distance Matrix:" << endl;
        cout << "    ";
        for (int i = 0; i < V; i++) cout << setw(5) << i;
        cout << endl;
        
        for (int i = 0; i < V; i++) {
            cout << setw(3) << i << " ";
            for (int j = 0; j < V; j++) {
                if (dist[i][j] == INF) {
                    cout << setw(5) << "INF";
                } else {
                    cout << setw(5) << dist[i][j];
                }
            }
            cout << endl;
        }
    }
    
    // ==================== Transitive Closure ====================
    vector<vector<bool>> transitiveClosure() {
        vector<vector<bool>> reach(V, vector<bool>(V, false));
        
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                reach[i][j] = (dist[i][j] < INF);
            }
        }
        
        return reach;
    }
    
    // ==================== Find Negative Cycles ====================
    vector<int> findNegativeCycleNodes() {
        vector<int> negCycleNodes;
        for (int i = 0; i < V; i++) {
            if (dist[i][i] < 0) {
                negCycleNodes.push_back(i);
            }
        }
        return negCycleNodes;
    }
    
    // ==================== Diameter of Graph ====================
    long long getDiameter() {
        long long diameter = 0;
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][j] < INF) {
                    diameter = max(diameter, dist[i][j]);
                }
            }
        }
        return diameter;
    }
};

// ==================== Min-Cost to Connect Cities ====================
class CityConnector {
public:
    int solve(int n, vector<vector<int>>& costs) {
        vector<vector<long long>> dist(n, vector<long long>(n, INF));
        
        for (int i = 0; i < n; i++) dist[i][i] = 0;
        
        for (auto& cost : costs) {
            int u = cost[0] - 1, v = cost[1] - 1, w = cost[2];
            dist[u][v] = min(dist[u][v], (long long)w);
            dist[v][u] = min(dist[v][u], (long long)w);
        }
        
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
        
        // Check if all cities are connected
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][j] == INF) return -1;
            }
        }
        
        return 0; // All connected
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cout << "=== Floyd-Warshall Algorithm Demo ===" << endl;
    
    FloydWarshall fw(4);
    fw.addEdge(0, 1, 3);
    fw.addEdge(0, 3, 5);
    fw.addEdge(1, 0, 2);
    fw.addEdge(1, 3, 4);
    fw.addEdge(2, 1, 1);
    fw.addEdge(3, 2, 2);
    
    bool noNegCycle = fw.compute();
    
    if (!noNegCycle) {
        cout << "Negative cycle detected!" << endl;
    } else {
        fw.printDistances();
        
        // Get specific path
        cout << "\nShortest path from 0 to 2:" << endl;
        vector<int> path = fw.getPath(0, 2);
        cout << "Path: ";
        for (int node : path) cout << node << " ";
        cout << "\nDistance: " << fw.getDistance(0, 2) << endl;
        
        // Diameter
        cout << "\nGraph diameter: " << fw.getDiameter() << endl;
        
        // Transitive closure
        cout << "\nTransitive Closure:" << endl;
        auto reach = fw.transitiveClosure();
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                cout << reach[i][j] << " ";
            }
            cout << endl;
        }
    }
    
    // Graph with negative cycle
    cout << "\n=== Graph with Negative Cycle ===" << endl;
    FloydWarshall fw2(3);
    fw2.addEdge(0, 1, 1);
    fw2.addEdge(1, 2, -3);
    fw2.addEdge(2, 0, 1);
    
    if (!fw2.compute()) {
        cout << "Negative cycle detected!" << endl;
        vector<int> negNodes = fw2.findNegativeCycleNodes();
        cout << "Nodes in negative cycle path: ";
        for (int node : negNodes) cout << node << " ";
        cout << endl;
    }
    
    return 0;
}







