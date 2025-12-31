/*
    Binary Tree Iterators
    =====================
    
    Implement iterators for different traversals of binary tree.
    Useful for processing tree elements one at a time.
    
    Time Complexity: O(1) amortized for next()
    Space Complexity: O(h) where h is height
*/

#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// ==================== BST ITERATOR (INORDER) ====================

class BSTIterator {
    stack<TreeNode*> st;
    
    void pushLeft(TreeNode* node) {
        while (node) {
            st.push(node);
            node = node->left;
        }
    }
    
public:
    BSTIterator(TreeNode* root) {
        pushLeft(root);
    }
    
    int next() {
        TreeNode* top = st.top();
        st.pop();
        
        if (top->right) {
            pushLeft(top->right);
        }
        
        return top->val;
    }
    
    bool hasNext() {
        return !st.empty();
    }
};

// ==================== REVERSE BST ITERATOR ====================

class ReverseBSTIterator {
    stack<TreeNode*> st;
    
    void pushRight(TreeNode* node) {
        while (node) {
            st.push(node);
            node = node->right;
        }
    }
    
public:
    ReverseBSTIterator(TreeNode* root) {
        pushRight(root);
    }
    
    int next() {
        TreeNode* top = st.top();
        st.pop();
        
        if (top->left) {
            pushRight(top->left);
        }
        
        return top->val;
    }
    
    bool hasNext() {
        return !st.empty();
    }
};

// ==================== PREORDER ITERATOR ====================

class PreorderIterator {
    stack<TreeNode*> st;
    
public:
    PreorderIterator(TreeNode* root) {
        if (root) st.push(root);
    }
    
    int next() {
        TreeNode* top = st.top();
        st.pop();
        
        // Push right first, then left (so left is processed first)
        if (top->right) st.push(top->right);
        if (top->left) st.push(top->left);
        
        return top->val;
    }
    
    bool hasNext() {
        return !st.empty();
    }
};

// ==================== POSTORDER ITERATOR ====================

class PostorderIterator {
    stack<TreeNode*> st;
    TreeNode* lastVisited;
    
    void pushLeft(TreeNode* node) {
        while (node) {
            st.push(node);
            node = node->left;
        }
    }
    
public:
    PostorderIterator(TreeNode* root) : lastVisited(nullptr) {
        pushLeft(root);
    }
    
    int next() {
        while (!st.empty()) {
            TreeNode* top = st.top();
            
            // If right child exists and wasn't just visited
            if (top->right && top->right != lastVisited) {
                pushLeft(top->right);
            } else {
                st.pop();
                lastVisited = top;
                return top->val;
            }
        }
        
        return -1; // Should not reach
    }
    
    bool hasNext() {
        return !st.empty();
    }
};

// ==================== LEVEL ORDER ITERATOR ====================

class LevelOrderIterator {
    queue<TreeNode*> q;
    
public:
    LevelOrderIterator(TreeNode* root) {
        if (root) q.push(root);
    }
    
    int next() {
        TreeNode* front = q.front();
        q.pop();
        
        if (front->left) q.push(front->left);
        if (front->right) q.push(front->right);
        
        return front->val;
    }
    
    bool hasNext() {
        return !q.empty();
    }
};

// ==================== TWO SUM BST USING ITERATORS ====================

bool findTarget(TreeNode* root, int k) {
    BSTIterator left(root);
    ReverseBSTIterator right(root);
    
    int l = left.next();
    int r = right.next();
    
    while (l < r) {
        int sum = l + r;
        
        if (sum == k) return true;
        
        if (sum < k) {
            l = left.next();
        } else {
            r = right.next();
        }
    }
    
    return false;
}

// ==================== MERGE TWO BST ITERATORS ====================

class MergedBSTIterator {
    BSTIterator it1, it2;
    int val1, val2;
    bool has1, has2;
    
    void advance1() {
        has1 = it1.hasNext();
        if (has1) val1 = it1.next();
    }
    
