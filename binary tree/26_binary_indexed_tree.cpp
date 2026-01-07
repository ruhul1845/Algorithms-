/*
    Binary Indexed Tree (Fenwick Tree)
    ==================================
    
    A data structure for efficient prefix sum queries and point updates.
    
    Operations:
    - Point Update: O(log n)
    - Prefix Sum Query: O(log n)
    - Range Sum Query: O(log n)
    
    Space Complexity: O(n)
*/

#include <bits/stdc++.h>
using namespace std;

// Basic Fenwick Tree for sum queries
class FenwickTree {
    vector<int> tree;
    int n;
    
    // Get lowest set bit
    int lowbit(int x) {
        return x & (-x);
    }
    
public:
    FenwickTree(int n) : n(n), tree(n + 1, 0) {}
    
    // Build from array
    FenwickTree(vector<int>& arr) : n(arr.size()), tree(arr.size() + 1, 0) {
        for (int i = 0; i < n; i++) {
            update(i + 1, arr[i]);
        }
    }
    
    // Add delta to index i (1-indexed)
    void update(int i, int delta) {
        while (i <= n) {
            tree[i] += delta;
            i += lowbit(i);
        }
    }
    
    // Get sum of first i elements (1-indexed)
    int prefixSum(int i) {
        int sum = 0;
        while (i > 0) {
            sum += tree[i];
            i -= lowbit(i);
        }
        return sum;
    }
    
    // Get sum in range [l, r] (1-indexed)
    int rangeSum(int l, int r) {
        return prefixSum(r) - prefixSum(l - 1);
    }
    
    // Get single element (1-indexed)
    int get(int i) {
        return rangeSum(i, i);
    }
    
    // Set value at index (1-indexed)
    void set(int i, int val) {
        int curr = get(i);
        update(i, val - curr);
    }
};

// 2D Fenwick Tree
class FenwickTree2D {
    vector<vector<int>> tree;
    int rows, cols;
    
    int lowbit(int x) { return x & (-x); }
    
public:
    FenwickTree2D(int rows, int cols) : rows(rows), cols(cols), 
                                         tree(rows + 1, vector<int>(cols + 1, 0)) {}
    
    // Build from 2D matrix
    FenwickTree2D(vector<vector<int>>& matrix) {
        rows = matrix.size();
        cols = matrix[0].size();
        tree.assign(rows + 1, vector<int>(cols + 1, 0));
        
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                update(i + 1, j + 1, matrix[i][j]);
            }
        }
    }
    
    void update(int row, int col, int delta) {
        for (int i = row; i <= rows; i += lowbit(i)) {
            for (int j = col; j <= cols; j += lowbit(j)) {
                tree[i][j] += delta;
            }
        }
    }
    
    // Sum of rectangle from (1,1) to (row, col)
    int prefixSum(int row, int col) {
        int sum = 0;
        for (int i = row; i > 0; i -= lowbit(i)) {
            for (int j = col; j > 0; j -= lowbit(j)) {
                sum += tree[i][j];
            }
        }
        return sum;
    }
    
    // Sum of rectangle from (r1, c1) to (r2, c2) (1-indexed)
    int rangeSum(int r1, int c1, int r2, int c2) {
        return prefixSum(r2, c2) - prefixSum(r1 - 1, c2) - 
               prefixSum(r2, c1 - 1) + prefixSum(r1 - 1, c1 - 1);
    }
};

// Fenwick Tree for range update, point query
class FenwickTreeRangeUpdate {
    vector<long long> tree;
    int n;
    
    int lowbit(int x) { return x & (-x); }
    
    void add(int i, long long delta) {
        while (i <= n) {
            tree[i] += delta;
            i += lowbit(i);
        }
    }
    
public:
    FenwickTreeRangeUpdate(int n) : n(n), tree(n + 1, 0) {}
    
    // Add delta to range [l, r]
    void rangeUpdate(int l, int r, long long delta) {
        add(l, delta);
        add(r + 1, -delta);
    }
    
    // Get value at index i
    long long pointQuery(int i) {
        long long sum = 0;
        while (i > 0) {
            sum += tree[i];
            i -= lowbit(i);
        }
        return sum;
    }
};

// Fenwick Tree for range update, range query
class FenwickTreeRangeUpdateQuery {
    vector<long long> tree1, tree2;
    int n;
    
    int lowbit(int x) { return x & (-x); }
    
    void add(vector<long long>& tree, int i, long long delta) {
        while (i <= n) {
            tree[i] += delta;
            i += lowbit(i);
        }
    }
    
