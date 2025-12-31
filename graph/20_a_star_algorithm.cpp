/*
    A* Algorithm - Shortest Path with Heuristic
    - Best for pathfinding in grids/maps
    - f(n) = g(n) + h(n)
    - Time: O(E) in best case, O(b^d) worst case
*/

#include <bits/stdc++.h>
using namespace std;

struct Node {
    int x, y;
    int g, h; // g: cost from start, h: heuristic to goal
    int f() const { return g + h; }
    bool operator>(const Node& other) const { return f() > other.f(); }
};

class AStar {
public:
    int rows, cols;
    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};
    
    AStar(int r, int c) : rows(r), cols(c) {}
    
    // Manhattan distance heuristic
    int heuristic(int x1, int y1, int x2, int y2) {
        return abs(x1 - x2) + abs(y1 - y2);
    }
    
    // Find shortest path in grid
    vector<pair<int, int>> findPath(vector<vector<int>>& grid, 
                                     pair<int,int> start, pair<int,int> goal) {
        if (grid[start.first][start.second] == 1 || 
            grid[goal.first][goal.second] == 1) return {};
        
        vector<vector<int>> gScore(rows, vector<int>(cols, INT_MAX));
        vector<vector<pair<int,int>>> parent(rows, vector<pair<int,int>>(cols, {-1, -1}));
        
        priority_queue<Node, vector<Node>, greater<Node>> pq;
        
        gScore[start.first][start.second] = 0;
        pq.push({start.first, start.second, 0, 
                 heuristic(start.first, start.second, goal.first, goal.second)});
        
        while (!pq.empty()) {
            Node curr = pq.top();
            pq.pop();
            
            if (curr.x == goal.first && curr.y == goal.second) {
                return reconstructPath(parent, start, goal);
            }
            
            if (curr.g > gScore[curr.x][curr.y]) continue;
            
            for (int d = 0; d < 4; d++) {
                int nx = curr.x + dx[d];
                int ny = curr.y + dy[d];
                
                if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && 
                    grid[nx][ny] == 0) {
                    int newG = curr.g + 1;
                    if (newG < gScore[nx][ny]) {
                        gScore[nx][ny] = newG;
                        parent[nx][ny] = {curr.x, curr.y};
                        pq.push({nx, ny, newG, heuristic(nx, ny, goal.first, goal.second)});
                    }
                }
            }
        }
        
        return {};
    }
    
    vector<pair<int, int>> reconstructPath(vector<vector<pair<int,int>>>& parent,
                                           pair<int,int> start, pair<int,int> goal) {
        vector<pair<int, int>> path;
        auto curr = goal;
        
        while (curr != start) {
            path.push_back(curr);
            curr = parent[curr.first][curr.second];
        }
        path.push_back(start);
        reverse(path.begin(), path.end());
        return path;
    }
};

// 8-directional A* with weighted grid
class AStarWeighted {
public:
    int rows, cols;
    int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
    
    AStarWeighted(int r, int c) : rows(r), cols(c) {}
    
    int heuristic(int x1, int y1, int x2, int y2) {
        return max(abs(x1 - x2), abs(y1 - y2)); // Chebyshev distance
    }
    
    int findShortestPath(vector<vector<int>>& grid, 
                         pair<int,int> start, pair<int,int> goal) {
        vector<vector<int>> dist(rows, vector<int>(cols, INT_MAX));
        priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, greater<>> pq;
        
        dist[start.first][start.second] = grid[start.first][start.second];
        pq.push({dist[start.first][start.second] + 
                 heuristic(start.first, start.second, goal.first, goal.second),
                 start.first, start.second});
        
        while (!pq.empty()) {
            auto [f, x, y] = pq.top();
            pq.pop();
            
            if (x == goal.first && y == goal.second) return dist[x][y];
            if (f - heuristic(x, y, goal.first, goal.second) > dist[x][y]) continue;
            
            for (int d = 0; d < 8; d++) {
                int nx = x + dx[d], ny = y + dy[d];
                if (nx >= 0 && nx < rows && ny >= 0 && ny < cols) {
                    int newDist = dist[x][y] + grid[nx][ny];
                    if (newDist < dist[nx][ny]) {
                        dist[nx][ny] = newDist;
                        pq.push({newDist + heuristic(nx, ny, goal.first, goal.second), nx, ny});
                    }
                }
            }
        }
        
        return -1;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cout << "=== A* Algorithm Demo ===" << endl;
    
    vector<vector<int>> grid = {
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 1, 0},
        {0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0}
    };
    
    AStar astar(5, 5);
    auto path = astar.findPath(grid, {0, 0}, {4, 4});
    
    cout << "Path from (0,0) to (4,4):" << endl;
    for (auto& [x, y] : path) {
        cout << "(" << x << "," << y << ") ";
    }
    cout << "\nPath length: " << path.size() - 1 << endl;
    
    return 0;
}



