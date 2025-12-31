/*
    Binary Tree Representation and Basic Operations
    ================================================
    
    A binary tree is a hierarchical data structure where each node has at most two children,
    referred to as left child and right child.
    
    Time Complexity: O(n) for most operations
    Space Complexity: O(h) where h is height of tree (for recursive calls)
*/

#include <bits/stdc++.h>
using namespace std;

// Node structure for Binary Tree
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* l, TreeNode* r) : val(x), left(l), right(r) {}
};

// Build tree from level order input (-1 represents NULL)
TreeNode* buildTree(vector<int>& nodes) {
    if (nodes.empty() || nodes[0] == -1) return nullptr;
    
    TreeNode* root = new TreeNode(nodes[0]);
    queue<TreeNode*> q;
    q.push(root);
    
    int i = 1;
    while (!q.empty() && i < nodes.size()) {
        TreeNode* curr = q.front();
        q.pop();
        
        // Left child
        if (i < nodes.size() && nodes[i] != -1) {
            curr->left = new TreeNode(nodes[i]);
            q.push(curr->left);
        }
        i++;
        
        // Right child
        if (i < nodes.size() && nodes[i] != -1) {
            curr->right = new TreeNode(nodes[i]);
            q.push(curr->right);
        }
        i++;
    }
    
    return root;
}

// Count total nodes
int countNodes(TreeNode* root) {
    if (!root) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

// Count leaf nodes
int countLeaves(TreeNode* root) {
    if (!root) return 0;
    if (!root->left && !root->right) return 1;
    return countLeaves(root->left) + countLeaves(root->right);
}

// Count internal nodes (non-leaf)
int countInternalNodes(TreeNode* root) {
    if (!root || (!root->left && !root->right)) return 0;
    return 1 + countInternalNodes(root->left) + countInternalNodes(root->right);
}

// Find maximum value in tree
int findMax(TreeNode* root) {
    if (!root) return INT_MIN;
    return max({root->val, findMax(root->left), findMax(root->right)});
}

// Find minimum value in tree
int findMin(TreeNode* root) {
    if (!root) return INT_MAX;
    return min({root->val, findMin(root->left), findMin(root->right)});
}

// Search for a value in tree
bool search(TreeNode* root, int target) {
    if (!root) return false;
    if (root->val == target) return true;
    return search(root->left, target) || search(root->right, target);
}

// Insert at first available position (level order)
TreeNode* insert(TreeNode* root, int val) {
    if (!root) return new TreeNode(val);
    
    queue<TreeNode*> q;
    q.push(root);
    
    while (!q.empty()) {
        TreeNode* curr = q.front();
        q.pop();
        
        if (!curr->left) {
            curr->left = new TreeNode(val);
            return root;
        } else {
            q.push(curr->left);
        }
        
        if (!curr->right) {
            curr->right = new TreeNode(val);
            return root;
        } else {
            q.push(curr->right);
        }
    }
    
    return root;
}

// Delete deepest node
void deleteDeepest(TreeNode* root, TreeNode* target) {
    queue<TreeNode*> q;
    q.push(root);
    
    while (!q.empty()) {
        TreeNode* curr = q.front();
        q.pop();
        
        if (curr == target) {
            delete curr;
            return;
        }
        
        if (curr->left) {
            if (curr->left == target) {
                delete curr->left;
                curr->left = nullptr;
                return;
            }
            q.push(curr->left);
        }
        
        if (curr->right) {
            if (curr->right == target) {
                delete curr->right;
                curr->right = nullptr;
                return;
            }
            q.push(curr->right);
        }
    }
}

// Delete a node with given value
TreeNode* deleteNode(TreeNode* root, int val) {
    if (!root) return nullptr;
    if (!root->left && !root->right) {
        if (root->val == val) {
            delete root;
            return nullptr;
        }
        return root;
    }
    
    queue<TreeNode*> q;
    q.push(root);
    TreeNode* target = nullptr;
    TreeNode* deepest = nullptr;
    
    while (!q.empty()) {
        deepest = q.front();
        q.pop();
        
        if (deepest->val == val) target = deepest;
        if (deepest->left) q.push(deepest->left);
        if (deepest->right) q.push(deepest->right);
    }
    
    if (target) {
        target->val = deepest->val;
        deleteDeepest(root, deepest);
    }
    
    return root;
}

// Print tree structure (for visualization)
void printTree(TreeNode* root, string prefix = "", bool isLeft = true) {
    if (!root) return;
    
    cout << prefix;
    cout << (isLeft ? "├──" : "└──");
    cout << root->val << endl;
    
    printTree(root->left, prefix + (isLeft ? "│   " : "    "), true);
    printTree(root->right, prefix + (isLeft ? "│   " : "    "), false);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // Example: Build tree from level order
    vector<int> nodes = {1, 2, 3, 4, 5, -1, 6, -1, -1, 7, 8};
    TreeNode* root = buildTree(nodes);
    
    /*
        Tree structure:
              1
            /   \
           2     3
          / \     \
         4   5     6
            / \
           7   8
    */
    
    cout << "Tree Structure:" << endl;
    printTree(root);
    
    cout << "\nTotal nodes: " << countNodes(root) << endl;
    cout << "Leaf nodes: " << countLeaves(root) << endl;
    cout << "Internal nodes: " << countInternalNodes(root) << endl;
    cout << "Maximum value: " << findMax(root) << endl;
    cout << "Minimum value: " << findMin(root) << endl;
    
    cout << "\nSearching for 5: " << (search(root, 5) ? "Found" : "Not Found") << endl;
    cout << "Searching for 10: " << (search(root, 10) ? "Found" : "Not Found") << endl;
    
    // Insert a new node
    root = insert(root, 9);
    cout << "\nAfter inserting 9:" << endl;
    printTree(root);
    
    return 0;
}

