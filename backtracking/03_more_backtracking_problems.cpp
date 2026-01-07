/*
 * Backtracking - More Problems
 * Rat in Maze, Knight's Tour, Hamiltonian Path, Graph Coloring, etc.
 */

#include <bits/stdc++.h>
using namespace std;

// 1. Rat in a Maze
bool isSafeRat(vector<vector<int>>& maze, int x, int y, int n, vector<vector<bool>>& visited) {
    return (x >= 0 && x < n && y >= 0 && y < n && maze[x][y] == 1 && !visited[x][y]);
}

void ratInMazeHelper(vector<vector<int>>& maze, int x, int y, int n, string path, 
                     vector<string>& result, vector<vector<bool>>& visited) {
    if (x == n - 1 && y == n - 1) {
        result.push_back(path);
        return;
    }
    
    visited[x][y] = true;
    
    // Down
    if (isSafeRat(maze, x + 1, y, n, visited)) {
        ratInMazeHelper(maze, x + 1, y, n, path + "D", result, visited);
    }
    
    // Left
    if (isSafeRat(maze, x, y - 1, n, visited)) {
        ratInMazeHelper(maze, x, y - 1, n, path + "L", result, visited);
    }
    
    // Right
    if (isSafeRat(maze, x, y + 1, n, visited)) {
        ratInMazeHelper(maze, x, y + 1, n, path + "R", result, visited);
    }
    
    // Up
    if (isSafeRat(maze, x - 1, y, n, visited)) {
        ratInMazeHelper(maze, x - 1, y, n, path + "U", result, visited);
    }
    
    visited[x][y] = false;
}

vector<string> ratInMaze(vector<vector<int>>& maze, int n) {
    vector<string> result;
    if (maze[0][0] == 0 || maze[n-1][n-1] == 0) return result;
    
    vector<vector<bool>> visited(n, vector<bool>(n, false));
    ratInMazeHelper(maze, 0, 0, n, "", result, visited);
    return result;
}

// 2. Knight's Tour Problem
bool isSafeKnight(int x, int y, int n, vector<vector<int>>& board) {
    return (x >= 0 && x < n && y >= 0 && y < n && board[x][y] == -1);
}

bool knightTourHelper(int x, int y, int moveCnt, vector<vector<int>>& board, int n) {
    if (moveCnt == n * n) {
        return true;
    }
    
    int dx[] = {2, 1, -1, -2, -2, -1, 1, 2};
    int dy[] = {1, 2, 2, 1, -1, -2, -2, -1};
    
    for (int i = 0; i < 8; i++) {
        int nextX = x + dx[i];
        int nextY = y + dy[i];
        
        if (isSafeKnight(nextX, nextY, n, board)) {
            board[nextX][nextY] = moveCnt;
            
            if (knightTourHelper(nextX, nextY, moveCnt + 1, board, n)) {
                return true;
            }
            
            board[nextX][nextY] = -1;
        }
    }
    
    return false;
}

bool knightTour(int n) {
    vector<vector<int>> board(n, vector<int>(n, -1));
    board[0][0] = 0;
    
    if (knightTourHelper(0, 0, 1, board, n)) {
        cout << "Knight's Tour Solution:" << endl;
        for (auto& row : board) {
            for (int val : row) {
                cout << setw(3) << val << " ";
            }
            cout << endl;
        }
        return true;
    }
    return false;
}

// 3. Hamiltonian Path (Visit all vertices exactly once)
bool hamiltonianPathHelper(vector<vector<int>>& graph, vector<int>& path, vector<bool>& visited, int n) {
    if (path.size() == n) {
        return true;
    }
    
    int lastVertex = path.back();
    
    for (int v = 0; v < n; v++) {
        if (graph[lastVertex][v] && !visited[v]) {
            path.push_back(v);
            visited[v] = true;
            
            if (hamiltonianPathHelper(graph, path, visited, n)) {
                return true;
            }
            
            path.pop_back();
            visited[v] = false;
        }
    }
    
    return false;
}

