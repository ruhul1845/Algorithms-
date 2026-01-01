/*
    Segment Tree
    ============
    
    A data structure for efficient range queries and updates.
    
    Operations:
    - Build: O(n)
    - Point Update: O(log n)
    - Range Query: O(log n)
    - Range Update with Lazy: O(log n)
    
    Space Complexity: O(4n) ≈ O(n)
*/

#include <bits/stdc++.h>
using namespace std;

// Basic Segment Tree for Range Sum Queries
class SegmentTree {
    vector<long long> tree;
    int n;
    
    void build(vector<int>& arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
            return;
        }
        
        int mid = (start + end) / 2;
        build(arr, 2 * node, start, mid);
        build(arr, 2 * node + 1, mid + 1, end);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }
    
    void updateHelper(int node, int start, int end, int idx, int val) {
        if (start == end) {
            tree[node] = val;
            return;
        }
        
        int mid = (start + end) / 2;
        if (idx <= mid) {
            updateHelper(2 * node, start, mid, idx, val);
        } else {
            updateHelper(2 * node + 1, mid + 1, end, idx, val);
        }
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }
    
    long long queryHelper(int node, int start, int end, int l, int r) {
        if (r < start || l > end) return 0;
        
        if (l <= start && end <= r) return tree[node];
        
        int mid = (start + end) / 2;
        return queryHelper(2 * node, start, mid, l, r) +
               queryHelper(2 * node + 1, mid + 1, end, l, r);
    }
    
public:
    SegmentTree(vector<int>& arr) {
        n = arr.size();
        tree.resize(4 * n);
        build(arr, 1, 0, n - 1);
    }
    
    void update(int idx, int val) {
        updateHelper(1, 0, n - 1, idx, val);
    }
    
    long long query(int l, int r) {
        return queryHelper(1, 0, n - 1, l, r);
    }
};

// Segment Tree with Lazy Propagation (Range Updates)
class LazySegmentTree {
    vector<long long> tree, lazy;
    int n;
    
    void pushDown(int node, int start, int end) {
        if (lazy[node] != 0) {
            tree[node] += lazy[node] * (end - start + 1);
            
            if (start != end) {
                lazy[2 * node] += lazy[node];
                lazy[2 * node + 1] += lazy[node];
            }
            
            lazy[node] = 0;
        }
    }
    
    void build(vector<int>& arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
            return;
        }
        
        int mid = (start + end) / 2;
        build(arr, 2 * node, start, mid);
        build(arr, 2 * node + 1, mid + 1, end);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }
    
    void updateRangeHelper(int node, int start, int end, int l, int r, long long val) {
        pushDown(node, start, end);
        
        if (r < start || l > end) return;
        
        if (l <= start && end <= r) {
            lazy[node] += val;
            pushDown(node, start, end);
            return;
        }
        
        int mid = (start + end) / 2;
        updateRangeHelper(2 * node, start, mid, l, r, val);
        updateRangeHelper(2 * node + 1, mid + 1, end, l, r, val);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }
    
    long long queryHelper(int node, int start, int end, int l, int r) {
        pushDown(node, start, end);
        
        if (r < start || l > end) return 0;
        
        if (l <= start && end <= r) return tree[node];
        
        int mid = (start + end) / 2;
        return queryHelper(2 * node, start, mid, l, r) +
               queryHelper(2 * node + 1, mid + 1, end, l, r);
    }
    
public:
    LazySegmentTree(vector<int>& arr) {
        n = arr.size();
        tree.resize(4 * n);
        lazy.resize(4 * n, 0);
        build(arr, 1, 0, n - 1);
    }
    
    void updateRange(int l, int r, long long val) {
        updateRangeHelper(1, 0, n - 1, l, r, val);
    }
    
    long long query(int l, int r) {
        return queryHelper(1, 0, n - 1, l, r);
    }
};

// Segment Tree for Range Minimum Query
class MinSegmentTree {
    vector<int> tree;
    int n;
    
    void build(vector<int>& arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
            return;
        }
        
        int mid = (start + end) / 2;
        build(arr, 2 * node, start, mid);
        build(arr, 2 * node + 1, mid + 1, end);
        tree[node] = min(tree[2 * node], tree[2 * node + 1]);
    }
    
    void updateHelper(int node, int start, int end, int idx, int val) {
        if (start == end) {
            tree[node] = val;
            return;
        }
        
        int mid = (start + end) / 2;
        if (idx <= mid) {
            updateHelper(2 * node, start, mid, idx, val);
        } else {
            updateHelper(2 * node + 1, mid + 1, end, idx, val);
        }
        tree[node] = min(tree[2 * node], tree[2 * node + 1]);
    }
    
    int queryHelper(int node, int start, int end, int l, int r) {
        if (r < start || l > end) return INT_MAX;
        
        if (l <= start && end <= r) return tree[node];
        
        int mid = (start + end) / 2;
        return min(queryHelper(2 * node, start, mid, l, r),
                   queryHelper(2 * node + 1, mid + 1, end, l, r));
    }
    
public:
    MinSegmentTree(vector<int>& arr) {
        n = arr.size();
        tree.resize(4 * n);
        build(arr, 1, 0, n - 1);
    }
    
    void update(int idx, int val) {
        updateHelper(1, 0, n - 1, idx, val);
    }
    
    int query(int l, int r) {
        return queryHelper(1, 0, n - 1, l, r);
    }
};

// Segment Tree for Range GCD
class GCDSegmentTree {
    vector<int> tree;
    int n;
    
    int gcd(int a, int b) {
        return b == 0 ? a : gcd(b, a % b);
    }
    
    void build(vector<int>& arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
            return;
        }
        
