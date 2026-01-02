/*
 * Backtracking - Advanced Problems
 * N-Queens, Sudoku Solver, Word Search
 */

#include <bits/stdc++.h>
using namespace std;

// 1. N-Queens
bool isSafe(vector<string>& board, int row, int col, int n) {
    // Check column
    for (int i = 0; i < row; i++) {
        if (board[i][col] == 'Q') return false;
    }
    
    // Check upper left diagonal
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == 'Q') return false;
    }
    
    // Check upper right diagonal
    for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++) {
        if (board[i][j] == 'Q') return false;
    }
    
    return true;
}

void solveNQueensHelper(int n, int row, vector<string>& board, vector<vector<string>>& result) {
    if (row == n) {
        result.push_back(board);
        return;
    }
    
    for (int col = 0; col < n; col++) {
        if (isSafe(board, row, col, n)) {
            board[row][col] = 'Q';
            solveNQueensHelper(n, row + 1, board, result);
            board[row][col] = '.';
        }
    }
}

vector<vector<string>> solveNQueens(int n) {
    vector<vector<string>> result;
    vector<string> board(n, string(n, '.'));
    solveNQueensHelper(n, 0, board, result);
    return result;
}

// 2. Sudoku Solver
bool isValidSudoku(vector<vector<char>>& board, int row, int col, char num) {
    for (int i = 0; i < 9; i++) {
        if (board[row][i] == num) return false;
        if (board[i][col] == num) return false;
        if (board[3 * (row / 3) + i / 3][3 * (col / 3) + i % 3] == num) return false;
    }
    return true;
}

bool solveSudokuHelper(vector<vector<char>>& board) {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (board[row][col] == '.') {
                for (char num = '1'; num <= '9'; num++) {
                    if (isValidSudoku(board, row, col, num)) {
                        board[row][col] = num;
                        
                        if (solveSudokuHelper(board)) {
                            return true;
                        }
                        
                        board[row][col] = '.';
                    }
                }
                return false;
            }
        }
    }
    return true;
}

void solveSudoku(vector<vector<char>>& board) {
    solveSudokuHelper(board);
}

// 3. Word Search
bool wordSearchHelper(vector<vector<char>>& board, string& word, int row, int col, int idx) {
    if (idx == word.length()) return true;
    
    int m = board.size(), n = board[0].size();
    if (row < 0 || row >= m || col < 0 || col >= n || board[row][col] != word[idx]) {
        return false;
    }
    
    char temp = board[row][col];
    board[row][col] = '#';
    
    bool found = wordSearchHelper(board, word, row + 1, col, idx + 1) ||
                 wordSearchHelper(board, word, row - 1, col, idx + 1) ||
                 wordSearchHelper(board, word, row, col + 1, idx + 1) ||
                 wordSearchHelper(board, word, row, col - 1, idx + 1);
    
    board[row][col] = temp;
    return found;
}

bool exist(vector<vector<char>>& board, string word) {
    int m = board.size(), n = board[0].size();
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (wordSearchHelper(board, word, i, j, 0)) {
                return true;
            }
        }
    }
    return false;
}

// 4. Word Search II (Multiple Words)
struct TrieNode {
    TrieNode* children[26];
    string word;
    
    TrieNode() {
        for (int i = 0; i < 26; i++) {
            children[i] = nullptr;
        }
        word = "";
    }
};

class Trie {
public:
    TrieNode* root;
    
    Trie() {
        root = new TrieNode();
    }
    
    void insert(string word) {
        TrieNode* node = root;
        for (char c : word) {
            int idx = c - 'a';
            if (!node->children[idx]) {
                node->children[idx] = new TrieNode();
            }
            node = node->children[idx];
        }
        node->word = word;
    }
};

void dfsWordSearch2(vector<vector<char>>& board, int i, int j, TrieNode* node, vector<string>& result) {
    int m = board.size(), n = board[0].size();
    if (i < 0 || i >= m || j < 0 || j >= n || board[i][j] == '#') return;
    
    char c = board[i][j];
    if (!node->children[c - 'a']) return;
    
    node = node->children[c - 'a'];
    
    if (!node->word.empty()) {
        result.push_back(node->word);
        node->word = ""; // Avoid duplicates
    }
    
    board[i][j] = '#';
    dfsWordSearch2(board, i + 1, j, node, result);
    dfsWordSearch2(board, i - 1, j, node, result);
    dfsWordSearch2(board, i, j + 1, node, result);
    dfsWordSearch2(board, i, j - 1, node, result);
    board[i][j] = c;
}

vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
    Trie trie;
    for (string& word : words) {
        trie.insert(word);
    }
    
    vector<string> result;
    int m = board.size(), n = board[0].size();
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            dfsWordSearch2(board, i, j, trie.root, result);
        }
    }
    
    return result;
}

// 5. Restore IP Addresses
void restoreIPHelper(string& s, int start, int dots, string current, vector<string>& result) {
    if (dots == 4 && start == s.length()) {
        current.pop_back(); // Remove trailing dot
        result.push_back(current);
        return;
    }
    
    if (dots > 4 || start >= s.length()) return;
    
    for (int len = 1; len <= 3 && start + len <= s.length(); len++) {
        string part = s.substr(start, len);
        
        if ((part.length() > 1 && part[0] == '0') || stoi(part) > 255) {
            continue;
        }
        
        restoreIPHelper(s, start + len, dots + 1, current + part + ".", result);
    }
}

vector<string> restoreIpAddresses(string s) {
    vector<string> result;
    restoreIPHelper(s, 0, 0, "", result);
    return result;
}

// 6. Robot Room Cleaner (Simulation)
class Robot {
public:
    bool move() { return true; }
    void turnLeft() {}
    void turnRight() {}
    void clean() {}
};

void cleanRoomHelper(Robot& robot, int x, int y, int dir, set<pair<int, int>>& visited) {
    visited.insert({x, y});
    robot.clean();
    
    int dx[] = {-1, 0, 1, 0};
    int dy[] = {0, 1, 0, -1};
    
    for (int i = 0; i < 4; i++) {
        int newDir = (dir + i) % 4;
        int newX = x + dx[newDir];
        int newY = y + dy[newDir];
        
        if (visited.find({newX, newY}) == visited.end() && robot.move()) {
            cleanRoomHelper(robot, newX, newY, newDir, visited);
            
            // Go back
            robot.turnRight();
            robot.turnRight();
            robot.move();
            robot.turnRight();
            robot.turnRight();
        }
        
        robot.turnRight();
    }
}

void cleanRoom(Robot& robot) {
    set<pair<int, int>> visited;
    cleanRoomHelper(robot, 0, 0, 0, visited);
}

// 7. Expression Add Operators
void addOperatorsHelper(string& num, int target, int idx, long long value, long long prev, string expr, vector<string>& result) {
    if (idx == num.length()) {
        if (value == target) {
            result.push_back(expr);
        }
        return;
    }
    
    for (int i = idx; i < num.length(); i++) {
        if (i > idx && num[idx] == '0') break;
        
        string part = num.substr(idx, i - idx + 1);
        long long curr = stoll(part);
        
        if (idx == 0) {
            addOperatorsHelper(num, target, i + 1, curr, curr, part, result);
        } else {
            addOperatorsHelper(num, target, i + 1, value + curr, curr, expr + "+" + part, result);
            addOperatorsHelper(num, target, i + 1, value - curr, -curr, expr + "-" + part, result);
            addOperatorsHelper(num, target, i + 1, value - prev + prev * curr, prev * curr, expr + "*" + part, result);
        }
    }
}

vector<string> addOperators(string num, int target) {
    vector<string> result;
    addOperatorsHelper(num, target, 0, 0, 0, "", result);
    return result;
}

int main() {
    // Test N-Queens
    vector<vector<string>> nQueens = solveNQueens(4);
    cout << "N-Queens (n=4): " << nQueens.size() << " solutions" << endl;
    
    // Test Word Search
    vector<vector<char>> board = {
        {'A','B','C','E'},
        {'S','F','C','S'},
        {'A','D','E','E'}
    };
    cout << "Word 'ABCCED' exists: " << (exist(board, "ABCCED") ? "Yes" : "No") << endl;
    
    // Test Restore IP
    vector<string> ips = restoreIpAddresses("25525511135");
    cout << "Valid IP addresses: ";
    for (string& ip : ips) cout << ip << " ";
    cout << endl;
    
    return 0;
}

