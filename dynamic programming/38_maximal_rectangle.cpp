/*
    Maximal Rectangle
    Problem: Find largest rectangle containing only 1s in binary matrix.
    
    Example: matrix = [["1","0","1","0","0"],["1","0","1","1","1"],
                       ["1","1","1","1","1"],["1","0","0","1","0"]]
             Output: 6
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== DP + Histogram Approach ====================
class Solution {
private:
    // Largest rectangle in histogram
    int largestRectangleInHistogram(vector<int>& heights) {
        stack<int> st;
        int maxArea = 0;
        int n = heights.size();
        
        for (int i = 0; i <= n; i++) {
            int h = (i == n) ? 0 : heights[i];
            
            while (!st.empty() && heights[st.top()] > h) {
                int height = heights[st.top()];
                st.pop();
                int width = st.empty() ? i : i - st.top() - 1;
                maxArea = max(maxArea, height * width);
            }
            st.push(i);
        }
        
        return maxArea;
    }
    
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        if (matrix.empty()) return 0;
        
        int m = matrix.size(), n = matrix[0].size();
        vector<int> heights(n, 0);
        int maxArea = 0;
        
        for (int i = 0; i < m; i++) {
            // Build histogram for current row
            for (int j = 0; j < n; j++) {
                heights[j] = (matrix[i][j] == '1') ? heights[j] + 1 : 0;
            }
            
            // Find max rectangle in this histogram
            maxArea = max(maxArea, largestRectangleInHistogram(heights));
        }
        
        return maxArea;
    }
};

// ==================== PURE DP APPROACH ====================
class PureDP {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        if (matrix.empty()) return 0;
        
        int m = matrix.size(), n = matrix[0].size();
        
        // height[j] = number of consecutive 1s above (including current)
        // left[j] = leftmost column of rectangle with height[j]
        // right[j] = rightmost column of rectangle with height[j]
        
        vector<int> height(n, 0);
        vector<int> left(n, 0);
        vector<int> right(n, n);
        
        int maxArea = 0;
        
        for (int i = 0; i < m; i++) {
            int curLeft = 0, curRight = n;
            
            // Update height
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == '1') {
                    height[j]++;
                } else {
                    height[j] = 0;
                }
            }
            
            // Update left
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == '1') {
                    left[j] = max(left[j], curLeft);
                } else {
                    left[j] = 0;
                    curLeft = j + 1;
                }
            }
            
            // Update right
            for (int j = n - 1; j >= 0; j--) {
                if (matrix[i][j] == '1') {
                    right[j] = min(right[j], curRight);
                } else {
                    right[j] = n;
                    curRight = j;
                }
            }
            
            // Calculate area
            for (int j = 0; j < n; j++) {
                maxArea = max(maxArea, (right[j] - left[j]) * height[j]);
            }
        }
        
        return maxArea;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int m, n;
    cout << "Enter matrix dimensions (m n): ";
    cin >> m >> n;
    
    vector<vector<char>> matrix(m, vector<char>(n));
    cout << "Enter matrix (0s and 1s):" << endl;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> matrix[i][j];
        }
    }
    
    Solution sol;
    PureDP dp;
    
    cout << "\n--- Results ---" << endl;
    cout << "Histogram Method: " << sol.maximalRectangle(matrix) << endl;
    cout << "Pure DP: " << dp.maximalRectangle(matrix) << endl;
    
    return 0;
}