        int mid = (start + end) / 2;
        build(arr, 2 * node, start, mid);
        build(arr, 2 * node + 1, mid + 1, end);
        tree[node] = gcd(tree[2 * node], tree[2 * node + 1]);
    }
    
    int queryHelper(int node, int start, int end, int l, int r) {
        if (r < start || l > end) return 0;
        
        if (l <= start && end <= r) return tree[node];
        
        int mid = (start + end) / 2;
        return gcd(queryHelper(2 * node, start, mid, l, r),
                   queryHelper(2 * node + 1, mid + 1, end, l, r));
    }
    
public:
    GCDSegmentTree(vector<int>& arr) {
        n = arr.size();
        tree.resize(4 * n);
        build(arr, 1, 0, n - 1);
    }
    
    int query(int l, int r) {
        return queryHelper(1, 0, n - 1, l, r);
    }
};

// Persistent Segment Tree
class PersistentSegmentTree {
    struct Node {
        int sum;
        int left, right;
    };
    
    vector<Node> nodes;
    vector<int> roots;
    int n;
    
    int build(vector<int>& arr, int start, int end) {
        int idx = nodes.size();
        nodes.push_back({0, -1, -1});
        
        if (start == end) {
            nodes[idx].sum = arr[start];
            return idx;
        }
        
        int mid = (start + end) / 2;
        nodes[idx].left = build(arr, start, mid);
        nodes[idx].right = build(arr, mid + 1, end);
        nodes[idx].sum = nodes[nodes[idx].left].sum + nodes[nodes[idx].right].sum;
        
        return idx;
    }
    
    int update(int prevRoot, int start, int end, int idx, int val) {
        int newIdx = nodes.size();
        nodes.push_back(nodes[prevRoot]);
        
        if (start == end) {
            nodes[newIdx].sum = val;
            return newIdx;
        }
        
        int mid = (start + end) / 2;
        if (idx <= mid) {
            nodes[newIdx].left = update(nodes[prevRoot].left, start, mid, idx, val);
        } else {
            nodes[newIdx].right = update(nodes[prevRoot].right, mid + 1, end, idx, val);
        }
        
        nodes[newIdx].sum = nodes[nodes[newIdx].left].sum + nodes[nodes[newIdx].right].sum;
        return newIdx;
    }
    
    int query(int root, int start, int end, int l, int r) {
        if (r < start || l > end) return 0;
        if (l <= start && end <= r) return nodes[root].sum;
        
        int mid = (start + end) / 2;
        return query(nodes[root].left, start, mid, l, r) +
               query(nodes[root].right, mid + 1, end, l, r);
    }
    
public:
    PersistentSegmentTree(vector<int>& arr) {
        n = arr.size();
        roots.push_back(build(arr, 0, n - 1));
    }
    
    void update(int idx, int val) {
        roots.push_back(update(roots.back(), 0, n - 1, idx, val));
    }
    
    int query(int version, int l, int r) {
        return query(roots[version], 0, n - 1, l, r);
    }
    
    int getVersionCount() {
        return roots.size();
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cout << "=== Segment Tree ===" << endl;
    
    // Basic Segment Tree
    vector<int> arr = {1, 3, 5, 7, 9, 11};
    SegmentTree st(arr);
    
    cout << "\nArray: 1 3 5 7 9 11" << endl;
    cout << "Sum [1..3]: " << st.query(1, 3) << endl;
    cout << "Sum [0..5]: " << st.query(0, 5) << endl;
    
    st.update(2, 10);
    cout << "\nAfter update index 2 to 10:" << endl;
    cout << "Sum [1..3]: " << st.query(1, 3) << endl;
    
    // Lazy Segment Tree
    cout << "\n=== Lazy Segment Tree ===" << endl;
    vector<int> arr2 = {1, 2, 3, 4, 5};
    LazySegmentTree lst(arr2);
    
    cout << "Array: 1 2 3 4 5" << endl;
    cout << "Sum [0..4]: " << lst.query(0, 4) << endl;
    
    lst.updateRange(1, 3, 10); // Add 10 to indices 1,2,3
    cout << "\nAfter adding 10 to range [1,3]:" << endl;
    cout << "Sum [0..4]: " << lst.query(0, 4) << endl;
    
    // Min Segment Tree
    cout << "\n=== Min Segment Tree ===" << endl;
    vector<int> arr3 = {5, 2, 8, 1, 9, 3};
    MinSegmentTree mst(arr3);
    
    cout << "Array: 5 2 8 1 9 3" << endl;
    cout << "Min [1..4]: " << mst.query(1, 4) << endl;
    cout << "Min [0..2]: " << mst.query(0, 2) << endl;
    
    // GCD Segment Tree
    cout << "\n=== GCD Segment Tree ===" << endl;
    vector<int> arr4 = {12, 18, 24, 36};
    GCDSegmentTree gst(arr4);
    
    cout << "Array: 12 18 24 36" << endl;
    cout << "GCD [0..3]: " << gst.query(0, 3) << endl;
    cout << "GCD [1..2]: " << gst.query(1, 2) << endl;
    
    // Persistent Segment Tree
    cout << "\n=== Persistent Segment Tree ===" << endl;
    vector<int> arr5 = {1, 2, 3, 4, 5};
    PersistentSegmentTree pst(arr5);
    
    cout << "Array: 1 2 3 4 5" << endl;
    cout << "Version 0, Sum [0..4]: " << pst.query(0, 0, 4) << endl;
    
    pst.update(2, 10);
    cout << "\nAfter update index 2 to 10:" << endl;
    cout << "Version 0, Sum [0..4]: " << pst.query(0, 0, 4) << endl;
    cout << "Version 1, Sum [0..4]: " << pst.query(1, 0, 4) << endl;
    
    return 0;
}





