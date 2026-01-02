/*
    Graph Traversal Applications
    - Connected Components, Flood Fill, etc.
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== Flood Fill ====================
class FloodFill {
public:
    vector<vector<int>> fill(vector<vector<int>>& image, int sr, int sc, int color) {
        if (image[sr][sc] == color) return image;
        
        int original = image[sr][sc];
        dfs(image, sr, sc, original, color);
        return image;
    }
    
    void dfs(vector<vector<int>>& img, int r, int c, int orig, int newColor) {
        if (r < 0 || r >= img.size() || c < 0 || c >= img[0].size()) return;
        if (img[r][c] != orig) return;
        
        img[r][c] = newColor;
        dfs(img, r+1, c, orig, newColor);
        dfs(img, r-1, c, orig, newColor);
        dfs(img, r, c+1, orig, newColor);
        dfs(img, r, c-1, orig, newColor);
    }
};

// ==================== Max Area of Island ====================
class MaxAreaIsland {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int maxArea = 0;
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[0].size(); j++) {
                if (grid[i][j] == 1) {
                    maxArea = max(maxArea, dfs(grid, i, j));
                }
            }
        }
        return maxArea;
    }
    
    int dfs(vector<vector<int>>& grid, int r, int c) {
        if (r < 0 || r >= grid.size() || c < 0 || c >= grid[0].size()) return 0;
        if (grid[r][c] != 1) return 0;
        
        grid[r][c] = 0;
        return 1 + dfs(grid, r+1, c) + dfs(grid, r-1, c) + 
                   dfs(grid, r, c+1) + dfs(grid, r, c-1);
    }
};

// ==================== Connected Components (Undirected) ====================
class ConnectedComponents {
public:
    int countComponents(int n, vector<vector<int>>& edges) {
        vector<vector<int>> adj(n);
        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }
        
        vector<bool> visited(n, false);
        int count = 0;
        
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                count++;
                dfs(i, adj, visited);
            }
        }
        return count;
    }
    
    void dfs(int node, vector<vector<int>>& adj, vector<bool>& visited) {
        visited[node] = true;
        for (int next : adj[node]) {
            if (!visited[next]) dfs(next, adj, visited);
        }
    }
};

// ==================== Shortest Bridge ====================
class ShortestBridge {
public:
    int shortestBridge(vector<vector<int>>& grid) {
        int n = grid.size();
        queue<pair<int, int>> q;
        bool found = false;
        
        // Find first island and mark it
        for (int i = 0; i < n && !found; i++) {
            for (int j = 0; j < n && !found; j++) {
                if (grid[i][j] == 1) {
                    markIsland(grid, i, j, q);
                    found = true;
                }
            }
        }
        
        // BFS to find second island
        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};
        int steps = 0;
        
        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; i++) {
                auto [x, y] = q.front();
                q.pop();
                
                for (int d = 0; d < 4; d++) {
                    int nx = x + dx[d], ny = y + dy[d];
                    if (nx >= 0 && nx < n && ny >= 0 && ny < n) {
                        if (grid[nx][ny] == 1) return steps;
                        if (grid[nx][ny] == 0) {
                            grid[nx][ny] = 2;
                            q.push({nx, ny});
                        }
                    }
                }
            }
            steps++;
        }
        return -1;
    }
    
    void markIsland(vector<vector<int>>& grid, int r, int c, queue<pair<int, int>>& q) {
        if (r < 0 || r >= grid.size() || c < 0 || c >= grid[0].size()) return;
        if (grid[r][c] != 1) return;
        
        grid[r][c] = 2;
        q.push({r, c});
        markIsland(grid, r+1, c, q);
        markIsland(grid, r-1, c, q);
        markIsland(grid, r, c+1, q);
        markIsland(grid, r, c-1, q);
    }
};

// ==================== Making A Large Island ====================
class MakeLargeIsland {
public:
    int largestIsland(vector<vector<int>>& grid) {
        int n = grid.size();
        map<int, int> area;
        int id = 2;
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    area[id] = dfs(grid, i, j, id);
                    id++;
                }
            }
        }
        
        int maxArea = 0;
        for (auto& [k, v] : area) maxArea = max(maxArea, v);
        
        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 0) {
                    set<int> neighbors;
                    for (int d = 0; d < 4; d++) {
                        int ni = i + dx[d], nj = j + dy[d];
                        if (ni >= 0 && ni < n && nj >= 0 && nj < n && grid[ni][nj] > 1) {
                            neighbors.insert(grid[ni][nj]);
                        }
                    }
                    int sum = 1;
                    for (int id : neighbors) sum += area[id];
                    maxArea = max(maxArea, sum);
                }
            }
        }
        
        return maxArea;
    }
    
    int dfs(vector<vector<int>>& grid, int r, int c, int id) {
        if (r < 0 || r >= grid.size() || c < 0 || c >= grid[0].size()) return 0;
        if (grid[r][c] != 1) return 0;
        
        grid[r][c] = id;
        return 1 + dfs(grid, r+1, c, id) + dfs(grid, r-1, c, id) +
                   dfs(grid, r, c+1, id) + dfs(grid, r, c-1, id);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cout << "=== Graph Traversal Applications Demo ===" << endl;
    
    // Max Area of Island
    MaxAreaIsland mai;
    vector<vector<int>> grid = {
        {0,0,1,0,0},
        {0,0,0,0,0},
        {0,1,1,0,1},
        {0,1,0,0,1},
        {0,1,0,0,1}
    };
    cout << "Max Area of Island: " << mai.maxAreaOfIsland(grid) << endl;
    
    // Connected Components
    ConnectedComponents cc;
    vector<vector<int>> edges = {{0,1},{1,2},{3,4}};
    cout << "Connected Components: " << cc.countComponents(5, edges) << endl;
    
    return 0;
}