vector<int> hamiltonianPath(vector<vector<int>>& graph, int start) {
    int n = graph.size();
    vector<int> path = {start};
    vector<bool> visited(n, false);
    visited[start] = true;
    
    if (hamiltonianPathHelper(graph, path, visited, n)) {
        return path;
    }
    return {};
}

// 4. Hamiltonian Cycle
bool hamiltonianCycleHelper(vector<vector<int>>& graph, vector<int>& path, int n) {
    if (path.size() == n) {
        // Check if there's an edge from last vertex to first vertex
        return graph[path.back()][path[0]] == 1;
    }
    
    for (int v = 1; v < n; v++) {
        bool alreadyInPath = false;
        for (int vertex : path) {
            if (vertex == v) {
                alreadyInPath = true;
                break;
            }
        }
        
        if (!alreadyInPath && graph[path.back()][v]) {
            path.push_back(v);
            
            if (hamiltonianCycleHelper(graph, path, n)) {
                return true;
            }
            
            path.pop_back();
        }
    }
    
    return false;
}

vector<int> hamiltonianCycle(vector<vector<int>>& graph) {
    int n = graph.size();
    vector<int> path = {0};
    
    if (hamiltonianCycleHelper(graph, path, n)) {
        path.push_back(0); // Complete the cycle
        return path;
    }
    return {};
}

// 5. Graph Coloring (m-coloring problem)
bool isSafeColor(vector<vector<int>>& graph, vector<int>& color, int v, int c) {
    for (int i = 0; i < graph.size(); i++) {
        if (graph[v][i] && color[i] == c) {
            return false;
        }
    }
    return true;
}

bool graphColoringHelper(vector<vector<int>>& graph, int m, vector<int>& color, int v) {
    int n = graph.size();
    if (v == n) {
        return true;
    }
    
    for (int c = 1; c <= m; c++) {
        if (isSafeColor(graph, color, v, c)) {
            color[v] = c;
            
            if (graphColoringHelper(graph, m, color, v + 1)) {
                return true;
            }
            
            color[v] = 0;
        }
    }
    
    return false;
}

bool graphColoring(vector<vector<int>>& graph, int m) {
    int n = graph.size();
    vector<int> color(n, 0);
    
    if (graphColoringHelper(graph, m, color, 0)) {
        cout << "Graph coloring with " << m << " colors:" << endl;
        for (int i = 0; i < n; i++) {
            cout << "Vertex " << i << " -> Color " << color[i] << endl;
        }
        return true;
    }
    return false;
}

// 6. Subset Sum Problem
void subsetSumHelper(vector<int>& arr, int target, int idx, vector<int>& current, 
                     vector<vector<int>>& result, int currentSum) {
    if (currentSum == target) {
        result.push_back(current);
        return;
    }
    
    if (idx >= arr.size() || currentSum > target) {
        return;
    }
    
    // Include current element
    current.push_back(arr[idx]);
    subsetSumHelper(arr, target, idx + 1, current, result, currentSum + arr[idx]);
    current.pop_back();
    
    // Exclude current element
    subsetSumHelper(arr, target, idx + 1, current, result, currentSum);
}

vector<vector<int>> subsetSum(vector<int>& arr, int target) {
    vector<vector<int>> result;
    vector<int> current;
    subsetSumHelper(arr, target, 0, current, result, 0);
    return result;
}

// 7. Cryptarithmetic Problem (SEND + MORE = MONEY)
bool isValidAssignment(string s1, string s2, string s3, unordered_map<char, int>& charToDigit) {
    auto getNumber = [&](string s) {
        int num = 0;
        for (char c : s) {
            num = num * 10 + charToDigit[c];
        }
        return num;
    };
    
    // Leading zeros not allowed
    if (charToDigit[s1[0]] == 0 || charToDigit[s2[0]] == 0 || charToDigit[s3[0]] == 0) {
        return false;
    }
    
    int num1 = getNumber(s1);
    int num2 = getNumber(s2);
    int num3 = getNumber(s3);
    
    return (num1 + num2 == num3);
}

