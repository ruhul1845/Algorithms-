/*
    Graph Representation
    - Adjacency List (most common for sparse graphs)
    - Adjacency Matrix (good for dense graphs)
    - Edge List
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== ADJACENCY LIST ====================
class AdjacencyList {
public:
    int V;
    vector<vector<int>> adj;           // Unweighted
    vector<vector<pair<int, int>>> adjW; // Weighted {neighbor, weight}
    
    AdjacencyList(int v) : V(v), adj(v), adjW(v) {}
    
    // Unweighted graph
    void addEdge(int u, int v, bool directed = false) {
        adj[u].push_back(v);
        if (!directed) adj[v].push_back(u);
    }
    
    // Weighted graph
    void addEdgeWeighted(int u, int v, int w, bool directed = false) {
        adjW[u].push_back({v, w});
        if (!directed) adjW[v].push_back({u, w});
    }
    
    void printGraph() {
        cout << "Adjacency List:" << endl;
        for (int i = 0; i < V; i++) {
            cout << i << " -> ";
            for (int neighbor : adj[i]) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }
    
    void printWeightedGraph() {
        cout << "Weighted Adjacency List:" << endl;
        for (int i = 0; i < V; i++) {
            cout << i << " -> ";
            for (auto& [neighbor, weight] : adjW[i]) {
                cout << "(" << neighbor << "," << weight << ") ";
            }
            cout << endl;
        }
    }
};

// ==================== ADJACENCY MATRIX ====================
class AdjacencyMatrix {
public:
    int V;
    vector<vector<int>> matrix;
    
    AdjacencyMatrix(int v) : V(v), matrix(v, vector<int>(v, 0)) {}
    
    void addEdge(int u, int v, int w = 1, bool directed = false) {
        matrix[u][v] = w;
        if (!directed) matrix[v][u] = w;
    }
    
    bool hasEdge(int u, int v) {
        return matrix[u][v] != 0;
    }
    
    void printMatrix() {
        cout << "Adjacency Matrix:" << endl;
        cout << "  ";
        for (int i = 0; i < V; i++) cout << i << " ";
        cout << endl;
        
        for (int i = 0; i < V; i++) {
            cout << i << " ";
            for (int j = 0; j < V; j++) {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
    }
};

// ==================== EDGE LIST ====================
class EdgeList {
public:
    int V, E;
    vector<tuple<int, int, int>> edges; // {u, v, weight}
    
    EdgeList(int v) : V(v), E(0) {}
    
    void addEdge(int u, int v, int w = 1) {
        edges.push_back({u, v, w});
        E++;
    }
    
    void printEdges() {
        cout << "Edge List:" << endl;
        for (auto& [u, v, w] : edges) {
            cout << u << " -- " << v << " (weight: " << w << ")" << endl;
        }
    }
};

// ==================== GRAPH WITH NODE VALUES ====================
template<typename T>
class GraphWithValues {
public:
    int V;
    vector<T> nodeValues;
    vector<vector<int>> adj;
    
    GraphWithValues(int v) : V(v), nodeValues(v), adj(v) {}
    
    void setNodeValue(int node, T value) {
        nodeValues[node] = value;
    }
    
    void addEdge(int u, int v, bool directed = false) {
        adj[u].push_back(v);
        if (!directed) adj[v].push_back(u);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cout << "=== Graph Representation Demo ===" << endl;
    
    // Adjacency List (Unweighted)
    cout << "\n1. Adjacency List (Unweighted):" << endl;
    AdjacencyList g1(5);
    g1.addEdge(0, 1);
    g1.addEdge(0, 4);
    g1.addEdge(1, 2);
    g1.addEdge(1, 3);
    g1.addEdge(1, 4);
    g1.addEdge(2, 3);
    g1.addEdge(3, 4);
    g1.printGraph();
    
    // Adjacency List (Weighted)
    cout << "\n2. Adjacency List (Weighted):" << endl;
    AdjacencyList g2(5);
    g2.addEdgeWeighted(0, 1, 10);
    g2.addEdgeWeighted(0, 4, 5);
    g2.addEdgeWeighted(1, 2, 3);
    g2.addEdgeWeighted(2, 3, 1);
    g2.printWeightedGraph();
    
    // Adjacency Matrix
    cout << "\n3. Adjacency Matrix:" << endl;
    AdjacencyMatrix g3(4);
    g3.addEdge(0, 1);
    g3.addEdge(0, 2);
    g3.addEdge(1, 2);
    g3.addEdge(2, 3);
    g3.printMatrix();
    
    // Edge List
    cout << "\n4. Edge List:" << endl;
    EdgeList g4(4);
    g4.addEdge(0, 1, 5);
    g4.addEdge(1, 2, 3);
    g4.addEdge(2, 3, 7);
    g4.addEdge(0, 3, 10);
    g4.printEdges();
    
    return 0;
}

