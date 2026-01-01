#include <bits/stdc++.h>
using namespace std;

/*
 * BINARY SEARCH IN 2D MATRIX
 * Various approaches for searching in matrices
 */

// Search in row-wise and column-wise sorted matrix (Method 1)
// Start from top-right or bottom-left
bool searchMatrix1(vector<vector<int>>& matrix, int target) {
    if (matrix.empty() || matrix[0].empty()) return false;
    
    int rows = matrix.size();
    int cols = matrix[0].size();
    
    // Start from top-right corner
    int row = 0, col = cols - 1;
    
    while (row < rows && col >= 0) {
        if (matrix[row][col] == target) {
            return true;
        } else if (matrix[row][col] > target) {
            col--;  // Move left
        } else {
            row++;  // Move down
        }
    }
    
    return false;
}

// Search in sorted matrix (each row sorted, first element of each row > last of previous)
bool searchMatrix2(vector<vector<int>>& matrix, int target) {
    if (matrix.empty() || matrix[0].empty()) return false;
    
    int rows = matrix.size();
    int cols = matrix[0].size();
    
    // Treat 2D matrix as 1D sorted array
    int left = 0, right = rows * cols - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int midValue = matrix[mid / cols][mid % cols];
        
        if (midValue == target) {
            return true;
        } else if (midValue < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return false;
}

// Find row with maximum 1s (binary array sorted row-wise)
int findMaxOnesRow(vector<vector<int>>& matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();
    
    int maxRow = -1;
    int maxCount = 0;
    int j = cols - 1;
    
    for (int i = 0; i < rows; i++) {
        // Move left while we see 1s
        while (j >= 0 && matrix[i][j] == 1) {
            j--;
            maxRow = i;
        }
    }
    
    return maxRow;
}

// Find row with maximum 1s using binary search
int countOnes(vector<int>& row) {
    int left = 0, right = row.size() - 1;
    int first = row.size();
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (row[mid] == 1) {
            first = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    
    return row.size() - first;
}

int findMaxOnesRowBS(vector<vector<int>>& matrix) {
    int maxRow = -1;
    int maxCount = 0;
    
    for (int i = 0; i < matrix.size(); i++) {
        int count = countOnes(matrix[i]);
        if (count > maxCount) {
            maxCount = count;
            maxRow = i;
        }
    }
    
    return maxRow;
}

// Find median in row-wise sorted matrix
int countLessEqual(vector<vector<int>>& matrix, int x) {
    int count = 0;
    
    for (auto& row : matrix) {
        count += upper_bound(row.begin(), row.end(), x) - row.begin();
    }
    
    return count;
}

int findMedian(vector<vector<int>>& matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();
    
    int minVal = INT_MAX, maxVal = INT_MIN;
    
    for (int i = 0; i < rows; i++) {
        minVal = min(minVal, matrix[i][0]);
        maxVal = max(maxVal, matrix[i][cols - 1]);
    }
    
    int desired = (rows * cols + 1) / 2;
    
    while (minVal < maxVal) {
        int mid = minVal + (maxVal - minVal) / 2;
        int count = countLessEqual(matrix, mid);
        
        if (count < desired) {
            minVal = mid + 1;
        } else {
            maxVal = mid;
        }
    }
    
    return minVal;
}

// Find kth smallest element in sorted matrix
int kthSmallest(vector<vector<int>>& matrix, int k) {
    int n = matrix.size();
    int left = matrix[0][0];
    int right = matrix[n-1][n-1];
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        int count = 0;
        
        // Count elements <= mid
        for (int i = 0; i < n; i++) {
            count += upper_bound(matrix[i].begin(), matrix[i].end(), mid) - matrix[i].begin();
        }
        
        if (count < k) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    
    return left;
}

// Peak element in 2D matrix
int findMaxInCol(vector<vector<int>>& matrix, int col) {
    int maxRow = 0;
    for (int i = 1; i < matrix.size(); i++) {
        if (matrix[i][col] > matrix[maxRow][col]) {
            maxRow = i;
        }
    }
    return maxRow;
}

vector<int> findPeakGrid(vector<vector<int>>& matrix) {
    int left = 0, right = matrix[0].size() - 1;
    
    while (left <= right) {
        int midCol = left + (right - left) / 2;
        int maxRow = findMaxInCol(matrix, midCol);
        
        int leftVal = (midCol > 0) ? matrix[maxRow][midCol - 1] : -1;
        int rightVal = (midCol < matrix[0].size() - 1) ? matrix[maxRow][midCol + 1] : -1;
        
        if (matrix[maxRow][midCol] > leftVal && matrix[maxRow][midCol] > rightVal) {
            return {maxRow, midCol};
        } else if (matrix[maxRow][midCol] < leftVal) {
            right = midCol - 1;
        } else {
            left = midCol + 1;
        }
    }
    
    return {-1, -1};
}

int main() {
    // Search in row-wise and column-wise sorted matrix
    vector<vector<int>> matrix1 = {
        {1, 4, 7, 11},
        {2, 5, 8, 12},
        {3, 6, 9, 16},
        {10, 13, 14, 17}
    };
    
    cout << "Matrix 1 (row and col sorted):\n";
    for (auto& row : matrix1) {
        for (int x : row) cout << x << " ";
        cout << "\n";
    }
    cout << "Search 5: " << (searchMatrix1(matrix1, 5) ? "Found" : "Not found") << "\n\n";
    
    // Search in fully sorted matrix
    vector<vector<int>> matrix2 = {
        {1, 3, 5, 7},
        {10, 11, 16, 20},
        {23, 30, 34, 60}
    };
    
    cout << "Matrix 2 (fully sorted):\n";
    for (auto& row : matrix2) {
        for (int x : row) cout << x << " ";
        cout << "\n";
    }
    cout << "Search 3: " << (searchMatrix2(matrix2, 3) ? "Found" : "Not found") << "\n\n";
    
    // Row with maximum 1s
    vector<vector<int>> matrix3 = {
        {0, 0, 0, 1},
        {0, 1, 1, 1},
        {0, 0, 1, 1}
    };
    
    cout << "Matrix 3 (binary):\n";
    for (auto& row : matrix3) {
        for (int x : row) cout << x << " ";
        cout << "\n";
    }
    cout << "Row with max 1s: " << findMaxOnesRow(matrix3) << "\n\n";
    
    // Median in matrix
    vector<vector<int>> matrix4 = {
        {1, 3, 5},
        {2, 6, 9},
        {3, 6, 9}
    };
    
    cout << "Median of matrix: " << findMedian(matrix4) << "\n";
    
    return 0;
}

