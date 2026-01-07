/*
 * Matrix/2D Array Problems
 * Common interview questions on matrices
 */

#include <bits/stdc++.h>
using namespace std;

// 1. Matrix Rotation (90 degrees clockwise)
void rotate(vector<vector<int>>& matrix) {
    int n = matrix.size();
    
    // Transpose
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            swap(matrix[i][j], matrix[j][i]);
        }
    }
    
    // Reverse each row
    for (int i = 0; i < n; i++) {
        reverse(matrix[i].begin(), matrix[i].end());
    }
}

// 2. Spiral Matrix Traversal
vector<int> spiralOrder(vector<vector<int>>& matrix) {
    vector<int> result;
    if (matrix.empty()) return result;
    
    int top = 0, bottom = matrix.size() - 1;
    int left = 0, right = matrix[0].size() - 1;
    
    while (top <= bottom && left <= right) {
        // Right
        for (int j = left; j <= right; j++) {
            result.push_back(matrix[top][j]);
        }
        top++;
        
        // Down
        for (int i = top; i <= bottom; i++) {
            result.push_back(matrix[i][right]);
        }
        right--;
        
        // Left
        if (top <= bottom) {
            for (int j = right; j >= left; j--) {
                result.push_back(matrix[bottom][j]);
            }
            bottom--;
        }
        
        // Up
        if (left <= right) {
            for (int i = bottom; i >= top; i--) {
                result.push_back(matrix[i][left]);
            }
            left++;
        }
    }
    return result;
}

// 3. Set Matrix Zeroes
void setZeroes(vector<vector<int>>& matrix) {
    int m = matrix.size(), n = matrix[0].size();
    bool firstRowZero = false, firstColZero = false;
    
    // Check if first row/col has zero
    for (int j = 0; j < n; j++) {
        if (matrix[0][j] == 0) firstRowZero = true;
    }
    for (int i = 0; i < m; i++) {
        if (matrix[i][0] == 0) firstColZero = true;
    }
    
    // Mark zeros on first row and column
    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            if (matrix[i][j] == 0) {
                matrix[i][0] = 0;
                matrix[0][j] = 0;
            }
        }
    }
    
    // Set zeros based on marks
    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            if (matrix[i][0] == 0 || matrix[0][j] == 0) {
                matrix[i][j] = 0;
            }
        }
    }
    
    // Handle first row and column
    if (firstRowZero) {
        for (int j = 0; j < n; j++) matrix[0][j] = 0;
    }
    if (firstColZero) {
        for (int i = 0; i < m; i++) matrix[i][0] = 0;
    }
}

// 4. Search in 2D Matrix
bool searchMatrix(vector<vector<int>>& matrix, int target) {
    if (matrix.empty()) return false;
    
    int m = matrix.size(), n = matrix[0].size();
    int left = 0, right = m * n - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int midVal = matrix[mid / n][mid % n];
        
        if (midVal == target) {
            return true;
        } else if (midVal < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return false;
}

// 5. Number of Islands (DFS)
void dfs(vector<vector<char>>& grid, int i, int j) {
    int m = grid.size(), n = grid[0].size();
    if (i < 0 || i >= m || j < 0 || j >= n || grid[i][j] == '0') {
        return;
    }
    
    grid[i][j] = '0';
    dfs(grid, i + 1, j);
    dfs(grid, i - 1, j);
    dfs(grid, i, j + 1);
    dfs(grid, i, j - 1);
}

int numIslands(vector<vector<char>>& grid) {
    if (grid.empty()) return 0;
    
    int count = 0;
    int m = grid.size(), n = grid[0].size();
    
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

// 6. Word Search
bool dfsWordSearch(vector<vector<char>>& board, string& word, int i, int j, int idx) {
    if (idx == word.length()) return true;
    
    int m = board.size(), n = board[0].size();
    if (i < 0 || i >= m || j < 0 || j >= n || board[i][j] != word[idx]) {
        return false;
    }
    
    char temp = board[i][j];
    board[i][j] = '#';
    
    bool found = dfsWordSearch(board, word, i+1, j, idx+1) ||
                 dfsWordSearch(board, word, i-1, j, idx+1) ||
                 dfsWordSearch(board, word, i, j+1, idx+1) ||
                 dfsWordSearch(board, word, i, j-1, idx+1);
    
    board[i][j] = temp;
    return found;
}

bool exist(vector<vector<char>>& board, string word) {
    int m = board.size(), n = board[0].size();
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (dfsWordSearch(board, word, i, j, 0)) {
                return true;
            }
        }
    }
    return false;
}

// 7. Diagonal Traverse
vector<int> findDiagonalOrder(vector<vector<int>>& mat) {
    if (mat.empty()) return {};
    
    int m = mat.size(), n = mat[0].size();
    vector<int> result;
    
    for (int d = 0; d < m + n - 1; d++) {
        vector<int> temp;
        int row = d < n ? 0 : d - n + 1;
        int col = d < n ? d : n - 1;
        
        while (row < m && col >= 0) {
            temp.push_back(mat[row][col]);
            row++;
            col--;
        }
        
        if (d % 2 == 0) {
            reverse(temp.begin(), temp.end());
        }
        
        result.insert(result.end(), temp.begin(), temp.end());
    }
    return result;
}

int main() {
    // Test Matrix Rotation
    vector<vector<int>> matrix = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    rotate(matrix);
    cout << "Rotated Matrix:" << endl;
    for (auto& row : matrix) {
        for (int x : row) cout << x << " ";
        cout << endl;
    }
    
    // Test Spiral Order
    vector<vector<int>> matrix2 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    vector<int> spiral = spiralOrder(matrix2);
    cout << "\nSpiral Order: ";
    for (int x : spiral) cout << x << " ";
    cout << endl;
    
    return 0;
}










