/*
    Minimum Spanning Arborescence (Directed MST)
    - Edmonds' Algorithm (Chu-Liu/Edmonds)
    - Time: O(VE)
*/

#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;

class MinimumArborescence {
public:
    struct Edge {
        int from, to;
        long long cost;
    };
    
    int n;
    vector<Edge> edges;
    
    MinimumArborescence(int n) : n(n) {}
    
    void addEdge(int from, int to, long long cost) {
        edges.push_back({from, to, cost});
    }
    
    // Find minimum cost arborescence rooted at 'root'
    long long solve(int root) {
        long long result = 0;
        vector<int> id(n), prev(n), visited(n);
        
        while (true) {
            // Step 1: Find minimum incoming edge for each non-root vertex
            fill(prev.begin(), prev.end(), -1);
            vector<long long> minCost(n, INF);
            
            for (auto& e : edges) {
                if (e.from != e.to && e.cost < minCost[e.to]) {
                    minCost[e.to] = e.cost;
                    prev[e.to] = e.from;
                }
            }
            
            // Check if all vertices are reachable
            for (int i = 0; i < n; i++) {
                if (i != root && prev[i] == -1) return -1;
            }
            
            // Step 2: Find cycles
            int cycleCount = 0;
            fill(id.begin(), id.end(), -1);
            fill(visited.begin(), visited.end(), -1);
            
            for (int i = 0; i < n; i++) {
                if (i == root) continue;
                result += minCost[i];
                
                int v = i;
                while (visited[v] == -1 && id[v] == -1 && v != root) {
                    visited[v] = i;
                    v = prev[v];
                }
                
                if (v != root && id[v] == -1 && visited[v] == i) {
                    // Found a cycle
                    for (int u = prev[v]; u != v; u = prev[u]) {
                        id[u] = cycleCount;
                    }
                    id[v] = cycleCount++;
                }
            }
            
            if (cycleCount == 0) break;
            
            // Assign remaining vertices to singleton components
            for (int i = 0; i < n; i++) {
                if (id[i] == -1) id[i] = cycleCount++;
            }
            
            // Step 3: Contract cycles and update edges
            for (auto& e : edges) {
                int u = id[e.from], v = id[e.to];
                if (u != v) {
                    e.cost -= minCost[e.to];
                }
                e.from = u;
                e.to = v;
            }
            
            n = cycleCount;
            root = id[root];
        }
        
        return result;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cout << "=== Minimum Spanning Arborescence Demo ===" << endl;
    
    MinimumArborescence g(4);
    g.addEdge(0, 1, 1);
    g.addEdge(0, 2, 2);
    g.addEdge(0, 3, 3);
    g.addEdge(1, 2, 4);
    g.addEdge(2, 1, 5);
    g.addEdge(2, 3, 6);
    g.addEdge(3, 0, 7);
    
    long long cost = g.solve(0);
    cout << "Minimum arborescence cost: " << cost << endl;
    
    return 0;
}







