/*
    Height and Depth of Binary Tree
    ================================
    
    Height: Number of edges on the longest path from node to a leaf
    Depth: Number of edges from root to the node
    
    Note: Some definitions use number of nodes instead of edges.
    Here we use edges (height of leaf = 0, height of empty tree = -1)
    
    Time Complexity: O(n)
    Space Complexity: O(h) where h is height of tree
*/

#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// Height of tree (number of nodes on longest path - 1)
// Empty tree: -1, Single node: 0
int heightEdges(TreeNode* root) {
    if (!root) return -1;
    return 1 + max(heightEdges(root->left), heightEdges(root->right));
}

// Height of tree (number of nodes on longest path)
// Empty tree: 0, Single node: 1
int heightNodes(TreeNode* root) {
    if (!root) return 0;
    return 1 + max(heightNodes(root->left), heightNodes(root->right));
}

// Iterative height using level order
int heightIterative(TreeNode* root) {
    if (!root) return 0;
    
    queue<TreeNode*> q;
    q.push(root);
    int height = 0;
    
    while (!q.empty()) {
        int size = q.size();
        height++;
        
        for (int i = 0; i < size; i++) {
            TreeNode* curr = q.front();
            q.pop();
            
            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
    }
    
    return height;
}

// Depth of a specific node (root has depth 0)
int findDepth(TreeNode* root, int target) {
    if (!root) return -1;
    if (root->val == target) return 0;
    
    int leftDepth = findDepth(root->left, target);
    if (leftDepth != -1) return leftDepth + 1;
    
    int rightDepth = findDepth(root->right, target);
    if (rightDepth != -1) return rightDepth + 1;
    
    return -1;
}

// Height of a specific node
int findHeight(TreeNode* root, int target) {
    if (!root) return -1;
    
    if (root->val == target) {
        return heightNodes(root) - 1;
    }
    
    int leftHeight = findHeight(root->left, target);
    if (leftHeight != -1) return leftHeight;
    
    return findHeight(root->right, target);
}

// Minimum depth (shortest path from root to any leaf)
int minDepth(TreeNode* root) {
    if (!root) return 0;
    
    // If only one child exists, go to that subtree
    if (!root->left) return 1 + minDepth(root->right);
    if (!root->right) return 1 + minDepth(root->left);
    
    return 1 + min(minDepth(root->left), minDepth(root->right));
}

// Minimum depth using BFS (more efficient - stops early)
int minDepthBFS(TreeNode* root) {
    if (!root) return 0;
    
    queue<pair<TreeNode*, int>> q;
    q.push({root, 1});
    
    while (!q.empty()) {
        auto [node, depth] = q.front();
        q.pop();
        
        // First leaf found
        if (!node->left && !node->right) return depth;
        
        if (node->left) q.push({node->left, depth + 1});
        if (node->right) q.push({node->right, depth + 1});
    }
    
    return 0;
}

// Maximum depth at each level
vector<int> maxDepthAtLevel(TreeNode* root) {
    vector<int> result;
    if (!root) return result;
    
    queue<TreeNode*> q;
    q.push(root);
    int level = 0;
    
    while (!q.empty()) {
        int size = q.size();
        int maxVal = INT_MIN;
        
        for (int i = 0; i < size; i++) {
            TreeNode* curr = q.front();
            q.pop();
            maxVal = max(maxVal, curr->val);
            
            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
        
        result.push_back(maxVal);
        level++;
    }
    
    return result;
}

// Get all nodes at given depth
vector<int> getNodesAtDepth(TreeNode* root, int k) {
    vector<int> result;
    
    function<void(TreeNode*, int)> dfs = [&](TreeNode* node, int depth) {
        if (!node) return;
        if (depth == k) {
            result.push_back(node->val);
            return;
        }
        dfs(node->left, depth + 1);
        dfs(node->right, depth + 1);
    };
    
    dfs(root, 0);
    return result;
}

// Sum of nodes at maximum depth
int sumDeepestLeaves(TreeNode* root) {
    if (!root) return 0;
    
    queue<TreeNode*> q;
    q.push(root);
    int sum = 0;
    
    while (!q.empty()) {
        int size = q.size();
        sum = 0;  // Reset for each level
        
        for (int i = 0; i < size; i++) {
            TreeNode* curr = q.front();
            q.pop();
            sum += curr->val;
            
            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
    }
    
    return sum;
}

// Check if tree is complete binary tree
bool isComplete(TreeNode* root) {
    if (!root) return true;
    
    queue<TreeNode*> q;
    q.push(root);
    bool foundNull = false;
    
    while (!q.empty()) {
        TreeNode* curr = q.front();
        q.pop();
        
        if (!curr) {
            foundNull = true;
        } else {
            if (foundNull) return false;
            q.push(curr->left);
            q.push(curr->right);
        }
    }
    
    return true;
}

// Count nodes at each depth
map<int, int> countNodesAtDepth(TreeNode* root) {
    map<int, int> counts;
    
    function<void(TreeNode*, int)> dfs = [&](TreeNode* node, int depth) {
        if (!node) return;
        counts[depth]++;
        dfs(node->left, depth + 1);
        dfs(node->right, depth + 1);
    };
    
    dfs(root, 0);
    return counts;
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
        Tree structure:
              1
            /   \
           2     3
          / \     \
         4   5     6
        /
       7
    */
    
    vector<int> nodes = {1, 2, 3, 4, 5, -1, 6, 7};
    TreeNode* root = buildTree(nodes);
    
    cout << "=== Height and Depth Problems ===" << endl;
    cout << "Height (edges): " << heightEdges(root) << endl;
    cout << "Height (nodes): " << heightNodes(root) << endl;
    cout << "Height (iterative): " << heightIterative(root) << endl;
    
    cout << "\nDepth of node 4: " << findDepth(root, 4) << endl;
    cout << "Depth of node 7: " << findDepth(root, 7) << endl;
    cout << "Height of node 2: " << findHeight(root, 2) << endl;
    
    cout << "\nMinimum depth: " << minDepth(root) << endl;
    cout << "Minimum depth (BFS): " << minDepthBFS(root) << endl;
    
    cout << "\nNodes at depth 2: ";
    for (int x : getNodesAtDepth(root, 2)) cout << x << " ";
    cout << endl;
    
    cout << "Sum of deepest leaves: " << sumDeepestLeaves(root) << endl;
    
    cout << "\nMax value at each level: ";
    for (int x : maxDepthAtLevel(root)) cout << x << " ";
    cout << endl;
    
    cout << "\nNodes count at each depth:" << endl;
    for (auto& [depth, count] : countNodesAtDepth(root)) {
        cout << "  Depth " << depth << ": " << count << " nodes" << endl;
    }
    
    cout << "\nIs complete binary tree: " << (isComplete(root) ? "Yes" : "No") << endl;
    
    return 0;
}
















