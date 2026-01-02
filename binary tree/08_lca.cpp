/*
    Lowest Common Ancestor (LCA)
    ============================
    
    The LCA of two nodes p and q in a tree is the lowest (deepest) node that has
    both p and q as descendants (where a node can be a descendant of itself).
    
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

// ==================== LCA IN BINARY TREE ====================

// Method 1: Recursive approach
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (!root || root == p || root == q) return root;
    
    TreeNode* left = lowestCommonAncestor(root->left, p, q);
    TreeNode* right = lowestCommonAncestor(root->right, p, q);
    
    if (left && right) return root;  // p and q are on different sides
    
    return left ? left : right;
}

// Method 2: Using path finding
bool findPath(TreeNode* root, TreeNode* target, vector<TreeNode*>& path) {
    if (!root) return false;
    
    path.push_back(root);
    
    if (root == target) return true;
    
    if (findPath(root->left, target, path) || 
        findPath(root->right, target, path)) {
        return true;
    }
    
    path.pop_back();
    return false;
}

TreeNode* lcaUsingPath(TreeNode* root, TreeNode* p, TreeNode* q) {
    vector<TreeNode*> pathP, pathQ;
    
    findPath(root, p, pathP);
    findPath(root, q, pathQ);
    
    TreeNode* lca = nullptr;
    int i = 0;
    while (i < pathP.size() && i < pathQ.size()) {
        if (pathP[i] == pathQ[i]) {
            lca = pathP[i];
        } else {
            break;
        }
        i++;
    }
    
    return lca;
}

// Method 3: Iterative using parent pointers
TreeNode* lcaIterative(TreeNode* root, TreeNode* p, TreeNode* q) {
    unordered_map<TreeNode*, TreeNode*> parent;
    stack<TreeNode*> st;
    
    parent[root] = nullptr;
    st.push(root);
    
    // Build parent map until both p and q are found
    while (parent.find(p) == parent.end() || parent.find(q) == parent.end()) {
        TreeNode* curr = st.top();
        st.pop();
        
        if (curr->left) {
            parent[curr->left] = curr;
            st.push(curr->left);
        }
        if (curr->right) {
            parent[curr->right] = curr;
            st.push(curr->right);
        }
    }
    
    // Find ancestors of p
    unordered_set<TreeNode*> ancestors;
    while (p) {
        ancestors.insert(p);
        p = parent[p];
    }
    
    // First ancestor of q that is also ancestor of p
    while (ancestors.find(q) == ancestors.end()) {
        q = parent[q];
    }
    
    return q;
}

// ==================== LCA IN BST ====================

// LCA in BST - Recursive
TreeNode* lcaBST(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (!root) return nullptr;
    
    if (p->val < root->val && q->val < root->val) {
        return lcaBST(root->left, p, q);
    }
    
    if (p->val > root->val && q->val > root->val) {
        return lcaBST(root->right, p, q);
    }
    
    return root;
}

// LCA in BST - Iterative
TreeNode* lcaBSTIterative(TreeNode* root, TreeNode* p, TreeNode* q) {
    while (root) {
        if (p->val < root->val && q->val < root->val) {
            root = root->left;
        } else if (p->val > root->val && q->val > root->val) {
            root = root->right;
        } else {
            return root;
        }
    }
    return nullptr;
}

// ==================== ADVANCED LCA PROBLEMS ====================

// LCA of multiple nodes
TreeNode* lcaMultiple(TreeNode* root, vector<TreeNode*>& nodes) {
    unordered_set<TreeNode*> nodeSet(nodes.begin(), nodes.end());
    
    function<TreeNode*(TreeNode*)> dfs = [&](TreeNode* node) -> TreeNode* {
        if (!node || nodeSet.count(node)) return node;
        
        TreeNode* left = dfs(node->left);
        TreeNode* right = dfs(node->right);
        
        if (left && right) return node;
        return left ? left : right;
    };
    
    return dfs(root);
}

// Distance between two nodes
int findLevel(TreeNode* root, TreeNode* target, int level) {
    if (!root) return -1;
    if (root == target) return level;
    
    int left = findLevel(root->left, target, level + 1);
    if (left != -1) return left;
    
    return findLevel(root->right, target, level + 1);
}

int distanceBetweenNodes(TreeNode* root, TreeNode* p, TreeNode* q) {
    TreeNode* lca = lowestCommonAncestor(root, p, q);
    
    int distP = findLevel(lca, p, 0);
    int distQ = findLevel(lca, q, 0);
    
    return distP + distQ;
}

// LCA with node existence check
TreeNode* lcaWithCheck(TreeNode* root, TreeNode* p, TreeNode* q) {
    bool foundP = false, foundQ = false;
    
    function<TreeNode*(TreeNode*)> dfs = [&](TreeNode* node) -> TreeNode* {
        if (!node) return nullptr;
        
        TreeNode* left = dfs(node->left);
        TreeNode* right = dfs(node->right);
        
        if (node == p) {
            foundP = true;
            return node;
        }
        if (node == q) {
            foundQ = true;
            return node;
        }
        
        if (left && right) return node;
        return left ? left : right;
    };
    
    TreeNode* lca = dfs(root);
    
    // Verify both nodes exist
    if (foundP && foundQ) return lca;
    if (foundP && !foundQ) {
        // Check if q is under p
        foundQ = (findLevel(p, q, 0) != -1);
    }
    if (foundQ && !foundP) {
        // Check if p is under q
        foundP = (findLevel(q, p, 0) != -1);
    }
    
    return (foundP && foundQ) ? lca : nullptr;
}

// All ancestors of a node
vector<int> findAncestors(TreeNode* root, TreeNode* target) {
    vector<int> ancestors;
    
    function<bool(TreeNode*)> dfs = [&](TreeNode* node) -> bool {
        if (!node) return false;
        if (node == target) return true;
        
        if (dfs(node->left) || dfs(node->right)) {
            ancestors.push_back(node->val);
            return true;
        }
        
        return false;
    };
    
    dfs(root);
    return ancestors;
}

// Check if node is ancestor of another
bool isAncestor(TreeNode* ancestor, TreeNode* descendant) {
    if (!ancestor) return false;
    if (ancestor == descendant) return true;
    
    return isAncestor(ancestor->left, descendant) || 
           isAncestor(ancestor->right, descendant);
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

TreeNode* findNode(TreeNode* root, int val) {
    if (!root) return nullptr;
    if (root->val == val) return root;
    
    TreeNode* left = findNode(root->left, val);
    if (left) return left;
    return findNode(root->right, val);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    /*
        Binary Tree:
              3
            /   \
           5     1
          / \   / \
         6   2 0   8
            / \
           7   4
    */
    
    vector<int> nodes = {3, 5, 1, 6, 2, 0, 8, -1, -1, 7, 4};
    TreeNode* root = buildTree(nodes);
    
    TreeNode* n5 = findNode(root, 5);
    TreeNode* n1 = findNode(root, 1);
    TreeNode* n6 = findNode(root, 6);
    TreeNode* n4 = findNode(root, 4);
    TreeNode* n7 = findNode(root, 7);
    
    cout << "=== Lowest Common Ancestor ===" << endl;
    
    // LCA in Binary Tree
    cout << "\nLCA of 5 and 1: " << lowestCommonAncestor(root, n5, n1)->val << endl;
    cout << "LCA of 5 and 4: " << lowestCommonAncestor(root, n5, n4)->val << endl;
    cout << "LCA of 6 and 4: " << lowestCommonAncestor(root, n6, n4)->val << endl;
    cout << "LCA of 7 and 4: " << lowestCommonAncestor(root, n7, n4)->val << endl;
    
    // Using path method
    cout << "\nLCA using path (6 and 4): " << lcaUsingPath(root, n6, n4)->val << endl;
    
    // Distance between nodes
    cout << "\nDistance between 6 and 4: " << distanceBetweenNodes(root, n6, n4) << endl;
    cout << "Distance between 5 and 1: " << distanceBetweenNodes(root, n5, n1) << endl;
    
    // Ancestors
    cout << "\nAncestors of 4: ";
    for (int x : findAncestors(root, n4)) cout << x << " ";
    cout << endl;
    
    // LCA in BST
    /*
        BST:
              6
            /   \
           2     8
          / \   / \
         0   4 7   9
            / \
           3   5
    */
    
    vector<int> bstNodes = {6, 2, 8, 0, 4, 7, 9, -1, -1, 3, 5};
    TreeNode* bst = buildTree(bstNodes);
    
    TreeNode* bst2 = findNode(bst, 2);
    TreeNode* bst8 = findNode(bst, 8);
    TreeNode* bst4 = findNode(bst, 4);
    
    cout << "\n=== LCA in BST ===" << endl;
    cout << "LCA of 2 and 8: " << lcaBST(bst, bst2, bst8)->val << endl;
    cout << "LCA of 2 and 4: " << lcaBST(bst, bst2, bst4)->val << endl;
    
    return 0;
}







