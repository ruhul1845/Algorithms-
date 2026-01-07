/*
    Common Graph Problems Collection
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== Clone Graph ====================
class CloneGraph {
public:
    struct Node {
        int val;
        vector<Node*> neighbors;
        Node(int v) : val(v) {}
    };
    
    Node* cloneGraph(Node* node) {
        if (!node) return nullptr;
        
        unordered_map<Node*, Node*> visited;
        return dfs(node, visited);
    }
    
    Node* dfs(Node* node, unordered_map<Node*, Node*>& visited) {
        if (visited.count(node)) return visited[node];
        
        Node* clone = new Node(node->val);
        visited[node] = clone;
        
        for (Node* neighbor : node->neighbors) {
            clone->neighbors.push_back(dfs(neighbor, visited));
        }
        
        return clone;
    }
};

// ==================== Word Ladder ====================
class WordLadder {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> wordSet(wordList.begin(), wordList.end());
        if (!wordSet.count(endWord)) return 0;
        
        queue<pair<string, int>> q;
        q.push({beginWord, 1});
        
        while (!q.empty()) {
            auto [word, dist] = q.front();
            q.pop();
            
            if (word == endWord) return dist;
            
            for (int i = 0; i < word.size(); i++) {
                string temp = word;
                for (char c = 'a'; c <= 'z'; c++) {
                    temp[i] = c;
                    if (wordSet.count(temp)) {
                        q.push({temp, dist + 1});
                        wordSet.erase(temp);
                    }
                }
            }
        }
        
        return 0;
    }
};

// ==================== Number of Islands ====================
class NumberOfIslands {
public:
    int numIslands(vector<vector<char>>& grid) {
        int m = grid.size(), n = grid[0].size();
        int count = 0;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == '1') {
                    count++;
                    dfs(grid, i, j);
                }
            }
        }
        
        return count;
    }
    
    void dfs(vector<vector<char>>& grid, int i, int j) {
        if (i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size()) return;
        if (grid[i][j] != '1') return;
        
        grid[i][j] = '0';
        dfs(grid, i+1, j);
        dfs(grid, i-1, j);
        dfs(grid, i, j+1);
        dfs(grid, i, j-1);
    }
};

// ==================== Surrounded Regions ====================
class SurroundedRegions {
public:
    void solve(vector<vector<char>>& board) {
        int m = board.size(), n = board[0].size();
        
        // Mark border-connected O's
        for (int i = 0; i < m; i++) {
            dfs(board, i, 0);
            dfs(board, i, n-1);
        }
        for (int j = 0; j < n; j++) {
            dfs(board, 0, j);
            dfs(board, m-1, j);
        }
        
        // Flip remaining O's to X, restore marked
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == 'O') board[i][j] = 'X';
                else if (board[i][j] == '#') board[i][j] = 'O';
            }
        }
    }
    
    void dfs(vector<vector<char>>& board, int i, int j) {
        if (i < 0 || i >= board.size() || j < 0 || j >= board[0].size()) return;
        if (board[i][j] != 'O') return;
        
        board[i][j] = '#';
        dfs(board, i+1, j);
        dfs(board, i-1, j);
        dfs(board, i, j+1);
        dfs(board, i, j-1);
    }
};

// ==================== Pacific Atlantic Water Flow ====================
class PacificAtlantic {
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        int m = heights.size(), n = heights[0].size();
        vector<vector<bool>> pacific(m, vector<bool>(n, false));
        vector<vector<bool>> atlantic(m, vector<bool>(n, false));
        
        for (int i = 0; i < m; i++) {
            dfs(heights, pacific, i, 0);
            dfs(heights, atlantic, i, n-1);
        }
        for (int j = 0; j < n; j++) {
            dfs(heights, pacific, 0, j);
            dfs(heights, atlantic, m-1, j);
        }
        
        vector<vector<int>> result;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (pacific[i][j] && atlantic[i][j]) {
                    result.push_back({i, j});
                }
            }
        }
        return result;
    }
    
    void dfs(vector<vector<int>>& h, vector<vector<bool>>& v, int i, int j) {
        if (v[i][j]) return;
        v[i][j] = true;
        
        int dx[] = {-1, 1, 0, 0}, dy[] = {0, 0, -1, 1};
        for (int d = 0; d < 4; d++) {
            int ni = i + dx[d], nj = j + dy[d];
            if (ni >= 0 && ni < h.size() && nj >= 0 && nj < h[0].size()) {
                if (h[ni][nj] >= h[i][j]) dfs(h, v, ni, nj);
            }
        }
    }
};

// ==================== Course Schedule II ====================
class CourseScheduleII {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> adj(numCourses);
        vector<int> inDegree(numCourses, 0);
        
        for (auto& p : prerequisites) {
            adj[p[1]].push_back(p[0]);
            inDegree[p[0]]++;
        }
        
        queue<int> q;
        for (int i = 0; i < numCourses; i++) {
            if (inDegree[i] == 0) q.push(i);
        }
        
        vector<int> order;
        while (!q.empty()) {
            int course = q.front();
            q.pop();
            order.push_back(course);
            
            for (int next : adj[course]) {
                if (--inDegree[next] == 0) q.push(next);
            }
        }
        
        return order.size() == numCourses ? order : vector<int>();
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cout << "=== Graph Problems Demo ===" << endl;
    
    // Word Ladder
    WordLadder wl;
    vector<string> wordList = {"hot","dot","dog","lot","log","cog"};
    cout << "Word Ladder length: " << wl.ladderLength("hit", "cog", wordList) << endl;
    
    // Number of Islands
    NumberOfIslands noi;
    vector<vector<char>> grid = {
        {'1','1','0','0','0'},
        {'1','1','0','0','0'},
        {'0','0','1','0','0'},
        {'0','0','0','1','1'}
    };
    cout << "Number of Islands: " << noi.numIslands(grid) << endl;
    
    // Course Schedule
    CourseScheduleII cs;
    vector<vector<int>> prereqs = {{1,0},{2,0},{3,1},{3,2}};
    auto order = cs.findOrder(4, prereqs);
    cout << "Course Order: ";
    for (int c : order) cout << c << " ";
    cout << endl;
    
    return 0;
}


