bool cryptarithmeticHelper(string s1, string s2, string s3, vector<char>& chars, 
                          vector<bool>& used, unordered_map<char, int>& charToDigit, int idx) {
    if (idx == chars.size()) {
        return isValidAssignment(s1, s2, s3, charToDigit);
    }
    
    for (int digit = 0; digit <= 9; digit++) {
        if (!used[digit]) {
            charToDigit[chars[idx]] = digit;
            used[digit] = true;
            
            if (cryptarithmeticHelper(s1, s2, s3, chars, used, charToDigit, idx + 1)) {
                return true;
            }
            
            used[digit] = false;
        }
    }
    
    return false;
}

bool solveCryptarithmetic(string s1, string s2, string s3) {
    set<char> uniqueChars;
    for (char c : s1) uniqueChars.insert(c);
    for (char c : s2) uniqueChars.insert(c);
    for (char c : s3) uniqueChars.insert(c);
    
    if (uniqueChars.size() > 10) return false;
    
    vector<char> chars(uniqueChars.begin(), uniqueChars.end());
    vector<bool> used(10, false);
    unordered_map<char, int> charToDigit;
    
    if (cryptarithmeticHelper(s1, s2, s3, chars, used, charToDigit, 0)) {
        cout << s1 << " + " << s2 << " = " << s3 << endl;
        for (auto& p : charToDigit) {
            cout << p.first << " = " << p.second << endl;
        }
        return true;
    }
    return false;
}

// 8. Partition Equal Subset Sum
bool partitionHelper(vector<int>& nums, int idx, int target) {
    if (target == 0) return true;
    if (idx >= nums.size() || target < 0) return false;
    
    // Include current element
    if (partitionHelper(nums, idx + 1, target - nums[idx])) {
        return true;
    }
    
    // Exclude current element
    return partitionHelper(nums, idx + 1, target);
}

bool canPartition(vector<int>& nums) {
    int sum = 0;
    for (int num : nums) sum += num;
    
    if (sum % 2 != 0) return false;
    
    return partitionHelper(nums, 0, sum / 2);
}

// 9. Tug of War (Divide array into two subsets with minimum difference)
void tugOfWarHelper(vector<int>& arr, int idx, vector<int>& current, vector<int>& remaining,
                    int currentSum, int remainingSum, int& minDiff, 
                    vector<int>& bestSubset) {
    if (idx == arr.size()) {
        if (current.size() == arr.size() / 2) {
            int diff = abs(currentSum - remainingSum);
            if (diff < minDiff) {
                minDiff = diff;
                bestSubset = current;
            }
        }
        return;
    }
    
    // Include in current subset
    if (current.size() < (arr.size() + 1) / 2) {
        current.push_back(arr[idx]);
        tugOfWarHelper(arr, idx + 1, current, remaining, currentSum + arr[idx], 
                      remainingSum, minDiff, bestSubset);
        current.pop_back();
    }
    
    // Include in remaining subset
    if (remaining.size() < (arr.size() + 1) / 2) {
        remaining.push_back(arr[idx]);
        tugOfWarHelper(arr, idx + 1, current, remaining, currentSum, 
                      remainingSum + arr[idx], minDiff, bestSubset);
        remaining.pop_back();
    }
}

void tugOfWar(vector<int>& arr) {
    vector<int> current, remaining, bestSubset;
    int minDiff = INT_MAX;
    tugOfWarHelper(arr, 0, current, remaining, 0, 0, minDiff, bestSubset);
    
    cout << "Subset 1: ";
    for (int x : bestSubset) cout << x << " ";
    cout << "\nSubset 2: ";
    
    set<int> subset1(bestSubset.begin(), bestSubset.end());
    for (int x : arr) {
        if (subset1.find(x) == subset1.end()) {
            cout << x << " ";
        }
    }
    cout << "\nMinimum difference: " << minDiff << endl;
}

// 10. Remove Invalid Parentheses
bool isValid(string s) {
    int count = 0;
    for (char c : s) {
        if (c == '(') count++;
        else if (c == ')') {
            count--;
            if (count < 0) return false;
        }
    }
    return count == 0;
}

