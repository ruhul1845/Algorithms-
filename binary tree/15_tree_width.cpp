/*
    Binary Tree Width Problems
    ==========================
    
    Maximum width and related problems.
    Width can be defined as:
    1. Max nodes at any level
    2. Max distance between leftmost and rightmost nodes at any level
    
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

// Maximum width (count of nodes at any level)
int maxWidthCount(TreeNode* root) {
    if (!root) return 0;
    
    int maxWidth = 0;
    queue<TreeNode*> q;
    q.push(root);
    
    while (!q.empty()) {
        int size = q.size();
        maxWidth = max(maxWidth, size);
        
        for (int i = 0; i < size; i++) {
            TreeNode* curr = q.front();
            q.pop();
            
            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
    }
    
    return maxWidth;
}

// Maximum width (including nulls between leftmost and rightmost)
// Uses position indexing
int widthOfBinaryTree(TreeNode* root) {
    if (!root) return 0;
    
    int maxWidth = 0;
    queue<pair<TreeNode*, unsigned long long>> q;
    q.push({root, 0});
    
    while (!q.empty()) {
        int size = q.size();
        unsigned long long left = q.front().second;
        unsigned long long right = left;
        
        for (int i = 0; i < size; i++) {
            auto [node, pos] = q.front();
            q.pop();
            right = pos;
            
            // Normalize position to avoid overflow
            unsigned long long normalizedPos = pos - left;
            
            if (node->left) {
                q.push({node->left, 2 * normalizedPos});
            }
            if (node->right) {
                q.push({node->right, 2 * normalizedPos + 1});
            }
        }
        
        maxWidth = max(maxWidth, (int)(right - left + 1));
    }
    
    return maxWidth;
}

// Width at each level
vector<int> widthAtEachLevel(TreeNode* root) {
    vector<int> result;
    if (!root) return result;
    
    queue<TreeNode*> q;
    q.push(root);
    
    while (!q.empty()) {
        int size = q.size();
        result.push_back(size);
        
        for (int i = 0; i < size; i++) {
            TreeNode* curr = q.front();
            q.pop();
            
            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
    }
    
    return result;
}

// Level with maximum width
int levelWithMaxWidth(TreeNode* root) {
    if (!root) return -1;
    
    int maxWidth = 0;
    int maxLevel = 0;
    int level = 0;
    
    queue<TreeNode*> q;
    q.push(root);
    
    while (!q.empty()) {
        int size = q.size();
        
        if (size > maxWidth) {
            maxWidth = size;
            maxLevel = level;
        }
        
        for (int i = 0; i < size; i++) {
            TreeNode* curr = q.front();
            q.pop();
            
            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
        
        level++;
    }
    
    return maxLevel;
}

// Complete binary tree node count (using width concept)
int countNodesComplete(TreeNode* root) {
    if (!root) return 0;
    
    int leftHeight = 0, rightHeight = 0;
    TreeNode* left = root;
    TreeNode* right = root;
    
    while (left) {
        leftHeight++;
        left = left->left;
    }
    
    while (right) {
        rightHeight++;
        right = right->right;
    }
    
    // If heights are equal, it's a perfect binary tree
    if (leftHeight == rightHeight) {
        return (1 << leftHeight) - 1;  // 2^h - 1
    }
    
    return 1 + countNodesComplete(root->left) + countNodesComplete(root->right);
}

// Check if tree is a full binary tree
bool isFullBinaryTree(TreeNode* root) {
    if (!root) return true;
    
    // If leaf node
    if (!root->left && !root->right) return true;
    
    // If both children exist
    if (root->left && root->right) {
        return isFullBinaryTree(root->left) && isFullBinaryTree(root->right);
    }
    
    return false;
}

// Check if tree is a perfect binary tree
bool isPerfectBinaryTree(TreeNode* root) {
    if (!root) return true;
    
    // Find depth of leftmost leaf
    int depth = 0;
    TreeNode* curr = root;
    while (curr->left) {
        depth++;
        curr = curr->left;
    }
    
    // Check if all leaves are at same level and internal nodes have 2 children
    function<bool(TreeNode*, int)> check = [&](TreeNode* node, int level) -> bool {
        if (!node) return true;
        
        // Leaf node should be at 'depth' level
        if (!node->left && !node->right) {
            return level == depth;
        }
        
        // Internal node must have both children
        if (!node->left || !node->right) return false;
        
        return check(node->left, level + 1) && check(node->right, level + 1);
    };
    
    return check(root, 0);
}

// Vertical width of tree
int verticalWidth(TreeNode* root) {
    if (!root) return 0;
    
    int minCol = 0, maxCol = 0;
    
    queue<pair<TreeNode*, int>> q;
    q.push({root, 0});
    
    while (!q.empty()) {
        auto [node, col] = q.front();
        q.pop();
        
        minCol = min(minCol, col);
        maxCol = max(maxCol, col);
        
        if (node->left) q.push({node->left, col - 1});
        if (node->right) q.push({node->right, col + 1});
    }
    
    return maxCol - minCol + 1;
}

// Count nodes at given level
int countNodesAtLevel(TreeNode* root, int level) {
    if (!root) return 0;
    if (level == 0) return 1;
    
    return countNodesAtLevel(root->left, level - 1) + 
           countNodesAtLevel(root->right, level - 1);
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
           3     2
          / \     \
         5   3     9
    */
    
    vector<int> nodes = {1, 3, 2, 5, 3, -1, 9};
    TreeNode* root = buildTree(nodes);
    
    cout << "=== Binary Tree Width Problems ===" << endl;
    
    cout << "\nMax width (node count): " << maxWidthCount(root) << endl;
    cout << "Max width (including gaps): " << widthOfBinaryTree(root) << endl;
    
    cout << "\nWidth at each level: ";
    for (int w : widthAtEachLevel(root)) cout << w << " ";
    cout << endl;
    
    cout << "Level with max width: " << levelWithMaxWidth(root) << endl;
    cout << "Vertical width: " << verticalWidth(root) << endl;
    
    // Perfect binary tree
    /*
              1
            /   \
           2     3
          / \   / \
         4   5 6   7
    */
    vector<int> perfectNodes = {1, 2, 3, 4, 5, 6, 7};
    TreeNode* perfect = buildTree(perfectNodes);
    
    cout << "\n=== Perfect Binary Tree [1,2,3,4,5,6,7] ===" << endl;
    cout << "Is full binary tree: " << (isFullBinaryTree(perfect) ? "Yes" : "No") << endl;
    cout << "Is perfect binary tree: " << (isPerfectBinaryTree(perfect) ? "Yes" : "No") << endl;
    cout << "Node count (optimized): " << countNodesComplete(perfect) << endl;
    
    // Complete but not perfect
    /*
              1
            /   \
           2     3
          / \   /
         4   5 6
    */
    vector<int> completeNodes = {1, 2, 3, 4, 5, 6};
    TreeNode* complete = buildTree(completeNodes);
    
    cout << "\n=== Complete Binary Tree [1,2,3,4,5,6] ===" << endl;
    cout << "Is full binary tree: " << (isFullBinaryTree(complete) ? "Yes" : "No") << endl;
    cout << "Is perfect binary tree: " << (isPerfectBinaryTree(complete) ? "Yes" : "No") << endl;
    cout << "Node count (optimized): " << countNodesComplete(complete) << endl;
    
    return 0;
}
