    void advance2() {
        has2 = it2.hasNext();
        if (has2) val2 = it2.next();
    }
    
public:
    MergedBSTIterator(TreeNode* root1, TreeNode* root2) : it1(root1), it2(root2) {
        advance1();
        advance2();
    }
    
    int next() {
        if (!has1) {
            int ret = val2;
            advance2();
            return ret;
        }
        
        if (!has2) {
            int ret = val1;
            advance1();
            return ret;
        }
        
        if (val1 <= val2) {
            int ret = val1;
            advance1();
            return ret;
        } else {
            int ret = val2;
            advance2();
            return ret;
        }
    }
    
    bool hasNext() {
        return has1 || has2;
    }
};

// ==================== PEEKING ITERATOR ====================

class PeekingBSTIterator {
    BSTIterator it;
    bool hasPeeked;
    int peekedVal;
    
public:
    PeekingBSTIterator(TreeNode* root) : it(root), hasPeeked(false) {}
    
    int peek() {
        if (!hasPeeked) {
            peekedVal = it.next();
            hasPeeked = true;
        }
        return peekedVal;
    }
    
    int next() {
        if (hasPeeked) {
            hasPeeked = false;
            return peekedVal;
        }
        return it.next();
    }
    
    bool hasNext() {
        return hasPeeked || it.hasNext();
    }
};

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
        BST:
              7
            /   \
           3     15
                /  \
               9    20
    */
    
    vector<int> nodes = {7, 3, 15, -1, -1, 9, 20};
    TreeNode* root = buildTree(nodes);
    
    cout << "=== Binary Tree Iterators ===" << endl;
    
    // Inorder Iterator
    cout << "\nInorder (BST Iterator): ";
    BSTIterator bstIt(root);
    while (bstIt.hasNext()) {
        cout << bstIt.next() << " ";
    }
    cout << endl;
    
    // Reverse Inorder
    cout << "Reverse Inorder: ";
    ReverseBSTIterator revIt(root);
    while (revIt.hasNext()) {
        cout << revIt.next() << " ";
    }
    cout << endl;
    
    // Preorder Iterator
    cout << "Preorder: ";
    PreorderIterator preIt(root);
    while (preIt.hasNext()) {
        cout << preIt.next() << " ";
    }
    cout << endl;
    
    // Postorder Iterator
    cout << "Postorder: ";
    PostorderIterator postIt(root);
    while (postIt.hasNext()) {
        cout << postIt.next() << " ";
    }
    cout << endl;
    
    // Level Order Iterator
    cout << "Level Order: ";
    LevelOrderIterator levelIt(root);
    while (levelIt.hasNext()) {
        cout << levelIt.next() << " ";
    }
    cout << endl;
    
    // Two Sum in BST
    cout << "\nTwo Sum k=22: " << (findTarget(root, 22) ? "Found" : "Not Found") << endl;
    cout << "Two Sum k=25: " << (findTarget(root, 25) ? "Found" : "Not Found") << endl;
    
    // Merge two BSTs
    vector<int> bst1Nodes = {2, 1, 4};
    vector<int> bst2Nodes = {3, -1, 5};
    TreeNode* bst1 = buildTree(bst1Nodes);
    TreeNode* bst2 = buildTree(bst2Nodes);
    
    cout << "\nMerged BST traversal: ";
    MergedBSTIterator mergedIt(bst1, bst2);
    while (mergedIt.hasNext()) {
        cout << mergedIt.next() << " ";
    }
    cout << endl;
    
    // Peeking Iterator
    cout << "\nPeeking Iterator demo:" << endl;
    PeekingBSTIterator peekIt(root);
    cout << "Peek: " << peekIt.peek() << endl;
    cout << "Peek again: " << peekIt.peek() << endl;
    cout << "Next: " << peekIt.next() << endl;
    cout << "Next: " << peekIt.next() << endl;
    
    return 0;
}

