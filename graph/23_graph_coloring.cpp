/*
    Graph Coloring
    - Chromatic number
    - m-coloring problem
    - Greedy coloring
*/

#include <bits/stdc++.h>
using namespace std;

class GraphColoring {
public:
    int V;
    vector<vector<int>> adj;
    
    GraphColoring(int v) : V(v), adj(v) {}
    
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    // ==================== Greedy Coloring ====================
    vector<int> greedyColoring() {
        vector<int> color(V, -1);
        color[0] = 0;
        
        for (int u = 1; u < V; u++) {
            set<int> usedColors;
            for (int neighbor : adj[u]) {
                if (color[neighbor] != -1) {
                    usedColors.insert(color[neighbor]);
                }
            }
            
            // Find first available color
            int c = 0;
            while (usedColors.count(c)) c++;
            color[u] = c;
        }
        
        return color;
    }
    
    // ==================== m-Coloring (Backtracking) ====================
    bool canColorWithM(int m) {
        vector<int> color(V, 0);
        return mColorUtil(0, m, color);
    }
    
    bool mColorUtil(int node, int m, vector<int>& color) {
        if (node == V) return true;
        
        for (int c = 1; c <= m; c++) {
            if (isSafe(node, c, color)) {
                color[node] = c;
                if (mColorUtil(node + 1, m, color)) return true;
                color[node] = 0;
            }
        }
        return false;
    }
    
    bool isSafe(int node, int c, vector<int>& color) {
        for (int neighbor : adj[node]) {
            if (color[neighbor] == c) return false;
        }
        return true;
    }
    
    // ==================== Chromatic Number ====================
    int chromaticNumber() {
        for (int m = 1; m <= V; m++) {
            if (canColorWithM(m)) return m;
        }
        return V;
    }
    
    // ==================== Welsh-Powell Algorithm ====================
    vector<int> welshPowell() {
        vector<pair<int, int>> degrees(V);
        for (int i = 0; i < V; i++) {
            degrees[i] = {adj[i].size(), i};
        }
        sort(degrees.rbegin(), degrees.rend());
        
        vector<int> color(V, -1);
        int currentColor = 0;
        
        for (auto& [deg, u] : degrees) {
            if (color[u] == -1) {
                color[u] = currentColor;
                
                for (auto& [d, v] : degrees) {
                    if (color[v] == -1 && isSafe(v, currentColor, color)) {
                        color[v] = currentColor;
                    }
                }
                currentColor++;
            }
        }
        
        return color;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cout << "=== Graph Coloring Demo ===" << endl;
    
    GraphColoring g(5);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    
    // Greedy coloring
    cout << "Greedy Coloring:" << endl;
    auto colors = g.greedyColoring();
    for (int i = 0; i < 5; i++) {
        cout << "Node " << i << ": Color " << colors[i] << endl;
    }
    
    int maxColor = *max_element(colors.begin(), colors.end());
    cout << "Colors used: " << maxColor + 1 << endl;
    
    // m-coloring
    cout << "\nCan color with 3 colors: " << (g.canColorWithM(3) ? "Yes" : "No") << endl;
    cout << "Chromatic number: " << g.chromaticNumber() << endl;
    
    return 0;
}