void removeInvalidParenthesesHelper(string s, int idx, int leftRem, int rightRem, 
                                   string current, set<string>& result) {
    if (idx == s.length()) {
        if (leftRem == 0 && rightRem == 0 && isValid(current)) {
            result.insert(current);
        }
        return;
    }
    
    if (s[idx] != '(' && s[idx] != ')') {
        removeInvalidParenthesesHelper(s, idx + 1, leftRem, rightRem, current + s[idx], result);
    } else {
        // Remove current parenthesis
        if (s[idx] == '(' && leftRem > 0) {
            removeInvalidParenthesesHelper(s, idx + 1, leftRem - 1, rightRem, current, result);
        }
        if (s[idx] == ')' && rightRem > 0) {
            removeInvalidParenthesesHelper(s, idx + 1, leftRem, rightRem - 1, current, result);
        }
        
        // Keep current parenthesis
        removeInvalidParenthesesHelper(s, idx + 1, leftRem, rightRem, current + s[idx], result);
    }
}

vector<string> removeInvalidParentheses(string s) {
    int leftRem = 0, rightRem = 0;
    
    for (char c : s) {
        if (c == '(') {
            leftRem++;
        } else if (c == ')') {
            if (leftRem > 0) leftRem--;
            else rightRem++;
        }
    }
    
    set<string> result;
    removeInvalidParenthesesHelper(s, 0, leftRem, rightRem, "", result);
    return vector<string>(result.begin(), result.end());
}

int main() {
    // Test Rat in Maze
    cout << "=== Rat in Maze ===" << endl;
    vector<vector<int>> maze = {
        {1, 0, 0, 0},
        {1, 1, 0, 1},
        {0, 1, 0, 0},
        {1, 1, 1, 1}
    };
    vector<string> paths = ratInMaze(maze, 4);
    cout << "Paths: ";
    for (string& path : paths) cout << path << " ";
    cout << "\n\n";
    
    // Test Knight's Tour
    cout << "=== Knight's Tour ===" << endl;
    knightTour(5);
    cout << "\n";
    
    // Test Hamiltonian Path
    cout << "=== Hamiltonian Path ===" << endl;
    vector<vector<int>> graph1 = {
        {0, 1, 0, 1, 0},
        {1, 0, 1, 1, 1},
        {0, 1, 0, 0, 1},
        {1, 1, 0, 0, 1},
        {0, 1, 1, 1, 0}
    };
    vector<int> hPath = hamiltonianPath(graph1, 0);
    cout << "Hamiltonian Path: ";
    for (int v : hPath) cout << v << " ";
    cout << "\n\n";
    
    // Test Graph Coloring
    cout << "=== Graph Coloring ===" << endl;
    vector<vector<int>> graph2 = {
        {0, 1, 1, 1},
        {1, 0, 1, 0},
        {1, 1, 0, 1},
        {1, 0, 1, 0}
    };
    graphColoring(graph2, 3);
    cout << "\n";
    
    // Test Subset Sum
    cout << "=== Subset Sum ===" << endl;
    vector<int> arr1 = {3, 34, 4, 12, 5, 2};
    vector<vector<int>> subsets = subsetSum(arr1, 9);
    cout << "Subsets with sum 9: " << subsets.size() << endl;
    for (auto& subset : subsets) {
        cout << "{ ";
        for (int x : subset) cout << x << " ";
        cout << "}" << endl;
    }
    cout << "\n";
    
    // Test Cryptarithmetic
    cout << "=== Cryptarithmetic (SEND + MORE = MONEY) ===" << endl;
    solveCryptarithmetic("SEND", "MORE", "MONEY");
    cout << "\n";
    
    // Test Partition Equal Subset Sum
    cout << "=== Partition Equal Subset Sum ===" << endl;
    vector<int> arr2 = {1, 5, 11, 5};
    cout << "Can partition: " << (canPartition(arr2) ? "Yes" : "No") << "\n\n";
    
    // Test Remove Invalid Parentheses
    cout << "=== Remove Invalid Parentheses ===" << endl;
    vector<string> validStrings = removeInvalidParentheses("()())()");
    cout << "Valid strings: ";
    for (string& str : validStrings) cout << str << " ";
    cout << endl;
    
    return 0;
}