    long long sum(vector<long long>& tree, int i) {
        long long s = 0;
        while (i > 0) {
            s += tree[i];
            i -= lowbit(i);
        }
        return s;
    }
    
public:
    FenwickTreeRangeUpdateQuery(int n) : n(n), tree1(n + 1, 0), tree2(n + 1, 0) {}
    
    // Add delta to range [l, r]
    void rangeUpdate(int l, int r, long long delta) {
        add(tree1, l, delta);
        add(tree1, r + 1, -delta);
        add(tree2, l, delta * (l - 1));
        add(tree2, r + 1, -delta * r);
    }
    
    // Get prefix sum [1, i]
    long long prefixSum(int i) {
        return sum(tree1, i) * i - sum(tree2, i);
    }
    
    // Get range sum [l, r]
    long long rangeSum(int l, int r) {
        return prefixSum(r) - prefixSum(l - 1);
    }
};

// Count inversions using Fenwick Tree
long long countInversions(vector<int>& arr) {
    int n = arr.size();
    
    // Coordinate compression
    vector<int> sorted_arr = arr;
    sort(sorted_arr.begin(), sorted_arr.end());
    sorted_arr.erase(unique(sorted_arr.begin(), sorted_arr.end()), sorted_arr.end());
    
    unordered_map<int, int> rank;
    for (int i = 0; i < sorted_arr.size(); i++) {
        rank[sorted_arr[i]] = i + 1;
    }
    
    FenwickTree ft(sorted_arr.size());
    long long inversions = 0;
    
    // Process from right to left
    for (int i = n - 1; i >= 0; i--) {
        inversions += ft.prefixSum(rank[arr[i]] - 1);
        ft.update(rank[arr[i]], 1);
    }
    
    return inversions;
}

// Count smaller elements after self
vector<int> countSmaller(vector<int>& nums) {
    int n = nums.size();
    vector<int> result(n);
    
    // Coordinate compression
    vector<int> sorted_nums = nums;
    sort(sorted_nums.begin(), sorted_nums.end());
    sorted_nums.erase(unique(sorted_nums.begin(), sorted_nums.end()), sorted_nums.end());
    
    unordered_map<int, int> rank;
    for (int i = 0; i < sorted_nums.size(); i++) {
        rank[sorted_nums[i]] = i + 1;
    }
    
    FenwickTree ft(sorted_nums.size());
    
    for (int i = n - 1; i >= 0; i--) {
        result[i] = ft.prefixSum(rank[nums[i]] - 1);
        ft.update(rank[nums[i]], 1);
    }
    
    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cout << "=== Binary Indexed Tree (Fenwick Tree) ===" << endl;
    
    // Basic Fenwick Tree
    vector<int> arr = {1, 3, 5, 7, 9, 11};
    FenwickTree ft(arr);
    
    cout << "\nArray: 1 3 5 7 9 11" << endl;
    cout << "Prefix sum [1..3]: " << ft.prefixSum(3) << endl;
    cout << "Range sum [2..5]: " << ft.rangeSum(2, 5) << endl;
    
    ft.update(3, 5); // Add 5 to index 3
    cout << "\nAfter adding 5 to index 3:" << endl;
    cout << "Range sum [2..5]: " << ft.rangeSum(2, 5) << endl;
    
    // 2D Fenwick Tree
    vector<vector<int>> matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    
    FenwickTree2D ft2d(matrix);
    
    cout << "\n=== 2D Fenwick Tree ===" << endl;
    cout << "Matrix 3x3" << endl;
    cout << "Sum of (1,1) to (2,2): " << ft2d.rangeSum(1, 1, 2, 2) << endl;
    cout << "Sum of (2,2) to (3,3): " << ft2d.rangeSum(2, 2, 3, 3) << endl;
    
    // Range Update
    cout << "\n=== Range Update Fenwick Tree ===" << endl;
    FenwickTreeRangeUpdate ftru(6);
    ftru.rangeUpdate(2, 4, 5); // Add 5 to indices 2,3,4
    
    cout << "After adding 5 to range [2,4]:" << endl;
    for (int i = 1; i <= 6; i++) {
        cout << "Index " << i << ": " << ftru.pointQuery(i) << endl;
    }
    
    // Count inversions
    cout << "\n=== Applications ===" << endl;
    vector<int> inv_arr = {5, 2, 6, 1};
    cout << "Array: 5 2 6 1" << endl;
    cout << "Inversions: " << countInversions(inv_arr) << endl;
    
    // Count smaller after self
    vector<int> nums = {5, 2, 6, 1};
    auto smaller = countSmaller(nums);
    cout << "\nSmaller elements after self: ";
    for (int x : smaller) cout << x << " ";
    cout << endl;
    
    return 0;
}
















