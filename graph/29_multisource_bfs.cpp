/*
    Multi-Source BFS
    - BFS from multiple sources simultaneously
    - Time: O(V + E)
*/

#include <bits/stdc++.h>
using namespace std;

class MultiSourceBFS {
public:
    // ==================== Basic Multi-Source BFS ====================
    vector<int> multiSourceBFS(int n, vector<vector<int>>& adj, vector<int>& sources) {
        vector<int> dist(n, INT_MAX);
        queue<int> q;
        
        for (int src : sources) {
            dist[src] = 0;
            q.push(src);
        }
        
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            
            for (int neighbor : adj[node]) {
                if (dist[neighbor] > dist[node] + 1) {
                    dist[neighbor] = dist[node] + 1;
                    q.push(neighbor);
                }
            }
        }
        
        return dist;
    }
    
    // ==================== 01 Matrix (LC 542) ====================
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        int m = mat.size(), n = mat[0].size();
        vector<vector<int>> dist(m, vector<int>(n, INT_MAX));
        queue<pair<int, int>> q;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (mat[i][j] == 0) {
                    dist[i][j] = 0;
                    q.push({i, j});
                }
            }
        }
        
        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};
        
        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();
            
            for (int d = 0; d < 4; d++) {
                int nx = x + dx[d], ny = y + dy[d];
                if (nx >= 0 && nx < m && ny >= 0 && ny < n) {
                    if (dist[nx][ny] > dist[x][y] + 1) {
                        dist[nx][ny] = dist[x][y] + 1;
                        q.push({nx, ny});
                    }
                }
            }
        }
        
        return dist;
    }
    
    // ==================== Rotting Oranges (LC 994) ====================
    int orangesRotting(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        queue<pair<int, int>> q;
        int fresh = 0;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 2) q.push({i, j});
                else if (grid[i][j] == 1) fresh++;
            }
        }
        
        if (fresh == 0) return 0;
        
        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};
        int minutes = 0;
        
        while (!q.empty()) {
            int size = q.size();
            bool rotted = false;
            
            for (int i = 0; i < size; i++) {
                auto [x, y] = q.front();
                q.pop();
                
                for (int d = 0; d < 4; d++) {
                    int nx = x + dx[d], ny = y + dy[d];
                    if (nx >= 0 && nx < m && ny >= 0 && ny < n && grid[nx][ny] == 1) {
                        grid[nx][ny] = 2;
                        fresh--;
                        q.push({nx, ny});
                        rotted = true;
                    }
                }
            }
            
            if (rotted) minutes++;
        }
        
        return fresh == 0 ? minutes : -1;
    }
    
    // ==================== Walls and Gates (LC 286) ====================
    void wallsAndGates(vector<vector<int>>& rooms) {
        int m = rooms.size(), n = rooms[0].size();
        queue<pair<int, int>> q;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (rooms[i][j] == 0) q.push({i, j});
            }
        }
        
        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};
        
        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();
            
            for (int d = 0; d < 4; d++) {
                int nx = x + dx[d], ny = y + dy[d];
                if (nx >= 0 && nx < m && ny >= 0 && ny < n) {
                    if (rooms[nx][ny] > rooms[x][y] + 1) {
                        rooms[nx][ny] = rooms[x][y] + 1;
                        q.push({nx, ny});
                    }
                }
            }
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cout << "=== Multi-Source BFS Demo ===" << endl;
    MultiSourceBFS msb;
    
    // 01 Matrix
    cout << "01 Matrix:" << endl;
    vector<vector<int>> mat = {{0,0,0},{0,1,0},{1,1,1}};
    auto result = msb.updateMatrix(mat);
    for (auto& row : result) {
        for (int x : row) cout << x << " ";
        cout << endl;
    }
    
    // Rotting Oranges
    cout << "\nRotting Oranges:" << endl;
    vector<vector<int>> grid = {{2,1,1},{1,1,0},{0,1,1}};
    cout << "Minutes: " << msb.orangesRotting(grid) << endl;
    
    return 0;
}









