/*
    Binary Tree Traversals
    ======================
    
    Different ways to visit all nodes of a binary tree:
    1. Inorder (Left, Root, Right) - Gives sorted order for BST
    2. Preorder (Root, Left, Right) - Used for copying tree
    3. Postorder (Left, Right, Root) - Used for deleting tree
    4. Level Order (BFS) - Visit level by level
    
    Time Complexity: O(n) for all traversals
    Space Complexity: O(h) for recursive, O(n) for iterative with stack/queue
*/

#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// ==================== INORDER TRAVERSAL ====================

// Recursive Inorder
void inorderRecursive(TreeNode* root, vector<int>& result) {
    if (!root) return;
    inorderRecursive(root->left, result);
    result.push_back(root->val);
    inorderRecursive(root->right, result);
}

// Iterative Inorder using Stack
vector<int> inorderIterative(TreeNode* root) {
    vector<int> result;
    stack<TreeNode*> st;
    TreeNode* curr = root;
    
    while (curr || !st.empty()) {
        // Go to leftmost node
        while (curr) {
            st.push(curr);
            curr = curr->left;
        }
        
        curr = st.top();
        st.pop();
        result.push_back(curr->val);
        curr = curr->right;
    }
    
    return result;
}

// ==================== PREORDER TRAVERSAL ====================

// Recursive Preorder
void preorderRecursive(TreeNode* root, vector<int>& result) {
    if (!root) return;
    result.push_back(root->val);
    preorderRecursive(root->left, result);
    preorderRecursive(root->right, result);
}

// Iterative Preorder using Stack
vector<int> preorderIterative(TreeNode* root) {
    vector<int> result;
    if (!root) return result;
    
    stack<TreeNode*> st;
    st.push(root);
    
    while (!st.empty()) {
        TreeNode* curr = st.top();
        st.pop();
        result.push_back(curr->val);
        
        // Push right first so left is processed first
        if (curr->right) st.push(curr->right);
        if (curr->left) st.push(curr->left);
    }
    
    return result;
}

// ==================== POSTORDER TRAVERSAL ====================

// Recursive Postorder
void postorderRecursive(TreeNode* root, vector<int>& result) {
    if (!root) return;
    postorderRecursive(root->left, result);
    postorderRecursive(root->right, result);
    result.push_back(root->val);
}

// Iterative Postorder using Two Stacks
vector<int> postorderIterative(TreeNode* root) {
    vector<int> result;
    if (!root) return result;
    
    stack<TreeNode*> st1, st2;
    st1.push(root);
    
    while (!st1.empty()) {
        TreeNode* curr = st1.top();
        st1.pop();
        st2.push(curr);
        
        if (curr->left) st1.push(curr->left);
        if (curr->right) st1.push(curr->right);
    }
    
    while (!st2.empty()) {
        result.push_back(st2.top()->val);
        st2.pop();
    }
    
    return result;
}

// Iterative Postorder using One Stack
vector<int> postorderOneStack(TreeNode* root) {
    vector<int> result;
    if (!root) return result;
    
    stack<TreeNode*> st;
    TreeNode* curr = root;
    TreeNode* lastVisited = nullptr;
    
    while (curr || !st.empty()) {
        while (curr) {
            st.push(curr);
            curr = curr->left;
        }
        
        TreeNode* top = st.top();
        
        if (top->right && top->right != lastVisited) {
            curr = top->right;
        } else {
            result.push_back(top->val);
            lastVisited = top;
            st.pop();
        }
    }
    
    return result;
}

// ==================== LEVEL ORDER TRAVERSAL ====================

// Level Order (BFS)
vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> result;
    if (!root) return result;
    
    queue<TreeNode*> q;
    q.push(root);
    
    while (!q.empty()) {
        int size = q.size();
        vector<int> level;
        
        for (int i = 0; i < size; i++) {
            TreeNode* curr = q.front();
            q.pop();
            level.push_back(curr->val);
            
            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
        
        result.push_back(level);
    }
    
    return result;
}

// Reverse Level Order (Bottom to Top)
vector<vector<int>> reverseLevelOrder(TreeNode* root) {
    vector<vector<int>> result = levelOrder(root);
    reverse(result.begin(), result.end());
    return result;
}

// ==================== ALL TRAVERSALS IN ONE PASS ====================

// Get all three traversals (Preorder, Inorder, Postorder) in single traversal
void allTraversals(TreeNode* root, vector<int>& pre, vector<int>& in, vector<int>& post) {
    if (!root) return;
    
    stack<pair<TreeNode*, int>> st;
    st.push({root, 1});
    
    while (!st.empty()) {
        auto& [node, state] = st.top();
        
        if (state == 1) {
            pre.push_back(node->val);
            state++;
            if (node->left) st.push({node->left, 1});
        } else if (state == 2) {
            in.push_back(node->val);
            state++;
            if (node->right) st.push({node->right, 1});
        } else {
            post.push_back(node->val);
            st.pop();
        }
    }
}

// Build tree helper
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

void printVector(const vector<int>& v, const string& name) {
    cout << name << ": ";
    for (int x : v) cout << x << " ";
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    /*
        Tree structure:
              1
            /   \
           2     3
          / \   / \
         4   5 6   7
    */
    
    vector<int> nodes = {1, 2, 3, 4, 5, 6, 7};
    TreeNode* root = buildTree(nodes);
    
    // Inorder Traversal
    vector<int> inResult;
    inorderRecursive(root, inResult);
    printVector(inResult, "Inorder (Recursive)");
    printVector(inorderIterative(root), "Inorder (Iterative)");
    
    // Preorder Traversal
    vector<int> preResult;
    preorderRecursive(root, preResult);
    printVector(preResult, "Preorder (Recursive)");
    printVector(preorderIterative(root), "Preorder (Iterative)");
    
    // Postorder Traversal
    vector<int> postResult;
    postorderRecursive(root, postResult);
    printVector(postResult, "Postorder (Recursive)");
    printVector(postorderIterative(root), "Postorder (Iterative)");
    printVector(postorderOneStack(root), "Postorder (One Stack)");
    
    // Level Order Traversal
    cout << "\nLevel Order: ";
    for (auto& level : levelOrder(root)) {
        cout << "[ ";
        for (int x : level) cout << x << " ";
        cout << "] ";
    }
    cout << endl;
    
    // Reverse Level Order
    cout << "Reverse Level Order: ";
    for (auto& level : reverseLevelOrder(root)) {
        cout << "[ ";
        for (int x : level) cout << x << " ";
        cout << "] ";
    }
    cout << endl;
    
    // All traversals in one pass
    cout << "\n=== All Traversals in One Pass ===" << endl;
    vector<int> pre, in, post;
    allTraversals(root, pre, in, post);
    printVector(pre, "Preorder");
    printVector(in, "Inorder");
    printVector(post, "Postorder");
    
    return 0;
}







