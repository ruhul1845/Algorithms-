/*
    Binary Tree Views
    =================
    
    Different views of binary tree:
    1. Left View - First node of each level
    2. Right View - Last node of each level  
    3. Top View - Nodes visible from top
    4. Bottom View - Nodes visible from bottom
    
    Time Complexity: O(n)
    Space Complexity: O(n)
*/

#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// LEFT VIEW - First node at each level
vector<int> leftView(TreeNode* root) {
    vector<int> result;
    if (!root) return result;
    
    queue<TreeNode*> q;
    q.push(root);
    
    while (!q.empty()) {
        int size = q.size();
        
        for (int i = 0; i < size; i++) {
            TreeNode* curr = q.front();
            q.pop();
            
            if (i == 0) result.push_back(curr->val);
            
            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
    }
    
    return result;
}

// Left View - Recursive
void leftViewRecursive(TreeNode* root, int level, int& maxLevel, vector<int>& result) {
    if (!root) return;
    
    if (level > maxLevel) {
        result.push_back(root->val);
        maxLevel = level;
    }
    
    leftViewRecursive(root->left, level + 1, maxLevel, result);
    leftViewRecursive(root->right, level + 1, maxLevel, result);
}

// RIGHT VIEW - Last node at each level
vector<int> rightView(TreeNode* root) {
    vector<int> result;
    if (!root) return result;
    
    queue<TreeNode*> q;
    q.push(root);
    
    while (!q.empty()) {
        int size = q.size();
        
        for (int i = 0; i < size; i++) {
            TreeNode* curr = q.front();
            q.pop();
            
            if (i == size - 1) result.push_back(curr->val);
            
            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
    }
    
    return result;
}

// Right View - Recursive
void rightViewRecursive(TreeNode* root, int level, int& maxLevel, vector<int>& result) {
    if (!root) return;
    
    if (level > maxLevel) {
        result.push_back(root->val);
        maxLevel = level;
    }
    
    rightViewRecursive(root->right, level + 1, maxLevel, result);
    rightViewRecursive(root->left, level + 1, maxLevel, result);
}

// TOP VIEW - Nodes visible from top
vector<int> topView(TreeNode* root) {
    vector<int> result;
    if (!root) return result;
    
    map<int, int> topNodes; // horizontal distance -> node value
    queue<pair<TreeNode*, int>> q; // node, horizontal distance
    q.push({root, 0});
    
    while (!q.empty()) {
        auto [node, hd] = q.front();
        q.pop();
        
        // Only first node at each horizontal distance
        if (topNodes.find(hd) == topNodes.end()) {
            topNodes[hd] = node->val;
        }
        
        if (node->left) q.push({node->left, hd - 1});
        if (node->right) q.push({node->right, hd + 1});
    }
    
    for (auto& [hd, val] : topNodes) {
        result.push_back(val);
    }
    
    return result;
}

// BOTTOM VIEW - Nodes visible from bottom
vector<int> bottomView(TreeNode* root) {
    vector<int> result;
    if (!root) return result;
    
    map<int, int> bottomNodes; // horizontal distance -> node value
    queue<pair<TreeNode*, int>> q;
    q.push({root, 0});
    
    while (!q.empty()) {
        auto [node, hd] = q.front();
        q.pop();
        
        // Override with last node at each horizontal distance
        bottomNodes[hd] = node->val;
        
        if (node->left) q.push({node->left, hd - 1});
        if (node->right) q.push({node->right, hd + 1});
    }
    
    for (auto& [hd, val] : bottomNodes) {
        result.push_back(val);
    }
    
    return result;
}

// VERTICAL ORDER TRAVERSAL
vector<vector<int>> verticalOrder(TreeNode* root) {
    vector<vector<int>> result;
    if (!root) return result;
    
    map<int, vector<int>> columns;
    queue<pair<TreeNode*, int>> q;
    q.push({root, 0});
    
    while (!q.empty()) {
        auto [node, col] = q.front();
        q.pop();
        
        columns[col].push_back(node->val);
        
        if (node->left) q.push({node->left, col - 1});
        if (node->right) q.push({node->right, col + 1});
    }
    
    for (auto& [col, vals] : columns) {
        result.push_back(vals);
    }
    
    return result;
}

// VERTICAL ORDER WITH SORTING (Same row, col -> sorted)
vector<vector<int>> verticalTraversal(TreeNode* root) {
    vector<vector<int>> result;
    if (!root) return result;
    
    // map: column -> map: row -> multiset of values
    map<int, map<int, multiset<int>>> nodes;
    queue<tuple<TreeNode*, int, int>> q; // node, row, col
    q.push({root, 0, 0});
    
    while (!q.empty()) {
        auto [node, row, col] = q.front();
        q.pop();
        
        nodes[col][row].insert(node->val);
        
        if (node->left) q.push({node->left, row + 1, col - 1});
        if (node->right) q.push({node->right, row + 1, col + 1});
    }
    
    for (auto& [col, rows] : nodes) {
        vector<int> colVals;
        for (auto& [row, vals] : rows) {
            for (int val : vals) {
                colVals.push_back(val);
            }
        }
        result.push_back(colVals);
    }
    
    return result;
}

// BOUNDARY TRAVERSAL
vector<int> boundaryTraversal(TreeNode* root) {
    vector<int> result;
    if (!root) return result;
    
    auto isLeaf = [](TreeNode* node) {
        return !node->left && !node->right;
    };
    
    // Add root if not leaf
    if (!isLeaf(root)) result.push_back(root->val);
    
    // Add left boundary (excluding leaves)
    TreeNode* curr = root->left;
    while (curr) {
        if (!isLeaf(curr)) result.push_back(curr->val);
        curr = curr->left ? curr->left : curr->right;
    }
    
    // Add all leaves (left to right)
    function<void(TreeNode*)> addLeaves = [&](TreeNode* node) {
        if (!node) return;
        if (isLeaf(node)) {
            result.push_back(node->val);
            return;
        }
        addLeaves(node->left);
        addLeaves(node->right);
    };
    addLeaves(root);
    
    // Add right boundary (excluding leaves, in reverse)
    vector<int> rightBoundary;
    curr = root->right;
    while (curr) {
        if (!isLeaf(curr)) rightBoundary.push_back(curr->val);
        curr = curr->right ? curr->right : curr->left;
    }
    reverse(rightBoundary.begin(), rightBoundary.end());
    for (int val : rightBoundary) result.push_back(val);
    
    return result;
}

// DIAGONAL TRAVERSAL
vector<vector<int>> diagonalTraversal(TreeNode* root) {
    vector<vector<int>> result;
    if (!root) return result;
    
    map<int, vector<int>> diagonals;
    queue<pair<TreeNode*, int>> q;
    q.push({root, 0});
    
    while (!q.empty()) {
        auto [node, diag] = q.front();
        q.pop();
        
        diagonals[diag].push_back(node->val);
        
        if (node->left) q.push({node->left, diag + 1});
        if (node->right) q.push({node->right, diag});
    }
    
    for (auto& [d, vals] : diagonals) {
        result.push_back(vals);
    }
    
    return result;
}

TreeNode* buildTree(vector<int>& nodes) {
    if (nodes.empty() || nodes[0] == -1) return nullptr;
    
    TreeNode* root = new TreeNode(nodes[0]);
    queue<TreeNode*> q;
    q.push(root);
    
    int i = 1;
    while (!q.empty() && i < nodes.size()) {
        TreeNode* curr = q.front();
        q.pop();
        
        if (i < nodes.size() && nodes[i] != -1) {
            curr->left = new TreeNode(nodes[i]);
            q.push(curr->left);
        }
        i++;
        
        if (i < nodes.size() && nodes[i] != -1) {
            curr->right = new TreeNode(nodes[i]);
            q.push(curr->right);
        }
        i++;
    }
    
    return root;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    /*
              1
            /   \
           2     3
          / \   / \
         4   5 6   7
            /   \
           8     9
    */
    
    vector<int> nodes = {1, 2, 3, 4, 5, 6, 7, -1, -1, 8, -1, -1, 9};
    TreeNode* root = buildTree(nodes);
    
    cout << "=== Binary Tree Views ===" << endl;
    
    cout << "\nLeft View: ";
    for (int x : leftView(root)) cout << x << " ";
    cout << endl;
    
    cout << "Right View: ";
    for (int x : rightView(root)) cout << x << " ";
    cout << endl;
    
    cout << "Top View: ";
    for (int x : topView(root)) cout << x << " ";
    cout << endl;
    
    cout << "Bottom View: ";
    for (int x : bottomView(root)) cout << x << " ";
    cout << endl;
    
    cout << "\nVertical Order Traversal:" << endl;
    for (auto& col : verticalOrder(root)) {
        cout << "  [ ";
        for (int x : col) cout << x << " ";
        cout << "]" << endl;
    }
    
    cout << "\nDiagonal Traversal:" << endl;
    for (auto& diag : diagonalTraversal(root)) {
        cout << "  [ ";
        for (int x : diag) cout << x << " ";
        cout << "]" << endl;
    }
    
    cout << "\nBoundary Traversal: ";
    for (int x : boundaryTraversal(root)) cout << x << " ";
    cout << endl;
    
    return 0;
}

