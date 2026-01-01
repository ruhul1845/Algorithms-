/*
    Dinic's Algorithm - Maximum Flow
    - Faster than Ford-Fulkerson for dense graphs
    - Uses level graph and blocking flow
    - Time: O(V² * E)
*/

#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to, cap, flow;
};

class Dinic {
public:
    int V;
    vector<Edge> edges;
    vector<vector<int>> adj;
    vector<int> level, ptr;
    
    Dinic(int v) : V(v), adj(v), level(v), ptr(v) {}
    
    void addEdge(int from, int to, int cap) {
        adj[from].push_back(edges.size());
        edges.push_back({to, cap, 0});
        adj[to].push_back(edges.size());
        edges.push_back({from, 0, 0}); // Reverse edge
    }
    
    // Build level graph using BFS
    bool bfs(int source, int sink) {
        fill(level.begin(), level.end(), -1);
        level[source] = 0;
        
        queue<int> q;
        q.push(source);
        
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            
            for (int id : adj[node]) {
                if (level[edges[id].to] == -1 && edges[id].cap > edges[id].flow) {
                    level[edges[id].to] = level[node] + 1;
                    q.push(edges[id].to);
                }
            }
        }
        
        return level[sink] != -1;
    }
    
    // Find blocking flow using DFS
    int dfs(int node, int sink, int pushed) {
        if (node == sink || pushed == 0) return pushed;
        
        for (int& cid = ptr[node]; cid < adj[node].size(); cid++) {
            int id = adj[node][cid];
            int to = edges[id].to;
            
            if (level[node] + 1 != level[to] || edges[id].cap <= edges[id].flow) {
                continue;
            }
            
            int tr = dfs(to, sink, min(pushed, edges[id].cap - edges[id].flow));
            if (tr > 0) {
                edges[id].flow += tr;
                edges[id ^ 1].flow -= tr;
                return tr;
            }
        }
        
        return 0;
    }
    
    // Calculate maximum flow
    long long maxflow(int source, int sink) {
        long long flow = 0;
        
        while (bfs(source, sink)) {
            fill(ptr.begin(), ptr.end(), 0);
            while (int pushed = dfs(source, sink, INT_MAX)) {
                flow += pushed;
            }
        }
        
        return flow;
    }
    
    // Get flow on each edge
    vector<tuple<int, int, int, int>> getFlowEdges() {
        vector<tuple<int, int, int, int>> result;
        for (int i = 0; i < edges.size(); i += 2) {
            int from = edges[i + 1].to;
            int to = edges[i].to;
            int cap = edges[i].cap;
            int flow = edges[i].flow;
            if (flow > 0) {
                result.push_back({from, to, flow, cap});
            }
        }
        return result;
    }
};

// ==================== Min Cost Max Flow ====================
class MinCostMaxFlow {
public:
    struct Edge {
        int to, cap, cost, flow;
    };
    
    int V;
    vector<Edge> edges;
    vector<vector<int>> adj;
    vector<int> dist, parent, parentEdge;
    vector<bool> inQueue;
    
    MinCostMaxFlow(int v) : V(v), adj(v), dist(v), parent(v), 
                            parentEdge(v), inQueue(v) {}
    
    void addEdge(int from, int to, int cap, int cost) {
        adj[from].push_back(edges.size());
        edges.push_back({to, cap, cost, 0});
        adj[to].push_back(edges.size());
        edges.push_back({from, 0, -cost, 0});
    }
    
    bool spfa(int source, int sink) {
        fill(dist.begin(), dist.end(), INT_MAX);
        fill(inQueue.begin(), inQueue.end(), false);
        
        dist[source] = 0;
        queue<int> q;
        q.push(source);
        inQueue[source] = true;
        
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            inQueue[node] = false;
            
            for (int id : adj[node]) {
                if (edges[id].cap > edges[id].flow && 
                    dist[node] + edges[id].cost < dist[edges[id].to]) {
                    dist[edges[id].to] = dist[node] + edges[id].cost;
                    parent[edges[id].to] = node;
                    parentEdge[edges[id].to] = id;
                    
                    if (!inQueue[edges[id].to]) {
                        q.push(edges[id].to);
                        inQueue[edges[id].to] = true;
                    }
                }
            }
        }
        
        return dist[sink] != INT_MAX;
    }
    
    pair<int, int> minCostFlow(int source, int sink, int maxFlow = INT_MAX) {
        int flow = 0, cost = 0;
        
        while (flow < maxFlow && spfa(source, sink)) {
            // Find min capacity along path
            int pushFlow = maxFlow - flow;
            int curr = sink;
            while (curr != source) {
                pushFlow = min(pushFlow, 
                              edges[parentEdge[curr]].cap - edges[parentEdge[curr]].flow);
                curr = parent[curr];
            }
            
            // Update flow along path
            curr = sink;
            while (curr != source) {
                edges[parentEdge[curr]].flow += pushFlow;
                edges[parentEdge[curr] ^ 1].flow -= pushFlow;
                curr = parent[curr];
            }
            
            flow += pushFlow;
            cost += pushFlow * dist[sink];
        }
        
        return {flow, cost};
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cout << "=== Dinic's Algorithm Demo ===" << endl;
    
    Dinic d(6);
    d.addEdge(0, 1, 16);
    d.addEdge(0, 2, 13);
    d.addEdge(1, 2, 10);
    d.addEdge(1, 3, 12);
    d.addEdge(2, 1, 4);
    d.addEdge(2, 4, 14);
    d.addEdge(3, 2, 9);
    d.addEdge(3, 5, 20);
    d.addEdge(4, 3, 7);
    d.addEdge(4, 5, 4);
    
    cout << "Maximum Flow: " << d.maxflow(0, 5) << endl;
    
    cout << "\nFlow on edges:" << endl;
    auto flowEdges = d.getFlowEdges();
    for (auto& [from, to, flow, cap] : flowEdges) {
        cout << from << " -> " << to << ": " << flow << "/" << cap << endl;
    }
    
    // Min Cost Max Flow
    cout << "\n=== Min Cost Max Flow Demo ===" << endl;
    MinCostMaxFlow mcmf(4);
    mcmf.addEdge(0, 1, 2, 1);
    mcmf.addEdge(0, 2, 1, 2);
    mcmf.addEdge(1, 2, 1, 1);
    mcmf.addEdge(1, 3, 1, 3);
    mcmf.addEdge(2, 3, 2, 1);
    
    auto [flow, cost] = mcmf.minCostFlow(0, 3);
    cout << "Max Flow: " << flow << ", Min Cost: " << cost << endl;
    
    return 0;
}







